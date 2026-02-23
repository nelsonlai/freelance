import os
import fastapi_poe as fp
from dotenv import load_dotenv
from pathlib import Path

BASE_DIR = Path(__file__).resolve().parent
load_dotenv(BASE_DIR / ".env")

print("POE_API_KEY =", os.getenv("POE_API_KEY"))

message = fp.ProtocolMessage(
    role="user",
    content="動畫藝術作品中的白貓，動畫風格，關鍵視覺，色彩鮮豔，動畫工作室"
)

for partial in fp.get_bot_response_sync(
    messages=[message],
    bot_name="nano-banana-pro",
    api_key=os.getenv("POE_API_KEY")
):
    print(partial)