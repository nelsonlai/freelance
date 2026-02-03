import requests


class PoeClient:
    def __init__(
        self,
        base_url: str,
        endpoint: str,
        api_key: str,
        timeout: int = 45,
        language: str = "zh",
    ):
        self.base_url = base_url.rstrip("/")
        self.endpoint = endpoint if endpoint.startswith("/") else f"/{endpoint}"
        self.api_key = api_key
        self.timeout = timeout
        self.language = language

    def analyze(self, text: str) -> str:
        if not self.api_key:
            raise RuntimeError("POE_API_KEY is missing")

        url = f"{self.base_url}{self.endpoint}"

        headers = {
            "Authorization": f"Bearer {self.api_key}",
            "Content-Type": "application/json",
        }

        body = {
            "text": text,
            "language": self.language,
        }

        resp = requests.post(
            url,
            headers=headers,
            json=body,
            timeout=self.timeout,
        )
        resp.raise_for_status()

        data = resp.json()
        if isinstance(data, dict):
            return data.get("result") or data.get("text") or str(data)

        return str(data)
