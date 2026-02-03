"""
PySide6 Intermediate Example 02: Model-View Programming
=======================================================

This example demonstrates:
- QAbstractTableModel for custom data models
- QTableView for displaying tabular data
- QSortFilterProxyModel for sorting and filtering
- Custom delegates for editing
- CRUD operations with models

Run: python 02_model_view.py
"""

import sys
from PySide6.QtWidgets import (
    QApplication, QMainWindow, QWidget, QVBoxLayout, QHBoxLayout,
    QTableView, QHeaderView, QPushButton, QLineEdit, QLabel,
    QSpinBox, QComboBox, QStyledItemDelegate, QMessageBox,
    QGroupBox, QFormLayout, QDialog, QDialogButtonBox
)
from PySide6.QtCore import Qt, QAbstractTableModel, QModelIndex, QSortFilterProxyModel


# Sample data
SAMPLE_DATA = [
    {"id": 1, "name": "Alice Johnson", "age": 28, "department": "Engineering", "salary": 75000},
    {"id": 2, "name": "Bob Smith", "age": 35, "department": "Marketing", "salary": 65000},
    {"id": 3, "name": "Carol Williams", "age": 42, "department": "Engineering", "salary": 95000},
    {"id": 4, "name": "David Brown", "age": 31, "department": "Sales", "salary": 55000},
    {"id": 5, "name": "Eva Martinez", "age": 26, "department": "Engineering", "salary": 70000},
    {"id": 6, "name": "Frank Lee", "age": 45, "department": "HR", "salary": 60000},
    {"id": 7, "name": "Grace Kim", "age": 38, "department": "Marketing", "salary": 72000},
    {"id": 8, "name": "Henry Davis", "age": 29, "department": "Sales", "salary": 52000},
]

DEPARTMENTS = ["Engineering", "Marketing", "Sales", "HR", "Finance", "Operations"]


class EmployeeTableModel(QAbstractTableModel):
    """Custom table model for employee data."""
    
    COLUMNS = ["ID", "Name", "Age", "Department", "Salary"]
    
    def __init__(self, data=None):
        super().__init__()
        self._data = data or []
        self._next_id = max((e["id"] for e in self._data), default=0) + 1
    
    def rowCount(self, parent=QModelIndex()):
        return len(self._data)
    
    def columnCount(self, parent=QModelIndex()):
        return len(self.COLUMNS)
    
    def data(self, index, role=Qt.ItemDataRole.DisplayRole):
        if not index.isValid() or not (0 <= index.row() < len(self._data)):
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
            elif column == 4:
                return f"${employee['salary']:,}"
        
        elif role == Qt.ItemDataRole.EditRole:
            if column == 0:
                return employee["id"]
            elif column == 1:
                return employee["name"]
            elif column == 2:
                return employee["age"]
            elif column == 3:
                return employee["department"]
            elif column == 4:
                return employee["salary"]
        
        elif role == Qt.ItemDataRole.TextAlignmentRole:
            if column in [0, 2, 4]:
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
        if index.column() == 0:  # ID is not editable
            return Qt.ItemFlag.ItemIsEnabled | Qt.ItemFlag.ItemIsSelectable
        return (Qt.ItemFlag.ItemIsEnabled | 
                Qt.ItemFlag.ItemIsSelectable | 
                Qt.ItemFlag.ItemIsEditable)
    
    def setData(self, index, value, role=Qt.ItemDataRole.EditRole):
        if not index.isValid() or role != Qt.ItemDataRole.EditRole:
            return False
        
        employee = self._data[index.row()]
        column = index.column()
        
        if column == 1:
            employee["name"] = value
        elif column == 2:
            employee["age"] = int(value)
        elif column == 3:
            employee["department"] = value
        elif column == 4:
            employee["salary"] = int(value)
        else:
            return False
        
        self.dataChanged.emit(index, index, [role])
        return True
    
    def addEmployee(self, name, age, department, salary):
        """Add a new employee."""
        row = len(self._data)
        self.beginInsertRows(QModelIndex(), row, row)
        
        self._data.append({
            "id": self._next_id,
            "name": name,
            "age": age,
            "department": department,
            "salary": salary
        })
        self._next_id += 1
        
        self.endInsertRows()
        return True
    
    def removeEmployee(self, row):
        """Remove an employee by row index."""
        if 0 <= row < len(self._data):
            self.beginRemoveRows(QModelIndex(), row, row)
            del self._data[row]
            self.endRemoveRows()
            return True
        return False
    
    def getEmployee(self, row):
        """Get employee data by row."""
        if 0 <= row < len(self._data):
            return self._data[row].copy()
        return None


class DepartmentDelegate(QStyledItemDelegate):
    """Custom delegate for department column (dropdown)."""
    
    def createEditor(self, parent, option, index):
        editor = QComboBox(parent)
        editor.addItems(DEPARTMENTS)
        return editor
    
    def setEditorData(self, editor, index):
        value = index.model().data(index, Qt.ItemDataRole.EditRole)
        idx = editor.findText(value)
        if idx >= 0:
            editor.setCurrentIndex(idx)
    
    def setModelData(self, editor, model, index):
        model.setData(index, editor.currentText(), Qt.ItemDataRole.EditRole)
    
    def updateEditorGeometry(self, editor, option, index):
        editor.setGeometry(option.rect)


class SalaryDelegate(QStyledItemDelegate):
    """Custom delegate for salary column (spin box)."""
    
    def createEditor(self, parent, option, index):
        editor = QSpinBox(parent)
        editor.setRange(0, 1000000)
        editor.setSingleStep(1000)
        editor.setPrefix("$")
        return editor
    
    def setEditorData(self, editor, index):
        value = index.model().data(index, Qt.ItemDataRole.EditRole)
        editor.setValue(int(value) if value else 0)
    
    def setModelData(self, editor, model, index):
        model.setData(index, editor.value(), Qt.ItemDataRole.EditRole)
    
    def updateEditorGeometry(self, editor, option, index):
        editor.setGeometry(option.rect)


