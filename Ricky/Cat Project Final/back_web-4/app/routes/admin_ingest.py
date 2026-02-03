from flask import Blueprint, jsonify, current_app, request
from ..services.storage import Storage

bp = Blueprint("admin_ingest", __name__, url_prefix="/api/admin")

@bp.post("/form-ingest")
def form_ingest():
    data = request.get_json(silent=True) or {}

    store = Storage(current_app.config["SQLITE_PATH"])
    # 存 raw + normalized
    store.insert_form_raw(data)
    store.insert_form_answers_from_make_payload(data)

    return jsonify({"status": "ok"}), 200
