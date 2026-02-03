"""
PySide6 Advanced Example 04: Database Connectivity
==================================================

This example demonstrates:
- SQLite database with Qt SQL module
- QSqlTableModel for automatic database binding
- CRUD operations (Create, Read, Update, Delete)
- Search and filtering
- Transaction handling

Run: python 04_database.py
"""

import sys
import os
from PySide6.QtWidgets import (
    QApplication, QMainWindow, QWidget, QVBoxLayout, QHBoxLayout,
    QTableView, QHeaderView, QPushButton, QLineEdit, QLabel,
    QMessageBox, QDialog, QFormLayout, QDialogButtonBox,
    QSpinBox, QDoubleSpinBox, QComboBox, QGroupBox
)
from PySide6.QtCore import Qt, QSortFilterProxyModel
from PySide6.QtSql import (
    QSqlDatabase, QSqlQuery, QSqlTableModel, QSqlError
)


class ProductDialog(QDialog):
    """Dialog for adding/editing products."""
    
    def __init__(self, parent=None, product_data=None):
        super().__init__(parent)
        self.product_data = product_data
        self.setWindowTitle("Edit Product" if product_data else "Add Product")
        self.setMinimumWidth(350)
        
        layout = QVBoxLayout(self)
        
        form = QFormLayout()
        
        self.name_input = QLineEdit()
        form.addRow("Name:", self.name_input)
        
        self.category_input = QComboBox()
        self.category_input.setEditable(True)
        self.category_input.addItems([
            "Electronics", "Clothing", "Food", "Books", 
            "Home & Garden", "Sports", "Other"
        ])
        form.addRow("Category:", self.category_input)
        
        self.price_input = QDoubleSpinBox()
        self.price_input.setRange(0, 1000000)
        self.price_input.setDecimals(2)
        self.price_input.setPrefix("$")
        form.addRow("Price:", self.price_input)
        
        self.quantity_input = QSpinBox()
        self.quantity_input.setRange(0, 1000000)
        form.addRow("Quantity:", self.quantity_input)
        
        layout.addLayout(form)
        
        # Buttons
        buttons = QDialogButtonBox(
            QDialogButtonBox.StandardButton.Ok |
            QDialogButtonBox.StandardButton.Cancel
        )
        buttons.accepted.connect(self.validate_and_accept)
        buttons.rejected.connect(self.reject)
        layout.addWidget(buttons)
        
        # Pre-fill if editing
        if product_data:
            self.name_input.setText(product_data.get("name", ""))
            self.category_input.setCurrentText(product_data.get("category", ""))
            self.price_input.setValue(product_data.get("price", 0))
            self.quantity_input.setValue(product_data.get("quantity", 0))
    
    def validate_and_accept(self):
        if not self.name_input.text().strip():
            QMessageBox.warning(self, "Validation Error", "Name is required!")
            return
        self.accept()
    
    def get_data(self):
        return {
            "name": self.name_input.text().strip(),
            "category": self.category_input.currentText(),
            "price": self.price_input.value(),
            "quantity": self.quantity_input.value()
        }


