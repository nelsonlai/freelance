from __future__ import annotations

from flask import Blueprint, render_template, request, redirect, session, current_app
from werkzeug.security import check_password_hash, generate_password_hash

from ..utils.auth import require_admin
from ..services.storage import Storage

bp = Blueprint("admin", __name__, url_prefix="/admin")


def _store() -> Storage:
    return Storage(current_app.config["SQLITE_PATH"])


@bp.route("/login", methods=["GET", "POST"])
def login():
    store = _store()

    if request.method == "GET":
        return render_template("admin/login.html", error=None)

    email = (request.form.get("email") or "").strip().lower()
    password = request.form.get("password") or ""

    user = store.get_user_by_email(email)
    if not user:
        return render_template("admin/login.html", error="Invalid credentials")

    # role check
    role = (user.get("role") or "user").lower()
    if role not in ("admin", "super_admin"):
        return render_template("admin/login.html", error="Not an admin account")

    if not check_password_hash(user["password_hash"], password):
        return render_template("admin/login.html", error="Invalid credentials")

    session["admin_user"] = {
        "id": user["id"],
        "email": user["email"],
        "role": role,
    }

    nxt = request.args.get("next") or "/admin"
    return redirect(nxt)


@bp.get("/logout")
def logout():
    session.pop("admin_user",None)   
    return redirect("/admin/login")


@bp.get("/")
@require_admin
def dashboard():
    store = _store()

    stats = {
        "users": store.count_users(),
        "reports": store.count_reports(),
        "webhooks": store.count_webhooks(),
    }

    return render_template(
        "admin/dashboard.html",
        stats=stats,
        admin_email=session.get("admin_email"),
        admin_role=session.get("admin_role"),
    )


@bp.route("/users", methods=["GET", "POST"])
@require_admin
def users():
    store = _store()

    # create admin/super_admin quickly
    if request.method == "POST":
        if session.get("admin_role") != "super_admin":
            return redirect("/admin/users")

        email = (request.form.get("email") or "").strip().lower()
        password = request.form.get("password") or ""
        role = (request.form.get("role") or "admin").strip().lower()

        if email and password and role in ("admin", "super_admin"):
            if not store.get_user_by_email(email):
                store.create_user_with_role(email=email, password_hash=generate_password_hash(password, method='pbkdf2:sha256'), role=role)

        return redirect("/admin/users")

    items = store.list_users(limit=200)
    return render_template(
        "admin/users.html",
        users=items,
        admin_role=session.get("admin_role"),
    )


@bp.post("/users/<int:user_id>/role")
@require_admin
def set_user_role(user_id: int):
    if session.get("admin_role") != "super_admin":
        return redirect("/admin/users")

    role = (request.form.get("role") or "user").strip().lower()
    if role not in ("user", "admin", "super_admin"):
        role = "user"

    store = _store()
    store.set_user_role(user_id=user_id, role=role)
    return redirect("/admin/users")


@bp.get("/reports")
@require_admin
def reports():
    store = _store()
    limit = int(request.args.get("limit", "50"))
    items = store.list_reports(owner_email=None, limit=limit)
    return render_template("admin/reports.html", reports=items)


@bp.get("/report/<report_id>")
@require_admin
def report_detail(report_id: str):
    store = _store()
    data = store.get_report(report_id)
    if not data:
        return render_template("admin/report_detail.html", report=None)

    return render_template("admin/report_detail.html", report=data)


@bp.get("/webhooks")
@require_admin
def webhooks():
    store = _store()
    limit = int(request.args.get("limit", "100"))
    items = store.list_webhooks(limit=limit)
    return render_template("admin/webhooks.html", webhooks=items)
