terraform {
  required_version = ">= 1.6"
  required_providers {
    aws = {
      source  = "hashicorp/aws"
      version = "~> 5.0"
    }
  }
}

provider "aws" {
  region = var.aws_region
}

resource "aws_ecs_cluster" "app" {
  name = "sample-python-app"
}

resource "aws_ecs_task_definition" "app" {
  family                   = "sample-python-app"
  requires_compatibilities = ["FARGATE"]
  cpu                      = "256"
  memory                   = "512"
  network_mode             = "awsvpc"
  execution_role_arn       = var.execution_role_arn

  container_definitions = jsonencode([
    {
      name      = "api",
      image     = "${var.ecr_repository_url}:${var.image_tag}",
      essential = true,
      portMappings = [
        {
          containerPort = 8080,
          hostPort      = 8080,
          protocol      = "tcp"
        }
      ],
      environment = [
        {
          name  = "ENV",
          value = var.environment
        }
      ]
    }
  ])
}

resource "aws_ecs_service" "app" {
  name            = "sample-python-app"
  cluster         = aws_ecs_cluster.app.id
  task_definition = aws_ecs_task_definition.app.arn
  desired_count   = 1
  launch_type     = "FARGATE"

  network_configuration {
    security_groups  = [var.security_group_id]
    subnets          = var.subnet_ids
    assign_public_ip = true
  }

  lifecycle {
    ignore_changes = [task_definition]
  }
}

