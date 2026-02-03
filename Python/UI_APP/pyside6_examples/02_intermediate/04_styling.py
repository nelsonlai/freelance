"""
PySide6 Intermediate Example 04: Styling with Qt Style Sheets
=============================================================

This example demonstrates:
- Qt Style Sheets (QSS) syntax
- Styling individual widgets
- Application-wide themes
- Dark and light theme switching
- Custom styled components

Run: python 04_styling.py
"""

import sys
from PySide6.QtWidgets import (
    QApplication, QMainWindow, QWidget, QVBoxLayout, QHBoxLayout,
    QLabel, QPushButton, QLineEdit, QTextEdit, QCheckBox,
    QRadioButton, QComboBox, QSlider, QProgressBar, QGroupBox,
    QTabWidget, QListWidget, QTableWidget, QTableWidgetItem,
    QSpinBox, QScrollArea
)
from PySide6.QtCore import Qt


# Light Theme
LIGHT_THEME = """
/* Global styles */
QWidget {
    background-color: #f5f5f5;
    color: #212121;
    font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, Arial, sans-serif;
    font-size: 13px;
}

/* Main Window */
QMainWindow {
    background-color: #fafafa;
}

/* Labels */
QLabel {
    color: #424242;
    padding: 2px;
}

QLabel#title {
    font-size: 18px;
    font-weight: bold;
    color: #1976d2;
    padding: 10px;
}

/* Buttons */
QPushButton {
    background-color: #1976d2;
    color: white;
    border: none;
    padding: 8px 16px;
    border-radius: 4px;
    min-width: 80px;
}

QPushButton:hover {
    background-color: #1e88e5;
}

QPushButton:pressed {
    background-color: #1565c0;
}

QPushButton:disabled {
    background-color: #bdbdbd;
    color: #757575;
}

QPushButton#success {
    background-color: #43a047;
}

QPushButton#success:hover {
    background-color: #4caf50;
}

QPushButton#danger {
    background-color: #e53935;
}

QPushButton#danger:hover {
    background-color: #ef5350;
}

/* Text inputs */
QLineEdit, QTextEdit, QPlainTextEdit {
    background-color: white;
    border: 1px solid #bdbdbd;
    border-radius: 4px;
    padding: 8px;
    selection-background-color: #1976d2;
}

QLineEdit:focus, QTextEdit:focus, QPlainTextEdit:focus {
    border: 2px solid #1976d2;
}

QLineEdit:disabled, QTextEdit:disabled {
    background-color: #eeeeee;
    color: #9e9e9e;
}

/* Combo Box */
QComboBox {
    background-color: white;
    border: 1px solid #bdbdbd;
    border-radius: 4px;
    padding: 6px 12px;
    min-width: 120px;
}

QComboBox:hover {
    border-color: #1976d2;
}

QComboBox::drop-down {
    border: none;
    width: 30px;
}

QComboBox::down-arrow {
    width: 12px;
    height: 12px;
}

QComboBox QAbstractItemView {
    background-color: white;
    border: 1px solid #bdbdbd;
    selection-background-color: #e3f2fd;
    selection-color: #1976d2;
}

/* Spin Box */
QSpinBox, QDoubleSpinBox {
    background-color: white;
    border: 1px solid #bdbdbd;
    border-radius: 4px;
    padding: 6px;
}

QSpinBox:focus, QDoubleSpinBox:focus {
    border: 2px solid #1976d2;
}

/* Checkboxes and Radio Buttons */
QCheckBox, QRadioButton {
    spacing: 8px;
    padding: 4px;
}

QCheckBox::indicator, QRadioButton::indicator {
    width: 18px;
    height: 18px;
}

QCheckBox::indicator {
    border-radius: 3px;
}

QRadioButton::indicator {
    border-radius: 9px;
}

QCheckBox::indicator:unchecked, QRadioButton::indicator:unchecked {
    border: 2px solid #757575;
    background-color: white;
}

QCheckBox::indicator:checked {
    border: 2px solid #1976d2;
    background-color: #1976d2;
}

QRadioButton::indicator:checked {
    border: 2px solid #1976d2;
    background-color: #1976d2;
}

/* Slider */
QSlider::groove:horizontal {
    height: 6px;
    background: #bdbdbd;
    border-radius: 3px;
}

QSlider::handle:horizontal {
    background: #1976d2;
    width: 18px;
    height: 18px;
    margin: -6px 0;
    border-radius: 9px;
}

QSlider::handle:horizontal:hover {
    background: #1e88e5;
}

QSlider::sub-page:horizontal {
    background: #1976d2;
    border-radius: 3px;
}

/* Progress Bar */
QProgressBar {
    background-color: #e0e0e0;
    border-radius: 4px;
    text-align: center;
    height: 20px;
}

QProgressBar::chunk {
    background-color: #1976d2;
    border-radius: 4px;
}

/* Group Box */
QGroupBox {
    font-weight: bold;
    border: 1px solid #e0e0e0;
    border-radius: 6px;
    margin-top: 12px;
    padding-top: 12px;
}

QGroupBox::title {
    subcontrol-origin: margin;
    left: 12px;
    padding: 0 6px;
    color: #1976d2;
}

/* Tab Widget */
QTabWidget::pane {
    border: 1px solid #e0e0e0;
    border-radius: 4px;
    padding: 8px;
}

QTabBar::tab {
    background-color: #e0e0e0;
    color: #757575;
    padding: 10px 20px;
    margin-right: 2px;
    border-top-left-radius: 4px;
    border-top-right-radius: 4px;
}

QTabBar::tab:selected {
    background-color: white;
    color: #1976d2;
    border-bottom: 2px solid #1976d2;
}

QTabBar::tab:hover:!selected {
    background-color: #eeeeee;
}

/* List Widget */
QListWidget {
    background-color: white;
    border: 1px solid #e0e0e0;
    border-radius: 4px;
    padding: 4px;
}

QListWidget::item {
    padding: 8px;
    border-radius: 4px;
}

QListWidget::item:selected {
    background-color: #e3f2fd;
    color: #1976d2;
}

QListWidget::item:hover:!selected {
    background-color: #f5f5f5;
}

/* Table Widget */
QTableWidget {
    background-color: white;
    border: 1px solid #e0e0e0;
    border-radius: 4px;
    gridline-color: #eeeeee;
}

QTableWidget::item {
    padding: 8px;
}

QTableWidget::item:selected {
    background-color: #e3f2fd;
    color: #1976d2;
}

QHeaderView::section {
    background-color: #f5f5f5;
    color: #424242;
    padding: 10px;
    border: none;
    border-bottom: 1px solid #e0e0e0;
    font-weight: bold;
}

/* Scroll Bar */
QScrollBar:vertical {
    background: #f5f5f5;
    width: 12px;
    border-radius: 6px;
}

QScrollBar::handle:vertical {
    background: #bdbdbd;
    min-height: 30px;
    border-radius: 6px;
}

QScrollBar::handle:vertical:hover {
    background: #9e9e9e;
}

QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {
    height: 0px;
}

QScrollBar:horizontal {
    background: #f5f5f5;
    height: 12px;
    border-radius: 6px;
}

QScrollBar::handle:horizontal {
    background: #bdbdbd;
    min-width: 30px;
    border-radius: 6px;
}

/* Tooltips */
QToolTip {
    background-color: #424242;
    color: white;
    border: none;
    padding: 6px;
    border-radius: 4px;
}
"""

