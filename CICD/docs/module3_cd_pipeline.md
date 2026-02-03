<!-- Module 3 – Continuous Delivery -->
# Module 3 – Continuous Delivery for Python Services

## 1. Stages of CD
1. **Artifact Promotion**: Fetch signed artifacts from CI (wheel, Docker image).
2. **Environment Provisioning**: Use IaC to create/update infrastructure.
3. **Configuration Management**: Apply env-specific settings (secrets, feature flags).
4. **Deployment Strategy**: Release to target environment using controlled rollout.
5. **Verification & Monitoring**: Run smoke tests, monitor metrics/logs, implement rollback.

Tie each stage back to automated triggers (manual approval or automated policy gate).

## 2. Deployment Strategies
- **Blue/Green**: Maintain two identical environments; shift traffic when new version passes verification.
- **Canary Releases**: Gradually expose new version to segments of users; watch metrics for anomalies.
- **Rolling Updates**: Replace instances incrementally; common in Kubernetes.
- **Feature Flags**: Decouple deployment from release; gradually enable features.
- **GitOps**: Use declarative configuration in Git to drive deployments (Argo CD, Flux).

Discuss when each approach fits (e.g., canary for user-facing apps, blue/green for critical systems).

## 3. Python Deployment Targets
- **Containers**: Docker + Kubernetes (EKS, AKS, GKE).
- **Serverless**: AWS Lambda + API Gateway, Azure Functions with Python.
- **PaaS**: Heroku, Render, Azure App Service; highlight quick start for students.
- **Hybrid**: EC2/VMs using Ansible or Fabric scripts for configuration.

Relate target choice to team skills, scaling needs, and operational constraints.

## 4. Sample Dockerfile
```dockerfile
FROM python:3.12-slim AS runtime
WORKDIR /app

ENV PYTHONUNBUFFERED=1
ENV PORT=8080

COPY requirements.txt .
RUN pip install --no-cache-dir -r requirements.txt

COPY app app

CMD ["uvicorn", "app.api:app", "--host", "0.0.0.0", "--port", "8080"]
```

Explain layering best practices, dependency caching, and runtime environment variables.

## 5. Infrastructure as Code Example (Terraform + AWS ECS Fargate)
```hcl
resource "aws_ecs_cluster" "app" {
  name = "sample-python-app"
}

resource "aws_ecs_task_definition" "app" {
  family                   = "sample-python-app"
  requires_compatibilities = ["FARGATE"]
  cpu                      = "256"
  memory                   = "512"
  network_mode             = "awsvpc"
  execution_role_arn       = aws_iam_role.ecs_execution.arn

  container_definitions = jsonencode([
    {
      name      = "api"
      image     = "123456789012.dkr.ecr.us-east-1.amazonaws.com/sample-api:${var.image_tag}"
      portMappings = [{ containerPort = 8080, hostPort = 8080 }]
      environment   = [{ name = "ENV", value = var.environment }]
    }
  ])
}
```

Highlight variable-driven promotion (`image_tag`) and environment segregation.

## 6. GitHub Actions CD Workflow (Staged Deployment)
```yaml
name: CD

on:
  workflow_run:
    workflows: ["CI"]
    types: [completed]

jobs:
  deploy:
    if: ${{ github.event.workflow_run.conclusion == 'success' }}
    runs-on: ubuntu-latest
    environment:
      name: production
      url: ${{ steps.deploy.outputs.service_url }}
    steps:
      - name: Download artifact
        uses: actions/download-artifact@v4
        with:
          name: dist-wheels
          run-id: ${{ github.event.workflow_run.id }}
      - name: Authenticate to AWS
        uses: aws-actions/configure-aws-credentials@v4
        with:
          role-to-assume: arn:aws:iam::123456789012:role/github-deploy
          aws-region: us-east-1
      - name: Build and push Docker image
        run: |
          export TAG=${{ github.sha }}
          docker build -t $ECR_REPOSITORY:$TAG .
          docker push $ECR_REPOSITORY:$TAG
      - name: Terraform apply
        run: |
          cd infra
          terraform init -input=false
          terraform apply -input=false -auto-approve \
            -var "image_tag=${{ github.sha }}" \
            -var "environment=production"
      - name: Smoke test
        id: deploy
        run: python scripts/smoke_test.py
```

Teach how to secure secrets (GitHub environments, OIDC) and require approvals before Terraform apply if desired.

## 7. Verification & Rollback
- **Automated Smoke Tests**: Hit `/healthz` endpoint post-deploy; fail pipeline on bad response.
- **Observability Hooks**: Integrate Datadog/New Relic; set SLOs and alerts.
- **Rollback Playbooks**: Maintain scripts to redeploy previous image tag (`terraform apply -var image_tag=previous`).

Encourage students to plan recovery before issues arise.

## 8. Classroom Activities
- **Lab**: Students modify deployment workflow to target a staging environment before production.
- **Scenario**: Provide failing smoke test; students triage and rollback.
- **Discussion**: Compare cost/complexity of Fargate vs serverless for small teams.

## 9. Instructor Tips
- Use diagrams (e.g., blue/green traffic switch) alongside command demonstrations.
- Stress the need for change management (approvals, audit logs) in regulated industries.
- Remind students that CD is as much about process and culture as tooling—automate everything that’s repeatable.

