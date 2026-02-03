"""
Stripe Payment Intents API – one-time payments with card/other methods.
Create a PaymentIntent on the server, then confirm on the client with Stripe.js using client_secret.
Docs: https://docs.stripe.com/api/payment_intents
"""
import stripe
import sys
import os

sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
from config import STRIPE_SECRET_KEY, DEFAULT_CURRENCY, ensure_stripe_key

stripe.api_key = STRIPE_SECRET_KEY


def create_payment_intent(
    amount_cents: int,
    currency: str = None,
    customer_id: str = None,
    description: str = None,
    metadata: dict = None,
    setup_future_usage: str = None,
    receipt_email: str = None,
):
    """
    Create a PaymentIntent. Return client_secret to the frontend for Stripe.js confirm.
    amount_cents: e.g. 2000 = $20.00 (smallest currency unit).
    setup_future_usage: 'off_session'|'on_session' to save payment method for later.
    """
    ensure_stripe_key()
    currency = currency or DEFAULT_CURRENCY
    params = {
        "amount": amount_cents,
        "currency": currency,
        "automatic_payment_methods": {"enabled": True},
    }
    if customer_id:
        params["customer"] = customer_id
    if description:
        params["description"] = description
    if metadata:
        params["metadata"] = metadata
    if setup_future_usage:
        params["setup_future_usage"] = setup_future_usage
    if receipt_email:
        params["receipt_email"] = receipt_email
    pi = stripe.PaymentIntent.create(**params)
    print(f"Created PaymentIntent: {pi.id} | client_secret: {pi.client_secret[:20]}...")
    return pi


def retrieve_payment_intent(payment_intent_id: str):
    """Retrieve a PaymentIntent (e.g. to check status after confirmation)."""
    ensure_stripe_key()
    return stripe.PaymentIntent.retrieve(payment_intent_id)


def update_payment_intent(payment_intent_id: str, **kwargs):
    """Update amount, metadata, etc. before confirming. Cannot change after confirm."""
    ensure_stripe_key()
    return stripe.PaymentIntent.modify(payment_intent_id, **kwargs)


def confirm_payment_intent(payment_intent_id: str, payment_method: str = None):
    """Confirm server-side (e.g. when you have payment_method from client)."""
    ensure_stripe_key()
    params = {}
    if payment_method:
        params["payment_method"] = payment_method
    return stripe.PaymentIntent.confirm(payment_intent_id, **params)


def cancel_payment_intent(payment_intent_id: str, cancellation_reason: str = None):
    """Cancel a PaymentIntent that hasn't been confirmed. reason: 'duplicate'|'fraudulent'|'requested_by_customer'."""
    ensure_stripe_key()
    params = {}
    if cancellation_reason:
        params["cancellation_reason"] = cancellation_reason
    return stripe.PaymentIntent.cancel(payment_intent_id, **params)


def capture_payment_intent(payment_intent_id: str, amount_to_capture: int = None):
    """Capture a manual_capture PaymentIntent. Omit amount_to_capture to capture full amount."""
    ensure_stripe_key()
    params = {}
    if amount_to_capture is not None:
        params["amount_to_capture"] = amount_to_capture
    return stripe.PaymentIntent.capture(payment_intent_id, **params)


def list_payment_intents(limit: int = 10, customer: str = None):
    """List PaymentIntents, optionally filtered by customer."""
    ensure_stripe_key()
    params = {"limit": limit}
    if customer:
        params["customer"] = customer
    return stripe.PaymentIntent.list(**params)


if __name__ == "__main__":
    ensure_stripe_key()
    print("=== Create PaymentIntent (for $25.00) ===")
    pi = create_payment_intent(
        2500,
        description="Demo order",
        metadata={"order_id": "ord_demo_001"},
    )
    print("=== Retrieve ===")
    obj = retrieve_payment_intent(pi.id)
    print(f"  status={obj.status} amount={obj.amount} {obj.currency}")
    print("=== Cancel (comment out to keep for client-side confirm) ===")
    # cancel_payment_intent(pi.id)
