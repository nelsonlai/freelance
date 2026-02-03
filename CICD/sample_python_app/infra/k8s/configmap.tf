# ConfigMap for application configuration
resource "kubernetes_config_map" "app" {
  metadata {
    name      = "${var.app_name}-config"
    namespace = var.namespace
    labels = {
      app = var.app_name
    }
  }

  data = {
    environment = var.environment
    log_level   = var.log_level
    api_timeout = tostring(var.api_timeout)
  }
}


