import os
from flask import Blueprint, current_app, send_from_directory, abort


bp = Blueprint("uploads", __name__, url_prefix="/uploads")


@bp.get("/<path:filename>")
def get_upload(filename: str):
    upload_dir = current_app.config.get("UPLOAD_DIR", "./uploads")
    # basic path traversal guard
    if ".." in filename or filename.startswith("/"):
        abort(400)
    if not os.path.exists(os.path.join(upload_dir, filename)):
        abort(404)
    return send_from_directory(upload_dir, filename)
