# Session 1: Introduction to Python Excel Libraries

Welcome to the first session of the Python Excel Operations course! This session introduces you to the fundamental libraries and concepts for working with Excel files in Python.

## 📋 Learning Objectives

By the end of this session, you will be able to:
- Understand different Excel file formats (.xlsx, .xls, .csv)
- Set up your Python environment with essential Excel libraries
- Read simple Excel files using pandas
- Understand basic DataFrame operations
- Navigate workbooks and worksheets programmatically
- Identify which library to use for different Excel tasks

## 📚 Topics Covered

1. **Excel File Formats**
   - .xlsx (Excel 2007+)
   - .xls (Legacy Excel)
   - .xlsm (Excel with macros)
   - .xlsb (Binary Excel)
   - .csv (Comma-separated values)

2. **Python Excel Libraries**
   - pandas - Data manipulation and basic Excel I/O
   - openpyxl - Read/write Excel 2010+ with formatting
   - xlsxwriter - Create Excel files with formatting and charts
   - xlrd/xlwt - Legacy Excel file support
   - pyxlsb - Binary Excel file support

3. **Setting Up Your Environment**
   - Installing required packages
   - Verifying installations
   - IDE setup and recommendations

4. **Reading Excel Files with Pandas**
   - Basic file reading
   - Understanding DataFrames
   - Exploring data structure
   - Simple data operations

## 📖 Materials

- `01_setup_and_basics.md` - Comprehensive theory and explanations
- `01_setup_and_basics.py` - Executable Python examples
- `01_setup_and_basics.ipynb` - Interactive Jupyter notebook
- `exercises/` - Practice exercises
- `sample_files/` - Sample Excel files for practice

## 🚀 Getting Started

### 1. Install Required Packages

Ensure you're in your virtual environment, then:

```bash
pip install pandas openpyxl xlsxwriter xlrd numpy
```

### 2. Verify Installation

```python
import pandas as pd
import openpyxl
import xlsxwriter
print("All libraries installed successfully!")
```

### 3. Study the Materials

1. Read `01_setup_and_basics.md` for theory
2. Run `01_setup_and_basics.py` to see examples in action
3. Open `01_setup_and_basics.ipynb` for interactive learning

### 4. Complete the Exercises

Work through the exercises in the `exercises/` folder to reinforce your learning.

## 💡 Key Concepts

### When to Use Each Library

- **pandas**: Best for data analysis, reading/writing simple Excel files
- **openpyxl**: Best for reading/writing Excel files with formatting, formulas, charts
- **xlsxwriter**: Best for creating new Excel files with advanced formatting and charts
- **xlrd/xlwt**: Only for legacy .xls files (Excel 97-2003)

### DataFrame Basics

A DataFrame is pandas' primary data structure - think of it as a table in memory:
- Rows and columns with labels
- Different data types per column
- Powerful methods for data manipulation
- Easy conversion to/from Excel

## ✅ Exercises

1. **Basic Reading** - Read a simple Excel file and display its contents
2. **Multiple Sheets** - Read an Excel file with multiple sheets
3. **Data Exploration** - Explore data using pandas methods
4. **Simple Operations** - Perform basic calculations on Excel data

## 🔗 Additional Resources

- [Pandas Documentation](https://pandas.pydata.org/docs/)
- [Openpyxl Documentation](https://openpyxl.readthedocs.io/)
- [Excel File Formats Explained](https://support.microsoft.com/en-us/office/file-formats-that-are-supported-in-excel-0943ff2c-6014-4e8d-aaea-b83d51d46247)

## 📝 Next Session

In Session 2, we'll dive deeper into reading Excel files, including:
- Reading specific rows, columns, and ranges
- Handling different data types
- Working with headers and indices
- Advanced reading techniques with openpyxl

---

**Ready to begin? Start with `01_setup_and_basics.md`!** 📊🐍