class AddEmployeeDialog(QDialog):
    """Dialog for adding new employee."""
    
    def __init__(self, parent=None):
        super().__init__(parent)
        self.setWindowTitle("Add Employee")
        self.setMinimumWidth(300)
        
        layout = QVBoxLayout(self)
        
        form = QFormLayout()
        
        self.name_input = QLineEdit()
        form.addRow("Name:", self.name_input)
        
        self.age_input = QSpinBox()
        self.age_input.setRange(18, 100)
        self.age_input.setValue(30)
        form.addRow("Age:", self.age_input)
        
        self.dept_input = QComboBox()
        self.dept_input.addItems(DEPARTMENTS)
        form.addRow("Department:", self.dept_input)
        
        self.salary_input = QSpinBox()
        self.salary_input.setRange(0, 1000000)
        self.salary_input.setSingleStep(1000)
        self.salary_input.setValue(50000)
        self.salary_input.setPrefix("$")
        form.addRow("Salary:", self.salary_input)
        
        layout.addLayout(form)
        
        buttons = QDialogButtonBox(
            QDialogButtonBox.StandardButton.Ok | 
            QDialogButtonBox.StandardButton.Cancel
        )
        buttons.accepted.connect(self.validate_and_accept)
        buttons.rejected.connect(self.reject)
        layout.addWidget(buttons)
    
    def validate_and_accept(self):
        if not self.name_input.text().strip():
            QMessageBox.warning(self, "Error", "Name is required!")
            return
        self.accept()
    
    def get_data(self):
        return {
            "name": self.name_input.text(),
            "age": self.age_input.value(),
            "department": self.dept_input.currentText(),
            "salary": self.salary_input.value()
        }


class ModelViewDemo(QMainWindow):
    """Main window demonstrating Model-View programming."""
    
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Model-View Programming Demo")
        self.setMinimumSize(800, 600)
        
        central = QWidget()
        self.setCentralWidget(central)
        layout = QVBoxLayout(central)
        
        # Create model and proxy
        self.model = EmployeeTableModel([e.copy() for e in SAMPLE_DATA])
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
        
        filter_layout.addWidget(QLabel("Department:"))
        self.dept_filter = QComboBox()
        self.dept_filter.addItem("All Departments")
        self.dept_filter.addItems(DEPARTMENTS)
        self.dept_filter.currentTextChanged.connect(self.apply_department_filter)
        filter_layout.addWidget(self.dept_filter)
        
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
        
        self.table_view.setColumnWidth(0, 50)
        self.table_view.setColumnWidth(2, 60)
        self.table_view.setColumnWidth(3, 120)
        self.table_view.setColumnWidth(4, 100)
        
        # Set custom delegates
        self.table_view.setItemDelegateForColumn(3, DepartmentDelegate(self.table_view))
        self.table_view.setItemDelegateForColumn(4, SalaryDelegate(self.table_view))
        
        layout.addWidget(self.table_view)
        
        # Action buttons
        button_layout = QHBoxLayout()
        
        add_btn = QPushButton("➕ Add Employee")
        add_btn.clicked.connect(self.add_employee)
        button_layout.addWidget(add_btn)
        
        delete_btn = QPushButton("❌ Delete Selected")
        delete_btn.clicked.connect(self.delete_employee)
        button_layout.addWidget(delete_btn)
        
        button_layout.addStretch()
        
        self.count_label = QLabel()
        self.update_count_label()
        button_layout.addWidget(self.count_label)
        
        layout.addLayout(button_layout)
        
        # Connect model signals
        self.model.rowsInserted.connect(self.update_count_label)
        self.model.rowsRemoved.connect(self.update_count_label)
    
    def apply_filter(self):
        """Apply search filter."""
        text = self.search_input.text()
        column = self.column_combo.currentData()
        
        self.proxy_model.setFilterKeyColumn(column if column >= 0 else -1)
        self.proxy_model.setFilterFixedString(text)
    
    def apply_department_filter(self, department):
        """Filter by department."""
        if department == "All Departments":
            self.proxy_model.setFilterKeyColumn(-1)
            self.proxy_model.setFilterFixedString("")
        else:
            self.proxy_model.setFilterKeyColumn(3)  # Department column
            self.proxy_model.setFilterFixedString(department)
    
    def add_employee(self):
        """Show add employee dialog."""
        dialog = AddEmployeeDialog(self)
        if dialog.exec() == QDialog.DialogCode.Accepted:
            data = dialog.get_data()
            self.model.addEmployee(
                data["name"], data["age"], 
                data["department"], data["salary"]
            )
    
    def delete_employee(self):
        """Delete selected employee."""
        selection = self.table_view.selectionModel().selectedRows()
        if not selection:
            QMessageBox.information(self, "Info", "Please select an employee to delete.")
            return
        
        # Get source row from proxy
        proxy_index = selection[0]
        source_index = self.proxy_model.mapToSource(proxy_index)
        
        employee = self.model.getEmployee(source_index.row())
        
        result = QMessageBox.question(
            self, "Confirm Delete",
            f"Are you sure you want to delete '{employee['name']}'?",
            QMessageBox.StandardButton.Yes | QMessageBox.StandardButton.No
        )
        
        if result == QMessageBox.StandardButton.Yes:
            self.model.removeEmployee(source_index.row())
    
    def update_count_label(self):
        """Update the employee count label."""
        total = self.model.rowCount()
        filtered = self.proxy_model.rowCount()
        
        if total == filtered:
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
