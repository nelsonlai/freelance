<!-- Module 2 – Continuous Integration -->
# Module 2 – Designing a Python CI Pipeline

## 1. CI Stage Overview
1. **Source Control Trigger**: Every push or pull request starts the pipeline.
2. **Environment Setup**: Create isolated Python environment, install dependencies.
3. **Static Analysis / Formatting**: Run `ruff` or `flake8`, `black`, and `isort`.
4. **Unit & Integration Tests**: Execute `pytest` (with coverage reporting).
5. **Build Artifacts**: Package Python code into wheels/containers.
6. **Report & Feedback**: Publish results (badges, PR annotations) and block merges on failures.

Illustrate each stage with a swimlane diagram showing automated progression and feedback loops to developers.

## 2. Python Tooling Stack
- **Environment**: `pyenv`, `venv`, or `tox` to guarantee reproducible runs.
- **Linting**: `ruff`, `flake8`, `pylint` catch style and bug risks.
- **Formatting**: `black` ensures consistent code style.
- **Type Checking**: `mypy` enforces type annotations, helpful for large teams.
- **Testing**: `pytest` with plugins (`pytest-cov`, `pytest-xdist` for parallelism).
- **Packaging**: `build` or `poetry build` create wheel/sdist artifacts.
- **Security**: `bandit`, `pip-audit` and dependency pinning via `pip-tools`.

Compare alternatives (e.g., `nox` vs `tox`) and discuss when each fits.

## 3. Sample Repository Structure
```
sample_python_app/
├── app/
│   ├── __init__.py
│   └── api.py
├── tests/
│   └── test_api.py
├── pyproject.toml
├── tox.ini
├── requirements.txt
└── .github/workflows/ci.yml
```

Discuss how separating `app` and `tests` encourages modular design; `pyproject.toml` centralizes metadata.

## 4. Example: `pyproject.toml`
```toml
[build-system]
requires = ["setuptools>=64", "wheel"]
build-backend = "setuptools.build_meta"

[project]
name = "sample-python-app"
version = "0.1.0"
description = "Teaching app for CI/CD workflows"
requires-python = ">=3.11"
dependencies = [
  "fastapi",
  "uvicorn",
]

[tool.black]
line-length = 88

[tool.pytest.ini_options]
minversion = "7.0"
addopts = "-ra -q --cov=app --cov-report=xml"
testpaths = ["tests"]
```

Walk through how metadata powers packaging, while tool sections encode CI defaults.

## 5. Example: `tox.ini`
```ini
[tox]
envlist = lint,py311
isolated_build = true

[testenv]
deps = -r requirements.txt
commands =
  pytest

[testenv:lint]
deps =
  ruff
  black
  mypy
commands =
  ruff check app tests
  black --check app tests
  mypy app
```

Explain how `tox` orchestrates multiple environments locally and in CI, providing parity with developer workflows.

## 6. Example: GitHub Actions CI Workflow
```yaml
name: CI

on:
  pull_request:
  push:
    branches: [ main ]

jobs:
  lint-test-build:
    runs-on: ubuntu-latest
    strategy:
      matrix:
        python-version: ["3.11", "3.12"]
    steps:
      - uses: actions/checkout@v4
      - uses: actions/setup-python@v5
        with:
          python-version: ${{ matrix.python-version }}
          cache: "pip"
      - name: Install dependencies
        run: |
          python -m pip install --upgrade pip
          pip install -r requirements.txt
          pip install -r requirements-dev.txt
      - name: Static analysis
        run: tox -e lint
      - name: Test suite
        run: tox -e py311
      - name: Build artifacts
        run: python -m build
      - name: Upload wheel
        uses: actions/upload-artifact@v4
        with:
          name: dist-wheels
          path: dist/*.whl
```

Break down each step, emphasizing caching and matrix builds for compatibility.

## 7. Metrics and Observability in CI
- Track build duration and queue time to spot scaling issues.
- Monitor flaky test rate; quarantine or fix quickly.
- Surface coverage trends and lint violations to dashboards.
- Integrate PR annotations (GitHub checks, Reviewdog, Danger) for faster feedback.

## 8. Classroom Exercises
- **Lab**: Students fork the sample repo, add a failing test, observe pipeline failure, then fix.
- **Challenge**: Configure caching in GitHub Actions to speed up dependency installs.
- **Extension**: Add `pip-audit` to the pipeline and remediate a vulnerable dependency.

## 9. Instructor Tips
- Demonstrate failing vs passing run screens via recorded demo if live pipeline isn’t available.
- Reinforce best practice of keeping pipelines under 10 minutes for fast feedback.
- Encourage students to run `tox` locally before pushing to mimic CI behavior.

