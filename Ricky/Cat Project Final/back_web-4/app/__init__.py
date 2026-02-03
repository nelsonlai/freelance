from flask import Flask
from flask_cors import CORS
from .config import Config
from .utils.logger import setup_logging
from werkzeug.security import generate_password_hash

def create_app():
    app = Flask(__name__)
    app.config.from_object(Config())

    # session secret for /admin
    app.secret_key = app.config.get("SECRET_KEY", "aadf@$9oaf")

    setup_logging(app)

    origins = [o.strip() for o in app.config["CORS_ORIGINS"].split(",") if o.strip()]
    CORS(app, resources={r"/*": {"origins": origins}}, supports_credentials=False)

    from .routes.health import bp as health_bp
    from .routes.auth import bp as auth_bp
    from .routes.make_webhook import bp as make_bp
    from .routes.reports import bp as reports_bp
    from .routes.api_auth import bp as api_auth_bp
    from .routes.cat_register import bp as cat_register_bp
    from .routes.match import bp as match_bp
    from .routes.uploads import bp as uploads_bp
    from .admin.routes import bp as admin_bp
    from .routes.admin_ingest import bp as admin_ingest_bp
    from .routes.admin_stats import bp as admin_stats_bp


    app.register_blueprint(health_bp)
    app.register_blueprint(auth_bp)
    app.register_blueprint(make_bp)
    app.register_blueprint(reports_bp)
    app.register_blueprint(api_auth_bp)
    app.register_blueprint(cat_register_bp)
    app.register_blueprint(match_bp)
    app.register_blueprint(uploads_bp)
    app.register_blueprint(admin_bp)
    app.register_blueprint(admin_ingest_bp)
    app.register_blueprint(admin_stats_bp)


    # Optional: bootstrap a first super_admin via env (one-time)
    try:
        from .services.storage import Storage
        admin_email = (app.config.get("ADMIN_EMAIL") or "").strip().lower()
        admin_password = app.config.get("ADMIN_PASSWORD") or ""
        if admin_email and admin_password:
            store = Storage(app.config["SQLITE_PATH"])
            if not store.get_user_by_email(admin_email):
                store.create_user_with_role(
                    email=admin_email,
                    password_hash=generate_password_hash(admin_password, method='pbkdf2:sha256'),
                    role="super_admin",
                )
                app.logger.warning("Bootstrapped super_admin: %s", admin_email)
    except Exception:
        app.logger.exception("Failed to bootstrap admin")

    app.logger.warning(
    "[DEBUG] POE_API_KEY loaded: %s",
    "YES" if app.config.get("POE_API_KEY") else "NO"
)
    app.logger.warning(
    "[DEBUG] POE_BASE_URL = %s",
        app.config.get("POE_BASE_URL")
)
    app.logger.warning(
    "[DEBUG] POE_ENDPOINT = %s",
        app.config.get("POE_ENDPOINT")
)

    print(app.url_map)
    return app
