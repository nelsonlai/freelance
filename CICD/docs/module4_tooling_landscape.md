<!-- Module 4 – Tooling Landscape -->
# Module 4 – CI/CD Tooling Landscape and Stack Options

## 1. CI/CD Platform Comparison
| Platform | Model | Strengths | Considerations | Python Notes |
| --- | --- | --- | --- | --- |
| GitHub Actions | SaaS, event-driven workflows | Native GitHub integration, reusable actions, generous community marketplace | Limited self-hosted runner autoscaling; YAML complexity grows | First-class Python setup action, simple matrix builds |
| GitLab CI/CD | SaaS/Self-hosted | Built-in DevOps lifecycle (SCM, CI, CD), Auto DevOps, strong role controls | Runner management required for advanced setups | Python templates, integrated package registry |
| Jenkins | Self-hosted | Highly extensible, plugin ecosystem, pipeline-as-code (Jenkinsfile) | Requires ops overhead, plugin maintenance, less opinionated | Use `pipeline` DSL, integrates with Python virtualenvs |
| CircleCI | SaaS | Fast parallelism, orbs for reusable config, insights dashboards | Pricing tied to compute; relies on orbs for complex logic | Prebuilt Python images, simple caching primitives |
| Azure DevOps Pipelines | SaaS/Hybrid | Enterprise governance, multi-stage pipelines, deep Azure integration | UI can be complex, YAML schema verbose | Hosted agents include Python runtimes, ties to Azure App Service |

Encourage students to evaluate tools by repository hosting, compliance needs, budget, and familiarity.

## 2. Artifact & Package Management
- **Registries**: GitHub Packages, AWS ECR, Azure Container Registry, Artifactory.
- **Python Package Indexing**: Private PyPI via Nexus/Artifactory, `pypiserver`.
- **Binary Storage**: S3/GCS buckets for models or large artifacts.

Discuss retention policies, immutability, and promotion workflows (dev ➜ staging ➜ prod).

## 3. Infrastructure & Configuration Tools
- **IaC**: Terraform, Pulumi (multi-cloud), AWS CloudFormation, Azure Bicep.
- **Configuration**: Ansible, Chef, Salt for VM-based workloads.
- **Container Orchestration**: Kubernetes (EKS/AKS/GKE), AWS ECS, HashiCorp Nomad.
- **Secret Management**: HashiCorp Vault, AWS Secrets Manager, Azure Key Vault, Doppler.

Highlight Python SDKs/CLIs (e.g., `boto3`, `pulumi`, `azure-cli`) to embed infrastructure steps in pipelines.

## 4. Observability & Quality Tooling
- **Monitoring**: Prometheus + Grafana, Datadog, New Relic.
- **Logging**: ELK/Opensearch stack, Splunk, AWS CloudWatch.
- **Tracing**: OpenTelemetry, Jaeger, Honeycomb.
- **Quality Gates**: SonarQube (Python code smell detection), Snyk or GitHub Advanced Security for dependency scanning.

Stress the need to integrate alerts (Slack, Teams) with deployment pipelines.

## 5. Recommended Teaching Stacks
1. **Beginner-friendly (All SaaS)**  
   - Repo: GitHub  
   - CI/CD: GitHub Actions  
   - Deploy: Render or Railway (Docker)  
   - Observability: Render dashboard + Sentry
2. **Cloud-native (AWS-centric)**  
   - CI: GitHub Actions or CodeBuild  
   - CD: AWS CodeDeploy + ECS Fargate  
   - IaC: Terraform  
   - Monitoring: CloudWatch + Datadog
3. **Self-managed**  
   - SCM: GitLab self-hosted  
   - CI/CD: GitLab runners or Jenkins  
   - Deploy: Kubernetes on-prem (Argo CD GitOps)  
   - Observability: Prometheus + Grafana

Provide rationale (cost, control, learning objectives) for each stack to help instructors tailor exercises.

## 6. Classroom Activity Ideas
- **Tool Selection Workshop**: Students evaluate a hypothetical company profile and pick a stack, justifying trade-offs.
- **Marketplace Exploration**: Assign teams to find useful GitHub Actions/CircleCI orbs for Python tasks and present findings.
- **Cost Estimation Exercise**: Roughly estimate monthly cost differences between SaaS and self-hosted setups.

## 7. Instructor Notes
- Keep discussions grounded in capabilities rather than exhaustive feature lists.
- Encourage students to consider compliance and data residency constraints early.
- Remind learners that tooling evolves quickly—focus on concepts like pipelines, artifacts, policy gates, and observability integrations.

