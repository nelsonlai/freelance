from flask import Blueprint, request, render_template, redirect, url_for, session, current_app
from werkzeug.security import check_password_hash
from ..services.storage import Storage

bp = Blueprint("admin", __name__, url_prefix="/admin")


@bp.get("/login")
def login():
    return render_template("admin/login.html")


@bp.post("/login")
def login_post():
    email = (request.form.get("email") or "").strip().lower()
    password = request.form.get("password") or ""

    store = Storage(current_app.config["SQLITE_PATH"])
    user = store.get_user_by_email(email)

    if not user or not check_password_hash(user["password_hash"], password):
        return render_template(
            "admin/login.html",
            error="Invalid credentials"
        )

    # ✅ 關鍵：建立 admin session
    session["admin_user"] = {
        "id": user["id"],
        "email": user["email"],
        "role": user["role"],
    }

    return redirect(url_for("admin.dashboard"))


@bp.get("/logout")
def logout():
    session.pop("admin_user", None)
    return redirect(url_for("admin.login"))
