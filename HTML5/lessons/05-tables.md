# 第 5 課：表格

## 📚 本課學習目標

- 理解表格的結構和用途
- 學會建立基本表格
- 掌握表格的進階功能
- 了解表格的最佳實踐和無障礙設計

## 📊 表格基本結構

HTML 表格用於顯示結構化的數據，由行和列組成。

### 基本標籤

| 標籤 | 說明 |
|------|------|
| `<table>` | 定義表格 |
| `<tr>` | 表格列（Table Row） |
| `<td>` | 表格儲存格（Table Data） |
| `<th>` | 表格標題儲存格（Table Header） |

### 最簡單的表格

```html
<table>
    <tr>
        <td>儲存格 1</td>
        <td>儲存格 2</td>
    </tr>
    <tr>
        <td>儲存格 3</td>
        <td>儲存格 4</td>
    </tr>
</table>
```

**顯示效果：**

| 儲存格 1 | 儲存格 2 |
| 儲存格 3 | 儲存格 4 |

## 🎯 帶標題的表格

```html
<table>
    <tr>
        <th>姓名</th>
        <th>年齡</th>
        <th>城市</th>
    </tr>
    <tr>
        <td>張三</td>
        <td>25</td>
        <td>台北</td>
    </tr>
    <tr>
        <td>李四</td>
        <td>30</td>
        <td>台中</td>
    </tr>
    <tr>
        <td>王五</td>
        <td>28</td>
        <td>高雄</td>
    </tr>
</table>
```

**顯示效果：**

| 姓名 | 年齡 | 城市 |
|------|------|------|
| 張三 | 25 | 台北 |
| 李四 | 30 | 台中 |
| 王五 | 28 | 高雄 |

## 🏗️ 表格的語義化結構

完整的表格應該包含 `<thead>`、`<tbody>` 和 `<tfoot>` 三個部分：

```html
<table>
    <thead>
        <tr>
            <th>商品</th>
            <th>數量</th>
            <th>單價</th>
            <th>小計</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <td>蘋果</td>
            <td>5</td>
            <td>$30</td>
            <td>$150</td>
        </tr>
        <tr>
            <td>香蕉</td>
            <td>3</td>
            <td>$25</td>
            <td>$75</td>
        </tr>
        <tr>
            <td>橘子</td>
            <td>4</td>
            <td>$20</td>
            <td>$80</td>
        </tr>
    </tbody>
    <tfoot>
        <tr>
            <th colspan="3">總計</th>
            <td>$305</td>
        </tr>
    </tfoot>
</table>
```

**結構說明：**
- `<thead>`：表格標題區（通常包含欄位名稱）
- `<tbody>`：表格主體區（包含實際數據）
- `<tfoot>`：表格頁腳區（通常包含統計資訊）

## 📐 表格標題

使用 `<caption>` 為表格加上標題：

```html
<table>
    <caption>2026 年第一季銷售報表</caption>
    <thead>
        <tr>
            <th>月份</th>
            <th>銷售額</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <td>一月</td>
            <td>$50,000</td>
        </tr>
        <tr>
            <td>二月</td>
            <td>$60,000</td>
        </tr>
        <tr>
            <td>三月</td>
            <td>$55,000</td>
        </tr>
    </tbody>
</table>
```

## 🔄 合併儲存格

### 1. 橫向合併（colspan）

合併同一列的多個儲存格：

```html
<table>
    <tr>
        <th colspan="3">學生成績表</th>
    </tr>
    <tr>
        <th>姓名</th>
        <th>數學</th>
        <th>英文</th>
    </tr>
    <tr>
        <td>張三</td>
        <td>85</td>
        <td>90</td>
    </tr>
</table>
```

### 2. 縱向合併（rowspan）

合併同一欄的多個儲存格：

```html
<table>
    <tr>
        <th>姓名</th>
        <th>科目</th>
        <th>成績</th>
    </tr>
    <tr>
        <td rowspan="2">張三</td>
        <td>數學</td>
        <td>85</td>
    </tr>
    <tr>
        <td>英文</td>
        <td>90</td>
    </tr>
    <tr>
        <td rowspan="2">李四</td>
        <td>數學</td>
        <td>78</td>
    </tr>
    <tr>
        <td>英文</td>
        <td>88</td>
    </tr>
</table>
```

### 3. 同時使用 colspan 和 rowspan

```html
<table>
    <caption>課程時間表</caption>
    <tr>
        <th>時間</th>
        <th>星期一</th>
        <th>星期二</th>
        <th>星期三</th>
    </tr>
    <tr>
        <td>09:00-10:00</td>
        <td>數學</td>
        <td rowspan="2">體育</td>
        <td>英文</td>
    </tr>
    <tr>
        <td>10:00-11:00</td>
        <td>國文</td>
        <td>數學</td>
    </tr>
    <tr>
        <td>11:00-12:00</td>
        <td colspan="3">午休</td>
    </tr>
</table>
```

## 💻 實作練習 1：學生成績表

