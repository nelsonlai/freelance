output "deployment_name" {
  description = "Name of the Kubernetes deployment"
  value       = kubernetes_deployment.app.metadata[0].name
}

output "service_name" {
  description = "Name of the Kubernetes service"
  value       = kubernetes_service.app.metadata[0].name
}

output "namespace" {
  description = "Kubernetes namespace"
  value       = var.namespace
}

output "replicas" {
  description = "Number of replicas"
  value       = kubernetes_deployment.app.spec[0].replicas
}

output "image" {
  description = "Container image being used"
  value       = "${var.ecr_repository_url}:${var.image_tag}"
}


