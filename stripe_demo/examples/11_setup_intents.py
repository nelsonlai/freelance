"""
Stripe Setup Intents – collect and save payment methods without charging.
Use when you want to save a card for later (e.g. for subscriptions or one-click pay).
Docs: https://docs.stripe.com/api/setup_intents
"""
import stripe
import sys
import os

sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
from config import STRIPE_SECRET_KEY, ensure_stripe_key

stripe.api_key = STRIPE_SECRET_KEY


def create_setup_intent(customer_id: str = None, payment_method_types: list = None, metadata: dict = None):
    """
    Create a SetupIntent. Frontend uses client_secret with Stripe.js to collect payment method.
    After confirm, payment_method is attached to customer (if customer_id provided).
    """
    ensure_stripe_key()
    params = {}
    if customer_id:
        params["customer"] = customer_id
    if payment_method_types:
        params["payment_method_types"] = payment_method_types
    if metadata:
        params["metadata"] = metadata
    si = stripe.SetupIntent.create(**params)
    print(f"SetupIntent: {si.id} client_secret={si.client_secret[:30]}...")
    return si


def retrieve_setup_intent(setup_intent_id: str):
    """Retrieve a SetupIntent (e.g. after confirmation)."""
    ensure_stripe_key()
    return stripe.SetupIntent.retrieve(setup_intent_id)


def cancel_setup_intent(setup_intent_id: str):
    """Cancel a SetupIntent that hasn't been confirmed."""
    ensure_stripe_key()
    return stripe.SetupIntent.cancel(setup_intent_id)


def list_setup_intents(customer_id: str = None, limit: int = 10):
    """List SetupIntents, optionally by customer."""
    ensure_stripe_key()
    params = {"limit": limit}
    if customer_id:
        params["customer"] = customer_id
    return stripe.SetupIntent.list(**params)


if __name__ == "__main__":
    ensure_stripe_key()
    print("=== Create SetupIntent for customer (save card) ===")
    # si = create_setup_intent(customer_id="cus_xxx")
    # Frontend: stripe.confirmCardSetup(si.client_secret, { payment_method: { card: ... } })
    # Then: payment_method is on the SetupIntent and can be attached to customer
