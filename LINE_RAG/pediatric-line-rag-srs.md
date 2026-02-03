# Software Requirements Specification (SRS)

**Project:** Pediatric Q&A via LINE (Python Flask + LINE + RAG with OpenAI)

**Version:** 1.0 (2025‑08‑25)

**Owner:** Pediatrics practice (clinic or hospital department)

**Prepared for:** Clinical lead (Pediatrician), Product owner, Engineering team

---

## 1. Purpose & Scope

### 1.1 Purpose
Enable parents/guardians to ask non‑urgent pediatric questions via LINE. The system provides a safe, multilingual, AI‑assisted answer (RAG over trusted pediatric content) and routes higher‑risk or unclear cases to a pediatrician for review.

### 1.2 Scope
- **In‑scope**: LINE bot, webhook/API (Flask), RAG pipeline (OpenAI + vector DB), staff console (review/override), triage/safety guardrails, analytics, consent & privacy controls, logging & audit.
- **Out‑of‑scope (MVP)**: Emergency care, diagnosis/prescription, real‑time telemedicine, billing, EHR integration (optional later), voice calls.

### 1.3 Goals
- Reduce repetitive questions handled by clinicians while improving response quality and time.
- Provide reliable, cited, plain‑language pediatric guidance with strong safety triage.
- Support English + Traditional Chinese (extendable to other languages).

---

## 2. Stakeholders & Personas
- **Parent/Guardian (end user)**: Asks questions via LINE; expects fast, clear, safe guidance and links to reputable sources.
- **Pediatrician (clinician reviewer)**: Reviews escalations, edits responses, sets content policy; needs audit trails.
- **Moderator/Coordinator**: Triage inbox, manage FAQ/knowledge, handle abuse/spam.
- **Administrator/Owner**: Configure clinic hours, disclaimers, consent, data retention.

---

## 3. Assumptions & Constraints
- Non‑urgent use only; clear **emergency disclaimers**.
- Content sources are reputable and licensed/allowable for internal use (e.g., local pediatric guidelines, CPS/AAP public materials, clinic leaflets, clinic policy documents).
- Hosting in a region compliant with applicable privacy law (e.g., Canada: PIPEDA/PHIPA) and clinic policy; encryption in transit/at rest.
- LINE Messaging API available and clinic can register a provider/channel.

---

## 4. User Stories (selected)
1. As a **parent**, I want to ask a question about my child’s fever and receive a concise, safe answer with references.
2. As a **parent**, I want the bot to ask follow‑up questions (age, temperature, duration) so advice is tailored.
3. As a **clinician**, I want high‑risk questions flagged for my review before anything is sent back.
4. As a **moderator**, I want to see a queue of escalations and send templated replies.
5. As an **administrator**, I want to configure disclaimers, hours, auto‑reply rules, languages, and data retention.
6. As a **parent**, I want my language automatically detected and answered in that language.
7. As a **clinician**, I want to see which sources were cited in an answer.

---

## 5. Functional Requirements

### 5.1 Messaging & Conversation
- **FR‑M1**: Receive LINE messages (text, images optional later) via `/line/webhook`.
- **FR‑M2**: Validate `X‑Line‑Signature`; reject invalid requests.
- **FR‑M3**: Handle: new question, bot clarifying questions, user follow‑ups, closing.
- **FR‑M4**: Persist conversations, messages, user profile (LINE userId, locale) with consent status.
- **FR‑M5**: Multilingual: detect language; reply in user’s language (start with EN/繁體中文).

### 5.2 Triage & Safety
- **FR‑T1**: Classify each message into **Emergency/High‑risk**, **Needs clinician review**, or **OK to auto‑answer** using rules + model (age <3 months with fever; severe symptoms keywords; suicidal ideation; medication dosing requests without enough context; etc.).
- **FR‑T2**: If **Emergency** → **do not** provide medical advice; send localized emergency guidance (e.g., “call emergency services / visit ER now”) and alert clinician inbox (optional SMS/email).
- **FR‑T3**: If **Needs review** → queue item to staff console; hold reply until approved.
- **FR‑T4**: Always display disclaimer + source citations for AI answers.

