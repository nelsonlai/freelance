"""
Stripe Invoices API – create and manage invoices (one-time and subscription).
Docs: https://docs.stripe.com/api/invoices
"""
import stripe
import sys
import os

sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
from config import STRIPE_SECRET_KEY, DEFAULT_CURRENCY, ensure_stripe_key

stripe.api_key = STRIPE_SECRET_KEY


def create_invoice(customer_id: str, collection_method: str = "send_invoice", days_until_due: int = 30):
    """Create a draft invoice for a customer. Add line items with add_invoice_item."""
    ensure_stripe_key()
    params = {
        "customer": customer_id,
        "collection_method": collection_method,
    }
    if collection_method == "send_invoice":
        params["days_until_due"] = days_until_due
    inv = stripe.Invoice.create(**params)
    print(f"Created draft invoice: {inv.id}")
    return inv


def add_invoice_item(customer_id: str, amount_cents: int, currency: str = None, description: str = None, invoice: str = None):
    """Add a line item to the next invoice (or to a specific draft invoice)."""
    ensure_stripe_key()
    currency = currency or DEFAULT_CURRENCY
    params = {
        "customer": customer_id,
        "amount": amount_cents,
        "currency": currency,
    }
    if description:
        params["description"] = description
    if invoice:
        params["invoice"] = invoice
    item = stripe.InvoiceItem.create(**params)
    print(f"Added invoice item: {item.id}")
    return item


def finalize_invoice(invoice_id: str):
    """Finalize a draft invoice so it can be paid or sent."""
    ensure_stripe_key()
    inv = stripe.Invoice.finalize_invoice(invoice_id)
    print(f"Finalized invoice: {invoice_id} host_invoice_url={getattr(inv, 'hosted_invoice_url', None)}")
    return inv


def pay_invoice(invoice_id: str, paid_out_of_band: bool = False):
    """Mark invoice as paid (e.g. if paid offline). paid_out_of_band=True when paid outside Stripe."""
    ensure_stripe_key()
    return stripe.Invoice.pay(invoice_id, paid_out_of_band=paid_out_of_band)


def retrieve_invoice(invoice_id: str):
    """Retrieve an invoice."""
    ensure_stripe_key()
    return stripe.Invoice.retrieve(invoice_id)


def list_invoices(customer_id: str = None, status: str = None, limit: int = 10):
    """List invoices. status: draft|open|paid|uncollectible|void."""
    ensure_stripe_key()
    params = {"limit": limit}
    if customer_id:
        params["customer"] = customer_id
    if status:
        params["status"] = status
    return stripe.Invoice.list(**params)


def void_invoice(invoice_id: str):
    """Void a draft or open invoice so it cannot be paid."""
    ensure_stripe_key()
    return stripe.Invoice.void_invoice(invoice_id)


def send_invoice(invoice_id: str):
    """Send the invoice to the customer (email with hosted_invoice_url)."""
    ensure_stripe_key()
    return stripe.Invoice.send_invoice(invoice_id)


if __name__ == "__main__":
    ensure_stripe_key()
    print("=== Create draft invoice and add items ===")
    # 1. create_invoice(customer_id, collection_method="send_invoice", days_until_due=30)
    # 2. add_invoice_item(customer_id, 5000, description="Consulting", invoice=inv.id)
    # 3. finalize_invoice(inv.id)
    # 4. send_invoice(inv.id)  # or pay via payment_intent if collection_method='charge_automatically'
