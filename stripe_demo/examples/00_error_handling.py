"""
Stripe error handling – how to catch and respond to API errors.
Docs: https://docs.stripe.com/api/errors, https://docs.stripe.com/error-handling
"""
import stripe
import sys
import os

sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
from config import STRIPE_SECRET_KEY, ensure_stripe_key

stripe.api_key = STRIPE_SECRET_KEY

# Stripe Python raises subclasses of stripe.error.StripeError:
# - stripe.error.CardError: card declined, etc. (has .user_message, .code, .decline_code)
# - stripe.error.RateLimitError: too many requests
# - stripe.error.InvalidRequestError: bad params (400)
# - stripe.error.AuthenticationError: invalid or missing API key (401)
# - stripe.error.APIConnectionError: network failure
# - stripe.error.StripeError: base class for all Stripe errors


def example_safe_call():
    """Example: wrap Stripe calls and handle errors appropriately."""
    try:
        ensure_stripe_key()
        customer = stripe.Customer.retrieve("cus_nonexistent")
        return customer
    except stripe.error.CardError as e:
        # Card was declined – show user_message to customer
        print(f"Card declined: {e.user_message} (code={e.code}, decline_code={e.decline_code})")
    except stripe.error.RateLimitError as e:
        print("Too many requests. Retry with backoff.")
    except stripe.error.InvalidRequestError as e:
        print(f"Invalid request: {e.user_message} param={e.param}")
    except stripe.error.AuthenticationError as e:
        print("Invalid API key or auth failed.")
    except stripe.error.APIConnectionError as e:
        print("Network error. Check connectivity.")
    except stripe.error.StripeError as e:
        print(f"Stripe error: {e}")
    except Exception as e:
        print(f"Unexpected: {e}")
    return None


if __name__ == "__main__":
    example_safe_call()
