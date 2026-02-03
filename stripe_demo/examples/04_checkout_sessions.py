"""
Stripe Checkout Sessions – hosted payment/subscription pages.
Redirect customers to Stripe-hosted Checkout; no custom payment form needed.
Docs: https://docs.stripe.com/api/checkout/sessions
"""
import stripe
import sys
import os

sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
from config import (
    STRIPE_SECRET_KEY,
    DEFAULT_SUCCESS_URL,
    DEFAULT_CANCEL_URL,
    ensure_stripe_key,
)

stripe.api_key = STRIPE_SECRET_KEY


def create_checkout_session_payment(
    line_items: list,
    success_url: str = None,
    cancel_url: str = None,
    customer_email: str = None,
    customer_id: str = None,
    client_reference_id: str = None,
    metadata: dict = None,
    allow_promotion_codes: bool = False,
    mode: str = "payment",
):
    """
    Create a Checkout Session for one-time payment.
    line_items: [{"price": "price_xxx", "quantity": 1}, ...] or
                [{"price_data": {"currency":"usd","product_data":{"name":"..."},"unit_amount":1000}, "quantity": 1}]
    Redirect user to session.url to complete payment.
    """
    ensure_stripe_key()
    success_url = success_url or DEFAULT_SUCCESS_URL
    cancel_url = cancel_url or DEFAULT_CANCEL_URL
    params = {
        "mode": mode,
        "line_items": line_items,
        "success_url": success_url,
        "cancel_url": cancel_url,
    }
    if customer_id:
        params["customer"] = customer_id
    elif customer_email:
        params["customer_email"] = customer_email
    if client_reference_id:
        params["client_reference_id"] = client_reference_id
    if metadata:
        params["metadata"] = metadata
    if allow_promotion_codes:
        params["allow_promotion_codes"] = True
    session = stripe.checkout.Session.create(**params)
    print(f"Checkout Session: {session.id} | url: {session.url[:50]}...")
    return session


def create_checkout_session_subscription(
    line_items: list,
    success_url: str = None,
    cancel_url: str = None,
    customer_email: str = None,
    customer_id: str = None,
    client_reference_id: str = None,
    metadata: dict = None,
    subscription_data: dict = None,
    allow_promotion_codes: bool = False,
):
    """
    Create a Checkout Session for subscription.
    line_items must use recurring Price IDs, e.g. [{"price": "price_xxx", "quantity": 1}].
    subscription_data: e.g. {"trial_period_days": 14, "metadata": {...}}
    """
    ensure_stripe_key()
    success_url = success_url or DEFAULT_SUCCESS_URL
    cancel_url = cancel_url or DEFAULT_CANCEL_URL
    params = {
        "mode": "subscription",
        "line_items": line_items,
        "success_url": success_url,
        "cancel_url": cancel_url,
    }
    if customer_id:
        params["customer"] = customer_id
    elif customer_email:
        params["customer_email"] = customer_email
    if client_reference_id:
        params["client_reference_id"] = client_reference_id
    if metadata:
        params["metadata"] = metadata
    if subscription_data:
        params["subscription_data"] = subscription_data
    if allow_promotion_codes:
        params["allow_promotion_codes"] = True
    session = stripe.checkout.Session.create(**params)
    print(f"Subscription Checkout Session: {session.id}")
    return session


def create_checkout_session_setup(success_url: str = None, cancel_url: str = None, customer_id: str = None):
    """Create a Checkout Session in 'setup' mode to save a payment method without charging."""
    ensure_stripe_key()
    success_url = success_url or DEFAULT_SUCCESS_URL
    cancel_url = cancel_url or DEFAULT_CANCEL_URL
    params = {
        "mode": "setup",
        "success_url": success_url,
        "cancel_url": cancel_url,
    }
    if customer_id:
        params["customer"] = customer_id
    session = stripe.checkout.Session.create(**params)
    print(f"Setup Checkout Session: {session.id}")
    return session


def retrieve_checkout_session(session_id: str):
    """Retrieve a Checkout Session (e.g. after redirect to success_url)."""
    ensure_stripe_key()
    return stripe.checkout.Session.retrieve(session_id)


def list_line_items(session_id: str):
    """List line items for a Checkout Session."""
    ensure_stripe_key()
    return stripe.checkout.Session.list_line_items(session_id)


def expire_session(session_id: str):
    """Expire an open Checkout Session so it can no longer be used."""
    ensure_stripe_key()
    return stripe.checkout.Session.expire(session_id)


if __name__ == "__main__":
    ensure_stripe_key()
    print("=== Create Payment Checkout (use price_xxx or price_data) ===")
    session = create_checkout_session_payment(
        line_items=[
            {
                "price_data": {
                    "currency": "usd",
                    "product_data": {"name": "Demo Product", "description": "One-time purchase"},
                    "unit_amount": 1500,
                },
                "quantity": 2,
            }
        ],
        customer_email="checkout-demo@example.com",
        allow_promotion_codes=True,
    )
    print("  Send user to:", session.url)
    print("=== Create Subscription Checkout (pass a recurring price_id) ===")
    # sub_session = create_checkout_session_subscription(
    #     line_items=[{"price": "price_xxx", "quantity": 1}],
    #     customer_email="sub-demo@example.com",
    # )
