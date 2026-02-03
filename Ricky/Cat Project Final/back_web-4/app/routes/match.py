import json
import logging
from flask import Blueprint, jsonify, request, current_app

from ..services.storage import Storage
from ..services.poe_analyze import (
    analyze_with_poe,
    generate_kitten_image
)
from ..utils.auth import require_jwt

logger = logging.getLogger(__name__)

bp = Blueprint("match", __name__, url_prefix="/api")


# ----------------------------
# Matching score logic
# ----------------------------
def _different_gender(my_gender: str, other_gender: str) -> bool:
    """Return True only if both genders are set and different (case-insensitive)."""
    a = (my_gender or "").strip().lower()
    b = (other_gender or "").strip().lower()
    if not a or not b:
        return False
    return a != b


def _score(my_cat: dict, other: dict) -> dict:
    score = 0

    # 1. Same breed
    if (my_cat.get("breed") or "") == (other.get("breed") or ""):
        score += 30

    # 2. Age similarity
    try:
        age_diff = abs(int(my_cat.get("age", 0)) - int(other.get("age", 0)))
        score += max(0, 25 - min(25, age_diff * 5))
    except Exception:
        pass

    # 3. Vaccination overlap
    my_v = set(my_cat.get("vaccinations") or [])
    ot_v = set(other.get("vaccinations") or [])
    score += min(10, len(my_v.intersection(ot_v)) * 2)

    # 4. Health similarity
    if (my_cat.get("health") or "").lower() == (other.get("health") or "").lower():
        score += 10

    return {
        "cat": other,
        "score": int(score),
    }


# ----------------------------
# Prompt builder (Poe analyze)
# ----------------------------
def _build_prompt(my_cat: dict, top_matches: list) -> str:
    my_profile = my_cat.get("profile") or {}

    my_summary = {
        "name": my_cat.get("name"),
        "breed": my_cat.get("breed"),
        "age": my_cat.get("age"),
        "sex_status": my_cat.get("gender"),
        "health": my_cat.get("health"),
        "vaccinations": my_cat.get("vaccinations"),
        "source": my_profile.get("source"),
        "owner_experience_years": my_profile.get("experience_years"),
        "origin_knowledge": my_profile.get("origin_knowledge"),
    }

    candidates = []
    for item in top_matches:
        c = item.get("cat") or {}
        candidates.append({
            "name": c.get("name"),
            "breed": c.get("breed"),
            "age": c.get("age"),
            "sex_status": c.get("gender"),
            "health": c.get("health"),
            "vaccinations": c.get("vaccinations"),
            "score": item.get("score"),
        })

    return f"""
# Role:
Professional AI Feline Health & Breed Consultant.

# Context:
You are an AI consultant for cat breeding & care.

# User's Cat:
{json.dumps(my_summary, ensure_ascii=False, indent=2)}

# Potential Match Cats:
{json.dumps(candidates, ensure_ascii=False, indent=2)}

# Output Format (JSON ONLY, no markdown block, no extra text):

{{
  "summary_md": "≤100 Chinese characters, markdown allowed",
  "image_prompt": "≤100 English words, for image generation"
}}
""".strip()


