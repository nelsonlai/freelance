from playwright.sync_api import sync_playwright

PROMPT = "用廣東話介紹一隻動畫風格白貓，語氣可愛"

with sync_playwright() as p:
    browser = p.chromium.launch(
        headless=False,
        slow_mo=200
    )
    context = browser.new_context(storage_state="poe_state.json")
    page = context.new_page()

    print("👉 打開 Poe bot 頁")
    page.goto("https://poe.com/Nano-Banana-Pro", timeout=60000)

    page.wait_for_timeout(3000)

    # ✅ 點擊「前往 Nano‑Banana‑Pro」
    page.click("text=前往 Nano-Banana-Pro", timeout=15000)
    print("✅ 已點擊『前往 Nano‑Banana‑Pro』")

    # ✅ 等 chat UI render
    page.wait_for_timeout(5000)

    print("🔍 嘗試 focus 輸入框")

    # ✅ Poe 穩定打法：直接用 keyboard focus
    page.keyboard.press("Tab")
    page.keyboard.press("Tab")
    page.keyboard.press("Tab")
    page.keyboard.press("Tab")
    page.keyboard.press("Tab")

    # ✅ 強制輸入
    page.keyboard.type(PROMPT, delay=50)
    page.keyboard.press("Enter")

    print("✅ 已送出 prompt（keyboard 強制輸入）")

    # ✅ 等生成
    page.wait_for_timeout(30000)

    print("✅ 完成，保留畫面 60 秒")
    page.wait_for_timeout(60000)

    browser.close()