from flask import Blueprint

botchat_bp = Blueprint("botchat", __name__, template_folder="templates")

from app.blueprints.botchat import routes
