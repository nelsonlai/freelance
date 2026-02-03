# PawMatch Backend API

A Flask-based backend API for the PawMatch cat matching and health analysis platform.

## Project Overview

This is a cat matching and health consultation platform that allows users to:
- Register with their cat's profile and health information
- Match their cat with other registered cats based on compatibility
- Get AI-powered health and breeding advice using Poe/GPT
- Generate AI kitten images using OpenRouter
- Admin dashboard for managing users, reports, and webhook logs

## Project Structure

```
back_web-4/
├── run.py                    # Application entry point
├── .env                      # Environment configuration
├── data.db                   # SQLite database
├── app/
│   ├── __init__.py           # Flask app factory
│   ├── config.py             # Configuration class
│   ├── routes/
│   │   ├── auth.py           # User authentication (register/login)
│   │   ├── cat_register.py   # Cat profile registration
│   │   ├── match.py          # Cat matching API
│   │   ├── reports.py        # User reports API
│   │   ├── uploads.py        # File serving for uploads
│   │   ├── health.py         # Health check endpoint
│   │   ├── make_webhook.py   # Make.com webhook integration
│   │   ├── admin_ingest.py   # Form data ingestion
│   │   ├── admin_stats.py    # Analytics/statistics API
│   │   └── api_auth.py       # API authentication
│   ├── admin/
│   │   ├── __init__.py
│   │   ├── auth.py           # Admin authentication
│   │   └── routes.py         # Admin dashboard routes
│   ├── services/
│   │   ├── storage.py        # SQLite database layer
│   │   ├── poe_client.py     # Poe API client
│   │   └── poe_analyze.py    # AI analysis & image generation
│   ├── utils/
│   │   ├── auth.py           # JWT & session utilities
│   │   └── logger.py         # Logging configuration
│   └── templates/
│       └── admin/            # Admin dashboard HTML templates
├── uploads/                  # User-uploaded files
├── photo/                    # Static cat photos
└── logs/                     # Application logs
```

## Prerequisites

- Python 3.9 or higher
- pip (Python package manager)

## Installation

1. **Clone the repository** (if not already done):
   ```bash
   cd /path/to/back_web-4
   ```

2. **Create a virtual environment** (recommended):
   ```bash
   python3 -m venv venv
   source venv/bin/activate  # On macOS/Linux
   # or
   venv\Scripts\activate     # On Windows
   ```

3. **Install dependencies**:
   ```bash
   pip install -r requirements.txt
   ```

4. **Configure environment variables**:
   
   Copy or edit the `.env` file with your settings:
   ```bash
   # Flask
   FLASK_ENV=development
   PORT=5050
   
   # Security
   SECRET_KEY=your-secret-key-here
   JWT_SECRET=your-jwt-secret-here
   MAKE_WEBHOOK_SECRET=your-webhook-secret
   MAKE_API_KEY=your-make-api-key
   
   # Admin bootstrap (optional - creates admin on first run)
   ADMIN_EMAIL=admin@example.com
   ADMIN_PASSWORD=your-secure-password
   
   # CORS
   CORS_ORIGINS=http://localhost:3000
   
   # Storage
   SQLITE_PATH=./data.db
   UPLOAD_DIR=./uploads
   
   # Poe API (for AI analysis)
   POE_API_KEY=your-poe-api-key
   POE_BASE_URL=https://api.explinks.com
   POE_ENDPOINT=/poe/v1/analyze
   POE_TIMEOUT=45
   
   # OpenRouter (for image generation)
   OPENROUTER_API_KEY=your-openrouter-api-key
   ```

## Running the Application

### Development Mode

```bash
python run.py
```

The server will start on `http://0.0.0.0:5050` with debug mode enabled.

### Production Mode

For production, use a WSGI server like Gunicorn:

```bash
pip install gunicorn
gunicorn -w 4 -b 0.0.0.0:5050 "app:create_app()"
```

## API Endpoints

### Public Endpoints

| Method | Endpoint | Description |
|--------|----------|-------------|
| GET | `/health` | Health check |
| POST | `/auth/register` | User registration |
| POST | `/auth/login` | User login |
| POST | `/api/cat-questionnaire` | Register user with cat profile |

### Protected Endpoints (Require JWT)

| Method | Endpoint | Description |
|--------|----------|-------------|
| GET | `/api/match-result` | Get cat matching results with AI analysis |
| GET | `/api/reports` | List user's reports |
| GET | `/api/report/<id>` | Get specific report |

### Admin Endpoints

| Method | Endpoint | Description |
|--------|----------|-------------|
| GET/POST | `/admin/login` | Admin login page |
| GET | `/admin/logout` | Admin logout |
| GET | `/admin/` | Admin dashboard |
| GET/POST | `/admin/users` | User management |
| GET | `/admin/reports` | View all reports |
| GET | `/admin/webhooks` | View webhook logs |

### Admin API Endpoints (Require Admin Session)

| Method | Endpoint | Description |
|--------|----------|-------------|
| GET | `/api/admin/stats/kpis` | KPI summary |
| GET | `/api/admin/stats/cat-breed` | Cat breed distribution |
| GET | `/api/admin/stats/cat-sex` | Cat sex distribution |
| GET | `/api/admin/stats/cat-source` | Cat source distribution |
| GET | `/api/admin/stats/vet-frequency` | Vet visit frequency |
| GET | `/api/admin/stats/hist/*` | Various histograms |

### Webhook Endpoints

| Method | Endpoint | Description |
|--------|----------|-------------|
| POST | `/webhook/make` | Make.com webhook receiver |
| POST | `/api/admin/form-ingest` | Form data ingestion |

### Static Files

| Method | Endpoint | Description |
|--------|----------|-------------|
| GET | `/uploads/<filename>` | Serve uploaded files |

## Authentication

### User Authentication (JWT)

For protected API endpoints, include the JWT token in the Authorization header:

```
Authorization: Bearer <your-jwt-token>
```

### Admin Authentication (Session)

Admin routes use Flask session-based authentication. Log in via `/admin/login`.

### Webhook Authentication

Webhooks require the `X-Make-Secret` header matching the `MAKE_WEBHOOK_SECRET` env variable.

## Database

The application uses SQLite with the following tables:

- `users` - User accounts with roles (user, admin, super_admin)
- `cats` - Cat profiles linked to users
- `reports` - AI analysis reports
- `webhook_logs` - Incoming webhook logs
- `form_raw` - Raw form submissions
- `form_answers` - Structured form answers for analytics

The database is automatically initialized on first run.

## Logging

Logs are written to:
- Console output
- `logs/app.log` file

## Troubleshooting

### Common Issues

1. **Port already in use**:
   ```bash
   # Find and kill the process using port 5050
   lsof -i :5050
   kill -9 <PID>
   ```

2. **Missing dependencies**:
   ```bash
   pip install -r requirements.txt
   ```

3. **Database errors**:
   Delete `data.db` to reset the database (all data will be lost).

4. **CORS errors**:
   Update `CORS_ORIGINS` in `.env` to include your frontend URL.

## License

Private/Proprietary - All rights reserved.
