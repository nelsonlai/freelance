"""
Minimal Flask webhook server for Stripe events.
Run: flask --app flask_webhook_server run --port 4242
Test: stripe listen --forward-to localhost:4242/webhook
"""
import stripe
import os
import sys

sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
try:
    from dotenv import load_dotenv
    load_dotenv()
except ImportError:
    pass

stripe.api_key = os.environ.get("STRIPE_SECRET_KEY", "")
WEBHOOK_SECRET = os.environ.get("STRIPE_WEBHOOK_SECRET", "")

try:
    from flask import Flask, request, jsonify
except ImportError:
    print("Install Flask: pip install flask")
    sys.exit(1)

app = Flask(__name__)


@app.route("/webhook", methods=["POST"])
def webhook():
    payload = request.get_data()
    sig_header = request.headers.get("Stripe-Signature")
    if not WEBHOOK_SECRET:
        return jsonify({"error": "STRIPE_WEBHOOK_SECRET not set"}), 500
    try:
        event = stripe.Webhook.construct_event(payload, sig_header, WEBHOOK_SECRET)
    except ValueError as e:
        return jsonify({"error": f"Invalid payload: {e}"}), 400
    except stripe.error.SignatureVerificationError as e:
        return jsonify({"error": f"Invalid signature: {e}"}), 400

    obj = event.data.object
    if event.type == "payment_intent.succeeded":
        print(f"[webhook] PaymentIntent succeeded: {obj.id}")
    elif event.type == "payment_intent.payment_failed":
        print(f"[webhook] PaymentIntent failed: {obj.id}")
    elif event.type == "checkout.session.completed":
        print(f"[webhook] Checkout completed: {obj.id} customer={obj.get('customer')}")
    elif event.type == "customer.subscription.created":
        print(f"[webhook] Subscription created: {obj.id}")
    elif event.type == "customer.subscription.deleted":
        print(f"[webhook] Subscription canceled: {obj.id}")
    elif event.type == "invoice.paid":
        print(f"[webhook] Invoice paid: {obj.id}")
    elif event.type == "invoice.payment_failed":
        print(f"[webhook] Invoice payment failed: {obj.id}")
    else:
        print(f"[webhook] Unhandled: {event.type}")

    return jsonify({"received": True}), 200


@app.route("/")
def index():
    return "Stripe webhook server. POST /webhook with Stripe-Signature."


if __name__ == "__main__":
    app.run(port=4242)
