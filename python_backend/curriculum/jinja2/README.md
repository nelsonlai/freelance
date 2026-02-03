# Module 0.5: Jinja2 - The Python Template Engine

Jinja2 is a fast, expressive, and extensible templating engine for Python. It is the default engine for Flask and can be used with many other frameworks (including FastAPI and Django).

## 1. What is a Template Engine?
A template engine allows you to write HTML with special placeholders and logic that get replaced with actual data by your Python code before being sent to the browser. This is called **Server-Side Rendering (SSR)**.

## 2. Basic Syntax

Jinja2 uses three main types of delimiters:
- `{{ ... }}`: **Expressions** to print to the template output (e.g., variables).
- `{% ... %}`: **Statements** for logic (e.g., loops, conditionals).
- `{# ... #}`: **Comments** not included in the template output.

### A. Variables
You can pass variables from Python to your template.
```html
<p>Hello, {{ user.name }}!</p>
```

### B. Conditionals
```html
{% if user.is_logged_in %}
  <a href="/logout">Logout</a>
{% else %}
  <a href="/login">Login</a>
{% endif %}
```

### C. For Loops
```html
<ul>
{% for item in items %}
  <li>{{ item.name }} - ${{ item.price }}</li>
{% else %}
  <li>No items found.</li>
{% endfor %}
</ul>
```

## 3. Filters
Filters allow you to modify variables before they are displayed. They are applied using the pipe symbol (`|`).

- `{{ name|upper }}`: Converts to uppercase.
- `{{ bio|truncate(100) }}`: Shortens text to 100 characters.
- `{{ items|length }}`: Returns the number of items in a list.
- `{{ price|default(0.00) }}`: Provides a fallback value.

## 4. Template Inheritance (The Most Important Feature)
Instead of copying the same header and footer on every page, you create a base layout and "extend" it.

### base.html
```html
<!DOCTYPE html>
<html>
<head>
    <title>{% block title %}My Site{% endblock %}</title>
</head>
<body>
    <nav>...</nav>
    <main>
        {% block content %}{% endblock %}
    </main>
    <footer>...</footer>
</body>
</html>
```

### index.html
```html
{% extends "base.html" %}

{% block title %}Home Page{% endblock %}

{% block content %}
    <h1>Welcome to my site!</h1>
{% endblock %}
```

## 5. Escaping and Security
By default, Jinja2 automatically escapes HTML tags in variables to prevent **Cross-Site Scripting (XSS)** attacks.
- If you *want* to render raw HTML, use the `safe` filter: `{{ my_html_code|safe }}`.