# ----------------------------
# API: GET /api/match-result
# ----------------------------
@bp.get("/match-result")
def match_result():
    user = require_jwt()
    user_id = int(user["user_id"])
    email = user["email"]

    store = Storage(current_app.config["SQLITE_PATH"])
    my_cat = store.get_cat_by_user_id(user_id)

    if not my_cat:
        return jsonify({
            "status": "error",
            "message": "No cat profile"
        }), 404

    # -------- 配對計分 --------
    others = store.list_other_cats(user_id=user_id, limit=200)
    # Only consider cats with a different gender than the user's feline
    others = [c for c in others if _different_gender(my_cat.get("gender"), c.get("gender"))]
    scored = sorted(
        [_score(my_cat, c) for c in others],
        key=lambda x: x["score"],
        reverse=True
    )
    top_matches = scored[:5]

    # -------- Poe 文字分析 --------
    review_md = "AI 分析暫時無法使用"
    image_prompt = None

    try:
        logger.info("Building prompt for Poe analysis...")
        prompt = _build_prompt(my_cat, top_matches)
        logger.info(f"Prompt built successfully, length: {len(prompt)}")
        
        logger.info("Calling analyze_with_poe...")
        ai_result = analyze_with_poe(prompt)
        logger.info(f"Poe analyze result: {ai_result}")

        if isinstance(ai_result, dict):
            review_md = ai_result.get("summary_md", review_md)
            image_prompt = ai_result.get("image_prompt")
            logger.info(f"Successfully extracted review_md and image_prompt")
        else:
            logger.warning(f"AI result is not a dict, got: {type(ai_result)}")

    except Exception as e:
        logger.exception(f"Poe analyze failed: {str(e)}")
        current_app.logger.exception("Poe analyze failed")

    # -------- OpenRouter 產圖 --------
    kitten_image_url = None
    image_result = None

    if image_prompt:
        image_prompt = image_prompt.strip()

        # 強制 ≤100 字
        if len(image_prompt) > 100:
            image_prompt = image_prompt[:100]

        try:
            logger.info(f"Generating image with prompt: {image_prompt[:50]}...")
            image_result = generate_kitten_image(
                image_prompt,
                logger=current_app.logger
            )
            logger.info(f"Image generation result: {image_result}")
        except Exception as e:
            logger.exception(f"Image generation crashed: {str(e)}")
            current_app.logger.exception("Image generation crashed")
    else:
        logger.info("No image prompt provided, skipping image generation")

    if image_result and image_result.get("success"):
        kitten_image_url = image_result.get("image_url")
    else:
        if image_result:
            current_app.logger.warning(
                f"Image generation failed: {image_result.get('error')}"
            )

    # -------- Response --------
    return jsonify({
        "status": "ok",
        "user": {
            "email": email,
            "user_id": user_id
        },
        "your_feline": my_cat,
        "match_review_md": review_md,
        "kitten_image_url": kitten_image_url,
        "potential_matches": top_matches
    }), 200


# ----------------------------
# Prompt builder for offspring generation
# ----------------------------
def _build_offspring_prompt(my_cat: dict, match_cat: dict) -> str:
    """Build a prompt for generating offspring review and image for a specific cat pair."""
    my_profile = my_cat.get("profile") or {}
    match_profile = match_cat.get("profile") or {}

    my_summary = {
        "name": my_cat.get("name"),
        "breed": my_cat.get("breed"),
        "age": my_cat.get("age"),
        "sex_status": my_cat.get("gender"),
        "health": my_cat.get("health"),
        "vaccinations": my_cat.get("vaccinations"),
    }

    match_summary = {
        "name": match_cat.get("name"),
        "breed": match_cat.get("breed"),
        "age": match_cat.get("age"),
        "sex_status": match_cat.get("gender"),
        "health": match_cat.get("health"),
        "vaccinations": match_cat.get("vaccinations"),
    }

    return f"""
# Role:
Professional AI Feline Genetics & Breeding Consultant.

# Context:
You are analyzing the potential offspring of two specific cats. Provide insights about what their kitten might look like, inherit traits, and health considerations.

# Parent Cat 1 (User's Cat):
{json.dumps(my_summary, ensure_ascii=False, indent=2)}

# Parent Cat 2 (Selected Match):
{json.dumps(match_summary, ensure_ascii=False, indent=2)}

# Task:
Analyze the potential offspring of these two cats. Consider:
1. Likely breed characteristics and appearance
2. Potential health traits inherited from parents
3. Expected temperament based on parent breeds

# Output Format (JSON ONLY, no markdown block, no extra text):

{{
  "summary_md": "≤150 Chinese characters markdown analysis of the potential offspring, including appearance, health predictions, and care recommendations",
  "image_prompt": "≤100 English words describing a realistic cute kitten that would result from breeding a {my_cat.get('breed', 'cat')} with a {match_cat.get('breed', 'cat')}, include specific appearance details like fur color, pattern, eye color, and body type"
}}
""".strip()


