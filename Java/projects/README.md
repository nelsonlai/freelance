# Library Management System - Multi-file Project Example

This project demonstrates a complete Java application with proper package structure and separation of concerns.

## Project Structure

```
src/com/example/library/
├── model/
│   ├── Book.java          # Book entity/model
│   └── Member.java        # Member entity/model
├── service/
│   └── LibraryService.java # Business logic
├── util/
│   └── ValidationUtil.java # Utility functions
└── main/
    └── LibraryApp.java    # Main application entry point
```

## How to Compile and Run

### Using Command Line:

1. Navigate to the projects directory:
```bash
cd projects
```

2. Compile all Java files:
```bash
javac -d bin src/com/example/library/**/*.java
```

3. Run the application: -cp: classpath
```bash
java -cp bin com.example.library.main.LibraryApp
```

### Using IDE (IntelliJ IDEA, Eclipse, VS Code):

1. Import the project
2. Set `src` as source root
3. Run `LibraryApp.java`

## Key Concepts Demonstrated

1. **Packages**: Organized code into logical packages
2. **Model Classes**: Represent data entities (Book, Member)
3. **Service Layer**: Contains business logic (LibraryService)
4. **Utility Classes**: Reusable helper methods (ValidationUtil)
5. **Main Class**: Application entry point
6. **Encapsulation**: Private fields with public getters/setters
7. **Collections**: Using Map, List for data storage
8. **Streams**: Using Java 8+ streams for operations

## Features

- Add/Remove books and members
- Search books by title or author
- Borrow and return books
- Track member borrowing history
- Validation of ISBN and email
- Statistics and reporting

