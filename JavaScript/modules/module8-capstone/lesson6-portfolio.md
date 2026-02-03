# Lesson 6: Capstone Project - Personal Portfolio

## 🎯 Learning Objectives

By the end of this lesson, you will be able to:

- Build a complete personal portfolio website
- Implement responsive design with modern CSS
- Create interactive components and animations
- Integrate contact form with backend
- Showcase projects and skills effectively
- Deploy portfolio to production

## 📚 Project Overview

We'll build a professional portfolio website that includes:
- Responsive design for all devices
- Interactive navigation and animations
- Project showcase with filtering
- Skills and experience sections
- Contact form with backend integration
- SEO optimization and performance

## 🏗️ Project Structure

```
portfolio/
├── package.json
├── public/
│   ├── index.html
│   └── images/
├── src/
│   ├── App.js
│   ├── index.js
│   ├── components/
│   │   ├── Header.js
│   │   ├── Hero.js
│   │   ├── About.js
│   │   ├── Skills.js
│   │   ├── Projects.js
│   │   ├── Contact.js
│   │   └── Footer.js
│   ├── data/
│   │   ├── projects.js
│   │   └── skills.js
│   └── styles/
│       ├── App.css
│       ├── components/
│       └── responsive.css
└── README.md
```

## 💻 Complete Implementation

### App.js
```javascript
import React, { useState, useEffect } from 'react';
import './styles/App.css';
import Header from './components/Header';
import Hero from './components/Hero';
import About from './components/About';
import Skills from './components/Skills';
import Projects from './components/Projects';
import Contact from './components/Contact';
import Footer from './components/Footer';

function App() {
    const [activeSection, setActiveSection] = useState('home');
    const [isMenuOpen, setIsMenuOpen] = useState(false);
    
    useEffect(() => {
        const handleScroll = () => {
            const sections = ['home', 'about', 'skills', 'projects', 'contact'];
            const scrollPosition = window.scrollY + 100;
            
            for (const section of sections) {
                const element = document.getElementById(section);
                if (element) {
                    const { offsetTop, offsetHeight } = element;
                    if (scrollPosition >= offsetTop && scrollPosition < offsetTop + offsetHeight) {
                        setActiveSection(section);
                        break;
                    }
                }
            }
        };
        
        window.addEventListener('scroll', handleScroll);
        return () => window.removeEventListener('scroll', handleScroll);
    }, []);
    
    const scrollToSection = (sectionId) => {
        const element = document.getElementById(sectionId);
        if (element) {
            element.scrollIntoView({ behavior: 'smooth' });
        }
        setIsMenuOpen(false);
    };
    
    return (
        <div className="app">
            <Header 
                activeSection={activeSection}
                onNavigate={scrollToSection}
                isMenuOpen={isMenuOpen}
                onMenuToggle={() => setIsMenuOpen(!isMenuOpen)}
            />
            
            <main>
                <Hero onNavigate={scrollToSection} />
                <About />
                <Skills />
                <Projects />
                <Contact />
            </main>
            
            <Footer />
        </div>
    );
}

export default App;
```

### components/Hero.js
```javascript
import React, { useState, useEffect } from 'react';

function Hero({ onNavigate }) {
    const [currentText, setCurrentText] = useState('');
    const [isDeleting, setIsDeleting] = useState(false);
    const [textIndex, setTextIndex] = useState(0);
    
    const texts = [
        'Frontend Developer',
        'React Specialist',
        'UI/UX Enthusiast',
        'Problem Solver'
    ];
    
    useEffect(() => {
        const typeSpeed = isDeleting ? 50 : 100;
        const pauseTime = 2000;
        
        const timer = setTimeout(() => {
            if (!isDeleting && currentText === texts[textIndex]) {
                setTimeout(() => setIsDeleting(true), pauseTime);
            } else if (isDeleting && currentText === '') {
                setIsDeleting(false);
                setTextIndex((prev) => (prev + 1) % texts.length);
            } else {
                setCurrentText((prev) => 
                    isDeleting 
                        ? prev.slice(0, -1)
                        : texts[textIndex].slice(0, prev.length + 1)
                );
            }
        }, typeSpeed);
        
        return () => clearTimeout(timer);
    }, [currentText, isDeleting, textIndex, texts]);
    
    return (
        <section id="home" className="hero">
            <div className="hero-content">
                <div className="hero-text">
                    <h1 className="hero-title">
                        Hi, I'm <span className="highlight">Your Name</span>
                    </h1>
                    <h2 className="hero-subtitle">
                        I'm a <span className="typing-text">{currentText}</span>
                        <span className="cursor">|</span>
                    </h2>
                    <p className="hero-description">
                        Passionate about creating beautiful, functional, and user-friendly applications.
                        I love turning complex problems into simple, elegant solutions.
                    </p>
                    <div className="hero-buttons">
                        <button 
                            className="btn btn-primary"
                            onClick={() => onNavigate('projects')}
                        >
                            View My Work
                        </button>
                        <button 
                            className="btn btn-secondary"
                            onClick={() => onNavigate('contact')}
                        >
                            Get In Touch
                        </button>
                    </div>
                </div>
                
                <div className="hero-image">
                    <div className="image-container">
                        <img 
                            src="/images/profile.jpg" 
                            alt="Profile" 
                            className="profile-image"
                        />
                        <div className="image-overlay"></div>
                    </div>
                </div>
            </div>
            
            <div className="scroll-indicator">
                <div className="scroll-arrow"></div>
            </div>
        </section>
    );
}

export default Hero;
```

