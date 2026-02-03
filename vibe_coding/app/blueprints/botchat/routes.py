from flask import render_template, request, jsonify
from flask_login import login_required, current_user
from app.blueprints.botchat import botchat_bp
from app.extensions import db
from app.models import ChatMessage


def get_bot_reply(user_message: str) -> str:
    """Simple rule-based bot. Replace with API/LLM later."""
    msg = user_message.lower().strip()
    if not msg:
        return "Say something and I'll reply!"
    if "hello" in msg or "hi" in msg:
        return "Hello! How can I help you today?"
    if "bye" in msg:
        return "Goodbye! Have a great day."
    if "help" in msg:
        return "I'm a simple bot. Try saying hello, or ask about the blog."
    if "blog" in msg:
        return "You can read and write posts in the Blog section."
    return f"You said: {user_message}. I'm a simple bot—customize my replies in app/blueprints/botchat/routes.py!"


@botchat_bp.route("/")
@login_required
def index():
    messages = (
        ChatMessage.query.filter_by(user_id=current_user.id)
        .order_by(ChatMessage.created_at.asc())
        .all()
    )
    return render_template("botchat/index.html", messages=messages)


@botchat_bp.route("/send", methods=["POST"])
@login_required
def send():
    data = request.get_json() or {}
    content = (data.get("message") or "").strip()
    if not content:
        return jsonify({"error": "Message is required"}), 400

    user_msg = ChatMessage(
        user_id=current_user.id, role="user", content=content
    )
    db.session.add(user_msg)
    db.session.commit()

    reply = get_bot_reply(content)
    bot_msg = ChatMessage(
        user_id=current_user.id, role="bot", content=reply
    )
    db.session.add(bot_msg)
    db.session.commit()

    return jsonify({
        "user_message": {"id": user_msg.id, "content": content, "role": "user"},
        "bot_message": {"id": bot_msg.id, "content": reply, "role": "bot"},
    })
