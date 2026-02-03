import os
from token import OP
import uuid
import base64
import requests
import fastapi_poe as fp
import json
TEXT_BOT_NAME = "gpt-5.2-instant"

OPENROUTER_URL = "https://openrouter.ai/api/v1/chat/completions"
# Use flux.2-pro (documented for image gen). Override with OPENROUTER_IMAGE_MODEL env.

# OPENROUTER_IMAGE_MODEL = os.getenv("OPENROUTER_IMAGE_MODEL", "black-forest-labs/flux.2-pro")
OPENROUTER_IMAGE_MODEL = os.getenv("OPENROUTER_IMAGE_MODEL", "google/gemini-2.5-flash-image")        
# -----------------------------
# Poe: 文字 + image_prompt
# -----------------------------
def analyze_with_poe(prompt: str) -> dict:
    api_key = os.getenv("POE_API_KEY")
    if not api_key:
        raise RuntimeError("POE_API_KEY missing")

    message = fp.ProtocolMessage(role="user", content=prompt)
    text = ""

    for partial in fp.get_bot_response_sync(
        messages=[message],
        bot_name=TEXT_BOT_NAME,
        api_key=api_key
    ):
        if hasattr(partial, "text") and partial.text:
            text += partial.text

    try:
        return json.loads(text)
    except json.JSONDecodeError:
        raise RuntimeError(f"Poe did not return valid JSON:\n{text[:500]}")

# -----------------------------
# OpenRouter: 圖片生成
# -----------------------------
def generate_kitten_image(image_prompt: str, logger=None) -> dict:
    api_key = os.getenv("OPENROUTER_API_KEY")
    upload_dir = os.getenv("UPLOAD_DIR", "./uploads")

    if not api_key:
        return {"success": False, "error": "OPENROUTER_API_KEY missing"}

    os.makedirs(upload_dir, exist_ok=True)

    headers = {
        "Authorization": f"Bearer {api_key}",
        "Content-Type": "application/json",
        "HTTP-Referer": "https://pawmatch.ai",
        "X-Title": "PawMatch",
    }

    payload = {
        "model": OPENROUTER_IMAGE_MODEL,
        "modalities": ["image", "text"],
        "messages": [
            {"role": "user", "content": image_prompt}
        ],
    }

    try:
        r = requests.post(
            OPENROUTER_URL,
            headers=headers,
            json=payload,
            timeout=90
        )
        if not r.ok and logger:
            try:
                err_body = r.text[:500] if r.text else "(no body)"
                logger.warning(f"OpenRouter response {r.status_code}: {err_body}")
            except Exception:
                pass
        r.raise_for_status()
        data = r.json()

        message = data["choices"][0]["message"]
        images = message.get("images")

        if not images:
            if logger:
                logger.warning(f"⚠️ No images returned. Full message: {message}")
            return {
                "success": False,
                "error": "OpenRouter returned no images",
                "raw_message": message
            }

        # Base64 data URL
        data_url = images[0]["image_url"]["url"]
        b64 = data_url.split(",", 1)[1]
        img_bytes = base64.b64decode(b64)

        filename = f"kitten_{uuid.uuid4().hex}.png"
        path = os.path.join(upload_dir, filename)

        with open(path, "wb") as f:
            f.write(img_bytes)

        if logger:
            logger.info(f"FLUX image saved: {path}")

        return {
            "success": True,
            "image_url": f"/uploads/{filename}"
        }

    except Exception as e:
        if logger:
            logger.exception("OpenRouter FLUX image generation failed")
        return {
            "success": False,
            "error": str(e)
        }