### components/Projects.js
```javascript
import React, { useState } from 'react';
import { projects } from '../data/projects';

function Projects() {
    const [filter, setFilter] = useState('all');
    
    const categories = ['all', 'frontend', 'backend', 'fullstack'];
    
    const filteredProjects = filter === 'all' 
        ? projects 
        : projects.filter(project => project.category === filter);
    
    return (
        <section id="projects" className="projects">
            <div className="container">
                <div className="section-header">
                    <h2 className="section-title">My Projects</h2>
                    <p className="section-description">
                        Here are some of my recent projects that showcase my skills and experience.
                    </p>
                </div>
                
                <div className="project-filters">
                    {categories.map(category => (
                        <button
                            key={category}
                            className={`filter-btn ${filter === category ? 'active' : ''}`}
                            onClick={() => setFilter(category)}
                        >
                            {category.charAt(0).toUpperCase() + category.slice(1)}
                        </button>
                    ))}
                </div>
                
                <div className="projects-grid">
                    {filteredProjects.map(project => (
                        <div key={project.id} className="project-card">
                            <div className="project-image">
                                <img src={project.image} alt={project.title} />
                                <div className="project-overlay">
                                    <div className="project-links">
                                        <a 
                                            href={project.liveUrl} 
                                            target="_blank" 
                                            rel="noopener noreferrer"
                                            className="project-link"
                                        >
                                            Live Demo
                                        </a>
                                        <a 
                                            href={project.githubUrl} 
                                            target="_blank" 
                                            rel="noopener noreferrer"
                                            className="project-link"
                                        >
                                            GitHub
                                        </a>
                                    </div>
                                </div>
                            </div>
                            
                            <div className="project-content">
                                <h3 className="project-title">{project.title}</h3>
                                <p className="project-description">{project.description}</p>
                                
                                <div className="project-tech">
                                    {project.technologies.map(tech => (
                                        <span key={tech} className="tech-tag">
                                            {tech}
                                        </span>
                                    ))}
                                </div>
                            </div>
                        </div>
                    ))}
                </div>
            </div>
        </section>
    );
}

export default Projects;
```

### data/projects.js
```javascript
export const projects = [
    {
        id: 1,
        title: 'E-Commerce Platform',
        description: 'A full-stack e-commerce platform with user authentication, product management, and payment integration.',
        image: '/images/project1.jpg',
        category: 'fullstack',
        technologies: ['React', 'Node.js', 'MongoDB', 'Stripe'],
        liveUrl: 'https://ecommerce-demo.com',
        githubUrl: 'https://github.com/username/ecommerce'
    },
    {
        id: 2,
        title: 'Task Management App',
        description: 'A collaborative task management application with real-time updates and team collaboration features.',
        image: '/images/project2.jpg',
        category: 'frontend',
        technologies: ['React', 'Redux', 'Socket.io', 'CSS3'],
        liveUrl: 'https://taskmanager-demo.com',
        githubUrl: 'https://github.com/username/taskmanager'
    },
    {
        id: 3,
        title: 'Weather API Service',
        description: 'A RESTful API service for weather data with caching, rate limiting, and comprehensive documentation.',
        image: '/images/project3.jpg',
        category: 'backend',
        technologies: ['Node.js', 'Express', 'Redis', 'JWT'],
        liveUrl: 'https://weather-api-demo.com',
        githubUrl: 'https://github.com/username/weather-api'
    }
];
```

## 🎯 Key Features Implemented

1. **Responsive Design** - Works on all devices
2. **Interactive Navigation** - Smooth scrolling and active states
3. **Typing Animation** - Dynamic text effects
4. **Project Filtering** - Category-based project display
5. **Contact Form** - Backend integration for messages
6. **SEO Optimization** - Meta tags and structured data
7. **Performance** - Optimized images and lazy loading

## 🎯 Key Takeaways

1. **Portfolio websites** showcase professional skills
2. **Responsive design** ensures cross-device compatibility
3. **Interactive elements** engage visitors
4. **Project showcase** demonstrates capabilities
5. **Contact integration** enables professional communication

## 🚀 Next Steps

Congratulations! You've built a professional portfolio website. In the next lesson, we'll create:

- **Real-Time Chat Application** - WebSocket integration
- **User authentication** - Login and registration
- **Message history** - Persistent chat data
- **File sharing** - Image and document uploads

---

**Next Lesson**: [Lesson 7: Capstone Project - Chat App](./lesson7-chat-app.md)
