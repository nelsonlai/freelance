import pytest
from src.mathy import add, div, reciprocal

def test_add():
    assert add(2, 3) == 5

def test_division_by_zero_type_and_message():
    with pytest.raises(ValueError, match="non-zero"):
        div(1, 0)

def test_sum_with_fixture(numbers):
    assert sum(numbers) == 10

# TODO: Exercise A
# 1) Implement subtract(a,b) in src/mathy.py
# 2) Add a new test here to assert subtract(3,5) == -2
# from src.mathy import subtract
# def test_subtract_negative():
#     assert subtract(3, 5) == -2
