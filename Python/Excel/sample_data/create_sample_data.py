"""
Create Sample Excel Files for the Course

This script generates all the sample Excel files used throughout the course
with realistic, randomly generated data.
"""

import pandas as pd
import numpy as np
from datetime import datetime, timedelta
import random
from pathlib import Path

# Set random seed for reproducibility
np.random.seed(42)
random.seed(42)

# Get the current directory
SAMPLE_DATA_DIR = Path(__file__).parent


def create_sales_data():
    """Create comprehensive sales data Excel file with multiple sheets."""
    print("Creating sales_data.xlsx...")
    
    # Generate dates for the year
    dates = pd.date_range('2024-01-01', '2024-12-31', freq='D')
    
    # Monthly sales data
    regions = ['North', 'South', 'East', 'West']
    products = ['Product A', 'Product B', 'Product C', 'Product D', 'Product E']
    
    # Sheet 1: Daily Sales
    daily_data = []
    for date in dates:
        for region in regions:
            daily_data.append({
                'Date': date,
                'Region': region,
                'Product': random.choice(products),
                'Units_Sold': np.random.randint(10, 100),
                'Unit_Price': round(np.random.uniform(10, 500), 2),
                'Discount': round(np.random.uniform(0, 0.2), 2)
            })
    
    df_daily = pd.DataFrame(daily_data)
    df_daily['Total_Sales'] = df_daily['Units_Sold'] * df_daily['Unit_Price'] * (1 - df_daily['Discount'])
    
    # Sheet 2: Monthly Summary
    df_monthly = df_daily.groupby([pd.Grouper(key='Date', freq='M'), 'Region']).agg({
        'Units_Sold': 'sum',
        'Total_Sales': 'sum'
    }).reset_index()
    df_monthly['Month'] = df_monthly['Date'].dt.strftime('%B %Y')
    
    # Sheet 3: Product Performance
    df_product = df_daily.groupby('Product').agg({
        'Units_Sold': 'sum',
        'Total_Sales': 'sum'
    }).reset_index()
    df_product['Avg_Price'] = df_product['Total_Sales'] / df_product['Units_Sold']
    
    # Sheet 4: Regional Performance
    df_regional = df_daily.groupby('Region').agg({
        'Units_Sold': 'sum',
        'Total_Sales': 'sum'
    }).reset_index()
    
    # Write to Excel with multiple sheets
    with pd.ExcelWriter(SAMPLE_DATA_DIR / 'sales_data.xlsx', engine='openpyxl') as writer:
        df_daily.to_excel(writer, sheet_name='Daily_Sales', index=False)
        df_monthly.to_excel(writer, sheet_name='Monthly_Summary', index=False)
        df_product.to_excel(writer, sheet_name='Product_Performance', index=False)
        df_regional.to_excel(writer, sheet_name='Regional_Performance', index=False)
    
    print("✓ sales_data.xlsx created")


def create_quarterly_sales():
    """Create Q1 and Q2 sales reports."""
    print("Creating quarterly sales files...")
    
    regions = ['North', 'South', 'East', 'West']
    products = ['Product A', 'Product B', 'Product C', 'Product D']
    
    # Q1 2024
    q1_dates = pd.date_range('2024-01-01', '2024-03-31', freq='D')
    q1_data = []
    for date in q1_dates:
        for region in regions:
            q1_data.append({
                'Date': date,
                'Region': region,
                'Product': random.choice(products),
                'Revenue': round(np.random.uniform(1000, 10000), 2),
                'Expenses': round(np.random.uniform(500, 5000), 2)
            })
    
    df_q1 = pd.DataFrame(q1_data)
    df_q1['Profit'] = df_q1['Revenue'] - df_q1['Expenses']
    df_q1.to_excel(SAMPLE_DATA_DIR / 'sales_q1_2024.xlsx', index=False)
    
    # Q2 2024
    q2_dates = pd.date_range('2024-04-01', '2024-06-30', freq='D')
    q2_data = []
    for date in q2_dates:
        for region in regions:
            q2_data.append({
                'Date': date,
                'Region': region,
                'Product': random.choice(products),
                'Revenue': round(np.random.uniform(1000, 10000), 2),
                'Expenses': round(np.random.uniform(500, 5000), 2)
            })
    
    df_q2 = pd.DataFrame(q2_data)
    df_q2['Profit'] = df_q2['Revenue'] - df_q2['Expenses']
    df_q2.to_excel(SAMPLE_DATA_DIR / 'sales_q2_2024.xlsx', index=False)
    
    print("✓ sales_q1_2024.xlsx and sales_q2_2024.xlsx created")


