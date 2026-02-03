variable "aws_region" {
  description = "AWS region for ECS resources."
  type        = string
  default     = "us-east-1"
}

variable "ecr_repository_url" {
  description = "ECR repository URI hosting the Docker image."
  type        = string
}

variable "image_tag" {
  description = "Docker image tag to deploy."
  type        = string
}

variable "environment" {
  description = "Deployment environment (e.g., staging, production)."
  type        = string
  default     = "staging"
}

variable "execution_role_arn" {
  description = "IAM role ARN used by ECS tasks for execution."
  type        = string
}

variable "security_group_id" {
  description = "Security group assigned to ECS tasks."
  type        = string
}

variable "subnet_ids" {
  description = "Subnets for ECS service networking."
  type        = list(string)
}

