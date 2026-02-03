(globalThis.TURBOPACK || (globalThis.TURBOPACK = [])).push([typeof document === "object" ? document.currentScript : undefined,
"[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/match-result/page.tsx [app-client] (ecmascript)", ((__turbopack_context__) => {
"use strict";

__turbopack_context__.s([
    "default",
    ()=>MatchResultPage
]);
var __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$build$2f$polyfills$2f$process$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__ = /*#__PURE__*/ __turbopack_context__.i("[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /node_modules/next/dist/build/polyfills/process.js [app-client] (ecmascript)");
var __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__ = __turbopack_context__.i("[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /node_modules/next/dist/compiled/react/jsx-dev-runtime.js [app-client] (ecmascript)");
var __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$index$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__ = __turbopack_context__.i("[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /node_modules/next/dist/compiled/react/index.js [app-client] (ecmascript)");
var __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$client$2f$app$2d$dir$2f$link$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__ = __turbopack_context__.i("[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /node_modules/next/dist/client/app-dir/link.js [app-client] (ecmascript)");
var __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$react$2d$markdown$2f$lib$2f$index$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__$3c$export__Markdown__as__default$3e$__ = __turbopack_context__.i("[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /node_modules/react-markdown/lib/index.js [app-client] (ecmascript) <export Markdown as default>");
;
var _s = __turbopack_context__.k.signature();
"use client";
;
;
;
;
function MatchResultPage() {
    _s();
    const [myCat, setMyCat] = (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$index$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["useState"])(null);
    const [matches, setMatches] = (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$index$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["useState"])([]);
    const [matchIdx, setMatchIdx] = (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$index$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["useState"])(0);
    const [review, setReview] = (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$index$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["useState"])("");
    const [userEmail, setUserEmail] = (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$index$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["useState"])("");
    const [loading, setLoading] = (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$index$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["useState"])(true);
    const [progress, setProgress] = (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$index$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["useState"])(0);
    const [loadingStage, setLoadingStage] = (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$index$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["useState"])("初始化...");
    const [kittenImageUrl, setKittenImageUrl] = (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$index$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["useState"])("");
    const [generatingOffspring, setGeneratingOffspring] = (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$index$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["useState"])(false);
    (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$index$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["useEffect"])({
        "MatchResultPage.useEffect": ()=>{
            const token = localStorage.getItem("auth_token") || "";
            if (!token) {
                window.location.href = "/login";
                return;
            }
            const API_BASE = ("TURBOPACK compile-time value", "http://localhost:5050") || "http://localhost:5050";
            // 模擬載入進度
            const progressInterval = setInterval({
                "MatchResultPage.useEffect.progressInterval": ()=>{
                    setProgress({
                        "MatchResultPage.useEffect.progressInterval": (prev)=>{
                            if (prev >= 90) return prev; // 停在 90% 等待實際數據
                            return prev + Math.random() * 15;
                        }
                    }["MatchResultPage.useEffect.progressInterval"]);
                }
            }["MatchResultPage.useEffect.progressInterval"], 300);
            ({
                "MatchResultPage.useEffect": async ()=>{
                    try {
                        setLoadingStage("正在連接伺服器...");
                        setProgress(10);
                        const res = await fetch(`${API_BASE}/api/match-result`, {
                            headers: {
                                Authorization: `Bearer ${token}`
                            }
                        });
                        setLoadingStage("正在接收數據...");
                        setProgress(50);
                        const json = await res.json().catch({
                            "MatchResultPage.useEffect": ()=>({})
                        }["MatchResultPage.useEffect"]);
                        if (!res.ok) {
                            clearInterval(progressInterval);
                            alert(json?.message || "Failed to load match result.");
                            return;
                        }
                        setLoadingStage("正在分析配對結果...");
                        setProgress(70);
                        setUserEmail(json?.user?.email || "");
                        setMyCat(json?.your_feline || null);
                        const MAX_CHARS = 600;
                        let text = json?.match_review_md || json?.match_review || "";
                        if (text.length > MAX_CHARS) {
                            text = text.slice(0, MAX_CHARS) + "…";
                        }
                        setReview(text);
                        setLoadingStage("正在準備顯示...");
                        setProgress(90);
                        setMatches(Array.isArray(json?.potential_matches) ? json.potential_matches : []);
                        setMatchIdx(0);
                        // 🎨 設定小貓圖片 URL
                        if (json?.kitten_image_url) {
                            setKittenImageUrl(json.kitten_image_url);
                        }
                        // 完成載入
                        setTimeout({
                            "MatchResultPage.useEffect": ()=>{
                                setProgress(100);
                                setLoadingStage("完成！");
                                setTimeout({
                                    "MatchResultPage.useEffect": ()=>{
                                        setLoading(false);
                                        clearInterval(progressInterval);
                                    }
                                }["MatchResultPage.useEffect"], 300);
                            }
                        }["MatchResultPage.useEffect"], 200);
                    } catch (err) {
                        clearInterval(progressInterval);
                        console.error(err);
                        alert("Something went wrong loading match data.");
                        setLoading(false);
                    }
                }
            })["MatchResultPage.useEffect"]();
            return ({
                "MatchResultPage.useEffect": ()=>clearInterval(progressInterval)
            })["MatchResultPage.useEffect"];
        }
    }["MatchResultPage.useEffect"], []);
    // Generate offspring when match changes
    (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$index$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["useEffect"])({
        "MatchResultPage.useEffect": ()=>{
            const currentMatch = matches.length ? matches[Math.min(matchIdx, matches.length - 1)] : null;
            const matchCatId = currentMatch?.cat?.id;
            if (!matchCatId || loading) return;
            const token = localStorage.getItem("auth_token") || "";
            if (!token) return;
            const API_BASE = ("TURBOPACK compile-time value", "http://localhost:5050") || "http://localhost:5050";
            const generateOffspring = {
                "MatchResultPage.useEffect.generateOffspring": async ()=>{
                    setGeneratingOffspring(true);
                    setKittenImageUrl(""); // Clear so we don't show previous pair's image
                    try {
                        const res = await fetch(`${API_BASE}/api/generate-offspring`, {
                            method: "POST",
                            headers: {
                                "Content-Type": "application/json",
                                Authorization: `Bearer ${token}`
                            },
                            body: JSON.stringify({
                                match_cat_id: matchCatId
                            })
                        });
                        const json = await res.json().catch({
                            "MatchResultPage.useEffect.generateOffspring": ()=>({})
                        }["MatchResultPage.useEffect.generateOffspring"]);
                        if (res.ok && json.status === "ok") {
                            // Update review
                            const MAX_CHARS = 600;
                            let text = json.review_md || "";
                            if (text.length > MAX_CHARS) {
                                text = text.slice(0, MAX_CHARS) + "…";
                            }
                            setReview(text);
                            // Update kitten image
                            if (json.kitten_image_url) {
                                setKittenImageUrl(json.kitten_image_url);
                            }
                        } else {
                            console.error("Failed to generate offspring:", json?.message);
                        }
                    } catch (err) {
                        console.error("Error generating offspring:", err);
                    } finally{
                        setGeneratingOffspring(false);
                    }
                }
            }["MatchResultPage.useEffect.generateOffspring"];
            generateOffspring();
        }
    }["MatchResultPage.useEffect"], [
        matchIdx,
        matches,
        loading
    ]);
    const handleBack = ()=>window.history.back();
    const API_BASE = ("TURBOPACK compile-time value", "http://localhost:5050") || "http://localhost:5050";
    const currentMatch = matches.length ? matches[Math.min(matchIdx, matches.length - 1)] : null;
    const matchCat = currentMatch?.cat || null;
    const nextMatch = ()=>{
        if (!matches.length) return;
        setMatchIdx((i)=>(i + 1) % matches.length);
    };
    const prevMatch = ()=>{
        if (!matches.length) return;
        setMatchIdx((i)=>(i - 1 + matches.length) % matches.length);
    };
    if (loading) {
        return /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("div", {
            className: "loading-page",
            children: /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("div", {
                className: "loading-container",
                children: [
                    /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("div", {
                        className: "spinner"
                    }, void 0, false, {
                        fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/match-result/page.tsx",
                        lineNumber: 191,
                        columnNumber: 11
                    }, this),
                    /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("h2", {
                        style: {
                            marginBottom: '8px',
                            color: '#333'
                        },
                        children: "載入配對結果中..."
                    }, void 0, false, {
                        fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/match-result/page.tsx",
                        lineNumber: 192,
                        columnNumber: 11
                    }, this),
                    /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("p", {
                        style: {
                            marginBottom: '24px',
                            color: '#777'
                        },
                        children: loadingStage
                    }, void 0, false, {
                        fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/match-result/page.tsx",
                        lineNumber: 193,
                        columnNumber: 11
                    }, this),
                    /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("div", {
                        className: "progress-bar-container",
                        children: /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("div", {
                            className: "progress-bar",
                            style: {
                                width: `${progress}%`
                            }
                        }, void 0, false, {
                            fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/match-result/page.tsx",
                            lineNumber: 196,
                            columnNumber: 13
                        }, this)
                    }, void 0, false, {
                        fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/match-result/page.tsx",
                        lineNumber: 195,
                        columnNumber: 11
                    }, this),
                    /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("p", {
                        style: {
                            marginTop: '12px',
                            fontSize: '0.9rem',
                            color: '#999'
                        },
                        children: [
                            Math.round(progress),
                            "% 完成"
                        ]
                    }, void 0, true, {
                        fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/match-result/page.tsx",
                        lineNumber: 199,
                        columnNumber: 11
                    }, this)
                ]
            }, void 0, true, {
                fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/match-result/page.tsx",
                lineNumber: 190,
                columnNumber: 9
            }, this)
        }, void 0, false, {
            fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/match-result/page.tsx",
            lineNumber: 189,
            columnNumber: 7
        }, this);
    }
    return /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("div", {
        className: "match-result-page",
        children: [
            /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("header", {
                className: "header",
                children: [
                    /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])(__TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$client$2f$app$2d$dir$2f$link$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["default"], {
                        href: "/",
                        className: "back-btn",
                        children: "← Back to Home"
                    }, void 0, false, {
                        fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/match-result/page.tsx",
                        lineNumber: 210,
                        columnNumber: 9
                    }, this),
                    /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("div", {
                        className: "logo",
                        children: [
                            "🐾 ",
                            /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("span", {
                                children: "PawMatch"
                            }, void 0, false, {
                                fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/match-result/page.tsx",
                                lineNumber: 215,
                                columnNumber: 14
                            }, this)
                        ]
                    }, void 0, true, {
                        fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/match-result/page.tsx",
                        lineNumber: 214,
                        columnNumber: 9
                    }, this),
                    /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("div", {
                        className: "head-titles",
                        children: [
                            /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("h1", {
                                children: "Feline Compatibility Analysis"
                            }, void 0, false, {
                                fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/match-result/page.tsx",
                                lineNumber: 219,
                                columnNumber: 11
                            }, this),
                            /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("p", {
                                children: "Find the purrfect partner for your beloved cat 💞"
                            }, void 0, false, {
                                fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/match-result/page.tsx",
                                lineNumber: 220,
                                columnNumber: 11
                            }, this)
                        ]
                    }, void 0, true, {
                        fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/match-result/page.tsx",
                        lineNumber: 218,
                        columnNumber: 9
                    }, this)
                ]
            }, void 0, true, {
                fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/match-result/page.tsx",
                lineNumber: 209,
                columnNumber: 7
            }, this),
            /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("main", {
                children: [
                    /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("div", {
                        className: "top-row",
                        children: [
                            /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("section", {
                                className: "card",
                                children: [
                                    /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("h2", {
                                        children: "Your Feline"
                                    }, void 0, false, {
                                        fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/match-result/page.tsx",
                                        lineNumber: 227,
                                        columnNumber: 13
                                    }, this),
                                    myCat ? /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("div", {
                                        className: "cat-info",
                                        children: [
                                            /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("div", {
                                                className: "cat-photo",
                                                children: /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("img", {
                                                    src: myCat.photo_path ? `${API_BASE}${myCat.photo_path}` : "/images/your_cat.jpg",
                                                    alt: myCat.name
                                                }, void 0, false, {
                                                    fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/match-result/page.tsx",
                                                    lineNumber: 232,
                                                    columnNumber: 19
                                                }, this)
                                            }, void 0, false, {
                                                fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/match-result/page.tsx",
                                                lineNumber: 231,
                                                columnNumber: 17
                                            }, this),
                                            /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("ul", {
                                                children: [
                                                    /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("li", {
                                                        children: [
                                                            /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("b", {
                                                                children: "Owner:"
                                                            }, void 0, false, {
                                                                fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/match-result/page.tsx",
                                                                lineNumber: 238,
                                                                columnNumber: 23
                                                            }, this),
                                                            " ",
                                                            userEmail || "-"
                                                        ]
                                                    }, void 0, true, {
                                                        fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/match-result/page.tsx",
                                                        lineNumber: 238,
                                                        columnNumber: 19
                                                    }, this),
                                                    /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("li", {
                                                        children: [
                                                            /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("b", {
                                                                children: "Name:"
                                                            }, void 0, false, {
                                                                fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/match-result/page.tsx",
                                                                lineNumber: 239,
                                                                columnNumber: 23
                                                            }, this),
                                                            " ",
                                                            myCat.name
                                                        ]
                                                    }, void 0, true, {
                                                        fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/match-result/page.tsx",
                                                        lineNumber: 239,
                                                        columnNumber: 19
                                                    }, this),
                                                    /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("li", {
                                                        children: [
                                                            /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("b", {
                                                                children: "Breed:"
                                                            }, void 0, false, {
                                                                fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/match-result/page.tsx",
                                                                lineNumber: 240,
                                                                columnNumber: 23
                                                            }, this),
                                                            " ",
                                                            myCat.breed
                                                        ]
                                                    }, void 0, true, {
                                                        fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/match-result/page.tsx",
                                                        lineNumber: 240,
                                                        columnNumber: 19
                                                    }, this),
                                                    /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("li", {
                                                        children: [
                                                            /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("b", {
                                                                children: "Age:"
                                                            }, void 0, false, {
                                                                fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/match-result/page.tsx",
                                                                lineNumber: 241,
                                                                columnNumber: 23
                                                            }, this),
                                                            " ",
                                                            myCat.age
                                                        ]
                                                    }, void 0, true, {
                                                        fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/match-result/page.tsx",
                                                        lineNumber: 241,
                                                        columnNumber: 19
                                                    }, this),
                                                    /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("li", {
                                                        children: [
                                                            /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("b", {
                                                                children: "Gender:"
                                                            }, void 0, false, {
                                                                fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/match-result/page.tsx",
                                                                lineNumber: 242,
                                                                columnNumber: 23
                                                            }, this),
                                                            " ",
                                                            myCat.gender || "-"
                                                        ]
                                                    }, void 0, true, {
                                                        fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/match-result/page.tsx",
                                                        lineNumber: 242,
                                                        columnNumber: 19
                                                    }, this),
                                                    /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("li", {
                                                        children: [
                                                            /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("b", {
                                                                children: "Health:"
                                                            }, void 0, false, {
                                                                fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/match-result/page.tsx",
                                                                lineNumber: 243,
                                                                columnNumber: 23
                                                            }, this),
                                                            " ",
                                                            myCat.health
                                                        ]
                                                    }, void 0, true, {
                                                        fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/match-result/page.tsx",
                                                        lineNumber: 243,
                                                        columnNumber: 19
                                                    }, this),
                                                    /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("li", {
                                                        children: [
                                                            /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("b", {
                                                                children: "Vaccinations:"
                                                            }, void 0, false, {
                                                                fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/match-result/page.tsx",
                                                                lineNumber: 244,
                                                                columnNumber: 23
                                                            }, this),
                                                            " ",
                                                            (myCat.vaccinations || []).join(", ")
                                                        ]
                                                    }, void 0, true, {
                                                        fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/match-result/page.tsx",
                                                        lineNumber: 244,
                                                        columnNumber: 19
                                                    }, this)
                                                ]
                                            }, void 0, true, {
                                                fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/match-result/page.tsx",
                                                lineNumber: 237,
                                                columnNumber: 17
                                            }, this)
                                        ]
                                    }, void 0, true, {
                                        fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/match-result/page.tsx",
                                        lineNumber: 230,
                                        columnNumber: 15
                                    }, this) : /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("p", {
                                        className: "desc",
                                        children: "Loading your cat profile..."
                                    }, void 0, false, {
                                        fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/match-result/page.tsx",
                                        lineNumber: 248,
                                        columnNumber: 15
                                    }, this),
                                    /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("p", {
                                        className: "desc",
                                        children: "Your cat's data helps PawMatch find their best match."
                                    }, void 0, false, {
                                        fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/match-result/page.tsx",
                                        lineNumber: 251,
                                        columnNumber: 13
                                    }, this)
                                ]
                            }, void 0, true, {
                                fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/match-result/page.tsx",
                                lineNumber: 226,
                                columnNumber: 11
                            }, this),
                            /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("section", {
                                className: "card",
                                children: [
                                    /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("h2", {
                                        children: "Potential Match"
                                    }, void 0, false, {
                                        fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/match-result/page.tsx",
                                        lineNumber: 257,
                                        columnNumber: 13
                                    }, this),
                                    /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("div", {
                                        className: "match-info",
                                        children: [
                                            /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("div", {
                                                className: "match-photo",
                                                children: [
                                                    /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("button", {
                                                        className: "arrow left",
                                                        onClick: prevMatch,
                                                        type: "button",
                                                        children: "←"
                                                    }, void 0, false, {
                                                        fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/match-result/page.tsx",
                                                        lineNumber: 260,
                                                        columnNumber: 17
                                                    }, this),
                                                    /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("img", {
                                                        src: matchCat?.photo_path ? `${API_BASE}${matchCat.photo_path}` : "/images/match_cat.jpg",
                                                        alt: "Potential Match"
                                                    }, void 0, false, {
                                                        fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/match-result/page.tsx",
                                                        lineNumber: 261,
                                                        columnNumber: 17
                                                    }, this),
                                                    /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("button", {
                                                        className: "arrow right",
                                                        onClick: nextMatch,
                                                        type: "button",
                                                        children: "→"
                                                    }, void 0, false, {
                                                        fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/match-result/page.tsx",
                                                        lineNumber: 265,
                                                        columnNumber: 17
                                                    }, this)
                                                ]
                                            }, void 0, true, {
                                                fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/match-result/page.tsx",
                                                lineNumber: 259,
                                                columnNumber: 15
                                            }, this),
                                            /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("ul", {
                                                children: matchCat ? /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])(__TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["Fragment"], {
                                                    children: [
                                                        /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("li", {
                                                            children: [
                                                                /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("b", {
                                                                    children: "Score:"
                                                                }, void 0, false, {
                                                                    fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/match-result/page.tsx",
                                                                    lineNumber: 270,
                                                                    columnNumber: 25
                                                                }, this),
                                                                " ",
                                                                currentMatch?.score ?? 0
                                                            ]
                                                        }, void 0, true, {
                                                            fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/match-result/page.tsx",
                                                            lineNumber: 270,
                                                            columnNumber: 21
                                                        }, this),
                                                        /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("li", {
                                                            children: [
                                                                /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("b", {
                                                                    children: "Name:"
                                                                }, void 0, false, {
                                                                    fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/match-result/page.tsx",
                                                                    lineNumber: 271,
                                                                    columnNumber: 25
                                                                }, this),
                                                                " ",
                                                                matchCat.name
                                                            ]
                                                        }, void 0, true, {
                                                            fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/match-result/page.tsx",
                                                            lineNumber: 271,
                                                            columnNumber: 21
                                                        }, this),
                                                        /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("li", {
                                                            children: [
                                                                /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("b", {
                                                                    children: "Breed:"
                                                                }, void 0, false, {
                                                                    fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/match-result/page.tsx",
                                                                    lineNumber: 272,
                                                                    columnNumber: 25
                                                                }, this),
                                                                " ",
                                                                matchCat.breed
                                                            ]
                                                        }, void 0, true, {
                                                            fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/match-result/page.tsx",
                                                            lineNumber: 272,
                                                            columnNumber: 21
                                                        }, this),
                                                        /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("li", {
                                                            children: [
                                                                /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("b", {
                                                                    children: "Age:"
                                                                }, void 0, false, {
                                                                    fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/match-result/page.tsx",
                                                                    lineNumber: 273,
                                                                    columnNumber: 25
                                                                }, this),
                                                                " ",
                                                                matchCat.age,
                                                                " years"
                                                            ]
                                                        }, void 0, true, {
                                                            fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/match-result/page.tsx",
                                                            lineNumber: 273,
                                                            columnNumber: 21
                                                        }, this),
                                                        /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("li", {
                                                            children: [
                                                                /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("b", {
                                                                    children: "Gender:"
                                                                }, void 0, false, {
                                                                    fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/match-result/page.tsx",
                                                                    lineNumber: 274,
                                                                    columnNumber: 25
                                                                }, this),
                                                                " ",
                                                                matchCat.gender || "-"
                                                            ]
                                                        }, void 0, true, {
                                                            fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/match-result/page.tsx",
                                                            lineNumber: 274,
                                                            columnNumber: 21
                                                        }, this),
                                                        /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("li", {
                                                            children: [
                                                                /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("b", {
                                                                    children: "Health:"
                                                                }, void 0, false, {
                                                                    fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/match-result/page.tsx",
                                                                    lineNumber: 275,
                                                                    columnNumber: 25
                                                                }, this),
                                                                " ",
                                                                matchCat.health
                                                            ]
                                                        }, void 0, true, {
                                                            fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/match-result/page.tsx",
                                                            lineNumber: 275,
                                                            columnNumber: 21
                                                        }, this),
                                                        /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("li", {
                                                            children: [
                                                                /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("b", {
                                                                    children: "Vaccinations:"
                                                                }, void 0, false, {
                                                                    fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/match-result/page.tsx",
                                                                    lineNumber: 276,
                                                                    columnNumber: 25
                                                                }, this),
                                                                " ",
                                                                (matchCat.vaccinations || []).join(", ")
                                                            ]
                                                        }, void 0, true, {
                                                            fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/match-result/page.tsx",
                                                            lineNumber: 276,
                                                            columnNumber: 21
                                                        }, this)
                                                    ]
                                                }, void 0, true) : /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("li", {
                                                    children: "No other cats in database yet."
                                                }, void 0, false, {
                                                    fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/match-result/page.tsx",
                                                    lineNumber: 279,
                                                    columnNumber: 19
                                                }, this)
                                            }, void 0, false, {
                                                fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/match-result/page.tsx",
                                                lineNumber: 267,
                                                columnNumber: 15
                                            }, this)
                                        ]
                                    }, void 0, true, {
                                        fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/match-result/page.tsx",
                                        lineNumber: 258,
                                        columnNumber: 13
                                    }, this),
                                    /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("p", {
                                        className: "desc",
                                        children: "Browse more compatible cats analyzed by PawMatch AI using the arrows."
                                    }, void 0, false, {
                                        fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/match-result/page.tsx",
                                        lineNumber: 283,
                                        columnNumber: 13
                                    }, this)
                                ]
                            }, void 0, true, {
                                fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/match-result/page.tsx",
                                lineNumber: 256,
                                columnNumber: 11
                            }, this)
                        ]
                    }, void 0, true, {
                        fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/match-result/page.tsx",
                        lineNumber: 225,
                        columnNumber: 9
                    }, this),
                    /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("section", {
                        className: "match-review",
                        children: [
                            /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("h2", {
                                children: "Match Review"
                            }, void 0, false, {
                                fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/match-result/page.tsx",
                                lineNumber: 290,
                                columnNumber: 11
                            }, this),
                            /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("p", {
                                className: "caption",
                                children: "AI-generated preview — possible kitten appearance 🧡"
                            }, void 0, false, {
                                fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/match-result/page.tsx",
                                lineNumber: 291,
                                columnNumber: 11
                            }, this),
                            /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("div", {
                                className: "kitten-photo",
                                children: generatingOffspring ? /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("div", {
                                    className: "offspring-loading",
                                    children: [
                                        /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("div", {
                                            className: "offspring-spinner"
                                        }, void 0, false, {
                                            fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/match-result/page.tsx",
                                            lineNumber: 298,
                                            columnNumber: 17
                                        }, this),
                                        /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("p", {
                                            children: "Generating AI kitten..."
                                        }, void 0, false, {
                                            fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/match-result/page.tsx",
                                            lineNumber: 299,
                                            columnNumber: 17
                                        }, this)
                                    ]
                                }, void 0, true, {
                                    fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/match-result/page.tsx",
                                    lineNumber: 297,
                                    columnNumber: 15
                                }, this) : /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("img", {
                                    src: kittenImageUrl ? `${API_BASE}${kittenImageUrl}` : "https://images.unsplash.com/photo-1514888286974-6c03e2ca1dba?w=400",
                                    alt: "AI Kitten",
                                    onError: (e)=>{
                                        e.currentTarget.src = "https://images.unsplash.com/photo-1514888286974-6c03e2ca1dba?w=400";
                                    }
                                }, kittenImageUrl || "kitten", false, {
                                    fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/match-result/page.tsx",
                                    lineNumber: 302,
                                    columnNumber: 15
                                }, this)
                            }, void 0, false, {
                                fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/match-result/page.tsx",
                                lineNumber: 295,
                                columnNumber: 11
                            }, this),
                            /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("div", {
                                className: "ai-review",
                                children: generatingOffspring ? /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("p", {
                                    className: "muted",
                                    children: "Generating AI review for this pair..."
                                }, void 0, false, {
                                    fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/match-result/page.tsx",
                                    lineNumber: 320,
                                    columnNumber: 15
                                }, this) : review ? /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])(__TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$react$2d$markdown$2f$lib$2f$index$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__$3c$export__Markdown__as__default$3e$__["default"], {
                                    children: review
                                }, void 0, false, {
                                    fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/match-result/page.tsx",
                                    lineNumber: 324,
                                    columnNumber: 15
                                }, this) : /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("p", {
                                    className: "muted",
                                    children: "AI review is not available yet."
                                }, void 0, false, {
                                    fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/match-result/page.tsx",
                                    lineNumber: 326,
                                    columnNumber: 15
                                }, this)
                            }, void 0, false, {
                                fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/match-result/page.tsx",
                                lineNumber: 318,
                                columnNumber: 11
                            }, this)
                        ]
                    }, void 0, true, {
                        fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/match-result/page.tsx",
                        lineNumber: 289,
                        columnNumber: 9
                    }, this),
                    /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("div", {
                        className: "actions",
                        children: /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("a", {
                            href: "https://docs.google.com/forms/d/e/1FAIpQLScPPwaHDG4b_HV-rFNSyjcdy31ESjHCbuKeIfb7w-Bn292KgQ/viewform",
                            target: "_blank",
                            rel: "noopener noreferrer",
                            className: "share",
                            children: "📤 Share Result"
                        }, void 0, false, {
                            fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/match-result/page.tsx",
                            lineNumber: 334,
                            columnNumber: 13
                        }, this)
                    }, void 0, false, {
                        fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/match-result/page.tsx",
                        lineNumber: 333,
                        columnNumber: 9
                    }, this)
                ]
            }, void 0, true, {
                fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/match-result/page.tsx",
                lineNumber: 224,
                columnNumber: 7
            }, this)
        ]
    }, void 0, true, {
        fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/match-result/page.tsx",
        lineNumber: 208,
        columnNumber: 5
    }, this);
}
_s(MatchResultPage, "ipGmQnj8xPALsXp63FmrXi/53oE=");
_c = MatchResultPage;
var _c;
__turbopack_context__.k.register(_c, "MatchResultPage");
if (typeof globalThis.$RefreshHelpers$ === 'object' && globalThis.$RefreshHelpers !== null) {
    __turbopack_context__.k.registerExports(__turbopack_context__.m, globalThis.$RefreshHelpers$);
}
}),
]);

//# sourceMappingURL=8a251_Ricky_Cat%20Project%20Final_fp_fixed%20_src_app_match-result_page_tsx_b9e085a0._.js.map