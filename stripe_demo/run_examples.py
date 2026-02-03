#!/usr/bin/env python3
"""
Run Stripe demo examples (requires STRIPE_SECRET_KEY set).
Usage: python run_examples.py [01|02|...|15]
If no number given, runs 01_customers and 02_products_prices only.
"""
import os
import sys

ROOT = os.path.dirname(os.path.abspath(__file__))
EXAMPLES = os.path.join(ROOT, "examples")
sys.path.insert(0, ROOT)
os.chdir(ROOT)

# Ensure key is set
from config import ensure_stripe_key
ensure_stripe_key()

which = sys.argv[1] if len(sys.argv) > 1 else None
if which is None:
    # default: run 01 and 02
    candidates = ["01_customers.py", "02_products_prices.py"]
else:
    name = f"{which}_" if len(which) <= 2 and which.isdigit() else ""
    candidates = [f for f in os.listdir(EXAMPLES) if f.endswith(".py") and f.startswith(name) and not f.startswith("00") and f != "flask_webhook_server.py"]
    if not candidates:
        candidates = ["01_customers.py", "02_products_prices.py"]

for mod in sorted(candidates)[:5]:  # cap at 5 to avoid long runs
    path = os.path.join(EXAMPLES, mod)
    print(f"\n--- Running {mod} ---")
    with open(path) as f:
        code = f.read()
    exec(compile(code, path, "exec"), {"__name__": "__main__", "__file__": path})
