import os
from dotenv import load_dotenv

class Config:
    def __init__(self):
        load_dotenv()

        # Flask session / admin backend
        # NOTE: set SECRET_KEY in .env for production.
        self.SECRET_KEY = os.getenv("SECRET_KEY", "dev-secret-change-me")

        self.PORT = int(os.getenv("PORT", "5000"))
        self.CORS_ORIGINS = os.getenv("CORS_ORIGINS", "http://localhost:3000,http://127.0.0.1:3000")

        self.JWT_SECRET = os.getenv("JWT_SECRET", "")
        self.MAKE_WEBHOOK_SECRET = os.getenv("MAKE_WEBHOOK_SECRET", "")

        # optional one-time bootstrap admin
        self.ADMIN_EMAIL = os.getenv("ADMIN_EMAIL", "")
        self.ADMIN_PASSWORD = os.getenv("ADMIN_PASSWORD", "")

        self.SQLITE_PATH = os.getenv("SQLITE_PATH", "./data.db")

        # File uploads (cat photos)
        base_dir = os.path.abspath(os.getcwd())
        self.UPLOAD_DIR = os.path.abspath(
            os.getenv("UPLOAD_DIR", os.path.join(base_dir, "uploads"))
        )


        self.POE_API_KEY = os.getenv("POE_API_KEY", "")
        self.POE_BASE_URL = os.getenv("POE_BASE_URL", "https://api.poe.com")
        self.POE_ENDPOINT = os.getenv("POE_ENDPOINT", "/v1/completions")
        self.POE_MODEL = os.getenv("POE_MODEL", "claude-3-opus")
        self.POE_TIMEOUT = int(os.getenv("POE_TIMEOUT", "45"))
