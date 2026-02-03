# NxN Table Programs

This repository contains programs to generate NxN multiplication tables in both C++ and Python.

## Files

- `nxn_table.cpp` - C++ implementation
- `nxn_table.py` - Python implementation
- `src/main/java/app/` - Java app framework (see below)

## Java App Framework

The Java version is structured as a small framework with clear separation of concerns:

```
src/main/java/app/
├── Main.java           # Entry point – wires components together
├── InputHandler.java   # Reads and validates user input
├── TableService.java   # Core logic – generates NxN table
└── TablePrinter.java   # Output – formats and prints the table
```

- **Main** – single entry point; composes input, service, and printer.
- **InputHandler** – prompts for N, validates positive integer.
- **TableService** – builds the multiplication table (no I/O).
- **TablePrinter** – formats and prints the table to the console.

To compile and run (from project root):

```bash
javac -d out src/main/java/app/*.java
java -cp out app.Main
```

## Usage

### C++ Version

Compile:
```bash
g++ -o nxn_table nxn_table.cpp
```

Run:
```bash
./nxn_table
```

### Python Version

Run:
```bash
python nxn_table.py
```

## Example Output

For N=5, the programs will generate a 5x5 multiplication table:

```
     1    2    3    4    5
     ---------------------
  1|    1    2    3    4    5
  2|    2    4    6    8   10
  3|    3    6    9   12   15
  4|    4    8   12   16   20
  5|    5   10   15   20   25
```

## Features

- Interactive input for table size
- Properly formatted output with aligned columns
- Input validation for positive integers
- Clean, readable code structure

