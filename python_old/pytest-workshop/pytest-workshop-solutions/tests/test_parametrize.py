import pytest, json
from src.mathy import add, reciprocal

@pytest.mark.parametrize(
    "a,b,expected",
    [(1,2,3), (0,0,0), (-1,1,0), (10,-7,3)],
    ids=["simple","zeros","cancel","mixed"],
)
def test_add_param(a,b,expected):
    assert add(a,b) == expected

@pytest.mark.parametrize("x,expected", [(4,0.25), (2,0.5), (8,0.125)])
def test_reciprocal_param(x, expected):
    assert reciprocal(x) == expected

@pytest.fixture
def payload(request):
    return json.loads(request.param)

@pytest.mark.parametrize("payload", ['{"x":1}', '{"x":2,"y":3}'], indirect=True)
def test_payload_shape(payload):
    assert "x" in payload
