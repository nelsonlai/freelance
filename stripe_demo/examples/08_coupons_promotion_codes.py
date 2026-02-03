"""
Stripe Coupons and Promotion Codes – discounts for customers.
Coupons define the discount; Promotion Codes are customer-facing codes (e.g. SAVE20).
Docs: https://docs.stripe.com/api/coupons, https://docs.stripe.com/api/promotion_codes
"""
import stripe
import sys
import os

sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
from config import STRIPE_SECRET_KEY, ensure_stripe_key

stripe.api_key = STRIPE_SECRET_KEY


def create_coupon_percent(percent_off: float, duration: str = "once", name: str = None):
    """
    Create a percentage-off coupon.
    duration: 'forever'|'once'|'repeating'; duration_in_months required when 'repeating'.
    """
    ensure_stripe_key()
    params = {"percent_off": percent_off, "duration": duration}
    if name:
        params["name"] = name
    coupon = stripe.Coupon.create(**params)
    print(f"Created coupon: {coupon.id} {percent_off}% off {duration}")
    return coupon


def create_coupon_amount_off(amount_off_cents: int, currency: str, duration: str = "once", name: str = None):
    """Create a fixed-amount-off coupon (e.g. $5 off)."""
    ensure_stripe_key()
    params = {"amount_off": amount_off_cents, "currency": currency, "duration": duration}
    if name:
        params["name"] = name
    coupon = stripe.Coupon.create(**params)
    print(f"Created coupon: {coupon.id} {amount_off_cents/100} {currency} off")
    return coupon


def create_promotion_code(coupon_id: str, code: str = None, max_redemptions: int = None):
    """Create a promotion code that customers enter at checkout (e.g. SAVE20)."""
    ensure_stripe_key()
    params = {"coupon": coupon_id}
    if code:
        params["code"] = code
    if max_redemptions is not None:
        params["max_redemptions"] = max_redemptions
    promo = stripe.PromotionCode.create(**params)
    print(f"Created promotion code: {promo.code} (id={promo.id})")
    return promo


def retrieve_coupon(coupon_id: str):
    """Retrieve a coupon."""
    ensure_stripe_key()
    return stripe.Coupon.retrieve(coupon_id)


def retrieve_promotion_code(promo_id: str):
    """Retrieve a promotion code."""
    ensure_stripe_key()
    return stripe.PromotionCode.retrieve(promo_id)


def list_coupons(limit: int = 10):
    """List coupons."""
    ensure_stripe_key()
    return stripe.Coupon.list(limit=limit)


def list_promotion_codes(coupon_id: str = None, code: str = None, limit: int = 10):
    """List promotion codes, optionally by coupon or code."""
    ensure_stripe_key()
    params = {"limit": limit}
    if coupon_id:
        params["coupon"] = coupon_id
    if code:
        params["code"] = code
    return stripe.PromotionCode.list(**params)


def deactivate_promotion_code(promo_id: str):
    """Deactivate a promotion code so it can't be used."""
    ensure_stripe_key()
    return stripe.PromotionCode.modify(promo_id, active=False)


if __name__ == "__main__":
    ensure_stripe_key()
    print("=== Create 20% off coupon ===")
    coup = create_coupon_percent(20, "once", name="20% off once")
    print("=== Create promotion code SAVE20 ===")
    promo = create_promotion_code(coup.id, code="SAVE20")
    print("  Use in Checkout: allow_promotion_codes=True, or pass discounts=[{coupon: coup.id}]")
