"use client";

import React, { useState, FormEvent } from "react";
import { useRouter } from "next/navigation";
import "./login.css";

export default function LoginPage() {
  const [email, setEmail] = useState("");
  const [password, setPassword] = useState("");
  const [loading, setLoading] = useState(false);
  const router = useRouter();

  const handleSubmit = async (e: FormEvent) => {
    e.preventDefault();

    // ⚙️ 暫時關閉 email 驗證 (測試模式)
    // 原本這段驗證可以暫時註解掉，之後再開回
    // if (!/^[^\s@]+@[^\s@]+\.[^\s@]+$/.test(email)) {
    //   alert("Please enter a valid email");
    //   return;
    // }

    try {
      setLoading(true);

      if (!email || !password) {
        alert("Please enter email and password.");
        return;
      }
      if (password.length < 8) {
        alert("Password must be at least 8 characters.");
        return;
      }

      const API_BASE = process.env.NEXT_PUBLIC_API_BASE || "http://localhost:5050";
      const res = await fetch(`${API_BASE}/api/auth/login`, {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({ email, password }),
      });

      const json = await res.json().catch(() => ({}));
      if (!res.ok) {
        alert(json?.message || "Login failed.");
        return;
      }

      localStorage.setItem("auth_token", json.token);
      localStorage.setItem("owner_email", email);

      router.push("/match-result");
    } catch (err) {
      console.error("❌ Submit failed:", err);
      alert("Something went wrong.");
    } finally {
      setLoading(false);
    }
  };

  return (
    <main className="login-container">
      <section className="login-card">
        <div className="left">
          <h1>Ethical Feline Registry</h1>
          <p className="subtitle">Connecting Whiskers with Kindness</p>

          <form onSubmit={handleSubmit}>
            <label>Email Address (Optional for Testing)</label>
            <input
              type="email"
              placeholder="you@example.com"
              value={email}
              onChange={(e) => setEmail(e.target.value)}
              disabled={loading}
            />

            <label>Password</label>
            <input
              type="password"
              placeholder="At least 8 characters"
              value={password}
              onChange={(e) => setPassword(e.target.value)}
              disabled={loading}
            />

            <button type="submit" disabled={loading}>
              {loading ? "Loading..." : "Log In"}
            </button>

            <p style={{ marginTop: 12, fontSize: 13 }}>
              No account yet? <a href="/cat-questionnaire" style={{ textDecoration: "underline" }}>Register your cat</a>
            </p>
          </form>
        </div>

        <div className="right">
          <img
            src="/image/sleepingcat.jpg"
            alt="Cute orange cat sleeping"
            className="cat-image"
            width={600}
          />
        </div>
      </section>
    </main>
  );
}
