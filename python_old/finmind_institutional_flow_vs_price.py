#!/usr/bin/env python3
# -*- coding: utf-8 -*-

'''
finmind_institutional_flow_vs_price.py

Purpose
-------
Explore how institutional investors' net buy/sell flows relate to short-term
returns for a target stock. We will:

1) Login to FinMind
2) Fetch:
   - Daily price:    dataset="TaiwanStockPrice"
   - Institutional:  dataset="TaiwanStockInstitutionalInvestorsBuySell"
3) Engineer features:
   - NetBuy_NTD = sum of major institutions
   - Rolling sums of NetBuy over 5/20 days
   - Forward returns over 5/10 days
4) Visualize with seaborn:
   - Timeseries: price vs. net buy (normalized)
   - regplot: NetBuy_5d vs. ForwardReturn_5d
   - KDE joint distributions
   - Rolling correlation between NetBuy_5d and future returns

Run
---
$ pip install finmind pandas seaborn matplotlib numpy
$ export FINMIND_TOKEN="your_api_token"
# or:
# export FINMIND_USER="your_email"
# export FINMIND_PASS="your_password"

$ python finmind_institutional_flow_vs_price.py

DISCLAIMER
----------
This script is for educational purposes. It is not investment advice.
'''

from __future__ import annotations

import os
import time
from dataclasses import dataclass
from typing import Optional, Tuple

import numpy as np
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

from FinMind.data import DataLoader

sns.set(context="notebook", style="whitegrid")


@dataclass
class Config:
    stock_id: str = "2330"
    start_date: str = "2020-01-01"
    end_date: Optional[str] = None
    polite_sleep_sec: float = 0.6
    figsize_wide: Tuple[int, int] = (14, 6)
    figsize_tall: Tuple[int, int] = (12, 8)


def finmind_login() -> DataLoader:
    api = DataLoader()
    # token = os.getenv("FINMIND_TOKEN", "").strip()
    # user = os.getenv("FINMIND_USER", "").strip()
    # pw = os.getenv("FINMIND_PASS", "").strip()
    token = "eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJkYXRlIjoiMjAyNS0wOC0wNSAwMDo1NjowNSIsInVzZXJfaWQiOiJOZWxzb25MYWkwNTIyIiwiaXAiOiI2OS4xNTguMTc5LjEyNSIsImV4cCI6MTc1NDkzMTM2NX0.MGL_d1mlyMaKtLbQaFT35aXdZQNsHNhC2jrujwHAupU"
    user = "NelsonLai0522"
    pw = "HjnH6&5GHKK"
    if token:
        api.login_by_token(api_token=token)
        print("[auth] Logged in with API token.")
        return api
    if user and pw:
        api.login(user_id=user, password=pw)
        print(f"[auth] Logged in with user: {user}")
        return api
    print("[auth] WARNING: Anonymous mode; consider setting FINMIND_TOKEN.")
    return api


def get_dataset(
    api: DataLoader,
    dataset: str,
    data_id: Optional[str],
    start_date: str,
    end_date: Optional[str],
    sleep_sec: float,
) -> pd.DataFrame:
    """
    Generic v4 dataset fetcher using DataLoader.get_data.
    """
    time.sleep(max(0.0, sleep_sec))
    params = {"dataset": dataset, "start_date": start_date}
    if data_id:
        params["data_id"] = data_id
    if end_date:
        params["end_date"] = end_date
    df = api.get_data(**params).copy()
    df.rename(columns={c: c.lower() for c in df.columns}, inplace=True)
    if "date" in df.columns:
        df["date"] = pd.to_datetime(df["date"])
    return df.sort_values("date").reset_index(drop=True)


def get_price(api: DataLoader, cfg: Config) -> pd.DataFrame:
    return get_dataset(
        api,
        dataset="TaiwanStockPrice",
        data_id=cfg.stock_id,
        start_date=cfg.start_date,
        end_date=cfg.end_date,
        sleep_sec=cfg.polite_sleep_sec,
    )


def get_institutional(api: DataLoader, cfg: Config) -> pd.DataFrame:
    return get_dataset(
        api,
        dataset="TaiwanStockInstitutionalInvestorsBuySell",
        data_id=cfg.stock_id,
        start_date=cfg.start_date,
        end_date=cfg.end_date,
        sleep_sec=cfg.polite_sleep_sec,
    )


def engineer_institutional_features(df_inst: pd.DataFrame) -> pd.DataFrame:
    """
    Create a 'net_buy' that aggregates major institutions.
    """
    out = df_inst.copy()
    candidate_cols = [
        "foreign_buy_sell",
        "investment_trust_buy_sell",
        "dealer_buy_sell",
        "dealer_self_buy_sell",
        "dealer_hedge_buy_sell",
        "foreign",
        "investment_trust",
        "dealer",
        "dealer_self",
        "dealer_hedge",
        "netbuy",
        "net_buy",
    ]
    used = [c for c in candidate_cols if c in out.columns]
    if not used:
        used = [c for c in out.columns if "buy" in c or "sell" in c or "foreign" in c or "dealer" in c]
    out[used] = out[used].fillna(0.0)
    out["net_buy"] = out[used].sum(axis=1)
    out["netbuy_5d"] = out["net_buy"].rolling(5, min_periods=1).sum()
    out["netbuy_20d"] = out["net_buy"].rolling(20, min_periods=1).sum()
    return out


