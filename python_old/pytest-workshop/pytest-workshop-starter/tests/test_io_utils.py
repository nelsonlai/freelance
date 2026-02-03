import json
from src.io_utils import write_lines, read_lines, get_api_key, greet, fetch_json

def test_write_and_read(tmp_path):
    p = tmp_path / "data.txt"
    write_lines(p, ["a", "b", "c"])
    assert read_lines(p) == ["a", "b", "c"]

def test_get_api_key(monkeypatch):
    monkeypatch.setenv("API_KEY", "secret123")
    assert get_api_key() == "secret123"

def test_greet_output_and_log(capsys, caplog):
    caplog.set_level("INFO")
    greet("Nelson")
    out = capsys.readouterr().out
    assert "Hello, Nelson!" in out
    assert any("Greeted Nelson" in r.message for r in caplog.records)

def test_fetch_json_mocker(mocker):
    fake = {"ok": True}
    get = mocker.patch("src.io_utils.requests.get")
    get.return_value.json.return_value = fake

    assert fetch_json("http://example.com") == fake
    get.assert_called_once_with("http://example.com", timeout=5)
