# Florence Hotel Website (Flask)

This project is a Flask implementation of the Florence hotel frontend based on `florence_hote.html`.

## Project Structure

- `app.py` - Flask application entrypoint
- `templates/index.html` - Main hotel website page (Flask template)
- `requirements.txt` - Python dependencies
- `florence_hote.html` - Original reference frontend file

## Prerequisites

- Python 3.9+ (recommended)
- `pip`

## Setup and Run

1. Open terminal in the project folder:

   ```bash
   cd /Users/nelsonlai/sources/freelance/Florence_Hotel
   ```

2. (Optional but recommended) Create and activate a virtual environment:

   ```bash
   python3 -m venv .venv
   source .venv/bin/activate
   ```

3. Install dependencies:

   ```bash
   pip install -r requirements.txt
   ```

4. Start the Flask app:

   ```bash
   python3 app.py
   ```

5. Open your browser:

   - `http://127.0.0.1:5000`

## Development Notes

- The page is served from Flask route `/`.
- The footer year is dynamically rendered using Flask/Jinja.
- Styling and fonts are loaded from Tailwind CDN and Google Fonts.
- Multilingual support is available via query parameter `lang`.

## Language Support

The site currently supports:

- English (`en`)
- Italian (`it`)
- French (`fr`)
- Spanish (`es`)
- Traditional Chinese (`zh-tw`)

You can change language in two ways:

1. Use the language selector in the top navigation bar.
2. Open the URL with a language query string, for example:

   - `http://127.0.0.1:5000/?lang=en`
   - `http://127.0.0.1:5000/?lang=it`
   - `http://127.0.0.1:5000/?lang=fr`
   - `http://127.0.0.1:5000/?lang=es`
   - `http://127.0.0.1:5000/?lang=zh-tw`