# ----------------------------
# API: POST /api/generate-offspring
# ----------------------------
@bp.post("/generate-offspring")
def generate_offspring():
    """Generate AI review and kitten image for a specific cat pair."""
    user = require_jwt()
    user_id = int(user["user_id"])

    data = request.get_json(silent=True) or {}
    match_cat_id = data.get("match_cat_id")

    if not match_cat_id:
        return jsonify({
            "status": "error",
            "message": "match_cat_id is required"
        }), 400

    store = Storage(current_app.config["SQLITE_PATH"])
    
    # Get user's cat
    my_cat = store.get_cat_by_user_id(user_id)
    if not my_cat:
        return jsonify({
            "status": "error",
            "message": "No cat profile found"
        }), 404

    # Get the matched cat by ID
    match_cat = None
    others = store.list_other_cats(user_id=user_id, limit=200)
    for cat in others:
        if cat.get("id") == match_cat_id:
            match_cat = cat
            break

    if not match_cat:
        return jsonify({
            "status": "error",
            "message": "Match cat not found"
        }), 404

    if not _different_gender(my_cat.get("gender"), match_cat.get("gender")):
        return jsonify({
            "status": "error",
            "message": "Your Feline and Potential Match must have different genders"
        }), 400

    # -------- Poe AI Analysis for this pair --------
    review_md = "AI 分析暫時無法使用"
    image_prompt = None

    try:
        logger.info(f"Building offspring prompt for cats: {my_cat.get('name')} + {match_cat.get('name')}")
        prompt = _build_offspring_prompt(my_cat, match_cat)
        logger.info(f"Offspring prompt built, length: {len(prompt)}")
        
        logger.info("Calling analyze_with_poe for offspring...")
        ai_result = analyze_with_poe(prompt)
        logger.info(f"Offspring Poe result: {ai_result}")

        if isinstance(ai_result, dict):
            review_md = ai_result.get("summary_md", review_md)
            image_prompt = ai_result.get("image_prompt")
            logger.info(f"Extracted offspring review and image_prompt")
        else:
            logger.warning(f"AI result is not a dict, got: {type(ai_result)}")

    except Exception as e:
        logger.exception(f"Offspring Poe analyze failed: {str(e)}")
        current_app.logger.exception("Offspring Poe analyze failed")

    # -------- OpenRouter Image Generation --------
    kitten_image_url = None
    image_result = None

    if image_prompt:
        image_prompt = image_prompt.strip()

        # Limit to 100 words
        words = image_prompt.split()
        if len(words) > 100:
            image_prompt = " ".join(words[:100])

        try:
            logger.info(f"Generating offspring image with prompt: {image_prompt[:80]}...")
            image_result = generate_kitten_image(
                image_prompt,
                logger=current_app.logger
            )
            logger.info(f"Offspring image generation result: {image_result}")
        except Exception as e:
            logger.exception(f"Offspring image generation crashed: {str(e)}")
            current_app.logger.exception("Offspring image generation crashed")
    else:
        logger.info("No image prompt for offspring, skipping image generation")

    if image_result and image_result.get("success"):
        kitten_image_url = image_result.get("image_url")
    else:
        if image_result:
            current_app.logger.warning(
                f"Offspring image generation failed: {image_result.get('error')}"
            )

    # -------- Response --------
    return jsonify({
        "status": "ok",
        "match_cat_id": match_cat_id,
        "match_cat_name": match_cat.get("name"),
        "review_md": review_md,
        "kitten_image_url": kitten_image_url
    }), 200