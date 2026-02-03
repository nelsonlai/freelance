from typing import List
import os
import logging
import requests

log = logging.getLogger(__name__)

def write_lines(path, lines: List[str]) -> None:
    with open(path, "w", encoding="utf-8") as f:
        for line in lines:
            f.write(line + "\n")

def read_lines(path):
    with open(path, "r", encoding="utf-8") as f:
        return [line.rstrip("\n") for line in f]

def get_api_key() -> str:
    return os.environ.get("API_KEY", "")

def greet(name: str) -> None:
    print(f"Hello, {name}!")
    log.info("Greeted %s", name)

def fetch_json(url: str):
    # Network call is mocked in tests; no real I/O occurs.
    return requests.get(url, timeout=5).json()
