"""Simple smoke test script for post-deployment verification."""
from __future__ import annotations

import os
import sys
import time

import requests


def main() -> None:
    base_url = os.getenv("SERVICE_URL")
    if not base_url:
        print("SERVICE_URL environment variable not set.", file=sys.stderr)
        sys.exit(1)

    health_url = f"{base_url.rstrip('/')}/healthz"
    deadline = time.time() + 30

    while time.time() < deadline:
        try:
            response = requests.get(health_url, timeout=5)
            if response.status_code == 200:
                payload = response.json()
                print(f"Smoke test passed: {payload}")
                return
        except requests.RequestException as exc:
            print(f"Health check attempt failed: {exc}", file=sys.stderr)
        time.sleep(3)

    print("Smoke test failed: service did not return healthy response in time.", file=sys.stderr)
    sys.exit(1)


if __name__ == "__main__":
    main()

