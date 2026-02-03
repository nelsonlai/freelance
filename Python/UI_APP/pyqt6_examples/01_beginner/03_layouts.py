"""
PyQt6 Beginner Example 03: Layout Management
============================================

This example demonstrates:
- QVBoxLayout (vertical layout)
- QHBoxLayout (horizontal layout)
- QGridLayout (grid layout)
- QFormLayout (form layout)
- Nested layouts

Run: python 03_layouts.py
"""

import sys
from PyQt6.QtWidgets import (
    QApplication, QMainWindow, QWidget, QTabWidget,
    QVBoxLayout, QHBoxLayout, QGridLayout, QFormLayout,
    QLabel, QPushButton, QLineEdit, QSpinBox, QGroupBox
)
from PyQt6.QtCore import Qt


class LayoutDemo(QMainWindow):
    """Demonstrates different layout types."""
    
    def __init__(self):
        super().__init__()
        self.setWindowTitle("PyQt6 Layout Management Demo")
        self.setMinimumSize(600, 500)
        
        tabs = QTabWidget()
        self.setCentralWidget(tabs)
        
        tabs.addTab(self.create_vbox_demo(), "VBox Layout")
        tabs.addTab(self.create_hbox_demo(), "HBox Layout")
        tabs.addTab(self.create_grid_demo(), "Grid Layout")
        tabs.addTab(self.create_form_demo(), "Form Layout")
    
    def create_vbox_demo(self):
        """Vertical layout demonstration."""
        widget = QWidget()
        layout = QVBoxLayout(widget)
        
        info = QLabel(
            "QVBoxLayout arranges widgets vertically, one below another."
        )
        info.setWordWrap(True)
        info.setStyleSheet("background: #e3f2fd; padding: 10px; border-radius: 5px;")
        layout.addWidget(info)
        
        for i in range(1, 6):
            btn = QPushButton(f"Button {i}")
            layout.addWidget(btn)
        
        layout.addStretch()
        layout.setSpacing(10)
        
        return widget
    
    def create_hbox_demo(self):
        """Horizontal layout demonstration."""
        widget = QWidget()
        main_layout = QVBoxLayout(widget)
        
        info = QLabel("QHBoxLayout arranges widgets horizontally.")
        info.setStyleSheet("background: #e3f2fd; padding: 10px; border-radius: 5px;")
        main_layout.addWidget(info)
        
        # Left aligned
        group1 = QGroupBox("Left Aligned")
        h1 = QHBoxLayout(group1)
        for i in range(3):
            h1.addWidget(QPushButton(f"Btn {i+1}"))
        h1.addStretch()
        main_layout.addWidget(group1)
        
        # Right aligned
        group2 = QGroupBox("Right Aligned")
        h2 = QHBoxLayout(group2)
        h2.addStretch()
        for i in range(3):
            h2.addWidget(QPushButton(f"Btn {i+1}"))
        main_layout.addWidget(group2)
        
        main_layout.addStretch()
        
        return widget
    
    def create_grid_demo(self):
        """Grid layout demonstration."""
        widget = QWidget()
        main_layout = QVBoxLayout(widget)
        
        info = QLabel("QGridLayout arranges widgets in a grid.")
        info.setStyleSheet("background: #e3f2fd; padding: 10px; border-radius: 5px;")
        main_layout.addWidget(info)
        
        # Calculator-style grid
        group = QGroupBox("Calculator Layout")
        grid = QGridLayout(group)
        
        display = QLineEdit("0")
        display.setAlignment(Qt.AlignmentFlag.AlignRight)
        display.setReadOnly(True)
        display.setStyleSheet("font-size: 24px; padding: 10px;")
        grid.addWidget(display, 0, 0, 1, 4)
        
        buttons = [
            ('7', 1, 0), ('8', 1, 1), ('9', 1, 2), ('/', 1, 3),
            ('4', 2, 0), ('5', 2, 1), ('6', 2, 2), ('*', 2, 3),
            ('1', 3, 0), ('2', 3, 1), ('3', 3, 2), ('-', 3, 3),
            ('0', 4, 0), ('.', 4, 1), ('=', 4, 2), ('+', 4, 3),
        ]
        
        for text, row, col in buttons:
            btn = QPushButton(text)
            btn.setMinimumSize(50, 50)
            grid.addWidget(btn, row, col)
        
        main_layout.addWidget(group)
        main_layout.addStretch()
        
        return widget
    
    def create_form_demo(self):
        """Form layout demonstration."""
        widget = QWidget()
        main_layout = QVBoxLayout(widget)
        
        info = QLabel("QFormLayout is optimized for form-style layouts.")
        info.setStyleSheet("background: #e3f2fd; padding: 10px; border-radius: 5px;")
        main_layout.addWidget(info)
        
        group = QGroupBox("User Registration")
        form = QFormLayout(group)
        
        form.addRow("First Name:", QLineEdit())
        form.addRow("Last Name:", QLineEdit())
        form.addRow("Email:", QLineEdit())
        form.addRow("Age:", QSpinBox())
        form.addRow("", QPushButton("Register"))
        
        main_layout.addWidget(group)
        main_layout.addStretch()
        
        return widget


def main():
    app = QApplication(sys.argv)
    window = LayoutDemo()
    window.show()
    sys.exit(app.exec())


if __name__ == "__main__":
    main()
