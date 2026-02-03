<!-- Module 1 – Foundations -->
# Module 1 – Foundations: Why CI/CD Matters

## 1. Motivation: Delivery Pain Points
Software teams often struggle with:
- Manual builds and deployments that are error prone and time consuming.
- Long feedback cycles that delay bug discovery and increase integration risk.
- Inconsistent environments causing “works on my machine” failures.
- Limited visibility into release readiness and change impact.
- Difficulty scaling release frequency without sacrificing quality.

Highlight real situations—late-night release crunches, broken production hotfixes, untested merges—to ground the conversation before introducing CI/CD.

## 2. Goals of CI/CD
- **Continuous Integration (CI)**: frequently merge code into a shared branch, run automated checks immediately, and keep the mainline in a deployable state.
- **Continuous Delivery (CD)**: automate packaging, environment provisioning, and release orchestration so any validated build can be deployed on demand.
- **Continuous Deployment**: push every passing build to production automatically, with guardrails and observability.

Discuss how incremental, automated workflows reduce risk (smaller changes), shorten lead time, and improve developer confidence.

## 3. Key Concepts and Vocabulary
- **Pipeline**: automated sequence of stages (lint, test, build, deploy).
- **Artifacts**: build outputs (wheel files, Docker images) promoted across environments.
- **Stages & Gates**: quality checks controlling progression (e.g., unit tests, manual approval).
- **Infrastructure as Code (IaC)**: declarative environment provisioning (Terraform, AWS CDK).
- **Shift Left**: moving testing/security earlier in the lifecycle.

Include a visual diagram during instruction showing commit ➜ CI checks ➜ artifact ➜ CD release.

## 4. Metrics for Success
- Lead time for changes (commit to production).
- Deployment frequency.
- Change failure rate (production incidents per release).
- Mean time to recovery (MTTR).
- Pipeline health (pass/fail trends, flaky tests).

Relate metrics to DORA benchmarks and explain their business impact.

## 5. Python Ecosystem Context
- Python’s dynamic typing and rich package ecosystem amplify the need for automated linting (`flake8`, `ruff`) and testing (`pytest`).
- Packaging standards (`pyproject.toml`, wheels) and virtual environments (venv, `pipenv`, `poetry`) align naturally with CI automation.
- Popular Python deployment targets: serverless (AWS Lambda), containerized apps (Docker + Kubernetes), PaaS (Heroku, Azure App Service).

## 6. Classroom Activities
- **Discussion**: Students share personal or hypothetical release pain points; map each challenge to a CI/CD practice.
- **Case Study**: Review a pre/post CI/CD scenario (e.g., Etsy, Netflix) and analyze improvements.
- **Exercise**: Identify manual steps in a sample workflow and brainstorm automation opportunities.

## 7. Instructor Notes
- Start with outcomes (faster delivery, higher confidence) before tools.
- Use a whiteboard timeline comparing manual vs automated release cycles.
- Emphasize cultural aspects: collaboration, shared ownership, automated quality gates.
- Bridge to Module 2 by previewing how modern CI tools operationalize these goals.

