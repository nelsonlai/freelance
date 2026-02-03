# FinMind Examples (Prices, Revenue, Institutional Flow)

This bundle contains **three complete Python scripts** that authenticate to **FinMind**, fetch Taiwan market data, and visualize with **pandas** and **seaborn**. Each script is heavily commented (300+ lines) for learning and adaptation.

> ⚠️ **Disclaimer:** Educational use only. Not investment advice.

---

## Contents

- `finmind_prices_ma_corr.py`  
  Fetches **daily prices** (`TaiwanStockPrice`) for multiple tickers, computes **returns** and **moving averages**, and produces:
  - Close + MA lines (focus ticker)  
  - Daily return distributions (FacetGrid)  
  - Pairplot of returns across tickers  
  - **Correlation heatmap** across tickers

- `finmind_monthly_revenue_analysis.py`  
  Pulls **monthly revenue** (`TaiwanStockMonthRevenue`) for multiple companies, computes **MoM/YoY** growth, and charts:
  - Monthly revenue trend lines  
  - YoY bar plots (recent 24 months)  
  - **YoY heatmap** by month/year (single ticker)  
  - **YTD cumulative revenue** comparison by year

- `finmind_institutional_flow_vs_price.py`  
  Fetches **institutional investors buy/sell** (`TaiwanStockInstitutionalInvestorsBuySell`) and **daily prices**, engineers **net buy** features (5d/20d sums), and explores relationships with **forward returns** via:
  - Price vs. NetBuy (z-scored overlay)  
  - Regressions (NetBuy_5d ↔ fwd returns)  
  - KDE joint density  
  - **Rolling correlation** (60D window)

---

## Prerequisites

- Python 3.9+ recommended
- Packages:
  ```bash
  pip install finmind pandas seaborn matplotlib numpy python-dateutil
  ```

- **Credentials** (choose one):
  - **Token (Recommended)**: set environment variable  
    `FINMIND_TOKEN="your_api_token"`
  - **User/Password**: set environment variables  
    `FINMIND_USER="your_email"` and `FINMIND_PASS="your_password"`

> All scripts try token first, then user/password, else anonymous (strictly rate-limited).

---

## Quick Start

1. Unzip this package.
2. Set your environment variables (macOS/Linux example):
   ```bash
   export FINMIND_TOKEN="YOUR_TOKEN_HERE"
   # or:
   export FINMIND_USER="YOUR_EMAIL"
   export FINMIND_PASS="YOUR_PASSWORD"
   ```
3. Run any script:
   ```bash
   python finmind_prices_ma_corr.py
   python finmind_monthly_revenue_analysis.py
   python finmind_institutional_flow_vs_price.py
   ```

Each script will pull data, show several charts, and print summary tables to your terminal.

---

## What Each Script Demonstrates

### 1) Prices, Moving Averages, Correlations
- **Dataset**: `TaiwanStockPrice`
- **Features**:  
  - Returns (`pct_change`)  
  - Moving Averages **MA(5/20/60)**  
- **Visualizations**:  
  - Focus ticker **Close + MAs**  
  - **Return distributions** (FacetGrid)  
  - **Pairplot** on a subset of tickers  
  - **Correlation heatmap** across tickers  
- **Customization**: edit `default_tickers`, `start_date`, or `ma_windows` in script.

### 2) Monthly Revenue: MoM, YoY, YTD
- **Dataset**: `TaiwanStockMonthRevenue`
- **Features**:  
  - **MoM** = `pct_change(1)`  
  - **YoY** = `pct_change(12)`  
  - **YTD** cumulative by year  
- **Visualizations**:  
  - Revenue line chart  
  - YoY bar plot (last 24 months)  
  - **YoY heatmap** by month/year (single ticker)  
  - **YTD lines** by year  
- **Notes**: First 12 months have `NaN` YoY by design.

### 3) Institutional Flow vs. Price / Returns
- **Datasets**:  
  - `TaiwanStockPrice`  
  - `TaiwanStockInstitutionalInvestorsBuySell`  
- **Features**:  
  - Aggregate **net buy** across available institution columns  
  - Rolling sums over **5D** and **20D**  
  - **Forward returns** over 5D and 10D from price series  
- **Visualizations**:  
  - Price vs. NetBuy (z-score overlay)  
  - **Regression plots** (relationship exploration)  
  - KDE joint density  
  - **Rolling correlation** as a monitoring tool

---

## Common Problems & Fixes

- **`ModuleNotFoundError: FinMind`**  
  → `pip install finmind`

- **Login fails**  
  → Double-check `FINMIND_TOKEN` (or `FINMIND_USER`/`FINMIND_PASS`). Try token first.  
  → Ensure quotes are correct and variables are exported in the same shell session.

- **Rate limiting (HTTP 429)**  
  → Reduce number of tickers or date range.  
  → Increase `polite_sleep_sec`.  
  → Use **token** auth for better quotas.

- **Empty / unexpected columns**  
  → Print `df.columns` to inspect schema; datasets can evolve.  
  → Update column references accordingly.

- **Charts are slow or memory-heavy**  
  → Sample your data for pairplots (`.sample(n=3000)` in the script).  
  → Limit date range or number of tickers.

---

## Security Tips

- Keep your **token** and **passwords** out of version control.  
- Prefer environment variables over hard-coding credentials.  
- If sharing notebooks, remove any saved tokens.

---

## Extending These Scripts

- Write output CSV/Parquet files and reuse them to avoid re-downloading.  
- Add CLI arguments via `argparse` (tickers, date ranges, windows).  
- Replace seaborn with matplotlib if you need strict style control.  
- Build dashboards (e.g., **Streamlit**, **Dash**) on top of these functions.  
- Add statistical tests, rolling betas, or event studies.

---

## Notes on Interpretation

These are **exploratory** analyses. Relationships (e.g., net buy vs. forward returns) can be noisy and unstable. Always validate, backtest, and consider transaction costs, survivorship bias, and regime changes.

---

## License

MIT (for these example scripts). The data usage is subject to **FinMind** terms of service.
