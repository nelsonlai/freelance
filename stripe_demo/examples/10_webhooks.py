"""
Stripe Webhooks – receive and verify events from Stripe.
Use STRIPE_WEBHOOK_SECRET (from Stripe CLI or Dashboard) to verify signatures.
Docs: https://docs.stripe.com/webhooks
"""
import stripe
import sys
import os

sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
from config import STRIPE_SECRET_KEY, STRIPE_WEBHOOK_SECRET, ensure_stripe_key

stripe.api_key = STRIPE_SECRET_KEY


def verify_and_parse_event(payload: bytes, sig_header: str, webhook_secret: str = None):
    """
    Verify webhook signature and parse event. Use in your HTTP handler.
    payload: raw request body (bytes)
    sig_header: request.headers.get('Stripe-Signature')
    webhook_secret: endpoint signing secret (whsec_...). Default: STRIPE_WEBHOOK_SECRET.
    """
    secret = webhook_secret or STRIPE_WEBHOOK_SECRET
    if not secret:
        raise ValueError("STRIPE_WEBHOOK_SECRET or webhook_secret required for verification")
    try:
        event = stripe.Webhook.construct_event(payload, sig_header, secret)
    except ValueError as e:
        raise ValueError(f"Invalid payload: {e}")
    except stripe.error.SignatureVerificationError as e:
        raise stripe.error.SignatureVerificationError(f"Invalid signature: {e}")
    return event


def handle_event(event):
    """
    Example handler: branch on event.type and process event.data.object.
    Return quickly (e.g. 200) then do heavy work in background (queue, celery, etc.).
    """
    obj = event.data.object
    if event.type == "payment_intent.succeeded":
        print(f"PaymentIntent succeeded: {obj.id}")
        # e.g. fulfill order, update DB
    elif event.type == "payment_intent.payment_failed":
        print(f"PaymentIntent failed: {obj.id}")
    elif event.type == "checkout.session.completed":
        print(f"Checkout completed: {obj.id} customer={obj.customer}")
        # session.payment_status, session.subscription, session.mode
    elif event.type == "customer.subscription.created":
        print(f"Subscription created: {obj.id}")
    elif event.type == "customer.subscription.updated":
        print(f"Subscription updated: {obj.id}")
    elif event.type == "customer.subscription.deleted":
        print(f"Subscription canceled: {obj.id}")
    elif event.type == "invoice.paid":
        print(f"Invoice paid: {obj.id}")
    elif event.type == "invoice.payment_failed":
        print(f"Invoice payment failed: {obj.id}")
    else:
        print(f"Unhandled event type: {event.type}")


# --- Flask example (uncomment and use with: flask run) ---
# from flask import Flask, request, jsonify
# app = Flask(__name__)
#
# @app.route("/webhook", methods=["POST"])
# def webhook():
#     payload = request.get_data()
#     sig_header = request.headers.get("Stripe-Signature")
#     try:
#         event = verify_and_parse_event(payload, sig_header)
#     except (ValueError, stripe.error.SignatureVerificationError) as e:
#         return jsonify({"error": str(e)}), 400
#     handle_event(event)
#     return jsonify({"received": True}), 200


# --- Minimal HTTP server example (for local testing with stripe listen) ---
def run_simple_webhook_server(port: int = 4242):
    """Run a minimal POST /webhook server. Use with: stripe listen --forward-to localhost:4242/webhook"""
    try:
        from http.server import HTTPServer, BaseHTTPRequestHandler
    except ImportError:
        print("Use Flask or another framework for a real webhook server.")
        return

    class Handler(BaseHTTPRequestHandler):
        def do_POST(self):
            if self.path != "/webhook":
                self.send_response(404)
                self.end_headers()
                return
            length = int(self.headers.get("Content-Length", 0))
            payload = self.rfile.read(length)
            sig = self.headers.get("Stripe-Signature", "")
            try:
                event = verify_and_parse_event(payload, sig)
                handle_event(event)
            except Exception as e:
                self.send_response(400)
                self.send_header("Content-Type", "application/json")
                self.end_headers()
                self.wfile.write(b'{"error":"' + str(e).encode() + b'"}')
                return
            self.send_response(200)
            self.end_headers()

        def log_message(self, format, *args):
            print(f"[webhook] {format % args}")

    server = HTTPServer(("", port), Handler)
    print(f"Serving /webhook on port {port}. Run: stripe listen --forward-to localhost:{port}/webhook")
    server.serve_forever()


if __name__ == "__main__":
    print("Webhook verification and handling helpers.")
    print("To test locally: stripe listen --forward-to localhost:4242/webhook")
    print("Then run a Flask/app server that calls verify_and_parse_event + handle_event in POST /webhook.")