### 5.3 RAG Answering
- **FR‑R1**: Ingest and index trusted pediatric documents; chunk and embed.
- **FR‑R2**: Retrieve top‑k relevant chunks for a question; build a structured prompt that:
  - requests **step‑by‑step reasoning internally** but returns only the **final answer** in parent‑friendly language,
  - includes **safety checklist** (age, red‑flags, when to seek care),
  - requires **citations** back to the ingested sources.
- **FR‑R3**: Enforce **grounding**: if retrieval confidence low → ask for clarifying info or escalate.
- **FR‑R4**: Log answer, citations, and retrieval score for audit.

### 5.4 Staff Console (Web)
- **FR‑C1**: Secure login (clinic SSO or email+2FA).
- **FR‑C2**: Work queue: escalations, drafts, audit history, search.
- **FR‑C3**: Edit/approve AI draft; send final via LINE.
- **FR‑C4**: Knowledge manager: upload/update documents; re‑index.
- **FR‑C5**: Configuration: disclaimers, intake forms, languages, clinic hours, routing rules.

### 5.5 Consent & Privacy
- **FR‑P1**: On first contact, present consent & privacy notice; record acceptance.
- **FR‑P2**: Allow user to request data deletion; administrator can export/anonymize.
- **FR‑P3**: Respect data retention policy (e.g., delete/anonymize after X days unless legally required to retain).

### 5.6 Analytics & Ops
- **FR‑A1**: Metrics: median time to response, % auto‑answered, escalation rate, safety‑intercept rate, language distribution.
- **FR‑A2**: Alerts: webhook failures, vector DB errors, OpenAI errors, abnormal escalation spikes.

---

## 6. Non‑Functional Requirements (NFR)
- **NFR‑1 Availability:** 99.9% monthly for webhook and console.
- **NFR‑2 Latency:** P95 end‑to‑end auto‑answer ≤ 6 s; escalations acknowledged within 10 s.
- **NFR‑3 Security:** TLS 1.2+; at‑rest encryption for DB and vector store; rotation of LINE/OpenAI secrets; RBAC & audit.
- **NFR‑4 Privacy/Compliance:** PIPEDA/PHIPA‑aligned handling; data residency per clinic policy; DPIA/Threat model maintained (not legal advice).
- **NFR‑5 Accessibility:** Console WCAG 2.1 AA; bot replies readable at grade‑8 level where possible.
- **NFR‑6 Internationalization:** i18n framework; Unicode throughout; locale‑aware formatting.

---

## 7. Data Model (MVP)

**users**(id, line_user_id, display_name, language, consent_status, created_at)

**conversations**(id, user_id, status[open|pending|closed], risk_level, created_at, updated_at)

**messages**(id, conversation_id, role[user|assistant|clinician], content, language, risk_flags, citations_json, created_at)

**documents**(id, title, source_url, license, version, uploaded_by, created_at)

**chunks**(id, document_id, chunk_index, text)

**embeddings**(id, chunk_id, provider, vector)

**escalations**(id, conversation_id, reason, assigned_to, status, created_at, resolved_at)

**audit_logs**(id, actor, action, target, metadata_json, created_at)

**settings**(key, value_json)

---

## 8. External Interfaces

### 8.1 LINE Messaging API
- Webhook endpoint: `POST /line/webhook`
- Signature: `X‑Line‑Signature` HMAC‑SHA256 (channel secret)
- Reply via `replyMessage` with `replyToken` within 1 minute; use `pushMessage` for later sends.

### 8.2 OpenAI API
- **Embeddings**: text‑embedding‑3‑large (or current equivalent).
- **Responses/Chat**: latest GPT family; tools/function‑calling for structured outputs (triage JSON, answer JSON).
- **Moderation**: content safety screening.

### 8.3 Vector Store
- FAISS (embedded) or Postgres + pgvector (managed). Support cosine similarity and metadata filters (age/topic).

---

## 9. Safety, Clinical Governance & Disclaimers
- **Emergency redirect**: If red‑flag symptoms or insufficient info for safe advice, provide emergency guidance and **do not** generate care instructions.
- **Human‑in‑the‑loop**: High‑risk → clinician approval required.
- **Citations & date stamps**: Include source titles and last‑updated dates where possible.
- **Medication**: Provide ranges only if source explicitly supports; otherwise escalate.
- **Privacy**: Remind parents not to send photos of private areas or full identifiers.
- **Audit**: All AI outputs and clinician edits are stored for review.

