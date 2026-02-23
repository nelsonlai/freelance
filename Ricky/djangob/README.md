# Weight Management V2 - Django Web Application

A modern Django-based web application for weight management and body transformation visualization. Users can input their body metrics (weight, height, age) and upload photos to receive personalized weight loss plans with AI-generated transformation previews.

## Features

### Core Functionality
- **Health Assessment Survey**: Collect user data including weight, height, age, and photos
- **Personalized Weight Loss Plans**: 
  - Plan 1: Lose 10-15% of current weight
  - Plan 2: Lose 20% of current weight
- **AI Transformation Preview**: Generate AI-powered images showing potential transformation results
- **Blog/Post Management**: Simple blog functionality to share health and fitness content
- **Admin Dashboard**: Django admin interface for content management
- **Media Upload**: Support for photo uploads with organized storage

### User Interface
- Modern, responsive design with custom CSS
- Beautiful form UI with emoji icons
- Visual feedback for uploaded photos
- Transformation preview cards
- Privacy-focused messaging

## Tech Stack

### Backend
- **Django 5.2.10**: Web framework
- **Python 3.x**: Programming language
- **SQLite**: Database (default)
- **python-dotenv**: Environment variable management

### Frontend
- **TailwindCSS 4.1.18**: Utility-first CSS framework
- **DaisyUI 5.5.16**: TailwindCSS component library
- **PostCSS**: CSS processing
- **Custom CSS**: Additional styling

### Additional Dependencies
- **python-dotenv 1.2.1**: Environment variable management from .env files
- **Pillow 10.0+**: Python Imaging Library for handling image uploads
- **playwright 1.40+**: Browser automation for Poe API interactions
- **fastapi-poe 0.0.40+**: Poe API client for AI image generation
- **asgiref 3.11.0**: ASGI support
- **django-tailwind 4.4.2**: Django-Tailwind integration
- **pytailwindcss 0.3.0**: Python Tailwind wrapper
- **sqlparse 0.5.5**: SQL parser
- **tzdata 2025.3**: Timezone data

## Project Structure

```
djangob/
├── core/                          # Main application
│   ├── migrations/                # Database migrations
│   ├── static/                    # Static files (CSS)
│   │   └── core/css/
│   ├── templates/                 # HTML templates
│   │   └── core/
│   │       ├── base.html
│   │       ├── survey.html
│   │       ├── assessment_result.html
│   │       ├── post_list.html
│   │       └── post_detail.html
│   ├── models.py                  # Database models (Post, Assessment)
│   ├── views.py                   # View functions
│   ├── urls.py                    # URL routing
│   └── admin.py                   # Admin configuration
├── first_apps/                    # Django project settings
│   ├── settings.py                # Main settings
│   ├── urls.py                    # Root URL configuration
│   ├── wsgi.py                    # WSGI configuration
│   └── asgi.py                    # ASGI configuration
├── media/                         # User-uploaded files
│   ├── photos/                    # Original photos
│   └── generated/                 # AI-generated images
├── theme/                         # Tailwind theme app
│   ├── static/                    # Compiled CSS
│   └── templates/
├── node_modules/                  # Node.js dependencies
├── manage.py                      # Django management script
├── poe_login.py                   # Playwright script for Poe authentication
├── poe_generate.py                # Playwright script for AI image generation
├── test_poe.py                    # Test script for Poe API integration
├── requirements.txt               # Python dependencies
├── package.json                   # Node.js dependencies
├── db.sqlite3                     # SQLite database
└── .env                           # Environment variables (not tracked)
```

## Installation

### Prerequisites
- Python 3.8 or higher
- Node.js and npm (for TailwindCSS)
- Git

### Step 1: Clone the Repository
```bash
git clone <repository-url>
cd djangob
```

### Step 2: Set Up Python Environment
```bash
# Create a virtual environment
python -m venv venv

# Activate the virtual environment
# On macOS/Linux:
source venv/bin/activate
# On Windows:
venv\Scripts\activate

# Install Python dependencies
pip install -r requirements.txt
```

### Step 3: Set Up Frontend Dependencies
```bash
# Install Node.js dependencies
npm install
```

### Step 4: Install Playwright Browsers (if using AI features)
```bash
# Install Playwright browser binaries
playwright install
```

