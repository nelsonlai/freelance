# Questionnaire System

A production-ready questionnaire system built with Next.js frontend and Express backend, featuring MySQL database integration via Prisma ORM.

## 🚀 Features

- **Frontend**: Modern Next.js application with TypeScript and Tailwind CSS
- **Backend**: Express API with comprehensive validation and security
- **Database**: MySQL integration with Prisma ORM
- **Security**: Rate limiting, CORS protection, input sanitization
- **Validation**: Client and server-side validation with Zod schemas
- **Responsive**: Mobile-friendly UI with modern design

## 🏗️ Architecture

```
┌─────────────────┐    ┌─────────────────┐    ┌─────────────────┐
│   Next.js       │    │   Express API   │    │   MySQL         │
│   Frontend      │◄──►│   Backend       │◄──►│   Database      │
│   (Port 3000)   │    │   (Port 4000)   │    │   (AWS RDS)     │
└─────────────────┘    └─────────────────┘    └─────────────────┘
```

## 📋 Prerequisites

- Node.js 18+ 
- npm or yarn
- MySQL database (AWS RDS or local)
- Git

## 🛠️ Installation

### 1. Clone the repository
```bash
git clone <repository-url>
cd questionnaire-system
```

### 2. Install dependencies
```bash
npm run install:all
```

### 3. Environment Configuration

#### Backend Configuration
Create a `.env` file in the `backend` directory:

```bash
cd backend
cp env.example .env
```

Edit the `.env` file with your database credentials:

```env
# Database connection string for MySQL (AWS RDS)
DATABASE_URL="mysql://username:password@your-aws-rds-endpoint:3306/mini_form"

# Server configuration
PORT=4000
NODE_ENV=development

# CORS configuration
CORS_ORIGIN=http://localhost:3000

# Security configuration
IP_SALT=your-random-salt-here-change-this-in-production

# Rate limiting
RATE_LIMIT_WINDOW_MS=60000
RATE_LIMIT_MAX_REQUESTS=60
```

#### Frontend Configuration
Create a `.env.local` file in the `frontend` directory:

```bash
cd ../frontend
touch .env.local
```

Add the following content:

```env
NEXT_PUBLIC_API_BASE_URL=http://localhost:4000
```

### 4. Database Setup

#### Using AWS RDS MySQL
1. Create a MySQL database in AWS RDS
2. Note the endpoint, port, username, and password
3. Update the `DATABASE_URL` in your backend `.env` file
4. Create a database named `mini_form`

#### Local MySQL (Alternative)
```bash
# Install MySQL locally or use Docker
docker run --name mysql-questionnaire \
  -e MYSQL_ROOT_PASSWORD=root \
  -e MYSQL_DATABASE=mini_form \
  -e MYSQL_USER=user \
  -e MYSQL_PASSWORD=pass \
  -p 3306:3306 \
  -d mysql:8.0
```

### 5. Database Migration
```bash
cd backend

# Generate Prisma client
npm run db:generate

# Run database migrations
npm run db:migrate

# (Optional) Seed with sample data
npm run db:seed
```

## 🚀 Running the Application

### Development Mode
```bash
# Start both frontend and backend
npm run dev

# Or start them separately:
npm run dev:frontend  # Frontend on port 3000
npm run dev:backend   # Backend on port 4000
```

### Production Mode
```bash
# Build the application
npm run build

# Start production servers
npm run start
```

## 📱 Usage

### 1. Access the Application
- Frontend: http://localhost:3000
- Backend API: http://localhost:4000

### 2. Fill Out the Questionnaire
- Navigate to the questionnaire form
- Answer the questions (mix of single choice, multi-choice, and text)
- Submit your responses

### 3. View Confirmation
- After successful submission, you'll be redirected to a thank you page
- Note your response ID for future reference

## 🔌 API Endpoints

### POST /api/v1/responses
Create a new questionnaire response.

**Request:**
```json
{
  "answers": {
    "q1": "A",
    "q2": ["X", "Y"],
    "q3": "Additional comments"
  }
}
```

**Response:**
```json
{
  "id": "ckxyz...",
  "createdAt": "2025-01-23T10:00:00Z"
}
```

### GET /api/v1/responses/:id
Retrieve a specific response by ID.

### GET /api/v1/metrics
Get aggregated metrics for all responses.

**Query Parameters:**
- `from`: Start date (ISO format)
- `to`: End date (ISO format)

**Response:**
```json
{
  "totalSubmissions": 123,
  "counts": {
    "q1": { "A": 40, "B": 60, "C": 23 },
    "q2": { "X": 70, "Y": 53, "Z": 12 }
  }
}
```

## 🧪 Testing

### Backend Tests
```bash
cd backend

# Run all tests
npm test

# Run tests in watch mode
npm run test:watch

# Run tests with coverage
npm test -- --coverage
```

### Frontend Tests
```bash
cd frontend

# Run linting
npm run lint

# Type checking
npm run type-check
```

## 📊 Database Schema

The system uses a simple schema with a single `Response` table:

```sql
model Response {
  id         String   @id @default(cuid())
  answers    Json     // Question answers as JSON
  userAgent  String?  // Optional user agent
  ipHash     String?  // Hashed IP address for privacy
  createdAt  DateTime @default(now())
}
```

## 🔒 Security Features

- **Input Validation**: Comprehensive validation using Zod schemas
- **Rate Limiting**: 60 requests per minute per IP
- **CORS Protection**: Restricted to specified origins
- **Input Sanitization**: XSS protection and HTML stripping
- **IP Hashing**: Privacy-preserving IP address storage
- **Request IDs**: Unique identifiers for request tracking

## 🚀 Deployment

### Backend Deployment
1. Build the application: `npm run build`
2. Set production environment variables
3. Deploy to your preferred hosting service (Heroku, AWS, etc.)

### Frontend Deployment
1. Build the application: `npm run build`
2. Deploy to Vercel, Netlify, or your preferred hosting service
3. Update the `NEXT_PUBLIC_API_BASE_URL` to point to your production backend

### Database Deployment
- Use AWS RDS MySQL for production
- Ensure proper security groups and network access
- Regular backups and monitoring

## 🐛 Troubleshooting

### Common Issues

#### Database Connection Issues
- Verify your `DATABASE_URL` is correct
- Ensure the database is accessible from your application
- Check firewall and security group settings

#### CORS Errors
- Verify `CORS_ORIGIN` is set correctly
- Ensure frontend and backend ports match

#### Rate Limiting
- Check if you're hitting the rate limit (60 req/min)
- Adjust limits in `.env` if needed

### Logs
- Backend logs are displayed in the console
- Check for request IDs in error messages
- Use `x-request-id` header for request tracking

## 📈 Monitoring

### Health Check
- Endpoint: `GET /health`
- Returns server status and timestamp

### Metrics
- Use the metrics endpoint to monitor response patterns
- Track total submissions and answer distributions

## 🤝 Contributing

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Add tests for new functionality
5. Submit a pull request

## 📄 License

This project is licensed under the MIT License.

## 🆘 Support

For support and questions:
- Check the troubleshooting section
- Review the API documentation
- Create an issue in the repository

---

**Built with ❤️ using Next.js, Express, and Prisma**
