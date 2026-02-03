"""Tests for the sample FastAPI application."""
from fastapi.testclient import TestClient

from app.api import app


client = TestClient(app)


def test_health_endpoint_returns_ok() -> None:
    response = client.get("/healthz")
    assert response.status_code == 200
    payload = response.json()
    assert payload["status"] == "ok"
    assert payload["service"] == "Sample Python CI/CD API"


def test_greet_returns_message() -> None:
    response = client.post("/greet", json={"name": "Ada"})
    assert response.status_code == 200
    payload = response.json()
    assert payload["message"].startswith("Hello, Ada")


def test_greet_validates_name() -> None:
    response = client.post("/greet", json={"name": ""})
    assert response.status_code == 422

