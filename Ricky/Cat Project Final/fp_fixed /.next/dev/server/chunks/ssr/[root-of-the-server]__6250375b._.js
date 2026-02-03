module.exports = [
"[externals]/next/dist/compiled/next-server/app-page-turbo.runtime.dev.js [external] (next/dist/compiled/next-server/app-page-turbo.runtime.dev.js, cjs)", ((__turbopack_context__, module, exports) => {

const mod = __turbopack_context__.x("next/dist/compiled/next-server/app-page-turbo.runtime.dev.js", () => require("next/dist/compiled/next-server/app-page-turbo.runtime.dev.js"));

module.exports = mod;
}),
"[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/cat-questionnaire/page.tsx [app-ssr] (ecmascript)", ((__turbopack_context__) => {
"use strict";

__turbopack_context__.s([
    "default",
    ()=>CatQuestionnairePage
]);
var __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$server$2f$route$2d$modules$2f$app$2d$page$2f$vendored$2f$ssr$2f$react$2d$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$ssr$5d$__$28$ecmascript$29$__ = __turbopack_context__.i("[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /node_modules/next/dist/server/route-modules/app-page/vendored/ssr/react-jsx-dev-runtime.js [app-ssr] (ecmascript)");
var __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$server$2f$route$2d$modules$2f$app$2d$page$2f$vendored$2f$ssr$2f$react$2e$js__$5b$app$2d$ssr$5d$__$28$ecmascript$29$__ = __turbopack_context__.i("[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /node_modules/next/dist/server/route-modules/app-page/vendored/ssr/react.js [app-ssr] (ecmascript)");
"use client";
;
;
;
function CatQuestionnairePage() {
    const [vaccines, setVaccines] = (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$server$2f$route$2d$modules$2f$app$2d$page$2f$vendored$2f$ssr$2f$react$2e$js__$5b$app$2d$ssr$5d$__$28$ecmascript$29$__["useState"])([]);
    const [photo, setPhoto] = (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$server$2f$route$2d$modules$2f$app$2d$page$2f$vendored$2f$ssr$2f$react$2e$js__$5b$app$2d$ssr$5d$__$28$ecmascript$29$__["useState"])(null);
    const [email, setEmail] = (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$server$2f$route$2d$modules$2f$app$2d$page$2f$vendored$2f$ssr$2f$react$2e$js__$5b$app$2d$ssr$5d$__$28$ecmascript$29$__["useState"])("");
    const [password, setPassword] = (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$server$2f$route$2d$modules$2f$app$2d$page$2f$vendored$2f$ssr$2f$react$2e$js__$5b$app$2d$ssr$5d$__$28$ecmascript$29$__["useState"])("");
    const [catName, setCatName] = (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$server$2f$route$2d$modules$2f$app$2d$page$2f$vendored$2f$ssr$2f$react$2e$js__$5b$app$2d$ssr$5d$__$28$ecmascript$29$__["useState"])("");
    const [breed, setBreed] = (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$server$2f$route$2d$modules$2f$app$2d$page$2f$vendored$2f$ssr$2f$react$2e$js__$5b$app$2d$ssr$5d$__$28$ecmascript$29$__["useState"])("");
    const [age, setAge] = (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$server$2f$route$2d$modules$2f$app$2d$page$2f$vendored$2f$ssr$2f$react$2e$js__$5b$app$2d$ssr$5d$__$28$ecmascript$29$__["useState"])("");
    const [gender, setGender] = (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$server$2f$route$2d$modules$2f$app$2d$page$2f$vendored$2f$ssr$2f$react$2e$js__$5b$app$2d$ssr$5d$__$28$ecmascript$29$__["useState"])("");
    const [health, setHealth] = (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$server$2f$route$2d$modules$2f$app$2d$page$2f$vendored$2f$ssr$2f$react$2e$js__$5b$app$2d$ssr$5d$__$28$ecmascript$29$__["useState"])("");
    const [loading, setLoading] = (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$server$2f$route$2d$modules$2f$app$2d$page$2f$vendored$2f$ssr$2f$react$2e$js__$5b$app$2d$ssr$5d$__$28$ecmascript$29$__["useState"])(false);
    const handleCheckbox = (v)=>{
        setVaccines((prev)=>prev.includes(v) ? prev.filter((x)=>x !== v) : [
                ...prev,
                v
            ]);
    };
    const handleFileChange = (e)=>{
        if (e.target.files?.[0]) setPhoto(e.target.files[0]);
    };
    const fileToDataUrl = (file)=>new Promise((resolve, reject)=>{
            const reader = new FileReader();
            reader.onload = ()=>resolve(String(reader.result || ""));
            reader.onerror = ()=>reject(new Error("Failed to read file"));
            reader.readAsDataURL(file);
        });
    const handleSubmit = async (e)=>{
        e.preventDefault();
        // ✅ Check email + password
        if (!email) {
            alert("Please enter your email address.");
            return;
        } else if (!/^[^\s@]+@[^\s@]+\.[^\s@]+$/.test(email)) {
            alert("Please enter a valid email address.");
            return;
        }
        if (!password || password.length < 8) {
            alert("Password must be at least 8 characters.");
            return;
        }
        if (!catName || !breed) {
            alert("Please fill in cat name and breed.");
            return;
        }
        if (age === "" || Number.isNaN(Number(age)) || Number(age) < 0) {
            alert("Please enter a valid age.");
            return;
        }
        if (!gender) {
            alert("Please select gender.");
            return;
        }
        if (!health) {
            alert("Please select health condition.");
            return;
        }
        // ✅ Check vaccines
        const required = [
            "FVRCP",
            "Rabies",
            "FeLV",
            "FIP"
        ];
        if (!required.every((v)=>vaccines.includes(v))) {
            alert("All four vaccines (FVRCP, Rabies, FeLV, FIP) are required.");
            return;
        }
        if (!photo) {
            alert("Please upload a photo(Max size: 5 MB).");
            return;
        }
        const sizeMB = photo.size / (1024 * 1024);
        if (sizeMB > 5) {
            alert("Photo size must be less than 5 MB.");
            return;
        }
        try {
            setLoading(true);
            const photo_data_url = photo ? await fileToDataUrl(photo) : "";
            const API_BASE = ("TURBOPACK compile-time value", "http://localhost:5050") || "http://localhost:5050";
            const payload = {
                email,
                password,
                cat_name: catName,
                breed,
                age: Number(age),
                gender,
                health,
                vaccines,
                photo_data_url
            };
            const res = await fetch(`${API_BASE}/api/cat-questionnaire`, {
                method: "POST",
                headers: {
                    "Content-Type": "application/json"
                },
                body: JSON.stringify(payload)
            });
            const json = await res.json().catch(()=>({}));
            if (!res.ok) {
                alert(json?.message || "Registration failed.");
                return;
            }
            localStorage.setItem("auth_token", json.token);
            localStorage.setItem("owner_email", email);
            // optional: store a quick snapshot for UI fallback
            localStorage.setItem("catProfile", JSON.stringify({
                name: catName,
                breed,
                age: String(age),
                temperament: "",
                health,
                vaccinations: vaccines.join(", "),
                photo: json?.cat?.photo_path ? `${API_BASE}${json.cat.photo_path}` : ""
            }));
            alert("✅ Registered successfully!");
            window.location.href = "/match-result";
        } catch (err) {
            console.error(err);
            alert("Something went wrong while submitting.");
        } finally{
            setLoading(false);
        }
    };
    return /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$server$2f$route$2d$modules$2f$app$2d$page$2f$vendored$2f$ssr$2f$react$2d$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$ssr$5d$__$28$ecmascript$29$__["jsxDEV"])("main", {
        className: "cat-page",
        children: /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$server$2f$route$2d$modules$2f$app$2d$page$2f$vendored$2f$ssr$2f$react$2d$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$ssr$5d$__$28$ecmascript$29$__["jsxDEV"])("form", {
            className: "cat-card",
            onSubmit: handleSubmit,
            children: [
                /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$server$2f$route$2d$modules$2f$app$2d$page$2f$vendored$2f$ssr$2f$react$2d$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$ssr$5d$__$28$ecmascript$29$__["jsxDEV"])("h1", {
                    className: "title",
                    children: "🐱 Ethical Feline Registry"
                }, void 0, false, {
                    fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/cat-questionnaire/page.tsx",
                    lineNumber: 145,
                    columnNumber: 9
                }, this),
                /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$server$2f$route$2d$modules$2f$app$2d$page$2f$vendored$2f$ssr$2f$react$2d$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$ssr$5d$__$28$ecmascript$29$__["jsxDEV"])("p", {
                    className: "subtitle",
                    children: "Cat Information Form"
                }, void 0, false, {
                    fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/cat-questionnaire/page.tsx",
                    lineNumber: 146,
                    columnNumber: 9
                }, this),
                /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$server$2f$route$2d$modules$2f$app$2d$page$2f$vendored$2f$ssr$2f$react$2d$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$ssr$5d$__$28$ecmascript$29$__["jsxDEV"])("div", {
                    className: "form-grid",
                    children: [
                        /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$server$2f$route$2d$modules$2f$app$2d$page$2f$vendored$2f$ssr$2f$react$2d$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$ssr$5d$__$28$ecmascript$29$__["jsxDEV"])("div", {
                            className: "group",
                            children: [
                                /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$server$2f$route$2d$modules$2f$app$2d$page$2f$vendored$2f$ssr$2f$react$2d$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$ssr$5d$__$28$ecmascript$29$__["jsxDEV"])("label", {
                                    htmlFor: "catName",
                                    children: "Cat's Name"
                                }, void 0, false, {
                                    fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/cat-questionnaire/page.tsx",
                                    lineNumber: 150,
                                    columnNumber: 13
                                }, this),
                                /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$server$2f$route$2d$modules$2f$app$2d$page$2f$vendored$2f$ssr$2f$react$2d$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$ssr$5d$__$28$ecmascript$29$__["jsxDEV"])("input", {
                                    id: "catName",
                                    type: "text",
                                    placeholder: "e.g. Momo",
                                    value: catName,
                                    onChange: (e)=>setCatName(e.target.value),
                                    required: true,
                                    disabled: loading
                                }, void 0, false, {
                                    fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/cat-questionnaire/page.tsx",
                                    lineNumber: 151,
                                    columnNumber: 13
                                }, this)
                            ]
                        }, void 0, true, {
                            fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/cat-questionnaire/page.tsx",
                            lineNumber: 149,
                            columnNumber: 11
                        }, this),
                        /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$server$2f$route$2d$modules$2f$app$2d$page$2f$vendored$2f$ssr$2f$react$2d$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$ssr$5d$__$28$ecmascript$29$__["jsxDEV"])("div", {
                            className: "group",
                            children: [
                                /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$server$2f$route$2d$modules$2f$app$2d$page$2f$vendored$2f$ssr$2f$react$2d$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$ssr$5d$__$28$ecmascript$29$__["jsxDEV"])("label", {
                                    htmlFor: "breed",
                                    children: "Breed"
                                }, void 0, false, {
                                    fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/cat-questionnaire/page.tsx",
                                    lineNumber: 162,
                                    columnNumber: 13
                                }, this),
                                /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$server$2f$route$2d$modules$2f$app$2d$page$2f$vendored$2f$ssr$2f$react$2d$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$ssr$5d$__$28$ecmascript$29$__["jsxDEV"])("select", {
                                    id: "breed",
                                    value: breed,
                                    onChange: (e)=>setBreed(e.target.value),
                                    required: true,
                                    disabled: loading,
                                    children: [
                                        /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$server$2f$route$2d$modules$2f$app$2d$page$2f$vendored$2f$ssr$2f$react$2d$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$ssr$5d$__$28$ecmascript$29$__["jsxDEV"])("option", {
                                            value: "",
                                            children: "Select Breed"
                                        }, void 0, false, {
                                            fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/cat-questionnaire/page.tsx",
                                            lineNumber: 170,
                                            columnNumber: 15
                                        }, this),
                                        /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$server$2f$route$2d$modules$2f$app$2d$page$2f$vendored$2f$ssr$2f$react$2d$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$ssr$5d$__$28$ecmascript$29$__["jsxDEV"])("option", {
                                            children: "British Shorthair"
                                        }, void 0, false, {
                                            fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/cat-questionnaire/page.tsx",
                                            lineNumber: 171,
                                            columnNumber: 15
                                        }, this),
                                        /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$server$2f$route$2d$modules$2f$app$2d$page$2f$vendored$2f$ssr$2f$react$2d$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$ssr$5d$__$28$ecmascript$29$__["jsxDEV"])("option", {
                                            children: "Persian"
                                        }, void 0, false, {
                                            fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/cat-questionnaire/page.tsx",
                                            lineNumber: 172,
                                            columnNumber: 15
                                        }, this),
                                        /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$server$2f$route$2d$modules$2f$app$2d$page$2f$vendored$2f$ssr$2f$react$2d$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$ssr$5d$__$28$ecmascript$29$__["jsxDEV"])("option", {
                                            children: "MaineCoon"
                                        }, void 0, false, {
                                            fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/cat-questionnaire/page.tsx",
                                            lineNumber: 173,
                                            columnNumber: 15
                                        }, this),
                                        /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$server$2f$route$2d$modules$2f$app$2d$page$2f$vendored$2f$ssr$2f$react$2d$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$ssr$5d$__$28$ecmascript$29$__["jsxDEV"])("option", {
                                            children: "Ragdoll"
                                        }, void 0, false, {
                                            fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/cat-questionnaire/page.tsx",
                                            lineNumber: 174,
                                            columnNumber: 15
                                        }, this)
                                    ]
                                }, void 0, true, {
                                    fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/cat-questionnaire/page.tsx",
                                    lineNumber: 163,
                                    columnNumber: 13
                                }, this)
                            ]
                        }, void 0, true, {
                            fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/cat-questionnaire/page.tsx",
                            lineNumber: 161,
                            columnNumber: 11
                        }, this)
                    ]
                }, void 0, true, {
                    fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/cat-questionnaire/page.tsx",
                    lineNumber: 148,
                    columnNumber: 9
                }, this),
                /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$server$2f$route$2d$modules$2f$app$2d$page$2f$vendored$2f$ssr$2f$react$2d$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$ssr$5d$__$28$ecmascript$29$__["jsxDEV"])("div", {
                    className: "group",
                    children: [
                        /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$server$2f$route$2d$modules$2f$app$2d$page$2f$vendored$2f$ssr$2f$react$2d$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$ssr$5d$__$28$ecmascript$29$__["jsxDEV"])("label", {
                            htmlFor: "ownerEmail",
                            children: [
                                "Owner Email Address ",
                                /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$server$2f$route$2d$modules$2f$app$2d$page$2f$vendored$2f$ssr$2f$react$2d$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$ssr$5d$__$28$ecmascript$29$__["jsxDEV"])("span", {
                                    style: {
                                        color: "red"
                                    },
                                    children: "*"
                                }, void 0, false, {
                                    fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/cat-questionnaire/page.tsx",
                                    lineNumber: 181,
                                    columnNumber: 59
                                }, this)
                            ]
                        }, void 0, true, {
                            fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/cat-questionnaire/page.tsx",
                            lineNumber: 181,
                            columnNumber: 11
                        }, this),
                        /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$server$2f$route$2d$modules$2f$app$2d$page$2f$vendored$2f$ssr$2f$react$2d$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$ssr$5d$__$28$ecmascript$29$__["jsxDEV"])("input", {
                            id: "ownerEmail",
                            type: "email",
                            placeholder: "you@example.com",
                            value: email,
                            onChange: (e)=>setEmail(e.target.value),
                            required: true,
                            disabled: loading
                        }, void 0, false, {
                            fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/cat-questionnaire/page.tsx",
                            lineNumber: 182,
                            columnNumber: 11
                        }, this)
                    ]
                }, void 0, true, {
                    fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/cat-questionnaire/page.tsx",
                    lineNumber: 180,
                    columnNumber: 9
                }, this),
                /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$server$2f$route$2d$modules$2f$app$2d$page$2f$vendored$2f$ssr$2f$react$2d$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$ssr$5d$__$28$ecmascript$29$__["jsxDEV"])("div", {
                    className: "group",
                    children: [
                        /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$server$2f$route$2d$modules$2f$app$2d$page$2f$vendored$2f$ssr$2f$react$2d$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$ssr$5d$__$28$ecmascript$29$__["jsxDEV"])("label", {
                            htmlFor: "ownerPassword",
                            children: [
                                "Password ",
                                /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$server$2f$route$2d$modules$2f$app$2d$page$2f$vendored$2f$ssr$2f$react$2d$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$ssr$5d$__$28$ecmascript$29$__["jsxDEV"])("span", {
                                    style: {
                                        color: "red"
                                    },
                                    children: "*"
                                }, void 0, false, {
                                    fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/cat-questionnaire/page.tsx",
                                    lineNumber: 194,
                                    columnNumber: 51
                                }, this)
                            ]
                        }, void 0, true, {
                            fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/cat-questionnaire/page.tsx",
                            lineNumber: 194,
                            columnNumber: 11
                        }, this),
                        /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$server$2f$route$2d$modules$2f$app$2d$page$2f$vendored$2f$ssr$2f$react$2d$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$ssr$5d$__$28$ecmascript$29$__["jsxDEV"])("input", {
                            id: "ownerPassword",
                            type: "password",
                            placeholder: "At least 8 characters",
                            value: password,
                            onChange: (e)=>setPassword(e.target.value),
                            required: true,
                            disabled: loading
                        }, void 0, false, {
                            fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/cat-questionnaire/page.tsx",
                            lineNumber: 195,
                            columnNumber: 11
                        }, this)
                    ]
                }, void 0, true, {
                    fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/cat-questionnaire/page.tsx",
                    lineNumber: 193,
                    columnNumber: 9
                }, this),
                /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$server$2f$route$2d$modules$2f$app$2d$page$2f$vendored$2f$ssr$2f$react$2d$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$ssr$5d$__$28$ecmascript$29$__["jsxDEV"])("div", {
                    className: "form-grid",
                    children: [
                        /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$server$2f$route$2d$modules$2f$app$2d$page$2f$vendored$2f$ssr$2f$react$2d$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$ssr$5d$__$28$ecmascript$29$__["jsxDEV"])("div", {
                            className: "group",
                            children: [
                                /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$server$2f$route$2d$modules$2f$app$2d$page$2f$vendored$2f$ssr$2f$react$2d$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$ssr$5d$__$28$ecmascript$29$__["jsxDEV"])("label", {
                                    children: "Age (Years)"
                                }, void 0, false, {
                                    fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/cat-questionnaire/page.tsx",
                                    lineNumber: 208,
                                    columnNumber: 13
                                }, this),
                                /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$server$2f$route$2d$modules$2f$app$2d$page$2f$vendored$2f$ssr$2f$react$2d$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$ssr$5d$__$28$ecmascript$29$__["jsxDEV"])("input", {
                                    type: "number",
                                    min: "0",
                                    required: true,
                                    value: age,
                                    onChange: (e)=>setAge(e.target.value),
                                    disabled: loading
                                }, void 0, false, {
                                    fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/cat-questionnaire/page.tsx",
                                    lineNumber: 209,
                                    columnNumber: 13
                                }, this)
                            ]
                        }, void 0, true, {
                            fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/cat-questionnaire/page.tsx",
                            lineNumber: 207,
                            columnNumber: 11
                        }, this),
                        /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$server$2f$route$2d$modules$2f$app$2d$page$2f$vendored$2f$ssr$2f$react$2d$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$ssr$5d$__$28$ecmascript$29$__["jsxDEV"])("div", {
                            className: "group",
                            children: [
                                /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$server$2f$route$2d$modules$2f$app$2d$page$2f$vendored$2f$ssr$2f$react$2d$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$ssr$5d$__$28$ecmascript$29$__["jsxDEV"])("label", {
                                    children: "Gender"
                                }, void 0, false, {
                                    fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/cat-questionnaire/page.tsx",
                                    lineNumber: 219,
                                    columnNumber: 13
                                }, this),
                                /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$server$2f$route$2d$modules$2f$app$2d$page$2f$vendored$2f$ssr$2f$react$2d$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$ssr$5d$__$28$ecmascript$29$__["jsxDEV"])("div", {
                                    className: "radio-inline",
                                    children: [
                                        /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$server$2f$route$2d$modules$2f$app$2d$page$2f$vendored$2f$ssr$2f$react$2d$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$ssr$5d$__$28$ecmascript$29$__["jsxDEV"])("label", {
                                            children: [
                                                /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$server$2f$route$2d$modules$2f$app$2d$page$2f$vendored$2f$ssr$2f$react$2d$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$ssr$5d$__$28$ecmascript$29$__["jsxDEV"])("input", {
                                                    type: "radio",
                                                    name: "gender",
                                                    value: "Male",
                                                    checked: gender === "Male",
                                                    onChange: (e)=>setGender(e.target.value),
                                                    required: true,
                                                    disabled: loading
                                                }, void 0, false, {
                                                    fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/cat-questionnaire/page.tsx",
                                                    lineNumber: 221,
                                                    columnNumber: 22
                                                }, this),
                                                " Male"
                                            ]
                                        }, void 0, true, {
                                            fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/cat-questionnaire/page.tsx",
                                            lineNumber: 221,
                                            columnNumber: 15
                                        }, this),
                                        /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$server$2f$route$2d$modules$2f$app$2d$page$2f$vendored$2f$ssr$2f$react$2d$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$ssr$5d$__$28$ecmascript$29$__["jsxDEV"])("label", {
                                            children: [
                                                /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$server$2f$route$2d$modules$2f$app$2d$page$2f$vendored$2f$ssr$2f$react$2d$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$ssr$5d$__$28$ecmascript$29$__["jsxDEV"])("input", {
                                                    type: "radio",
                                                    name: "gender",
                                                    value: "Female",
                                                    checked: gender === "Female",
                                                    onChange: (e)=>setGender(e.target.value),
                                                    required: true,
                                                    disabled: loading
                                                }, void 0, false, {
                                                    fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/cat-questionnaire/page.tsx",
                                                    lineNumber: 222,
                                                    columnNumber: 22
                                                }, this),
                                                " Female"
                                            ]
                                        }, void 0, true, {
                                            fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/cat-questionnaire/page.tsx",
                                            lineNumber: 222,
                                            columnNumber: 15
                                        }, this)
                                    ]
                                }, void 0, true, {
                                    fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/cat-questionnaire/page.tsx",
                                    lineNumber: 220,
                                    columnNumber: 13
                                }, this)
                            ]
                        }, void 0, true, {
                            fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/cat-questionnaire/page.tsx",
                            lineNumber: 218,
                            columnNumber: 11
                        }, this)
                    ]
                }, void 0, true, {
                    fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/cat-questionnaire/page.tsx",
                    lineNumber: 206,
                    columnNumber: 9
                }, this),
                /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$server$2f$route$2d$modules$2f$app$2d$page$2f$vendored$2f$ssr$2f$react$2d$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$ssr$5d$__$28$ecmascript$29$__["jsxDEV"])("div", {
                    className: "group",
                    children: [
                        /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$server$2f$route$2d$modules$2f$app$2d$page$2f$vendored$2f$ssr$2f$react$2d$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$ssr$5d$__$28$ecmascript$29$__["jsxDEV"])("label", {
                            children: "Health Condition"
                        }, void 0, false, {
                            fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/cat-questionnaire/page.tsx",
                            lineNumber: 228,
                            columnNumber: 11
                        }, this),
                        /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$server$2f$route$2d$modules$2f$app$2d$page$2f$vendored$2f$ssr$2f$react$2d$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$ssr$5d$__$28$ecmascript$29$__["jsxDEV"])("div", {
                            className: "radio-row",
                            children: [
                                "Healthy",
                                "Excellence Condition",
                                "Minor Issues",
                                "Previous Illness",
                                "Ongoing Condition",
                                "Disabled"
                            ].map((h)=>/*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$server$2f$route$2d$modules$2f$app$2d$page$2f$vendored$2f$ssr$2f$react$2d$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$ssr$5d$__$28$ecmascript$29$__["jsxDEV"])("label", {
                                    children: [
                                        /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$server$2f$route$2d$modules$2f$app$2d$page$2f$vendored$2f$ssr$2f$react$2d$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$ssr$5d$__$28$ecmascript$29$__["jsxDEV"])("input", {
                                            type: "radio",
                                            name: "health",
                                            value: h,
                                            checked: health === h,
                                            onChange: (e)=>setHealth(e.target.value),
                                            required: true,
                                            disabled: loading
                                        }, void 0, false, {
                                            fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/cat-questionnaire/page.tsx",
                                            lineNumber: 239,
                                            columnNumber: 17
                                        }, this),
                                        h
                                    ]
                                }, h, true, {
                                    fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/cat-questionnaire/page.tsx",
                                    lineNumber: 238,
                                    columnNumber: 15
                                }, this))
                        }, void 0, false, {
                            fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/cat-questionnaire/page.tsx",
                            lineNumber: 229,
                            columnNumber: 11
                        }, this)
                    ]
                }, void 0, true, {
                    fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/cat-questionnaire/page.tsx",
                    lineNumber: 227,
                    columnNumber: 9
                }, this),
                /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$server$2f$route$2d$modules$2f$app$2d$page$2f$vendored$2f$ssr$2f$react$2d$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$ssr$5d$__$28$ecmascript$29$__["jsxDEV"])("div", {
                    className: "group",
                    children: [
                        /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$server$2f$route$2d$modules$2f$app$2d$page$2f$vendored$2f$ssr$2f$react$2d$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$ssr$5d$__$28$ecmascript$29$__["jsxDEV"])("label", {
                            children: "Vaccination Record"
                        }, void 0, false, {
                            fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/cat-questionnaire/page.tsx",
                            lineNumber: 255,
                            columnNumber: 11
                        }, this),
                        /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$server$2f$route$2d$modules$2f$app$2d$page$2f$vendored$2f$ssr$2f$react$2d$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$ssr$5d$__$28$ecmascript$29$__["jsxDEV"])("p", {
                            className: "warning",
                            children: "⚠️All four core vaccines (FVRCP, Rabies, FeLV, FIP) are required before registration."
                        }, void 0, false, {
                            fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/cat-questionnaire/page.tsx",
                            lineNumber: 256,
                            columnNumber: 11
                        }, this),
                        [
                            "FVRCP",
                            "Rabies",
                            "FeLV",
                            "FIP"
                        ].map((v)=>/*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$server$2f$route$2d$modules$2f$app$2d$page$2f$vendored$2f$ssr$2f$react$2d$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$ssr$5d$__$28$ecmascript$29$__["jsxDEV"])("label", {
                                className: "checkbox",
                                children: [
                                    /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$server$2f$route$2d$modules$2f$app$2d$page$2f$vendored$2f$ssr$2f$react$2d$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$ssr$5d$__$28$ecmascript$29$__["jsxDEV"])("input", {
                                        type: "checkbox",
                                        checked: vaccines.includes(v),
                                        onChange: ()=>handleCheckbox(v)
                                    }, void 0, false, {
                                        fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/cat-questionnaire/page.tsx",
                                        lineNumber: 261,
                                        columnNumber: 15
                                    }, this),
                                    " ",
                                    v
                                ]
                            }, v, true, {
                                fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/cat-questionnaire/page.tsx",
                                lineNumber: 260,
                                columnNumber: 13
                            }, this))
                    ]
                }, void 0, true, {
                    fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/cat-questionnaire/page.tsx",
                    lineNumber: 254,
                    columnNumber: 9
                }, this),
                /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$server$2f$route$2d$modules$2f$app$2d$page$2f$vendored$2f$ssr$2f$react$2d$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$ssr$5d$__$28$ecmascript$29$__["jsxDEV"])("div", {
                    className: "group",
                    children: [
                        /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$server$2f$route$2d$modules$2f$app$2d$page$2f$vendored$2f$ssr$2f$react$2d$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$ssr$5d$__$28$ecmascript$29$__["jsxDEV"])("label", {
                            children: [
                                "Upload Your Cat's Photo (1 MB - 5 MB)",
                                /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$server$2f$route$2d$modules$2f$app$2d$page$2f$vendored$2f$ssr$2f$react$2d$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$ssr$5d$__$28$ecmascript$29$__["jsxDEV"])("span", {
                                    style: {
                                        color: "red"
                                    },
                                    children: "*"
                                }, void 0, false, {
                                    fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/cat-questionnaire/page.tsx",
                                    lineNumber: 272,
                                    columnNumber: 55
                                }, this)
                            ]
                        }, void 0, true, {
                            fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/cat-questionnaire/page.tsx",
                            lineNumber: 272,
                            columnNumber: 11
                        }, this),
                        /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$server$2f$route$2d$modules$2f$app$2d$page$2f$vendored$2f$ssr$2f$react$2d$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$ssr$5d$__$28$ecmascript$29$__["jsxDEV"])("input", {
                            type: "file",
                            accept: ".jpg,.jpeg,.png",
                            required: true,
                            onChange: handleFileChange,
                            disabled: loading
                        }, void 0, false, {
                            fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/cat-questionnaire/page.tsx",
                            lineNumber: 273,
                            columnNumber: 11
                        }, this)
                    ]
                }, void 0, true, {
                    fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/cat-questionnaire/page.tsx",
                    lineNumber: 271,
                    columnNumber: 9
                }, this),
                /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$Cat__Project__Final$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$server$2f$route$2d$modules$2f$app$2d$page$2f$vendored$2f$ssr$2f$react$2d$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$ssr$5d$__$28$ecmascript$29$__["jsxDEV"])("button", {
                    type: "submit",
                    className: "submit-btn",
                    disabled: loading,
                    children: loading ? "Saving..." : "Save & Continue"
                }, void 0, false, {
                    fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/cat-questionnaire/page.tsx",
                    lineNumber: 282,
                    columnNumber: 9
                }, this)
            ]
        }, void 0, true, {
            fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/cat-questionnaire/page.tsx",
            lineNumber: 144,
            columnNumber: 7
        }, this)
    }, void 0, false, {
        fileName: "[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /src/app/cat-questionnaire/page.tsx",
        lineNumber: 143,
        columnNumber: 5
    }, this);
}
}),
"[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /node_modules/next/dist/server/route-modules/app-page/module.compiled.js [app-ssr] (ecmascript)", ((__turbopack_context__, module, exports) => {
"use strict";

if ("TURBOPACK compile-time falsy", 0) //TURBOPACK unreachable
;
else {
    if ("TURBOPACK compile-time falsy", 0) //TURBOPACK unreachable
    ;
    else {
        if ("TURBOPACK compile-time truthy", 1) {
            if ("TURBOPACK compile-time truthy", 1) {
                module.exports = __turbopack_context__.r("[externals]/next/dist/compiled/next-server/app-page-turbo.runtime.dev.js [external] (next/dist/compiled/next-server/app-page-turbo.runtime.dev.js, cjs)");
            } else //TURBOPACK unreachable
            ;
        } else //TURBOPACK unreachable
        ;
    }
} //# sourceMappingURL=module.compiled.js.map
}),
"[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /node_modules/next/dist/server/route-modules/app-page/vendored/ssr/react-jsx-dev-runtime.js [app-ssr] (ecmascript)", ((__turbopack_context__, module, exports) => {
"use strict";

module.exports = __turbopack_context__.r("[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /node_modules/next/dist/server/route-modules/app-page/module.compiled.js [app-ssr] (ecmascript)").vendored['react-ssr'].ReactJsxDevRuntime; //# sourceMappingURL=react-jsx-dev-runtime.js.map
}),
"[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /node_modules/next/dist/server/route-modules/app-page/vendored/ssr/react.js [app-ssr] (ecmascript)", ((__turbopack_context__, module, exports) => {
"use strict";

module.exports = __turbopack_context__.r("[project]/sources/freelance/Ricky/Cat Project Final/fp_fixed /node_modules/next/dist/server/route-modules/app-page/module.compiled.js [app-ssr] (ecmascript)").vendored['react-ssr'].React; //# sourceMappingURL=react.js.map
}),
];

//# sourceMappingURL=%5Broot-of-the-server%5D__6250375b._.js.map