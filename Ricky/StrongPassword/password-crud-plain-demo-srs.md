# Software Requirements Specification (SRS)
**Product:** Password CRUD (Next.js + Express.js + Prisma + SQLite) – *Plain Password Demo*  
**Version:** 1.1  
**Date:** 29-Aug-2025  
**Author:** ChatGPT (“Cathy”)

## 1. Purpose & Scope
**Purpose.** Define requirements for a demo web app where the frontend (Next.js) generates strong passwords and performs CRUD on user records, while the backend (Express.js) persists **plain-text passwords** using Prisma + SQLite.

**Scope (v1.1).**
- Next.js UI: password generator (length slider), username/email inputs, CRUD via REST APIs.
- Express.js backend: input validation, **store password as plain text** (demo only), Prisma/SQLite persistence, CRUD endpoints.
- SQLite file DB.

> ⚠️ **Demo-only warning:** This build stores passwords in plain text and may return them via an opt-in flag. **Do not** use in production.

## 2. Stakeholders & Users
- **Owner/Developer:** Project maintainer.
- **End user:** Admin/operator using the UI.

## 3. Assumptions & Constraints
- **Stack:** Next.js, Express.js, Prisma, SQLite 3, Node.js ≥ 20.x.
- **Runtime:** Single instance; local/dev use.
- **Security:** Intentionally weak for demo (see §9).

## 4. System Overview
- **Frontend:** Records table + Create/Update form; password generator (8–64); copy/show-hide; toasts.
- **Backend:** REST under `/api/v1/records`; validates, stores **plain password**.
- **DB:** Single `Record` table.

## 5. Functional Requirements

### FR-1 Password Generation (Frontend)
1. Slider 8–64 (default 16).
2. Toggles: uppercase, lowercase, digits, symbols (all on by default).
3. Generated password must contain at least one char from each enabled class.
4. Show/hide + copy; simple strength indicator.

### FR-2 Create Record
1. Inputs: `username`, `email`, `password` (generated or manual).
2. Frontend POSTs JSON to backend.
3. Backend:
   - Validates payload (FR-6).
   - **Stores password as plain text**.
   - Returns created record **without** `password` by default.

### FR-3 Read/List Records
1. Frontend fetches all records (GET).
2. Backend returns list excluding `password` by default.
3. **Demo option:** If query `?includePassword=true` is present, include `password` in response.

### FR-4 Update Record
1. Edit form for `username`, `email`, and optional new `password`.
2. Backend validates; if `password` present, **store plain text**.
3. Returns updated record (exclude `password` by default; include if `?includePassword=true`).

### FR-5 Delete Record
1. Delete with confirmation.
2. Backend hard-deletes; returns 204.

### FR-6 Validation Rules
- **username:** 3–50 chars, `[A-Za-z0-9_]+`, unique (case-insensitive).
- **email:** Valid format, unique (case-insensitive).
- **password:** 8–128 chars; at least **three** classes among lower/upper/digit/symbol.

### FR-7 Error Handling (Contract)
```json
{ "error": { "code": "VALIDATION_ERROR", "message": "Email already exists.", "details": {"field": "email"} } }
```
Codes: `VALIDATION_ERROR`, `NOT_FOUND`, `CONFLICT`, `BAD_REQUEST`, `INTERNAL_ERROR`.

### FR-8 Frontend UX
- Table: **ID**, **Username**, **Email**, **Created At**, **Updated At**, **Actions**.
- Create/Edit modal; client-side checks mirroring backend.
- Delete confirmation; success/failure toasts.

## 6. API Specification (REST)

**Base:** `/api/v1`

### POST `/records`
**Body**
```json
{ "username":"nelson", "email":"nelson@example.com", "password":"S3cure!Pass" }
```
**201**
```json
{ "id":"clx123", "username":"nelson", "email":"nelson@example.com", "createdAt":"...", "updatedAt":"..." }
```
Errors: 400, 409.

### GET `/records`
**Query (optional):** `includePassword=true`  
**200**
```json
{
  "items": [
    { "id":"clx123","username":"nelson","email":"nelson@example.com","createdAt":"...","updatedAt":"..." }
  ],
  "total": 1
}
```
If `includePassword=true`, each item adds `"password":"S3cure!Pass"`.

### GET `/records/:id`
**Query (optional):** `includePassword=true`  
**200:** record (no password unless flag).  
**404:** not found.

### PATCH `/records/:id`
**Body (any subset)**
```json
{ "username":"newname", "email":"new@example.com", "password":"New!Passw0rd" }
```
**200:** updated record (password excluded unless `includePassword=true`).  
Errors: 400, 404, 409.

### DELETE `/records/:id`
**204** on success; **404** if not found.

**Headers:** `Content-Type: application/json`.  
**Auth:** none (demo).

## 7. Data Model

### Prisma Schema (normative)
```prisma
model Record {
  id        String   @id @default(cuid())
  username  String   @unique
  email     String   @unique
  password  String   // PLAINTEXT FOR DEMO ONLY
  createdAt DateTime @default(now())
  updatedAt DateTime @updatedAt
}
```
> Case-insensitive uniqueness enforced via app logic or DB collation.

## 8. Non-Functional Requirements (NFR)
- **NFR-PERF-01:** p95 API latency < 250 ms locally for CRUD ≤ 1k records.
- **NFR-RELI-01:** Graceful start/stop; DB retry.
- **NFR-MAINT-01:** TypeScript recommended; ESLint/Prettier.
- **NFR-PORT-01:** Single command dev (`npm run dev` for both apps).
- **NFR-TEST-01:** Unit tests for generator/validators; integration tests for CRUD.

## 9. Security (Demo-Only Posture)
- **SR-DEMO-01:** Passwords are stored and (optionally) returned **in plain text** for demo only.
- **SR-DEMO-02:** Do **not** deploy to production; remove/disable `includePassword` before any real use.
- **SR-DEMO-03:** HTTPS recommended even in demos; avoid logging passwords; mask in UI where possible.
- **SR-DEMO-04:** No secrets in VCS; env-based config.

## 10. Environment & Configuration
- **Node:** ≥ 20.x
- **Env (backend):**
  - `DATABASE_URL="file:./dev.db"`
  - `PORT=4000`
  - `CORS_ORIGIN=http://localhost:3000`
  - `ALLOW_PASSWORD_IN_RESPONSE=true` (controls `includePassword` support; default true for demo)
- **Prisma:** `prisma generate`, `prisma migrate dev`.
- **SQLite file:** `./prisma/dev.db`.

## 11. Acceptance Criteria (Samples)
- **AC-Create-Plain-01:** POST `/records` stores `password` column equal to submitted string; response 201 excludes password by default.
- **AC-Read-Plain-02:** GET `/records?includePassword=true` returns each item with a `password` field identical to the stored value.
- **AC-Update-Plain-03:** PATCH with new `password` updates stored value; subsequent GET with include flag returns the new password.
- **AC-Delete-01:** DELETE removes row; subsequent GET `/:id` returns 404.
- **AC-Conflict-Email:** Creating two records with same email (any case) returns 409 on second.

## 12. Out of Scope (v1.1)
- Production security (hashing, auth, RBAC).
- Audit logs, soft deletes.
- Pagination/search (beyond simple list).
- Email delivery.

## 13. Future Enhancements
- Switch to secure storage (**Argon2id/bcrypt**) and never return passwords.
- Auth (sessions/JWT), RBAC.
- Pagination, filtering, sorting.
- Docker/CI/CD; Postgres/MySQL; audit trails; soft delete.
