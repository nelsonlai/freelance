<!-- Module 5 – Hands-on Project -->
# Module 5 – Guided Python CI/CD Project

## 1. Project Overview
- **Objective**: Build, test, package, and deploy a Python FastAPI service using automated CI/CD pipelines.
- **Deliverables**: Working web API, CI pipeline (lint ➜ tests ➜ build), CD pipeline (Docker ➜ Terraform ➜ deployment), observability hooks, documentation.
- **Teaching Format**: 2 × 90-minute lab sessions plus homework extension.

## 2. Repository Layout
```
sample_python_app/
├── app/
│   ├── __init__.py
│   └── api.py            # FastAPI router
├── tests/
│   └── test_api.py       # pytest suite with coverage
├── scripts/
│   └── smoke_test.py     # Post-deploy validation script
├── infra/
│   ├── main.tf           # Terraform ECS service definition (mocked for lab)
│   └── variables.tf
├── Dockerfile
├── pyproject.toml
├── requirements.txt
├── requirements-dev.txt
├── tox.ini
└── .github/workflows/
    ├── ci.yml
    └── cd.yml
```

Provide students with starter repo; each section of the lab enhances a specific component.

## 3. Lab Part 1 – Build the API
1. Create FastAPI endpoint returning health status and greeting.
2. Add request model with validation using `pydantic`.
3. Write unit tests with `pytest` and `httpx.AsyncClient`.
4. Ensure local execution via `uvicorn app.api:app --reload`.

**Checkpoint**: `pytest` passes locally; explain importance of green tests before CI run.

## 4. Lab Part 2 – Configure CI
1. Populate `pyproject.toml` with metadata and pytest options.
2. Define `tox.ini` environments for linting and testing.
3. Author GitHub Actions workflow:
   - Trigger on pull requests and main branch pushes.
   - Cache dependencies.
   - Run `tox -e lint` and `tox -e py311`.
   - Build wheel artifact and upload.
4. Add status badge to README.

**Stretch**: Introduce CodeQL or `pip-audit` job for security scanning.

## 5. Lab Part 3 – Containerization
1. Write Dockerfile using multi-stage build for deterministic images.
2. Build locally (`docker build -t sample-api:dev .`) and run container.
3. Add `docker-compose.yml` (optional) for local dev conveniences.

Discuss image tagging conventions (commit SHA, semantic version).

## 6. Lab Part 4 – Infrastructure & CD
1. Review Terraform configuration (mock AWS ECS setup). Emphasize variables and state management.
2. Create GitHub Actions CD workflow triggered by successful CI runs.
3. Inject environment variables/secrets via GitHub Environments.
4. Run `scripts/smoke_test.py` during deploy to validate `/healthz`.
5. Demonstrate manual approval gate for production environment.

**Optional Extension**: Swap Terraform for Docker Compose deployment on a self-hosted server.

## 7. Lab Part 5 – Observability & Rollback
- Add basic logging and `/metrics` stub.
- Configure pipeline step to push deployment metadata to a mock monitoring service (e.g., log message or stub script).
- Simulate failure and practice rollback by redeploying previous artifact.

## 8. Assessment Rubric
- **CI Configuration (30%)**: Pipeline passes, lint/test/build stages implemented, artifacts uploaded.
- **CD Configuration (30%)**: Docker image builds, Terraform executed (or mocked), smoke test integrated.
- **Code Quality (20%)**: API functionality, test coverage ≥80%, clean code style.
- **Documentation (10%)**: README with setup instructions, architecture diagram or description.
- **Reflection (10%)**: Short write-up on challenges, automation wins, next steps.

## 9. Instructor Notes
- Offer pre-built cloud credentials in sandbox accounts or use local Docker deploy to avoid cost.
- Provide troubleshooting guide for common pipeline failures (dependency mismatches, Terraform auth).
- Encourage pair programming; assign DevOps roles (release engineer, infra engineer, QA lead) to mimic real teams.
- Collect pipeline logs for review sessions to reinforce observability mindset.

