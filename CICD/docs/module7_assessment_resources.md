<!-- Module 7 – Assessment & Resources -->
# Module 7 – Assessments, Labs, and Further Learning

## 1. Knowledge Check Quiz (Sample Questions)
1. **Why is Continuous Integration critical for collaboration on Python projects?**  
   - a) It eliminates the need for code reviews  
   - b) It automates dependency upgrades  
   - c) It surfaces integration issues quickly and keeps main branches deployable  
   - d) It allows developers to work without tests  
2. **Which pipeline stage is the best place to run `pip-audit` and why?**
3. **Explain the difference between blue/green deployments and canary releases.**
4. **How do feature flags support trunk-based development?**
5. **List two metrics that indicate a healthy CI pipeline and describe how to track them.**

Provide answer key and evaluation criteria (full credit requires explanation, not just letter choices).

## 2. Lab Assignments
- **Lab 1 – Build & Test Pipeline**: Students fork starter repo, add new API endpoint, extend tests, and ensure CI passes.  
  *Assessment*: Functional endpoint, tests, lint compliance, README updates.
- **Lab 2 – Containerize & Deploy**: Configure Docker image, adjust Terraform variables, run CD workflow against sandbox AWS account or local kind cluster.  
  *Assessment*: Successful deployment, smoke test evidence (logs or screenshots).
- **Lab 3 – Advanced Guardrails**: Add `pip-audit` and `ruff` caching, configure GitHub branch protection rules, simulate failure and recovery.  
  *Assessment*: Pipeline history, remediation steps documented.

Encourage peer reviews; require students to submit pipeline run URLs with lab reports.

## 3. Project Presentation Guidelines
- 10-minute demo covering pipeline flow, deployment architecture, observability hooks.
- Include failure scenario walkthrough (what happens when tests fail? when smoke test fails?).
- Reflection slide: top automation win, biggest challenge, next enhancement.

Provide rubric (clarity, technical depth, storytelling, visuals).

## 4. Additional Resources
- **Books & Guides**: *Accelerate* (Forsgren et al.), *Continuous Delivery* (Humble & Farley), *Infrastructure as Code* (Morris).  
- **Online Courses**: Google Cloud DevOps Professional, AWS CI/CD specialty modules, FastAPI documentation tutorial.  
- **Reference Docs**: GitHub Actions docs, Terraform registry, AWS ECS developer guide, OpenTelemetry Python.
- **Communities**: DevOps subreddit, CNCF Slack (#ci-cd), PySlackers DevOps channel.

Curate URLs in LMS or shared document for easy access.

## 5. Feedback & Iteration
- Collect lab retrospectives after each module (what went well, what to improve).
- Use anonymous surveys to assess pacing and tooling comfort.
- Iterate curriculum each cohort; note pipeline steps that caused friction and automate or simplify them.

## 6. Instructor Support Materials
- Slide deck outline per module (objectives, diagrams, demo cues).
- Answer key for quizzes and lab checklists.
- Troubleshooting guide: dependency conflicts, AWS credential setup, Terraform state issues, GitHub workflow debugging.

Encourage co-instructors to run through labs before class to verify instructions.