```html
<!DOCTYPE html>
<html lang="zh-TW">
<head>
    <meta charset="UTF-8">
    <title>學生成績表</title>
    <style>
        table {
            border-collapse: collapse;
            width: 100%;
        }
        th, td {
            border: 1px solid #ddd;
            padding: 8px;
            text-align: center;
        }
        th {
            background-color: #4CAF50;
            color: white;
        }
        caption {
            font-size: 1.5em;
            margin: 10px;
            font-weight: bold;
        }
    </style>
</head>
<body>
    <table>
        <caption>高中一年級成績表</caption>
        <thead>
            <tr>
                <th>學號</th>
                <th>姓名</th>
                <th>國文</th>
                <th>英文</th>
                <th>數學</th>
                <th>總分</th>
                <th>平均</th>
            </tr>
        </thead>
        <tbody>
            <tr>
                <td>A001</td>
                <td>張小明</td>
                <td>85</td>
                <td>90</td>
                <td>88</td>
                <td>263</td>
                <td>87.7</td>
            </tr>
            <tr>
                <td>A002</td>
                <td>李小華</td>
                <td>78</td>
                <td>85</td>
                <td>92</td>
                <td>255</td>
                <td>85.0</td>
            </tr>
            <tr>
                <td>A003</td>
                <td>王小美</td>
                <td>92</td>
                <td>88</td>
                <td>90</td>
                <td>270</td>
                <td>90.0</td>
            </tr>
        </tbody>
        <tfoot>
            <tr>
                <th colspan="2">班級平均</th>
                <td>85.0</td>
                <td>87.7</td>
                <td>90.0</td>
                <td>262.7</td>
                <td>87.6</td>
            </tr>
        </tfoot>
    </table>
</body>
</html>
```

## 🎨 表格屬性

### scope 屬性（無障礙）

幫助螢幕閱讀器理解標題與資料的關係：

```html
<table>
    <tr>
        <th scope="col">姓名</th>
        <th scope="col">年齡</th>
    </tr>
    <tr>
        <th scope="row">張三</th>
        <td>25</td>
    </tr>
</table>
```

**scope 的值：**
- `col`：欄標題
- `row`：列標題
- `colgroup`：欄群組標題
- `rowgroup`：列群組標題

### headers 屬性（複雜表格）

用於複雜表格，明確指定儲存格與標題的關係：

```html
<table>
    <tr>
        <th id="name">姓名</th>
        <th id="age">年齡</th>
    </tr>
    <tr>
        <td headers="name">張三</td>
        <td headers="age">25</td>
    </tr>
</table>
```

## 💻 實作練習 2：產品價格表

```html
<!DOCTYPE html>
<html lang="zh-TW">
<head>
    <meta charset="UTF-8">
    <title>產品價格表</title>
    <style>
        table {
            border-collapse: collapse;
            width: 80%;
            margin: 20px auto;
        }
        th, td {
            border: 1px solid #333;
            padding: 12px;
            text-align: center;
        }
        thead th {
            background-color: #2196F3;
            color: white;
        }
        tbody tr:nth-child(odd) {
            background-color: #f2f2f2;
        }
        tbody tr:hover {
            background-color: #ddd;
        }
        .highlight {
            background-color: #ffeb3b;
            font-weight: bold;
        }
    </style>
</head>
<body>
    <h1 style="text-align: center;">智慧型手機價格比較</h1>
    
    <table>
        <caption>2026 年 2 月價格</caption>
        <thead>
            <tr>
                <th scope="col">品牌</th>
                <th scope="col">型號</th>
                <th scope="col">儲存空間</th>
                <th scope="col">價格</th>
                <th scope="col">評分</th>
            </tr>
        </thead>
        <tbody>
            <tr>
                <td rowspan="2">Apple</td>
                <td>iPhone 15</td>
                <td>128GB</td>
                <td>$29,900</td>
                <td>4.5/5.0</td>
            </tr>
            <tr>
                <td>iPhone 15 Pro</td>
                <td>256GB</td>
                <td class="highlight">$36,900</td>
                <td>4.8/5.0</td>
            </tr>
            <tr>
                <td rowspan="2">Samsung</td>
                <td>Galaxy S24</td>
                <td>128GB</td>
                <td>$27,900</td>
                <td>4.4/5.0</td>
            </tr>
            <tr>
                <td>Galaxy S24 Ultra</td>
                <td>256GB</td>
                <td>$38,900</td>
                <td>4.7/5.0</td>
            </tr>
        </tbody>
        <tfoot>
            <tr>
                <td colspan="5">
                    <small>價格僅供參考，實際售價以店家為準。</small>
                </td>
            </tr>
        </tfoot>
    </table>
</body>
</html>
```

## 🎯 表格樣式化（CSS 預覽）

雖然我們還沒學 CSS，但可以先看一下基本的表格樣式：

```html
<style>
    table {
        border-collapse: collapse;  /* 合併邊框 */
        width: 100%;
    }
    
    th, td {
        border: 1px solid #ddd;    /* 邊框 */
        padding: 8px;               /* 內距 */
        text-align: left;           /* 文字對齊 */
    }
    
    th {
        background-color: #4CAF50;  /* 背景色 */
        color: white;               /* 文字色 */
    }
    
    tr:nth-child(even) {
        background-color: #f2f2f2;  /* 斑馬條紋 */
    }
    
    tr:hover {
        background-color: #ddd;     /* 滑鼠懸停效果 */
    }
</style>
```