def align_price_and_inst(price: pd.DataFrame, inst: pd.DataFrame) -> pd.DataFrame:
    p = price[["date", "close"]].copy()
    p["ret_1d"] = p["close"].pct_change()
    p["fwdret_5d"] = p["close"].shift(-5) / p["close"] - 1.0
    p["fwdret_10d"] = p["close"].shift(-10) / p["close"] - 1.0
    i = inst[["date", "net_buy", "netbuy_5d", "netbuy_20d"]].copy()
    merged = pd.merge(p, i, on="date", how="inner").dropna().reset_index(drop=True)
    return merged


def plot_price_vs_netbuy(df: pd.DataFrame, cfg: Config) -> None:
    sub = df.copy()
    for col in ["close", "netbuy_5d"]:
        mu, sd = sub[col].mean(), sub[col].std(ddof=0)
        sub[f"z_{col}"] = 0.0 if sd == 0 else (sub[col] - mu) / sd
    plt.figure(figsize=cfg.figsize_wide)
    sns.lineplot(data=sub, x="date", y="z_close", label="Price (z-score)")
    sns.lineplot(data=sub, x="date", y="z_netbuy_5d", label="NetBuy_5d (z-score)")
    plt.title(f"{cfg.stock_id}: Price vs. NetBuy (5-day sum, z-scored)")
    plt.xlabel("Date")
    plt.ylabel("Z-Score")
    plt.tight_layout()
    plt.show()


def plot_reg_forward_returns(df: pd.DataFrame, cfg: Config) -> None:
    sub = df.copy()
    plt.figure(figsize=cfg.figsize_wide)
    sns.regplot(data=sub, x="netbuy_5d", y="fwdret_5d", scatter_kws={"s": 20, "alpha": 0.6})
    plt.title(f"{cfg.stock_id}: NetBuy_5d vs Forward 5D Return")
    plt.xlabel("NetBuy 5D Sum (NTD)")
    plt.ylabel("Forward 5D Return")
    plt.tight_layout()
    plt.show()

    plt.figure(figsize=cfg.figsize_wide)
    sns.regplot(data=sub, x="netbuy_20d", y="fwdret_10d", scatter_kws={"s": 20, "alpha": 0.6})
    plt.title(f"{cfg.stock_id}: NetBuy_20d vs Forward 10D Return")
    plt.xlabel("NetBuy 20D Sum (NTD)")
    plt.ylabel("Forward 10D Return")
    plt.tight_layout()
    plt.show()


def plot_kde(df: pd.DataFrame, cfg: Config) -> None:
    sub = df.copy()
    # Drop rows with NaN or infinite values in the relevant columns
    sub = sub[["netbuy_5d", "fwdret_5d"]].replace([np.inf, -np.inf], np.nan).dropna()
    # Only plot if there are enough unique values
    if sub["netbuy_5d"].nunique() > 1 and sub["fwdret_5d"].nunique() > 1:
        plt.figure(figsize=(8, 6))
        try:
            sns.kdeplot(data=sub, x="netbuy_5d", y="fwdret_5d", fill=True, thresh=0.05, alpha=0.9)
            plt.title(f"{cfg.stock_id}: KDE of NetBuy_5d vs Forward 5D Return")
            plt.tight_layout()
            plt.show()
        except Exception as e:
            print(f"[warn] KDE plot failed: {e}")
    else:
        print("[warn] Not enough unique data to plot KDE.")


def plot_rolling_corr(df: pd.DataFrame, cfg: Config) -> None:
    sub = df[["date", "netbuy_5d", "fwdret_5d"]].dropna().copy()
    sub["rollcorr_60d"] = sub["netbuy_5d"].rolling(60).corr(sub["fwdret_5d"])
    plt.figure(figsize=cfg.figsize_wide)
    sns.lineplot(data=sub, x="date", y="rollcorr_60d")
    plt.axhline(0.0, ls="--", lw=1, color="black")
    plt.title(f"{cfg.stock_id}: Rolling Corr( NetBuy_5d , Forward5D )  (60D window)")
    plt.xlabel("Date")
    plt.ylabel("Correlation")
    plt.tight_layout()
    plt.show()


def main():
    cfg = Config(stock_id="2308", start_date="2018-01-01", end_date=None)
    api = finmind_login()

    print("[step] Fetch daily price…")
    price = get_price(api, cfg)
    print(f"[data] price rows: {len(price)}")

    print("[step] Fetch institutional investors buy/sell…")
    inst = get_institutional(api, cfg)
    print(f"[data] institutional rows: {len(inst)}")

    print("[step] Engineer features…")
    inst_feat = engineer_institutional_features(inst)

    merged = align_price_and_inst(price, inst_feat)

    print("\n=== Descriptive stats (merged) ===")
    with pd.option_context("display.float_format", "{:,.6f}".format):
        print(merged[["ret_1d", "fwdret_5d", "fwdret_10d", "net_buy", "netbuy_5d", "netbuy_20d"]].describe())

    plot_price_vs_netbuy(merged, cfg)
    plot_reg_forward_returns(merged, cfg)
    plot_kde(merged, cfg)
    plot_rolling_corr(merged, cfg)


if __name__ == "__main__":
    main()

# Extra notes
# - Always verify available columns in the institutional dataset via print(df.columns).
# - Interpret any observed relationships cautiously; signals may not be stable.
# - Consider log-scaling large flow numbers before regression.
# - Try additional lags (e.g., 2d, 3d) for forward returns.
# - You can also analyze separate institution categories rather than aggregating.
# - Save plots to files using plt.savefig for reporting pipelines.
# - Add CLI args (argparse) for configurable stock_id, dates, and windows.
# - Use joblib or on-disk caches to avoid repeated downloads during iteration.
# - End of file.
# 