class DatabaseManager:
    """Manages database connection and operations."""
    
    def __init__(self, db_name="products.db"):
        self.db_name = db_name
        self.db = None
    
    def connect(self):
        """Connect to the database."""
        self.db = QSqlDatabase.addDatabase("QSQLITE")
        self.db.setDatabaseName(self.db_name)
        
        if not self.db.open():
            error = self.db.lastError().text()
            raise Exception(f"Cannot open database: {error}")
        
        self.create_tables()
        return True
    
    def create_tables(self):
        """Create the required tables."""
        query = QSqlQuery()
        
        # Products table
        query.exec("""
            CREATE TABLE IF NOT EXISTS products (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                name TEXT NOT NULL,
                category TEXT,
                price REAL DEFAULT 0,
                quantity INTEGER DEFAULT 0,
                created_at DATETIME DEFAULT CURRENT_TIMESTAMP
            )
        """)
        
        # Check if table is empty and add sample data
        query.exec("SELECT COUNT(*) FROM products")
        if query.next() and query.value(0) == 0:
            self.insert_sample_data()
    
    def insert_sample_data(self):
        """Insert sample products."""
        sample_products = [
            ("Laptop", "Electronics", 999.99, 50),
            ("Smartphone", "Electronics", 699.99, 100),
            ("Headphones", "Electronics", 149.99, 200),
            ("T-Shirt", "Clothing", 29.99, 500),
            ("Jeans", "Clothing", 59.99, 300),
            ("Novel", "Books", 14.99, 150),
            ("Cookbook", "Books", 24.99, 75),
            ("Soccer Ball", "Sports", 39.99, 80),
            ("Tennis Racket", "Sports", 89.99, 40),
            ("Coffee Maker", "Home & Garden", 79.99, 60),
        ]
        
        query = QSqlQuery()
        query.prepare("""
            INSERT INTO products (name, category, price, quantity)
            VALUES (?, ?, ?, ?)
        """)
        
        for name, category, price, quantity in sample_products:
            query.addBindValue(name)
            query.addBindValue(category)
            query.addBindValue(price)
            query.addBindValue(quantity)
            query.exec()
    
    def add_product(self, name, category, price, quantity):
        """Add a new product."""
        query = QSqlQuery()
        query.prepare("""
            INSERT INTO products (name, category, price, quantity)
            VALUES (?, ?, ?, ?)
        """)
        query.addBindValue(name)
        query.addBindValue(category)
        query.addBindValue(price)
        query.addBindValue(quantity)
        
        if not query.exec():
            raise Exception(query.lastError().text())
        
        return query.lastInsertId()
    
    def update_product(self, product_id, name, category, price, quantity):
        """Update an existing product."""
        query = QSqlQuery()
        query.prepare("""
            UPDATE products 
            SET name = ?, category = ?, price = ?, quantity = ?
            WHERE id = ?
        """)
        query.addBindValue(name)
        query.addBindValue(category)
        query.addBindValue(price)
        query.addBindValue(quantity)
        query.addBindValue(product_id)
        
        if not query.exec():
            raise Exception(query.lastError().text())
    
    def delete_product(self, product_id):
        """Delete a product."""
        query = QSqlQuery()
        query.prepare("DELETE FROM products WHERE id = ?")
        query.addBindValue(product_id)
        
        if not query.exec():
            raise Exception(query.lastError().text())
    
    def get_statistics(self):
        """Get database statistics."""
        stats = {}
        query = QSqlQuery()
        
        query.exec("SELECT COUNT(*) FROM products")
        if query.next():
            stats["total_products"] = query.value(0)
        
        query.exec("SELECT SUM(quantity) FROM products")
        if query.next():
            stats["total_items"] = query.value(0) or 0
        
        query.exec("SELECT SUM(price * quantity) FROM products")
        if query.next():
            stats["total_value"] = query.value(0) or 0
        
        query.exec("SELECT COUNT(DISTINCT category) FROM products")
        if query.next():
            stats["categories"] = query.value(0)
        
        return stats
    
    def close(self):
        """Close the database connection."""
        if self.db and self.db.isOpen():
            self.db.close()


