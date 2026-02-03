import base64
import os
import re
import uuid
from typing import Optional
from flask import Blueprint, request, jsonify, current_app
from werkzeug.security import generate_password_hash

from ..services.storage import Storage
from ..utils.auth import issue_jwt


bp = Blueprint("cat_register", __name__, url_prefix="/api")

_EMAIL_RE = re.compile(r"^[^\s@]+@[^\s@]+\.[^\s@]+$")


def _save_data_url_to_file(data_url: str, upload_dir: str) -> Optional[str]:
    """Accepts a data URL (data:image/png;base64,...) and saves it into upload_dir.
    Returns relative file path or None if not provided.
    """
    if not data_url:
        return None
    if not data_url.startswith("data:"):
        return None

    try:
        header, b64 = data_url.split(",", 1)
        # header example: data:image/png;base64
        ext = "bin"
        if ";" in header:
            mime = header[5:].split(";", 1)[0]
            if "/" in mime:
                ext = mime.split("/", 1)[1].strip() or "bin"
        raw = base64.b64decode(b64)
    except Exception:
        return None

    os.makedirs(upload_dir, exist_ok=True)
    filename = f"cat_{uuid.uuid4().hex}.{ext}"
    path = os.path.join(upload_dir, filename)
    with open(path, "wb") as f:
        f.write(raw)

    # store relative path for serving later if you add static route
    return filename




@bp.route("/cat-questionnaire", methods=["OPTIONS"])
def cat_questionnaire_options():
    return jsonify({"ok": True}), 200
@bp.post("/cat-questionnaire")
def register_with_cat():
    """Register user (email+password) and upsert the single cat profile."""
    data = request.get_json(silent=True) or {}

    email = (data.get("email") or "").strip().lower()
    password = data.get("password") or ""

    if not email or not password:
        return jsonify({"status": "error", "message": "email and password are required"}), 400
    if not _EMAIL_RE.match(email):
        return jsonify({"status": "error", "message": "invalid email"}), 400
    if len(password) < 8:
        return jsonify({"status": "error", "message": "password must be at least 8 characters"}), 400

    # Cat fields
    name = (data.get("cat_name") or "").strip()
    breed = (data.get("breed") or data.get("cat_breed") or "").strip()
    age = data.get("age")
    gender = (data.get("gender") or "").strip()
    health = (data.get("health") or "").strip()
    vaccinations = data.get("vaccines") or data.get("vaccinations") or []
    photo_data_url = data.get("photo_data_url") or ""

    if not name or not breed:
        return jsonify({"status": "error", "message": "cat_name and breed are required"}), 400
    try:
        age_int = int(age)
        if age_int < 0:
            raise ValueError
    except Exception:
        return jsonify({"status": "error", "message": "invalid age"}), 400
    if not gender:
        return jsonify({"status": "error", "message": "gender is required"}), 400
    if not health:
        return jsonify({"status": "error", "message": "health is required"}), 400

    if not isinstance(vaccinations, list):
        vaccinations = []

    required_v = {"FVRCP", "Rabies", "FeLV", "FIP"}
    if not required_v.issubset(set(vaccinations)):
        return jsonify({"status": "error", "message": "all four core vaccines are required"}), 400

    store = Storage(current_app.config["SQLITE_PATH"])
    if store.get_user_by_email(email):
        return jsonify({"status": "error", "message": "user already exists"}), 409

    password_hash = generate_password_hash(password, method='pbkdf2:sha256')
    store.create_user(email, password_hash)
    user = store.get_user_by_email(email)
    if not user:
        return jsonify({"status": "error", "message": "failed to create user"}), 500

    upload_dir = current_app.config.get("UPLOAD_DIR", "./uploads")
    saved_name = _save_data_url_to_file(photo_data_url, upload_dir)
    photo_path = None
    if saved_name:
        photo_path = f"/uploads/{saved_name}"

    profile = dict(data)
    # keep only safe fields if you want; for now store full questionnaire
    cat_id = store.upsert_cat_for_user(
        user_id=user["id"],
        name=name,
        breed=breed,
        age=age_int,
        gender=gender,
        health=health,
        vaccinations=vaccinations,
        profile=profile,
        photo_path=photo_path,
    )

    token = issue_jwt(user_id=user["id"], email=user["email"])
    return jsonify({
        "status": "ok",
        "token": token,
        "user": {"id": user["id"], "email": user["email"]},
        "cat": {"id": cat_id, "name": name, "breed": breed, "age": age_int, "gender": gender, "health": health, "vaccinations": vaccinations, "photo_path": photo_path},
    }), 201
