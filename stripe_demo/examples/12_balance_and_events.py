"""
Stripe Balance, Balance Transactions, and Events.
Balance: available and pending funds. Balance Transactions: ledger of moves.
Events: audit log of what happened (also used for webhooks).
Docs: https://docs.stripe.com/api/balance, balance_transactions, events
"""
import stripe
import sys
import os

sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
from config import STRIPE_SECRET_KEY, ensure_stripe_key

stripe.api_key = STRIPE_SECRET_KEY


def retrieve_balance():
    """Get current balance (available and pending by currency)."""
    ensure_stripe_key()
    balance = stripe.Balance.retrieve()
    for amount in balance.available:
        print(f"  available: {amount.amount/100} {amount.currency}")
    for amount in balance.pending:
        print(f"  pending:   {amount.amount/100} {amount.currency}")
    return balance


def list_balance_transactions(limit: int = 10, type: str = None):
    """List balance transactions (charges, refunds, payouts, etc.)."""
    ensure_stripe_key()
    params = {"limit": limit}
    if type:
        params["type"] = type
    bt = stripe.BalanceTransaction.list(**params)
    for t in bt.data:
        print(f"  {t.id} | {t.amount/100} {t.currency} | {t.type} | {t.created}")
    return bt


def retrieve_balance_transaction(txn_id: str):
    """Retrieve a single balance transaction."""
    ensure_stripe_key()
    return stripe.BalanceTransaction.retrieve(txn_id)


def list_events(limit: int = 10, type: str = None):
    """List recent events (e.g. charge.succeeded, payment_intent.created)."""
    ensure_stripe_key()
    params = {"limit": limit}
    if type:
        params["type"] = type
    events = stripe.Event.list(**params)
    for e in events.data:
        print(f"  {e.id} | {e.type} | {e.created}")
    return events


def retrieve_event(event_id: str):
    """Retrieve a single event (includes data.object)."""
    ensure_stripe_key()
    return stripe.Event.retrieve(event_id)


if __name__ == "__main__":
    ensure_stripe_key()
    print("=== Balance ===")
    retrieve_balance()
    print("=== Balance transactions ===")
    list_balance_transactions(limit=5)
    print("=== Events ===")
    list_events(limit=5)
