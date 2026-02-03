"""
PySide6 Beginner Example 02: Basic Widgets
==========================================

This example demonstrates:
- Various common Qt widgets
- Getting and setting widget values
- Basic widget interaction

Run: python 02_widgets_basic.py
"""

import sys
from PySide6.QtWidgets import (
    QApplication, QMainWindow, QWidget, QVBoxLayout, QHBoxLayout,
    QLabel, QPushButton, QLineEdit, QTextEdit, QCheckBox,
    QRadioButton, QComboBox, QSpinBox, QDoubleSpinBox, QSlider,
    QProgressBar, QGroupBox, QButtonGroup
)
from PySide6.QtCore import Qt


class WidgetShowcase(QMainWindow):
    """Demonstrates various Qt widgets."""
    
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Widget Showcase")
        self.setMinimumSize(600, 700)
        
        # Central widget and main layout
        central = QWidget()
        self.setCentralWidget(central)
        layout = QVBoxLayout(central)
        
        # Add widget groups
        layout.addWidget(self.create_input_group())
        layout.addWidget(self.create_selection_group())
        layout.addWidget(self.create_number_group())
        layout.addWidget(self.create_button_group())
        
        # Add stretch to push widgets to top
        layout.addStretch()
    
    def create_input_group(self):
        """Create text input widgets group."""
        group = QGroupBox("Text Input Widgets")
        layout = QVBoxLayout(group)
        
        # QLineEdit - single line text
        line_layout = QHBoxLayout()
        line_layout.addWidget(QLabel("Name:"))
        self.name_input = QLineEdit()
        self.name_input.setPlaceholderText("Enter your name...")
        self.name_input.textChanged.connect(self.on_name_changed)
        line_layout.addWidget(self.name_input)
        layout.addLayout(line_layout)
        
        # QLineEdit - password
        pass_layout = QHBoxLayout()
        pass_layout.addWidget(QLabel("Password:"))
        self.pass_input = QLineEdit()
        self.pass_input.setEchoMode(QLineEdit.EchoMode.Password)
        self.pass_input.setPlaceholderText("Enter password...")
        pass_layout.addWidget(self.pass_input)
        layout.addLayout(pass_layout)
        
        # QTextEdit - multi-line text
        layout.addWidget(QLabel("Bio:"))
        self.bio_input = QTextEdit()
        self.bio_input.setPlaceholderText("Tell us about yourself...")
        self.bio_input.setMaximumHeight(80)
        layout.addWidget(self.bio_input)
        
        return group
    
    def create_selection_group(self):
        """Create selection widgets group."""
        group = QGroupBox("Selection Widgets")
        layout = QVBoxLayout(group)
        
        # QCheckBox
        check_layout = QHBoxLayout()
        self.newsletter_check = QCheckBox("Subscribe to newsletter")
        self.terms_check = QCheckBox("Accept terms and conditions")
        check_layout.addWidget(self.newsletter_check)
        check_layout.addWidget(self.terms_check)
        check_layout.addStretch()
        layout.addLayout(check_layout)
        
        # QRadioButton
        radio_layout = QHBoxLayout()
        radio_layout.addWidget(QLabel("Gender:"))
        
        self.gender_group = QButtonGroup(self)
        self.male_radio = QRadioButton("Male")
        self.female_radio = QRadioButton("Female")
        self.other_radio = QRadioButton("Other")
        
        self.gender_group.addButton(self.male_radio, 1)
        self.gender_group.addButton(self.female_radio, 2)
        self.gender_group.addButton(self.other_radio, 3)
        
        radio_layout.addWidget(self.male_radio)
        radio_layout.addWidget(self.female_radio)
        radio_layout.addWidget(self.other_radio)
        radio_layout.addStretch()
        layout.addLayout(radio_layout)
        
        # QComboBox
        combo_layout = QHBoxLayout()
        combo_layout.addWidget(QLabel("Country:"))
        self.country_combo = QComboBox()
        self.country_combo.addItems([
            "Select...", "United States", "United Kingdom", 
            "Canada", "Australia", "Germany", "France", "Japan"
        ])
        self.country_combo.currentTextChanged.connect(self.on_country_changed)
        combo_layout.addWidget(self.country_combo)
        combo_layout.addStretch()
        layout.addLayout(combo_layout)
        
        return group
    
    def create_number_group(self):
        """Create number input widgets group."""
        group = QGroupBox("Number Widgets")
        layout = QVBoxLayout(group)
        
        # QSpinBox
        spin_layout = QHBoxLayout()
        spin_layout.addWidget(QLabel("Age:"))
        self.age_spin = QSpinBox()
        self.age_spin.setRange(0, 150)
        self.age_spin.setValue(25)
        self.age_spin.setSuffix(" years")
        spin_layout.addWidget(self.age_spin)
        spin_layout.addStretch()
        layout.addLayout(spin_layout)
        
        # QDoubleSpinBox
        double_layout = QHBoxLayout()
        double_layout.addWidget(QLabel("Height:"))
        self.height_spin = QDoubleSpinBox()
        self.height_spin.setRange(0.0, 3.0)
        self.height_spin.setValue(1.75)
        self.height_spin.setDecimals(2)
        self.height_spin.setSingleStep(0.01)
        self.height_spin.setSuffix(" m")
        double_layout.addWidget(self.height_spin)
        double_layout.addStretch()
        layout.addLayout(double_layout)
        
        # QSlider with QProgressBar
        slider_layout = QHBoxLayout()
        slider_layout.addWidget(QLabel("Satisfaction:"))
        self.satisfaction_slider = QSlider(Qt.Orientation.Horizontal)
        self.satisfaction_slider.setRange(0, 100)
        self.satisfaction_slider.setValue(75)
        self.satisfaction_slider.valueChanged.connect(self.on_slider_changed)
        slider_layout.addWidget(self.satisfaction_slider)
        
        self.satisfaction_progress = QProgressBar()
        self.satisfaction_progress.setRange(0, 100)
        self.satisfaction_progress.setValue(75)
        self.satisfaction_progress.setMaximumWidth(100)
        slider_layout.addWidget(self.satisfaction_progress)
        layout.addLayout(slider_layout)
        
        return group
    
    def create_button_group(self):
        """Create button widgets group."""
        group = QGroupBox("Actions")
        layout = QHBoxLayout(group)
        
        submit_btn = QPushButton("Submit")
        submit_btn.clicked.connect(self.on_submit)
        
        clear_btn = QPushButton("Clear")
        clear_btn.clicked.connect(self.on_clear)
        
        layout.addStretch()
        layout.addWidget(clear_btn)
        layout.addWidget(submit_btn)
        
        return group
    
    # Event handlers
    def on_name_changed(self, text):
        """Called when name input changes."""
        print(f"Name changed to: {text}")
    
    def on_country_changed(self, text):
        """Called when country selection changes."""
        if text != "Select...":
            print(f"Country selected: {text}")
    
    def on_slider_changed(self, value):
        """Called when slider value changes."""
        self.satisfaction_progress.setValue(value)
    
    def on_submit(self):
        """Called when submit button is clicked."""
        # Gather all widget values
        data = {
            "name": self.name_input.text(),
            "bio": self.bio_input.toPlainText(),
            "newsletter": self.newsletter_check.isChecked(),
            "terms": self.terms_check.isChecked(),
            "country": self.country_combo.currentText(),
            "age": self.age_spin.value(),
            "height": self.height_spin.value(),
            "satisfaction": self.satisfaction_slider.value(),
        }
        
        # Get selected gender
        gender_btn = self.gender_group.checkedButton()
        data["gender"] = gender_btn.text() if gender_btn else "Not selected"
        
        print("\n=== Form Data ===")
        for key, value in data.items():
            print(f"  {key}: {value}")
        print("=================\n")
    
    def on_clear(self):
        """Clear all form fields."""
        self.name_input.clear()
        self.pass_input.clear()
        self.bio_input.clear()
        self.newsletter_check.setChecked(False)
        self.terms_check.setChecked(False)
        self.gender_group.setExclusive(False)
        for btn in self.gender_group.buttons():
            btn.setChecked(False)
        self.gender_group.setExclusive(True)
        self.country_combo.setCurrentIndex(0)
        self.age_spin.setValue(25)
        self.height_spin.setValue(1.75)
        self.satisfaction_slider.setValue(50)


def main():
    app = QApplication(sys.argv)
    window = WidgetShowcase()
    window.show()
    sys.exit(app.exec())


if __name__ == "__main__":
    main()
