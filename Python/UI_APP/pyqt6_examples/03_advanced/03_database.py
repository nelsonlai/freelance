"""
PyQt6 Advanced Example 03: Database Connectivity
================================================

This example demonstrates:
- SQLite database with Qt SQL module
- QSqlTableModel for database binding
- CRUD operations

Run: python 03_database.py
"""

import sys
from PyQt6.QtWidgets import (
    QApplication, QMainWindow, QWidget, QVBoxLayout, QHBoxLayout,
    QTableView, QHeaderView, QPushButton, QLineEdit, QLabel,
    QMessageBox, QDialog, QFormLayout, QDialogButtonBox,
    QSpinBox, QDoubleSpinBox, QComboBox, QGroupBox
)
from PyQt6.QtCore import Qt, QSortFilterProxyModel
from PyQt6.QtSql import QSqlDatabase, QSqlQuery, QSqlTableModel


SAMPLE_DATA = [
    ("Laptop", "Electronics", 999.99, 50),
    ("Smartphone", "Electronics", 699.99, 100),
    ("T-Shirt", "Clothing", 29.99, 500),
    ("Novel", "Books", 14.99, 150),
]


class ProductDialog(QDialog):
    def __init__(self, parent=None, product_data=None):
        super().__init__(parent)
        self.setWindowTitle("Edit Product" if product_data else "Add Product")
        self.setMinimumWidth(300)
        
        layout = QVBoxLayout(self)
        form = QFormLayout()
        
        self.name_input = QLineEdit()
        form.addRow("Name:", self.name_input)
        
        self.category_input = QComboBox()
        self.category_input.setEditable(True)
        self.category_input.addItems(["Electronics", "Clothing", "Books", "Other"])
        form.addRow("Category:", self.category_input)
        
        self.price_input = QDoubleSpinBox()
        self.price_input.setRange(0, 1000000)
        self.price_input.setPrefix("$")
        form.addRow("Price:", self.price_input)
        
        self.quantity_input = QSpinBox()
        self.quantity_input.setRange(0, 1000000)
        form.addRow("Quantity:", self.quantity_input)
        
        layout.addLayout(form)
        
        buttons = QDialogButtonBox(
            QDialogButtonBox.StandardButton.Ok |
            QDialogButtonBox.StandardButton.Cancel
        )
        buttons.accepted.connect(self.accept)
        buttons.rejected.connect(self.reject)
        layout.addWidget(buttons)
        
        if product_data:
            self.name_input.setText(product_data.get("name", ""))
            self.category_input.setCurrentText(product_data.get("category", ""))
            self.price_input.setValue(product_data.get("price", 0))
            self.quantity_input.setValue(product_data.get("quantity", 0))
    
    def get_data(self):
        return {
            "name": self.name_input.text(),
            "category": self.category_input.currentText(),
            "price": self.price_input.value(),
            "quantity": self.quantity_input.value()
        }


