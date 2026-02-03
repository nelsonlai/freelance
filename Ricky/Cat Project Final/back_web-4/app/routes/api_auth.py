from flask import Blueprint, request, jsonify, current_app
from werkzeug.security import check_password_hash

from ..services.storage import Storage
from ..utils.auth import issue_jwt, require_jwt


bp = Blueprint("api_auth", __name__, url_prefix="/api/auth")


@bp.post("/login")
def api_login():
    """Email + password login. Returns JWT token."""
    data = request.get_json(silent=True) or {}
    email = (data.get("email") or "").strip().lower()
    password = data.get("password") or ""

    if not email or not password:
        return jsonify({"status": "error", "message": "email and password are required"}), 400

    store = Storage(current_app.config["SQLITE_PATH"])
    user = store.get_user_by_email(email)
    if not user or not check_password_hash(user["password_hash"], password):
        return jsonify({"status": "error", "message": "invalid credentials"}), 401

    token = issue_jwt(user_id=user["id"], email=user["email"])
    return jsonify({
        "status": "ok",
        "token": token,
        "user": {"email": user["email"], "role": user.get("role", "user")},
    }), 200


@bp.get("/me")
def api_me():
    """Return current user from JWT."""
    user = require_jwt()
    store = Storage(current_app.config["SQLITE_PATH"])
    db_user = store.get_user_by_email(user.get("email", ""))
    if not db_user:
        return jsonify({"status": "error", "message": "user not found"}), 404
    return jsonify({
        "status": "ok",
        "user": {"id": db_user["id"], "email": db_user["email"], "role": db_user.get("role", "user")},
    }), 200
