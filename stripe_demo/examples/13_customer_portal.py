"""
Stripe Customer Portal – let customers manage subscription, payment methods, invoices.
Create a portal session and redirect the customer to session.url.
Docs: https://docs.stripe.com/api/customer_portal/sessions
"""
import stripe
import sys
import os

sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
from config import STRIPE_SECRET_KEY, DEFAULT_SUCCESS_URL, ensure_stripe_key

RETURN_URL = DEFAULT_SUCCESS_URL

stripe.api_key = STRIPE_SECRET_KEY


def create_portal_session(customer_id: str, return_url: str = None):
    """
    Create a Customer Portal session. Redirect the customer to session.url.
    In the portal they can: update payment method, cancel subscription, view invoices.
    """
    ensure_stripe_key()
    return_url = return_url or RETURN_URL
    session = stripe.billing_portal.Session.create(
        customer=customer_id,
        return_url=return_url,
    )
    print(f"Portal session: {session.url}")
    return session


def create_portal_configuration():
    """
    Create or update portal configuration (what features are shown).
    Default configuration is used if you don't create one.
    """
    ensure_stripe_key()
    # Example: allow subscription cancellation and payment method update
    config = stripe.billing_portal.Configuration.create(
        business_profile={
            "headline": "Manage your subscription",
        },
        features={
            "customer_update": {"enabled": True},
            "invoice_history": {"enabled": True},
            "payment_method_update": {"enabled": True},
            "subscription_cancel": {"enabled": True},
        },
    )
    print(f"Portal configuration: {config.id}")
    return config


def list_portal_configurations(limit: int = 10):
    """List billing portal configurations."""
    ensure_stripe_key()
    return stripe.billing_portal.Configuration.list(limit=limit)


if __name__ == "__main__":
    ensure_stripe_key()
    print("=== Create portal session for customer ===")
    # session = create_portal_session("cus_xxx")
    # Redirect user to: session.url
