from playwright.sync_api import sync_playwright

with sync_playwright() as p:
    browser = p.chromium.launch(headless=False)

    # ✅ 第一次：不要讀 storage_state
    context = browser.new_context()
    page = context.new_page()

    page.goto("https://poe.com")

    print("👉 請手動登入 Poe（登入完成後，停留喺 Poe 主頁）")
    print("👉 登完之後等 15 秒，唔洗做任何嘢")

    page.wait_for_timeout(15000)

    # ✅ 登入完成後，先儲存 session
    context.storage_state(path="poe_state.json")
    print("✅ 已成功儲存登入狀態：poe_state.json")

    browser.close()