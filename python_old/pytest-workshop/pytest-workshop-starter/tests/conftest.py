import pytest

@pytest.fixture(scope="module")
def numbers():
    return [1, 2, 3, 4]
