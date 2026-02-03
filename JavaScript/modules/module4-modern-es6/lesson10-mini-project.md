# Lesson 10: Mini Project - GitHub Profile Finder

## 🎯 Learning Objectives

By the end of this lesson, you will be able to:

- Build a complete GitHub profile finder application
- Use GitHub API with modern JavaScript features
- Implement advanced async/await patterns
- Apply all ES6+ features learned in this module
- Create a responsive, modern user interface

## 📚 Project Overview

We'll build a GitHub profile finder that:
- Searches for GitHub users
- Displays user profiles with repositories
- Shows repository statistics
- Handles errors gracefully
- Uses modern ES6+ features throughout

## 🏗️ Project Structure

```
github-finder/
├── index.html
├── style.css
├── script.js
└── package.json
```

## 📝 HTML Structure

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>GitHub Profile Finder</title>
    <link rel="stylesheet" href="style.css">
</head>
<body>
    <div class="container">
        <header>
            <h1>GitHub Profile Finder</h1>
            <div class="search-container">
                <input type="text" id="usernameInput" placeholder="Enter GitHub username...">
                <button id="searchBtn">Search</button>
            </div>
        </header>
        
        <main>
            <div id="loading" class="loading hidden">
                <div class="spinner"></div>
                <p>Searching GitHub...</p>
            </div>
            
            <div id="error" class="error hidden">
                <p>User not found or error occurred.</p>
            </div>
            
            <div id="profile" class="profile hidden">
                <div class="profile-header">
                    <img id="avatar" src="" alt="Profile Avatar">
                    <div class="profile-info">
                        <h2 id="name"></h2>
                        <p id="username"></p>
                        <p id="bio"></p>
                        <div class="stats">
                            <span id="followers"></span>
                            <span id="following"></span>
                            <span id="repos"></span>
                        </div>
                    </div>
                </div>
                
                <div class="repositories">
                    <h3>Repositories</h3>
                    <div id="repoList" class="repo-list"></div>
                </div>
            </div>
        </main>
    </div>
    
    <script src="script.js"></script>
</body>
</html>
```

## 💻 JavaScript Implementation

```javascript
class GitHubFinder {
    constructor() {
        this.baseUrl = 'https://api.github.com';
        this.usernameInput = document.getElementById('usernameInput');
        this.searchBtn = document.getElementById('searchBtn');
        this.loading = document.getElementById('loading');
        this.error = document.getElementById('error');
        this.profile = document.getElementById('profile');
        
        this.init();
    }
    
    init() {
        this.searchBtn.addEventListener('click', () => this.searchUser());
        this.usernameInput.addEventListener('keypress', (e) => {
            if (e.key === 'Enter') {
                this.searchUser();
            }
        });
    }
    
    async searchUser() {
        const username = this.usernameInput.value.trim();
        
        if (!username) {
            this.showError('Please enter a username');
            return;
        }
        
        this.showLoading();
        
        try {
            const [user, repos] = await Promise.all([
                this.fetchUser(username),
                this.fetchRepositories(username)
            ]);
            
            this.displayProfile(user, repos);
            this.hideLoading();
            
        } catch (error) {
            console.error('Search error:', error);
            this.showError('User not found or API error occurred');
            this.hideLoading();
        }
    }
    
    async fetchUser(username) {
        const response = await fetch(`${this.baseUrl}/users/${username}`);
        
        if (!response.ok) {
            throw new Error(`HTTP error! status: ${response.status}`);
        }
        
        return await response.json();
    }
    
    async fetchRepositories(username) {
        const response = await fetch(`${this.baseUrl}/users/${username}/repos?sort=updated&per_page=10`);
        
        if (!response.ok) {
            throw new Error(`HTTP error! status: ${response.status}`);
        }
        
        return await response.json();
    }
    
    displayProfile(user, repos) {
        // Profile header
        document.getElementById('avatar').src = user.avatar_url;
        document.getElementById('name').textContent = user.name || user.login;
        document.getElementById('username').textContent = `@${user.login}`;
        document.getElementById('bio').textContent = user.bio || 'No bio available';
        
        // Stats
        document.getElementById('followers').textContent = `${user.followers} followers`;
        document.getElementById('following').textContent = `${user.following} following`;
        document.getElementById('repos').textContent = `${user.public_repos} repositories`;
        
        // Repositories
        this.displayRepositories(repos);
        
        this.profile.classList.remove('hidden');
    }
    
    displayRepositories(repos) {
        const repoList = document.getElementById('repoList');
        repoList.innerHTML = '';
        
        if (repos.length === 0) {
            repoList.innerHTML = '<p>No repositories found</p>';
            return;
        }
        
        repos.forEach(repo => {
            const repoElement = document.createElement('div');
            repoElement.className = 'repo-item';
            
            repoElement.innerHTML = `
                <h4><a href="${repo.html_url}" target="_blank">${repo.name}</a></h4>
                <p>${repo.description || 'No description'}</p>
                <div class="repo-stats">
                    <span>⭐ ${repo.stargazers_count}</span>
                    <span>🍴 ${repo.forks_count}</span>
                    <span>📅 ${new Date(repo.updated_at).toLocaleDateString()}</span>
                </div>
            `;
            
            repoList.appendChild(repoElement);
        });
    }
    
    showLoading() {
        this.hideAll();
        this.loading.classList.remove('hidden');
    }
    
    hideLoading() {
        this.loading.classList.add('hidden');
    }
    
    showError(message) {
        this.hideAll();
        this.error.querySelector('p').textContent = message;
        this.error.classList.remove('hidden');
    }
    
    hideAll() {
        this.loading.classList.add('hidden');
        this.error.classList.add('hidden');
        this.profile.classList.add('hidden');
    }
}

// Initialize the app
const githubFinder = new GitHubFinder();
```

## 🎯 Key Features Implemented

1. **Modern ES6+ Features** - Classes, async/await, arrow functions
2. **GitHub API Integration** - Fetch user data and repositories
3. **Error Handling** - Graceful error management
4. **Responsive Design** - Works on all devices
5. **Loading States** - Visual feedback during API calls
6. **Repository Display** - Shows top repositories with stats

## 🎯 Key Takeaways

1. **ES6+ features** make code cleaner and more maintainable
2. **Async/await** simplifies asynchronous operations
3. **Error handling** provides better user experience
4. **Modern JavaScript** enables powerful applications
5. **API integration** connects to real-world data

## 🚀 Next Steps

Congratulations! You've completed Module 4. You now understand:

- Arrow functions and their use cases
- Default parameters and optional chaining
- Advanced Promise and async/await patterns
- Iterators and generators
- Modern collections (Map, Set, WeakMap, WeakSet)
- Symbols and metadata
- Build tools and transpilation
- Error handling patterns
- Building complete modern applications

**Ready for Module 5: Browser APIs & UI Development!** 🎉

---

**Next Module**: [Module 5: Browser APIs & UI Development](../module5-browser-apis/README.md)
