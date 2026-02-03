# Session 1 Exercises

Complete these exercises to reinforce your understanding of Python Excel basics.

## Exercise 1: Library Setup and Verification

**Objective**: Verify that all required libraries are properly installed.

**Tasks**:
1. Import pandas, openpyxl, xlsxwriter, and numpy
2. Print the version of each library
3. Handle any ImportError exceptions gracefully
4. Create a simple verification script

**Expected Output**:
```
✓ pandas version: 2.0.0
✓ openpyxl version: 3.1.0
✓ xlsxwriter version: 3.1.0
✓ numpy version: 1.24.0
All libraries installed successfully!
```

## Exercise 2: Create Your First DataFrame

**Objective**: Create a DataFrame with custom data and explore its properties.

**Tasks**:
1. Create a DataFrame with at least 5 rows and 4 columns
2. The data should represent a real-world scenario (e.g., students, products, employees)
3. Display the DataFrame
4. Print the shape, columns, and data types
5. Display the first 3 rows and last 2 rows

**Data Suggestion**: Student records with Name, Subject, Score, Grade

## Exercise 3: Excel Write and Read

**Objective**: Practice writing and reading Excel files.

**Tasks**:
1. Create a DataFrame with product information (at least 10 products)
2. Write it to an Excel file named `my_products.xlsx`
3. Read the file back into a new DataFrame
4. Verify that the data matches the original
5. Print a success message if they match

## Exercise 4: Data Filtering and Analysis

**Objective**: Perform basic data analysis operations.

**Given Dataset**: Sales data with columns: Product, Category, Price, Quantity_Sold

**Tasks**:
1. Calculate total revenue for each product (Price × Quantity_Sold)
2. Find products with revenue > $5,000
3. Calculate average price by category
4. Find the top 3 best-selling products
5. Create a summary DataFrame with results

## Exercise 5: Multi-Sheet Workbook

**Objective**: Create and work with multiple sheets.

**Tasks**:
1. Create three DataFrames:
   - Monthly sales data (Month, Revenue, Expenses)
   - Employee data (Name, Department, Salary)
   - Product inventory (Product, Stock, Reorder_Level)
2. Write all three to a single Excel file with separate sheets
3. Read each sheet back individually
4. Display the first 3 rows of each sheet

## Exercise 6: Data Transformation

**Objective**: Transform and enhance data.

**Given**: Employee DataFrame with Name, Department, Base_Salary

**Tasks**:
1. Add a Bonus column (10% of Base_Salary)
2. Add a Total_Compensation column (Base_Salary + Bonus)
3. Add a Tax column (25% of Total_Compensation)
4. Add a Net_Pay column (Total_Compensation - Tax)
5. Sort by Net_Pay in descending order
6. Save to Excel with formatting

## Exercise 7: Openpyxl Cell Operations

**Objective**: Practice cell-level operations with openpyxl.

**Tasks**:
1. Create an Excel file with pandas (any data)
2. Load it with openpyxl
3. Read and print the value of cell A1
4. Read and print all values in row 1
5. Read and print all values in column A
6. Iterate through the first 5 rows and print each row

## Exercise 8: Error Handling

**Objective**: Implement proper error handling.

**Tasks**:
1. Try to read a non-existent file and handle the error
2. Try to read a non-existent sheet and handle the error
3. Try to access a cell outside the data range
4. Create a function that safely reads any Excel file
5. The function should return the DataFrame or None if there's an error

## Exercise 9: Data Aggregation

**Objective**: Practice groupby and aggregation operations.

**Given**: Sales transactions with Date, Region, Product, Sales_Amount

**Tasks**:
1. Calculate total sales by region
2. Calculate average sales by product
3. Find the region with the highest sales
4. Calculate total sales by month (extract month from Date)
5. Create a pivot table showing sales by Region and Product

## Exercise 10: Combined Challenge

**Objective**: Combine multiple concepts in one exercise.

**Tasks**:
1. Read a sample Excel file (create one if needed)
2. Perform data cleaning (handle missing values, duplicates)
3. Calculate summary statistics
4. Create a new DataFrame with insights
5. Write results to a new Excel file with formatting
6. Add multiple sheets for different analyses
7. Use openpyxl to format the header rows

**Bonus**: Add a chart to the Excel file

## Solutions

Solutions for all exercises can be found in `exercise_solutions.py`.

Try to complete the exercises on your own first before checking the solutions!

## Submission Guidelines

For classroom settings:
1. Complete all exercises in separate Python files or a single notebook
2. Name your files: `session01_ex{number}_{yourname}.py`
3. Include comments explaining your approach
4. Test your code to ensure it runs without errors
5. Submit the Python files and any generated Excel files

## Grading Rubric

- **Correctness**: Does the code produce the expected output? (50%)
- **Code Quality**: Is the code clean, readable, and well-commented? (20%)
- **Error Handling**: Are errors handled appropriately? (15%)
- **Best Practices**: Are pandas/openpyxl best practices followed? (15%)

Good luck! 🚀

