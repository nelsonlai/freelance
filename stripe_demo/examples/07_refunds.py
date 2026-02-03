"""
Stripe Refunds API – refund charges and PaymentIntents.
Docs: https://docs.stripe.com/api/refunds
"""
import stripe
import sys
import os

sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
from config import STRIPE_SECRET_KEY, ensure_stripe_key

stripe.api_key = STRIPE_SECRET_KEY


def create_refund(
    charge_id: str = None,
    payment_intent_id: str = None,
    amount_cents: int = None,
    reason: str = None,
    metadata: dict = None,
):
    """
    Create a refund. Provide charge_id or payment_intent_id.
    amount_cents: partial refund amount; omit for full refund.
    reason: 'duplicate'|'fraudulent'|'requested_by_customer'
    """
    ensure_stripe_key()
    if not charge_id and not payment_intent_id:
        raise ValueError("Provide charge_id or payment_intent_id")
    params = {}
    if charge_id:
        params["charge"] = charge_id
    if payment_intent_id:
        params["payment_intent"] = payment_intent_id
    if amount_cents is not None:
        params["amount"] = amount_cents
    if reason:
        params["reason"] = reason
    if metadata:
        params["metadata"] = metadata
    refund = stripe.Refund.create(**params)
    print(f"Created refund: {refund.id} amount={refund.amount} status={refund.status}")
    return refund


def retrieve_refund(refund_id: str):
    """Retrieve a refund by ID."""
    ensure_stripe_key()
    return stripe.Refund.retrieve(refund_id)


def update_refund(refund_id: str, metadata: dict = None):
    """Update refund metadata. Only pending refunds can be updated."""
    ensure_stripe_key()
    params = {}
    if metadata:
        params["metadata"] = metadata
    return stripe.Refund.modify(refund_id, **params)


def cancel_refund(refund_id: str):
    """Cancel a pending refund."""
    ensure_stripe_key()
    return stripe.Refund.cancel(refund_id)


def list_refunds(charge_id: str = None, payment_intent_id: str = None, limit: int = 10):
    """List refunds, optionally by charge or payment_intent."""
    ensure_stripe_key()
    params = {"limit": limit}
    if charge_id:
        params["charge"] = charge_id
    if payment_intent_id:
        params["payment_intent"] = payment_intent_id
    return stripe.Refund.list(**params)


if __name__ == "__main__":
    ensure_stripe_key()
    print("=== Refund a charge (use charge_id from a PaymentIntent.charges or Charge) ===")
    print("  create_refund(charge_id='ch_xxx')")
    print("  create_refund(payment_intent_id='pi_xxx', amount_cents=500, reason='requested_by_customer')")
