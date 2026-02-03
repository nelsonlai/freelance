from dotenv import load_dotenv
import os

load_dotenv(dotenv_path=os.path.join(os.path.dirname(__file__), ".env"))

from app import create_app

app = create_app()

if __name__ == "__main__":
    print(app.url_map)

    app.run(host="0.0.0.0", port=5050, debug=True)
