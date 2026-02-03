"use client";
import React, { useState, useEffect } from "react";
import "./match-result.css";
import Link from "next/link";
import ReactMarkdown from "react-markdown";

interface CatProfile {
  name: string;
  breed: string;
  age: number;
  gender?: string;
  health: string;
  vaccinations: string[];
  photo_path?: string;
}

interface CatProfileWithId extends CatProfile {
  id?: number;
}

export default function MatchResultPage() {
  const [myCat, setMyCat] = useState<CatProfile | null>(null);
  const [matches, setMatches] = useState<{ cat: CatProfileWithId; score: number }[]>([]);
  const [matchIdx, setMatchIdx] = useState(0);
  const [review, setReview] = useState<string>("");
  const [userEmail, setUserEmail] = useState<string>("");
  const [loading, setLoading] = useState(true);
  const [progress, setProgress] = useState(0);
  const [loadingStage, setLoadingStage] = useState("初始化...");
  const [kittenImageUrl, setKittenImageUrl] = useState<string>("");
  const [generatingOffspring, setGeneratingOffspring] = useState(false);

  useEffect(() => {
    const token = localStorage.getItem("auth_token") || "";
    if (!token) {
      window.location.href = "/login";
      return;
    }

    const API_BASE = process.env.NEXT_PUBLIC_API_BASE || "http://localhost:5050";

    // 模擬載入進度
    const progressInterval = setInterval(() => {
      setProgress((prev) => {
        if (prev >= 90) return prev; // 停在 90% 等待實際數據
        return prev + Math.random() * 15;
      });
    }, 300);

    (async () => {
      try {
        setLoadingStage("正在連接伺服器...");
        setProgress(10);

        const res = await fetch(`${API_BASE}/api/match-result`, {
          headers: {
            Authorization: `Bearer ${token}`,
          },
        });

        setLoadingStage("正在接收數據...");
        setProgress(50);

        const json = await res.json().catch(() => ({}));
        
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
        setTimeout(() => {
          setProgress(100);
          setLoadingStage("完成！");
          setTimeout(() => {
            setLoading(false);
            clearInterval(progressInterval);
          }, 300);
        }, 200);

      } catch (err) {
        clearInterval(progressInterval);
        console.error(err);
        alert("Something went wrong loading match data.");
        setLoading(false);
      }
    })();

    return () => clearInterval(progressInterval);
  }, []);

  // Generate offspring when match changes
  useEffect(() => {
    const currentMatch = matches.length ? matches[Math.min(matchIdx, matches.length - 1)] : null;
    const matchCatId = currentMatch?.cat?.id;
    
    if (!matchCatId || loading) return;

    const token = localStorage.getItem("auth_token") || "";
    if (!token) return;

    const API_BASE = process.env.NEXT_PUBLIC_API_BASE || "http://localhost:5050";

    const generateOffspring = async () => {
      setGeneratingOffspring(true);
      setKittenImageUrl(""); // Clear so we don't show previous pair's image
      
      try {
        const res = await fetch(`${API_BASE}/api/generate-offspring`, {
          method: "POST",
          headers: {
            "Content-Type": "application/json",
            Authorization: `Bearer ${token}`,
          },
          body: JSON.stringify({ match_cat_id: matchCatId }),
        });

        const json = await res.json().catch(() => ({}));
        
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
      } finally {
        setGeneratingOffspring(false);
      }
    };

    generateOffspring();
  }, [matchIdx, matches, loading]);

  const handleBack = () => window.history.back();

  const API_BASE = process.env.NEXT_PUBLIC_API_BASE || "http://localhost:5050";
  const currentMatch = matches.length ? matches[Math.min(matchIdx, matches.length - 1)] : null;
  const matchCat = currentMatch?.cat || null;
  
  const nextMatch = () => {
    if (!matches.length) return;
    setMatchIdx((i) => (i + 1) % matches.length);
  };
  
  const prevMatch = () => {
    if (!matches.length) return;
    setMatchIdx((i) => (i - 1 + matches.length) % matches.length);
  };

  if (loading) {
    return (
      <div className="loading-page">
        <div className="loading-container">
          <div className="spinner"></div>
          <h2 style={{ marginBottom: '8px', color: '#333' }}>載入配對結果中...</h2>
          <p style={{ marginBottom: '24px', color: '#777' }}>{loadingStage}</p>
          
          <div className="progress-bar-container">
            <div className="progress-bar" style={{ width: `${progress}%` }}></div>
          </div>
          
          <p style={{ marginTop: '12px', fontSize: '0.9rem', color: '#999' }}>
            {Math.round(progress)}% 完成
          </p>
        </div>
      </div>
    );
  }

  return (
    <div className="match-result-page">
      <header className="header">
        <Link href="/" className="back-btn">
          ← Back to Home
        </Link>

        <div className="logo">
          🐾 <span>PawMatch</span>
        </div>

        <div className="head-titles">
          <h1>Feline Compatibility Analysis</h1>
          <p>Find the purrfect partner for your beloved cat 💞</p>
        </div>
      </header>

      <main>
        <div className="top-row">
          <section className="card">
            <h2>Your Feline</h2>

            {myCat ? (
              <div className="cat-info">
                <div className="cat-photo">
                  <img
                    src={(myCat.photo_path ? `${API_BASE}${myCat.photo_path}` : "/images/your_cat.jpg")}
                    alt={myCat.name}
                  />
                </div>
                <ul>
                  <li><b>Owner:</b> {userEmail || "-"}</li>
                  <li><b>Name:</b> {myCat.name}</li>
                  <li><b>Breed:</b> {myCat.breed}</li>
                  <li><b>Age:</b> {myCat.age}</li>
                  <li><b>Gender:</b> {myCat.gender || "-"}</li>
                  <li><b>Health:</b> {myCat.health}</li>
                  <li><b>Vaccinations:</b> {(myCat.vaccinations || []).join(", ")}</li>
                </ul>
              </div>
            ) : (
              <p className="desc">Loading your cat profile...</p>
            )}

            <p className="desc">
              Your cat's data helps PawMatch find their best match.
            </p>
          </section>

          <section className="card">
            <h2>Potential Match</h2>
            <div className="match-info">
              <div className="match-photo">
                <button className="arrow left" onClick={prevMatch} type="button">←</button>
                <img
                  src={(matchCat?.photo_path ? `${API_BASE}${matchCat.photo_path}` : "/images/match_cat.jpg")}
                  alt="Potential Match"
                />
                <button className="arrow right" onClick={nextMatch} type="button">→</button>
              </div>
              <ul>
                {matchCat ? (
                  <>
                    <li><b>Score:</b> {currentMatch?.score ?? 0}</li>
                    <li><b>Name:</b> {matchCat.name}</li>
                    <li><b>Breed:</b> {matchCat.breed}</li>
                    <li><b>Age:</b> {matchCat.age} years</li>
                    <li><b>Gender:</b> {matchCat.gender || "-"}</li>
                    <li><b>Health:</b> {matchCat.health}</li>
                    <li><b>Vaccinations:</b> {(matchCat.vaccinations || []).join(", ")}</li>
                  </>
                ) : (
                  <li>No other cats in database yet.</li>
                )}
              </ul>
            </div>
            <p className="desc">
              Browse more compatible cats analyzed by PawMatch AI using the arrows.
            </p>
          </section>
        </div>

        <section className="match-review">
          <h2>Match Review</h2>
          <p className="caption">
            AI-generated preview — possible kitten appearance 🧡
          </p>

          <div className="kitten-photo">
            {generatingOffspring ? (
              <div className="offspring-loading">
                <div className="offspring-spinner"></div>
                <p>Generating AI kitten...</p>
              </div>
            ) : (
              <img
                key={kittenImageUrl || "kitten"}
                src={
                  kittenImageUrl
                    ? `${API_BASE}${kittenImageUrl}`
                    : "https://images.unsplash.com/photo-1514888286974-6c03e2ca1dba?w=400"
                }
                alt="AI Kitten"
                onError={(e) => {
                  e.currentTarget.src =
                    "https://images.unsplash.com/photo-1514888286974-6c03e2ca1dba?w=400";
                }}
              />
            )}
          </div>

          <div className="ai-review">
            {generatingOffspring ? (
              <p className="muted">
                Generating AI review for this pair...
              </p>
            ) : review ? (
              <ReactMarkdown>{review}</ReactMarkdown>
            ) : (
              <p className="muted">
                AI review is not available yet.
              </p>
            )}
          </div>
        </section>

        <div className="actions">
            <a
            href="https://docs.google.com/forms/d/e/1FAIpQLScPPwaHDG4b_HV-rFNSyjcdy31ESjHCbuKeIfb7w-Bn292KgQ/viewform"
            target="_blank"
            rel="noopener noreferrer"
            className="share"
            >
            📤 Share Result
            </a>
        </div>
      </main>
    </div>
  );
}