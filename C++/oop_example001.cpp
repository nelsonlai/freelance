/*
 * OBJECT-ORIENTED PROGRAMMING EXAMPLES EXAMPLES
 * 
 * This file demonstrates OOP concepts including classes, inheritance, and polymorphism:
 * - Core concepts and syntax
 * - Practical examples and usage patterns
 * - Best practices and optimization techniques
 * - Real-world applications and scenarios
 * 
 * Learning Objectives:
 * - Understand fundamental OBJECT-ORIENTED PROGRAMMING concepts
 * - Learn proper syntax and implementation
 * - Master different techniques and approaches
 * - Apply knowledge in practical scenarios
 * - Develop problem-solving skills
 * 
 * Prerequisites:
 * - Basic C++ knowledge
 * - Understanding of data types and variables
 * - Familiarity with control structures
 * - Basic understanding of functions and classes
 * 
 * Key Topics Covered:
 * - Syntax and language features
 * - Implementation techniques
 * - Performance considerations
 * - Error handling and best practices
 * - Real-world applications
 */

/*
    C++ version of a UML-inspired Library System
    Demonstrates class inheritance, method overriding, encapsulation, and state handling
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Book {
private:
    string title;
    string author;
    string state; // States: New, Borrowed, Returned

public:
    Book(string t, string a) : title(t), author(a), state("New") {}

    string getTitle() { return title; }

    bool isAvailable() {
        return state == "New" || state == "Returned";
    }

    void borrow() {
        if (isAvailable()) {
            state = "Borrowed";
        }
    }

    void returnBook() {
        state = "Returned";
    }

    string getState() { return state; }
};

class Person {
protected:
    string name;

public:
    Person(string n) : name(n) {}

    virtual void display() {
        cout << "Name: " << name << endl;
    }
};

class Member : public Person {
private:
    string memberId;
    vector<Book*> borrowedBooks;

public:
    Member(string n, string id) : Person(n), memberId(id) {}

    void borrowBook(Book* book) {
        if (book->isAvailable()) {
            book->borrow();
            borrowedBooks.push_back(book);
            cout << name << " borrowed '" << book->getTitle() << "'" << endl;
        } else {
            cout << "Sorry, '" << book->getTitle() << "' is not available." << endl;
        }
    }
};

class Librarian : public Person {
public:
    Librarian(string n) : Person(n) {}

    void manageBook(Book* book) {
        cout << "Librarian " << name << " is managing the book '" << book->getTitle() << "'" << endl;
    }
};

// =================== TEST THE SYSTEM =====================

int main() {
    Book book1("1984", "George Orwell");
    Book book2("The Catcher in the Rye", "J.D. Salinger");

    Librarian librarian("Alice");
    Member member("Bob", "M001");

    member.borrowBook(&book1);
    member.borrowBook(&book2);

    book1.returnBook();
    cout << "'" << book1.getTitle() << "' state: " << book1.getState() << endl;

    member.borrowBook(&book1);

    librarian.manageBook(&book1);

    return 0;
}
