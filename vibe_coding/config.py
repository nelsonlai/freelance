"""
Application configuration. Load from environment for production.
"""
import os
from dotenv import load_dotenv

load_dotenv()


class Config:
    SECRET_KEY = os.environ.get("SECRET_KEY") or "dev-secret-change-in-production"
    _db_url = os.environ.get("DATABASE_URL", "").strip()
    SQLALCHEMY_DATABASE_URI = (
        _db_url if _db_url.startswith("mysql+") or _db_url.startswith("sqlite") else "mysql+pymysql://root:password@localhost:3306/vibe_coding"
    )
    SQLALCHEMY_TRACK_MODIFICATIONS = False
    SQLALCHEMY_ENGINE_OPTIONS = {"pool_pre_ping": True}