def create_employee_data():
    """Create employee data files."""
    print("Creating employee files...")
    
    first_names = ['John', 'Jane', 'Michael', 'Emily', 'David', 'Sarah', 'Robert', 'Lisa', 
                   'James', 'Mary', 'William', 'Patricia', 'Richard', 'Jennifer', 'Thomas']
    last_names = ['Smith', 'Johnson', 'Williams', 'Brown', 'Jones', 'Garcia', 'Miller', 
                  'Davis', 'Rodriguez', 'Martinez', 'Wilson', 'Anderson', 'Taylor']
    departments = ['Sales', 'Marketing', 'IT', 'HR', 'Finance', 'Operations']
    positions = ['Manager', 'Senior', 'Junior', 'Lead', 'Specialist', 'Coordinator']
    
    # Employee information
    n_employees = 200
    employees = []
    for i in range(1, n_employees + 1):
        hire_date = datetime(2020, 1, 1) + timedelta(days=np.random.randint(0, 1500))
        employees.append({
            'Employee_ID': f'EMP{i:04d}',
            'First_Name': random.choice(first_names),
            'Last_Name': random.choice(last_names),
            'Department': random.choice(departments),
            'Position': random.choice(positions),
            'Hire_Date': hire_date,
            'Email': f'employee{i}@company.com',
            'Phone': f'555-{np.random.randint(1000, 9999)}',
            'Location': random.choice(['New York', 'Los Angeles', 'Chicago', 'Houston', 'Phoenix'])
        })
    
    df_employees = pd.DataFrame(employees)
    df_employees.to_excel(SAMPLE_DATA_DIR / 'employees.xlsx', index=False)
    
    # Employee salaries
    salaries = []
    for emp in employees:
        base_salary = np.random.randint(40000, 150000)
        salaries.append({
            'Employee_ID': emp['Employee_ID'],
            'Base_Salary': base_salary,
            'Bonus': round(base_salary * np.random.uniform(0, 0.2), 2),
            'Commission': round(np.random.uniform(0, 10000), 2),
            'Benefits': round(base_salary * 0.15, 2)
        })
    
    df_salaries = pd.DataFrame(salaries)
    df_salaries['Total_Compensation'] = (df_salaries['Base_Salary'] + 
                                         df_salaries['Bonus'] + 
                                         df_salaries['Commission'] + 
                                         df_salaries['Benefits'])
    df_salaries.to_excel(SAMPLE_DATA_DIR / 'employee_salaries.xlsx', index=False)
    
    print("✓ employees.xlsx and employee_salaries.xlsx created")


def create_financial_data():
    """Create financial report and budget files."""
    print("Creating financial files...")
    
    # Financial Report
    categories = ['Revenue', 'Cost of Goods Sold', 'Operating Expenses', 
                 'Marketing', 'R&D', 'Administrative']
    quarters = ['Q1 2024', 'Q2 2024', 'Q3 2024', 'Q4 2024']
    
    financial_data = []
    for category in categories:
        row = {'Category': category}
        for quarter in quarters:
            if category == 'Revenue':
                row[quarter] = np.random.randint(500000, 1000000)
            else:
                row[quarter] = np.random.randint(50000, 300000)
        row['Total'] = sum([row[q] for q in quarters])
        financial_data.append(row)
    
    df_financial = pd.DataFrame(financial_data)
    df_financial.to_excel(SAMPLE_DATA_DIR / 'financial_report.xlsx', index=False)
    
    # Budget 2024
    departments = ['Sales', 'Marketing', 'IT', 'HR', 'Finance', 'Operations', 'R&D']
    budget_categories = ['Salaries', 'Equipment', 'Travel', 'Training', 'Software', 'Miscellaneous']
    
    budget_data = []
    for dept in departments:
        for category in budget_categories:
            budget_data.append({
                'Department': dept,
                'Category': category,
                'Q1_Budget': np.random.randint(10000, 100000),
                'Q2_Budget': np.random.randint(10000, 100000),
                'Q3_Budget': np.random.randint(10000, 100000),
                'Q4_Budget': np.random.randint(10000, 100000)
            })
    
    df_budget = pd.DataFrame(budget_data)
    df_budget['Annual_Budget'] = (df_budget['Q1_Budget'] + df_budget['Q2_Budget'] + 
                                   df_budget['Q3_Budget'] + df_budget['Q4_Budget'])
    df_budget.to_excel(SAMPLE_DATA_DIR / 'budget_2024.xlsx', index=False)
    
    print("✓ financial_report.xlsx and budget_2024.xlsx created")


