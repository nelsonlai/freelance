# Module 3: Python Flask

Flask is a lightweight **micro-framework** for Python. You can build REST APIs, server-rendered web apps with templates (Jinja2), or both.

---

## 1. Why Flask?

- **Simple**: Minimal boilerplate; you add what you need.
- **Flexible**: APIs only, or full web app with HTML/CSS/JS.
- **Jinja2**: Built-in templating for server-rendered pages.
- **Ecosystem**: Many extensions (Flask-SQLAlchemy, Flask-JWT, etc.).

---

## 2. Setup

```bash
python -m venv venv
source venv/bin/activate   # Windows: venv\Scripts\activate
pip install flask
```

---

## 3. Minimal App

```python
from flask import Flask

app = Flask(__name__)

@app.route("/")
def index():
    return {"message": "Hello World"}

@app.route("/health")
def health():
    return {"status": "ok"}

if __name__ == "__main__":
    app.run(debug=True)
```

Run: `python app.py` → http://127.0.0.1:5000  

---

## 4. Routing

```python
from flask import Flask, request

app = Flask(__name__)

# Path parameter
@app.route("/users/<int:user_id>")
def get_user(user_id):
    return {"user_id": user_id}

# Query parameters
@app.route("/items")
def list_items():
    skip = request.args.get("skip", 0, type=int)
    limit = request.args.get("limit", 10, type=int)
    return {"skip": skip, "limit": limit}

# Multiple methods
@app.route("/users", methods=["GET", "POST"])
def users():
    if request.method == "POST":
        data = request.get_json()
        return create_user(data), 201
    return list_users()
```

- Use `<int:user_id>` for typed path params.
- Use `request.args` for query, `request.get_json()` for JSON body.

---

## 5. Request Body (JSON API)

```python
from flask import Flask, request, jsonify

app = Flask(__name__)

@app.post("/users")
def create_user():
    data = request.get_json(force=True, silent=False)
    if not data or "email" not in data:
        return jsonify({"error": "email required"}), 400
    user = save_user(data)
    return jsonify(user), 201
```

- Validate input manually or use a library (e.g. **marshmallow**, **pydantic**).
- Use `jsonify(...)` for JSON responses; set status with second return value.

---

## 6. REST CRUD Pattern

```python
# GET    /users      -> list
# GET    /users/<id> -> get one
# POST   /users      -> create
# PUT    /users/<id> -> update
# DELETE /users/<id> -> delete

@app.get("/users")
def list_users():
    return jsonify({"data": get_all_users()})

@app.get("/users/<int:user_id>")
def get_user(user_id):
    user = find_user(user_id)
    if not user:
        return jsonify({"error": "Not found"}), 404
    return jsonify(user)

@app.post("/users")
def create_user():
    data = request.get_json()
    user = save_user(data)
    return jsonify(user), 201

@app.put("/users/<int:user_id>")
def update_user(user_id):
    data = request.get_json()
    user = update_user_by_id(user_id, data)
    if not user:
        return jsonify({"error": "Not found"}), 404
    return jsonify(user)

@app.delete("/users/<int:user_id>")
def delete_user(user_id):
    if not delete_user_by_id(user_id):
        return jsonify({"error": "Not found"}), 404
    return "", 204
```

---

## 7. Server-Rendered Pages (Jinja2)

```python
from flask import Flask, render_template, request, redirect, url_for, flash

app = Flask(__name__)
app.secret_key = "your-secret-key"

@app.route("/")
def index():
    messages = get_messages()
    return render_template("index.html", messages=messages)

@app.route("/post", methods=["POST"])
def post_message():
    name = request.form.get("name")
    content = request.form.get("content")
    if not name or not content:
        flash("Name and content required", "error")
    else:
        add_message(name, content)
        flash("Message added", "success")
    return redirect(url_for("index"))
```

- **Templates** go in `templates/` (e.g. `index.html`).
- Use `{{ variable }}`, `{% if %}`, `{% for %}` in Jinja2.
- Use `request.form` for form data, `redirect()` and `url_for()` for navigation, `flash()` for one-time messages.

---

## 8. Blueprints (Modular Apps)

```python
# users.py
from flask import Blueprint, jsonify

bp = Blueprint("users", __name__, url_prefix="/users")

@bp.get("/")
def list_users():
    return jsonify({"data": []})

# app.py
from flask import Flask
from users import bp as users_bp

app = Flask(__name__)
app.register_blueprint(users_bp)
```

- Use **Blueprints** to split routes by feature (users, items, etc.).

---

## 9. Error Handlers

```python
@app.errorhandler(404)
def not_found(e):
    return jsonify({"error": "Not found"}), 404

@app.errorhandler(500)
def server_error(e):
    return jsonify({"error": "Internal server error"}), 500
```

---

## 10. Configuration

```python
app.config["SECRET_KEY"] = "dev-secret"
app.config["DEBUG"] = True

# Or from env / config file
import os
app.config["SECRET_KEY"] = os.environ.get("SECRET_KEY", "dev")
```

---

## 11. Middleware-Like Behavior

- **Before/after request**: Use `@app.before_request` and `@app.after_request` for logging, DB session, etc.
- **CORS**: Use extension **Flask-CORS** for cross-origin API access.

---

## 12. Flask vs FastAPI (APIs)

| Aspect       | Flask        | FastAPI           |
|-------------|--------------|-------------------|
| Async       | Optional     | Native async      |
| Validation  | Manual/extra | Pydantic built-in |
| OpenAPI     | Via extension| Built-in          |
| Learning    | Very easy    | Easy + types      |

- Use **Flask** when you want minimal setup, server-rendered pages, or a small API.
- Use **FastAPI** when you want automatic validation, OpenAPI docs, and async by default.

---

## Lesson Plan

1. Hello World and routing.
2. Path and query parameters, request body.
3. REST CRUD with JSON.
4. Jinja2 templates and forms (if building web UI).
5. Blueprints and project structure.
6. Error handling and configuration.

---

## Example in This Repo

- **Flask curriculum + guestbook app**: `../python_backend/curriculum/flask/`  
  - Run: `cd ../python_backend/curriculum/flask && pip install -r requirements.txt && python app.py`  
  - Open: http://127.0.0.1:5000  

---

## Next

- [01_restful_api](../01_restful_api/) — REST  
- [02_python_fastapi](../02_python_fastapi/) — FastAPI  
- [06_sql](../06_sql/) / [07_nosql](../07_nosql/) — Databases  
