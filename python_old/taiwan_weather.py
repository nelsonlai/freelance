import requests
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
import urllib3
import platform
from datetime import datetime
from matplotlib import rcParams, font_manager as fm

# Disable SSL warnings
urllib3.disable_warnings(urllib3.exceptions.InsecureRequestWarning)

# Explicit font path for macOS (PingFang)
system = platform.system()
if system == "Darwin":  # macOS
    font_path = "/System/Library/Fonts/STHeiti Medium.ttc"
    prop = fm.FontProperties(fname=font_path)
elif system == "Windows":
    font_path = None
    prop = fm.FontProperties(fname="C:/Windows/Fonts/msjh.ttc")
else:  # Linux or others
    font_path = None
    prop = fm.FontProperties(fname="/usr/share/fonts/opentype/noto/NotoSansCJK-Regular.ttc")

rcParams['axes.unicode_minus'] = False

API_KEY = "CWA-976D7922-89DC-47F2-8F1C-40B6F5834EA9"
BASE_FORECAST = "https://opendata.cwa.gov.tw/api/v1/rest/datastore/F-C0032-001"

def fetch_forecast():
    params = {
        "Authorization": API_KEY,
        "format": "JSON"
    }
    r = requests.get(BASE_FORECAST, params=params, verify=False)
    ## How to print the response? (with pretty way) # Home work
    return r.json()

def forecast_to_df(json_data):
    recs = []
    locations = json_data.get("records", {}).get("location", [])
    for loc in locations:
        locname = loc.get("locationName")
        for we in loc.get("weatherElement", []):
            elename = we.get("elementName")
            for t in we.get("time", []):
                param = t.get("parameter", {})
                recs.append({
                    "location": locname,
                    "element": elename,
                    "startTime": t.get("startTime"),
                    "endTime": t.get("endTime"),
                    "value": param.get("parameterName")
                })
    ## print recs, type(recs) ...
    print(recs)
    df = pd.DataFrame(recs)
    if df.empty:
        return df

    df = df.pivot_table(index=["location", "startTime", "endTime"], columns="element", values="value", aggfunc="first").reset_index()

    for col in ["MaxT", "MinT", "PoP"]:
        if col in df.columns:
            df[col] = pd.to_numeric(df[col], errors="coerce")

    df["startTime"] = pd.to_datetime(df["startTime"], errors="coerce")
    df["endTime"] = pd.to_datetime(df["endTime"], errors="coerce")
    return df

def set_ticks_font(ax):
    for label in ax.get_xticklabels() + ax.get_yticklabels():
        label.set_fontproperties(prop)

def plot_forecast(df):
    sns.set_style("whitegrid")

    # 1. MaxT/MinT lineplot
    plt.figure(figsize=(12, 6))
    ax = sns.lineplot(data=df, x="startTime", y="MaxT", hue="location", marker="o")
    sns.lineplot(data=df, x="startTime", y="MinT", hue="location", marker="x", legend=False)
    plt.title("MaxT 和 MinT 時間趨勢", fontproperties=prop)
    plt.xticks(rotation=45, fontproperties=prop)
    plt.yticks(fontproperties=prop)
    ax.legend(prop=prop)
    plt.tight_layout()
    plt.show()

    # 2. PoP distribution
    if "PoP" in df.columns:
        plt.figure(figsize=(8, 5))
        ax = sns.histplot(df["PoP"].dropna(), bins=20, kde=True)
        plt.title("降雨機率分佈", fontproperties=prop)
        plt.xticks(fontproperties=prop)
        plt.yticks(fontproperties=prop)
        plt.tight_layout()
        plt.show()

    # 3. MaxT boxplot by location
    if "MaxT" in df.columns:
        plt.figure(figsize=(10, 5))
        ax = sns.boxplot(data=df, x="location", y="MaxT")
        plt.xticks(rotation=90, fontproperties=prop)
        plt.yticks(fontproperties=prop)
        plt.title("各地區最高溫度", fontproperties=prop)
        ax.legend(prop=prop) if ax.get_legend() else None
        plt.tight_layout()
        plt.show()

    # 4. MinT boxplot by location
    if "MinT" in df.columns:
        plt.figure(figsize=(10, 5))
        ax = sns.boxplot(data=df, x="location", y="MinT")
        plt.xticks(rotation=90, fontproperties=prop)
        plt.yticks(fontproperties=prop)
        plt.title("各地區最低溫度", fontproperties=prop)
        ax.legend(prop=prop) if ax.get_legend() else None
        plt.tight_layout()
        plt.show()

    # 5. MaxT vs MinT scatter
    if "MaxT" in df.columns and "MinT" in df.columns:
        plt.figure(figsize=(8, 6))
        ax = sns.scatterplot(data=df, x="MaxT", y="MinT", hue="location")
        plt.title("最高溫度與最低溫度關係", fontproperties=prop)
        plt.xticks(fontproperties=prop)
        plt.yticks(fontproperties=prop)
        ax.legend(prop=prop)
        plt.tight_layout()
        plt.show()

def main():
    print("Fetching forecast data...")
    data = fetch_forecast()
    df = forecast_to_df(data)
    if df.empty:
        print("No forecast data available.")
        return
    print(df.head())
    plot_forecast(df)

if __name__ == "__main__":
    main()

## Create, Read, Update, Delete - CRUD