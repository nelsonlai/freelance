"""
PySide6 Beginner Example 03: Layout Management
==============================================

This example demonstrates:
- QVBoxLayout (vertical layout)
- QHBoxLayout (horizontal layout)
- QGridLayout (grid layout)
- QFormLayout (form layout)
- Nested layouts
- Spacing and margins

Run: python 03_layouts.py
"""

import sys
from PySide6.QtWidgets import (
    QApplication, QMainWindow, QWidget, QTabWidget,
    QVBoxLayout, QHBoxLayout, QGridLayout, QFormLayout,
    QLabel, QPushButton, QLineEdit, QSpinBox, QGroupBox
)
from PySide6.QtCore import Qt


class LayoutDemo(QMainWindow):
    """Demonstrates different layout types."""
    
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Layout Management Demo")
        self.setMinimumSize(600, 500)
        
        # Use a tab widget to show different layouts
        tabs = QTabWidget()
        self.setCentralWidget(tabs)
        
        tabs.addTab(self.create_vbox_demo(), "VBox Layout")
        tabs.addTab(self.create_hbox_demo(), "HBox Layout")
        tabs.addTab(self.create_grid_demo(), "Grid Layout")
        tabs.addTab(self.create_form_demo(), "Form Layout")
        tabs.addTab(self.create_nested_demo(), "Nested Layouts")
    
    def create_vbox_demo(self):
        """Vertical layout demonstration."""
        widget = QWidget()
        layout = QVBoxLayout(widget)
        
        # Add explanation
        info = QLabel(
            "QVBoxLayout arranges widgets vertically, one below another.\n"
            "Widgets expand horizontally to fill the available width."
        )
        info.setWordWrap(True)
        info.setStyleSheet("background: #e3f2fd; padding: 10px; border-radius: 5px;")
        layout.addWidget(info)
        
        # Add some buttons
        for i in range(1, 6):
            btn = QPushButton(f"Button {i}")
            layout.addWidget(btn)
        
        # Add stretch at the bottom
        layout.addStretch()
        
        # Demonstrate spacing
        layout.setSpacing(10)
        layout.setContentsMargins(20, 20, 20, 20)
        
        return widget
    
    def create_hbox_demo(self):
        """Horizontal layout demonstration."""
        widget = QWidget()
        main_layout = QVBoxLayout(widget)
        
        # Add explanation
        info = QLabel(
            "QHBoxLayout arranges widgets horizontally, side by side.\n"
            "Use addStretch() to control spacing and alignment."
        )
        info.setWordWrap(True)
        info.setStyleSheet("background: #e3f2fd; padding: 10px; border-radius: 5px;")
        main_layout.addWidget(info)
        
        # Example 1: Equal spacing
        group1 = QGroupBox("Equal Distribution")
        h1 = QHBoxLayout(group1)
        for i in range(1, 4):
            h1.addWidget(QPushButton(f"Button {i}"))
        main_layout.addWidget(group1)
        
        # Example 2: Left aligned
        group2 = QGroupBox("Left Aligned")
        h2 = QHBoxLayout(group2)
        for i in range(1, 4):
            h2.addWidget(QPushButton(f"Button {i}"))
        h2.addStretch()  # Push buttons to the left
        main_layout.addWidget(group2)
        
        # Example 3: Right aligned
        group3 = QGroupBox("Right Aligned")
        h3 = QHBoxLayout(group3)
        h3.addStretch()  # Push buttons to the right
        for i in range(1, 4):
            h3.addWidget(QPushButton(f"Button {i}"))
        main_layout.addWidget(group3)
        
        # Example 4: Center aligned
        group4 = QGroupBox("Center Aligned")
        h4 = QHBoxLayout(group4)
        h4.addStretch()
        for i in range(1, 4):
            h4.addWidget(QPushButton(f"Button {i}"))
        h4.addStretch()
        main_layout.addWidget(group4)
        
        main_layout.addStretch()
        
        return widget
    
    def create_grid_demo(self):
        """Grid layout demonstration."""
        widget = QWidget()
        main_layout = QVBoxLayout(widget)
        
        # Add explanation
        info = QLabel(
            "QGridLayout arranges widgets in a grid of rows and columns.\n"
            "Widgets can span multiple rows or columns."
        )
        info.setWordWrap(True)
        info.setStyleSheet("background: #e3f2fd; padding: 10px; border-radius: 5px;")
        main_layout.addWidget(info)
        
        # Calculator-style grid
        group = QGroupBox("Calculator Layout Example")
        grid = QGridLayout(group)
        
        # Display
        display = QLineEdit("0")
        display.setAlignment(Qt.AlignmentFlag.AlignRight)
        display.setReadOnly(True)
        display.setStyleSheet("font-size: 24px; padding: 10px;")
        grid.addWidget(display, 0, 0, 1, 4)  # Row 0, Col 0, Span 1 row, 4 cols
        
        # Buttons
        buttons = [
            ('7', 1, 0), ('8', 1, 1), ('9', 1, 2), ('/', 1, 3),
            ('4', 2, 0), ('5', 2, 1), ('6', 2, 2), ('*', 2, 3),
            ('1', 3, 0), ('2', 3, 1), ('3', 3, 2), ('-', 3, 3),
            ('0', 4, 0, 1, 2), ('.', 4, 2), ('+', 4, 3),
        ]
        
        for item in buttons:
            text = item[0]
            row = item[1]
            col = item[2]
            row_span = item[3] if len(item) > 3 else 1
            col_span = item[4] if len(item) > 4 else 1
            
            btn = QPushButton(text)
            btn.setMinimumSize(50, 50)
            grid.addWidget(btn, row, col, row_span, col_span)
        
        # Equal button spanning
        equal_btn = QPushButton("=")
        equal_btn.setMinimumHeight(50)
        equal_btn.setStyleSheet("background: #4CAF50; color: white;")
        grid.addWidget(equal_btn, 5, 0, 1, 4)
        
        main_layout.addWidget(group)
        main_layout.addStretch()
        
        return widget
    
    def create_form_demo(self):
        """Form layout demonstration."""
        widget = QWidget()
        main_layout = QVBoxLayout(widget)
        
        # Add explanation
        info = QLabel(
            "QFormLayout is optimized for creating form-style layouts.\n"
            "It automatically aligns labels and fields in a two-column layout."
        )
        info.setWordWrap(True)
        info.setStyleSheet("background: #e3f2fd; padding: 10px; border-radius: 5px;")
        main_layout.addWidget(info)
        
        # Form
        group = QGroupBox("User Registration")
        form = QFormLayout(group)
        
        # Add form rows
        form.addRow("First Name:", QLineEdit())
        form.addRow("Last Name:", QLineEdit())
        form.addRow("Email:", QLineEdit())
        form.addRow("Age:", QSpinBox())
        form.addRow("Phone:", QLineEdit())
        
        # Add a section header
        form.addRow(QLabel(""))  # Spacer
        section = QLabel("Optional Information")
        section.setStyleSheet("font-weight: bold; color: #1976d2;")
        form.addRow(section)
        
        form.addRow("Company:", QLineEdit())
        form.addRow("Website:", QLineEdit())
        
        # Submit button
        form.addRow("", QPushButton("Register"))
        
        main_layout.addWidget(group)
        main_layout.addStretch()
        
        return widget
    
    def create_nested_demo(self):
        """Nested layouts demonstration."""
        widget = QWidget()
        main_layout = QVBoxLayout(widget)
        
        # Add explanation
        info = QLabel(
            "Layouts can be nested inside each other to create complex UIs.\n"
            "This example shows a typical application layout structure."
        )
        info.setWordWrap(True)
        info.setStyleSheet("background: #e3f2fd; padding: 10px; border-radius: 5px;")
        main_layout.addWidget(info)
        
        # Header section (horizontal)
        header = QHBoxLayout()
        logo = QLabel("🚀 MyApp")
        logo.setStyleSheet("font-size: 20px; font-weight: bold;")
        header.addWidget(logo)
        header.addStretch()
        header.addWidget(QPushButton("Settings"))
        header.addWidget(QPushButton("Profile"))
        main_layout.addLayout(header)
        
        # Content area (horizontal: sidebar + main content)
        content = QHBoxLayout()
        
        # Sidebar (vertical)
        sidebar = QVBoxLayout()
        sidebar_group = QGroupBox("Navigation")
        sidebar_inner = QVBoxLayout(sidebar_group)
        for item in ["Dashboard", "Users", "Products", "Orders", "Reports"]:
            btn = QPushButton(item)
            btn.setCheckable(True)
            sidebar_inner.addWidget(btn)
        sidebar_inner.addStretch()
        sidebar.addWidget(sidebar_group)
        content.addLayout(sidebar, 1)  # Stretch factor 1
        
        # Main content (vertical with grid)
        main_content = QVBoxLayout()
        
        # Stats section (horizontal)
        stats = QHBoxLayout()
        for title, value, color in [
            ("Users", "1,234", "#2196F3"),
            ("Orders", "567", "#4CAF50"),
            ("Revenue", "$12,345", "#FF9800"),
        ]:
            stat_widget = QWidget()
            stat_widget.setStyleSheet(f"background: {color}; border-radius: 8px;")
            stat_layout = QVBoxLayout(stat_widget)
            stat_layout.addWidget(
                QLabel(value),
                alignment=Qt.AlignmentFlag.AlignCenter
            )
            stat_layout.addWidget(
                QLabel(title),
                alignment=Qt.AlignmentFlag.AlignCenter
            )
            stat_widget.setStyleSheet(f"""
                background: {color}; 
                border-radius: 8px; 
                color: white; 
                padding: 10px;
            """)
            stats.addWidget(stat_widget)
        main_content.addLayout(stats)
        
        # Data table placeholder
        table_placeholder = QLabel("📊 Data Table Goes Here")
        table_placeholder.setAlignment(Qt.AlignmentFlag.AlignCenter)
        table_placeholder.setStyleSheet("""
            background: #f5f5f5; 
            border: 2px dashed #ccc; 
            border-radius: 8px; 
            padding: 40px;
            font-size: 16px;
        """)
        main_content.addWidget(table_placeholder, 1)  # Stretch to fill
        
        content.addLayout(main_content, 3)  # Stretch factor 3
        main_layout.addLayout(content, 1)
        
        # Footer (horizontal)
        footer = QHBoxLayout()
        footer.addWidget(QLabel("© 2025 MyApp"))
        footer.addStretch()
        footer.addWidget(QLabel("Version 1.0.0"))
        main_layout.addLayout(footer)
        
        return widget


def main():
    app = QApplication(sys.argv)
    window = LayoutDemo()
    window.show()
    sys.exit(app.exec())


if __name__ == "__main__":
    main()
