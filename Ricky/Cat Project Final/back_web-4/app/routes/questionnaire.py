import uuid
from flask import Blueprint, request, jsonify, current_app
from ..utils.auth import require_jwt
from ..services.storage import Storage

bp = Blueprint("questionnaire", __name__, url_prefix="/api")

@bp.post("/questionnaire")
def submit_questionnaire():
    user = require_jwt()
    email = user.get("email")

    payload = request.get_json(silent=True)
    if not payload:
        return jsonify({
            "status": "error",
            "message": "empty payload"
        }), 400

    report_id = str(uuid.uuid4())

    store = Storage(current_app.config["SQLITE_PATH"])
    store.save_report(
        report_id=report_id,
        payload=payload,
        result={},              # 先空，之後可補 Poe
        owner_email=email
    )

    return jsonify({
        "status": "ok",
        "report_id": report_id
    }), 201
