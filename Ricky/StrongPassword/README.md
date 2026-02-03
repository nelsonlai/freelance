# Password CRUD Demo Application

A demonstration web application for password CRUD operations with **plain text storage** (demo purposes only).

## ⚠️ Security Warning

**This application stores passwords in plain text for demonstration purposes only.**
- **DO NOT** use in production environments
- **DO NOT** deploy to public servers
- This is intended for local development and learning purposes only

## 🏗️ Architecture

- **Frontend**: Next.js 14 with TypeScript and Tailwind CSS
- **Backend**: Express.js with TypeScript
- **Database**: SQLite with Prisma ORM
- **Password Storage**: Plain text (demo only)

## 🚀 Quick Start

### Prerequisites

- Node.js 20.x or higher
- npm or yarn

### Installation

1. **Clone and install dependencies:**
   ```bash
   git clone <repository-url>
   cd StrongPassword
   npm run install:all
   ```

2. **Set up the database:**
   ```bash
   npm run db:generate
   npm run db:migrate
   ```

3. **Start the development servers:**
   ```bash
   npm run dev
   ```

This will start both the backend (port 4000) and frontend (port 3000) concurrently.

### Manual Setup

If you prefer to run services separately:

**Backend:**
```bash
cd backend
npm install
npm run dev
```

**Frontend:**
```bash
cd frontend
npm install
npm run dev
```

## 📁 Project Structure

```
StrongPassword/
├── backend/                 # Express.js backend
│   ├── src/
│   │   ├── controllers/    # Request handlers
│   │   ├── services/       # Business logic
│   │   ├── routes/         # API routes
│   │   ├── middleware/     # Express middleware
│   │   ├── validation/     # Input validation schemas
│   │   └── types/          # TypeScript type definitions
│   ├── prisma/             # Database schema and migrations
│   └── package.json
├── frontend/               # Next.js frontend
│   ├── src/
│   │   ├── app/           # Next.js app directory
│   │   ├── components/    # React components
│   │   ├── services/      # API client
│   │   ├── types/         # TypeScript type definitions
│   │   └── utils/         # Utility functions
│   └── package.json
├── package.json            # Root package.json with scripts
└── README.md
```

## 🔧 Configuration

### Backend Environment Variables

Create a `.env` file in the `backend/` directory:

```env
DATABASE_URL="file:./dev.db"
PORT=4000
CORS_ORIGIN=http://localhost:3000
ALLOW_PASSWORD_IN_RESPONSE=true
NODE_ENV=development
```

### Frontend Configuration

The frontend is configured to proxy API requests to the backend via Next.js rewrites.

## 🗄️ Database

### Prisma Schema

```prisma
model Record {
  id        String   @id @default(cuid())
  username  String   @unique
  email     String   @unique
  password  String   // PLAINTEXT FOR DEMO ONLY
  createdAt DateTime @default(now())
  updatedAt DateTime @updatedAt

  @@map("records")
}
```

### Database Commands

```bash
# Generate Prisma client
npm run db:generate

# Run migrations
npm run db:migrate

# Open Prisma Studio (database browser)
npm run db:studio
```

## 🌐 API Endpoints

**Base URL:** `http://localhost:4000/api/v1`

### Records

- `POST /records` - Create a new record
- `GET /records` - Get all records (optional: `?includePassword=true`)
- `GET /records/:id` - Get a specific record (optional: `?includePassword=true`)
- `PATCH /records/:id` - Update a record
- `DELETE /records/:id` - Delete a record

### Health Check

- `GET /health` - Server health status

## 🎯 Features

### Password Generator
- Configurable length (8-64 characters)
- Character class toggles (uppercase, lowercase, numbers, symbols)
- Ensures at least one character from each enabled class
- Password strength indicator
- Copy to clipboard functionality

### Record Management
- Create, read, update, delete operations
- Input validation (client and server-side)
- Username and email uniqueness checks
- Optional password visibility toggle
- Responsive table layout

### Security Features (Demo Only)
- Rate limiting (100 requests per 15 minutes per IP)
- Input validation and sanitization
- CORS configuration
- Helmet.js security headers

## 🧪 Testing

### Backend Tests
```bash
cd backend
npm test
```

### Frontend Tests
```bash
cd frontend
npm test
```

## 🚀 Production Deployment

**⚠️ IMPORTANT: This application is NOT suitable for production use.**

If you want to adapt this for production:

1. **Remove plain text password storage**
2. **Implement proper password hashing** (Argon2id, bcrypt)
3. **Add authentication and authorization**
4. **Use environment-specific configuration**
5. **Implement proper logging and monitoring**
6. **Add HTTPS and security headers**
7. **Use a production database** (PostgreSQL, MySQL)

## 📝 Development

### Available Scripts

**Root:**
- `npm run dev` - Start both frontend and backend
- `npm run install:all` - Install all dependencies
- `npm run build` - Build both applications

**Backend:**
- `npm run dev` - Start development server with hot reload
- `npm run build` - Build for production
- `npm start` - Start production server

**Frontend:**
- `npm run dev` - Start development server
- `npm run build` - Build for production
- `npm start` - Start production server

### Code Quality

- TypeScript for type safety
- ESLint for code linting
- Prettier for code formatting
- Tailwind CSS for styling

## 🤝 Contributing

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Add tests if applicable
5. Submit a pull request

## 📄 License

This project is licensed under the MIT License.

## ⚠️ Disclaimer

This application is provided as-is for educational and demonstration purposes. The authors are not responsible for any misuse or security incidents that may occur from using this code in production environments.

**Remember: Never store passwords in plain text in real applications!**
