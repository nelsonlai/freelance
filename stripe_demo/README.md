# Stripe Python Demo

Comprehensive Python examples showing how to use [Stripe](https://stripe.com) for payments, subscriptions, invoicing, webhooks, and more. All code uses the official [Stripe Python SDK](https://docs.stripe.com/api?lang=python).

---

## Table of Contents

- [Setup](#setup)
- [Configuration](#configuration)
- [Project Structure](#project-structure)
- [Examples Overview](#examples-overview)
- [Running Examples](#running-examples)
- [Stripe Concepts](#stripe-concepts)
- [API Quick Reference](#api-quick-reference)
- [Testing](#testing)
- [Webhooks](#webhooks)
- [Security & Best Practices](#security--best-practices)
- [Links](#links)

---

## Setup

1. **Create a Stripe account**  
   Sign up at [dashboard.stripe.com](https://dashboard.stripe.com/register).

2. **Install dependencies**

   ```bash
   pip install -r requirements.txt
   ```

   This installs:
   - `stripe` – official Stripe Python library
   - `flask` – optional, for the webhook server example
   - `python-dotenv` – optional, for loading `.env`

3. **Get your API keys**  
   In [Developers → API keys](https://dashboard.stripe.com/apikeys):
   - **Secret key** (`sk_test_...` or `sk_live_...`) – used only on the server
   - **Publishable key** (`pk_test_...` or `pk_live_...`) – safe to use in browsers/apps

   Use **test** keys while developing; they never move real money.

---

## Configuration

Set your keys via environment variables or a `.env` file in the project root:

```bash
# .env (do not commit; add to .gitignore)
STRIPE_SECRET_KEY=sk_test_xxxxxxxxxxxx
STRIPE_PUBLISHABLE_KEY=pk_test_xxxxxxxxxxxx

# Optional: for webhook signature verification (from Stripe CLI or Dashboard)
STRIPE_WEBHOOK_SECRET=whsec_xxxxxxxxxxxx

# Optional: URLs for Checkout / Payment Links
SUCCESS_URL=https://yoursite.com/success
CANCEL_URL=https://yoursite.com/cancel
```

- **STRIPE_SECRET_KEY** – Required for all server-side examples.
- **STRIPE_PUBLISHABLE_KEY** – Used by frontend (Stripe.js, mobile SDKs); examples don’t call it directly.
- **STRIPE_WEBHOOK_SECRET** – Required to verify webhook events (see [Webhooks](#webhooks)).

---

## Project Structure

```
stripe_demo/
├── README.md                 # This file
├── requirements.txt         # Python dependencies
├── config.py                # Loads STRIPE_SECRET_KEY, etc.
├── run_examples.py           # Run selected examples
└── examples/
    ├── 00_error_handling.py  # How to catch Stripe errors
    ├── 01_customers.py       # Customers CRUD
    ├── 02_products_prices.py  # Products and Prices catalog
    ├── 03_payment_intents.py # One-time payments (Payment Intents)
    ├── 04_checkout_sessions.py # Hosted Checkout (payment / subscription / setup)
    ├── 05_subscriptions.py   # Subscriptions, items, schedules
    ├── 06_invoices.py       # Invoices and invoice items
    ├── 07_refunds.py        # Refunds
    ├── 08_coupons_promotion_codes.py # Coupons and promotion codes
    ├── 09_payment_links.py   # Payment Links (no-code style)
    ├── 10_webhooks.py        # Webhook verification and handling
    ├── 11_setup_intents.py   # Save payment method without charging
    ├── 12_balance_and_events.py # Balance, balance transactions, events
    ├── 13_customer_portal.py # Billing portal for customers
    ├── 14_payment_methods.py # List/attach/detach payment methods
    ├── 15_tax_rates.py       # Tax rates for invoices/checkout
    └── flask_webhook_server.py # Minimal Flask webhook server
```

---

## Examples Overview

| File | What it demonstrates |
|------|------------------------|
| **00_error_handling** | Catching `CardError`, `InvalidRequestError`, etc. |
| **01_customers** | Create, retrieve, update, list, delete, search customers |
| **02_products_prices** | Products, one-time and recurring prices |
| **03_payment_intents** | Create/confirm/cancel PaymentIntents for one-time payments |
| **04_checkout_sessions** | Hosted Checkout for payment, subscription, or setup |
| **05_subscriptions** | Create/cancel subscriptions, add/update items, schedules |
| **06_invoices** | Draft invoices, line items, finalize, send, pay |
| **07_refunds** | Full and partial refunds by charge or PaymentIntent |
| **08_coupons_promotion_codes** | Percent/amount-off coupons and promotion codes |
| **09_payment_links** | One-time and subscription Payment Links |
| **10_webhooks** | Verify signature and handle event types |
| **11_setup_intents** | Save a card for later (no charge) |
| **12_balance_and_events** | Balance, balance transactions, events list |
| **13_customer_portal** | Billing portal session and configuration |
| **14_payment_methods** | List/attach/detach, set default payment method |
| **15_tax_rates** | Create and use tax rates |
| **flask_webhook_server** | Minimal Flask app that receives Stripe webhooks |

---

## Running Examples

Ensure `STRIPE_SECRET_KEY` is set, then:

```bash
# Run a specific example by number (e.g. customers)
python run_examples.py 01

# Run customers + products/prices (default)
python run_examples.py

# Run an example file directly
python examples/01_customers.py
python examples/03_payment_intents.py
```

Or from the `examples/` directory:

```bash
cd examples
python 01_customers.py
```

Each file’s `if __name__ == "__main__":` block shows a small flow (create, retrieve, list, etc.). Edit IDs (e.g. `customer_id`, `price_id`) to match your Stripe test data.

---

## Stripe Concepts

### Customers

- Represent buyers in your system.
- Store email, name, address, and **payment methods**.
- Required for subscriptions and for “charge saved card” flows.
- Create with `stripe.Customer.create(email=..., name=...)`.

### Products & Prices

- **Product** = what you sell (e.g. “Pro Plan”, “T‑shirt”).
- **Price** = how much and how often: one-time or recurring (e.g. $10/month).
- One product can have many prices. Checkout and Payment Links use **Price IDs** (`price_xxx`).

### Payment Intents

- Model a single payment (card, etc.) and its lifecycle.
- You create a PaymentIntent on the server, then the frontend uses `client_secret` with Stripe.js or Mobile SDKs to confirm.
- Status flow: `requires_payment_method` → `requires_confirmation` → `requires_action` (e.g. 3DS) → `succeeded` (or `requires_capture` for manual capture).

### Checkout Sessions

- Hosted payment pages. You create a session with `line_items`, `success_url`, `cancel_url`; Stripe returns a `url` to redirect the customer.
- Modes: `payment` (one-time), `subscription`, `setup` (save card only).
- No need to build your own payment form; Stripe hosts it.

### Subscriptions

- Recurring billing tied to a **Customer** and one or more **Prices** (recurring).
- Create with `stripe.Subscription.create(customer=..., items=[{"price": "price_xxx", "quantity": 1}])`.
- Stripe creates **Invoices** and **PaymentIntents** for each billing cycle.

### Invoices

- Invoices can be created by subscriptions (automatic) or manually.
- For manual: create a draft, add line items with `stripe.InvoiceItem.create(...)`, then `stripe.Invoice.finalize_invoice(...)` and optionally `stripe.Invoice.send_invoice(...)`.

### Webhooks

- Stripe sends **events** (e.g. `payment_intent.succeeded`, `customer.subscription.deleted`) to your endpoint via HTTP POST.
- You must **verify the signature** using `Stripe-Signature` and your webhook secret, then handle `event.type` and `event.data.object`.

### Idempotency

- For create/update operations that change money or state, send an `Idempotency-Key` header (unique value per “logical” request) so retries don’t double-charge. The Python SDK can accept `idempotency_key='...'` on create/update calls.

---

## API Quick Reference

All examples use the same pattern: `stripe.api_key = STRIPE_SECRET_KEY` (or set via `config`), then call the resource.

| Resource | Create | Retrieve | List | Update | Delete / Cancel |
|----------|--------|----------|------|--------|------------------|
| **Customers** | `stripe.Customer.create(...)` | `stripe.Customer.retrieve(id)` | `stripe.Customer.list(...)` | `stripe.Customer.modify(id, ...)` | `stripe.Customer.delete(id)` |
| **Products** | `stripe.Product.create(...)` | `stripe.Product.retrieve(id)` | `stripe.Product.list(...)` | `stripe.Product.modify(id, ...)` | — |
| **Prices** | `stripe.Price.create(...)` | `stripe.Price.retrieve(id)` | `stripe.Price.list(...)` | `stripe.Price.modify(id, ...)` | — |
| **PaymentIntents** | `stripe.PaymentIntent.create(...)` | `stripe.PaymentIntent.retrieve(id)` | `stripe.PaymentIntent.list(...)` | `stripe.PaymentIntent.modify(id, ...)` | `stripe.PaymentIntent.cancel(id)` |
| **Checkout Sessions** | `stripe.checkout.Session.create(...)` | `stripe.checkout.Session.retrieve(id)` | `stripe.checkout.Session.list(...)` | `stripe.checkout.Session.modify(id, ...)` | `stripe.checkout.Session.expire(id)` |
| **Subscriptions** | `stripe.Subscription.create(...)` | `stripe.Subscription.retrieve(id)` | `stripe.Subscription.list(...)` | `stripe.Subscription.modify(id, ...)` | `stripe.Subscription.delete(id)` or `modify(..., cancel_at_period_end=True)` |
| **Invoices** | `stripe.Invoice.create(...)` | `stripe.Invoice.retrieve(id)` | `stripe.Invoice.list(...)` | — | `stripe.Invoice.void_invoice(id)` |
| **Refunds** | `stripe.Refund.create(...)` | `stripe.Refund.retrieve(id)` | `stripe.Refund.list(...)` | `stripe.Refund.modify(id, ...)` | `stripe.Refund.cancel(id)` (pending only) |

Amounts in the API are in the **smallest currency unit** (e.g. cents for USD). So $19.99 = `1999`.

---

## Testing

- Use **test keys** (`sk_test_...`, `pk_test_...`) so no real charges occur.
- Test cards: [Stripe test cards](https://docs.stripe.com/testing#cards), e.g. `4242 4242 4242 4242` for success.
- Trigger test events: [Stripe CLI](https://docs.stripe.com/stripe-cli) – e.g. `stripe trigger payment_intent.succeeded`.
- Forward webhooks to your machine: `stripe listen --forward-to localhost:4242/webhook` (use the printed webhook secret in `.env` as `STRIPE_WEBHOOK_SECRET`).

---

## Webhooks

1. **Local testing**
   - Run the Flask webhook server: `flask --app examples/flask_webhook_server run --port 4242`
   - In another terminal: `stripe listen --forward-to localhost:4242/webhook`
   - Use the `whsec_...` secret from the CLI output as `STRIPE_WEBHOOK_SECRET` in your env.

2. **Verify signatures**
   - Always verify using the raw request body and `Stripe-Signature` with `stripe.Webhook.construct_event(payload, sig_header, secret)`.

3. **Respond quickly**
   - Return `2xx` immediately, then process the event in a background job/queue so the endpoint doesn’t time out.

4. **Idempotency**
   - Stripe may send the same event more than once. Track processed `event.id` (or `data.object.id` + `type`) to avoid duplicate work.

---

## Security & Best Practices

- **Never** put your secret key in client-side code or in version control.
- Use **HTTPS** in production for all endpoints, including webhooks.
- Prefer **Stripe.js** or official mobile SDKs on the frontend so card data never touches your server (PCI scope reduction).
- Use **Checkout** or **Payment Element** when possible; they handle SCA, 3DS, and local methods.
- Restrict API keys (e.g. [Restricted keys](https://docs.stripe.com/keys#limit-access)) to the minimum needed.
- Rotate webhook signing secrets periodically and when you suspect exposure.

---

## Links

- [Stripe API Reference (Python)](https://docs.stripe.com/api?lang=python)
- [Stripe Docs](https://docs.stripe.com/)
- [Payments quickstart](https://docs.stripe.com/payments/quickstart)
- [Checkout – build subscriptions](https://docs.stripe.com/payments/checkout/build-subscriptions)
- [Webhooks](https://docs.stripe.com/webhooks)
- [Testing](https://docs.stripe.com/testing)
- [Stripe Python on GitHub](https://github.com/stripe/stripe-python)
