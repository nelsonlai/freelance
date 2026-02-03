from flask import Blueprint, jsonify, current_app, request
from ..utils.auth import require_jwt
from ..services.storage import Storage

bp = Blueprint("reports", __name__, url_prefix="/api")

@bp.get("/reports")
def list_reports():
    user = require_jwt()
    email = user.get("email")

    limit = int(request.args.get("limit", "50"))
    store = Storage(current_app.config["SQLITE_PATH"])
    items = store.list_reports(owner_email=email, limit=limit)

    return jsonify({"status": "ok", "reports": items})

@bp.get("/report/<report_id>")
def get_report(report_id: str):
    user = require_jwt()
    email = user.get("email")

    store = Storage(current_app.config["SQLITE_PATH"])
    data = store.get_report(report_id)
    if not data:
        return jsonify({"status": "not_found"}), 404

    # 權限：只能看自己的
    if data.get("owner_email") and data["owner_email"] != email:
        return jsonify({"status": "forbidden"}), 403

    return jsonify({"status": "ok", "data": data})
