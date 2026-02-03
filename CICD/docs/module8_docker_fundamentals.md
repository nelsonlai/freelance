<!-- Module 8 – Docker Foundations -->
# Module 8 – Docker for CI/CD Practitioners

## 1. Teaching Objectives
- Explain container fundamentals and why Docker matters in CI/CD.
- Build, tag, scan, and publish container images for Python services.
- Optimize Dockerfiles for reproducibility, security, and performance.
- Integrate container workflows into existing pipelines.

## 2. Key Concepts
- **Containers vs Virtual Machines**: Share host kernel; lightweight, fast startup; ideal for ephemeral CI jobs.
- **Image Layers**: Read-only stack; caching implications for build speed.
- **Registry**: Remote store (Docker Hub, Amazon ECR, GitHub Container Registry) for pushing/pulling images.
- **Runtime Configuration**: Environment variables, mounted volumes, health checks.

Use diagrams to show Docker client ↔ daemon ↔ registry interactions and layer caching.

## 3. Python-centric Docker Patterns
- Base images: `python:3.12-slim`, `tiangolo/uvicorn-gunicorn-fastapi`.
- Multi-stage builds to separate dependencies, tests, and runtime artifacts.
- Non-root user creation for runtime security (`USER app`).
- Handling dependencies: `pip install --no-cache-dir`, pinned versions.
- Removing build tools to shrink image size; using `.dockerignore`.

Discuss trade-offs between slim images vs full `python` base for compiled dependencies.

## 4. Lab Sequence
1. **Build Basics**: Create Dockerfile for `sample_python_app`, run `docker build`, launch container locally.
2. **Improve Dockerfile**: Add multi-stage build, use `--mount=type=cache` for pip cache.
3. **Security Scan**: Run `docker scout cves` or `trivy image` to identify vulnerabilities; remediate by updating base image.
4. **Publish to Registry**: Tag image (`docker tag sample-api:latest ghcr.io/org/sample-api:0.1.0`) and push.
5. **Automate Builds**: Extend CI workflow to build image on pull requests, run containerized integration tests.

## 5. Advanced Topics
- **Docker Compose**: Define multi-service dev environments; map Compose to Kubernetes manifests.
- **BuildKit Optimizations**: Parallel builds, inline cache export/import, secret mounts for private dependencies.
- **Immutable Tags vs Rolling Tags**: Use digest pinning in CD to guarantee reproducibility.
- **Image Signing**: Use `cosign` to sign and verify container images before deployment.

## 6. Classroom Activities
- **Layer Analysis**: Use `dive` to inspect image layers and identify bloat.
- **Best Practice Review**: Students critique example Dockerfiles, suggest improvements.
- **Infra Cost Exercise**: Compare container resource usage vs VMs for the sample app.

## 7. Instructor Notes
- Provide pre-built images for students lacking Docker Desktop (use Play with Docker or Codespaces).
- Encourage frequent `docker system prune` to manage disk usage in labs.
- Tie Docker concepts back to Module 3 CD pipeline and Module 5 project to reinforce integration.

