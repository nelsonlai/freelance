# Module 3: Django - The Batteries-Included Framework

Django is a high-level Python web framework that encourages rapid development and clean, pragmatic design. It includes everything you need out of the box.

## Key Concepts to Learn

1.  **The MVT Pattern**: Model, View, Template (Django's version of MVC).
2.  **ORM (Object-Relational Mapper)**: Interacting with the database using Python classes instead of SQL.
3.  **Migrations**: Managing changes to your database schema.
4.  **Admin Interface**: A built-in, automatic admin site for managing data.
5.  **Authentication**: Built-in user login, logout, and permissions.

## Lesson Plan

1.  **Project vs App**: Understanding Django's modular structure.
2.  **Models**: Defining data structures in `models.py`.
3.  **The Admin**: Registering models to see them in the admin dashboard.
4.  **Views & URLs**: Connecting logic to endpoints.
5.  **Templates**: Using Django's powerful template engine.

## Running the Example

1. `cd curriculum/django`
2. `pip install -r requirements.txt`
3. `python manage.py migrate` (Create the database)
4. `python manage.py createsuperuser` (Follow prompts to create an admin account)
5. `python manage.py runserver`
6. Open `http://127.0.0.1:8000` for the site, and `http://127.0.0.1:8000/admin` for the dashboard.