def create_product_data():
    """Create product and inventory files."""
    print("Creating product files...")
    
    # Products
    product_categories = ['Electronics', 'Clothing', 'Home & Garden', 'Sports', 'Books']
    
    products = []
    for i in range(1, 101):
        products.append({
            'Product_ID': f'PROD{i:04d}',
            'Product_Name': f'Product {i}',
            'Category': random.choice(product_categories),
            'Unit_Price': round(np.random.uniform(10, 500), 2),
            'Cost': round(np.random.uniform(5, 250), 2),
            'Weight_kg': round(np.random.uniform(0.1, 10), 2),
            'Supplier': f'Supplier {np.random.randint(1, 11)}',
            'Active': random.choice([True, False])
        })
    
    df_products = pd.DataFrame(products)
    df_products['Margin'] = ((df_products['Unit_Price'] - df_products['Cost']) / 
                             df_products['Unit_Price'] * 100).round(2)
    df_products.to_excel(SAMPLE_DATA_DIR / 'products.xlsx', index=False)
    
    # Inventory
    warehouses = ['Warehouse A', 'Warehouse B', 'Warehouse C']
    
    inventory = []
    for product in products:
        for warehouse in warehouses:
            inventory.append({
                'Product_ID': product['Product_ID'],
                'Product_Name': product['Product_Name'],
                'Warehouse': warehouse,
                'Quantity_In_Stock': np.random.randint(0, 1000),
                'Reorder_Level': np.random.randint(50, 200),
                'Last_Restocked': datetime.now() - timedelta(days=np.random.randint(1, 90))
            })
    
    df_inventory = pd.DataFrame(inventory)
    df_inventory.to_excel(SAMPLE_DATA_DIR / 'inventory.xlsx', index=False)
    
    print("✓ products.xlsx and inventory.xlsx created")


def create_customer_data():
    """Create customer and order files."""
    print("Creating customer files...")
    
    # Customers
    n_customers = 500
    customers = []
    for i in range(1, n_customers + 1):
        customers.append({
            'Customer_ID': f'CUST{i:05d}',
            'Company_Name': f'Company {i}',
            'Contact_Name': f'Contact {i}',
            'Email': f'customer{i}@email.com',
            'Phone': f'555-{np.random.randint(1000, 9999)}',
            'Address': f'{np.random.randint(1, 9999)} Main St',
            'City': random.choice(['New York', 'Los Angeles', 'Chicago', 'Houston', 'Phoenix']),
            'State': random.choice(['NY', 'CA', 'IL', 'TX', 'AZ']),
            'Zip_Code': f'{np.random.randint(10000, 99999)}',
            'Country': 'USA',
            'Registration_Date': datetime(2020, 1, 1) + timedelta(days=np.random.randint(0, 1500))
        })
    
    df_customers = pd.DataFrame(customers)
    df_customers.to_excel(SAMPLE_DATA_DIR / 'customers.xlsx', index=False)
    
    # Customer Orders
    orders = []
    for i in range(1, 1001):
        order_date = datetime(2024, 1, 1) + timedelta(days=np.random.randint(0, 365))
        orders.append({
            'Order_ID': f'ORD{i:06d}',
            'Customer_ID': random.choice([c['Customer_ID'] for c in customers]),
            'Order_Date': order_date,
            'Ship_Date': order_date + timedelta(days=np.random.randint(1, 7)),
            'Product_ID': f'PROD{np.random.randint(1, 101):04d}',
            'Quantity': np.random.randint(1, 50),
            'Unit_Price': round(np.random.uniform(10, 500), 2),
            'Discount': round(np.random.uniform(0, 0.3), 2),
            'Shipping_Cost': round(np.random.uniform(5, 50), 2),
            'Status': random.choice(['Pending', 'Shipped', 'Delivered', 'Cancelled'])
        })
    
    df_orders = pd.DataFrame(orders)
    df_orders['Subtotal'] = df_orders['Quantity'] * df_orders['Unit_Price']
    df_orders['Discount_Amount'] = df_orders['Subtotal'] * df_orders['Discount']
    df_orders['Total'] = df_orders['Subtotal'] - df_orders['Discount_Amount'] + df_orders['Shipping_Cost']
    df_orders.to_excel(SAMPLE_DATA_DIR / 'customer_orders.xlsx', index=False)
    
    print("✓ customers.xlsx and customer_orders.xlsx created")


def main():
    """Create all sample data files."""
    print("=" * 60)
    print("Creating Sample Excel Files for Python Excel Operations Course")
    print("=" * 60)
    print()
    
    create_sales_data()
    create_quarterly_sales()
    create_employee_data()
    create_financial_data()
    create_product_data()
    create_customer_data()
    
    print()
    print("=" * 60)
    print("✓ All sample files created successfully!")
    print("=" * 60)
    print()
    print("Files created in:", SAMPLE_DATA_DIR)
    print()
    print("You can now use these files for practice throughout the course.")


if __name__ == "__main__":
    main()

