<!-- Module 10 – GitHub Actions -->
# Module 10 – GitHub Actions Deep Dive

## 1. Teaching Objectives
- Understand GitHub Actions architecture (events, workflows, jobs, runners).
- Build reusable workflow templates for Python CI/CD.
- Leverage Actions marketplace, caching, and matrix strategies for efficient pipelines.
- Apply security best practices (OIDC, least privilege, secret management).

## 2. Core Concepts
- **Events**: `push`, `pull_request`, `workflow_dispatch`, `workflow_run`.
- **Workflow**: YAML file under `.github/workflows/` describing jobs and steps.
- **Jobs & Steps**: Jobs run on runners; steps execute actions or shell commands.
- **Runners**: Hosted Ubuntu/Windows/macOS or self-hosted; note concurrency limits.
- **Artifacts & Caching**: `actions/upload-artifact`, `actions/cache`.

Illustrate workflow lifecycle with diagram: trigger ➜ job matrix ➜ artifacts ➜ downstream workflow.

## 3. Python Workflow Patterns
- **Smoke Test**: `tox` matrix across Python versions, fail-fast strategy.
- **Container Build**: `docker/login-action`, `docker/build-push-action` for image publishing.
- **IaC Deployment**: GitHub OIDC + Terraform apply gates.
- **Reusable Workflows**: Centralize lint/test logic with `workflow_call`.
- **Environment Promotion**: Use `environments` with reviewers and secrets per stage.

Discuss caching pip dependencies (`actions/setup-python` cache), using `uv` or `poetry`.

## 4. Hands-on Labs
1. **Workflow Basics**: Students create `ci.yml` triggered on PR; run `pytest`.
2. **Matrix Expansion**: Add `os` + `python-version` matrix; explore fail-fast and strategy settings.
3. **Reusable Workflow**: Extract lint/test job into `.github/workflows/python-ci.yml`; call from multiple repositories.
4. **Secrets & OIDC**: Configure AWS role assumption with `configure-aws-credentials`; test CD workflow to staging.
5. **Deploy Preview**: Use `actions/deploy-pages` or ephemeral environment workflow; tear down on PR close.

Encourage peer review of workflows; highlight common YAML pitfalls.

## 5. Security & Governance
- Use organization-level policies and workflow approvals.
- Restrict `GITHUB_TOKEN` permissions; disable unneeded scopes.
- Require branches to use specific workflows (branch protection).
- Monitor for malicious PRs (third-party contributions) by using `pull_request_target` carefully.

## 6. Observability & Debugging
- Enable step summary reports; use `actions/upload-artifact` for logs on failure.
- Leverage workflow run logs, `gh run watch`, and `act` for local testing.
- Track workflow metrics with GitHub Insights or export via API to dashboards.

## 7. Classroom Activities
- **Marketplace Review**: Students pick 3 useful Python-related actions, evaluate pros/cons.
- **Incident Simulation**: Break a workflow (e.g., expired secret), triage and fix.
- **Cost Calculation**: Estimate minutes consumed for sample project; discuss billing tiers.

## 8. Instructor Notes
- Provide GitHub Classroom template repo linking to provided sample project.
- Use `gh` CLI demos for managing workflows (`gh workflow run`, `gh workflow view`).
- Encourage best practice of testing actions locally with `nektos/act` where feasible.

