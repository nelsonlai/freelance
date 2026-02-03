"""
Stripe Payment Methods – attach, detach, list cards and other methods.
Docs: https://docs.stripe.com/api/payment_methods
"""
import stripe
import sys
import os

sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
from config import STRIPE_SECRET_KEY, ensure_stripe_key

stripe.api_key = STRIPE_SECRET_KEY


def list_payment_methods(customer_id: str, type: str = "card", limit: int = 10):
    """List payment methods attached to a customer. type: 'card'|'us_bank_account'|etc."""
    ensure_stripe_key()
    methods = stripe.PaymentMethod.list(customer=customer_id, type=type, limit=limit)
    for pm in methods.data:
        print(f"  {pm.id} | {pm.type} | {getattr(pm.card, 'last4', '-')}")
    return methods


def retrieve_payment_method(payment_method_id: str):
    """Retrieve a payment method by ID."""
    ensure_stripe_key()
    return stripe.PaymentMethod.retrieve(payment_method_id)


def attach_payment_method(payment_method_id: str, customer_id: str):
    """Attach a payment method to a customer (e.g. after SetupIntent confirm)."""
    ensure_stripe_key()
    return stripe.PaymentMethod.attach(payment_method_id, customer=customer_id)


def detach_payment_method(payment_method_id: str):
    """Detach a payment method from a customer."""
    ensure_stripe_key()
    return stripe.PaymentMethod.detach(payment_method_id)


def set_default_payment_method(customer_id: str, payment_method_id: str):
    """Set a payment method as the customer's default for subscriptions/invoices."""
    ensure_stripe_key()
    return stripe.Customer.modify(
        customer_id,
        invoice_settings={"default_payment_method": payment_method_id},
    )


if __name__ == "__main__":
    ensure_stripe_key()
    print("=== List payment methods for customer ===")
    # list_payment_methods("cus_xxx")
    print("=== Attach/Detach/Set default are used after SetupIntent or PaymentElement. ===")
