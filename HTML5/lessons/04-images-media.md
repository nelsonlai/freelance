# 第 4 課：圖片和多媒體

## 📚 本課學習目標

- 學會在網頁中插入圖片
- 了解圖片的各種屬性和最佳實踐
- 掌握音訊和視訊的使用方法
- 認識響應式圖片技術

## 🖼️ 圖片標籤

### 基本語法

```html
<img src="圖片路徑" alt="替代文字">
```

**必要屬性：**
- `src`：圖片的來源路徑
- `alt`：替代文字（圖片無法顯示時的說明）

### 完整範例

```html
<img src="images/sunset.jpg" 
     alt="美麗的日落景色" 
     width="600" 
     height="400"
     title="在海邊拍攝的日落">
```

## 📁 圖片路徑

### 1. 相對路徑

```html
<!-- 同一資料夾 -->
<img src="photo.jpg" alt="照片">

<!-- 在 images 子資料夾中 -->
<img src="images/photo.jpg" alt="照片">

<!-- 在上一層資料夾 -->
<img src="../photo.jpg" alt="照片">

<!-- 在上一層的 images 資料夾中 -->
<img src="../images/photo.jpg" alt="照片">
```

### 2. 絕對路徑

```html
<!-- 網站根目錄 -->
<img src="/images/logo.png" alt="網站標誌">

<!-- 完整 URL -->
<img src="https://www.example.com/images/photo.jpg" alt="照片">
```

## 🎨 圖片屬性

### 1. 寬度和高度

```html
<!-- 使用像素 -->
<img src="photo.jpg" alt="照片" width="300" height="200">

<!-- 只設定寬度，高度自動等比例縮放 -->
<img src="photo.jpg" alt="照片" width="300">
```

**注意事項：**
- 建議設定寬高，避免頁面載入時跳動
- 可以用 CSS 控制大小，更靈活

### 2. title 屬性

滑鼠移到圖片上時顯示的提示文字：

```html
<img src="cat.jpg" alt="可愛的貓咪" title="我家的貓咪「小白」">
```

### 3. loading 屬性（延遲載入）

```html
<!-- 延遲載入，提升網頁效能 -->
<img src="large-image.jpg" alt="大圖片" loading="lazy">

<!-- 立即載入（預設值） -->
<img src="important.jpg" alt="重要圖片" loading="eager">
```

## 🖼️ 圖片與連結結合

將圖片變成可點擊的連結：

```html
<a href="https://www.example.com">
    <img src="banner.jpg" alt="點擊前往範例網站">
</a>

<!-- 在新分頁開啟 -->
<a href="large-photo.jpg" target="_blank">
    <img src="thumbnail.jpg" alt="點擊查看大圖">
</a>
```

## 📐 圖片的圖說（Figure 和 Figcaption）

```html
<figure>
    <img src="chart.png" alt="銷售數據圖表">
    <figcaption>圖 1：2026 年第一季銷售數據</figcaption>
</figure>
```

## 💻 實作練習 1：圖片相簿

```html
<!DOCTYPE html>
<html lang="zh-TW">
<head>
    <meta charset="UTF-8">
    <title>我的相簿</title>
</head>
<body>
    <h1>旅遊相簿</h1>
    
    <h2>日本之旅</h2>
    
    <figure>
        <img src="images/tokyo.jpg" 
             alt="東京鐵塔" 
             width="400"
             loading="lazy">
        <figcaption>東京鐵塔的夜景</figcaption>
    </figure>
    
    <figure>
        <img src="images/kyoto.jpg" 
             alt="京都清水寺" 
             width="400"
             loading="lazy">
        <figcaption>京都清水寺的櫻花季</figcaption>
    </figure>
    
    <figure>
        <img src="images/osaka.jpg" 
             alt="大阪城" 
             width="400"
             loading="lazy">
        <figcaption>大阪城堡</figcaption>
    </figure>
    
    <p><a href="index.html">返回首頁</a></p>
</body>
</html>
```

## 🎵 音訊標籤

HTML5 提供 `<audio>` 標籤來播放音訊。

### 基本語法

```html
<audio src="music.mp3" controls>
    您的瀏覽器不支援音訊播放。
</audio>
```

### 完整範例

```html
<audio controls autoplay loop>
    <source src="music.mp3" type="audio/mpeg">
    <source src="music.ogg" type="audio/ogg">
    您的瀏覽器不支援音訊播放。
</audio>
```

### 音訊屬性

| 屬性 | 說明 |
|------|------|
| `controls` | 顯示播放控制介面 |
| `autoplay` | 自動播放 |
| `loop` | 循環播放 |
| `muted` | 靜音 |
| `preload` | 預載設定（`auto`、`metadata`、`none`） |

### 範例

```html
<h3>背景音樂</h3>
<audio controls loop>
    <source src="bgm.mp3" type="audio/mpeg">
    <source src="bgm.wav" type="audio/wav">
    您的瀏覽器不支援音訊播放功能。
</audio>
```

## 🎬 視訊標籤

HTML5 提供 `<video>` 標籤來播放視訊。

### 基本語法

```html
<video src="movie.mp4" controls width="640" height="360">
    您的瀏覽器不支援視訊播放。
</video>
```

### 完整範例

```html
<video controls width="640" height="360" poster="thumbnail.jpg">
    <source src="movie.mp4" type="video/mp4">
    <source src="movie.webm" type="video/webm">
    <source src="movie.ogg" type="video/ogg">
    您的瀏覽器不支援視訊播放。
</video>
```

### 視訊屬性

