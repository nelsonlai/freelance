"use client";
import React, { useState, ChangeEvent, FormEvent } from "react";
import "./style.css";

export default function CatQuestionnairePage() {
  const [vaccines, setVaccines] = useState<string[]>([]);
  const [photo, setPhoto] = useState<File | null>(null);
  const [email, setEmail] = useState("");
  const [password, setPassword] = useState("");
  const [catName, setCatName] = useState("");
  const [breed, setBreed] = useState("");
  const [age, setAge] = useState<string>("");
  const [gender, setGender] = useState("");
  const [health, setHealth] = useState("");
  const [loading, setLoading] = useState(false);

  const handleCheckbox = (v: string) => {
    setVaccines((prev) =>
      prev.includes(v) ? prev.filter((x) => x !== v) : [...prev, v]
    );
  };

  const handleFileChange = (e: ChangeEvent<HTMLInputElement>) => {
    if (e.target.files?.[0]) setPhoto(e.target.files[0]);
  };

  const fileToDataUrl = (file: File) =>
    new Promise<string>((resolve, reject) => {
      const reader = new FileReader();
      reader.onload = () => resolve(String(reader.result || ""));
      reader.onerror = () => reject(new Error("Failed to read file"));
      reader.readAsDataURL(file);
    });

  const handleSubmit = async (e: FormEvent) => {
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
    const required = ["FVRCP", "Rabies", "FeLV", "FIP"];
    if (!required.every((v) => vaccines.includes(v))) {
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
      const API_BASE = process.env.NEXT_PUBLIC_API_BASE || "http://localhost:5050";

      const payload = {
        email,
        password,
        cat_name: catName,
        breed,
        age: Number(age),
        gender,
        health,
        vaccines,
        photo_data_url,
      };

      const res = await fetch(`${API_BASE}/api/cat-questionnaire`, {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify(payload),
      });

      const json = await res.json().catch(() => ({}));
      if (!res.ok) {
        alert(json?.message || "Registration failed.");
        return;
      }

      localStorage.setItem("auth_token", json.token);
      localStorage.setItem("owner_email", email);

      // optional: store a quick snapshot for UI fallback
      localStorage.setItem(
        "catProfile",
        JSON.stringify({
          name: catName,
          breed,
          age: String(age),
          temperament: "",
          health,
          vaccinations: vaccines.join(", "),
          photo: json?.cat?.photo_path ? `${API_BASE}${json.cat.photo_path}` : "",
        })
      );

      alert("✅ Registered successfully!");
      window.location.href = "/match-result";
    } catch (err) {
      console.error(err);
      alert("Something went wrong while submitting.");
    } finally {
      setLoading(false);
    }
  };

  return (
    <main className="cat-page">
      <form className="cat-card" onSubmit={handleSubmit}>
        <h1 className="title">🐱 Ethical Feline Registry</h1>
        <p className="subtitle">Cat Information Form</p>

        <div className="form-grid">
          <div className="group">
            <label htmlFor="catName">Cat's Name</label>
            <input
              id="catName"
              type="text"
              placeholder="e.g. Momo"
              value={catName}
              onChange={(e) => setCatName(e.target.value)}
              required
              disabled={loading}
            />
          </div>
          <div className="group">
            <label htmlFor="breed">Breed</label>
            <select
              id="breed"
              value={breed}
              onChange={(e) => setBreed(e.target.value)}
              required
              disabled={loading}
            >
              <option value="">Select Breed</option>
              <option>British Shorthair</option>
              <option>Persian</option>
              <option>MaineCoon</option>
              <option>Ragdoll</option>
            </select>
          </div>
        </div>

        {/* ✅ NEW Owner Email */}
        <div className="group">
          <label htmlFor="ownerEmail">Owner Email Address <span style={{color:"red"}}>*</span></label>
          <input
            id="ownerEmail"
            type="email"
            placeholder="you@example.com"
            value={email}
            onChange={(e) => setEmail(e.target.value)}
            required
            disabled={loading}
          />
        </div>

        <div className="group">
          <label htmlFor="ownerPassword">Password <span style={{color:"red"}}>*</span></label>
          <input
            id="ownerPassword"
            type="password"
            placeholder="At least 8 characters"
            value={password}
            onChange={(e) => setPassword(e.target.value)}
            required
            disabled={loading}
          />
        </div>

        <div className="form-grid">
          <div className="group">
            <label>Age (Years)</label>
            <input
              type="number"
              min="0"
              required
              value={age}
              onChange={(e) => setAge(e.target.value)}
              disabled={loading}
            />
          </div>
          <div className="group">
            <label>Gender</label>
            <div className="radio-inline">
              <label><input type="radio" name="gender" value="Male" checked={gender==="Male"} onChange={(e)=>setGender(e.target.value)} required disabled={loading} /> Male</label>
              <label><input type="radio" name="gender" value="Female" checked={gender==="Female"} onChange={(e)=>setGender(e.target.value)} required disabled={loading} /> Female</label>
            </div>
          </div>
        </div>

        <div className="group">
          <label>Health Condition</label>
          <div className="radio-row">
            {[
              "Healthy",
              "Excellence Condition",
              "Minor Issues",
              "Previous Illness",
              "Ongoing Condition",
              "Disabled",
            ].map((h) => (
              <label key={h}>
                <input
                  type="radio"
                  name="health"
                  value={h}
                  checked={health === h}
                  onChange={(e) => setHealth(e.target.value)}
                  required
                  disabled={loading}
                />
                {h}
              </label>
            ))}
          </div>
        </div>

        <div className="group">
          <label>Vaccination Record</label>
          <p className="warning">
            ⚠️All four core vaccines (FVRCP, Rabies, FeLV, FIP) are required before registration.
          </p>
          {["FVRCP", "Rabies", "FeLV", "FIP"].map((v) => (
            <label key={v} className="checkbox">
              <input
                type="checkbox"
                checked={vaccines.includes(v)}
                onChange={() => handleCheckbox(v)}
              />{" "}
              {v}
            </label>
          ))}
        </div>

        <div className="group">
          <label>Upload Your Cat's Photo (1 MB - 5 MB)<span style={{color:"red"}}>*</span></label>
          <input
            type="file"
            accept=".jpg,.jpeg,.png"
            required
            onChange={handleFileChange}
            disabled={loading}
          />
        </div>

        <button type="submit" className="submit-btn" disabled={loading}>
          {loading ? "Saving..." : "Save & Continue"}
        </button>
      </form>
    </main>
  );
}