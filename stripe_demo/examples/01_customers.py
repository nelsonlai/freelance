"""
Stripe Customers API – create, retrieve, update, list, delete.
Customers represent your buyers; you attach payment methods and subscriptions to them.
Docs: https://docs.stripe.com/api/customers
"""
import stripe
import sys
import os

sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
from config import STRIPE_SECRET_KEY, ensure_stripe_key

stripe.api_key = STRIPE_SECRET_KEY


def create_customer(email: str, name: str = None, metadata: dict = None):
    """Create a new customer. Required for subscriptions and saving payment methods."""
    ensure_stripe_key()
    params = {"email": email}
    if name:
        params["name"] = name
    if metadata:
        params["metadata"] = metadata
    customer = stripe.Customer.create(**params)
    print(f"Created customer: {customer.id} ({customer.email})")
    return customer


def retrieve_customer(customer_id: str):
    """Retrieve a customer by ID."""
    ensure_stripe_key()
    customer = stripe.Customer.retrieve(customer_id)
    print(f"Retrieved: {customer.id} {customer.email}")
    return customer


def update_customer(customer_id: str, **kwargs):
    """Update customer (email, name, address, metadata, default_source, invoice_settings, etc.)."""
    ensure_stripe_key()
    customer = stripe.Customer.modify(customer_id, **kwargs)
    print(f"Updated customer: {customer.id}")
    return customer


def list_customers(limit: int = 10, email: str = None):
    """List customers with optional filters. Supports pagination via starting_after."""
    ensure_stripe_key()
    params = {"limit": limit}
    if email:
        params["email"] = email
    customers = stripe.Customer.list(**params)
    for c in customers.data:
        print(f"  {c.id} | {c.email} | {c.name or '-'}")
    return customers


def delete_customer(customer_id: str):
    """Permanently delete a customer. Subscriptions and unpaid invoices are deleted."""
    ensure_stripe_key()
    deleted = stripe.Customer.delete(customer_id)
    print(f"Deleted customer: {customer_id}")
    return deleted


def search_customers(query: str):
    """Search customers (e.g. by email or name). Requires Stripe API search."""
    ensure_stripe_key()
    results = stripe.Customer.search(query=query)
    for c in results.data:
        print(f"  {c.id} | {c.email} | {c.name or '-'}")
    return results


if __name__ == "__main__":
    ensure_stripe_key()
    print("=== Create customer ===")
    c = create_customer("demo@example.com", name="Demo User", metadata={"source": "demo"})
    print("=== Retrieve ===")
    retrieve_customer(c.id)
    print("=== Update ===")
    update_customer(c.id, description="Updated from demo")
    print("=== List ===")
    list_customers(limit=3)
    print("=== Delete (comment out to keep) ===")
    # delete_customer(c.id)
