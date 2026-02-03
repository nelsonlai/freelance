"""
Run the Flask app. For development only.
Production: use gunicorn or uwsgi with app:create_app().
"""
import os

from app import create_app

app = create_app(os.environ.get("FLASK_CONFIG") or "config.Config")

if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000, debug=True)
