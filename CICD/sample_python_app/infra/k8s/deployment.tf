# Kubernetes Deployment
resource "kubernetes_deployment" "app" {
  metadata {
    name      = var.app_name
    namespace = var.namespace
    labels = {
      app = var.app_name
    }
  }

  spec {
    replicas = var.replicas

    selector {
      match_labels = {
        app = var.app_name
      }
    }

    strategy {
      type = "RollingUpdate"
      rolling_update {
        max_surge       = 1
        max_unavailable = 0
      }
    }

    template {
      metadata {
        labels = {
          app     = var.app_name
          version = var.image_tag
        }
      }

      spec {
        container {
          name  = "api"
          image = "${var.ecr_repository_url}:${var.image_tag}"

          port {
            container_port = 8080
            name           = "http"
            protocol      = "TCP"
          }

          env {
            name  = "ENV"
            value = var.environment
          }

          env {
            name  = "PORT"
            value = "8080"
          }

          env_from {
            config_map_ref {
              name = kubernetes_config_map.app.metadata[0].name
            }
          }

          resources {
            requests = {
              cpu    = var.cpu_request
              memory = var.memory_request
            }
            limits = {
              cpu    = var.cpu_limit
              memory = var.memory_limit
            }
          }

          liveness_probe {
            http_get {
              path = "/healthz"
              port = 8080
            }
            initial_delay_seconds = var.liveness_initial_delay
            period_seconds        = var.liveness_period
            timeout_seconds      = var.liveness_timeout
            failure_threshold    = var.liveness_failure_threshold
          }

          readiness_probe {
            http_get {
              path = "/healthz"
              port = 8080
            }
            initial_delay_seconds = var.readiness_initial_delay
            period_seconds        = var.readiness_period
            timeout_seconds       = var.readiness_timeout
            failure_threshold     = var.readiness_failure_threshold
          }
        }
      }
    }
  }
}


