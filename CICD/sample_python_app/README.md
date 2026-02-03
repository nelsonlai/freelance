# Sample Python CI/CD Application

This repository accompanies the Python CI/CD teaching curriculum. It provides a FastAPI service and end-to-end automation examples covering linting, testing, packaging, containerization, and deployment.

## Getting Started
```bash
python -m venv .venv
source .venv/bin/activate
pip install -r requirements.txt -r requirements-dev.txt
uvicorn app.api:app --reload
```

Visit `http://127.0.0.1:8000/healthz` to verify the service is running.

## Quality Gates
- `tox -e lint` runs Ruff, Black, and MyPy.
- `tox -e py311` executes pytest with coverage.
- `python -m build` packages the project into a wheel.

## CI Pipeline
The `.github/workflows/ci.yml` workflow performs:
1. Dependency installation with caching.
2. Linting and type checks via `tox -e lint`.
3. Test execution via `tox -e py311`.
4. Wheel build and artifact upload.

## CD Pipeline
The `.github/workflows/cd.yml` workflow listens for successful CI runs and then:
1. Builds a Docker image and pushes it to Amazon ECR.
2. Applies Terraform to update the ECS service.
3. Runs `scripts/smoke_test.py` against the deployed service.

Configure GitHub environment secrets for AWS credentials, `SERVICE_URL`, and Terraform state backend before enabling CD.

## Infrastructure
Terraform templates in `infra/` describe a simplified ECS Fargate deployment. Replace placeholder values (role ARNs, subnet IDs) with your lab environment specifics.

## Extending the Lab
- Add staging environment with manual approval and environment-specific variables.
- Integrate `pip-audit` into the CI workflow.
- Publish observability data (deployment metadata, metrics) to an external service.