class DatabaseDemo(QMainWindow):
    """Main window for database demo."""
    
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Database Demo - Product Manager")
        self.setMinimumSize(900, 600)
        
        # Initialize database
        self.db_manager = DatabaseManager()
        try:
            self.db_manager.connect()
        except Exception as e:
            QMessageBox.critical(self, "Database Error", str(e))
            sys.exit(1)
        
        # Create model
        self.model = QSqlTableModel()
        self.model.setTable("products")
        self.model.setEditStrategy(QSqlTableModel.EditStrategy.OnFieldChange)
        self.model.select()
        
        # Set headers
        self.model.setHeaderData(0, Qt.Orientation.Horizontal, "ID")
        self.model.setHeaderData(1, Qt.Orientation.Horizontal, "Name")
        self.model.setHeaderData(2, Qt.Orientation.Horizontal, "Category")
        self.model.setHeaderData(3, Qt.Orientation.Horizontal, "Price")
        self.model.setHeaderData(4, Qt.Orientation.Horizontal, "Quantity")
        self.model.setHeaderData(5, Qt.Orientation.Horizontal, "Created")
        
        # Create proxy for filtering
        self.proxy_model = QSortFilterProxyModel()
        self.proxy_model.setSourceModel(self.model)
        self.proxy_model.setFilterCaseSensitivity(Qt.CaseSensitivity.CaseInsensitive)
        
        self.setup_ui()
        self.update_statistics()
    
    def setup_ui(self):
        """Set up the user interface."""
        central = QWidget()
        self.setCentralWidget(central)
        layout = QVBoxLayout(central)
        
        # Search and filter section
        filter_group = QGroupBox("Search & Filter")
        filter_layout = QHBoxLayout(filter_group)
        
        filter_layout.addWidget(QLabel("Search:"))
        self.search_input = QLineEdit()
        self.search_input.setPlaceholderText("Search products...")
        self.search_input.textChanged.connect(self.apply_filter)
        filter_layout.addWidget(self.search_input)
        
        filter_layout.addWidget(QLabel("Category:"))
        self.category_filter = QComboBox()
        self.category_filter.addItem("All Categories")
        self.category_filter.addItems([
            "Electronics", "Clothing", "Food", "Books", 
            "Home & Garden", "Sports", "Other"
        ])
        self.category_filter.currentTextChanged.connect(self.apply_category_filter)
        filter_layout.addWidget(self.category_filter)
        
        refresh_btn = QPushButton("🔄 Refresh")
        refresh_btn.clicked.connect(self.refresh_data)
        filter_layout.addWidget(refresh_btn)
        
        layout.addWidget(filter_group)
        
        # Table view
        self.table_view = QTableView()
        self.table_view.setModel(self.proxy_model)
        self.table_view.setSortingEnabled(True)
        self.table_view.setAlternatingRowColors(True)
        self.table_view.setSelectionBehavior(QTableView.SelectionBehavior.SelectRows)
        self.table_view.setSelectionMode(QTableView.SelectionMode.SingleSelection)
        
        # Set column widths
        header = self.table_view.horizontalHeader()
        header.setSectionResizeMode(0, QHeaderView.ResizeMode.Fixed)
        header.setSectionResizeMode(1, QHeaderView.ResizeMode.Stretch)
        header.setSectionResizeMode(2, QHeaderView.ResizeMode.Fixed)
        header.setSectionResizeMode(3, QHeaderView.ResizeMode.Fixed)
        header.setSectionResizeMode(4, QHeaderView.ResizeMode.Fixed)
        header.setSectionResizeMode(5, QHeaderView.ResizeMode.Fixed)
        
        self.table_view.setColumnWidth(0, 50)
        self.table_view.setColumnWidth(2, 120)
        self.table_view.setColumnWidth(3, 100)
        self.table_view.setColumnWidth(4, 80)
        self.table_view.setColumnWidth(5, 150)
        
        layout.addWidget(self.table_view)
        
        # Action buttons
        button_layout = QHBoxLayout()
        
        add_btn = QPushButton("➕ Add Product")
        add_btn.clicked.connect(self.add_product)
        button_layout.addWidget(add_btn)
        
        edit_btn = QPushButton("✏️ Edit Selected")
        edit_btn.clicked.connect(self.edit_product)
        button_layout.addWidget(edit_btn)
        
        delete_btn = QPushButton("❌ Delete Selected")
        delete_btn.clicked.connect(self.delete_product)
        button_layout.addWidget(delete_btn)
        
        button_layout.addStretch()
        
        # Statistics
        self.stats_label = QLabel()
        button_layout.addWidget(self.stats_label)
        
        layout.addLayout(button_layout)
    
    def apply_filter(self, text):
        """Apply text filter."""
        self.proxy_model.setFilterKeyColumn(-1)  # Search all columns
        self.proxy_model.setFilterFixedString(text)
    
    def apply_category_filter(self, category):
        """Filter by category."""
        if category == "All Categories":
            self.proxy_model.setFilterKeyColumn(-1)
            self.proxy_model.setFilterFixedString("")
        else:
            self.proxy_model.setFilterKeyColumn(2)  # Category column
            self.proxy_model.setFilterFixedString(category)
    
    def refresh_data(self):
        """Refresh data from database."""
        self.model.select()
        self.update_statistics()
    
    def add_product(self):
        """Show dialog to add a new product."""
        dialog = ProductDialog(self)
        if dialog.exec() == QDialog.DialogCode.Accepted:
            data = dialog.get_data()
            try:
                self.db_manager.add_product(
                    data["name"], data["category"],
                    data["price"], data["quantity"]
                )
                self.refresh_data()
                QMessageBox.information(self, "Success", "Product added successfully!")
            except Exception as e:
                QMessageBox.critical(self, "Error", str(e))
    
    def edit_product(self):
        """Edit the selected product."""
        selection = self.table_view.selectionModel().selectedRows()
        if not selection:
            QMessageBox.information(self, "Info", "Please select a product to edit.")
            return
        
        proxy_index = selection[0]
        source_index = self.proxy_model.mapToSource(proxy_index)
        row = source_index.row()
        
        # Get current data
        product_data = {
            "id": self.model.data(self.model.index(row, 0)),
            "name": self.model.data(self.model.index(row, 1)),
            "category": self.model.data(self.model.index(row, 2)),
            "price": self.model.data(self.model.index(row, 3)),
            "quantity": self.model.data(self.model.index(row, 4)),
        }
        
        dialog = ProductDialog(self, product_data)
        if dialog.exec() == QDialog.DialogCode.Accepted:
            data = dialog.get_data()
            try:
                self.db_manager.update_product(
                    product_data["id"],
                    data["name"], data["category"],
                    data["price"], data["quantity"]
                )
                self.refresh_data()
                QMessageBox.information(self, "Success", "Product updated successfully!")
            except Exception as e:
                QMessageBox.critical(self, "Error", str(e))
    
    def delete_product(self):
        """Delete the selected product."""
        selection = self.table_view.selectionModel().selectedRows()
        if not selection:
            QMessageBox.information(self, "Info", "Please select a product to delete.")
            return
        
        proxy_index = selection[0]
        source_index = self.proxy_model.mapToSource(proxy_index)
        row = source_index.row()
        
        product_id = self.model.data(self.model.index(row, 0))
        product_name = self.model.data(self.model.index(row, 1))
        
        result = QMessageBox.question(
            self, "Confirm Delete",
            f"Are you sure you want to delete '{product_name}'?",
            QMessageBox.StandardButton.Yes | QMessageBox.StandardButton.No
        )
        
        if result == QMessageBox.StandardButton.Yes:
            try:
                self.db_manager.delete_product(product_id)
                self.refresh_data()
                QMessageBox.information(self, "Success", "Product deleted successfully!")
            except Exception as e:
                QMessageBox.critical(self, "Error", str(e))
    
    def update_statistics(self):
        """Update statistics display."""
        stats = self.db_manager.get_statistics()
        self.stats_label.setText(
            f"Products: {stats.get('total_products', 0)} | "
            f"Items: {stats.get('total_items', 0):,} | "
            f"Total Value: ${stats.get('total_value', 0):,.2f} | "
            f"Categories: {stats.get('categories', 0)}"
        )
    
    def closeEvent(self, event):
        """Clean up on close."""
        self.db_manager.close()
        
        # Remove database file (for demo purposes)
        # In production, you'd keep the database
        # if os.path.exists("products.db"):
        #     os.remove("products.db")
        
        event.accept()


def main():
    app = QApplication(sys.argv)
    window = DatabaseDemo()
    window.show()
    sys.exit(app.exec())


if __name__ == "__main__":
    main()
