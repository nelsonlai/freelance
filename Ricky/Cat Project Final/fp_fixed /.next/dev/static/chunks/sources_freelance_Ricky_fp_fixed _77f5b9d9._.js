(globalThis.TURBOPACK || (globalThis.TURBOPACK = [])).push([typeof document === "object" ? document.currentScript : undefined,
"[project]/sources/freelance/Ricky/fp_fixed /src/app/cat-questionnaire/page.tsx [app-client] (ecmascript)", ((__turbopack_context__) => {
"use strict";

__turbopack_context__.s([
    "default",
    ()=>CatQuestionnairePage
]);
var __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$build$2f$polyfills$2f$process$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__ = /*#__PURE__*/ __turbopack_context__.i("[project]/sources/freelance/Ricky/fp_fixed /node_modules/next/dist/build/polyfills/process.js [app-client] (ecmascript)");
var __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__ = __turbopack_context__.i("[project]/sources/freelance/Ricky/fp_fixed /node_modules/next/dist/compiled/react/jsx-dev-runtime.js [app-client] (ecmascript)");
var __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$index$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__ = __turbopack_context__.i("[project]/sources/freelance/Ricky/fp_fixed /node_modules/next/dist/compiled/react/index.js [app-client] (ecmascript)");
;
var _s = __turbopack_context__.k.signature();
"use client";
;
;
function CatQuestionnairePage() {
    _s();
    const [vaccines, setVaccines] = (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$index$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["useState"])([]);
    const [photo, setPhoto] = (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$index$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["useState"])(null);
    const [email, setEmail] = (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$index$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["useState"])("");
    const [password, setPassword] = (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$index$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["useState"])("");
    const [catName, setCatName] = (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$index$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["useState"])("");
    const [breed, setBreed] = (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$index$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["useState"])("");
    const [age, setAge] = (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$index$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["useState"])("");
    const [gender, setGender] = (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$index$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["useState"])("");
    const [health, setHealth] = (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$index$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["useState"])("");
    const [loading, setLoading] = (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$index$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["useState"])(false);
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
    return /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("main", {
        className: "cat-page",
        children: /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("form", {
            className: "cat-card",
            onSubmit: handleSubmit,
            children: [
                /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("h1", {
                    className: "title",
                    children: "🐱 Ethical Feline Registry"
                }, void 0, false, {
                    fileName: "[project]/sources/freelance/Ricky/fp_fixed /src/app/cat-questionnaire/page.tsx",
                    lineNumber: 145,
                    columnNumber: 9
                }, this),
                /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("p", {
                    className: "subtitle",
                    children: "Cat Information Form"
                }, void 0, false, {
                    fileName: "[project]/sources/freelance/Ricky/fp_fixed /src/app/cat-questionnaire/page.tsx",
                    lineNumber: 146,
                    columnNumber: 9
                }, this),
                /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("div", {
                    className: "form-grid",
                    children: [
                        /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("div", {
                            className: "group",
                            children: [
                                /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("label", {
                                    htmlFor: "catName",
                                    children: "Cat's Name"
                                }, void 0, false, {
                                    fileName: "[project]/sources/freelance/Ricky/fp_fixed /src/app/cat-questionnaire/page.tsx",
                                    lineNumber: 150,
                                    columnNumber: 13
                                }, this),
                                /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("input", {
                                    id: "catName",
                                    type: "text",
                                    placeholder: "e.g. Momo",
                                    value: catName,
                                    onChange: (e)=>setCatName(e.target.value),
                                    required: true,
                                    disabled: loading
                                }, void 0, false, {
                                    fileName: "[project]/sources/freelance/Ricky/fp_fixed /src/app/cat-questionnaire/page.tsx",
                                    lineNumber: 151,
                                    columnNumber: 13
                                }, this)
                            ]
                        }, void 0, true, {
                            fileName: "[project]/sources/freelance/Ricky/fp_fixed /src/app/cat-questionnaire/page.tsx",
                            lineNumber: 149,
                            columnNumber: 11
                        }, this),
                        /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("div", {
                            className: "group",
                            children: [
                                /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("label", {
                                    htmlFor: "breed",
                                    children: "Breed"
                                }, void 0, false, {
                                    fileName: "[project]/sources/freelance/Ricky/fp_fixed /src/app/cat-questionnaire/page.tsx",
                                    lineNumber: 162,
                                    columnNumber: 13
                                }, this),
                                /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("select", {
                                    id: "breed",
                                    value: breed,
                                    onChange: (e)=>setBreed(e.target.value),
                                    required: true,
                                    disabled: loading,
                                    children: [
                                        /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("option", {
                                            value: "",
                                            children: "Select Breed"
                                        }, void 0, false, {
                                            fileName: "[project]/sources/freelance/Ricky/fp_fixed /src/app/cat-questionnaire/page.tsx",
                                            lineNumber: 170,
                                            columnNumber: 15
                                        }, this),
                                        /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("option", {
                                            children: "British Shorthair"
                                        }, void 0, false, {
                                            fileName: "[project]/sources/freelance/Ricky/fp_fixed /src/app/cat-questionnaire/page.tsx",
                                            lineNumber: 171,
                                            columnNumber: 15
                                        }, this),
                                        /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("option", {
                                            children: "Persian"
                                        }, void 0, false, {
                                            fileName: "[project]/sources/freelance/Ricky/fp_fixed /src/app/cat-questionnaire/page.tsx",
                                            lineNumber: 172,
                                            columnNumber: 15
                                        }, this),
                                        /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("option", {
                                            children: "MaineCoon"
                                        }, void 0, false, {
                                            fileName: "[project]/sources/freelance/Ricky/fp_fixed /src/app/cat-questionnaire/page.tsx",
                                            lineNumber: 173,
                                            columnNumber: 15
                                        }, this),
                                        /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("option", {
                                            children: "Ragdoll"
                                        }, void 0, false, {
                                            fileName: "[project]/sources/freelance/Ricky/fp_fixed /src/app/cat-questionnaire/page.tsx",
                                            lineNumber: 174,
                                            columnNumber: 15
                                        }, this)
                                    ]
                                }, void 0, true, {
                                    fileName: "[project]/sources/freelance/Ricky/fp_fixed /src/app/cat-questionnaire/page.tsx",
                                    lineNumber: 163,
                                    columnNumber: 13
                                }, this)
                            ]
                        }, void 0, true, {
                            fileName: "[project]/sources/freelance/Ricky/fp_fixed /src/app/cat-questionnaire/page.tsx",
                            lineNumber: 161,
                            columnNumber: 11
                        }, this)
                    ]
                }, void 0, true, {
                    fileName: "[project]/sources/freelance/Ricky/fp_fixed /src/app/cat-questionnaire/page.tsx",
                    lineNumber: 148,
                    columnNumber: 9
                }, this),
                /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("div", {
                    className: "group",
                    children: [
                        /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("label", {
                            htmlFor: "ownerEmail",
                            children: [
                                "Owner Email Address ",
                                /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("span", {
                                    style: {
                                        color: "red"
                                    },
                                    children: "*"
                                }, void 0, false, {
                                    fileName: "[project]/sources/freelance/Ricky/fp_fixed /src/app/cat-questionnaire/page.tsx",
                                    lineNumber: 181,
                                    columnNumber: 59
                                }, this)
                            ]
                        }, void 0, true, {
                            fileName: "[project]/sources/freelance/Ricky/fp_fixed /src/app/cat-questionnaire/page.tsx",
                            lineNumber: 181,
                            columnNumber: 11
                        }, this),
                        /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("input", {
                            id: "ownerEmail",
                            type: "email",
                            placeholder: "you@example.com",
                            value: email,
                            onChange: (e)=>setEmail(e.target.value),
                            required: true,
                            disabled: loading
                        }, void 0, false, {
                            fileName: "[project]/sources/freelance/Ricky/fp_fixed /src/app/cat-questionnaire/page.tsx",
                            lineNumber: 182,
                            columnNumber: 11
                        }, this)
                    ]
                }, void 0, true, {
                    fileName: "[project]/sources/freelance/Ricky/fp_fixed /src/app/cat-questionnaire/page.tsx",
                    lineNumber: 180,
                    columnNumber: 9
                }, this),
                /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("div", {
                    className: "group",
                    children: [
                        /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("label", {
                            htmlFor: "ownerPassword",
                            children: [
                                "Password ",
                                /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("span", {
                                    style: {
                                        color: "red"
                                    },
                                    children: "*"
                                }, void 0, false, {
                                    fileName: "[project]/sources/freelance/Ricky/fp_fixed /src/app/cat-questionnaire/page.tsx",
                                    lineNumber: 194,
                                    columnNumber: 51
                                }, this)
                            ]
                        }, void 0, true, {
                            fileName: "[project]/sources/freelance/Ricky/fp_fixed /src/app/cat-questionnaire/page.tsx",
                            lineNumber: 194,
                            columnNumber: 11
                        }, this),
                        /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("input", {
                            id: "ownerPassword",
                            type: "password",
                            placeholder: "At least 8 characters",
                            value: password,
                            onChange: (e)=>setPassword(e.target.value),
                            required: true,
                            disabled: loading
                        }, void 0, false, {
                            fileName: "[project]/sources/freelance/Ricky/fp_fixed /src/app/cat-questionnaire/page.tsx",
                            lineNumber: 195,
                            columnNumber: 11
                        }, this)
                    ]
                }, void 0, true, {
                    fileName: "[project]/sources/freelance/Ricky/fp_fixed /src/app/cat-questionnaire/page.tsx",
                    lineNumber: 193,
                    columnNumber: 9
                }, this),
                /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("div", {
                    className: "form-grid",
                    children: [
                        /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("div", {
                            className: "group",
                            children: [
                                /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("label", {
                                    children: "Age (Years)"
                                }, void 0, false, {
                                    fileName: "[project]/sources/freelance/Ricky/fp_fixed /src/app/cat-questionnaire/page.tsx",
                                    lineNumber: 208,
                                    columnNumber: 13
                                }, this),
                                /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("input", {
                                    type: "number",
                                    min: "0",
                                    required: true,
                                    value: age,
                                    onChange: (e)=>setAge(e.target.value),
                                    disabled: loading
                                }, void 0, false, {
                                    fileName: "[project]/sources/freelance/Ricky/fp_fixed /src/app/cat-questionnaire/page.tsx",
                                    lineNumber: 209,
                                    columnNumber: 13
                                }, this)
                            ]
                        }, void 0, true, {
                            fileName: "[project]/sources/freelance/Ricky/fp_fixed /src/app/cat-questionnaire/page.tsx",
                            lineNumber: 207,
                            columnNumber: 11
                        }, this),
                        /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("div", {
                            className: "group",
                            children: [
                                /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("label", {
                                    children: "Gender"
                                }, void 0, false, {
                                    fileName: "[project]/sources/freelance/Ricky/fp_fixed /src/app/cat-questionnaire/page.tsx",
                                    lineNumber: 219,
                                    columnNumber: 13
                                }, this),
                                /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("div", {
                                    className: "radio-inline",
                                    children: [
                                        /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("label", {
                                            children: [
                                                /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("input", {
                                                    type: "radio",
                                                    name: "gender",
                                                    value: "Male",
                                                    checked: gender === "Male",
                                                    onChange: (e)=>setGender(e.target.value),
                                                    required: true,
                                                    disabled: loading
                                                }, void 0, false, {
                                                    fileName: "[project]/sources/freelance/Ricky/fp_fixed /src/app/cat-questionnaire/page.tsx",
                                                    lineNumber: 221,
                                                    columnNumber: 22
                                                }, this),
                                                " Male"
                                            ]
                                        }, void 0, true, {
                                            fileName: "[project]/sources/freelance/Ricky/fp_fixed /src/app/cat-questionnaire/page.tsx",
                                            lineNumber: 221,
                                            columnNumber: 15
                                        }, this),
                                        /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("label", {
                                            children: [
                                                /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("input", {
                                                    type: "radio",
                                                    name: "gender",
                                                    value: "Female",
                                                    checked: gender === "Female",
                                                    onChange: (e)=>setGender(e.target.value),
                                                    required: true,
                                                    disabled: loading
                                                }, void 0, false, {
                                                    fileName: "[project]/sources/freelance/Ricky/fp_fixed /src/app/cat-questionnaire/page.tsx",
                                                    lineNumber: 222,
                                                    columnNumber: 22
                                                }, this),
                                                " Female"
                                            ]
                                        }, void 0, true, {
                                            fileName: "[project]/sources/freelance/Ricky/fp_fixed /src/app/cat-questionnaire/page.tsx",
                                            lineNumber: 222,
                                            columnNumber: 15
                                        }, this)
                                    ]
                                }, void 0, true, {
                                    fileName: "[project]/sources/freelance/Ricky/fp_fixed /src/app/cat-questionnaire/page.tsx",
                                    lineNumber: 220,
                                    columnNumber: 13
                                }, this)
                            ]
                        }, void 0, true, {
                            fileName: "[project]/sources/freelance/Ricky/fp_fixed /src/app/cat-questionnaire/page.tsx",
                            lineNumber: 218,
                            columnNumber: 11
                        }, this)
                    ]
                }, void 0, true, {
                    fileName: "[project]/sources/freelance/Ricky/fp_fixed /src/app/cat-questionnaire/page.tsx",
                    lineNumber: 206,
                    columnNumber: 9
                }, this),
                /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("div", {
                    className: "group",
                    children: [
                        /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("label", {
                            children: "Health Condition"
                        }, void 0, false, {
                            fileName: "[project]/sources/freelance/Ricky/fp_fixed /src/app/cat-questionnaire/page.tsx",
                            lineNumber: 228,
                            columnNumber: 11
                        }, this),
                        /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("div", {
                            className: "radio-row",
                            children: [
                                "Healthy",
                                "Excellence Condition",
                                "Minor Issues",
                                "Previous Illness",
                                "Ongoing Condition",
                                "Disabled"
                            ].map((h)=>/*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("label", {
                                    children: [
                                        /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("input", {
                                            type: "radio",
                                            name: "health",
                                            value: h,
                                            checked: health === h,
                                            onChange: (e)=>setHealth(e.target.value),
                                            required: true,
                                            disabled: loading
                                        }, void 0, false, {
                                            fileName: "[project]/sources/freelance/Ricky/fp_fixed /src/app/cat-questionnaire/page.tsx",
                                            lineNumber: 239,
                                            columnNumber: 17
                                        }, this),
                                        h
                                    ]
                                }, h, true, {
                                    fileName: "[project]/sources/freelance/Ricky/fp_fixed /src/app/cat-questionnaire/page.tsx",
                                    lineNumber: 238,
                                    columnNumber: 15
                                }, this))
                        }, void 0, false, {
                            fileName: "[project]/sources/freelance/Ricky/fp_fixed /src/app/cat-questionnaire/page.tsx",
                            lineNumber: 229,
                            columnNumber: 11
                        }, this)
                    ]
                }, void 0, true, {
                    fileName: "[project]/sources/freelance/Ricky/fp_fixed /src/app/cat-questionnaire/page.tsx",
                    lineNumber: 227,
                    columnNumber: 9
                }, this),
                /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("div", {
                    className: "group",
                    children: [
                        /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("label", {
                            children: "Vaccination Record"
                        }, void 0, false, {
                            fileName: "[project]/sources/freelance/Ricky/fp_fixed /src/app/cat-questionnaire/page.tsx",
                            lineNumber: 255,
                            columnNumber: 11
                        }, this),
                        /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("p", {
                            className: "warning",
                            children: "⚠️All four core vaccines (FVRCP, Rabies, FeLV, FIP) are required before registration."
                        }, void 0, false, {
                            fileName: "[project]/sources/freelance/Ricky/fp_fixed /src/app/cat-questionnaire/page.tsx",
                            lineNumber: 256,
                            columnNumber: 11
                        }, this),
                        [
                            "FVRCP",
                            "Rabies",
                            "FeLV",
                            "FIP"
                        ].map((v)=>/*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("label", {
                                className: "checkbox",
                                children: [
                                    /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("input", {
                                        type: "checkbox",
                                        checked: vaccines.includes(v),
                                        onChange: ()=>handleCheckbox(v)
                                    }, void 0, false, {
                                        fileName: "[project]/sources/freelance/Ricky/fp_fixed /src/app/cat-questionnaire/page.tsx",
                                        lineNumber: 261,
                                        columnNumber: 15
                                    }, this),
                                    " ",
                                    v
                                ]
                            }, v, true, {
                                fileName: "[project]/sources/freelance/Ricky/fp_fixed /src/app/cat-questionnaire/page.tsx",
                                lineNumber: 260,
                                columnNumber: 13
                            }, this))
                    ]
                }, void 0, true, {
                    fileName: "[project]/sources/freelance/Ricky/fp_fixed /src/app/cat-questionnaire/page.tsx",
                    lineNumber: 254,
                    columnNumber: 9
                }, this),
                /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("div", {
                    className: "group",
                    children: [
                        /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("label", {
                            children: [
                                "Upload Your Cat's Photo (1 MB - 5 MB)",
                                /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("span", {
                                    style: {
                                        color: "red"
                                    },
                                    children: "*"
                                }, void 0, false, {
                                    fileName: "[project]/sources/freelance/Ricky/fp_fixed /src/app/cat-questionnaire/page.tsx",
                                    lineNumber: 272,
                                    columnNumber: 55
                                }, this)
                            ]
                        }, void 0, true, {
                            fileName: "[project]/sources/freelance/Ricky/fp_fixed /src/app/cat-questionnaire/page.tsx",
                            lineNumber: 272,
                            columnNumber: 11
                        }, this),
                        /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("input", {
                            type: "file",
                            accept: ".jpg,.jpeg,.png",
                            required: true,
                            onChange: handleFileChange,
                            disabled: loading
                        }, void 0, false, {
                            fileName: "[project]/sources/freelance/Ricky/fp_fixed /src/app/cat-questionnaire/page.tsx",
                            lineNumber: 273,
                            columnNumber: 11
                        }, this)
                    ]
                }, void 0, true, {
                    fileName: "[project]/sources/freelance/Ricky/fp_fixed /src/app/cat-questionnaire/page.tsx",
                    lineNumber: 271,
                    columnNumber: 9
                }, this),
                /*#__PURE__*/ (0, __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$compiled$2f$react$2f$jsx$2d$dev$2d$runtime$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__["jsxDEV"])("button", {
                    type: "submit",
                    className: "submit-btn",
                    disabled: loading,
                    children: loading ? "Saving..." : "Save & Continue"
                }, void 0, false, {
                    fileName: "[project]/sources/freelance/Ricky/fp_fixed /src/app/cat-questionnaire/page.tsx",
                    lineNumber: 282,
                    columnNumber: 9
                }, this)
            ]
        }, void 0, true, {
            fileName: "[project]/sources/freelance/Ricky/fp_fixed /src/app/cat-questionnaire/page.tsx",
            lineNumber: 144,
            columnNumber: 7
        }, this)
    }, void 0, false, {
        fileName: "[project]/sources/freelance/Ricky/fp_fixed /src/app/cat-questionnaire/page.tsx",
        lineNumber: 143,
        columnNumber: 5
    }, this);
}
_s(CatQuestionnairePage, "mCBzocBmv41jv6y/7MP7rFf6zn0=");
_c = CatQuestionnairePage;
var _c;
__turbopack_context__.k.register(_c, "CatQuestionnairePage");
if (typeof globalThis.$RefreshHelpers$ === 'object' && globalThis.$RefreshHelpers !== null) {
    __turbopack_context__.k.registerExports(__turbopack_context__.m, globalThis.$RefreshHelpers$);
}
}),
"[project]/sources/freelance/Ricky/fp_fixed /node_modules/next/dist/compiled/react/cjs/react-jsx-dev-runtime.development.js [app-client] (ecmascript)", ((__turbopack_context__, module, exports) => {
"use strict";

var __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$build$2f$polyfills$2f$process$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__ = /*#__PURE__*/ __turbopack_context__.i("[project]/sources/freelance/Ricky/fp_fixed /node_modules/next/dist/build/polyfills/process.js [app-client] (ecmascript)");
/**
 * @license React
 * react-jsx-dev-runtime.development.js
 *
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */ "use strict";
"production" !== ("TURBOPACK compile-time value", "development") && function() {
    function getComponentNameFromType(type) {
        if (null == type) return null;
        if ("function" === typeof type) return type.$$typeof === REACT_CLIENT_REFERENCE ? null : type.displayName || type.name || null;
        if ("string" === typeof type) return type;
        switch(type){
            case REACT_FRAGMENT_TYPE:
                return "Fragment";
            case REACT_PROFILER_TYPE:
                return "Profiler";
            case REACT_STRICT_MODE_TYPE:
                return "StrictMode";
            case REACT_SUSPENSE_TYPE:
                return "Suspense";
            case REACT_SUSPENSE_LIST_TYPE:
                return "SuspenseList";
            case REACT_ACTIVITY_TYPE:
                return "Activity";
            case REACT_VIEW_TRANSITION_TYPE:
                return "ViewTransition";
        }
        if ("object" === typeof type) switch("number" === typeof type.tag && console.error("Received an unexpected object in getComponentNameFromType(). This is likely a bug in React. Please file an issue."), type.$$typeof){
            case REACT_PORTAL_TYPE:
                return "Portal";
            case REACT_CONTEXT_TYPE:
                return type.displayName || "Context";
            case REACT_CONSUMER_TYPE:
                return (type._context.displayName || "Context") + ".Consumer";
            case REACT_FORWARD_REF_TYPE:
                var innerType = type.render;
                type = type.displayName;
                type || (type = innerType.displayName || innerType.name || "", type = "" !== type ? "ForwardRef(" + type + ")" : "ForwardRef");
                return type;
            case REACT_MEMO_TYPE:
                return innerType = type.displayName || null, null !== innerType ? innerType : getComponentNameFromType(type.type) || "Memo";
            case REACT_LAZY_TYPE:
                innerType = type._payload;
                type = type._init;
                try {
                    return getComponentNameFromType(type(innerType));
                } catch (x) {}
        }
        return null;
    }
    function testStringCoercion(value) {
        return "" + value;
    }
    function checkKeyStringCoercion(value) {
        try {
            testStringCoercion(value);
            var JSCompiler_inline_result = !1;
        } catch (e) {
            JSCompiler_inline_result = !0;
        }
        if (JSCompiler_inline_result) {
            JSCompiler_inline_result = console;
            var JSCompiler_temp_const = JSCompiler_inline_result.error;
            var JSCompiler_inline_result$jscomp$0 = "function" === typeof Symbol && Symbol.toStringTag && value[Symbol.toStringTag] || value.constructor.name || "Object";
            JSCompiler_temp_const.call(JSCompiler_inline_result, "The provided key is an unsupported type %s. This value must be coerced to a string before using it here.", JSCompiler_inline_result$jscomp$0);
            return testStringCoercion(value);
        }
    }
    function getTaskName(type) {
        if (type === REACT_FRAGMENT_TYPE) return "<>";
        if ("object" === typeof type && null !== type && type.$$typeof === REACT_LAZY_TYPE) return "<...>";
        try {
            var name = getComponentNameFromType(type);
            return name ? "<" + name + ">" : "<...>";
        } catch (x) {
            return "<...>";
        }
    }
    function getOwner() {
        var dispatcher = ReactSharedInternals.A;
        return null === dispatcher ? null : dispatcher.getOwner();
    }
    function UnknownOwner() {
        return Error("react-stack-top-frame");
    }
    function hasValidKey(config) {
        if (hasOwnProperty.call(config, "key")) {
            var getter = Object.getOwnPropertyDescriptor(config, "key").get;
            if (getter && getter.isReactWarning) return !1;
        }
        return void 0 !== config.key;
    }
    function defineKeyPropWarningGetter(props, displayName) {
        function warnAboutAccessingKey() {
            specialPropKeyWarningShown || (specialPropKeyWarningShown = !0, console.error("%s: `key` is not a prop. Trying to access it will result in `undefined` being returned. If you need to access the same value within the child component, you should pass it as a different prop. (https://react.dev/link/special-props)", displayName));
        }
        warnAboutAccessingKey.isReactWarning = !0;
        Object.defineProperty(props, "key", {
            get: warnAboutAccessingKey,
            configurable: !0
        });
    }
    function elementRefGetterWithDeprecationWarning() {
        var componentName = getComponentNameFromType(this.type);
        didWarnAboutElementRef[componentName] || (didWarnAboutElementRef[componentName] = !0, console.error("Accessing element.ref was removed in React 19. ref is now a regular prop. It will be removed from the JSX Element type in a future release."));
        componentName = this.props.ref;
        return void 0 !== componentName ? componentName : null;
    }
    function ReactElement(type, key, props, owner, debugStack, debugTask) {
        var refProp = props.ref;
        type = {
            $$typeof: REACT_ELEMENT_TYPE,
            type: type,
            key: key,
            props: props,
            _owner: owner
        };
        null !== (void 0 !== refProp ? refProp : null) ? Object.defineProperty(type, "ref", {
            enumerable: !1,
            get: elementRefGetterWithDeprecationWarning
        }) : Object.defineProperty(type, "ref", {
            enumerable: !1,
            value: null
        });
        type._store = {};
        Object.defineProperty(type._store, "validated", {
            configurable: !1,
            enumerable: !1,
            writable: !0,
            value: 0
        });
        Object.defineProperty(type, "_debugInfo", {
            configurable: !1,
            enumerable: !1,
            writable: !0,
            value: null
        });
        Object.defineProperty(type, "_debugStack", {
            configurable: !1,
            enumerable: !1,
            writable: !0,
            value: debugStack
        });
        Object.defineProperty(type, "_debugTask", {
            configurable: !1,
            enumerable: !1,
            writable: !0,
            value: debugTask
        });
        Object.freeze && (Object.freeze(type.props), Object.freeze(type));
        return type;
    }
    function jsxDEVImpl(type, config, maybeKey, isStaticChildren, debugStack, debugTask) {
        var children = config.children;
        if (void 0 !== children) if (isStaticChildren) if (isArrayImpl(children)) {
            for(isStaticChildren = 0; isStaticChildren < children.length; isStaticChildren++)validateChildKeys(children[isStaticChildren]);
            Object.freeze && Object.freeze(children);
        } else console.error("React.jsx: Static children should always be an array. You are likely explicitly calling React.jsxs or React.jsxDEV. Use the Babel transform instead.");
        else validateChildKeys(children);
        if (hasOwnProperty.call(config, "key")) {
            children = getComponentNameFromType(type);
            var keys = Object.keys(config).filter(function(k) {
                return "key" !== k;
            });
            isStaticChildren = 0 < keys.length ? "{key: someKey, " + keys.join(": ..., ") + ": ...}" : "{key: someKey}";
            didWarnAboutKeySpread[children + isStaticChildren] || (keys = 0 < keys.length ? "{" + keys.join(": ..., ") + ": ...}" : "{}", console.error('A props object containing a "key" prop is being spread into JSX:\n  let props = %s;\n  <%s {...props} />\nReact keys must be passed directly to JSX without using spread:\n  let props = %s;\n  <%s key={someKey} {...props} />', isStaticChildren, children, keys, children), didWarnAboutKeySpread[children + isStaticChildren] = !0);
        }
        children = null;
        void 0 !== maybeKey && (checkKeyStringCoercion(maybeKey), children = "" + maybeKey);
        hasValidKey(config) && (checkKeyStringCoercion(config.key), children = "" + config.key);
        if ("key" in config) {
            maybeKey = {};
            for(var propName in config)"key" !== propName && (maybeKey[propName] = config[propName]);
        } else maybeKey = config;
        children && defineKeyPropWarningGetter(maybeKey, "function" === typeof type ? type.displayName || type.name || "Unknown" : type);
        return ReactElement(type, children, maybeKey, getOwner(), debugStack, debugTask);
    }
    function validateChildKeys(node) {
        isValidElement(node) ? node._store && (node._store.validated = 1) : "object" === typeof node && null !== node && node.$$typeof === REACT_LAZY_TYPE && ("fulfilled" === node._payload.status ? isValidElement(node._payload.value) && node._payload.value._store && (node._payload.value._store.validated = 1) : node._store && (node._store.validated = 1));
    }
    function isValidElement(object) {
        return "object" === typeof object && null !== object && object.$$typeof === REACT_ELEMENT_TYPE;
    }
    var React = __turbopack_context__.r("[project]/sources/freelance/Ricky/fp_fixed /node_modules/next/dist/compiled/react/index.js [app-client] (ecmascript)"), REACT_ELEMENT_TYPE = Symbol.for("react.transitional.element"), REACT_PORTAL_TYPE = Symbol.for("react.portal"), REACT_FRAGMENT_TYPE = Symbol.for("react.fragment"), REACT_STRICT_MODE_TYPE = Symbol.for("react.strict_mode"), REACT_PROFILER_TYPE = Symbol.for("react.profiler"), REACT_CONSUMER_TYPE = Symbol.for("react.consumer"), REACT_CONTEXT_TYPE = Symbol.for("react.context"), REACT_FORWARD_REF_TYPE = Symbol.for("react.forward_ref"), REACT_SUSPENSE_TYPE = Symbol.for("react.suspense"), REACT_SUSPENSE_LIST_TYPE = Symbol.for("react.suspense_list"), REACT_MEMO_TYPE = Symbol.for("react.memo"), REACT_LAZY_TYPE = Symbol.for("react.lazy"), REACT_ACTIVITY_TYPE = Symbol.for("react.activity"), REACT_VIEW_TRANSITION_TYPE = Symbol.for("react.view_transition"), REACT_CLIENT_REFERENCE = Symbol.for("react.client.reference"), ReactSharedInternals = React.__CLIENT_INTERNALS_DO_NOT_USE_OR_WARN_USERS_THEY_CANNOT_UPGRADE, hasOwnProperty = Object.prototype.hasOwnProperty, isArrayImpl = Array.isArray, createTask = console.createTask ? console.createTask : function() {
        return null;
    };
    React = {
        react_stack_bottom_frame: function(callStackForError) {
            return callStackForError();
        }
    };
    var specialPropKeyWarningShown;
    var didWarnAboutElementRef = {};
    var unknownOwnerDebugStack = React.react_stack_bottom_frame.bind(React, UnknownOwner)();
    var unknownOwnerDebugTask = createTask(getTaskName(UnknownOwner));
    var didWarnAboutKeySpread = {};
    exports.Fragment = REACT_FRAGMENT_TYPE;
    exports.jsxDEV = function(type, config, maybeKey, isStaticChildren) {
        var trackActualOwner = 1e4 > ReactSharedInternals.recentlyCreatedOwnerStacks++;
        if (trackActualOwner) {
            var previousStackTraceLimit = Error.stackTraceLimit;
            Error.stackTraceLimit = 10;
            var debugStackDEV = Error("react-stack-top-frame");
            Error.stackTraceLimit = previousStackTraceLimit;
        } else debugStackDEV = unknownOwnerDebugStack;
        return jsxDEVImpl(type, config, maybeKey, isStaticChildren, debugStackDEV, trackActualOwner ? createTask(getTaskName(type)) : unknownOwnerDebugTask);
    };
}();
}),
"[project]/sources/freelance/Ricky/fp_fixed /node_modules/next/dist/compiled/react/jsx-dev-runtime.js [app-client] (ecmascript)", ((__turbopack_context__, module, exports) => {
"use strict";

var __TURBOPACK__imported__module__$5b$project$5d2f$sources$2f$freelance$2f$Ricky$2f$fp_fixed__$2f$node_modules$2f$next$2f$dist$2f$build$2f$polyfills$2f$process$2e$js__$5b$app$2d$client$5d$__$28$ecmascript$29$__ = /*#__PURE__*/ __turbopack_context__.i("[project]/sources/freelance/Ricky/fp_fixed /node_modules/next/dist/build/polyfills/process.js [app-client] (ecmascript)");
'use strict';
if ("TURBOPACK compile-time falsy", 0) //TURBOPACK unreachable
;
else {
    module.exports = __turbopack_context__.r("[project]/sources/freelance/Ricky/fp_fixed /node_modules/next/dist/compiled/react/cjs/react-jsx-dev-runtime.development.js [app-client] (ecmascript)");
}
}),
]);

//# sourceMappingURL=sources_freelance_Ricky_fp_fixed%20_77f5b9d9._.js.map