## 📝 表格最佳實踐

### ✅ 應該做的

1. **使用語義化標籤**：正確使用 `<thead>`、`<tbody>`、`<tfoot>`
2. **加上 caption**：為表格提供標題
3. **使用 scope 屬性**：提升無障礙性
4. **適當使用 th**：標題儲存格用 `<th>`，資料儲存格用 `<td>`
5. **保持簡單**：避免過度複雜的表格

### ❌ 不應該做的

1. **不要用表格做版面配置**：應該使用 CSS 來控制版面
2. **避免過多巢狀**：不要在表格內嵌套太多表格
3. **不要省略必要標籤**：保持 HTML 結構完整

## 💻 實作練習 3：課程時間表

```html
<!DOCTYPE html>
<html lang="zh-TW">
<head>
    <meta charset="UTF-8">
    <title>課程時間表</title>
    <style>
        table {
            border-collapse: collapse;
            width: 100%;
            margin: 20px 0;
        }
        th, td {
            border: 2px solid #333;
            padding: 15px;
            text-align: center;
        }
        thead th {
            background-color: #FF5722;
            color: white;
        }
        .time {
            background-color: #FFC107;
            font-weight: bold;
        }
        .break {
            background-color: #E0E0E0;
        }
    </style>
</head>
<body>
    <h1 style="text-align: center;">高中一年級課表</h1>
    
    <table>
        <caption>第一學期課程時間表</caption>
        <thead>
            <tr>
                <th scope="col">節次/時間</th>
                <th scope="col">星期一</th>
                <th scope="col">星期二</th>
                <th scope="col">星期三</th>
                <th scope="col">星期四</th>
                <th scope="col">星期五</th>
            </tr>
        </thead>
        <tbody>
            <tr>
                <td class="time" scope="row">第一節<br>08:10-09:00</td>
                <td>國文</td>
                <td>數學</td>
                <td>英文</td>
                <td>歷史</td>
                <td>地理</td>
            </tr>
            <tr>
                <td class="time" scope="row">第二節<br>09:10-10:00</td>
                <td>數學</td>
                <td>英文</td>
                <td>物理</td>
                <td>化學</td>
                <td>生物</td>
            </tr>
            <tr>
                <td class="time" scope="row">第三節<br>10:10-11:00</td>
                <td>英文</td>
                <td>國文</td>
                <td>數學</td>
                <td>體育</td>
                <td>音樂</td>
            </tr>
            <tr>
                <td class="time" scope="row">第四節<br>11:10-12:00</td>
                <td>歷史</td>
                <td>地理</td>
                <td>公民</td>
                <td>國文</td>
                <td>英文</td>
            </tr>
            <tr>
                <td class="break" colspan="6">午休時間 12:00-13:10</td>
            </tr>
            <tr>
                <td class="time" scope="row">第五節<br>13:10-14:00</td>
                <td>體育</td>
                <td>電腦</td>
                <td>美術</td>
                <td>音樂</td>
                <td>班會</td>
            </tr>
        </tbody>
    </table>
</body>
</html>
```

## 📝 本課重點回顧

- ✅ 表格使用 `<table>`、`<tr>`、`<td>`、`<th>` 建立
- ✅ 完整的表格包含 `<thead>`、`<tbody>`、`<tfoot>`
- ✅ 使用 `<caption>` 為表格加上標題
- ✅ `colspan` 橫向合併儲存格，`rowspan` 縱向合併儲存格
- ✅ 使用 `scope` 屬性提升無障礙性
- ✅ 表格用於顯示結構化數據，不用於版面配置
- ✅ `<th>` 用於標題，`<td>` 用於資料

## 🎯 課後練習

1. **基礎練習**：建立個人每週行程表
   - 包含星期一到星期日
   - 至少包含 5 個時段（早上、上午、中午、下午、晚上）
   - 填入你的日常活動
   - 使用不同顏色區分不同類型的活動

2. **進階挑戰**：建立產品比較表
   - 比較至少 3 個產品（手機、筆電、相機等）
   - 包含至少 5 個比較項目（價格、規格、重量等）
   - 使用 `rowspan` 或 `colspan` 合併某些儲存格
   - 加上表格標題和頁腳說明

3. **實戰練習**：建立餐廳菜單表
   - 分類顯示（前菜、主餐、甜點、飲料）
   - 包含菜名、價格、說明
   - 使用合併儲存格突顯分類標題
   - 加上適當的樣式（顏色、對齊等）

## 🔗 下一課預告

在下一課中，我們將學習 HTML 表單的基礎知識，包括輸入欄位、按鈕、下拉選單等，讓使用者可以與網頁互動！

---

[← 上一課：圖片和多媒體](./04-images-media.md) | [返回目錄](../README.md) | [下一課：表單基礎 →](./06-forms-basics.md)