**Sample disclaimer (EN):** “This service offers general pediatric information and is **not** a medical diagnosis. If your child has severe symptoms (e.g., difficulty breathing, bluish lips, seizures), seek emergency care immediately.” (Provide localized variants.)

---

## 10. Acceptance Criteria (MVP)
- Webhook validates signature and handles text messages.
- RAG returns an answer with ≥2 source citations when confidence is adequate.
- Emergency keyword test cases trigger emergency template, not AI advice.
- Staff console allows approval and push reply back to LINE.
- Consent recorded before storing conversations.

---

## 11. Testing Strategy (overview)
- Unit: parsing events, signature check, RAG retriever, prompt builder, safety rules.
- Integration: end‑to‑end LINE → webhook → RAG → reply; error injection.
- Clinical QA: pediatrician reviews a stratified sample before launch; periodic spot checks.
- Load: 20 RPS sustained webhook; vector queries p95 < 100 ms (warm cache).

---

## 12. Risks & Mitigations
- **Hallucination or outdated guidance** → Strict grounding; low‑confidence escalation; source freshness trackers.
- **Privacy breach** → Encryption, least‑privilege, incident response runbook.
- **Misuse/abuse** → Rate limits, moderation, blocklist.
- **Vendor outages** → Circuit breaker, graceful degradation, queueing, cached FAQs.

---

# Software Architecture

## A. High‑Level Overview

```
[Parent on LINE]
     |
     v
[LINE Messaging API]  ———>  [Flask Webhook /line/webhook]
                                   |
                      +------------+-------------+
                      |                          |
                 [Safety/Triage]           [Conversation Manager]
                      |                          |
          (Emergency? escalate)                  v
                      |                   [RAG Orchestrator]
                      |                          |
                      |                 +--------+---------+
                      |                 |                  |
                 [Clinician Console]  [Vector Store]   [OpenAI API]
                      |                          \      /
                      v                           [Answer]
                [Approve/Send]                         |
                      |                                 v
                      +----------------------------> [LINE Reply]
```

## B. Components

1. **Flask App**
   - Endpoints: `/healthz`, `/line/webhook`, `/admin/*` (console API), `/docs/*` (document admin)
   - Middleware: auth, rate limit, request/response logging (PII‑safe), locale detection.

2. **Message Router**
   - Parses LINE events, deduplicates, manages reply tokens vs push messages.

3. **Safety/Triage Service**
   - Rules (age <3 mo + fever, dehydration, respiratory distress keywords, self‑harm) + model score.
   - Outputs `{risk_level, reasons[], required_fields[]}`.

4. **RAG Orchestrator**
   - Query rewriting (expand symptoms, extract entities: age, duration, temp, meds);
   - Retrieval (top‑k, MMR); cite sources; build prompt (system + context + user + safety checklist).
   - Post‑processing: ensure language, reading level, bullet formatting, citations.

5. **Vector Store**
   - FAISS/pgvector; metadata: topic, age range, last_updated, source.

6. **OpenAI Client**
   - Embeddings creation, chat/responses, moderation; retry with backoff; circuit breaker.

7. **Clinician/Moderator Console** (Flask/HTMX or Flask + React later)
   - Secure auth (RBAC); queues; diff of AI vs final; content manager; settings.

8. **Background Jobs** (Celery/RQ + Redis)
   - Re‑index docs, delayed push messages, nightly health checks, analytics aggregation.

9. **Storage**
   - Postgres/MySQL for relational data; S3‑compatible for document files.

10. **Observability**
   - Structured logs, traces, metrics; alerting on failures.

## C. Sequence (Auto‑answer path)

1. Parent sends LINE text → LINE forwards to `/line/webhook`.
2. Flask verifies signature and enqueues event.
3. Safety/Triage evaluates; if safe → proceed, else emergency or escalate.
4. RAG Orchestrator retrieves chunks; builds prompt; calls OpenAI; enforces style & citations.
5. Reply sent via `replyMessage` (or `pushMessage` if delayed). Conversation stored.

