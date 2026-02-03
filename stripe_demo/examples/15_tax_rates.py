"""
Stripe Tax Rates – create and use tax rates for invoices and checkouts.
Docs: https://docs.stripe.com/api/tax_rates
"""
import stripe
import sys
import os

sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
from config import STRIPE_SECRET_KEY, ensure_stripe_key

stripe.api_key = STRIPE_SECRET_KEY


def create_tax_rate(display_name: str, percentage: float, inclusive: bool = False, description: str = None):
    """
    Create a tax rate (e.g. VAT 20%). inclusive=True means price includes tax.
    """
    ensure_stripe_key()
    params = {
        "display_name": display_name,
        "percentage": percentage,
        "inclusive": inclusive,
    }
    if description:
        params["description"] = description
    rate = stripe.TaxRate.create(**params)
    print(f"Created tax rate: {rate.id} {rate.display_name} {rate.percentage}%")
    return rate


def retrieve_tax_rate(tax_rate_id: str):
    """Retrieve a tax rate."""
    ensure_stripe_key()
    return stripe.TaxRate.retrieve(tax_rate_id)


def list_tax_rates(active: bool = True, limit: int = 10):
    """List tax rates."""
    ensure_stripe_key()
    return stripe.TaxRate.list(active=active, limit=limit)


def update_tax_rate(tax_rate_id: str, **kwargs):
    """Update display_name, description, or active. Percentage cannot be changed."""
    ensure_stripe_key()
    return stripe.TaxRate.modify(tax_rate_id, **kwargs)


if __name__ == "__main__":
    ensure_stripe_key()
    print("=== Create tax rate (VAT 20%) ===")
    rate = create_tax_rate("VAT", 20.0, inclusive=False, description="Value Added Tax")
    print("  Use in invoice: default_tax_rates=[rate.id], or in line items.")