# Dark Theme
DARK_THEME = """
/* Global styles */
QWidget {
    background-color: #1e1e1e;
    color: #d4d4d4;
    font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, Arial, sans-serif;
    font-size: 13px;
}

/* Main Window */
QMainWindow {
    background-color: #252526;
}

/* Labels */
QLabel {
    color: #cccccc;
    padding: 2px;
}

QLabel#title {
    font-size: 18px;
    font-weight: bold;
    color: #4fc3f7;
    padding: 10px;
}

/* Buttons */
QPushButton {
    background-color: #0e639c;
    color: white;
    border: none;
    padding: 8px 16px;
    border-radius: 4px;
    min-width: 80px;
}

QPushButton:hover {
    background-color: #1177bb;
}

QPushButton:pressed {
    background-color: #0d5a8c;
}

QPushButton:disabled {
    background-color: #3c3c3c;
    color: #808080;
}

QPushButton#success {
    background-color: #388e3c;
}

QPushButton#success:hover {
    background-color: #43a047;
}

QPushButton#danger {
    background-color: #d32f2f;
}

QPushButton#danger:hover {
    background-color: #e53935;
}

/* Text inputs */
QLineEdit, QTextEdit, QPlainTextEdit {
    background-color: #3c3c3c;
    color: #d4d4d4;
    border: 1px solid #3c3c3c;
    border-radius: 4px;
    padding: 8px;
    selection-background-color: #264f78;
}

QLineEdit:focus, QTextEdit:focus, QPlainTextEdit:focus {
    border: 1px solid #0e639c;
}

QLineEdit:disabled, QTextEdit:disabled {
    background-color: #2d2d2d;
    color: #6e6e6e;
}

/* Combo Box */
QComboBox {
    background-color: #3c3c3c;
    color: #d4d4d4;
    border: 1px solid #3c3c3c;
    border-radius: 4px;
    padding: 6px 12px;
    min-width: 120px;
}

QComboBox:hover {
    border-color: #0e639c;
}

QComboBox::drop-down {
    border: none;
    width: 30px;
}

QComboBox QAbstractItemView {
    background-color: #252526;
    border: 1px solid #3c3c3c;
    selection-background-color: #0e639c;
    selection-color: white;
}

/* Spin Box */
QSpinBox, QDoubleSpinBox {
    background-color: #3c3c3c;
    color: #d4d4d4;
    border: 1px solid #3c3c3c;
    border-radius: 4px;
    padding: 6px;
}

QSpinBox:focus, QDoubleSpinBox:focus {
    border: 1px solid #0e639c;
}

/* Checkboxes and Radio Buttons */
QCheckBox, QRadioButton {
    color: #d4d4d4;
    spacing: 8px;
    padding: 4px;
}

QCheckBox::indicator, QRadioButton::indicator {
    width: 18px;
    height: 18px;
}

QCheckBox::indicator {
    border-radius: 3px;
}

QRadioButton::indicator {
    border-radius: 9px;
}

QCheckBox::indicator:unchecked, QRadioButton::indicator:unchecked {
    border: 2px solid #6e6e6e;
    background-color: #3c3c3c;
}

QCheckBox::indicator:checked {
    border: 2px solid #0e639c;
    background-color: #0e639c;
}

QRadioButton::indicator:checked {
    border: 2px solid #0e639c;
    background-color: #0e639c;
}

/* Slider */
QSlider::groove:horizontal {
    height: 6px;
    background: #3c3c3c;
    border-radius: 3px;
}

QSlider::handle:horizontal {
    background: #0e639c;
    width: 18px;
    height: 18px;
    margin: -6px 0;
    border-radius: 9px;
}

QSlider::handle:horizontal:hover {
    background: #1177bb;
}

QSlider::sub-page:horizontal {
    background: #0e639c;
    border-radius: 3px;
}

/* Progress Bar */
QProgressBar {
    background-color: #3c3c3c;
    border-radius: 4px;
    text-align: center;
    height: 20px;
    color: #d4d4d4;
}

QProgressBar::chunk {
    background-color: #0e639c;
    border-radius: 4px;
}

/* Group Box */
QGroupBox {
    font-weight: bold;
    border: 1px solid #3c3c3c;
    border-radius: 6px;
    margin-top: 12px;
    padding-top: 12px;
}

QGroupBox::title {
    subcontrol-origin: margin;
    left: 12px;
    padding: 0 6px;
    color: #4fc3f7;
}

/* Tab Widget */
QTabWidget::pane {
    border: 1px solid #3c3c3c;
    border-radius: 4px;
    padding: 8px;
    background-color: #1e1e1e;
}

QTabBar::tab {
    background-color: #2d2d2d;
    color: #808080;
    padding: 10px 20px;
    margin-right: 2px;
    border-top-left-radius: 4px;
    border-top-right-radius: 4px;
}

QTabBar::tab:selected {
    background-color: #1e1e1e;
    color: #d4d4d4;
    border-bottom: 2px solid #0e639c;
}

QTabBar::tab:hover:!selected {
    background-color: #383838;
}

/* List Widget */
QListWidget {
    background-color: #252526;
    border: 1px solid #3c3c3c;
    border-radius: 4px;
    padding: 4px;
}

QListWidget::item {
    padding: 8px;
    border-radius: 4px;
    color: #d4d4d4;
}

QListWidget::item:selected {
    background-color: #0e639c;
    color: white;
}

QListWidget::item:hover:!selected {
    background-color: #2a2d2e;
}

/* Table Widget */
QTableWidget {
    background-color: #252526;
    border: 1px solid #3c3c3c;
    border-radius: 4px;
    gridline-color: #3c3c3c;
}

QTableWidget::item {
    padding: 8px;
    color: #d4d4d4;
}

QTableWidget::item:selected {
    background-color: #0e639c;
    color: white;
}

QHeaderView::section {
    background-color: #333333;
    color: #d4d4d4;
    padding: 10px;
    border: none;
    border-bottom: 1px solid #3c3c3c;
    font-weight: bold;
}

/* Scroll Bar */
QScrollBar:vertical {
    background: #1e1e1e;
    width: 12px;
    border-radius: 6px;
}

QScrollBar::handle:vertical {
    background: #5a5a5a;
    min-height: 30px;
    border-radius: 6px;
}

QScrollBar::handle:vertical:hover {
    background: #6e6e6e;
}

QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {
    height: 0px;
}

QScrollBar:horizontal {
    background: #1e1e1e;
    height: 12px;
    border-radius: 6px;
}

QScrollBar::handle:horizontal {
    background: #5a5a5a;
    min-width: 30px;
    border-radius: 6px;
}

/* Tooltips */
QToolTip {
    background-color: #252526;
    color: #d4d4d4;
    border: 1px solid #3c3c3c;
    padding: 6px;
    border-radius: 4px;
}
"""


