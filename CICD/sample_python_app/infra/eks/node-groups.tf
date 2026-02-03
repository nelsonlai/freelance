# EKS Node Group
resource "aws_eks_node_group" "main" {
  cluster_name    = aws_eks_cluster.main.name
  node_group_name = "${var.cluster_name}-node-group"
  node_role_arn   = aws_iam_role.node.arn
  subnet_ids      = aws_subnet.private[*].id

  scaling_config {
    desired_size = var.node_desired_size
    max_size     = var.node_max_size
    min_size     = var.node_min_size
  }

  instance_types = [var.node_instance_type]

  # Update configuration
  update_config {
    max_unavailable = 1
  }

  # Labels for the node group
  labels = {
    role = "general"
  }

  # Taints (optional - uncomment if needed)
  # taint {
  #   key    = "dedicated"
  #   value  = "true"
  #   effect = "NO_SCHEDULE"
  # }

  depends_on = [
    aws_iam_role_policy_attachment.node_AmazonEKSWorkerNodePolicy,
    aws_iam_role_policy_attachment.node_AmazonEKS_CNI_Policy,
    aws_iam_role_policy_attachment.node_AmazonEC2ContainerRegistryReadOnly,
  ]

  tags = {
    Name = "${var.cluster_name}-node-group"
  }
}


