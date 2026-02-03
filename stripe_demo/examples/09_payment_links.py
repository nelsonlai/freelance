"""
Stripe Payment Links – shareable links for one-time or subscription payments.
No backend required for simple flows; create a link and share the URL.
Docs: https://docs.stripe.com/api/payment-link
"""
import stripe
import sys
import os

sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
from config import STRIPE_SECRET_KEY, DEFAULT_SUCCESS_URL, DEFAULT_CANCEL_URL, ensure_stripe_key

stripe.api_key = STRIPE_SECRET_KEY


def create_payment_link_one_time(
    line_items: list,
    success_url: str = None,
    cancel_url: str = None,
    allow_promotion_codes: bool = False,
    metadata: dict = None,
):
    """
    Create a Payment Link for one-time payment.
    line_items: [{"price": "price_xxx", "quantity": 1}, ...] or
                [{"price_data": {"currency":"usd","product_data":{"name":"..."},"unit_amount":1000}, "quantity": 1}]
    """
    ensure_stripe_key()
    success_url = success_url or DEFAULT_SUCCESS_URL
    cancel_url = cancel_url or DEFAULT_CANCEL_URL
    params = {
        "line_items": line_items,
        "after_completion": {"type": "redirect", "redirect": {"url": success_url}},
        "metadata": metadata or {},
    }
    if allow_promotion_codes:
        params["allow_promotion_codes"] = True
    link = stripe.PaymentLink.create(**params)
    print(f"Payment Link: {link.url}")
    return link


def create_payment_link_subscription(
    line_items: list,
    success_url: str = None,
    cancel_url: str = None,
    allow_promotion_codes: bool = False,
    metadata: dict = None,
):
    """Create a Payment Link for subscription (line_items must use recurring prices)."""
    ensure_stripe_key()
    success_url = success_url or DEFAULT_SUCCESS_URL
    cancel_url = cancel_url or DEFAULT_CANCEL_URL
    params = {
        "line_items": line_items,
        "after_completion": {"type": "redirect", "redirect": {"url": success_url}},
        "metadata": metadata or {},
    }
    if allow_promotion_codes:
        params["allow_promotion_codes"] = True
    link = stripe.PaymentLink.create(**params)
    print(f"Subscription Payment Link: {link.url}")
    return link


def retrieve_payment_link(link_id: str):
    """Retrieve a Payment Link."""
    ensure_stripe_key()
    return stripe.PaymentLink.retrieve(link_id)


def list_payment_links(active: bool = True, limit: int = 10):
    """List Payment Links."""
    ensure_stripe_key()
    return stripe.PaymentLink.list(active=active, limit=limit)


if __name__ == "__main__":
    ensure_stripe_key()
    print("=== Create one-time Payment Link ===")
    link = create_payment_link_one_time(
        line_items=[
            {
                "price_data": {
                    "currency": "usd",
                    "product_data": {"name": "Demo product via link"},
                    "unit_amount": 2000,
                },
                "quantity": 1,
            }
        ],
        allow_promotion_codes=True,
    )
    print("  Share URL:", link.url)
