import pytest
from src.text_utils import slugify

@pytest.mark.parametrize("inp,expected", [
    ("Hello World", "hello-world"),
    ("  multiple   spaces  ", "multiple-spaces"),
    ("Symbols!@#$", "symbols"),
    ("MiXeD-Case", "mixed-case"),
    ("", ""),
    ("   ", ""),
], ids=["basic","spaces","symbols","case","empty","spaces-only"])
def test_slugify(inp, expected):
    assert slugify(inp) == expected

@pytest.mark.xfail(reason="accent stripping not implemented", strict=False)
def test_slugify_accents():
    assert slugify("Café à la carte") == "cafe-a-la-carte"
