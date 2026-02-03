# syntax=docker/dockerfile:1.7-labs

FROM python:3.12-slim AS base
ENV PYTHONDONTWRITEBYTECODE=1
ENV PYTHONUNBUFFERED=1
WORKDIR /app

FROM base AS builder
RUN apt-get update && apt-get install -y build-essential && rm -rf /var/lib/apt/lists/*
COPY requirements.txt requirements-dev.txt ./
RUN pip install --upgrade pip && pip install -r requirements.txt

FROM base AS runtime
COPY --from=builder /usr/local /usr/local
COPY app app
COPY requirements.txt .
ENV PORT=8080
EXPOSE 8080
CMD ["uvicorn", "app.api:app", "--host", "0.0.0.0", "--port", "8080"]

