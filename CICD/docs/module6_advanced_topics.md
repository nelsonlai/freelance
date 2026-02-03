<!-- Module 6 – Advanced Topics -->
# Module 6 – Advanced CI/CD Practices

## 1. Branching & Release Strategies
- **Trunk-based Development**: Short-lived feature branches, feature flags to decouple release from deploy.
- **GitFlow Variants**: Long-lived develop/release branches for regulated environments; highlight overhead and merge complexity.
- **Release Trains**: Fixed cadence deployments that aggregate changes while keeping pipelines green.

Guide students to align branching strategy with team size, compliance requirements, and deployment frequency goals.

## 2. Quality & Security Enhancements
- **Static Application Security Testing (SAST)**: Integrate tools like CodeQL, Bandit, or Semgrep into CI.
- **Dependency Scanning**: Use `pip-audit`, Snyk, or Dependabot to catch vulnerable packages.
- **Secret Scanning**: Employ Gitleaks or GitGuardian; enforce pre-commit hooks.
- **Policy as Code**: Validate infrastructure changes with Open Policy Agent (OPA) or Conftest.

Demonstrate failing builds when security policies are violated and discuss exception handling.

## 3. Progressive Delivery Techniques
- **Feature Flags**: Services like LaunchDarkly or open-source Unleash; Python SDK usage patterns.
- **A/B Testing**: Route traffic to different versions; collect metrics for data-driven rollouts.
- **Automated Rollbacks**: Use health checks + canary analysis (Kayenta) to trigger rollback on degradation.

Encourage building guardrails before enabling automatic production deployments.

## 4. Observability & Feedback Loops
- **Metrics Pipelines**: Emit deployment markers (timestamp, version) to time-series databases.
- **Structured Logging**: Use JSON logging (`structlog`) and correlation IDs; ship to ELK or CloudWatch.
- **Tracing**: Instrument FastAPI with OpenTelemetry; propagate trace IDs through async calls.

Tie observability to SRE practices (SLI/SLO/SLA) and incident response.

## 5. Compliance and Governance
- **Audit Trails**: Retain pipeline logs, artifact signatures, and approval records.
- **Change Management**: Integrate with ITSM tools (ServiceNow, Jira Service Management).
- **Access Controls**: Enforce least privilege on runners, artifact stores, and cloud credentials.

Discuss how automation supports regulatory requirements (SOC 2, HIPAA, GDPR).

## 6. Scaling Pipelines
- **Pipeline as Code Reuse**: Composite actions, Jenkins shared libraries, GitLab includes.
- **Caching & Parallelism**: Use build caches, artifact reuse, and test splitting to keep feedback fast.
- **Self-hosted Runners**: Autoscale via Kubernetes (actions-runner-controller) for CPU/GPU workloads.

Encourage monitoring pipeline metrics to inform when to optimize.

## 7. Classroom Activities
- **Security Drill**: Introduce a vulnerable dependency; students configure `pip-audit` and remediate.
- **Feature Flag Lab**: Wrap new feature behind flag and roll out gradually.
- **Observability Workshop**: Instrument API with OpenTelemetry, visualize traces in Jaeger sandbox.

## 8. Instructor Notes
- Start with one advanced topic per cohort to avoid overwhelm.
- Provide decision matrices to help teams choose which advanced practices to adopt first.
- Reinforce that maturity is iterative—encourage teams to “automate the pain” they experience most.