class DatabaseDemo(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("PyQt6 Database Demo")
        self.setMinimumSize(700, 500)
        
        self.setup_database()
        
        self.model = QSqlTableModel()
        self.model.setTable("products")
        self.model.setEditStrategy(QSqlTableModel.EditStrategy.OnFieldChange)
        self.model.select()
        
        self.model.setHeaderData(0, Qt.Orientation.Horizontal, "ID")
        self.model.setHeaderData(1, Qt.Orientation.Horizontal, "Name")
        self.model.setHeaderData(2, Qt.Orientation.Horizontal, "Category")
        self.model.setHeaderData(3, Qt.Orientation.Horizontal, "Price")
        self.model.setHeaderData(4, Qt.Orientation.Horizontal, "Quantity")
        
        self.proxy_model = QSortFilterProxyModel()
        self.proxy_model.setSourceModel(self.model)
        self.proxy_model.setFilterCaseSensitivity(Qt.CaseSensitivity.CaseInsensitive)
        
        self.setup_ui()
    
    def setup_database(self):
        db = QSqlDatabase.addDatabase("QSQLITE")
        db.setDatabaseName("pyqt6_products.db")
        
        if not db.open():
            QMessageBox.critical(self, "Error", "Cannot open database")
            sys.exit(1)
        
        query = QSqlQuery()
        query.exec("""
            CREATE TABLE IF NOT EXISTS products (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                name TEXT NOT NULL,
                category TEXT,
                price REAL DEFAULT 0,
                quantity INTEGER DEFAULT 0
            )
        """)
        
        query.exec("SELECT COUNT(*) FROM products")
        if query.next() and query.value(0) == 0:
            for name, cat, price, qty in SAMPLE_DATA:
                query.prepare("INSERT INTO products (name, category, price, quantity) VALUES (?, ?, ?, ?)")
                query.addBindValue(name)
                query.addBindValue(cat)
                query.addBindValue(price)
                query.addBindValue(qty)
                query.exec()
    
    def setup_ui(self):
        central = QWidget()
        self.setCentralWidget(central)
        layout = QVBoxLayout(central)
        
        # Filter
        filter_group = QGroupBox("Search")
        filter_layout = QHBoxLayout(filter_group)
        
        filter_layout.addWidget(QLabel("Search:"))
        self.search_input = QLineEdit()
        self.search_input.textChanged.connect(self.apply_filter)
        filter_layout.addWidget(self.search_input)
        
        refresh_btn = QPushButton("Refresh")
        refresh_btn.clicked.connect(self.model.select)
        filter_layout.addWidget(refresh_btn)
        
        layout.addWidget(filter_group)
        
        # Table
        self.table_view = QTableView()
        self.table_view.setModel(self.proxy_model)
        self.table_view.setSortingEnabled(True)
        self.table_view.setAlternatingRowColors(True)
        self.table_view.setSelectionBehavior(QTableView.SelectionBehavior.SelectRows)
        
        header = self.table_view.horizontalHeader()
        header.setSectionResizeMode(1, QHeaderView.ResizeMode.Stretch)
        
        layout.addWidget(self.table_view)
        
        # Buttons
        btn_layout = QHBoxLayout()
        
        add_btn = QPushButton("Add Product")
        add_btn.clicked.connect(self.add_product)
        btn_layout.addWidget(add_btn)
        
        delete_btn = QPushButton("Delete Selected")
        delete_btn.clicked.connect(self.delete_product)
        btn_layout.addWidget(delete_btn)
        
        btn_layout.addStretch()
        layout.addLayout(btn_layout)
    
    def apply_filter(self, text):
        self.proxy_model.setFilterKeyColumn(-1)
        self.proxy_model.setFilterFixedString(text)
    
    def add_product(self):
        dialog = ProductDialog(self)
        if dialog.exec() == QDialog.DialogCode.Accepted:
            data = dialog.get_data()
            query = QSqlQuery()
            query.prepare("INSERT INTO products (name, category, price, quantity) VALUES (?, ?, ?, ?)")
            query.addBindValue(data["name"])
            query.addBindValue(data["category"])
            query.addBindValue(data["price"])
            query.addBindValue(data["quantity"])
            query.exec()
            self.model.select()
    
    def delete_product(self):
        selection = self.table_view.selectionModel().selectedRows()
        if not selection:
            QMessageBox.information(self, "Info", "Select a product to delete")
            return
        
        proxy_index = selection[0]
        source_index = self.proxy_model.mapToSource(proxy_index)
        
        result = QMessageBox.question(
            self, "Confirm", "Delete selected product?",
            QMessageBox.StandardButton.Yes | QMessageBox.StandardButton.No
        )
        
        if result == QMessageBox.StandardButton.Yes:
            self.model.removeRow(source_index.row())
            self.model.select()


def main():
    app = QApplication(sys.argv)
    window = DatabaseDemo()
    window.show()
    sys.exit(app.exec())


if __name__ == "__main__":
    main()
