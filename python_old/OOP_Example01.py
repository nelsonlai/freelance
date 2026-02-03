# Python version of a UML-inspired Library System
# Key OOP Concepts: Class, Inheritance, Encapsulation, State Handling

class Person:
    def __init__(self, name):
        self.name = name

    def display(self):
        print(f"Name: {self.name}")


class Member(Person):
    def __init__(self, name, member_id):
        super().__init__(name)
        self.member_id = member_id
        self.borrowed_books = []

    def borrow_book(self, book):
        if book.is_available():
            book.borrow()
            self.borrowed_books.append(book)
            print(f"{self.name} borrowed '{book.title}'")
        else:
            print(f"Sorry, '{book.title}' is not available.")


class Librarian(Person):
    def __init__(self, name):
        super().__init__(name)

    def manage_book(self, book):
        print(f"Librarian {self.name} is managing the book '{book.title}'")


class Book:
    def __init__(self, title, author):
        self.title = title
        self.author = author
        self.state = "New"  # States: New, Borrowed, Returned

    def is_available(self):
        return self.state == "New" or self.state == "Returned"

    def borrow(self):
        if self.is_available():
            self.state = "Borrowed"

    def return_book(self):
        self.state = "Returned"


# =================== TEST THE SYSTEM =====================

# Create some books
book1 = Book("1984", "George Orwell")
book2 = Book("The Catcher in the Rye", "J.D. Salinger")

# Create a librarian
librarian = Librarian("Alice")

# Create a member
member = Member("Bob", "M001")

# Borrowing process
member.borrow_book(book1)
member.borrow_book(book2)

# Return a book
book1.return_book()
print(f"'{book1.title}' state: {book1.state}")

# Try borrowing the returned book again
member.borrow_book(book1)

# Manage a book
librarian.manage_book(book1)