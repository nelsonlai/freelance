"""
PyQt6 Intermediate Example 02: Model-View Programming
=====================================================

This example demonstrates:
- QAbstractTableModel for custom data models
- QTableView for displaying tabular data
- QSortFilterProxyModel for sorting and filtering

Run: python 02_model_view.py
"""

import sys
from PyQt6.QtWidgets import (
    QApplication, QMainWindow, QWidget, QVBoxLayout, QHBoxLayout,
    QTableView, QHeaderView, QPushButton, QLineEdit, QLabel,
    QSpinBox, QComboBox, QMessageBox, QGroupBox
)
from PyQt6.QtCore import Qt, QAbstractTableModel, QModelIndex, QSortFilterProxyModel


SAMPLE_DATA = [
    {"id": 1, "name": "Alice Johnson", "age": 28, "department": "Engineering"},
    {"id": 2, "name": "Bob Smith", "age": 35, "department": "Marketing"},
    {"id": 3, "name": "Carol Williams", "age": 42, "department": "Engineering"},
    {"id": 4, "name": "David Brown", "age": 31, "department": "Sales"},
    {"id": 5, "name": "Eva Martinez", "age": 26, "department": "Engineering"},
]


class EmployeeTableModel(QAbstractTableModel):
    """Custom table model for employee data."""
    
    COLUMNS = ["ID", "Name", "Age", "Department"]
    
    def __init__(self, data=None):
        super().__init__()
        self._data = data or []
    
    def rowCount(self, parent=QModelIndex()):
        return len(self._data)
    
    def columnCount(self, parent=QModelIndex()):
        return len(self.COLUMNS)
    
    def data(self, index, role=Qt.ItemDataRole.DisplayRole):
        if not index.isValid():
            return None
        
        employee = self._data[index.row()]
        column = index.column()
        
        if role == Qt.ItemDataRole.DisplayRole:
            if column == 0:
                return employee["id"]
            elif column == 1:
                return employee["name"]
            elif column == 2:
                return employee["age"]
            elif column == 3:
                return employee["department"]
        
        elif role == Qt.ItemDataRole.TextAlignmentRole:
            if column in [0, 2]:
                return Qt.AlignmentFlag.AlignRight | Qt.AlignmentFlag.AlignVCenter
            return Qt.AlignmentFlag.AlignLeft | Qt.AlignmentFlag.AlignVCenter
        
        return None
    
    def headerData(self, section, orientation, role=Qt.ItemDataRole.DisplayRole):
        if role == Qt.ItemDataRole.DisplayRole:
            if orientation == Qt.Orientation.Horizontal:
                return self.COLUMNS[section]
            return str(section + 1)
        return None
    
    def flags(self, index):
        return Qt.ItemFlag.ItemIsEnabled | Qt.ItemFlag.ItemIsSelectable


class ModelViewDemo(QMainWindow):
    """Main window demonstrating Model-View programming."""
    
    def __init__(self):
        super().__init__()
        self.setWindowTitle("PyQt6 Model-View Demo")
        self.setMinimumSize(700, 500)
        
        central = QWidget()
        self.setCentralWidget(central)
        layout = QVBoxLayout(central)
        
        # Create model
        self.model = EmployeeTableModel([e.copy() for e in SAMPLE_DATA])
        
        # Create proxy for filtering
        self.proxy_model = QSortFilterProxyModel()
        self.proxy_model.setSourceModel(self.model)
        self.proxy_model.setFilterCaseSensitivity(Qt.CaseSensitivity.CaseInsensitive)
        
        # Filter controls
        filter_group = QGroupBox("Filter & Search")
        filter_layout = QHBoxLayout(filter_group)
        
        filter_layout.addWidget(QLabel("Search:"))
        self.search_input = QLineEdit()
        self.search_input.setPlaceholderText("Type to search...")
        self.search_input.textChanged.connect(self.apply_filter)
        filter_layout.addWidget(self.search_input)
        
        filter_layout.addWidget(QLabel("Column:"))
        self.column_combo = QComboBox()
        self.column_combo.addItem("All Columns", -1)
        for i, col in enumerate(EmployeeTableModel.COLUMNS):
            self.column_combo.addItem(col, i)
        self.column_combo.currentIndexChanged.connect(self.apply_filter)
        filter_layout.addWidget(self.column_combo)
        
        layout.addWidget(filter_group)
        
        # Table view
        self.table_view = QTableView()
        self.table_view.setModel(self.proxy_model)
        self.table_view.setSortingEnabled(True)
        self.table_view.setAlternatingRowColors(True)
        self.table_view.setSelectionBehavior(QTableView.SelectionBehavior.SelectRows)
        
        header = self.table_view.horizontalHeader()
        header.setSectionResizeMode(1, QHeaderView.ResizeMode.Stretch)
        
        layout.addWidget(self.table_view)
        
        # Count label
        self.count_label = QLabel(f"Total: {len(SAMPLE_DATA)} employees")
        layout.addWidget(self.count_label)
    
    def apply_filter(self):
        text = self.search_input.text()
        column = self.column_combo.currentData()
        
        self.proxy_model.setFilterKeyColumn(column if column >= 0 else -1)
        self.proxy_model.setFilterFixedString(text)
        
        # Update count
        filtered = self.proxy_model.rowCount()
        total = self.model.rowCount()
        if filtered == total:
            self.count_label.setText(f"Total: {total} employees")
        else:
            self.count_label.setText(f"Showing: {filtered} of {total} employees")


def main():
    app = QApplication(sys.argv)
    window = ModelViewDemo()
    window.show()
    sys.exit(app.exec())


if __name__ == "__main__":
    main()
