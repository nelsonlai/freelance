from flask import Flask, render_template, request, redirect, url_for, flash

app = Flask(__name__)
app.secret_key = "super_secret_key_for_learning"

# In-memory "database" for the guestbook
messages = [
    {"name": "Alice", "content": "Welcome to the Flask lesson!"},
    {"name": "Bob", "content": "Jinja2 is really powerful."}
]

@app.route("/")
def index():
    """Home page showing all guestbook entries"""
    return render_template("index.html", messages=messages)

@app.route("/post", methods=["POST"])
def post_message():
    """Handle form submission to add a new message"""
    name = request.form.get("name")
    content = request.form.get("content")
    
    if not name or not content:
        flash("Both name and content are required!", "error")
    else:
        messages.append({"name": name, "content": content})
        flash("Message added successfully!", "success")
        
    return redirect(url_for("index"))

if __name__ == "__main__":
    app.run(debug=True)
