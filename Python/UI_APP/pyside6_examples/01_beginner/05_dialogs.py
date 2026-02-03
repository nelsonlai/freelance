"""
PySide6 Beginner Example 05: Dialog Boxes
=========================================

This example demonstrates:
- QMessageBox (info, warning, error, question)
- QInputDialog (text, int, item selection)
- QFileDialog (open, save, directory)
- QColorDialog and QFontDialog
- Custom dialogs

Run: python 05_dialogs.py
"""

import sys
from PySide6.QtWidgets import (
    QApplication, QMainWindow, QWidget, QVBoxLayout, QHBoxLayout,
    QLabel, QPushButton, QGroupBox, QMessageBox, QInputDialog,
    QFileDialog, QColorDialog, QFontDialog, QDialog, QFormLayout,
    QLineEdit, QSpinBox, QDialogButtonBox, QTextEdit
)
from PySide6.QtCore import Qt
from PySide6.QtGui import QFont, QColor


class CustomUserDialog(QDialog):
    """A custom dialog for user input."""
    
    def __init__(self, parent=None):
        super().__init__(parent)
        self.setWindowTitle("User Information")
        self.setModal(True)
        self.setMinimumWidth(350)
        
        layout = QVBoxLayout(self)
        
        # Form
        form = QFormLayout()
        
        self.name_input = QLineEdit()
        self.name_input.setPlaceholderText("Enter full name")
        form.addRow("Name:", self.name_input)
        
        self.email_input = QLineEdit()
        self.email_input.setPlaceholderText("user@example.com")
        form.addRow("Email:", self.email_input)
        
        self.age_input = QSpinBox()
        self.age_input.setRange(1, 150)
        self.age_input.setValue(25)
        form.addRow("Age:", self.age_input)
        
        layout.addLayout(form)
        
        # Buttons
        button_box = QDialogButtonBox(
            QDialogButtonBox.StandardButton.Ok |
            QDialogButtonBox.StandardButton.Cancel
        )
        button_box.accepted.connect(self.validate_and_accept)
        button_box.rejected.connect(self.reject)
        layout.addWidget(button_box)
    
    def validate_and_accept(self):
        """Validate input before accepting."""
        if not self.name_input.text().strip():
            QMessageBox.warning(self, "Validation Error", "Name is required!")
            self.name_input.setFocus()
            return
        
        if not self.email_input.text().strip():
            QMessageBox.warning(self, "Validation Error", "Email is required!")
            self.email_input.setFocus()
            return
        
        self.accept()
    
    def get_data(self):
        """Return the entered data."""
        return {
            "name": self.name_input.text(),
            "email": self.email_input.text(),
            "age": self.age_input.value()
        }


