# Lesson 5: Project Deployment

## 🎯 Learning Objectives

By the end of this lesson, you will be able to:

- Deploy frontend applications to Vercel/Netlify
- Deploy backend applications to Heroku/Railway
- Configure environment variables
- Set up custom domains
- Monitor application performance
- Handle production issues

## 📚 Deployment Platforms

### Frontend Deployment (Vercel)
```bash
# Install Vercel CLI
npm install -g vercel

# Deploy from project directory
vercel

# Set environment variables
vercel env add API_URL
vercel env add DATABASE_URL

# Deploy to production
vercel --prod
```

### Backend Deployment (Heroku)
```bash
# Install Heroku CLI
# Create Procfile
echo "web: node server.js" > Procfile

# Initialize Heroku app
heroku create my-app-name

# Set environment variables
heroku config:set NODE_ENV=production
heroku config:set DATABASE_URL=postgres://...

# Deploy
git push heroku main
```

## 🎯 Practice Exercises

### Exercise 1: Full-Stack Deployment
Deploy a complete full-stack application:

**Solution:**
```bash
# Frontend deployment (Vercel)
# 1. Build frontend
cd frontend
npm run build

# 2. Deploy to Vercel
vercel

# 3. Set environment variables
vercel env add REACT_APP_API_URL production

# Backend deployment (Railway)
# 1. Create railway.json
echo '{
  "build": {
    "builder": "NIXPACKS"
  },
  "deploy": {
    "startCommand": "npm start",
    "healthcheckPath": "/health"
  }
}' > railway.json

# 2. Deploy to Railway
railway login
railway init
railway up

# 3. Set environment variables
railway variables set NODE_ENV=production
railway variables set DATABASE_URL=postgres://...
```

## 🎯 Key Takeaways

1. **Vercel/Netlify** deploy frontend applications
2. **Heroku/Railway** deploy backend applications
3. **Environment variables** configure production settings
4. **Custom domains** provide professional URLs
5. **Monitoring** tracks application health

---

**Next Lesson**: [Lesson 6: Capstone Project - Personal Portfolio](./lesson6-portfolio.md)