## D. Deployment Topology (MVP)
- **Ingress/Nginx** → **Flask (Gunicorn, 2–4 workers)** → **Redis** (queue) → **Worker** → **DB** (Postgres/MySQL) + **Vector DB** (pgvector/FAISS) + **Object store**.
- HTTPS with Let’s Encrypt; environment secrets via vault or cloud secret manager.

## E. Configuration (env examples)
```
LINE_CHANNEL_SECRET=...
LINE_CHANNEL_ACCESS_TOKEN=...
OPENAI_API_KEY=...
DB_URL=postgresql+psycopg2://user:pass@host:5432/peds
VECTOR_DB_URL=postgresql://user:pass@host:5432/peds
ALLOWED_LANGS=en,zh-Hant
RETENTION_DAYS=365
```

## F. Prompt & Tools (sketch)
**System prompt excerpt:**
- You are a pediatric information assistant. Provide **general information only**, not diagnosis. Always include **when to seek urgent care** and **source citations**.
- Ask for **age, weight, duration, temperature, medications** if missing.
- Keep answers in the user’s language.

**Function/tool schema (examples):**
- `triage_symptoms(input) -> {risk_level, reasons[], missing_fields[]}`
- `retrieve_context(query, age_months, locale) -> [chunks]`

## G. Safety Rules (examples)
- Age <3 months with fever ≥38°C → **Emergency advice** only.
- Respiratory distress keywords or cyanosis → emergency template.
- Dosing questions without weight → ask for weight or escalate.
- Suicidal/self‑harm → crisis resources; notify clinician (per policy).

## H. Minimal DB Schema (DDL sketch)
```sql
CREATE TABLE users (
  id BIGSERIAL PRIMARY KEY,
  line_user_id TEXT UNIQUE NOT NULL,
  display_name TEXT,
  language TEXT DEFAULT 'en',
  consent_status TEXT NOT NULL CHECK (consent_status IN ('pending','accepted','declined')),
  created_at TIMESTAMP NOT NULL DEFAULT NOW()
);

CREATE TABLE conversations (
  id BIGSERIAL PRIMARY KEY,
  user_id BIGINT REFERENCES users(id),
  status TEXT NOT NULL CHECK (status IN ('open','pending','closed')),
  risk_level TEXT CHECK (risk_level IN ('low','review','emergency')),
  created_at TIMESTAMP NOT NULL DEFAULT NOW(),
  updated_at TIMESTAMP NOT NULL DEFAULT NOW()
);

CREATE TABLE messages (
  id BIGSERIAL PRIMARY KEY,
  conversation_id BIGINT REFERENCES conversations(id),
  role TEXT NOT NULL CHECK (role IN ('user','assistant','clinician')),
  content TEXT NOT NULL,
  language TEXT,
  risk_flags JSONB,
  citations JSONB,
  created_at TIMESTAMP NOT NULL DEFAULT NOW()
);
```

## I. Logging & Analytics
- **PII‑aware logging**: redact identifiers and temperatures if configured; full content only in secure store.
- **Dashboards**: response times, escalation rate, topic distribution.

## J. Rollout Plan
1. **Week 1–2**: LINE bot registration, Flask skeleton, webhook validation.
2. **Week 3–4**: Vector DB + ingestion pipeline; initial RAG; English only.
3. **Week 5–6**: Safety rules, clinician console (approve/send), Traditional Chinese.
4. **Week 7**: Clinical QA, red‑team tests, DPIA review, go‑live to pilot cohort.

## K. Open Questions
- Exact list of approved sources and licensing status?
- Data residency requirements (province/country)?
- Escalation SLA during off‑hours?
- Photo handling (enable later with explicit consent)?

---

## Appendix: Example Intake & Reply Templates

**Intake (auto‑ask if missing):**
- Child’s **age** and **weight**
- **Main concern** and **duration**
- **Temperature** and method (oral/axillary/tympanic)
- Any **medications** given (name, dose, time)
- **Red‑flag** symptoms (breathing difficulty, dehydration, seizure)

**Reply skeleton:**
1) Summary of what you told us
2) What’s typical for this age
3) Home care steps (if appropriate)
4) **When to seek urgent care** (clear bullets)
5) References (titles/links)
6) Disclaimer
