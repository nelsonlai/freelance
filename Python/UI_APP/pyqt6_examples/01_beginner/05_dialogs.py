"""
PyQt6 Beginner Example 05: Dialog Boxes
=======================================

This example demonstrates:
- QMessageBox (info, warning, error, question)
- QInputDialog (text, int, item selection)
- QFileDialog (open, save, directory)
- QColorDialog and QFontDialog
- Custom dialogs

Run: python 05_dialogs.py
"""

import sys
from PyQt6.QtWidgets import (
    QApplication, QMainWindow, QWidget, QVBoxLayout, QHBoxLayout,
    QLabel, QPushButton, QGroupBox, QMessageBox, QInputDialog,
    QFileDialog, QColorDialog, QFontDialog, QDialog, QFormLayout,
    QLineEdit, QSpinBox, QDialogButtonBox, QTextEdit
)
from PyQt6.QtCore import Qt
from PyQt6.QtGui import QFont, QColor


class CustomUserDialog(QDialog):
    """A custom dialog for user input."""
    
    def __init__(self, parent=None):
        super().__init__(parent)
        self.setWindowTitle("User Information")
        self.setModal(True)
        self.setMinimumWidth(350)
        
        layout = QVBoxLayout(self)
        
        form = QFormLayout()
        
        self.name_input = QLineEdit()
        form.addRow("Name:", self.name_input)
        
        self.email_input = QLineEdit()
        form.addRow("Email:", self.email_input)
        
        self.age_input = QSpinBox()
        self.age_input.setRange(1, 150)
        form.addRow("Age:", self.age_input)
        
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
            "email": self.email_input.text(),
            "age": self.age_input.value()
        }


