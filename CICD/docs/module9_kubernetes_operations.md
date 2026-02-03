<!-- Module 9 – Kubernetes Operations -->
# Module 9 – Kubernetes for CI/CD Pipelines

## 1. Teaching Objectives
- Introduce Kubernetes architecture and why teams deploy to it.
- Deploy Python workloads to Kubernetes using manifests and Helm.
- Automate Kubernetes delivery in CI/CD pipelines with GitOps patterns.
- Monitor, troubleshoot, and scale containerized services.

## 2. Cluster Building Blocks
- **Control Plane Components**: API server, etcd, scheduler, controller manager; managed by providers in EKS/AKS/GKE.
- **Worker Nodes**: Kubelet, container runtime (containerd), kube-proxy.
- **Pods**: Smallest deployable unit; one or more containers with shared networking/storage.
- **ReplicaSets & Deployments**: Replica management and rolling updates.
- **Services**: Expose pods (ClusterIP, NodePort, LoadBalancer).
- **ConfigMaps & Secrets**: Externalize configuration.

Use architecture diagrams to show API interactions and label components.

## 3. Deploying the Sample Python App
1. Create Kubernetes manifests (`deployment.yaml`, `service.yaml`) pointing to container image from Module 8.
2. Apply manifests locally via `kind` or `minikube`.
3. Expose service using LoadBalancer (cloud) or `kubectl port-forward` (local).
4. Verify `/healthz` endpoint using `kubectl exec` or HTTP client.

Provide baseline manifest:
```yaml
apiVersion: apps/v1
kind: Deployment
metadata:
  name: sample-api
spec:
  replicas: 2
  selector:
    matchLabels:
      app: sample-api
  template:
    metadata:
      labels:
        app: sample-api
    spec:
      containers:
        - name: api
          image: ghcr.io/org/sample-api:0.1.0
          ports:
            - containerPort: 8080
          env:
            - name: ENV
              value: production
---
apiVersion: v1
kind: Service
metadata:
  name: sample-api
spec:
  type: ClusterIP
  selector:
    app: sample-api
  ports:
    - port: 80
      targetPort: 8080
```

## 4. Scaling & Resilience
- **Horizontal Pod Autoscaler (HPA)**: Scale pods based on CPU/memory/custom metrics.
- **Liveness/Readiness Probes**: Tie to FastAPI `/healthz`; prevent traffic to unready pods.
- **Rolling vs Blue/Green**: Understand Deployment rollout strategies; use `kubectl rollout status`.
- **Stateful Workloads**: Brief overview (StatefulSets, PersistentVolumes) even if project is stateless.

Have students experiment with `kubectl scale` and simulate failures.

## 5. CI/CD Integration Patterns
- **Kubectl Apply in CD**: Simple approach; requires cluster credentials and RBAC.
- **Helm Charts**: Package and templatize Kubernetes resources; store charts in OCI registries.
- **GitOps**: Argo CD or Flux monitors Git repo and syncs desired state; integrate with Terraform for cluster bootstrap.
- **Namespace Promotion**: Use separate namespaces (`dev`, `staging`, `prod`) with policy gates.

Discuss RBAC and service account management for GitHub Actions workloads.

## 6. Observability
- **Logging**: Fluent Bit/Fluentd to ELK or CloudWatch, structured JSON logging from FastAPI.
- **Metrics**: Prometheus scraping, Grafana dashboards; track request latency, error rates.
- **Tracing**: OpenTelemetry Collector, Jaeger/Tempo; propagate trace IDs.
- **Alerting**: Configure alerts for error spikes or failed rollouts; integrate with Slack/Teams.

Tie back to Module 6 advanced observability practices.

## 7. Classroom Activities
- **Hands-on Deploy**: Students deploy to local kind cluster, inspect pods/services, fix common errors.
- **Helm Template Lab**: Convert raw manifests into Helm chart; customize values per environment.
- **GitOps Simulation**: Use Argo CD in sandbox; demonstrate automatic rollback on drift.

## 8. Instructor Notes
- Offer managed cluster alternatives (e.g., Play with Kubernetes) if students lack local resources.
- Provide RBAC presets and kubeconfig templates to avoid setup delays.
- Emphasize security best practices (network policies, PodSecurityContexts) as future learning paths.
- Connect Kubernetes release strategies back to CI/CD metrics and DORA benchmarks.

