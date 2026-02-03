# Advanced Jinja2 Features

Take your templating skills to the next level with these advanced concepts.

## 1. Macros
Macros are like functions for your templates. They allow you to reuse HTML snippets.

```html
{% macro input(name, value='', type='text') -%}
    <input type="{{ type }}" name="{{ name }}" value="{{ value|e }}">
{%- endmacro %}

{{ input('username') }}
{{ input('password', type='password') }}
```

## 2. Including Templates
The `include` statement is useful for small, reusable components like a sidebar or a newsletter signup form.

```html
{% include "sidebar.html" %}
```

## 3. Working with Data Structures
Jinja2 can handle complex Python objects, dictionaries, and lists easily.

```html
<p>User Email: {{ user['email'] }}</p>
<p>First Tag: {{ tags[0] }}</p>
```

## 4. The `loop` Object
Inside a `for` loop, you have access to a special `loop` object that provides metadata.

- `loop.index`: The current iteration (1-indexed).
- `loop.first`: True if this is the first item.
- `loop.last`: True if this is the last item.
- `loop.cycle('odd', 'even')`: Alternates between values (great for zebra-striping tables).

```html
{% for user in users %}
  <tr class="{{ loop.cycle('bg-light', 'bg-dark') }}">
    <td>{{ loop.index }}</td>
    <td>{{ user.name }}</td>
  </tr>
{% endfor %}
```

## 5. Custom Filters (Python Side)
You can even create your own filters in your Flask/Python code:

```python
@app.template_filter('reverse_string')
def reverse_filter(s):
    return s[::-1]
```
Then use it in Jinja2: `{{ "hello"|reverse_string }}` -> `olleh`.
