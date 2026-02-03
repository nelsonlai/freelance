import sqlite3
import json
import time
from typing import Optional, Dict, Any, List


class Storage:
    def __init__(self, sqlite_path: str):
        self.sqlite_path = sqlite_path
        self._init_db()
        

    # =========================================================
    # DB connection
    # =========================================================
    def _conn(self):
        conn = sqlite3.connect(self.sqlite_path)
        conn.row_factory = sqlite3.Row
        return conn

    # =========================================================
    # DB INIT
    # =========================================================
    def _init_db(self):
        with self._conn() as conn:
            # ---------- USERS ----------
            conn.execute("""
            CREATE TABLE IF NOT EXISTS users (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                email TEXT UNIQUE NOT NULL,
                password_hash TEXT NOT NULL,
                role TEXT NOT NULL DEFAULT 'user',
                created_at INTEGER NOT NULL
            )
            """)

            # ---------- REPORTS ----------
            conn.execute("""
            CREATE TABLE IF NOT EXISTS reports (
                id TEXT PRIMARY KEY,
                owner_email TEXT,
                created_at INTEGER NOT NULL,
                payload_json TEXT NOT NULL,
                result_json TEXT NOT NULL
            )
            """)

            # ---------- WEBHOOK LOGS ----------
            conn.execute("""
            CREATE TABLE IF NOT EXISTS webhook_logs (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                source TEXT NOT NULL,
                created_at INTEGER NOT NULL,
                payload_json TEXT NOT NULL,
                meta_json TEXT NOT NULL
            )
            """)

            # ---------- RAW FORM ----------
            conn.execute("""
            CREATE TABLE IF NOT EXISTS form_raw (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                payload TEXT NOT NULL,
                created_at INTEGER NOT NULL
            )
            """)

            # ---------- FORM ANSWERS ----------
            conn.execute("""
            CREATE TABLE IF NOT EXISTS form_answers (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                created_at INTEGER NOT NULL,

                cat_age INTEGER,
                cat_breed TEXT,
                cat_sex_status TEXT,

                cat_source TEXT,
                owning_years INTEGER,
                origin_known TEXT,

                vet_frequency TEXT,
                vet_cost INTEGER,

                supplements TEXT,
                grooming TEXT,

                special_diet TEXT,
                medical_history TEXT,

                digestive_issues INTEGER,
                chronic_disease TEXT,
                chronic_disease_list TEXT,

                genetic_disease_known TEXT,
                parents_genetic_issue TEXT,

                aggressive_behavior INTEGER,
                expense_reasonable INTEGER,
                affectionate INTEGER,

                care_hours_per_week INTEGER,
                life_fulfillment INTEGER
            )
            """)

            # ---------- CATS ----------
            conn.execute("""
            CREATE TABLE IF NOT EXISTS cats (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                user_id INTEGER UNIQUE NOT NULL,
                name TEXT NOT NULL,
                breed TEXT NOT NULL,
                age INTEGER NOT NULL,
                gender TEXT NOT NULL,
                health TEXT NOT NULL,
                vaccinations_json TEXT NOT NULL,
                photo_path TEXT,
                profile_json TEXT NOT NULL,
                created_at INTEGER NOT NULL,
                updated_at INTEGER NOT NULL
            )
            """)

            conn.commit()

    # =========================================================
    # HELPERS
    # =========================================================
    def _int(self, v):
        try:
            return int(v)
        except Exception:
            return None

    def _range_mid(self, v: Optional[str]):
        if not v:
            return None
        import re
        nums = re.findall(r"\d+", v.replace(",", ""))
        if len(nums) >= 2:
            return (int(nums[0]) + int(nums[1])) // 2
        if len(nums) == 1:
            return int(nums[0])
        return None

    # =========================================================
    # RAW FORM
    # =========================================================
    def insert_form_raw(self, payload: dict):
        with self._conn() as conn:
            conn.execute(
                "INSERT INTO form_raw (payload, created_at) VALUES (?, ?)",
                (json.dumps(payload, ensure_ascii=False), int(time.time()))
            )
            conn.commit()

    # =========================================================
    # FORM ANSWERS (STRUCTURED)
    # =========================================================
    def insert_form_answers_from_make_payload(self, payload: dict):
        with self._conn() as conn:
            conn.execute(
                """
                INSERT INTO form_answers (
                    created_at,
                    cat_age, cat_breed, cat_sex_status,
                    cat_source, owning_years, origin_known,
                    vet_frequency, vet_cost,
                    supplements, grooming,
                    special_diet, medical_history,
                    digestive_issues, chronic_disease, chronic_disease_list,
                    genetic_disease_known, parents_genetic_issue,
                    aggressive_behavior, expense_reasonable, affectionate,
                    care_hours_per_week, life_fulfillment
                ) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)
                """,
                (
                    int(time.time()),
                    self._range_mid(payload.get("cat_age")),
                    payload.get("cat_breed"),
                    payload.get("cat_sex_status"),
                    payload.get("cat_source"),
                    self._range_mid(payload.get("owning_years")),
                    payload.get("origin_known"),
                    payload.get("vet_frequency"),
                    self._range_mid(payload.get("vet_cost")),
                    payload.get("supplements"),
                    payload.get("grooming"),
                    payload.get("special_diet"),
                    payload.get("medical_history"),
                    self._int(payload.get("digestive_issues")),
                    payload.get("chronic_disease"),
                    payload.get("chronic_disease_list"),
                    payload.get("genetic_disease_known"),
                    payload.get("parents_genetic_issue"),
                    self._int(payload.get("aggressive_behavior")),
                    self._int(payload.get("expense_reasonable")),
                    self._int(payload.get("affectionate")),
                    self._range_mid(payload.get("care_hours_per_week")),
                    self._int(payload.get("life_fulfillment")),
                ),
            )
            conn.commit()

    # =========================================================
    # USERS
    # =========================================================
    def create_user(self, email: str, password_hash: str):
        with self._conn() as conn:
            conn.execute(
                "INSERT INTO users (email, password_hash, role, created_at) VALUES (?, ?, 'user', ?)",
                (email, password_hash, int(time.time()))
            )
            conn.commit()

    def create_user_with_role(self, email: str, password_hash: str, role: str):
        with self._conn() as conn:
            conn.execute(
                "INSERT INTO users (email, password_hash, role, created_at) VALUES (?, ?, ?, ?)",
                (email, password_hash, role, int(time.time()))
            )
            conn.commit()

    def get_user_by_email(self, email: str) -> Optional[Dict[str, Any]]:
        with self._conn() as conn:
            r = conn.execute(
                "SELECT id, email, password_hash, role FROM users WHERE email = ?",
                (email,),
            ).fetchone()
            return dict(r) if r else None

    def list_users(self, limit=200):
        with self._conn() as conn:
            rows = conn.execute(
                "SELECT id, email, role, created_at FROM users ORDER BY created_at DESC LIMIT ?",
                (limit,),
            ).fetchall()
            return [dict(r) for r in rows]

    def set_user_role(self, user_id: int, role: str):
        with self._conn() as conn:
            conn.execute("UPDATE users SET role=? WHERE id=?", (role, user_id))
            conn.commit()

    def count_users(self):
        with self._conn() as conn:
            return conn.execute("SELECT COUNT(*) FROM users").fetchone()[0]

    # =========================================================
    # CATS (MATCH / REGISTER)
    # =========================================================
    def upsert_cat_for_user(
        self,
        user_id: int,
        name: str,
        breed: str,
        age: int,
        gender: str,
        health: str,
        vaccinations: List[str],
        profile: Dict[str, Any],
        photo_path: Optional[str] = None,
    ):
        now = int(time.time())
        with self._conn() as conn:
            conn.execute(
                """
                INSERT INTO cats
                (user_id, name, breed, age, gender, health,
                 vaccinations_json, photo_path, profile_json,
                 created_at, updated_at)
                VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)
                ON CONFLICT(user_id) DO UPDATE SET
                    name=excluded.name,
                    breed=excluded.breed,
                    age=excluded.age,
                    gender=excluded.gender,
                    health=excluded.health,
                    vaccinations_json=excluded.vaccinations_json,
                    photo_path=COALESCE(excluded.photo_path, cats.photo_path),
                    profile_json=excluded.profile_json,
                    updated_at=excluded.updated_at
                """,
                (
                    user_id,
                    name,
                    breed,
                    age,
                    gender,
                    health,
                    json.dumps(vaccinations, ensure_ascii=False),
                    photo_path,
                    json.dumps(profile, ensure_ascii=False),
                    now,
                    now,
                ),
            )
            conn.commit()
        return self.get_cat_by_user_id(user_id)

    def get_cat_by_user_id(self, user_id: int):
        with self._conn() as conn:
            r = conn.execute(
                "SELECT * FROM cats WHERE user_id=?",
                (user_id,),
            ).fetchone()
            if not r:
                return None
            d = dict(r)
            d["vaccinations"] = json.loads(d["vaccinations_json"])
            d["profile"] = json.loads(d["profile_json"])
            return d

    # =========================================================
    # REPORTS
    # =========================================================
    def save_report(self, report_id, payload, result, owner_email):
        with self._conn() as conn:
            conn.execute(
                """
                INSERT OR REPLACE INTO reports
                (id, owner_email, created_at, payload_json, result_json)
                VALUES (?, ?, ?, ?, ?)
                """,
                (
                    report_id,
                    owner_email,
                    int(time.time()),
                    json.dumps(payload),
                    json.dumps(result),
                ),
            )
            conn.commit()

    def list_reports(self, owner_email=None, limit=50):
        with self._conn() as conn:
            if owner_email:
                rows = conn.execute(
                    "SELECT * FROM reports WHERE owner_email=? ORDER BY created_at DESC LIMIT ?",
                    (owner_email, limit),
                ).fetchall()
            else:
                rows = conn.execute(
                    "SELECT * FROM reports ORDER BY created_at DESC LIMIT ?",
                    (limit,),
                ).fetchall()

            out = []
            for r in rows:
                out.append({
                    "id": r["id"],
                    "owner_email": r["owner_email"],
                    "created_at": r["created_at"],
                    "payload": json.loads(r["payload_json"]),
                    "result": json.loads(r["result_json"]),
                })
            return out

    def get_report(self, report_id):
        with self._conn() as conn:
            r = conn.execute(
                "SELECT * FROM reports WHERE id=?",
                (report_id,),
            ).fetchone()
            if not r:
                return None
            return {
                "id": r["id"],
                "owner_email": r["owner_email"],
                "created_at": r["created_at"],
                "payload": json.loads(r["payload_json"]),
                "result": json.loads(r["result_json"]),
            }

    def count_reports(self):
        with self._conn() as conn:
            return conn.execute("SELECT COUNT(*) FROM reports").fetchone()[0]

    # =========================================================
    # WEBHOOK LOGS
    # =========================================================
    def add_webhook_log(self, source, payload, meta):
        with self._conn() as conn:
            conn.execute(
                "INSERT INTO webhook_logs (source, created_at, payload_json, meta_json) VALUES (?, ?, ?, ?)",
                (
                    source,
                    int(time.time()),
                    json.dumps(payload),
                    json.dumps(meta),
                ),
            )
            conn.commit()

    def list_webhooks(self, limit=100):
        with self._conn() as conn:
            rows = conn.execute(
                "SELECT * FROM webhook_logs ORDER BY created_at DESC LIMIT ?",
                (limit,),
            ).fetchall()

            out = []
            for r in rows:
                out.append({
                    "id": r["id"],
                    "source": r["source"],
                    "created_at": r["created_at"],
                    "payload": json.loads(r["payload_json"]),
                    "meta": json.loads(r["meta_json"]),
                })
            return out

    def count_webhooks(self):
        with self._conn() as conn:
            return conn.execute("SELECT COUNT(*) FROM webhook_logs").fetchone()[0]

    # =========================================================
    # ANALYTICS
    # =========================================================
    def kpis(self):
        with self._conn() as conn:
            r = conn.execute("""
                SELECT
                    COUNT(*) AS total_forms,
                    ROUND(AVG(cat_age),1) AS avg_cat_age,
                    ROUND(AVG(owning_years),1) AS avg_owning_years,
                    ROUND(AVG(life_fulfillment),1) AS avg_life_fulfillment
                FROM form_answers
            """).fetchone()
            return dict(r)

    def group_count(self, column: str):
        with self._conn() as conn:
            rows = conn.execute(
                f"""
                SELECT {column} AS label, COUNT(*) AS value
                FROM form_answers
                WHERE {column} IS NOT NULL
                GROUP BY {column}
                ORDER BY value DESC
                """
            ).fetchall()
            return [dict(r) for r in rows]

    def histogram_int(self, column: str, bins: List[int]):
        bins = sorted(bins)
        labels = [f"{bins[i]}–{bins[i+1]-1}" for i in range(len(bins)-1)]
        counts = [0] * (len(bins) - 1)

        with self._conn() as conn:
            rows = conn.execute(
                f"SELECT {column} AS v FROM form_answers WHERE {column} IS NOT NULL"
            ).fetchall()

            for r in rows:
                v = r["v"]
                for i in range(len(bins) - 1):
                    if bins[i] <= v < bins[i + 1]:
                        counts[i] += 1
                        break

        return {"labels": labels, "counts": counts}
    def list_other_cats(self, user_id: int, limit: int = 200):
        conn = self._conn()
        try:
            cur = conn.execute(
                """
                SELECT *
                FROM cats
                WHERE user_id != ?
                ORDER BY id DESC
                LIMIT ?
                """,
                (user_id, limit)
            )
            rows = cur.fetchall()

            results = []
            for row in rows:
                cat = dict(row)
                if cat.get("profile"):
                    try:
                        cat["profile"] = json.loads(cat["profile"])
                    except Exception:
                        cat["profile"] = {}
                results.append(cat)

            return results
        finally:
            conn.close()