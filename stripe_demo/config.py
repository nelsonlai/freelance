"""
Stripe configuration and initialization.
Load API key from STRIPE_SECRET_KEY environment variable.
Use test keys (sk_test_...) for development; live keys (sk_live_...) for production.
"""
import os

try:
    from dotenv import load_dotenv
    load_dotenv()
except ImportError:
    pass

# Secret key: never expose in client-side code. Use for server-side API calls.
STRIPE_SECRET_KEY = os.environ.get("STRIPE_SECRET_KEY", "")

# Publishable key: safe to use in browser/mobile apps for Stripe.js / mobile SDKs.
STRIPE_PUBLISHABLE_KEY = os.environ.get("STRIPE_PUBLISHABLE_KEY", "")

# Webhook signing secret: verify webhook events (get from Stripe CLI or Dashboard).
STRIPE_WEBHOOK_SECRET = os.environ.get("STRIPE_WEBHOOK_SECRET", "")

# Currency and locale defaults
DEFAULT_CURRENCY = "usd"
DEFAULT_SUCCESS_URL = os.environ.get("SUCCESS_URL", "https://example.com/success")
DEFAULT_CANCEL_URL = os.environ.get("CANCEL_URL", "https://example.com/cancel")


def ensure_stripe_key():
    """Raise if STRIPE_SECRET_KEY is not set."""
    if not STRIPE_SECRET_KEY or not STRIPE_SECRET_KEY.startswith("sk_"):
        raise ValueError(
            "Set STRIPE_SECRET_KEY in environment or .env. "
            "Get keys at https://dashboard.stripe.com/apikeys"
        )
