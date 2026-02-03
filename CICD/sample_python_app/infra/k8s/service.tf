# Kubernetes Service
resource "kubernetes_service" "app" {
  metadata {
    name      = var.app_name
    namespace = var.namespace
    labels = {
      app = var.app_name
    }
  }

  spec {
    type = var.service_type

    selector = {
      app = var.app_name
    }

    port {
      port        = 80
      target_port = 8080
      protocol    = "TCP"
      name        = "http"
    }
  }
}