class DialogsDemo(QMainWindow):
    """Demonstrates various dialog types."""
    
    def __init__(self):
        super().__init__()
        self.setWindowTitle("PyQt6 Dialogs Demo")
        self.setMinimumSize(600, 600)
        
        central = QWidget()
        self.setCentralWidget(central)
        layout = QVBoxLayout(central)
        
        layout.addWidget(self.create_message_box_group())
        layout.addWidget(self.create_input_dialog_group())
        layout.addWidget(self.create_file_dialog_group())
        layout.addWidget(self.create_other_dialogs_group())
        layout.addWidget(self.create_result_group())
        
        layout.addStretch()
    
    def create_message_box_group(self):
        group = QGroupBox("Message Boxes")
        layout = QHBoxLayout(group)
        
        info_btn = QPushButton("ℹ️ Information")
        info_btn.clicked.connect(self.show_info)
        layout.addWidget(info_btn)
        
        warn_btn = QPushButton("⚠️ Warning")
        warn_btn.clicked.connect(self.show_warning)
        layout.addWidget(warn_btn)
        
        error_btn = QPushButton("❌ Error")
        error_btn.clicked.connect(self.show_error)
        layout.addWidget(error_btn)
        
        question_btn = QPushButton("❓ Question")
        question_btn.clicked.connect(self.show_question)
        layout.addWidget(question_btn)
        
        return group
    
    def create_input_dialog_group(self):
        group = QGroupBox("Input Dialogs")
        layout = QHBoxLayout(group)
        
        text_btn = QPushButton("📝 Get Text")
        text_btn.clicked.connect(self.get_text_input)
        layout.addWidget(text_btn)
        
        int_btn = QPushButton("🔢 Get Integer")
        int_btn.clicked.connect(self.get_int_input)
        layout.addWidget(int_btn)
        
        item_btn = QPushButton("📋 Select Item")
        item_btn.clicked.connect(self.get_item_input)
        layout.addWidget(item_btn)
        
        custom_btn = QPushButton("👤 Custom Dialog")
        custom_btn.clicked.connect(self.show_custom_dialog)
        layout.addWidget(custom_btn)
        
        return group
    
    def create_file_dialog_group(self):
        group = QGroupBox("File Dialogs")
        layout = QHBoxLayout(group)
        
        open_btn = QPushButton("📂 Open File")
        open_btn.clicked.connect(self.open_file)
        layout.addWidget(open_btn)
        
        save_btn = QPushButton("💾 Save File")
        save_btn.clicked.connect(self.save_file)
        layout.addWidget(save_btn)
        
        dir_btn = QPushButton("📁 Select Directory")
        dir_btn.clicked.connect(self.select_directory)
        layout.addWidget(dir_btn)
        
        return group
    
    def create_other_dialogs_group(self):
        group = QGroupBox("Other Dialogs")
        layout = QHBoxLayout(group)
        
        color_btn = QPushButton("🎨 Color Picker")
        color_btn.clicked.connect(self.pick_color)
        layout.addWidget(color_btn)
        
        font_btn = QPushButton("🔤 Font Picker")
        font_btn.clicked.connect(self.pick_font)
        layout.addWidget(font_btn)
        
        return group
    
    def create_result_group(self):
        group = QGroupBox("Results")
        layout = QVBoxLayout(group)
        
        self.result_display = QTextEdit()
        self.result_display.setReadOnly(True)
        self.result_display.setMaximumHeight(150)
        layout.addWidget(self.result_display)
        
        return group
    
    def log_result(self, message):
        self.result_display.append(message)
    
    def show_info(self):
        QMessageBox.information(self, "Information", "This is an info message.")
        self.log_result("ℹ️ Information dialog shown")
    
    def show_warning(self):
        QMessageBox.warning(self, "Warning", "This is a warning message.")
        self.log_result("⚠️ Warning dialog shown")
    
    def show_error(self):
        QMessageBox.critical(self, "Error", "This is an error message.")
        self.log_result("❌ Error dialog shown")
    
    def show_question(self):
        result = QMessageBox.question(
            self, "Confirm",
            "Do you want to proceed?",
            QMessageBox.StandardButton.Yes | QMessageBox.StandardButton.No
        )
        
        if result == QMessageBox.StandardButton.Yes:
            self.log_result("❓ User clicked: Yes")
        else:
            self.log_result("❓ User clicked: No")
    
    def get_text_input(self):
        text, ok = QInputDialog.getText(self, "Input", "Enter your name:")
        if ok and text:
            self.log_result(f"📝 Text entered: '{text}'")
    
    def get_int_input(self):
        value, ok = QInputDialog.getInt(self, "Input", "Enter your age:", 25, 1, 150)
        if ok:
            self.log_result(f"🔢 Integer entered: {value}")
    
    def get_item_input(self):
        items = ["Python", "JavaScript", "Java", "C++", "Go"]
        item, ok = QInputDialog.getItem(self, "Select", "Favorite language:", items)
        if ok and item:
            self.log_result(f"📋 Item selected: '{item}'")
    
    def show_custom_dialog(self):
        dialog = CustomUserDialog(self)
        if dialog.exec() == QDialog.DialogCode.Accepted:
            data = dialog.get_data()
            self.log_result(f"👤 User: {data['name']}, {data['email']}, Age: {data['age']}")
    
    def open_file(self):
        path, _ = QFileDialog.getOpenFileName(
            self, "Open File", "",
            "Text Files (*.txt);;All Files (*)"
        )
        if path:
            self.log_result(f"📂 File: {path}")
    
    def save_file(self):
        path, _ = QFileDialog.getSaveFileName(
            self, "Save File", "",
            "Text Files (*.txt);;All Files (*)"
        )
        if path:
            self.log_result(f"💾 Save to: {path}")
    
    def select_directory(self):
        directory = QFileDialog.getExistingDirectory(self, "Select Directory")
        if directory:
            self.log_result(f"📁 Directory: {directory}")
    
    def pick_color(self):
        color = QColorDialog.getColor()
        if color.isValid():
            self.log_result(f"🎨 Color: {color.name()}")
    
    def pick_font(self):
        font, ok = QFontDialog.getFont()
        if ok:
            self.log_result(f"🔤 Font: {font.family()}, {font.pointSize()}pt")


def main():
    app = QApplication(sys.argv)
    window = DialogsDemo()
    window.show()
    sys.exit(app.exec())


if __name__ == "__main__":
    main()
