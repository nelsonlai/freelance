"""
Stripe Products and Prices – catalog for one-time and recurring purchases.
Products = what you sell; Prices = how much and how often (one-time or recurring).
Docs: https://docs.stripe.com/api/products, https://docs.stripe.com/api/prices
"""
import stripe
import sys
import os

sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
from config import STRIPE_SECRET_KEY, DEFAULT_CURRENCY, ensure_stripe_key

stripe.api_key = STRIPE_SECRET_KEY


def create_product(name: str, description: str = None, images: list = None, metadata: dict = None):
    """Create a product. Attach prices to sell it."""
    ensure_stripe_key()
    params = {"name": name}
    if description:
        params["description"] = description
    if images:
        params["images"] = images
    if metadata:
        params["metadata"] = metadata
    product = stripe.Product.create(**params)
    print(f"Created product: {product.id} - {product.name}")
    return product


def create_price_one_time(product_id: str, unit_amount_cents: int, currency: str = None):
    """Create a one-time price (e.g. $10.00 = 1000 cents)."""
    ensure_stripe_key()
    currency = currency or DEFAULT_CURRENCY
    price = stripe.Price.create(
        product=product_id,
        unit_amount=unit_amount_cents,
        currency=currency,
    )
    print(f"Created one-time price: {price.id} {price.unit_amount/100} {currency}")
    return price


def create_price_recurring(product_id: str, unit_amount_cents: int, interval: str = "month", currency: str = None):
    """Create a recurring price. interval: 'day'|'week'|'month'|'year'."""
    ensure_stripe_key()
    currency = currency or DEFAULT_CURRENCY
    price = stripe.Price.create(
        product=product_id,
        unit_amount=unit_amount_cents,
        currency=currency,
        recurring={"interval": interval},
    )
    print(f"Created recurring price: {price.id} {price.unit_amount/100} {currency}/{interval}")
    return price


def retrieve_product(product_id: str):
    """Retrieve a product by ID."""
    ensure_stripe_key()
    return stripe.Product.retrieve(product_id)


def retrieve_price(price_id: str):
    """Retrieve a price by ID."""
    ensure_stripe_key()
    return stripe.Price.retrieve(price_id)


def list_products(active: bool = True, limit: int = 10):
    """List products. Use active=True to get only active products."""
    ensure_stripe_key()
    products = stripe.Product.list(active=active, limit=limit)
    for p in products.data:
        print(f"  {p.id} | {p.name} | active={p.active}")
    return products


def list_prices(product_id: str = None, active: bool = True, limit: int = 10):
    """List prices, optionally filtered by product."""
    ensure_stripe_key()
    params = {"active": active, "limit": limit}
    if product_id:
        params["product"] = product_id
    prices = stripe.Price.list(**params)
    for pr in prices.data:
        recurring = getattr(pr.recurring, "interval", None) if pr.recurring else None
        rec = f"/{recurring}" if recurring else " one-time"
        print(f"  {pr.id} | {pr.unit_amount/100} {pr.currency}{rec}")
    return prices


def update_product(product_id: str, **kwargs):
    """Update product (name, description, images, metadata, active, etc.)."""
    ensure_stripe_key()
    return stripe.Product.modify(product_id, **kwargs)


def deactivate_price(price_id: str):
    """Set price to inactive so it can't be used for new purchases."""
    ensure_stripe_key()
    return stripe.Price.modify(price_id, active=False)


if __name__ == "__main__":
    ensure_stripe_key()
    print("=== Create product ===")
    prod = create_product("Demo T-Shirt", description="A demo product for Stripe", metadata={"sku": "DEMO-001"})
    print("=== One-time price ===")
    p1 = create_price_one_time(prod.id, 1999)  # $19.99
    print("=== Recurring price ===")
    p2 = create_price_recurring(prod.id, 999, "month")  # $9.99/month
    print("=== List products ===")
    list_products(limit=5)
    print("=== List prices for product ===")
    list_prices(product_id=prod.id)
