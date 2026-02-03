import uuid
from flask import Blueprint, jsonify, request, current_app
from ..utils.auth import require_make_secret
from ..services.storage import Storage
from ..services.poe_client import PoeClient

bp = Blueprint("make", __name__, url_prefix="/webhook")

@bp.post("/make")
def make_webhook():
    require_make_secret()

    payload = request.get_json(silent=True)
    if not payload:
        return jsonify({"status": "error", "message": "Empty payload"}), 400

    # log webhook (for /admin)
    try:
        store = Storage(current_app.config["SQLITE_PATH"])
        meta = {
            "ip": request.headers.get("X-Forwarded-For", request.remote_addr),
            "user_agent": request.headers.get("User-Agent"),
        }
        store.add_webhook_log(source="make", payload=payload, meta=meta)
    except Exception:
        current_app.logger.exception("Failed to log webhook")

    report_id = str(uuid.uuid4())

    prompt = build_cat_analysis_prompt(payload)

    poe = PoeClient(
        base_url=current_app.config["POE_BASE_URL"],
        endpoint=current_app.config["POE_ENDPOINT"],
        api_key=current_app.config["POE_API_KEY"],
        model=current_app.config["POE_MODEL"],
        timeout=current_app.config["POE_TIMEOUT"],
    )

    try:
        poe_result = poe.complete(prompt)
    except Exception as e:
        current_app.logger.exception("Poe call failed")
        return jsonify({"status": "error", "message": str(e)}), 502

    owner_email = payload.get("owner_email") or payload.get("email")  # 若你未來 Make 也送 email
    store = Storage(current_app.config["SQLITE_PATH"])
    store.save_report(report_id=report_id, payload=payload, result=poe_result, owner_email=owner_email)

    return jsonify({"status": "ok", "report_id": report_id})


def build_cat_analysis_prompt(data: dict) -> str:
    return f"""
你是一位專業的「貓咪健康與行為分析顧問」，具備獸醫助理、貓行為學與飼主諮詢經驗。

請根據以下【貓咪飼養問卷資料】，產出一份給一般飼主看得懂、但具專業深度的分析報告。

【請嚴格依照以下結構輸出】：
一、基本概況摘要（3–5 行）
二、健康風險評估（腸胃/慢性病/遺傳風險；需不需要就醫與原因）
三、行為與心理狀態（親人/攻擊性/壓力來源/飼主投入時間是否足夠）
四、照護與飲食建議（飲食/補充品/梳毛/預防）
五、飼主負擔與滿意度（expense_reasonable、care_hours_per_week、life_fulfillment）
六、需補問的關鍵問題（最多 5 個）

【重要限制】：
- 不要下醫療診斷結論
- 不要恐嚇飼主
- 語氣需專業、溫和、支持性
- 如資料不足要明確指出

【問卷資料(JSON)】：
{data}
""".strip()
