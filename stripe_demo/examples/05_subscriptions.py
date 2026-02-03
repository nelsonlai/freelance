"""
Stripe Subscriptions API – recurring billing.
Create and manage subscriptions, subscription items, and schedules.
Docs: https://docs.stripe.com/api/subscriptions
"""
import stripe
import sys
import os

sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
from config import STRIPE_SECRET_KEY, ensure_stripe_key

stripe.api_key = STRIPE_SECRET_KEY


def create_subscription(
    customer_id: str,
    price_id: str,
    quantity: int = 1,
    metadata: dict = None,
    trial_period_days: int = None,
    payment_behavior: str = "default_incomplete",
):
    """
    Create a subscription for a customer on a recurring price.
    payment_behavior: 'default_incomplete' (require payment upfront),
                      'allow_incomplete', 'error_if_incomplete', 'pending_if_incomplete'
    """
    ensure_stripe_key()
    params = {
        "customer": customer_id,
        "items": [{"price": price_id, "quantity": quantity}],
        "payment_behavior": payment_behavior,
    }
    if metadata:
        params["metadata"] = metadata
    if trial_period_days is not None:
        params["trial_period_days"] = trial_period_days
    sub = stripe.Subscription.create(**params)
    print(f"Created subscription: {sub.id} status={sub.status}")
    return sub


def retrieve_subscription(subscription_id: str, expand: list = None):
    """Retrieve a subscription. expand e.g. ['latest_invoice.payment_intent']."""
    ensure_stripe_key()
    params = {}
    if expand:
        params["expand"] = expand
    return stripe.Subscription.retrieve(subscription_id, **params)


def update_subscription(subscription_id: str, **kwargs):
    """Update subscription: cancel_at_period_end, metadata, items, proration_behavior, etc."""
    ensure_stripe_key()
    return stripe.Subscription.modify(subscription_id, **kwargs)


def cancel_subscription(subscription_id: str, cancel_at_period_end: bool = True):
    """Cancel immediately or at period end. At period end keeps access until current period ends."""
    ensure_stripe_key()
    if cancel_at_period_end:
        sub = stripe.Subscription.modify(subscription_id, cancel_at_period_end=True)
        print(f"Subscription {subscription_id} will cancel at period end")
        return sub
    return stripe.Subscription.delete(subscription_id)


def list_subscriptions(customer_id: str = None, status: str = None, limit: int = 10):
    """List subscriptions. status: 'active'|'past_due'|'unpaid'|'canceled'|'incomplete'|'incomplete_expired'|'trialing'|'paused'."""
    ensure_stripe_key()
    params = {"limit": limit}
    if customer_id:
        params["customer"] = customer_id
    if status:
        params["status"] = status
    subs = stripe.Subscription.list(**params)
    for s in subs.data:
        print(f"  {s.id} | customer={s.customer} | status={s.status}")
    return subs


def add_subscription_item(subscription_id: str, price_id: str, quantity: int = 1):
    """Add another price to an existing subscription (e.g. add-on)."""
    ensure_stripe_key()
    return stripe.SubscriptionItem.create(
        subscription=subscription_id,
        price=price_id,
        quantity=quantity,
    )


def update_subscription_item(item_id: str, quantity: int = None, price: str = None):
    """Change quantity or switch price for a subscription item."""
    ensure_stripe_key()
    params = {}
    if quantity is not None:
        params["quantity"] = quantity
    if price:
        params["price"] = price
    return stripe.SubscriptionItem.modify(item_id, **params)


def create_subscription_schedule(
    customer_id: str,
    phases: list,
    start_date: str = "now",
):
    """
    Schedule future subscription phases (e.g. introductory then full price).
    phases: [{"items": [{"price": "price_xxx", "quantity": 1}], "iterations": 3}, ...]
    """
    ensure_stripe_key()
    params = {
        "customer": customer_id,
        "phases": phases,
        "start_date": start_date,
    }
    return stripe.SubscriptionSchedule.create(**params)


if __name__ == "__main__":
    ensure_stripe_key()
    print("=== Create customer and recurring price first, then: ===")
    print("  create_subscription(customer_id, price_id)")
    print("  list_subscriptions(customer_id=customer_id)")
    print("  cancel_subscription(sub_id, cancel_at_period_end=True)")
