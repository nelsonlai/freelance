# Lesson 3: Version Control (Git/GitHub)

## 🎯 Learning Objectives

By the end of this lesson, you will be able to:

- Use Git for version control
- Create and manage repositories
- Work with branches and merges
- Collaborate using GitHub
- Handle merge conflicts
- Follow Git best practices

## 📚 Git Fundamentals

### Basic Git Commands
```bash
# Initialize repository
git init

# Add files to staging
git add .
git add filename.js

# Commit changes
git commit -m "Add user authentication"

# Check status
git status

# View commit history
git log --oneline

# Create and switch to branch
git checkout -b feature/new-feature

# Merge branches
git merge feature/new-feature

# Push to remote
git push origin main
```

### Git Workflow
```bash
# 1. Create feature branch
git checkout -b feature/user-dashboard

# 2. Make changes and commit
git add .
git commit -m "Add user dashboard component"

# 3. Push branch to remote
git push origin feature/user-dashboard

# 4. Create pull request on GitHub
# 5. After review, merge to main
git checkout main
git pull origin main
git merge feature/user-dashboard
git push origin main
```

## 🎯 Practice Exercises

### Exercise 1: Git Repository Setup
Set up a complete Git workflow:

**Solution:**
```bash
# Initialize repository
git init
git config user.name "Your Name"
git config user.email "your.email@example.com"

# Create .gitignore
echo "node_modules/" >> .gitignore
echo "*.log" >> .gitignore
echo ".env" >> .gitignore
echo "dist/" >> .gitignore

# Initial commit
git add .
git commit -m "Initial commit: project setup"

# Create main branch
git branch -M main

# Add remote repository
git remote add origin https://github.com/username/repository.git

# Push to remote
git push -u origin main
```

### Exercise 2: Feature Branch Workflow
Implement a complete feature branch workflow:

**Solution:**
```bash
# Create feature branch
git checkout -b feature/add-login

# Make changes
echo "// Login component" > src/components/Login.js
git add src/components/Login.js
git commit -m "Add login component"

# Push feature branch
git push origin feature/add-login

# Create pull request on GitHub
# After review and approval, merge

# Switch back to main
git checkout main
git pull origin main

# Delete feature branch
git branch -d feature/add-login
git push origin --delete feature/add-login
```

## 🎯 Key Takeaways

1. **Git** tracks changes and enables collaboration
2. **Branches** isolate feature development
3. **Commits** create checkpoints in history
4. **GitHub** provides remote collaboration
5. **Pull requests** enable code review

---

**Next Lesson**: [Lesson 4: CI/CD Basics](./lesson4-cicd.md)