class StylingDemo(QMainWindow):
    """Demonstrates Qt Style Sheets."""
    
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Qt Style Sheets Demo")
        self.setMinimumSize(800, 700)
        
        self.current_theme = "light"
        
        central = QWidget()
        self.setCentralWidget(central)
        layout = QVBoxLayout(central)
        
        # Title and theme switch
        header = QHBoxLayout()
        title = QLabel("Qt Styling Demo")
        title.setObjectName("title")
        header.addWidget(title)
        header.addStretch()
        
        self.theme_btn = QPushButton("🌙 Dark Mode")
        self.theme_btn.clicked.connect(self.toggle_theme)
        header.addWidget(self.theme_btn)
        
        layout.addLayout(header)
        
        # Content in tabs
        tabs = QTabWidget()
        tabs.addTab(self.create_buttons_tab(), "Buttons")
        tabs.addTab(self.create_inputs_tab(), "Inputs")
        tabs.addTab(self.create_selections_tab(), "Selections")
        tabs.addTab(self.create_lists_tab(), "Lists & Tables")
        
        layout.addWidget(tabs)
        
        # Apply initial theme
        self.apply_theme("light")
    
    def create_buttons_tab(self):
        """Buttons showcase."""
        widget = QWidget()
        layout = QVBoxLayout(widget)
        
        group = QGroupBox("Button Styles")
        group_layout = QVBoxLayout(group)
        
        # Row 1: Normal buttons
        row1 = QHBoxLayout()
        row1.addWidget(QPushButton("Primary"))
        
        success_btn = QPushButton("Success")
        success_btn.setObjectName("success")
        row1.addWidget(success_btn)
        
        danger_btn = QPushButton("Danger")
        danger_btn.setObjectName("danger")
        row1.addWidget(danger_btn)
        
        disabled_btn = QPushButton("Disabled")
        disabled_btn.setEnabled(False)
        row1.addWidget(disabled_btn)
        
        group_layout.addLayout(row1)
        
        # Row 2: Different sizes
        row2 = QHBoxLayout()
        for text in ["Small", "Medium", "Large"]:
            btn = QPushButton(text)
            row2.addWidget(btn)
        row2.addStretch()
        group_layout.addLayout(row2)
        
        layout.addWidget(group)
        layout.addStretch()
        
        return widget
    
    def create_inputs_tab(self):
        """Input widgets showcase."""
        widget = QWidget()
        layout = QVBoxLayout(widget)
        
        group = QGroupBox("Input Widgets")
        group_layout = QVBoxLayout(group)
        
        # Line edits
        row1 = QHBoxLayout()
        le1 = QLineEdit()
        le1.setPlaceholderText("Normal input...")
        row1.addWidget(le1)
        
        le2 = QLineEdit()
        le2.setPlaceholderText("Disabled input...")
        le2.setEnabled(False)
        row1.addWidget(le2)
        group_layout.addLayout(row1)
        
        # Text edit
        te = QTextEdit()
        te.setPlaceholderText("Multi-line text input...")
        te.setMaximumHeight(100)
        group_layout.addWidget(te)
        
        # Spin boxes and combos
        row2 = QHBoxLayout()
        row2.addWidget(QLabel("SpinBox:"))
        spin = QSpinBox()
        spin.setRange(0, 100)
        row2.addWidget(spin)
        
        row2.addWidget(QLabel("ComboBox:"))
        combo = QComboBox()
        combo.addItems(["Option 1", "Option 2", "Option 3"])
        row2.addWidget(combo)
        row2.addStretch()
        group_layout.addLayout(row2)
        
        layout.addWidget(group)
        layout.addStretch()
        
        return widget
    
    def create_selections_tab(self):
        """Selection widgets showcase."""
        widget = QWidget()
        layout = QVBoxLayout(widget)
        
        # Checkboxes and radios
        check_group = QGroupBox("Checkboxes & Radio Buttons")
        check_layout = QHBoxLayout(check_group)
        
        cb_layout = QVBoxLayout()
        cb_layout.addWidget(QCheckBox("Option 1"))
        cb_layout.addWidget(QCheckBox("Option 2 (checked)"))
        cb_layout.addWidget(QCheckBox("Option 3"))
        cb_layout.itemAt(1).widget().setChecked(True)
        check_layout.addLayout(cb_layout)
        
        rb_layout = QVBoxLayout()
        rb_layout.addWidget(QRadioButton("Choice A"))
        rb_layout.addWidget(QRadioButton("Choice B (selected)"))
        rb_layout.addWidget(QRadioButton("Choice C"))
        rb_layout.itemAt(1).widget().setChecked(True)
        check_layout.addLayout(rb_layout)
        
        layout.addWidget(check_group)
        
        # Slider and progress
        slider_group = QGroupBox("Slider & Progress")
        slider_layout = QVBoxLayout(slider_group)
        
        slider = QSlider(Qt.Orientation.Horizontal)
        slider.setRange(0, 100)
        slider.setValue(60)
        slider_layout.addWidget(slider)
        
        progress = QProgressBar()
        progress.setRange(0, 100)
        progress.setValue(60)
        slider.valueChanged.connect(progress.setValue)
        slider_layout.addWidget(progress)
        
        layout.addWidget(slider_group)
        layout.addStretch()
        
        return widget
    
    def create_lists_tab(self):
        """Lists and tables showcase."""
        widget = QWidget()
        layout = QHBoxLayout(widget)
        
        # List widget
        list_group = QGroupBox("List Widget")
        list_layout = QVBoxLayout(list_group)
        
        list_widget = QListWidget()
        for i in range(10):
            list_widget.addItem(f"List Item {i + 1}")
        list_layout.addWidget(list_widget)
        layout.addWidget(list_group)
        
        # Table widget
        table_group = QGroupBox("Table Widget")
        table_layout = QVBoxLayout(table_group)
        
        table = QTableWidget(5, 3)
        table.setHorizontalHeaderLabels(["Name", "Age", "City"])
        
        data = [
            ("Alice", "28", "New York"),
            ("Bob", "35", "Los Angeles"),
            ("Carol", "42", "Chicago"),
            ("David", "31", "Houston"),
            ("Eva", "26", "Phoenix"),
        ]
        
        for row, (name, age, city) in enumerate(data):
            table.setItem(row, 0, QTableWidgetItem(name))
            table.setItem(row, 1, QTableWidgetItem(age))
            table.setItem(row, 2, QTableWidgetItem(city))
        
        table_layout.addWidget(table)
        layout.addWidget(table_group)
        
        return widget
    
    def toggle_theme(self):
        """Switch between light and dark theme."""
        if self.current_theme == "light":
            self.apply_theme("dark")
        else:
            self.apply_theme("light")
    
    def apply_theme(self, theme):
        """Apply the specified theme."""
        self.current_theme = theme
        
        if theme == "dark":
            QApplication.instance().setStyleSheet(DARK_THEME)
            self.theme_btn.setText("☀️ Light Mode")
        else:
            QApplication.instance().setStyleSheet(LIGHT_THEME)
            self.theme_btn.setText("🌙 Dark Mode")


def main():
    app = QApplication(sys.argv)
    app.setStyleSheet(LIGHT_THEME)
    window = StylingDemo()
    window.show()
    sys.exit(app.exec())


if __name__ == "__main__":
    main()
