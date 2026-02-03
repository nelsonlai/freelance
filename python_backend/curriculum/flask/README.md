# Module 2: Flask & Jinja2 - Lightweight Web Apps

Flask is a "micro-framework" that provides the essentials for building web applications. Combined with Jinja2 templates, it's perfect for server-side rendered websites.

## Key Concepts to Learn

1.  **Routing**: Mapping URLs to Python functions.
2.  **Jinja2 Templating**: Using `{{ variable }}` and `{% if %}` / `{% for %}` in HTML.
3.  **Template Inheritance**: Creating a `base.html` to share layouts across pages.
4.  **Form Handling**: Receiving data from HTML forms.
5.  **Static Files**: Serving CSS, Images, and JavaScript.

## Lesson Plan

1.  **Basic Route**: Returning HTML from a function.
2.  **Rendering Templates**: Using `render_template()` to show HTML files.
3.  **Dynamic Content**: Passing Python lists/dicts to Jinja2.
4.  **Forms & POST**: Building a simple "Guestbook" application.
5.  **Flash Messages**: Notifying users of success or errors.

## Running the Example

1. `cd curriculum/flask`
2. `pip install -r requirements.txt`
3. `python app.py`
4. Open `http://127.0.0.1:5000` in your browser.