| 屬性 | 說明 |
|------|------|
| `controls` | 顯示播放控制介面 |
| `autoplay` | 自動播放 |
| `loop` | 循環播放 |
| `muted` | 靜音 |
| `poster` | 視訊封面圖片 |
| `preload` | 預載設定 |
| `width` / `height` | 寬度和高度 |

### 範例

```html
<h3>教學影片</h3>
<video controls width="800" poster="video-cover.jpg">
    <source src="tutorial.mp4" type="video/mp4">
    <source src="tutorial.webm" type="video/webm">
    <track src="subtitles-zh.vtt" kind="subtitles" srclang="zh" label="繁體中文">
    <track src="subtitles-en.vtt" kind="subtitles" srclang="en" label="English">
    您的瀏覽器不支援視訊播放功能。
</video>
```

## 🎞️ 嵌入 YouTube 影片

```html
<iframe width="560" 
        height="315" 
        src="https://www.youtube.com/embed/VIDEO_ID" 
        title="YouTube video player" 
        frameborder="0" 
        allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" 
        allowfullscreen>
</iframe>
```

**取得 YouTube 嵌入代碼：**
1. 開啟 YouTube 影片
2. 點擊「分享」
3. 選擇「嵌入」
4. 複製代碼

## 💻 實作練習 2：多媒體展示頁面

```html
<!DOCTYPE html>
<html lang="zh-TW">
<head>
    <meta charset="UTF-8">
    <title>多媒體展示</title>
</head>
<body>
    <h1>多媒體內容展示</h1>
    
    <section>
        <h2>圖片展示</h2>
        <figure>
            <img src="images/landscape.jpg" 
                 alt="美麗的風景" 
                 width="600"
                 loading="lazy">
            <figcaption>山間的美麗風景</figcaption>
        </figure>
    </section>
    
    <section>
        <h2>音訊播放</h2>
        <audio controls>
            <source src="audio/song.mp3" type="audio/mpeg">
            <source src="audio/song.ogg" type="audio/ogg">
            您的瀏覽器不支援音訊播放。
        </audio>
    </section>
    
    <section>
        <h2>視訊播放</h2>
        <video controls width="640" poster="images/video-poster.jpg">
            <source src="videos/demo.mp4" type="video/mp4">
            <source src="videos/demo.webm" type="video/webm">
            您的瀏覽器不支援視訊播放。
        </video>
    </section>
    
    <section>
        <h2>YouTube 影片</h2>
        <iframe width="560" 
                height="315" 
                src="https://www.youtube.com/embed/dQw4w9WgXcQ" 
                title="YouTube 影片" 
                frameborder="0" 
                allowfullscreen>
        </iframe>
    </section>
</body>
</html>
```

## 🌐 響應式圖片

### 使用 srcset 屬性

針對不同螢幕提供不同尺寸的圖片：

```html
<img src="small.jpg"
     srcset="small.jpg 300w,
             medium.jpg 600w,
             large.jpg 1200w"
     sizes="(max-width: 600px) 300px,
            (max-width: 1200px) 600px,
            1200px"
     alt="響應式圖片">
```

### 使用 picture 元素

```html
<picture>
    <source media="(max-width: 600px)" srcset="small.jpg">
    <source media="(max-width: 1200px)" srcset="medium.jpg">
    <img src="large.jpg" alt="響應式圖片">
</picture>
```

## 🎯 圖片格式選擇

| 格式 | 特點 | 適用場景 |
|------|------|----------|
| **JPEG** | 高壓縮率，不支援透明 | 照片、複雜圖像 |
| **PNG** | 支援透明，檔案較大 | 標誌、圖示、需要透明的圖片 |
| **GIF** | 支援動畫，顏色限制 | 簡單動畫 |
| **WebP** | 現代格式，壓縮率高 | 現代瀏覽器的所有圖片 |
| **SVG** | 向量圖形，可縮放 | 圖示、標誌、簡單圖形 |

## 📝 本課重點回顧

- ✅ 使用 `<img>` 標籤插入圖片，`src` 和 `alt` 是必要屬性
- ✅ `alt` 提供替代文字，對 SEO 和無障礙很重要
- ✅ `loading="lazy"` 可以延遲載入圖片，提升效能
- ✅ 使用 `<figure>` 和 `<figcaption>` 為圖片加上說明
- ✅ `<audio>` 用於播放音訊，`<video>` 用於播放視訊
- ✅ `controls` 屬性顯示播放控制介面
- ✅ 提供多種格式的媒體檔案，確保瀏覽器相容性
- ✅ 使用 `<iframe>` 嵌入 YouTube 等外部影片

## 🎯 課後練習

1. **基礎練習**：建立個人相簿頁面
   - 至少放入 6 張圖片
   - 每張圖片都使用 `<figure>` 和 `<figcaption>`
   - 為所有圖片加上有意義的 `alt` 文字
   - 使用 `loading="lazy"` 優化載入

2. **進階挑戰**：建立多媒體作品集
   - 包含至少 3 個區塊：圖片、音訊、視訊
   - 圖片區：建立一個小型相簿（至少 4 張圖）
   - 音訊區：放入音樂播放器
   - 視訊區：嵌入一個 YouTube 影片
   - 為每個區塊加上標題和說明

3. **實戰練習**：建立產品展示頁
   - 展示一個產品（手機、相機、書籍等）
   - 包含多張產品圖片
   - 加入產品介紹影片
   - 每張圖片都可以點擊放大查看
   - 使用響應式圖片技術

## 🔗 下一課預告

在下一課中，我們將學習如何建立表格，用來展示結構化的數據和資訊！

---

[← 上一課：列表和連結](./03-lists-links.md) | [返回目錄](../README.md) | [下一課：表格 →](./05-tables.md)
