from flask import Blueprint, request, redirect, url_for, jsonify, current_app, session
from werkzeug.security import generate_password_hash, check_password_hash
from ..services.storage import Storage
from ..utils.auth import issue_jwt

bp = Blueprint("auth", __name__, url_prefix="/auth")


# =========================
# Register（註冊）
# =========================
@bp.post("/register")
def register():
    data = request.get_json(silent=True) or {}

    email = (data.get("email") or "").strip().lower()
    password = data.get("password") or ""

    if not email or not password:
        return jsonify({
            "status": "error",
            "message": "email and password are required"
        }), 400

    if len(password) < 8:
        return jsonify({
            "status": "error",
            "message": "password must be at least 8 characters"
        }), 400

    store = Storage(current_app.config["SQLITE_PATH"])

    # 已存在使用者
    if store.get_user_by_email(email):
        return jsonify({
            "status": "error",
            "message": "user already exists"
        }), 409

    password_hash = generate_password_hash(password, method='pbkdf2:sha256')
    store.create_user(email, password_hash)

    return jsonify({
        "status": "ok",
        "message": "user registered"
    }), 201


# =========================
# Login（登入）
# =========================
@bp.post("/login")
def login():
    data = request.get_json(silent=True) or {}

    email = (data.get("email") or "").strip().lower()
    password = data.get("password") or ""

    if not email or not password:
        return jsonify({
            "status": "error",
            "message": "email and password are required"
        }), 400

    store = Storage(current_app.config["SQLITE_PATH"])
    user = store.get_user_by_email(email)

    # 帳密錯誤（不要透露是哪一個錯）
    if not user or not check_password_hash(user["password_hash"], password):
        return jsonify({
            "status": "error",
            "message": "invalid credentials"
        }), 401

    # 發 JWT
    token = issue_jwt(
        user_id=user["id"],
        email=user["email"]
    )

    return jsonify({
        "status": "ok",
        "token": token,
        "user": {
            "email": user["email"]
        }
    }), 200
# =========================================================
# Admin session（給後台用）
# =========================================================
def require_admin():
    """
    保護 /admin 與 /api/admin/*
    使用 Flask session
    """
    admin = session.get("admin_user")

    if not admin:
        # API request → 回 401
        if request.path.startswith("/api/"):
            return jsonify({"error": "Unauthorized"}), 401

        # Page request → 導向 admin login
        return redirect(url_for("admin.login"))

    return admin









