"""FastAPI application used in the CI/CD teaching project."""
from __future__ import annotations

import os
import datetime as dt
from typing import Optional

from fastapi import FastAPI
from pydantic import BaseModel, Field


def _get_commit_sha() -> str:
    """Return the short commit SHA injected by the pipeline, if available."""
    return os.getenv("GIT_COMMIT", "unknown")


app = FastAPI(title="Sample Python CI/CD API", version="0.1.0")


class GreetingRequest(BaseModel):
    """Payload accepted by the greeting endpoint."""

    name: str = Field(..., min_length=1, max_length=100)
    language: Optional[str] = Field(
        default="en",
        description="ISO 639-1 language code. Currently supports EN and ES.",
    )


class GreetingResponse(BaseModel):
    """Response returned by the greeting endpoint."""

    message: str
    served_at: dt.datetime


@app.get("/healthz", summary="Service health probe")
async def health() -> dict[str, str]:
    """Return service health status for monitoring and smoke tests."""
    return {
        "status": "ok",
        "service": app.title,
        "version": app.version,
        "commit": _get_commit_sha(),
    }


@app.post("/greet", response_model=GreetingResponse, summary="Personalized greeting")
async def greet(payload: GreetingRequest) -> GreetingResponse:
    """Return a greeting message in the requested language."""
    templates = {
        "en": "Hello, {name}! Welcome to the CI/CD workshop.",
        "es": "¡Hola, {name}! Bienvenido al taller de CI/CD.",
    }
    template = templates.get(payload.language or "en", templates["en"])
    return GreetingResponse(
        message=template.format(name=payload.name),
        served_at=dt.datetime.utcnow(),
    )

