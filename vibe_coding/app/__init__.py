"""
Flask application factory.
"""
from flask import Flask, redirect, url_for
from app.extensions import db, login_manager


def create_app(config_class="config.Config"):
    app = Flask(__name__)
    app.config.from_object(config_class)

    db.init_app(app)
    login_manager.init_app(app)
    login_manager.login_view = "auth.login"
    login_manager.login_message = "Please log in to access this page."

    from app.models import User

    @login_manager.user_loader
    def load_user(user_id):
        return db.session.get(User, int(user_id))

    from app.blueprints.auth import auth_bp
    from app.blueprints.blog import blog_bp
    from app.blueprints.botchat import botchat_bp

    app.register_blueprint(auth_bp, url_prefix="/auth")
    app.register_blueprint(blog_bp, url_prefix="/blog")
    app.register_blueprint(botchat_bp, url_prefix="/botchat")

    @app.route("/")
    def index():
        return redirect(url_for("blog.index"))

    with app.app_context():
        from app import models  # noqa: F401 – register models with SQLAlchemy
        db.create_all()

    return app
