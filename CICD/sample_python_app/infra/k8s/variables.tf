variable "aws_region" {
  description = "AWS region"
  type        = string
  default     = "us-east-1"
}

variable "cluster_name" {
  description = "Name of the EKS cluster"
  type        = string
}

variable "namespace" {
  description = "Kubernetes namespace for the application"
  type        = string
  default     = "default"
}

variable "app_name" {
  description = "Name of the application"
  type        = string
  default     = "sample-python-app"
}

variable "ecr_repository_url" {
  description = "ECR repository URL (without tag)"
  type        = string
}

variable "image_tag" {
  description = "Docker image tag to deploy"
  type        = string
}

variable "replicas" {
  description = "Number of replicas"
  type        = number
  default     = 2
}

variable "environment" {
  description = "Environment name (e.g., staging, production)"
  type        = string
  default     = "production"
}

variable "log_level" {
  description = "Log level for the application"
  type        = string
  default     = "info"
}

variable "api_timeout" {
  description = "API timeout in seconds"
  type        = number
  default     = 30
}

variable "service_type" {
  description = "Kubernetes service type (ClusterIP, NodePort, LoadBalancer)"
  type        = string
  default     = "LoadBalancer"
}

variable "cpu_request" {
  description = "CPU request for containers"
  type        = string
  default     = "250m"
}

variable "memory_request" {
  description = "Memory request for containers"
  type        = string
  default     = "256Mi"
}

variable "cpu_limit" {
  description = "CPU limit for containers"
  type        = string
  default     = "500m"
}

variable "memory_limit" {
  description = "Memory limit for containers"
  type        = string
  default     = "512Mi"
}

variable "liveness_initial_delay" {
  description = "Initial delay for liveness probe in seconds"
  type        = number
  default     = 30
}

variable "liveness_period" {
  description = "Period for liveness probe in seconds"
  type        = number
  default     = 10
}

variable "liveness_timeout" {
  description = "Timeout for liveness probe in seconds"
  type        = number
  default     = 5
}

variable "liveness_failure_threshold" {
  description = "Failure threshold for liveness probe"
  type        = number
  default     = 3
}

variable "readiness_initial_delay" {
  description = "Initial delay for readiness probe in seconds"
  type        = number
  default     = 5
}

variable "readiness_period" {
  description = "Period for readiness probe in seconds"
  type        = number
  default     = 5
}

variable "readiness_timeout" {
  description = "Timeout for readiness probe in seconds"
  type        = number
  default     = 3
}

variable "readiness_failure_threshold" {
  description = "Failure threshold for readiness probe"
  type        = number
  default     = 3
}


