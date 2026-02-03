<!-- Module 11 – Jenkins Pipelines -->
# Module 11 – Jenkins for Enterprise CI/CD

## 1. Teaching Objectives
- Explain Jenkins architecture, master/agent model, and plugin ecosystem.
- Author declarative and scripted pipelines for Python projects.
- Manage Jenkins credentials, shared libraries, and folder-based multibranch jobs.
- Operate Jenkins securely with pipelines-as-code best practices.

## 2. Architecture Overview
- **Controller (formerly Master)**: Orchestrates jobs, hosts web UI, manages plugins.
- **Agents**: Execute builds; can be static (VMs) or ephemeral (Kubernetes Pod templates).
- **Plugins**: Extend functionality (Git, Pipeline, Blue Ocean, Credentials Binding).
- **Jobs**: Freestyle vs Pipeline vs Multibranch; emphasize pipeline-as-code with `Jenkinsfile`.

Draw architecture with SCM triggers → Jenkins controller → agent nodes → artifact registry.

## 3. Declarative Pipeline Template for Python
```groovy
pipeline {
  agent any
  environment {
    PYTHON = 'python3.11'
  }
  options {
    timestamps()
    ansiColor('xterm')
  }
  stages {
    stage('Checkout') {
      steps {
        checkout scm
      }
    }
    stage('Setup') {
      steps {
        sh '''
          python -m venv .venv
          . .venv/bin/activate
          pip install --upgrade pip
          pip install -r requirements.txt -r requirements-dev.txt
        '''
      }
    }
    stage('Lint & Test') {
      steps {
        sh '. .venv/bin/activate && tox -e lint,py311'
      }
    }
    stage('Build Artifact') {
      steps {
        sh '. .venv/bin/activate && python -m build'
        archiveArtifacts artifacts: 'dist/*.whl', fingerprint: true
      }
    }
    stage('Docker Build') {
      when { branch 'main' }
      steps {
        sh '''
          docker build -t registry.example.com/sample-api:${GIT_COMMIT} .
          docker push registry.example.com/sample-api:${GIT_COMMIT}
        '''
      }
    }
  }
  post {
    always {
      junit 'reports/**/*.xml'
      cleanWs()
    }
    failure {
      mail to: 'dev-team@example.com', subject: "Pipeline failed ${env.BUILD_TAG}", body: "Investigate ${env.BUILD_URL}"
    }
  }
}
```

Break down stages, environment setup, artifact archiving, post conditions, and email notifications.

## 4. Multibranch & Shared Libraries
- **Multibranch Pipelines**: Auto-discover branches/PRs; use branch indexing; integrate with Bitbucket/GitHub.
- **Shared Libraries**: DRY pipeline logic; define global steps (e.g., `pyLintTestBuild()`) in `vars/`.
- **Folder Credentials**: Scope secrets per team; use credential IDs in pipelines.

Provide example `@Library('python-ci') _` usage and library structure.

## 5. Jenkins with Kubernetes
- Use Kubernetes plugin for ephemeral agents; define Pod template with Python + Docker.
- Manage docker-in-docker vs kaniko for builds; highlight security considerations.
- Deploy with `kubectl` or Helm from pipeline; set service accounts and RBAC.

Tie back to Module 9 for Kubernetes deployments.

## 6. Security & Maintenance
- Keep controller updated; manage plugin versions carefully.
- Enforce Role-Based Access Control (Matrix Authorization, Folders).
- Use credentials binding rather than plaintext; rotate secrets.
- Harden Jenkins: disable script security bypasses, restrict script approvals, use OIDC/SSO.

Discuss auditing builds and using `Configuration as Code` (JCasC) for reproducible setups.

## 7. Classroom Labs
- **Pipeline Authoring**: Students write Jenkinsfile replicating GitHub Actions workflow.
- **Shared Library Workshop**: Extract common steps into shared library; consume in pipeline.
- **Agent Provisioning**: Configure Docker agent on local VM; run pipeline using label selectors.
- **Blue Ocean Visualization**: Install Blue Ocean, explore pipeline visualization.

## 8. Instructor Notes
- Offer ready-to-run Jenkins Docker Compose stack for labs.
- Preload required plugins to save time; provide plugin list YAML (JCasC).
- Encourage students to migrate from Freestyle Jobs to Pipelines to experience pipeline-as-code benefits.
- Highlight operational overhead and when a managed CI platform may be preferable.

