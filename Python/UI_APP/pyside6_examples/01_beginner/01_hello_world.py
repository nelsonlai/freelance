"""
PySide6 Beginner Example 01: Hello World
=========================================

This example demonstrates:
- Creating a basic PySide6 application
- Creating a main window
- Adding a simple label widget
- Running the application event loop

Run: python 01_hello_world.py
"""

import sys
from PySide6.QtWidgets import QApplication, QMainWindow, QLabel
from PySide6.QtCore import Qt


class MainWindow(QMainWindow):
    """Main application window."""
    
    def __init__(self):
        super().__init__()
        
        # Set window properties
        self.setWindowTitle("Hello PySide6!")
        self.setGeometry(100, 100, 400, 300)
        
        # Create a label widget
        label = QLabel("Hello, World!")
        label.setAlignment(Qt.AlignmentFlag.AlignCenter)
        
        # Set the label as the central widget
        self.setCentralWidget(label)
        
        # Apply some basic styling
        label.setStyleSheet("""
            QLabel {
                font-size: 24px;
                font-weight: bold;
                color: #2c3e50;
            }
        """)


def main():
    """Main entry point."""
    # Create the application instance
    # QApplication manages application-wide resources
    app = QApplication(sys.argv)
    
    # Create and show the main window
    window = MainWindow()
    window.show()
    
    # Start the event loop
    # exec() blocks until the application exits
    sys.exit(app.exec())


if __name__ == "__main__":
    main()