class DialogsDemo(QMainWindow):
    """Demonstrates various dialog types."""
    
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Dialogs Demo")
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
        """Message box buttons."""
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
        """Input dialog buttons."""
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
        """File dialog buttons."""
        group = QGroupBox("File Dialogs")
        layout = QHBoxLayout(group)
        
        open_btn = QPushButton("📂 Open File")
        open_btn.clicked.connect(self.open_file)
        layout.addWidget(open_btn)
        
        open_multi_btn = QPushButton("📂 Open Multiple")
        open_multi_btn.clicked.connect(self.open_files)
        layout.addWidget(open_multi_btn)
        
        save_btn = QPushButton("💾 Save File")
        save_btn.clicked.connect(self.save_file)
        layout.addWidget(save_btn)
        
        dir_btn = QPushButton("📁 Select Directory")
        dir_btn.clicked.connect(self.select_directory)
        layout.addWidget(dir_btn)
        
        return group
    
    def create_other_dialogs_group(self):
        """Other dialog types."""
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
        """Display results."""
        group = QGroupBox("Results")
        layout = QVBoxLayout(group)
        
        self.result_display = QTextEdit()
        self.result_display.setReadOnly(True)
        self.result_display.setMaximumHeight(150)
        layout.addWidget(self.result_display)
        
        clear_btn = QPushButton("Clear")
        clear_btn.clicked.connect(self.result_display.clear)
        layout.addWidget(clear_btn)
        
        return group
    
    def log_result(self, message):
        """Log a result message."""
        self.result_display.append(message)
    
    # Message Box Methods
    def show_info(self):
        """Show information dialog."""
        QMessageBox.information(
            self,
            "Information",
            "This is an informational message.\n\n"
            "Use this for general notifications."
        )
        self.log_result("ℹ️ Information dialog shown")
    
    def show_warning(self):
        """Show warning dialog."""
        QMessageBox.warning(
            self,
            "Warning",
            "This is a warning message.\n\n"
            "Use this to alert users about potential issues."
        )
        self.log_result("⚠️ Warning dialog shown")
    
    def show_error(self):
        """Show error dialog."""
        QMessageBox.critical(
            self,
            "Error",
            "This is an error message.\n\n"
            "Use this for serious problems or failures."
        )
        self.log_result("❌ Error dialog shown")
    
    def show_question(self):
        """Show question dialog."""
        result = QMessageBox.question(
            self,
            "Confirm Action",
            "Do you want to proceed with this action?\n\n"
            "This cannot be undone.",
            QMessageBox.StandardButton.Yes |
            QMessageBox.StandardButton.No |
            QMessageBox.StandardButton.Cancel,
            QMessageBox.StandardButton.No  # Default button
        )
        
        if result == QMessageBox.StandardButton.Yes:
            self.log_result("❓ User clicked: Yes")
        elif result == QMessageBox.StandardButton.No:
            self.log_result("❓ User clicked: No")
        else:
            self.log_result("❓ User clicked: Cancel")
    
    # Input Dialog Methods
    def get_text_input(self):
        """Get text from user."""
        text, ok = QInputDialog.getText(
            self,
            "Text Input",
            "Please enter your name:",
            QLineEdit.EchoMode.Normal,
            "John Doe"  # Default value
        )
        
        if ok and text:
            self.log_result(f"📝 Text entered: '{text}'")
        else:
            self.log_result("📝 Text input cancelled")
    
    def get_int_input(self):
        """Get integer from user."""
        value, ok = QInputDialog.getInt(
            self,
            "Integer Input",
            "Enter your age:",
            25,  # Default value
            1,   # Minimum
            150, # Maximum
            1    # Step
        )
        
        if ok:
            self.log_result(f"🔢 Integer entered: {value}")
        else:
            self.log_result("🔢 Integer input cancelled")
    
    def get_item_input(self):
        """Get item selection from user."""
        items = ["Python", "JavaScript", "Java", "C++", "Go", "Rust", "TypeScript"]
        
        item, ok = QInputDialog.getItem(
            self,
            "Select Item",
            "Choose your favorite programming language:",
            items,
            0,     # Current index
            False  # Editable
        )
        
        if ok and item:
            self.log_result(f"📋 Item selected: '{item}'")
        else:
            self.log_result("📋 Item selection cancelled")
    
    def show_custom_dialog(self):
        """Show custom dialog."""
        dialog = CustomUserDialog(self)
        
        if dialog.exec() == QDialog.DialogCode.Accepted:
            data = dialog.get_data()
            self.log_result(
                f"👤 User data: Name='{data['name']}', "
                f"Email='{data['email']}', Age={data['age']}"
            )
        else:
            self.log_result("👤 Custom dialog cancelled")
    
    # File Dialog Methods
    def open_file(self):
        """Open single file."""
        file_path, _ = QFileDialog.getOpenFileName(
            self,
            "Open File",
            "",
            "Text Files (*.txt);;Python Files (*.py);;All Files (*)"
        )
        
        if file_path:
            self.log_result(f"📂 File selected: {file_path}")
        else:
            self.log_result("📂 File selection cancelled")
    
    def open_files(self):
        """Open multiple files."""
        file_paths, _ = QFileDialog.getOpenFileNames(
            self,
            "Open Files",
            "",
            "Images (*.png *.jpg *.jpeg *.gif);;All Files (*)"
        )
        
        if file_paths:
            self.log_result(f"📂 {len(file_paths)} files selected:")
            for path in file_paths[:5]:  # Show first 5
                self.log_result(f"   - {path}")
            if len(file_paths) > 5:
                self.log_result(f"   ... and {len(file_paths) - 5} more")
        else:
            self.log_result("📂 File selection cancelled")
    
    def save_file(self):
        """Save file dialog."""
        file_path, _ = QFileDialog.getSaveFileName(
            self,
            "Save File",
            "untitled.txt",
            "Text Files (*.txt);;All Files (*)"
        )
        
        if file_path:
            self.log_result(f"💾 Save path: {file_path}")
        else:
            self.log_result("💾 Save cancelled")
    
    def select_directory(self):
        """Select directory."""
        directory = QFileDialog.getExistingDirectory(
            self,
            "Select Directory",
            "",
            QFileDialog.Option.ShowDirsOnly
        )
        
        if directory:
            self.log_result(f"📁 Directory selected: {directory}")
        else:
            self.log_result("📁 Directory selection cancelled")
    
    # Other Dialogs
    def pick_color(self):
        """Color picker dialog."""
        color = QColorDialog.getColor(
            QColor(255, 0, 0),  # Initial color (red)
            self,
            "Select Color"
        )
        
        if color.isValid():
            self.log_result(
                f"🎨 Color selected: {color.name()} "
                f"(RGB: {color.red()}, {color.green()}, {color.blue()})"
            )
            # Apply color to result display
            self.result_display.setStyleSheet(
                f"background-color: {color.name()}; color: {'white' if color.lightness() < 128 else 'black'};"
            )
        else:
            self.log_result("🎨 Color selection cancelled")
    
    def pick_font(self):
        """Font picker dialog."""
        # PySide6 returns (ok, font) - note the order!
        ok, font = QFontDialog.getFont(
            QFont("Arial", 12),  # Initial font
            self,
            "Select Font"
        )
        
        if ok and font:
            self.log_result(
                f"🔤 Font selected: {font.family()}, "
                f"{font.pointSize()}pt, "
                f"{'Bold' if font.bold() else 'Normal'}, "
                f"{'Italic' if font.italic() else 'Regular'}"
            )
            # Apply font to result display
            self.result_display.setFont(font)
        else:
            self.log_result("🔤 Font selection cancelled")


def main():
    app = QApplication(sys.argv)
    window = DialogsDemo()
    window.show()
    sys.exit(app.exec())


if __name__ == "__main__":
    main()
