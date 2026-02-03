"""
PyQt6 Intermediate Example 04: Styling with Qt Style Sheets
============================================================

This example demonstrates:
- Qt Style Sheets (QSS) for PyQt6
- Dark and light theme switching

Run: python 04_styling.py
"""

import sys
from PyQt6.QtWidgets import (
    QApplication, QMainWindow, QWidget, QVBoxLayout, QHBoxLayout,
    QLabel, QPushButton, QLineEdit, QTextEdit, QCheckBox,
    QComboBox, QSlider, QProgressBar, QGroupBox, QTabWidget
)
from PyQt6.QtCore import Qt


LIGHT_THEME = """
QWidget {
    background-color: #f5f5f5;
    color: #212121;
    font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, Arial, sans-serif;
    font-size: 13px;
}

QPushButton {
    background-color: #1976d2;
    color: white;
    border: none;
    padding: 8px 16px;
    border-radius: 4px;
}

QPushButton:hover {
    background-color: #1e88e5;
}

QLineEdit, QTextEdit {
    background-color: white;
    border: 1px solid #bdbdbd;
    border-radius: 4px;
    padding: 8px;
}

QLineEdit:focus, QTextEdit:focus {
    border: 2px solid #1976d2;
}

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
    color: #1976d2;
}
"""

DARK_THEME = """
QWidget {
    background-color: #1e1e1e;
    color: #d4d4d4;
    font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, Arial, sans-serif;
    font-size: 13px;
}

QPushButton {
    background-color: #0e639c;
    color: white;
    border: none;
    padding: 8px 16px;
    border-radius: 4px;
}

QPushButton:hover {
    background-color: #1177bb;
}

QLineEdit, QTextEdit {
    background-color: #3c3c3c;
    color: #d4d4d4;
    border: 1px solid #3c3c3c;
    border-radius: 4px;
    padding: 8px;
}

QLineEdit:focus, QTextEdit:focus {
    border: 1px solid #0e639c;
}

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
    color: #4fc3f7;
}
"""


class StylingDemo(QMainWindow):
    """Demonstrates Qt Style Sheets."""
    
    def __init__(self):
        super().__init__()
        self.setWindowTitle("PyQt6 Styling Demo")
        self.setMinimumSize(600, 500)
        
        self.current_theme = "light"
        
        central = QWidget()
        self.setCentralWidget(central)
        layout = QVBoxLayout(central)
        
        # Header
        header = QHBoxLayout()
        title = QLabel("Qt Styling Demo")
        title.setStyleSheet("font-size: 18px; font-weight: bold;")
        header.addWidget(title)
        header.addStretch()
        
        self.theme_btn = QPushButton("🌙 Dark Mode")
        self.theme_btn.clicked.connect(self.toggle_theme)
        header.addWidget(self.theme_btn)
        
        layout.addLayout(header)
        
        # Widgets
        group = QGroupBox("Sample Widgets")
        group_layout = QVBoxLayout(group)
        
        # Inputs
        row1 = QHBoxLayout()
        row1.addWidget(QLineEdit())
        row1.addWidget(QComboBox())
        group_layout.addLayout(row1)
        
        # Checkbox
        group_layout.addWidget(QCheckBox("Enable feature"))
        
        # Slider and progress
        slider = QSlider(Qt.Orientation.Horizontal)
        slider.setRange(0, 100)
        slider.setValue(60)
        group_layout.addWidget(slider)
        
        progress = QProgressBar()
        progress.setValue(60)
        slider.valueChanged.connect(progress.setValue)
        group_layout.addWidget(progress)
        
        # Buttons
        btn_layout = QHBoxLayout()
        btn_layout.addWidget(QPushButton("Button 1"))
        btn_layout.addWidget(QPushButton("Button 2"))
        btn_layout.addStretch()
        group_layout.addLayout(btn_layout)
        
        layout.addWidget(group)
        layout.addStretch()
        
        self.apply_theme("light")
    
    def toggle_theme(self):
        if self.current_theme == "light":
            self.apply_theme("dark")
        else:
            self.apply_theme("light")
    
    def apply_theme(self, theme):
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