### Step 5: Configure Environment Variables
Create a `.env` file in the project root:
```bash
# Optional: Add your POE API key for AI features
POE_API_KEY=your_api_key_here
```

### Step 6: Initialize the Database
```bash
# Run migrations
python manage.py migrate

# Create a superuser for admin access
python manage.py createsuperuser
```

### Step 7: Collect Static Files (Optional for Production)
```bash
python manage.py collectstatic
```

## Running the Application

### Development Server
```bash
# Start the Django development server
python manage.py runserver
```

The application will be available at `http://127.0.0.1:8000/`

### Available URLs
- **Home/Survey**: `http://127.0.0.1:8000/` - Main weight management survey
- **Admin Panel**: `http://127.0.0.1:8000/admin/` - Django admin interface
- **Blog**: `http://127.0.0.1:8000/blog/` - Blog post listing

## Usage

### For End Users

1. **Submit Assessment**:
   - Navigate to the homepage
   - Fill in your weight (kg), height (cm), and age (years)
   - Upload a recent photo
   - Click "Calculate My Transformation Plan"

2. **View Results**:
   - See your personalized weight loss plans
   - View your uploaded photo
   - Click "Generate AI Transformation" to see potential results

3. **Read Blog Posts**:
   - Visit `/blog/` to read health and fitness articles

### For Administrators

1. **Access Admin Panel**:
   - Navigate to `http://127.0.0.1:8000/admin/`
   - Log in with your superuser credentials

2. **Manage Content**:
   - Create and edit blog posts
   - View user assessments
   - Manage uploaded photos

## Database Models

### Post
- `title`: CharField (max 100 characters)
- `content`: TextField
- `created_at`: DateTimeField (auto)

### Assessment
- `weight`: FloatField
- `height`: FloatField
- `age`: IntegerField
- `photo`: ImageField (uploaded to `media/photos/`)
- `after_plan1`: ImageField (AI-generated, optional)
- `after_plan2`: ImageField (AI-generated, optional)
- `created_at`: DateTimeField (auto)

## Development Notes

### Security Considerations
- `DEBUG = True` is currently enabled - **MUST be set to `False` in production**
- Secret key is exposed in `settings.py` - **MUST be moved to environment variables**
- Update `ALLOWED_HOSTS` for production deployment
- Consider using PostgreSQL for production instead of SQLite

### AI Image Generation
The project includes Poe API integration for AI-powered image transformation:

**Available Scripts:**
- `poe_login.py`: First-time authentication script to save login session
- `poe_generate.py`: Automated script to generate images via Poe's Nano-Banana-Pro bot
- `test_poe.py`: Test script for Poe API functionality

**Setup:**
1. Run `poe_login.py` once to authenticate and save session
2. Add your `POE_API_KEY` to the `.env` file
3. The `generate_ai_images` function in `core/views.py` currently uses placeholder logic
4. Integrate the Poe scripts to enable actual AI transformation

### TailwindCSS
The project uses TailwindCSS with DaisyUI for styling. To rebuild CSS:
```bash
npx tailwindcss -i ./theme/static_src/src/styles.css -o ./theme/static/css/dist/styles.css --watch
```

## Troubleshooting

### Common Issues

**Issue**: `ModuleNotFoundError: No module named 'dotenv'`
```bash
pip install python-dotenv
```

**Issue**: `ModuleNotFoundError: No module named 'playwright'`
```bash
pip install playwright
playwright install
```

**Issue**: `PIL/Pillow not found` or Image upload errors
```bash
pip install Pillow
```

**Issue**: Media files not displaying
- Ensure `DEBUG = True` for development
- Check that `MEDIA_URL` and `MEDIA_ROOT` are configured correctly
- Verify uploaded files exist in the `media/` directory

**Issue**: Database errors
```bash
# Reset migrations (warning: deletes all data)
python manage.py migrate --run-syncdb
```

## Future Enhancements

- [ ] Integrate real AI image generation API
- [ ] Add user authentication and profiles
- [ ] Implement progress tracking over time
- [ ] Add nutrition and exercise recommendations
- [ ] Export reports as PDF
- [ ] Multi-language support
- [ ] Mobile app version

## Contributing

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

## License

This project is private and proprietary.

## Support

For issues, questions, or contributions, please contact the project maintainer.

---

**Note**: This is a development version. Do not deploy to production without implementing proper security measures, environment variable management, and production-ready database configuration.
