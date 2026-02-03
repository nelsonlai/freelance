# PyTest 90‑Minute Workshop

This repository contains **starter** and **solutions** projects for teaching a 90‑minute PyTest class.

## Structure
- `pytest-workshop-starter/` – exercises with some tests failing or TODOs (for students to complete).
- `pytest-workshop-solutions/` – fully implemented reference solution; all tests should pass.

## Quick Start
```bash
cd pytest-workshop-starter   # or pytest-workshop-solutions
python -m venv .venv && source .venv/bin/activate  # Windows: .venv\Scripts\activate
pip install -U pip
pip install -r requirements.txt
pytest -vv
# With coverage
pytest --cov=src --cov-report=term-missing
```

## What to Teach (highlights)
- Discovery, assertions, and `pytest.raises`
- Fixtures (`tmp_path`, `monkeypatch`, `capsys`, `caplog`), scopes, teardown via `yield`
- Parametrization (including indirect)
- Markers: `skip`, `xfail`, custom markers via `pytest.ini`
- Test organization with `conftest.py`
- Mocking with `pytest-mock`
- Coverage gates with `pytest-cov`
- Debugging options: `-k`, `--lf`, `-x`, `--pdb`
- CI example: GitHub Actions workflow in `.github/workflows/tests.yml`

## Capstone
Implement `slugify(text) -> str` to pass its tests (starter has tests ready; solutions include implementation).
