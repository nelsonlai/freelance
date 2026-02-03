import jwt
from functools import wraps
from flask import request, abort, current_app, session, redirect, url_for, jsonify

def require_make_secret():
    expected = current_app.config["MAKE_WEBHOOK_SECRET"]
    got = request.headers.get("X-Make-Secret", "")
    if not expected or got != expected:
        abort(401, description="Invalid Make secret")

def issue_jwt(user_id: int, email: str):
    secret = current_app.config["JWT_SECRET"]
    if not secret:
        raise RuntimeError("JWT_SECRET is missing in .env")

    payload = {"user_id": user_id, "email": email}
    token = jwt.encode(payload, secret, algorithm="HS256")
    return token

def require_jwt():
    auth = request.headers.get("Authorization", "")
    if not auth.startswith("Bearer "):
        abort(401, description="Missing Bearer token")

    token = auth.split(" ", 1)[1].strip()
    secret = current_app.config["JWT_SECRET"]
    if not secret:
        abort(500, description="JWT_SECRET not configured")

    try:
        return jwt.decode(token, secret, algorithms=["HS256"])
    except Exception:
        abort(401, description="Invalid token")

# =========================================================
# Admin session（給後台用）
# =========================================================
def require_admin(func):
    """
    Decorator: 保護 /admin 與 /api/admin/*
    使用 Flask session
    """
    @wraps(func)
    def wrapper(*args, **kwargs):
        admin = session.get("admin_user")

        if not admin:
            # API request → 回 401
            if request.path.startswith("/api/"):
                return jsonify({"error": "Unauthorized"}), 401

            # Page request → 導向 admin login
            return redirect(url_for("admin.login"))

        return func(*args, **kwargs)

    return wrapper