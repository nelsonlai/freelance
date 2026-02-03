# PySide6 Complete Tutorial
## From Beginner to Advanced

---

# Table of Contents

## Part 1: Beginner Level
1. [Introduction to PySide6](#1-introduction-to-pyside6)
2. [Your First Application](#2-your-first-application)
3. [Understanding Qt Widgets](#3-understanding-qt-widgets)
4. [Layout Management](#4-layout-management)
5. [Signals and Slots](#5-signals-and-slots)
6. [Dialog Boxes](#6-dialog-boxes)
7. [Basic Event Handling](#7-basic-event-handling)

## Part 2: Intermediate Level
8. [Custom Widgets](#8-custom-widgets)
9. [Model-View Programming](#9-model-view-programming)
10. [Multithreading with QThread](#10-multithreading-with-qthread)
11. [Styling with Qt Style Sheets](#11-styling-with-qt-style-sheets)
12. [Menus, Toolbars, and Status Bars](#12-menus-toolbars-and-status-bars)
13. [Working with Files](#13-working-with-files)
14. [Settings and Preferences](#14-settings-and-preferences)

## Part 3: Advanced Level
15. [Graphics View Framework](#15-graphics-view-framework)
16. [Animations and State Machines](#16-animations-and-state-machines)
17. [QML and Qt Quick Integration](#17-qml-and-qt-quick-integration)
18. [Database Connectivity](#18-database-connectivity)
19. [Networking](#19-networking)
20. [Multimedia](#20-multimedia)
21. [Packaging and Deployment](#21-packaging-and-deployment)

---

# Part 1: Beginner Level

---

## 1. Introduction to PySide6

### What is PySide6?

PySide6 is the official Python binding for Qt 6, developed by The Qt Company. It provides access to the complete Qt 6 framework, enabling you to create professional-grade desktop applications.

### Key Features

- **Cross-platform**: Works on Windows, macOS, and Linux
- **Rich widget library**: Hundreds of ready-to-use UI components
- **Signal/Slot mechanism**: Powerful event-driven programming
- **Graphics capabilities**: 2D and 3D graphics support
- **Database integration**: Built-in SQL support
- **Networking**: HTTP, TCP, UDP, WebSocket support
- **Multimedia**: Audio, video, and camera access

### Qt Architecture Overview

```
┌─────────────────────────────────────────────────────────────┐
│                    Your Python Application                   │
├─────────────────────────────────────────────────────────────┤
│                         PySide6                              │
├───────────┬───────────┬───────────┬───────────┬─────────────┤
│ QtWidgets │  QtCore   │   QtGui   │  QtQuick  │   QtSql     │
├───────────┴───────────┴───────────┴───────────┴─────────────┤
│                      Qt Framework (C++)                      │
├─────────────────────────────────────────────────────────────┤
│            Operating System (Windows/macOS/Linux)            │
└─────────────────────────────────────────────────────────────┘
```

### Main Modules

| Module | Description |
|--------|-------------|
| `QtCore` | Core non-GUI functionality (signals, slots, event loop) |
| `QtWidgets` | Classic desktop widgets (buttons, labels, tables) |
| `QtGui` | GUI primitives (fonts, colors, images) |
| `QtQuick` | QML declarative UI framework |
| `QtQml` | QML engine |
| `QtSql` | Database connectivity |
| `QtNetwork` | Networking classes |
| `QtMultimedia` | Audio and video |
| `QtCharts` | Charts and graphs |
| `QtWebEngine` | Web browser engine |

### Installation

```bash
pip install PySide6
```

This installs:
- `PySide6_Essentials`: Core modules
- `PySide6_Addons`: Additional modules (Charts, 3D, etc.)

---

## 2. Your First Application

### The Minimal Application

Every PySide6 application needs:
1. A `QApplication` instance (exactly one per application)
2. At least one widget to display

```python
import sys
from PySide6.QtWidgets import QApplication, QLabel

# Create the application instance
app = QApplication(sys.argv)

# Create a simple label widget
label = QLabel("Hello, PySide6!")
label.show()

# Start the event loop
sys.exit(app.exec())
```

### Understanding the Code

1. **`QApplication`**: Manages application-wide resources and settings
2. **`sys.argv`**: Command-line arguments passed to the application
3. **`QLabel`**: A widget that displays text or images
4. **`.show()`**: Makes the widget visible
5. **`.exec()`**: Starts the event loop (blocks until application quits)
6. **`sys.exit()`**: Ensures proper cleanup on exit

### Creating a Main Window

Most applications use `QMainWindow` as their primary window:

```python
import sys
from PySide6.QtWidgets import QApplication, QMainWindow, QLabel
from PySide6.QtCore import Qt

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        
        # Window properties
        self.setWindowTitle("My First PySide6 App")
        self.setGeometry(100, 100, 600, 400)  # x, y, width, height
        
        # Central widget
        label = QLabel("Welcome to PySide6!")
        label.setAlignment(Qt.AlignmentFlag.AlignCenter)
        self.setCentralWidget(label)

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec())
```

### QMainWindow Structure

```
┌─────────────────────────────────────────┐
│            Menu Bar                      │
├─────────────────────────────────────────┤
│            Tool Bar(s)                   │
├─────┬─────────────────────────────┬─────┤
│     │                             │     │
│ D   │                             │ D   │
│ o   │      Central Widget         │ o   │
│ c   │                             │ c   │
│ k   │                             │ k   │
│     │                             │     │
├─────┴─────────────────────────────┴─────┤
│            Status Bar                    │
└─────────────────────────────────────────┘
```

---

## 3. Understanding Qt Widgets

### What Are Widgets?

Widgets are the visual elements of your GUI: buttons, text fields, labels, etc. All widgets inherit from `QWidget`.

### Common Widgets

#### QPushButton - Clickable Button

```python
from PySide6.QtWidgets import QPushButton

button = QPushButton("Click Me!")
button.setToolTip("This is a tooltip")
button.setEnabled(True)  # or False to disable
```

#### QLabel - Text/Image Display

```python
from PySide6.QtWidgets import QLabel
from PySide6.QtCore import Qt

label = QLabel("Hello World")
label.setAlignment(Qt.AlignmentFlag.AlignCenter)
label.setWordWrap(True)

# Display an image
from PySide6.QtGui import QPixmap
image_label = QLabel()
image_label.setPixmap(QPixmap("image.png"))
```

#### QLineEdit - Single Line Text Input

```python
from PySide6.QtWidgets import QLineEdit
from PySide6.QtGui import QValidator

line_edit = QLineEdit()
line_edit.setPlaceholderText("Enter your name...")
line_edit.setMaxLength(50)
line_edit.setEchoMode(QLineEdit.EchoMode.Password)  # For passwords

# Get/Set text
text = line_edit.text()
line_edit.setText("Default value")
line_edit.clear()
```

#### QTextEdit - Multi-line Text Editor

```python
from PySide6.QtWidgets import QTextEdit

text_edit = QTextEdit()
text_edit.setPlainText("Plain text content")
text_edit.setHtml("<b>Bold</b> and <i>italic</i> text")
text_edit.setReadOnly(True)  # Make read-only

# Get content
plain_text = text_edit.toPlainText()
html_text = text_edit.toHtml()
```

#### QCheckBox - Checkbox

```python
from PySide6.QtWidgets import QCheckBox
from PySide6.QtCore import Qt

checkbox = QCheckBox("Enable feature")
checkbox.setChecked(True)
checkbox.setTristate(True)  # Enable three states

# Check state
if checkbox.isChecked():
    print("Checked!")
    
# Tri-state values
state = checkbox.checkState()
# Qt.CheckState.Unchecked, Qt.CheckState.PartiallyChecked, Qt.CheckState.Checked
```

#### QRadioButton - Radio Button

```python
from PySide6.QtWidgets import QRadioButton, QButtonGroup, QVBoxLayout, QWidget

# Radio buttons in a group
widget = QWidget()
layout = QVBoxLayout(widget)

radio1 = QRadioButton("Option 1")
radio2 = QRadioButton("Option 2")
radio3 = QRadioButton("Option 3")

radio1.setChecked(True)  # Default selection

layout.addWidget(radio1)
layout.addWidget(radio2)
layout.addWidget(radio3)

# Button group for exclusive selection
group = QButtonGroup(widget)
group.addButton(radio1, 1)
group.addButton(radio2, 2)
group.addButton(radio3, 3)
```

#### QComboBox - Dropdown List

```python
from PySide6.QtWidgets import QComboBox

combo = QComboBox()
combo.addItem("Option 1")
combo.addItem("Option 2")
combo.addItems(["Option 3", "Option 4", "Option 5"])

combo.setCurrentIndex(0)  # Select first item
combo.setCurrentText("Option 2")  # Select by text
combo.setEditable(True)  # Allow custom input

# Get selection
current_text = combo.currentText()
current_index = combo.currentIndex()
```

#### QSpinBox and QDoubleSpinBox - Numeric Input

```python
from PySide6.QtWidgets import QSpinBox, QDoubleSpinBox

# Integer spinner
spin = QSpinBox()
spin.setRange(0, 100)  # Min and max values
spin.setValue(50)
spin.setSingleStep(5)
spin.setPrefix("$ ")
spin.setSuffix(" items")

# Float spinner
double_spin = QDoubleSpinBox()
double_spin.setRange(0.0, 100.0)
double_spin.setValue(50.5)
double_spin.setDecimals(2)
double_spin.setSingleStep(0.1)
```

#### QSlider - Slider Control

```python
from PySide6.QtWidgets import QSlider
from PySide6.QtCore import Qt

slider = QSlider(Qt.Orientation.Horizontal)  # or Vertical
slider.setRange(0, 100)
slider.setValue(50)
slider.setTickPosition(QSlider.TickPosition.TicksBelow)
slider.setTickInterval(10)
slider.setSingleStep(1)
slider.setPageStep(10)
```

#### QProgressBar - Progress Indicator

```python
from PySide6.QtWidgets import QProgressBar

progress = QProgressBar()
progress.setRange(0, 100)
progress.setValue(75)
progress.setTextVisible(True)
progress.setFormat("%v / %m (%p%)")  # Custom format

# Indeterminate mode (busy indicator)
progress.setRange(0, 0)  # Set both to 0 for indeterminate
```

#### QListWidget - Simple List

```python
from PySide6.QtWidgets import QListWidget, QListWidgetItem

list_widget = QListWidget()
list_widget.addItem("Item 1")
list_widget.addItems(["Item 2", "Item 3", "Item 4"])

# Custom items
item = QListWidgetItem("Custom Item")
item.setToolTip("This is a custom item")
list_widget.addItem(item)

# Selection
list_widget.setSelectionMode(QListWidget.SelectionMode.MultiSelection)
selected_items = list_widget.selectedItems()
```

#### QTableWidget - Simple Table

```python
from PySide6.QtWidgets import QTableWidget, QTableWidgetItem

table = QTableWidget(5, 3)  # 5 rows, 3 columns
table.setHorizontalHeaderLabels(["Name", "Age", "City"])

# Set cell content
table.setItem(0, 0, QTableWidgetItem("Alice"))
table.setItem(0, 1, QTableWidgetItem("25"))
table.setItem(0, 2, QTableWidgetItem("New York"))

# Table properties
table.setAlternatingRowColors(True)
table.setSortingEnabled(True)
```

### Complete Widget Example

```python
import sys
from PySide6.QtWidgets import (
    QApplication, QMainWindow, QWidget, QVBoxLayout, QHBoxLayout,
    QLabel, QPushButton, QLineEdit, QCheckBox, QComboBox, QSpinBox
)

class WidgetDemo(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Widget Demo")
        self.setGeometry(100, 100, 400, 300)
        
        # Central widget and layout
        central = QWidget()
        self.setCentralWidget(central)
        layout = QVBoxLayout(central)
        
        # Name input
        name_layout = QHBoxLayout()
        name_layout.addWidget(QLabel("Name:"))
        self.name_input = QLineEdit()
        self.name_input.setPlaceholderText("Enter your name")
        name_layout.addWidget(self.name_input)
        layout.addLayout(name_layout)
        
        # Age spinner
        age_layout = QHBoxLayout()
        age_layout.addWidget(QLabel("Age:"))
        self.age_spin = QSpinBox()
        self.age_spin.setRange(0, 150)
        self.age_spin.setValue(25)
        age_layout.addWidget(self.age_spin)
        age_layout.addStretch()
        layout.addLayout(age_layout)
        
        # Country dropdown
        country_layout = QHBoxLayout()
        country_layout.addWidget(QLabel("Country:"))
        self.country_combo = QComboBox()
        self.country_combo.addItems(["USA", "UK", "Canada", "Australia", "Other"])
        country_layout.addWidget(self.country_combo)
        layout.addLayout(country_layout)
        
        # Newsletter checkbox
        self.newsletter_check = QCheckBox("Subscribe to newsletter")
        layout.addWidget(self.newsletter_check)
        
        # Submit button
        self.submit_btn = QPushButton("Submit")
        self.submit_btn.clicked.connect(self.on_submit)
        layout.addWidget(self.submit_btn)
        
        # Result label
        self.result_label = QLabel("")
        layout.addWidget(self.result_label)
        
        layout.addStretch()
    
    def on_submit(self):
        name = self.name_input.text()
        age = self.age_spin.value()
        country = self.country_combo.currentText()
        newsletter = "Yes" if self.newsletter_check.isChecked() else "No"
        
        result = f"Name: {name}, Age: {age}, Country: {country}, Newsletter: {newsletter}"
        self.result_label.setText(result)

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = WidgetDemo()
    window.show()
    sys.exit(app.exec())
```

---

## 4. Layout Management

### Why Use Layouts?

Layouts automatically:
- Arrange widgets in an organized manner
- Resize widgets when the window resizes
- Handle different screen sizes and DPIs

### QVBoxLayout - Vertical Layout

Arranges widgets in a vertical column:

```python
from PySide6.QtWidgets import QWidget, QVBoxLayout, QPushButton

widget = QWidget()
layout = QVBoxLayout(widget)

layout.addWidget(QPushButton("Button 1"))
layout.addWidget(QPushButton("Button 2"))
layout.addWidget(QPushButton("Button 3"))
```

```
┌─────────────┐
│  Button 1   │
├─────────────┤
│  Button 2   │
├─────────────┤
│  Button 3   │
└─────────────┘
```

### QHBoxLayout - Horizontal Layout

Arranges widgets in a horizontal row:

```python
from PySide6.QtWidgets import QWidget, QHBoxLayout, QPushButton

widget = QWidget()
layout = QHBoxLayout(widget)

layout.addWidget(QPushButton("Button 1"))
layout.addWidget(QPushButton("Button 2"))
layout.addWidget(QPushButton("Button 3"))
```

```
┌──────────┬──────────┬──────────┐
│ Button 1 │ Button 2 │ Button 3 │
└──────────┴──────────┴──────────┘
```

### QGridLayout - Grid Layout

Arranges widgets in a grid:

```python
from PySide6.QtWidgets import QWidget, QGridLayout, QPushButton

widget = QWidget()
layout = QGridLayout(widget)

# addWidget(widget, row, column, rowSpan, columnSpan)
layout.addWidget(QPushButton("1"), 0, 0)
layout.addWidget(QPushButton("2"), 0, 1)
layout.addWidget(QPushButton("3"), 0, 2)
layout.addWidget(QPushButton("4"), 1, 0)
layout.addWidget(QPushButton("5"), 1, 1)
layout.addWidget(QPushButton("6"), 1, 2)

# Spanning multiple cells
layout.addWidget(QPushButton("Wide"), 2, 0, 1, 3)  # Spans 3 columns
```

```
┌─────┬─────┬─────┐
│  1  │  2  │  3  │
├─────┼─────┼─────┤
│  4  │  5  │  6  │
├─────┴─────┴─────┤
│      Wide       │
└─────────────────┘
```

### QFormLayout - Form Layout

For form-style layouts (label-field pairs):

```python
from PySide6.QtWidgets import QWidget, QFormLayout, QLineEdit, QSpinBox

widget = QWidget()
layout = QFormLayout(widget)

layout.addRow("Name:", QLineEdit())
layout.addRow("Age:", QSpinBox())
layout.addRow("Email:", QLineEdit())
```

```
┌────────┬──────────────────┐
│  Name: │ [              ] │
├────────┼──────────────────┤
│   Age: │ [    0    ↕]     │
├────────┼──────────────────┤
│ Email: │ [              ] │
└────────┴──────────────────┘
```

### QStackedLayout - Stacked Pages

Shows one widget at a time (like tabs without the tab bar):

```python
from PySide6.QtWidgets import QWidget, QStackedLayout, QLabel

widget = QWidget()
layout = QStackedLayout(widget)

page1 = QLabel("Page 1")
page2 = QLabel("Page 2")
page3 = QLabel("Page 3")

layout.addWidget(page1)
layout.addWidget(page2)
layout.addWidget(page3)

# Switch pages
layout.setCurrentIndex(1)  # Show page 2
```

### Nested Layouts

Combine layouts for complex UIs:

```python
from PySide6.QtWidgets import (
    QWidget, QVBoxLayout, QHBoxLayout, QGridLayout,
    QLabel, QLineEdit, QPushButton
)

widget = QWidget()
main_layout = QVBoxLayout(widget)

# Form section
form_layout = QGridLayout()
form_layout.addWidget(QLabel("Username:"), 0, 0)
form_layout.addWidget(QLineEdit(), 0, 1)
form_layout.addWidget(QLabel("Password:"), 1, 0)
form_layout.addWidget(QLineEdit(), 1, 1)
main_layout.addLayout(form_layout)

# Button section
button_layout = QHBoxLayout()
button_layout.addStretch()  # Push buttons to the right
button_layout.addWidget(QPushButton("Cancel"))
button_layout.addWidget(QPushButton("OK"))
main_layout.addLayout(button_layout)
```

### Layout Spacing and Margins

```python
layout = QVBoxLayout()

# Spacing between widgets
layout.setSpacing(10)

# Margins around the layout (left, top, right, bottom)
layout.setContentsMargins(20, 20, 20, 20)
```

### Stretch and Spacers

```python
layout = QVBoxLayout()

layout.addWidget(QPushButton("Top"))
layout.addStretch(1)  # Flexible space
layout.addWidget(QPushButton("Bottom"))

# Or use QSpacerItem for more control
from PySide6.QtWidgets import QSpacerItem, QSizePolicy
spacer = QSpacerItem(20, 40, QSizePolicy.Policy.Minimum, QSizePolicy.Policy.Expanding)
layout.addItem(spacer)
```

### Size Policies

Control how widgets behave when resized:

```python
from PySide6.QtWidgets import QSizePolicy

button = QPushButton("Button")
button.setSizePolicy(
    QSizePolicy.Policy.Expanding,   # Horizontal policy
    QSizePolicy.Policy.Fixed        # Vertical policy
)
```

Size Policy Options:
- `Fixed`: Widget cannot grow or shrink
- `Minimum`: Widget can grow but not shrink below minimum
- `Maximum`: Widget can shrink but not grow beyond maximum
- `Preferred`: Widget prefers its size hint
- `Expanding`: Widget wants to grow
- `MinimumExpanding`: Widget can grow, minimum size is hint
- `Ignored`: Size hint is ignored

---

## 5. Signals and Slots

### The Signal-Slot Mechanism

Signals and slots are Qt's mechanism for communication between objects. When an event occurs (signal), connected functions (slots) are called.

```
┌─────────────┐         signal          ┌─────────────┐
│   Sender    │ ──────────────────────> │  Receiver   │
│   Object    │                         │    Slot     │
└─────────────┘                         └─────────────┘
```

### Basic Connection

```python
from PySide6.QtWidgets import QApplication, QPushButton
import sys

def on_button_clicked():
    print("Button was clicked!")

app = QApplication(sys.argv)

button = QPushButton("Click me")
button.clicked.connect(on_button_clicked)
button.show()

sys.exit(app.exec())
```

### Connecting to Methods

```python
class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        
        button = QPushButton("Click me")
        button.clicked.connect(self.on_button_clicked)
        self.setCentralWidget(button)
    
    def on_button_clicked(self):
        print("Button clicked!")
```

### Signals with Arguments

Many signals pass data:

```python
from PySide6.QtWidgets import QLineEdit

line_edit = QLineEdit()

# textChanged signal passes the new text
line_edit.textChanged.connect(self.on_text_changed)

def on_text_changed(text):
    print(f"Text changed to: {text}")
```

### Lambda Connections

Use lambdas for simple connections or to pass extra arguments:

```python
button.clicked.connect(lambda: print("Clicked!"))

# Passing extra data
button.clicked.connect(lambda: self.handle_button(button_id=1))

# With signal argument
line_edit.textChanged.connect(lambda text: self.handle_text(text, source="input"))
```

### Disconnecting Signals

```python
# Disconnect specific slot
button.clicked.disconnect(self.on_button_clicked)

# Disconnect all slots from a signal
button.clicked.disconnect()
```

### Custom Signals

Create your own signals:

```python
from PySide6.QtCore import Signal, QObject

class Worker(QObject):
    # Define custom signals
    finished = Signal()
    progress = Signal(int)
    result = Signal(str, int)  # Multiple arguments
    
    def do_work(self):
        for i in range(100):
            self.progress.emit(i)  # Emit progress
        
        self.result.emit("Done", 100)
        self.finished.emit()

# Connect to custom signals
worker = Worker()
worker.finished.connect(lambda: print("Work finished!"))
worker.progress.connect(lambda value: print(f"Progress: {value}%"))
worker.result.connect(lambda msg, val: print(f"{msg}: {val}"))
```

### Common Widget Signals

| Widget | Signal | Description |
|--------|--------|-------------|
| `QPushButton` | `clicked` | Button was clicked |
| `QPushButton` | `pressed` | Button was pressed down |
| `QPushButton` | `released` | Button was released |
| `QLineEdit` | `textChanged(str)` | Text was modified |
| `QLineEdit` | `returnPressed` | Enter key was pressed |
| `QCheckBox` | `stateChanged(int)` | Check state changed |
| `QComboBox` | `currentIndexChanged(int)` | Selection changed |
| `QSlider` | `valueChanged(int)` | Value changed |
| `QSpinBox` | `valueChanged(int)` | Value changed |
| `QListWidget` | `itemClicked(QListWidgetItem)` | Item clicked |
| `QListWidget` | `itemDoubleClicked(QListWidgetItem)` | Item double-clicked |

### Complete Signals Example

```python
import sys
from PySide6.QtWidgets import (
    QApplication, QMainWindow, QWidget, QVBoxLayout,
    QPushButton, QLineEdit, QLabel, QSlider, QProgressBar
)
from PySide6.QtCore import Qt, Signal

class SignalDemo(QMainWindow):
    # Custom signal
    custom_signal = Signal(str)
    
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Signals and Slots Demo")
        
        central = QWidget()
        self.setCentralWidget(central)
        layout = QVBoxLayout(central)
        
        # Button signals
        self.button = QPushButton("Click me (0)")
        self.click_count = 0
        self.button.clicked.connect(self.on_button_click)
        layout.addWidget(self.button)
        
        # Text input signals
        self.line_edit = QLineEdit()
        self.line_edit.setPlaceholderText("Type something...")
        self.line_edit.textChanged.connect(self.on_text_changed)
        self.line_edit.returnPressed.connect(self.on_return_pressed)
        layout.addWidget(self.line_edit)
        
        self.text_label = QLabel("You typed: ")
        layout.addWidget(self.text_label)
        
        # Slider signals
        self.slider = QSlider(Qt.Orientation.Horizontal)
        self.slider.setRange(0, 100)
        self.slider.valueChanged.connect(self.on_slider_changed)
        layout.addWidget(self.slider)
        
        self.progress = QProgressBar()
        self.progress.setRange(0, 100)
        layout.addWidget(self.progress)
        
        # Custom signal
        self.custom_signal.connect(self.on_custom_signal)
        
        emit_btn = QPushButton("Emit Custom Signal")
        emit_btn.clicked.connect(lambda: self.custom_signal.emit("Hello from custom signal!"))
        layout.addWidget(emit_btn)
        
        self.custom_label = QLabel("")
        layout.addWidget(self.custom_label)
    
    def on_button_click(self):
        self.click_count += 1
        self.button.setText(f"Click me ({self.click_count})")
    
    def on_text_changed(self, text):
        self.text_label.setText(f"You typed: {text}")
    
    def on_return_pressed(self):
        self.text_label.setText(f"You pressed Enter! Text: {self.line_edit.text()}")
    
    def on_slider_changed(self, value):
        self.progress.setValue(value)
    
    def on_custom_signal(self, message):
        self.custom_label.setText(message)

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = SignalDemo()
    window.show()
    sys.exit(app.exec())
```

---

## 6. Dialog Boxes

### Message Boxes

Quick dialogs for user feedback:

```python
from PySide6.QtWidgets import QMessageBox

# Information
QMessageBox.information(self, "Info", "Operation completed successfully!")

# Warning
QMessageBox.warning(self, "Warning", "Are you sure you want to proceed?")

# Error/Critical
QMessageBox.critical(self, "Error", "An error occurred!")

# Question (returns button clicked)
result = QMessageBox.question(
    self, 
    "Confirm", 
    "Do you want to save changes?",
    QMessageBox.StandardButton.Yes | QMessageBox.StandardButton.No | QMessageBox.StandardButton.Cancel
)

if result == QMessageBox.StandardButton.Yes:
    print("User clicked Yes")
elif result == QMessageBox.StandardButton.No:
    print("User clicked No")
else:
    print("User clicked Cancel")
```

### Custom Message Box

```python
from PySide6.QtWidgets import QMessageBox
from PySide6.QtGui import QIcon

msg = QMessageBox()
msg.setIcon(QMessageBox.Icon.Question)
msg.setWindowTitle("Custom Dialog")
msg.setText("This is the main message")
msg.setInformativeText("This is additional information")
msg.setDetailedText("Here are the details:\n- Detail 1\n- Detail 2")
msg.setStandardButtons(
    QMessageBox.StandardButton.Ok | 
    QMessageBox.StandardButton.Cancel |
    QMessageBox.StandardButton.Help
)
msg.setDefaultButton(QMessageBox.StandardButton.Ok)

result = msg.exec()
```

### Input Dialogs

```python
from PySide6.QtWidgets import QInputDialog

# Text input
text, ok = QInputDialog.getText(self, "Input", "Enter your name:")
if ok and text:
    print(f"Name: {text}")

# Integer input
number, ok = QInputDialog.getInt(
    self, "Input", "Enter a number:",
    value=50, min=0, max=100, step=1
)

# Double input
value, ok = QInputDialog.getDouble(
    self, "Input", "Enter a value:",
    value=0.5, min=0.0, max=1.0, decimals=2
)

# Item selection
items = ["Option 1", "Option 2", "Option 3"]
item, ok = QInputDialog.getItem(
    self, "Select", "Choose an option:",
    items, current=0, editable=False
)
```

### File Dialogs

```python
from PySide6.QtWidgets import QFileDialog

# Open single file
file_path, _ = QFileDialog.getOpenFileName(
    self,
    "Open File",
    "",  # Starting directory
    "Text Files (*.txt);;Python Files (*.py);;All Files (*)"
)

# Open multiple files
file_paths, _ = QFileDialog.getOpenFileNames(
    self,
    "Open Files",
    "",
    "Images (*.png *.jpg *.jpeg);;All Files (*)"
)

# Save file
file_path, _ = QFileDialog.getSaveFileName(
    self,
    "Save File",
    "",
    "Text Files (*.txt);;All Files (*)"
)

# Select directory
directory = QFileDialog.getExistingDirectory(
    self,
    "Select Directory",
    ""
)
```

### Color Dialog

```python
from PySide6.QtWidgets import QColorDialog
from PySide6.QtGui import QColor

# Basic color dialog
color = QColorDialog.getColor(
    initial=QColor(255, 0, 0),  # Starting color
    parent=self,
    title="Select Color"
)

if color.isValid():
    print(f"Selected: {color.name()}")  # e.g., "#ff0000"
    print(f"RGB: {color.red()}, {color.green()}, {color.blue()}")
```

### Font Dialog

```python
from PySide6.QtWidgets import QFontDialog
from PySide6.QtGui import QFont

font, ok = QFontDialog.getFont(
    QFont("Arial", 12),  # Initial font
    self,
    "Select Font"
)

if ok:
    print(f"Selected: {font.family()}, {font.pointSize()}pt")
    self.some_label.setFont(font)
```

### Custom Dialogs

Create your own dialog by subclassing `QDialog`:

```python
from PySide6.QtWidgets import (
    QDialog, QVBoxLayout, QHBoxLayout, QFormLayout,
    QLineEdit, QSpinBox, QDialogButtonBox, QLabel
)
from PySide6.QtCore import Qt

class UserDialog(QDialog):
    def __init__(self, parent=None):
        super().__init__(parent)
        self.setWindowTitle("User Information")
        self.setModal(True)  # Block parent window
        
        layout = QVBoxLayout(self)
        
        # Form
        form = QFormLayout()
        self.name_input = QLineEdit()
        self.age_input = QSpinBox()
        self.age_input.setRange(0, 150)
        self.email_input = QLineEdit()
        
        form.addRow("Name:", self.name_input)
        form.addRow("Age:", self.age_input)
        form.addRow("Email:", self.email_input)
        layout.addLayout(form)
        
        # Buttons
        button_box = QDialogButtonBox(
            QDialogButtonBox.StandardButton.Ok | 
            QDialogButtonBox.StandardButton.Cancel
        )
        button_box.accepted.connect(self.accept)
        button_box.rejected.connect(self.reject)
        layout.addWidget(button_box)
    
    def get_data(self):
        return {
            "name": self.name_input.text(),
            "age": self.age_input.value(),
            "email": self.email_input.text()
        }

# Usage
dialog = UserDialog(self)
if dialog.exec() == QDialog.DialogCode.Accepted:
    data = dialog.get_data()
    print(f"User data: {data}")
```

---

## 7. Basic Event Handling

### Event System Overview

Events are low-level notifications about what's happening in your application: mouse clicks, key presses, window resizes, etc.

### Mouse Events

```python
from PySide6.QtWidgets import QWidget
from PySide6.QtCore import Qt

class MouseWidget(QWidget):
    def mousePressEvent(self, event):
        if event.button() == Qt.MouseButton.LeftButton:
            print(f"Left click at ({event.position().x()}, {event.position().y()})")
        elif event.button() == Qt.MouseButton.RightButton:
            print("Right click")
        super().mousePressEvent(event)
    
    def mouseReleaseEvent(self, event):
        print("Mouse released")
        super().mouseReleaseEvent(event)
    
    def mouseDoubleClickEvent(self, event):
        print("Double click!")
        super().mouseDoubleClickEvent(event)
    
    def mouseMoveEvent(self, event):
        # Note: only called when button is pressed by default
        # Enable mouse tracking for all moves: self.setMouseTracking(True)
        print(f"Mouse moved to ({event.position().x()}, {event.position().y()})")
        super().mouseMoveEvent(event)
    
    def wheelEvent(self, event):
        delta = event.angleDelta().y()
        if delta > 0:
            print("Scroll up")
        else:
            print("Scroll down")
        super().wheelEvent(event)
```

### Keyboard Events

```python
from PySide6.QtWidgets import QWidget
from PySide6.QtCore import Qt

class KeyboardWidget(QWidget):
    def keyPressEvent(self, event):
        key = event.key()
        text = event.text()
        modifiers = event.modifiers()
        
        # Check for specific keys
        if key == Qt.Key.Key_Escape:
            print("Escape pressed")
        elif key == Qt.Key.Key_Return or key == Qt.Key.Key_Enter:
            print("Enter pressed")
        elif key == Qt.Key.Key_Space:
            print("Space pressed")
        
        # Check modifiers
        if modifiers & Qt.KeyboardModifier.ControlModifier:
            if key == Qt.Key.Key_S:
                print("Ctrl+S pressed (Save)")
            elif key == Qt.Key.Key_C:
                print("Ctrl+C pressed (Copy)")
        
        # Regular character
        if text:
            print(f"Character: {text}")
        
        super().keyPressEvent(event)
    
    def keyReleaseEvent(self, event):
        print(f"Key released: {event.key()}")
        super().keyReleaseEvent(event)
```

### Window Events

```python
from PySide6.QtWidgets import QMainWindow
from PySide6.QtCore import Qt

class MainWindow(QMainWindow):
    def resizeEvent(self, event):
        old_size = event.oldSize()
        new_size = event.size()
        print(f"Window resized from {old_size.width()}x{old_size.height()} "
              f"to {new_size.width()}x{new_size.height()}")
        super().resizeEvent(event)
    
    def moveEvent(self, event):
        old_pos = event.oldPos()
        new_pos = event.pos()
        print(f"Window moved from ({old_pos.x()}, {old_pos.y()}) "
              f"to ({new_pos.x()}, {new_pos.y()})")
        super().moveEvent(event)
    
    def closeEvent(self, event):
        # Ask for confirmation before closing
        from PySide6.QtWidgets import QMessageBox
        
        reply = QMessageBox.question(
            self, "Confirm Exit",
            "Are you sure you want to exit?",
            QMessageBox.StandardButton.Yes | QMessageBox.StandardButton.No
        )
        
        if reply == QMessageBox.StandardButton.Yes:
            event.accept()  # Allow close
        else:
            event.ignore()  # Prevent close
    
    def showEvent(self, event):
        print("Window is now visible")
        super().showEvent(event)
    
    def hideEvent(self, event):
        print("Window is now hidden")
        super().hideEvent(event)
```

### Focus Events

```python
from PySide6.QtWidgets import QLineEdit

class FocusLineEdit(QLineEdit):
    def focusInEvent(self, event):
        print("Widget gained focus")
        self.setStyleSheet("background-color: lightyellow;")
        super().focusInEvent(event)
    
    def focusOutEvent(self, event):
        print("Widget lost focus")
        self.setStyleSheet("")
        super().focusOutEvent(event)
```

### Drag and Drop Events

```python
from PySide6.QtWidgets import QLabel
from PySide6.QtCore import Qt

class DropLabel(QLabel):
    def __init__(self):
        super().__init__("Drop files here")
        self.setAcceptDrops(True)
        self.setAlignment(Qt.AlignmentFlag.AlignCenter)
        self.setStyleSheet("border: 2px dashed gray; padding: 20px;")
    
    def dragEnterEvent(self, event):
        if event.mimeData().hasUrls():
            event.acceptProposedAction()
            self.setStyleSheet("border: 2px dashed green; padding: 20px; background: lightgreen;")
    
    def dragLeaveEvent(self, event):
        self.setStyleSheet("border: 2px dashed gray; padding: 20px;")
    
    def dropEvent(self, event):
        self.setStyleSheet("border: 2px dashed gray; padding: 20px;")
        
        for url in event.mimeData().urls():
            file_path = url.toLocalFile()
            print(f"Dropped: {file_path}")
        
        event.acceptProposedAction()
```

### Event Filters

Intercept events before they reach a widget:

```python
from PySide6.QtCore import QObject, QEvent

class EventFilter(QObject):
    def eventFilter(self, obj, event):
        if event.type() == QEvent.Type.KeyPress:
            print(f"Key pressed in {obj.objectName()}: {event.key()}")
            # Return True to consume the event, False to pass it on
            return False
        return super().eventFilter(obj, event)

# Install the filter
filter = EventFilter()
some_widget.installEventFilter(filter)
```

---

# Part 2: Intermediate Level

---

## 8. Custom Widgets

### Creating Custom Widgets

Create unique widgets by subclassing existing ones or `QWidget`:

```python
from PySide6.QtWidgets import QWidget
from PySide6.QtCore import Qt, Signal, Property
from PySide6.QtGui import QPainter, QColor, QPen, QBrush

class CircularProgress(QWidget):
    """A circular progress indicator widget."""
    
    valueChanged = Signal(int)
    
    def __init__(self, parent=None):
        super().__init__(parent)
        self._value = 0
        self._minimum = 0
        self._maximum = 100
        self._color = QColor(0, 120, 212)
        self._background_color = QColor(230, 230, 230)
        self._thickness = 10
        
        self.setMinimumSize(100, 100)
    
    def value(self):
        return self._value
    
    def setValue(self, value):
        if self._minimum <= value <= self._maximum:
            self._value = value
            self.valueChanged.emit(value)
            self.update()  # Trigger repaint
    
    def setRange(self, minimum, maximum):
        self._minimum = minimum
        self._maximum = maximum
        self.update()
    
    def setColor(self, color):
        self._color = color
        self.update()
    
    def paintEvent(self, event):
        painter = QPainter(self)
        painter.setRenderHint(QPainter.RenderHint.Antialiasing)
        
        # Calculate dimensions
        side = min(self.width(), self.height())
        rect = self.rect().adjusted(
            self._thickness, self._thickness,
            -self._thickness, -self._thickness
        )
        
        # Draw background circle
        painter.setPen(QPen(self._background_color, self._thickness))
        painter.drawArc(rect, 0, 360 * 16)
        
        # Draw progress arc
        progress_pen = QPen(self._color, self._thickness)
        progress_pen.setCapStyle(Qt.PenCapStyle.RoundCap)
        painter.setPen(progress_pen)
        
        # Calculate span angle (in 1/16th of a degree)
        range_val = self._maximum - self._minimum
        if range_val > 0:
            span = int((self._value - self._minimum) / range_val * 360 * 16)
            painter.drawArc(rect, 90 * 16, -span)  # Start from top
        
        # Draw percentage text
        painter.setPen(QPen(Qt.GlobalColor.black))
        percentage = int((self._value - self._minimum) / (self._maximum - self._minimum) * 100)
        painter.drawText(rect, Qt.AlignmentFlag.AlignCenter, f"{percentage}%")
```

### Custom Paint Events

The `paintEvent` is where you draw your widget:

```python
from PySide6.QtWidgets import QWidget
from PySide6.QtCore import Qt
from PySide6.QtGui import QPainter, QColor, QPen, QBrush, QLinearGradient

class GradientWidget(QWidget):
    def paintEvent(self, event):
        painter = QPainter(self)
        painter.setRenderHint(QPainter.RenderHint.Antialiasing)
        
        # Create gradient
        gradient = QLinearGradient(0, 0, self.width(), self.height())
        gradient.setColorAt(0, QColor(255, 0, 0))
        gradient.setColorAt(0.5, QColor(0, 255, 0))
        gradient.setColorAt(1, QColor(0, 0, 255))
        
        # Fill with gradient
        painter.fillRect(self.rect(), gradient)
        
        # Draw shapes
        painter.setPen(QPen(Qt.GlobalColor.white, 2))
        painter.setBrush(QBrush(QColor(255, 255, 255, 100)))
        
        # Draw rectangle
        painter.drawRect(20, 20, 100, 60)
        
        # Draw ellipse
        painter.drawEllipse(150, 20, 80, 60)
        
        # Draw rounded rectangle
        painter.drawRoundedRect(260, 20, 100, 60, 15, 15)
```

### Custom Widget with Properties

Make your widget designer-compatible:

```python
from PySide6.QtWidgets import QWidget
from PySide6.QtCore import Property, Signal

class ToggleSwitch(QWidget):
    toggled = Signal(bool)
    
    def __init__(self, parent=None):
        super().__init__(parent)
        self._checked = False
        self._track_color = QColor(180, 180, 180)
        self._thumb_color = QColor(255, 255, 255)
        self._active_color = QColor(0, 120, 212)
        
        self.setFixedSize(50, 26)
        self.setCursor(Qt.CursorShape.PointingHandCursor)
    
    def isChecked(self):
        return self._checked
    
    def setChecked(self, checked):
        if self._checked != checked:
            self._checked = checked
            self.toggled.emit(checked)
            self.update()
    
    # Define Qt Property for use in Qt Designer
    checked = Property(bool, isChecked, setChecked)
    
    def mousePressEvent(self, event):
        self.setChecked(not self._checked)
    
    def paintEvent(self, event):
        painter = QPainter(self)
        painter.setRenderHint(QPainter.RenderHint.Antialiasing)
        
        # Draw track
        track_color = self._active_color if self._checked else self._track_color
        painter.setBrush(QBrush(track_color))
        painter.setPen(Qt.PenStyle.NoPen)
        painter.drawRoundedRect(0, 3, 50, 20, 10, 10)
        
        # Draw thumb
        thumb_x = 26 if self._checked else 2
        painter.setBrush(QBrush(self._thumb_color))
        painter.drawEllipse(thumb_x, 1, 22, 22)
```

### Composite Widgets

Combine existing widgets into new ones:

```python
from PySide6.QtWidgets import (
    QWidget, QHBoxLayout, QVBoxLayout,
    QLabel, QLineEdit, QPushButton
)
from PySide6.QtCore import Signal

class SearchBox(QWidget):
    """A search input with clear button."""
    
    searchRequested = Signal(str)
    textChanged = Signal(str)
    
    def __init__(self, parent=None):
        super().__init__(parent)
        
        layout = QHBoxLayout(self)
        layout.setContentsMargins(0, 0, 0, 0)
        
        self.line_edit = QLineEdit()
        self.line_edit.setPlaceholderText("Search...")
        self.line_edit.textChanged.connect(self.textChanged.emit)
        self.line_edit.returnPressed.connect(self._on_search)
        
        self.clear_btn = QPushButton("✕")
        self.clear_btn.setFixedSize(24, 24)
        self.clear_btn.clicked.connect(self.clear)
        self.clear_btn.hide()
        
        self.search_btn = QPushButton("🔍")
        self.search_btn.setFixedSize(24, 24)
        self.search_btn.clicked.connect(self._on_search)
        
        layout.addWidget(self.line_edit)
        layout.addWidget(self.clear_btn)
        layout.addWidget(self.search_btn)
        
        self.line_edit.textChanged.connect(self._update_clear_button)
    
    def _update_clear_button(self, text):
        self.clear_btn.setVisible(bool(text))
    
    def _on_search(self):
        self.searchRequested.emit(self.line_edit.text())
    
    def clear(self):
        self.line_edit.clear()
    
    def text(self):
        return self.line_edit.text()
    
    def setText(self, text):
        self.line_edit.setText(text)
```

---

## 9. Model-View Programming

### The Model-View Architecture

Qt separates data (Model) from presentation (View):

```
┌─────────┐     ┌───────────┐     ┌──────────┐
│  Data   │ ←── │   Model   │ ──→ │   View   │
└─────────┘     └───────────┘     └──────────┘
                      │
                      ↓
               ┌──────────────┐
               │   Delegate   │
               └──────────────┘
```

### QStringListModel - Simple List Model

```python
from PySide6.QtWidgets import QListView
from PySide6.QtCore import QStringListModel

# Create model
model = QStringListModel()
model.setStringList(["Apple", "Banana", "Cherry", "Date"])

# Create view
view = QListView()
view.setModel(model)

# Modify data
model.insertRow(0)
model.setData(model.index(0), "Apricot")

# Get data
for i in range(model.rowCount()):
    print(model.data(model.index(i)))
```

### QStandardItemModel - Flexible Item Model

```python
from PySide6.QtWidgets import QTreeView
from PySide6.QtGui import QStandardItemModel, QStandardItem

# Create model
model = QStandardItemModel()
model.setHorizontalHeaderLabels(["Name", "Size", "Type"])

# Add items
root = model.invisibleRootItem()

# Add files
folder = QStandardItem("Documents")
folder.appendRow([
    QStandardItem("report.pdf"),
    QStandardItem("2.5 MB"),
    QStandardItem("PDF Document")
])
folder.appendRow([
    QStandardItem("notes.txt"),
    QStandardItem("4 KB"),
    QStandardItem("Text File")
])
root.appendRow(folder)

# Create view
view = QTreeView()
view.setModel(model)
```

### Custom Table Model

```python
from PySide6.QtCore import Qt, QAbstractTableModel, QModelIndex

class PersonTableModel(QAbstractTableModel):
    def __init__(self, data=None):
        super().__init__()
        self._data = data or []
        self._headers = ["Name", "Age", "City"]
    
    def rowCount(self, parent=QModelIndex()):
        return len(self._data)
    
    def columnCount(self, parent=QModelIndex()):
        return len(self._headers)
    
    def data(self, index, role=Qt.ItemDataRole.DisplayRole):
        if not index.isValid():
            return None
        
        row = index.row()
        col = index.column()
        
        if role == Qt.ItemDataRole.DisplayRole:
            person = self._data[row]
            if col == 0:
                return person["name"]
            elif col == 1:
                return person["age"]
            elif col == 2:
                return person["city"]
        
        elif role == Qt.ItemDataRole.TextAlignmentRole:
            if col == 1:  # Age column
                return Qt.AlignmentFlag.AlignCenter
        
        return None
    
    def headerData(self, section, orientation, role=Qt.ItemDataRole.DisplayRole):
        if role == Qt.ItemDataRole.DisplayRole:
            if orientation == Qt.Orientation.Horizontal:
                return self._headers[section]
            else:
                return str(section + 1)
        return None
    
    def flags(self, index):
        return Qt.ItemFlag.ItemIsEnabled | Qt.ItemFlag.ItemIsSelectable | Qt.ItemFlag.ItemIsEditable
    
    def setData(self, index, value, role=Qt.ItemDataRole.EditRole):
        if role == Qt.ItemDataRole.EditRole:
            row = index.row()
            col = index.column()
            
            if col == 0:
                self._data[row]["name"] = value
            elif col == 1:
                self._data[row]["age"] = int(value)
            elif col == 2:
                self._data[row]["city"] = value
            
            self.dataChanged.emit(index, index, [role])
            return True
        return False
    
    def addPerson(self, name, age, city):
        self.beginInsertRows(QModelIndex(), len(self._data), len(self._data))
        self._data.append({"name": name, "age": age, "city": city})
        self.endInsertRows()
    
    def removePerson(self, row):
        self.beginRemoveRows(QModelIndex(), row, row)
        del self._data[row]
        self.endRemoveRows()

# Usage
data = [
    {"name": "Alice", "age": 30, "city": "New York"},
    {"name": "Bob", "age": 25, "city": "Los Angeles"},
    {"name": "Charlie", "age": 35, "city": "Chicago"}
]

model = PersonTableModel(data)
view = QTableView()
view.setModel(model)
```

### Proxy Models for Sorting and Filtering

```python
from PySide6.QtCore import QSortFilterProxyModel

# Create source model
source_model = PersonTableModel(data)

# Create proxy for filtering/sorting
proxy_model = QSortFilterProxyModel()
proxy_model.setSourceModel(source_model)
proxy_model.setFilterKeyColumn(0)  # Filter on name column
proxy_model.setFilterCaseSensitivity(Qt.CaseSensitivity.CaseInsensitive)

# Apply filter
proxy_model.setFilterFixedString("ali")  # Shows only "Alice"

# Or use regex
proxy_model.setFilterRegularExpression("^[AB].*")  # Names starting with A or B

# Enable sorting
view = QTableView()
view.setModel(proxy_model)
view.setSortingEnabled(True)
```

### Custom Delegates

Control how items are displayed and edited:

```python
from PySide6.QtWidgets import QStyledItemDelegate, QSpinBox, QComboBox
from PySide6.QtCore import Qt

class AgeSpinBoxDelegate(QStyledItemDelegate):
    """Custom delegate for editing age with a spin box."""
    
    def createEditor(self, parent, option, index):
        editor = QSpinBox(parent)
        editor.setRange(0, 150)
        return editor
    
    def setEditorData(self, editor, index):
        value = index.model().data(index, Qt.ItemDataRole.EditRole)
        editor.setValue(int(value) if value else 0)
    
    def setModelData(self, editor, model, index):
        model.setData(index, editor.value(), Qt.ItemDataRole.EditRole)
    
    def updateEditorGeometry(self, editor, option, index):
        editor.setGeometry(option.rect)

class CityComboDelegate(QStyledItemDelegate):
    """Custom delegate for selecting city from a dropdown."""
    
    def __init__(self, cities, parent=None):
        super().__init__(parent)
        self.cities = cities
    
    def createEditor(self, parent, option, index):
        editor = QComboBox(parent)
        editor.addItems(self.cities)
        return editor
    
    def setEditorData(self, editor, index):
        value = index.model().data(index, Qt.ItemDataRole.EditRole)
        idx = editor.findText(value)
        if idx >= 0:
            editor.setCurrentIndex(idx)
    
    def setModelData(self, editor, model, index):
        model.setData(index, editor.currentText(), Qt.ItemDataRole.EditRole)

# Apply delegates to specific columns
view = QTableView()
view.setModel(model)
view.setItemDelegateForColumn(1, AgeSpinBoxDelegate(view))
view.setItemDelegateForColumn(2, CityComboDelegate(
    ["New York", "Los Angeles", "Chicago", "Houston", "Phoenix"],
    view
))
```

---

## 10. Multithreading with QThread

### Why Use Threading?

Long-running operations block the GUI, making it unresponsive. Use threads for:
- Network requests
- File I/O
- Heavy computations
- Database operations

### Worker Pattern (Recommended)

```python
from PySide6.QtCore import QObject, QThread, Signal
import time

class Worker(QObject):
    """Worker that performs heavy computation."""
    
    started = Signal()
    progress = Signal(int)
    finished = Signal(str)
    error = Signal(str)
    
    def __init__(self):
        super().__init__()
        self._is_running = True
    
    def run(self):
        try:
            self.started.emit()
            
            for i in range(101):
                if not self._is_running:
                    break
                    
                # Simulate work
                time.sleep(0.05)
                self.progress.emit(i)
            
            self.finished.emit("Task completed successfully!")
            
        except Exception as e:
            self.error.emit(str(e))
    
    def stop(self):
        self._is_running = False

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setup_ui()
        
        # Thread and worker setup
        self.thread = None
        self.worker = None
    
    def setup_ui(self):
        central = QWidget()
        self.setCentralWidget(central)
        layout = QVBoxLayout(central)
        
        self.progress_bar = QProgressBar()
        self.start_btn = QPushButton("Start")
        self.stop_btn = QPushButton("Stop")
        self.status_label = QLabel("Ready")
        
        self.start_btn.clicked.connect(self.start_work)
        self.stop_btn.clicked.connect(self.stop_work)
        self.stop_btn.setEnabled(False)
        
        layout.addWidget(self.progress_bar)
        layout.addWidget(self.start_btn)
        layout.addWidget(self.stop_btn)
        layout.addWidget(self.status_label)
    
    def start_work(self):
        # Create thread and worker
        self.thread = QThread()
        self.worker = Worker()
        
        # Move worker to thread
        self.worker.moveToThread(self.thread)
        
        # Connect signals
        self.thread.started.connect(self.worker.run)
        self.worker.started.connect(self.on_started)
        self.worker.progress.connect(self.on_progress)
        self.worker.finished.connect(self.on_finished)
        self.worker.error.connect(self.on_error)
        self.worker.finished.connect(self.thread.quit)
        self.worker.finished.connect(self.worker.deleteLater)
        self.thread.finished.connect(self.thread.deleteLater)
        
        # Start thread
        self.thread.start()
    
    def stop_work(self):
        if self.worker:
            self.worker.stop()
    
    def on_started(self):
        self.start_btn.setEnabled(False)
        self.stop_btn.setEnabled(True)
        self.status_label.setText("Working...")
    
    def on_progress(self, value):
        self.progress_bar.setValue(value)
    
    def on_finished(self, result):
        self.start_btn.setEnabled(True)
        self.stop_btn.setEnabled(False)
        self.status_label.setText(result)
    
    def on_error(self, error):
        self.start_btn.setEnabled(True)
        self.stop_btn.setEnabled(False)
        self.status_label.setText(f"Error: {error}")
```

### QThread Subclass Pattern

```python
from PySide6.QtCore import QThread, Signal

class DownloadThread(QThread):
    progress = Signal(int, int)  # current, total
    finished = Signal(bytes)
    error = Signal(str)
    
    def __init__(self, url):
        super().__init__()
        self.url = url
    
    def run(self):
        try:
            import urllib.request
            
            response = urllib.request.urlopen(self.url)
            total = int(response.headers.get('Content-Length', 0))
            
            data = b''
            chunk_size = 8192
            downloaded = 0
            
            while True:
                chunk = response.read(chunk_size)
                if not chunk:
                    break
                data += chunk
                downloaded += len(chunk)
                self.progress.emit(downloaded, total)
            
            self.finished.emit(data)
            
        except Exception as e:
            self.error.emit(str(e))

# Usage
thread = DownloadThread("https://example.com/file.zip")
thread.progress.connect(lambda cur, tot: print(f"{cur}/{tot}"))
thread.finished.connect(lambda data: print(f"Downloaded {len(data)} bytes"))
thread.start()
```

### Thread-Safe Updates with Signals

Always use signals to update the GUI from threads:

```python
# WRONG - Direct access from thread
class BadWorker(QThread):
    def run(self):
        self.parent().label.setText("Done")  # CRASH or undefined behavior!

# CORRECT - Use signals
class GoodWorker(QThread):
    update_label = Signal(str)
    
    def run(self):
        self.update_label.emit("Done")  # Safe!
```

### QThreadPool and QRunnable

For many small tasks:

```python
from PySide6.QtCore import QThreadPool, QRunnable, Signal, QObject

class WorkerSignals(QObject):
    finished = Signal()
    result = Signal(object)
    error = Signal(str)

class TaskRunner(QRunnable):
    def __init__(self, task_id, fn, *args, **kwargs):
        super().__init__()
        self.task_id = task_id
        self.fn = fn
        self.args = args
        self.kwargs = kwargs
        self.signals = WorkerSignals()
    
    def run(self):
        try:
            result = self.fn(*self.args, **self.kwargs)
            self.signals.result.emit(result)
        except Exception as e:
            self.signals.error.emit(str(e))
        finally:
            self.signals.finished.emit()

# Usage
pool = QThreadPool.globalInstance()
print(f"Max threads: {pool.maxThreadCount()}")

def heavy_task(n):
    import time
    time.sleep(1)
    return n * 2

for i in range(10):
    runner = TaskRunner(i, heavy_task, i)
    runner.signals.result.connect(lambda r: print(f"Result: {r}"))
    pool.start(runner)
```

---

## 11. Styling with Qt Style Sheets

### Introduction to QSS

Qt Style Sheets (QSS) are similar to CSS and allow you to customize widget appearance.

### Basic Syntax

```python
# Apply to single widget
button.setStyleSheet("background-color: blue; color: white;")

# Apply to application (all widgets)
app.setStyleSheet("""
    QPushButton {
        background-color: #0078d4;
        color: white;
        border: none;
        padding: 8px 16px;
        border-radius: 4px;
    }
    
    QPushButton:hover {
        background-color: #1084d8;
    }
    
    QPushButton:pressed {
        background-color: #006cbd;
    }
    
    QPushButton:disabled {
        background-color: #cccccc;
        color: #666666;
    }
""")
```

### Selectors

```css
/* Type selector - all buttons */
QPushButton {
    background-color: blue;
}

/* ID selector - specific widget with objectName */
#submitButton {
    font-weight: bold;
}

/* Class selector - widgets with property */
.important {
    color: red;
}

/* Descendant selector */
QDialog QPushButton {
    margin: 5px;
}

/* Child selector */
QFrame > QLabel {
    font-size: 14px;
}
```

```python
# Set object name for ID selector
button.setObjectName("submitButton")

# Set property for class selector
button.setProperty("class", "important")
```

### Pseudo-States

```css
/* Mouse hover */
QPushButton:hover {
    background-color: lightblue;
}

/* Pressed state */
QPushButton:pressed {
    background-color: darkblue;
}

/* Focused */
QLineEdit:focus {
    border: 2px solid blue;
}

/* Disabled */
QWidget:disabled {
    color: gray;
}

/* Checked (for checkboxes, radio buttons) */
QCheckBox:checked {
    color: green;
}

/* Selected items in lists */
QListWidget::item:selected {
    background-color: #0078d4;
    color: white;
}
```

### Sub-Controls

Style specific parts of complex widgets:

```css
/* Scroll bar components */
QScrollBar:vertical {
    width: 12px;
    background: #f0f0f0;
}

QScrollBar::handle:vertical {
    background: #c0c0c0;
    min-height: 20px;
    border-radius: 6px;
}

QScrollBar::add-line:vertical,
QScrollBar::sub-line:vertical {
    height: 0px;
}

/* Combo box dropdown */
QComboBox::drop-down {
    width: 20px;
    border: none;
}

QComboBox::down-arrow {
    image: url(down_arrow.png);
    width: 12px;
    height: 12px;
}

/* Tab bar */
QTabBar::tab {
    padding: 8px 16px;
    background: #e0e0e0;
}

QTabBar::tab:selected {
    background: white;
    border-bottom: 2px solid #0078d4;
}

/* Check box indicator */
QCheckBox::indicator {
    width: 18px;
    height: 18px;
}

QCheckBox::indicator:checked {
    image: url(checkbox_checked.png);
}
```

### Complete Theme Example

```python
DARK_THEME = """
/* Main window and containers */
QMainWindow, QDialog, QWidget {
    background-color: #1e1e1e;
    color: #d4d4d4;
}

/* Labels */
QLabel {
    color: #d4d4d4;
}

/* Buttons */
QPushButton {
    background-color: #0e639c;
    color: white;
    border: none;
    padding: 8px 16px;
    border-radius: 4px;
    font-size: 13px;
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

/* Text inputs */
QLineEdit, QTextEdit, QPlainTextEdit {
    background-color: #3c3c3c;
    color: #d4d4d4;
    border: 1px solid #3c3c3c;
    border-radius: 4px;
    padding: 6px;
    selection-background-color: #264f78;
}

QLineEdit:focus, QTextEdit:focus, QPlainTextEdit:focus {
    border: 1px solid #0e639c;
}

/* Combo boxes */
QComboBox {
    background-color: #3c3c3c;
    color: #d4d4d4;
    border: 1px solid #3c3c3c;
    border-radius: 4px;
    padding: 6px;
}

QComboBox:hover {
    border: 1px solid #0e639c;
}

QComboBox::drop-down {
    border: none;
    width: 20px;
}

QComboBox QAbstractItemView {
    background-color: #252526;
    color: #d4d4d4;
    selection-background-color: #0e639c;
}

/* Checkboxes and radio buttons */
QCheckBox, QRadioButton {
    color: #d4d4d4;
    spacing: 8px;
}

QCheckBox::indicator, QRadioButton::indicator {
    width: 18px;
    height: 18px;
}

/* Scroll bars */
QScrollBar:vertical {
    background: #1e1e1e;
    width: 12px;
}

QScrollBar::handle:vertical {
    background: #5a5a5a;
    border-radius: 6px;
    min-height: 20px;
}

QScrollBar::handle:vertical:hover {
    background: #6a6a6a;
}

/* Tables and lists */
QTableView, QListView, QTreeView {
    background-color: #252526;
    color: #d4d4d4;
    border: 1px solid #3c3c3c;
    gridline-color: #3c3c3c;
}

QTableView::item:selected, QListView::item:selected, QTreeView::item:selected {
    background-color: #0e639c;
}

QHeaderView::section {
    background-color: #333333;
    color: #d4d4d4;
    padding: 8px;
    border: none;
    border-right: 1px solid #3c3c3c;
}

/* Tab widget */
QTabWidget::pane {
    border: 1px solid #3c3c3c;
    background-color: #1e1e1e;
}

QTabBar::tab {
    background-color: #2d2d2d;
    color: #808080;
    padding: 10px 20px;
    border: none;
}

QTabBar::tab:selected {
    background-color: #1e1e1e;
    color: #d4d4d4;
    border-bottom: 2px solid #0e639c;
}

QTabBar::tab:hover:!selected {
    background-color: #383838;
}

/* Menu bar */
QMenuBar {
    background-color: #1e1e1e;
    color: #d4d4d4;
}

QMenuBar::item:selected {
    background-color: #3c3c3c;
}

QMenu {
    background-color: #252526;
    color: #d4d4d4;
    border: 1px solid #3c3c3c;
}

QMenu::item:selected {
    background-color: #0e639c;
}

/* Progress bar */
QProgressBar {
    background-color: #3c3c3c;
    border-radius: 4px;
    text-align: center;
    color: #d4d4d4;
}

QProgressBar::chunk {
    background-color: #0e639c;
    border-radius: 4px;
}

/* Tooltips */
QToolTip {
    background-color: #252526;
    color: #d4d4d4;
    border: 1px solid #3c3c3c;
    padding: 4px;
}
"""

# Apply theme
app.setStyleSheet(DARK_THEME)
```

---

## 12. Menus, Toolbars, and Status Bars

### Menu Bar

```python
from PySide6.QtWidgets import QMainWindow, QMenuBar, QMenu
from PySide6.QtGui import QAction, QKeySequence

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.create_menus()
    
    def create_menus(self):
        # Get menu bar
        menubar = self.menuBar()
        
        # File menu
        file_menu = menubar.addMenu("&File")
        
        # Actions
        new_action = QAction("&New", self)
        new_action.setShortcut(QKeySequence.StandardKey.New)
        new_action.setStatusTip("Create a new file")
        new_action.triggered.connect(self.new_file)
        file_menu.addAction(new_action)
        
        open_action = QAction("&Open...", self)
        open_action.setShortcut(QKeySequence.StandardKey.Open)
        open_action.triggered.connect(self.open_file)
        file_menu.addAction(open_action)
        
        save_action = QAction("&Save", self)
        save_action.setShortcut(QKeySequence.StandardKey.Save)
        save_action.triggered.connect(self.save_file)
        file_menu.addAction(save_action)
        
        file_menu.addSeparator()
        
        exit_action = QAction("E&xit", self)
        exit_action.setShortcut(QKeySequence.StandardKey.Quit)
        exit_action.triggered.connect(self.close)
        file_menu.addAction(exit_action)
        
        # Edit menu
        edit_menu = menubar.addMenu("&Edit")
        
        undo_action = QAction("&Undo", self)
        undo_action.setShortcut(QKeySequence.StandardKey.Undo)
        edit_menu.addAction(undo_action)
        
        redo_action = QAction("&Redo", self)
        redo_action.setShortcut(QKeySequence.StandardKey.Redo)
        edit_menu.addAction(redo_action)
        
        edit_menu.addSeparator()
        
        # Submenu
        format_menu = edit_menu.addMenu("&Format")
        format_menu.addAction(QAction("Bold", self))
        format_menu.addAction(QAction("Italic", self))
        format_menu.addAction(QAction("Underline", self))
        
        # View menu with checkable actions
        view_menu = menubar.addMenu("&View")
        
        toolbar_action = QAction("&Toolbar", self)
        toolbar_action.setCheckable(True)
        toolbar_action.setChecked(True)
        toolbar_action.triggered.connect(self.toggle_toolbar)
        view_menu.addAction(toolbar_action)
        
        statusbar_action = QAction("&Status Bar", self)
        statusbar_action.setCheckable(True)
        statusbar_action.setChecked(True)
        statusbar_action.triggered.connect(self.toggle_statusbar)
        view_menu.addAction(statusbar_action)
    
    def new_file(self):
        print("New file")
    
    def open_file(self):
        print("Open file")
    
    def save_file(self):
        print("Save file")
    
    def toggle_toolbar(self, checked):
        self.toolbar.setVisible(checked)
    
    def toggle_statusbar(self, checked):
        self.statusBar().setVisible(checked)
```

### Context Menus

```python
from PySide6.QtWidgets import QWidget, QMenu
from PySide6.QtCore import Qt

class ContextMenuWidget(QWidget):
    def __init__(self):
        super().__init__()
        self.setContextMenuPolicy(Qt.ContextMenuPolicy.CustomContextMenu)
        self.customContextMenuRequested.connect(self.show_context_menu)
    
    def show_context_menu(self, position):
        menu = QMenu(self)
        
        cut_action = menu.addAction("Cut")
        copy_action = menu.addAction("Copy")
        paste_action = menu.addAction("Paste")
        
        menu.addSeparator()
        
        delete_action = menu.addAction("Delete")
        
        # Show menu and get selected action
        action = menu.exec(self.mapToGlobal(position))
        
        if action == cut_action:
            print("Cut selected")
        elif action == copy_action:
            print("Copy selected")
        # ... etc
```

### Toolbars

```python
from PySide6.QtWidgets import QToolBar
from PySide6.QtGui import QAction, QIcon
from PySide6.QtCore import Qt

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.create_toolbar()
    
    def create_toolbar(self):
        # Create toolbar
        self.toolbar = QToolBar("Main Toolbar")
        self.toolbar.setMovable(True)
        self.toolbar.setIconSize(QSize(24, 24))
        self.addToolBar(Qt.ToolBarArea.TopToolBarArea, self.toolbar)
        
        # Add actions
        new_action = QAction(QIcon("icons/new.png"), "New", self)
        new_action.setToolTip("Create new file (Ctrl+N)")
        new_action.triggered.connect(self.new_file)
        self.toolbar.addAction(new_action)
        
        open_action = QAction(QIcon("icons/open.png"), "Open", self)
        open_action.triggered.connect(self.open_file)
        self.toolbar.addAction(open_action)
        
        save_action = QAction(QIcon("icons/save.png"), "Save", self)
        save_action.triggered.connect(self.save_file)
        self.toolbar.addAction(save_action)
        
        self.toolbar.addSeparator()
        
        # Add widget to toolbar
        from PySide6.QtWidgets import QLineEdit
        search_input = QLineEdit()
        search_input.setPlaceholderText("Search...")
        search_input.setMaximumWidth(200)
        self.toolbar.addWidget(search_input)
```

### Status Bar

```python
from PySide6.QtWidgets import QStatusBar, QLabel, QProgressBar

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.create_statusbar()
    
    def create_statusbar(self):
        # Get status bar
        statusbar = self.statusBar()
        
        # Temporary message (disappears after timeout)
        statusbar.showMessage("Ready", 3000)  # 3 seconds
        
        # Permanent widgets
        self.status_label = QLabel("Line: 1, Col: 1")
        statusbar.addPermanentWidget(self.status_label)
        
        self.progress = QProgressBar()
        self.progress.setMaximumWidth(150)
        self.progress.setVisible(False)
        statusbar.addPermanentWidget(self.progress)
    
    def update_cursor_position(self, line, col):
        self.status_label.setText(f"Line: {line}, Col: {col}")
    
    def show_progress(self, visible):
        self.progress.setVisible(visible)
    
    def set_progress(self, value):
        self.progress.setValue(value)
```

---

## 13. Working with Files

### Reading and Writing Text Files

```python
from PySide6.QtCore import QFile, QTextStream, QIODevice

# Using Qt classes
def read_file_qt(path):
    file = QFile(path)
    if file.open(QIODevice.OpenModeFlag.ReadOnly | QIODevice.OpenModeFlag.Text):
        stream = QTextStream(file)
        content = stream.readAll()
        file.close()
        return content
    return None

def write_file_qt(path, content):
    file = QFile(path)
    if file.open(QIODevice.OpenModeFlag.WriteOnly | QIODevice.OpenModeFlag.Text):
        stream = QTextStream(file)
        stream << content
        file.close()
        return True
    return False

# Using Python (recommended for simplicity)
def read_file(path):
    with open(path, 'r', encoding='utf-8') as f:
        return f.read()

def write_file(path, content):
    with open(path, 'w', encoding='utf-8') as f:
        f.write(content)
```

### File Dialog Integration

```python
from PySide6.QtWidgets import QMainWindow, QTextEdit, QFileDialog, QMessageBox

class TextEditor(QMainWindow):
    def __init__(self):
        super().__init__()
        self.current_file = None
        
        self.editor = QTextEdit()
        self.setCentralWidget(self.editor)
        
        self.create_menus()
    
    def create_menus(self):
        file_menu = self.menuBar().addMenu("File")
        file_menu.addAction("New", self.new_file)
        file_menu.addAction("Open...", self.open_file)
        file_menu.addAction("Save", self.save_file)
        file_menu.addAction("Save As...", self.save_file_as)
    
    def new_file(self):
        if self.maybe_save():
            self.editor.clear()
            self.current_file = None
            self.setWindowTitle("Untitled")
    
    def open_file(self):
        if self.maybe_save():
            path, _ = QFileDialog.getOpenFileName(
                self, "Open File", "",
                "Text Files (*.txt);;All Files (*)"
            )
            if path:
                self.load_file(path)
    
    def load_file(self, path):
        try:
            with open(path, 'r', encoding='utf-8') as f:
                self.editor.setPlainText(f.read())
            self.current_file = path
            self.setWindowTitle(path)
        except Exception as e:
            QMessageBox.critical(self, "Error", f"Could not open file:\n{e}")
    
    def save_file(self):
        if self.current_file:
            return self.save_to_file(self.current_file)
        return self.save_file_as()
    
    def save_file_as(self):
        path, _ = QFileDialog.getSaveFileName(
            self, "Save File", "",
            "Text Files (*.txt);;All Files (*)"
        )
        if path:
            return self.save_to_file(path)
        return False
    
    def save_to_file(self, path):
        try:
            with open(path, 'w', encoding='utf-8') as f:
                f.write(self.editor.toPlainText())
            self.current_file = path
            self.setWindowTitle(path)
            return True
        except Exception as e:
            QMessageBox.critical(self, "Error", f"Could not save file:\n{e}")
            return False
    
    def maybe_save(self):
        if not self.editor.document().isModified():
            return True
        
        result = QMessageBox.warning(
            self, "Unsaved Changes",
            "Do you want to save changes?",
            QMessageBox.StandardButton.Save |
            QMessageBox.StandardButton.Discard |
            QMessageBox.StandardButton.Cancel
        )
        
        if result == QMessageBox.StandardButton.Save:
            return self.save_file()
        elif result == QMessageBox.StandardButton.Cancel:
            return False
        return True
```

### Binary Files

```python
from PySide6.QtCore import QFile, QDataStream, QIODevice

def write_binary(path, data):
    file = QFile(path)
    if file.open(QIODevice.OpenModeFlag.WriteOnly):
        stream = QDataStream(file)
        
        # Write different data types
        stream.writeInt32(42)
        stream.writeFloat(3.14)
        stream.writeQString("Hello")
        stream.writeBytes(b"Binary data")
        
        file.close()

def read_binary(path):
    file = QFile(path)
    if file.open(QIODevice.OpenModeFlag.ReadOnly):
        stream = QDataStream(file)
        
        integer = stream.readInt32()
        floating = stream.readFloat()
        string = stream.readQString()
        binary = stream.readBytes()
        
        file.close()
        return integer, floating, string, binary
```

---

## 14. Settings and Preferences

### QSettings - Persistent Settings

```python
from PySide6.QtCore import QSettings

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        
        # Initialize settings
        self.settings = QSettings("MyCompany", "MyApp")
        
        self.load_settings()
    
    def load_settings(self):
        # Window geometry
        geometry = self.settings.value("geometry")
        if geometry:
            self.restoreGeometry(geometry)
        
        # Window state
        state = self.settings.value("windowState")
        if state:
            self.restoreState(state)
        
        # Custom settings
        self.recent_files = self.settings.value("recentFiles", [])
        self.font_size = int(self.settings.value("fontSize", 12))
        self.theme = self.settings.value("theme", "light")
    
    def save_settings(self):
        # Window geometry
        self.settings.setValue("geometry", self.saveGeometry())
        self.settings.setValue("windowState", self.saveState())
        
        # Custom settings
        self.settings.setValue("recentFiles", self.recent_files)
        self.settings.setValue("fontSize", self.font_size)
        self.settings.setValue("theme", self.theme)
    
    def closeEvent(self, event):
        self.save_settings()
        event.accept()
```

### Settings with Groups

```python
settings = QSettings("MyCompany", "MyApp")

# Use groups for organization
settings.beginGroup("Editor")
settings.setValue("fontSize", 14)
settings.setValue("fontFamily", "Consolas")
settings.setValue("wordWrap", True)
settings.endGroup()

settings.beginGroup("Window")
settings.setValue("maximized", False)
settings.setValue("width", 800)
settings.setValue("height", 600)
settings.endGroup()

# Read grouped settings
settings.beginGroup("Editor")
font_size = settings.value("fontSize", 12, type=int)
settings.endGroup()
```

### Preferences Dialog

```python
from PySide6.QtWidgets import (
    QDialog, QVBoxLayout, QHBoxLayout, QTabWidget, QWidget,
    QFormLayout, QSpinBox, QComboBox, QCheckBox, QFontComboBox,
    QDialogButtonBox
)

class PreferencesDialog(QDialog):
    def __init__(self, settings, parent=None):
        super().__init__(parent)
        self.settings = settings
        self.setWindowTitle("Preferences")
        self.setup_ui()
        self.load_settings()
    
    def setup_ui(self):
        layout = QVBoxLayout(self)
        
        # Tab widget
        tabs = QTabWidget()
        
        # General tab
        general_tab = QWidget()
        general_layout = QFormLayout(general_tab)
        
        self.theme_combo = QComboBox()
        self.theme_combo.addItems(["Light", "Dark", "System"])
        general_layout.addRow("Theme:", self.theme_combo)
        
        self.language_combo = QComboBox()
        self.language_combo.addItems(["English", "Spanish", "French", "German"])
        general_layout.addRow("Language:", self.language_combo)
        
        tabs.addTab(general_tab, "General")
        
        # Editor tab
        editor_tab = QWidget()
        editor_layout = QFormLayout(editor_tab)
        
        self.font_combo = QFontComboBox()
        editor_layout.addRow("Font:", self.font_combo)
        
        self.font_size_spin = QSpinBox()
        self.font_size_spin.setRange(8, 72)
        editor_layout.addRow("Font Size:", self.font_size_spin)
        
        self.word_wrap_check = QCheckBox()
        editor_layout.addRow("Word Wrap:", self.word_wrap_check)
        
        self.line_numbers_check = QCheckBox()
        editor_layout.addRow("Line Numbers:", self.line_numbers_check)
        
        tabs.addTab(editor_tab, "Editor")
        
        layout.addWidget(tabs)
        
        # Buttons
        button_box = QDialogButtonBox(
            QDialogButtonBox.StandardButton.Ok |
            QDialogButtonBox.StandardButton.Cancel |
            QDialogButtonBox.StandardButton.Apply
        )
        button_box.accepted.connect(self.accept)
        button_box.rejected.connect(self.reject)
        button_box.button(QDialogButtonBox.StandardButton.Apply).clicked.connect(self.apply_settings)
        layout.addWidget(button_box)
    
    def load_settings(self):
        self.theme_combo.setCurrentText(self.settings.value("theme", "Light"))
        self.language_combo.setCurrentText(self.settings.value("language", "English"))
        
        self.settings.beginGroup("Editor")
        self.font_combo.setCurrentText(self.settings.value("fontFamily", "Monospace"))
        self.font_size_spin.setValue(int(self.settings.value("fontSize", 12)))
        self.word_wrap_check.setChecked(self.settings.value("wordWrap", True, type=bool))
        self.line_numbers_check.setChecked(self.settings.value("lineNumbers", True, type=bool))
        self.settings.endGroup()
    
    def apply_settings(self):
        self.settings.setValue("theme", self.theme_combo.currentText())
        self.settings.setValue("language", self.language_combo.currentText())
        
        self.settings.beginGroup("Editor")
        self.settings.setValue("fontFamily", self.font_combo.currentText())
        self.settings.setValue("fontSize", self.font_size_spin.value())
        self.settings.setValue("wordWrap", self.word_wrap_check.isChecked())
        self.settings.setValue("lineNumbers", self.line_numbers_check.isChecked())
        self.settings.endGroup()
    
    def accept(self):
        self.apply_settings()
        super().accept()
```

---

# Part 3: Advanced Level

---

## 15. Graphics View Framework

### Overview

The Graphics View Framework provides a surface for managing and interacting with a large number of custom 2D graphical items.

```
┌─────────────────────────────────────────────────┐
│                 QGraphicsView                    │
│  (Widget that displays the scene)               │
│                                                  │
│  ┌──────────────────────────────────────────┐   │
│  │           QGraphicsScene                  │   │
│  │  (Container for graphics items)          │   │
│  │                                          │   │
│  │   ┌─────┐  ┌─────────┐  ┌───────────┐   │   │
│  │   │Item │  │  Item   │  │   Item    │   │   │
│  │   └─────┘  └─────────┘  └───────────┘   │   │
│  │                                          │   │
│  └──────────────────────────────────────────┘   │
└─────────────────────────────────────────────────┘
```

### Basic Setup

```python
from PySide6.QtWidgets import (
    QGraphicsView, QGraphicsScene, QGraphicsRectItem,
    QGraphicsEllipseItem, QGraphicsTextItem
)
from PySide6.QtCore import Qt
from PySide6.QtGui import QBrush, QPen, QColor

# Create scene
scene = QGraphicsScene()
scene.setSceneRect(-400, -300, 800, 600)  # Set scene bounds

# Add items
rect = QGraphicsRectItem(0, 0, 100, 50)
rect.setBrush(QBrush(QColor(100, 149, 237)))
rect.setPen(QPen(Qt.GlobalColor.black, 2))
rect.setPos(-50, -25)  # Center it
scene.addItem(rect)

ellipse = QGraphicsEllipseItem(0, 0, 80, 80)
ellipse.setBrush(QBrush(QColor(255, 165, 0)))
ellipse.setPos(100, 50)
scene.addItem(ellipse)

text = QGraphicsTextItem("Hello Graphics!")
text.setPos(-50, -80)
scene.addItem(text)

# Create view
view = QGraphicsView(scene)
view.setRenderHint(QPainter.RenderHint.Antialiasing)
view.setDragMode(QGraphicsView.DragMode.ScrollHandDrag)
view.show()
```

### Custom Graphics Items

```python
from PySide6.QtWidgets import QGraphicsItem
from PySide6.QtCore import QRectF, Qt
from PySide6.QtGui import QPainter, QPainterPath

class CustomShape(QGraphicsItem):
    def __init__(self, parent=None):
        super().__init__(parent)
        self.setFlag(QGraphicsItem.GraphicsItemFlag.ItemIsMovable)
        self.setFlag(QGraphicsItem.GraphicsItemFlag.ItemIsSelectable)
        self.setFlag(QGraphicsItem.GraphicsItemFlag.ItemSendsGeometryChanges)
        
        self._color = QColor(100, 149, 237)
        self._width = 100
        self._height = 60
    
    def boundingRect(self):
        """Define the item's bounding rectangle."""
        return QRectF(-self._width/2, -self._height/2, 
                      self._width, self._height)
    
    def paint(self, painter, option, widget):
        """Paint the item."""
        painter.setRenderHint(QPainter.RenderHint.Antialiasing)
        
        # Draw shadow when selected
        if self.isSelected():
            painter.setPen(QPen(Qt.GlobalColor.blue, 2, Qt.PenStyle.DashLine))
        else:
            painter.setPen(QPen(Qt.GlobalColor.black, 1))
        
        painter.setBrush(QBrush(self._color))
        
        # Draw rounded rectangle
        painter.drawRoundedRect(self.boundingRect(), 10, 10)
    
    def shape(self):
        """Define the item's shape for collision detection."""
        path = QPainterPath()
        path.addRoundedRect(self.boundingRect(), 10, 10)
        return path
    
    def mousePressEvent(self, event):
        print(f"Item clicked at {event.pos()}")
        super().mousePressEvent(event)
    
    def mouseDoubleClickEvent(self, event):
        # Toggle color on double-click
        if self._color == QColor(100, 149, 237):
            self._color = QColor(255, 99, 71)
        else:
            self._color = QColor(100, 149, 237)
        self.update()
```

### Interactive Drawing Application

```python
from PySide6.QtWidgets import (
    QMainWindow, QGraphicsView, QGraphicsScene, QToolBar,
    QColorDialog
)
from PySide6.QtCore import Qt, QPointF
from PySide6.QtGui import QPen, QColor, QPainter

class DrawingScene(QGraphicsScene):
    def __init__(self):
        super().__init__()
        self.drawing = False
        self.current_path = None
        self.pen_color = QColor(Qt.GlobalColor.black)
        self.pen_width = 2
    
    def mousePressEvent(self, event):
        if event.button() == Qt.MouseButton.LeftButton:
            self.drawing = True
            pos = event.scenePos()
            self.current_path = QPainterPath(pos)
            pen = QPen(self.pen_color, self.pen_width)
            pen.setCapStyle(Qt.PenCapStyle.RoundCap)
            self.path_item = self.addPath(self.current_path, pen)
        super().mousePressEvent(event)
    
    def mouseMoveEvent(self, event):
        if self.drawing and self.current_path:
            self.current_path.lineTo(event.scenePos())
            self.path_item.setPath(self.current_path)
        super().mouseMoveEvent(event)
    
    def mouseReleaseEvent(self, event):
        self.drawing = False
        self.current_path = None
        super().mouseReleaseEvent(event)

class DrawingApp(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Drawing App")
        
        self.scene = DrawingScene()
        self.scene.setSceneRect(-500, -500, 1000, 1000)
        
        self.view = QGraphicsView(self.scene)
        self.view.setRenderHint(QPainter.RenderHint.Antialiasing)
        self.setCentralWidget(self.view)
        
        self.create_toolbar()
    
    def create_toolbar(self):
        toolbar = QToolBar()
        self.addToolBar(toolbar)
        
        toolbar.addAction("Clear", self.scene.clear)
        toolbar.addAction("Color", self.choose_color)
    
    def choose_color(self):
        color = QColorDialog.getColor(self.scene.pen_color, self)
        if color.isValid():
            self.scene.pen_color = color
```

---

## 16. Animations and State Machines

### Property Animations

```python
from PySide6.QtCore import QPropertyAnimation, QEasingCurve, QPoint, QSize
from PySide6.QtWidgets import QPushButton

# Animate button position
button = QPushButton("Animated")
button.setGeometry(0, 0, 100, 50)

animation = QPropertyAnimation(button, b"pos")
animation.setDuration(1000)  # 1 second
animation.setStartValue(QPoint(0, 0))
animation.setEndValue(QPoint(200, 100))
animation.setEasingCurve(QEasingCurve.Type.OutBounce)
animation.start()

# Animate size
size_anim = QPropertyAnimation(button, b"size")
size_anim.setDuration(500)
size_anim.setStartValue(QSize(100, 50))
size_anim.setEndValue(QSize(150, 75))
size_anim.start()
```

### Sequential and Parallel Animations

```python
from PySide6.QtCore import (
    QSequentialAnimationGroup, QParallelAnimationGroup,
    QPropertyAnimation, QPauseAnimation
)

# Sequential: one after another
seq_group = QSequentialAnimationGroup()

move_right = QPropertyAnimation(button, b"pos")
move_right.setDuration(500)
move_right.setEndValue(QPoint(200, 0))

move_down = QPropertyAnimation(button, b"pos")
move_down.setDuration(500)
move_down.setEndValue(QPoint(200, 200))

seq_group.addAnimation(move_right)
seq_group.addAnimation(QPauseAnimation(200))  # Pause 200ms
seq_group.addAnimation(move_down)
seq_group.start()

# Parallel: simultaneously
par_group = QParallelAnimationGroup()

pos_anim = QPropertyAnimation(button, b"pos")
pos_anim.setDuration(1000)
pos_anim.setEndValue(QPoint(200, 200))

size_anim = QPropertyAnimation(button, b"size")
size_anim.setDuration(1000)
size_anim.setEndValue(QSize(150, 75))

par_group.addAnimation(pos_anim)
par_group.addAnimation(size_anim)
par_group.start()
```

### Custom Animated Widget

```python
from PySide6.QtWidgets import QWidget
from PySide6.QtCore import Property, QPropertyAnimation, QEasingCurve
from PySide6.QtGui import QPainter, QColor

class PulsatingCircle(QWidget):
    def __init__(self):
        super().__init__()
        self._radius = 50
        self._color = QColor(100, 149, 237)
        
        self.setMinimumSize(200, 200)
        
        # Create pulsating animation
        self.animation = QPropertyAnimation(self, b"radius")
        self.animation.setDuration(1000)
        self.animation.setStartValue(30)
        self.animation.setEndValue(80)
        self.animation.setEasingCurve(QEasingCurve.Type.InOutSine)
        self.animation.setLoopCount(-1)  # Infinite loop
        self.animation.start()
    
    def get_radius(self):
        return self._radius
    
    def set_radius(self, value):
        self._radius = value
        self.update()  # Trigger repaint
    
    radius = Property(int, get_radius, set_radius)
    
    def paintEvent(self, event):
        painter = QPainter(self)
        painter.setRenderHint(QPainter.RenderHint.Antialiasing)
        
        painter.setBrush(self._color)
        painter.setPen(Qt.PenStyle.NoPen)
        
        center = self.rect().center()
        painter.drawEllipse(center, self._radius, self._radius)
```

### State Machines

```python
from PySide6.QtCore import QState, QStateMachine, QPropertyAnimation
from PySide6.QtWidgets import QPushButton

# Create state machine
machine = QStateMachine()

# Define states
state1 = QState()
state1.assignProperty(button, "geometry", QRect(0, 0, 100, 50))
state1.assignProperty(button, "styleSheet", "background: blue; color: white;")

state2 = QState()
state2.assignProperty(button, "geometry", QRect(200, 100, 150, 75))
state2.assignProperty(button, "styleSheet", "background: green; color: white;")

state3 = QState()
state3.assignProperty(button, "geometry", QRect(100, 200, 120, 60))
state3.assignProperty(button, "styleSheet", "background: red; color: white;")

# Add transitions
state1.addTransition(button.clicked, state2)
state2.addTransition(button.clicked, state3)
state3.addTransition(button.clicked, state1)

# Add states to machine
machine.addState(state1)
machine.addState(state2)
machine.addState(state3)
machine.setInitialState(state1)

# Add animations to transitions
for state in [state1, state2, state3]:
    for transition in state.transitions():
        animation = QPropertyAnimation(button, b"geometry")
        animation.setDuration(500)
        transition.addAnimation(animation)

# Start machine
machine.start()
```

---

## 17. QML and Qt Quick Integration

### What is QML?

QML is a declarative language for designing dynamic, animated user interfaces.

### Basic QML File (main.qml)

```qml
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    id: window
    width: 400
    height: 300
    visible: true
    title: "QML Example"
    
    ColumnLayout {
        anchors.centerIn: parent
        spacing: 20
        
        Label {
            text: "Hello from QML!"
            font.pixelSize: 24
            Layout.alignment: Qt.AlignHCenter
        }
        
        Button {
            text: "Click Me"
            Layout.alignment: Qt.AlignHCenter
            onClicked: {
                counter.count++
            }
        }
        
        Label {
            id: counter
            property int count: 0
            text: "Clicked: " + count + " times"
            font.pixelSize: 16
            Layout.alignment: Qt.AlignHCenter
        }
    }
}
```

### Loading QML from Python

```python
import sys
from PySide6.QtWidgets import QApplication
from PySide6.QtQml import QQmlApplicationEngine

app = QApplication(sys.argv)

engine = QQmlApplicationEngine()
engine.load("main.qml")

if not engine.rootObjects():
    sys.exit(-1)

sys.exit(app.exec())
```

### Python-QML Communication

```python
from PySide6.QtCore import QObject, Signal, Slot, Property

class Backend(QObject):
    countChanged = Signal()
    
    def __init__(self):
        super().__init__()
        self._count = 0
    
    @Property(int, notify=countChanged)
    def count(self):
        return self._count
    
    @count.setter
    def count(self, value):
        if self._count != value:
            self._count = value
            self.countChanged.emit()
    
    @Slot()
    def increment(self):
        self.count += 1
    
    @Slot(str, result=str)
    def process(self, text):
        return text.upper()

# Register and use in QML
backend = Backend()
engine.rootContext().setContextProperty("backend", backend)
```

```qml
// In QML
Button {
    text: "Count: " + backend.count
    onClicked: backend.increment()
}

TextField {
    id: input
    onTextChanged: {
        result.text = backend.process(text)
    }
}
Label {
    id: result
}
```

### QML with Custom Types

```python
from PySide6.QtQml import qmlRegisterType

# Register Python class for use in QML
qmlRegisterType(MyCustomClass, "MyModule", 1, 0, "MyCustomClass")
```

```qml
import MyModule 1.0

MyCustomClass {
    id: custom
    someProperty: "value"
}
```

---

## 18. Database Connectivity

### SQLite with Qt SQL

```python
from PySide6.QtSql import QSqlDatabase, QSqlQuery, QSqlTableModel
from PySide6.QtWidgets import QTableView

# Connect to database
db = QSqlDatabase.addDatabase("QSQLITE")
db.setDatabaseName("myapp.db")

if not db.open():
    print(f"Cannot open database: {db.lastError().text()}")

# Create table
query = QSqlQuery()
query.exec("""
    CREATE TABLE IF NOT EXISTS users (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        name TEXT NOT NULL,
        email TEXT UNIQUE,
        age INTEGER
    )
""")

# Insert data
query.prepare("INSERT INTO users (name, email, age) VALUES (?, ?, ?)")
query.addBindValue("Alice")
query.addBindValue("alice@example.com")
query.addBindValue(30)
query.exec()

# Query data
query.exec("SELECT * FROM users")
while query.next():
    id = query.value(0)
    name = query.value(1)
    email = query.value(2)
    age = query.value(3)
    print(f"{id}: {name}, {email}, {age}")
```

### Table Model with Database

```python
from PySide6.QtSql import QSqlTableModel, QSqlRelationalTableModel
from PySide6.QtWidgets import QTableView

# Create model
model = QSqlTableModel()
model.setTable("users")
model.setEditStrategy(QSqlTableModel.EditStrategy.OnFieldChange)
model.select()

# Set column headers
model.setHeaderData(0, Qt.Orientation.Horizontal, "ID")
model.setHeaderData(1, Qt.Orientation.Horizontal, "Name")
model.setHeaderData(2, Qt.Orientation.Horizontal, "Email")
model.setHeaderData(3, Qt.Orientation.Horizontal, "Age")

# Create view
view = QTableView()
view.setModel(model)
view.hideColumn(0)  # Hide ID column
view.resizeColumnsToContents()

# Add new record
record = model.record()
record.setValue("name", "Bob")
record.setValue("email", "bob@example.com")
record.setValue("age", 25)
model.insertRecord(-1, record)

# Delete record
model.removeRow(selected_row)

# Filter and sort
model.setFilter("age > 20")
model.setSort(1, Qt.SortOrder.AscendingOrder)
model.select()
```

### Database Manager Class

```python
from PySide6.QtSql import QSqlDatabase, QSqlQuery
from PySide6.QtCore import QObject, Signal

class DatabaseManager(QObject):
    error_occurred = Signal(str)
    
    def __init__(self, db_path="app.db"):
        super().__init__()
        self.db_path = db_path
        self.db = None
    
    def connect(self):
        self.db = QSqlDatabase.addDatabase("QSQLITE")
        self.db.setDatabaseName(self.db_path)
        
        if not self.db.open():
            self.error_occurred.emit(self.db.lastError().text())
            return False
        
        self.create_tables()
        return True
    
    def create_tables(self):
        query = QSqlQuery()
        query.exec("""
            CREATE TABLE IF NOT EXISTS tasks (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                title TEXT NOT NULL,
                description TEXT,
                completed INTEGER DEFAULT 0,
                created_at DATETIME DEFAULT CURRENT_TIMESTAMP
            )
        """)
    
    def add_task(self, title, description=""):
        query = QSqlQuery()
        query.prepare("INSERT INTO tasks (title, description) VALUES (?, ?)")
        query.addBindValue(title)
        query.addBindValue(description)
        
        if not query.exec():
            self.error_occurred.emit(query.lastError().text())
            return None
        
        return query.lastInsertId()
    
    def get_tasks(self, include_completed=True):
        query = QSqlQuery()
        
        if include_completed:
            query.exec("SELECT * FROM tasks ORDER BY created_at DESC")
        else:
            query.exec("SELECT * FROM tasks WHERE completed = 0 ORDER BY created_at DESC")
        
        tasks = []
        while query.next():
            tasks.append({
                "id": query.value(0),
                "title": query.value(1),
                "description": query.value(2),
                "completed": bool(query.value(3)),
                "created_at": query.value(4)
            })
        
        return tasks
    
    def complete_task(self, task_id):
        query = QSqlQuery()
        query.prepare("UPDATE tasks SET completed = 1 WHERE id = ?")
        query.addBindValue(task_id)
        return query.exec()
    
    def delete_task(self, task_id):
        query = QSqlQuery()
        query.prepare("DELETE FROM tasks WHERE id = ?")
        query.addBindValue(task_id)
        return query.exec()
    
    def close(self):
        if self.db and self.db.isOpen():
            self.db.close()
```

---

## 19. Networking

### HTTP Requests with QNetworkAccessManager

```python
from PySide6.QtNetwork import QNetworkAccessManager, QNetworkRequest, QNetworkReply
from PySide6.QtCore import QUrl, QObject, Signal

class HttpClient(QObject):
    finished = Signal(str)
    error = Signal(str)
    
    def __init__(self):
        super().__init__()
        self.manager = QNetworkAccessManager()
        self.manager.finished.connect(self.on_finished)
    
    def get(self, url):
        request = QNetworkRequest(QUrl(url))
        self.manager.get(request)
    
    def post(self, url, data):
        request = QNetworkRequest(QUrl(url))
        request.setHeader(
            QNetworkRequest.KnownHeaders.ContentTypeHeader,
            "application/json"
        )
        self.manager.post(request, data.encode())
    
    def on_finished(self, reply):
        if reply.error() == QNetworkReply.NetworkError.NoError:
            data = reply.readAll().data().decode()
            self.finished.emit(data)
        else:
            self.error.emit(reply.errorString())
        
        reply.deleteLater()

# Usage
client = HttpClient()
client.finished.connect(lambda data: print(f"Response: {data}"))
client.error.connect(lambda err: print(f"Error: {err}"))
client.get("https://api.github.com/users/octocat")
```

### File Download

```python
from PySide6.QtNetwork import QNetworkAccessManager, QNetworkRequest
from PySide6.QtCore import QUrl, QFile, QIODevice

class Downloader(QObject):
    progress = Signal(int, int)  # bytes received, total bytes
    finished = Signal(str)
    error = Signal(str)
    
    def __init__(self):
        super().__init__()
        self.manager = QNetworkAccessManager()
        self.file = None
        self.reply = None
    
    def download(self, url, save_path):
        self.file = QFile(save_path)
        if not self.file.open(QIODevice.OpenModeFlag.WriteOnly):
            self.error.emit(f"Cannot open file: {save_path}")
            return
        
        request = QNetworkRequest(QUrl(url))
        self.reply = self.manager.get(request)
        self.reply.downloadProgress.connect(self.on_progress)
        self.reply.readyRead.connect(self.on_ready_read)
        self.reply.finished.connect(self.on_finished)
    
    def on_progress(self, received, total):
        self.progress.emit(received, total)
    
    def on_ready_read(self):
        if self.file:
            self.file.write(self.reply.readAll())
    
    def on_finished(self):
        if self.file:
            self.file.close()
        
        if self.reply.error() == QNetworkReply.NetworkError.NoError:
            self.finished.emit(self.file.fileName())
        else:
            self.error.emit(self.reply.errorString())
        
        self.reply.deleteLater()
```

### WebSocket Client

```python
from PySide6.QtWebSockets import QWebSocket
from PySide6.QtCore import QUrl

class WebSocketClient(QObject):
    connected = Signal()
    disconnected = Signal()
    message_received = Signal(str)
    error = Signal(str)
    
    def __init__(self):
        super().__init__()
        self.socket = QWebSocket()
        
        self.socket.connected.connect(self.on_connected)
        self.socket.disconnected.connect(self.on_disconnected)
        self.socket.textMessageReceived.connect(self.on_message)
        self.socket.errorOccurred.connect(self.on_error)
    
    def connect(self, url):
        self.socket.open(QUrl(url))
    
    def send(self, message):
        self.socket.sendTextMessage(message)
    
    def disconnect(self):
        self.socket.close()
    
    def on_connected(self):
        self.connected.emit()
    
    def on_disconnected(self):
        self.disconnected.emit()
    
    def on_message(self, message):
        self.message_received.emit(message)
    
    def on_error(self, error):
        self.error.emit(self.socket.errorString())

# Usage
ws = WebSocketClient()
ws.connected.connect(lambda: ws.send("Hello!"))
ws.message_received.connect(lambda msg: print(f"Received: {msg}"))
ws.connect("wss://echo.websocket.org")
```

---

## 20. Multimedia

### Playing Audio

```python
from PySide6.QtMultimedia import QMediaPlayer, QAudioOutput
from PySide6.QtCore import QUrl

player = QMediaPlayer()
audio_output = QAudioOutput()
player.setAudioOutput(audio_output)

# Load and play
player.setSource(QUrl.fromLocalFile("music.mp3"))
audio_output.setVolume(0.5)  # 50% volume
player.play()

# Control playback
player.pause()
player.stop()
player.setPosition(30000)  # Seek to 30 seconds
```

### Audio Player Widget

```python
from PySide6.QtWidgets import (
    QWidget, QHBoxLayout, QVBoxLayout, QPushButton, QSlider, QLabel
)
from PySide6.QtMultimedia import QMediaPlayer, QAudioOutput
from PySide6.QtCore import Qt, QUrl

class AudioPlayer(QWidget):
    def __init__(self):
        super().__init__()
        
        self.player = QMediaPlayer()
        self.audio_output = QAudioOutput()
        self.player.setAudioOutput(self.audio_output)
        
        self.setup_ui()
        self.connect_signals()
    
    def setup_ui(self):
        layout = QVBoxLayout(self)
        
        # Position slider
        self.position_slider = QSlider(Qt.Orientation.Horizontal)
        layout.addWidget(self.position_slider)
        
        # Time labels
        time_layout = QHBoxLayout()
        self.current_time = QLabel("0:00")
        self.total_time = QLabel("0:00")
        time_layout.addWidget(self.current_time)
        time_layout.addStretch()
        time_layout.addWidget(self.total_time)
        layout.addLayout(time_layout)
        
        # Controls
        controls = QHBoxLayout()
        
        self.play_btn = QPushButton("▶")
        self.stop_btn = QPushButton("⏹")
        
        self.volume_slider = QSlider(Qt.Orientation.Horizontal)
        self.volume_slider.setRange(0, 100)
        self.volume_slider.setValue(50)
        self.volume_slider.setMaximumWidth(100)
        
        controls.addWidget(self.play_btn)
        controls.addWidget(self.stop_btn)
        controls.addStretch()
        controls.addWidget(QLabel("🔊"))
        controls.addWidget(self.volume_slider)
        
        layout.addLayout(controls)
    
    def connect_signals(self):
        self.play_btn.clicked.connect(self.toggle_play)
        self.stop_btn.clicked.connect(self.player.stop)
        self.volume_slider.valueChanged.connect(
            lambda v: self.audio_output.setVolume(v / 100)
        )
        
        self.player.positionChanged.connect(self.update_position)
        self.player.durationChanged.connect(self.update_duration)
        self.position_slider.sliderMoved.connect(self.player.setPosition)
    
    def load(self, path):
        self.player.setSource(QUrl.fromLocalFile(path))
    
    def toggle_play(self):
        if self.player.playbackState() == QMediaPlayer.PlaybackState.PlayingState:
            self.player.pause()
            self.play_btn.setText("▶")
        else:
            self.player.play()
            self.play_btn.setText("⏸")
    
    def update_position(self, position):
        self.position_slider.setValue(position)
        self.current_time.setText(self.format_time(position))
    
    def update_duration(self, duration):
        self.position_slider.setRange(0, duration)
        self.total_time.setText(self.format_time(duration))
    
    def format_time(self, ms):
        s = ms // 1000
        m = s // 60
        s = s % 60
        return f"{m}:{s:02d}"
```

### Video Player

```python
from PySide6.QtMultimedia import QMediaPlayer, QAudioOutput
from PySide6.QtMultimediaWidgets import QVideoWidget

# Create video widget
video_widget = QVideoWidget()

# Create player
player = QMediaPlayer()
audio_output = QAudioOutput()
player.setAudioOutput(audio_output)
player.setVideoOutput(video_widget)

# Load and play video
player.setSource(QUrl.fromLocalFile("video.mp4"))
video_widget.show()
player.play()
```

### Complete Media Player with Repeat

Here's a full-featured media player that supports both audio and video files with repeat functionality:

```python
"""
Complete Audio/Video Media Player with PySide6
Features: Play, Pause, Stop, Seek, Volume, Repeat
"""

import sys
from pathlib import Path
from PySide6.QtWidgets import (
    QApplication, QMainWindow, QWidget, QVBoxLayout, QHBoxLayout,
    QPushButton, QSlider, QLabel, QFileDialog, QStyle, QSizePolicy,
    QCheckBox
)
from PySide6.QtCore import Qt, QUrl, Slot, QTime
from PySide6.QtGui import QAction, QKeySequence
from PySide6.QtMultimedia import QMediaPlayer, QAudioOutput
from PySide6.QtMultimediaWidgets import QVideoWidget


class MediaPlayer(QMainWindow):
    """A complete audio/video media player with repeat support."""
    
    def __init__(self):
        super().__init__()
        self.setWindowTitle("PySide6 Media Player")
        self.setMinimumSize(800, 600)
        
        # Initialize media player
        self.media_player = QMediaPlayer()
        self.audio_output = QAudioOutput()
        self.media_player.setAudioOutput(self.audio_output)
        self.audio_output.setVolume(0.5)
        
        # Track repeat state
        self.is_repeat = False
        
        self.setup_ui()
        self.setup_connections()
    
    def setup_ui(self):
        """Create the user interface."""
        central_widget = QWidget()
        self.setCentralWidget(central_widget)
        layout = QVBoxLayout(central_widget)
        
        # Video widget
        self.video_widget = QVideoWidget()
        self.video_widget.setMinimumHeight(300)
        self.media_player.setVideoOutput(self.video_widget)
        layout.addWidget(self.video_widget)
        
        # Seek slider with time labels
        seek_layout = QHBoxLayout()
        self.position_label = QLabel("00:00")
        self.seek_slider = QSlider(Qt.Orientation.Horizontal)
        self.duration_label = QLabel("00:00")
        seek_layout.addWidget(self.position_label)
        seek_layout.addWidget(self.seek_slider)
        seek_layout.addWidget(self.duration_label)
        layout.addLayout(seek_layout)
        
        # Controls
        controls = QHBoxLayout()
        
        self.open_btn = QPushButton("Open File")
        controls.addWidget(self.open_btn)
        
        self.play_btn = QPushButton()
        self.play_btn.setIcon(self.style().standardIcon(QStyle.StandardPixmap.SP_MediaPlay))
        controls.addWidget(self.play_btn)
        
        self.stop_btn = QPushButton()
        self.stop_btn.setIcon(self.style().standardIcon(QStyle.StandardPixmap.SP_MediaStop))
        controls.addWidget(self.stop_btn)
        
        # Repeat checkbox
        self.repeat_checkbox = QCheckBox("Repeat")
        controls.addWidget(self.repeat_checkbox)
        
        controls.addStretch()
        
        # Volume
        controls.addWidget(QLabel("Volume:"))
        self.volume_slider = QSlider(Qt.Orientation.Horizontal)
        self.volume_slider.setRange(0, 100)
        self.volume_slider.setValue(50)
        self.volume_slider.setMaximumWidth(100)
        controls.addWidget(self.volume_slider)
        
        layout.addLayout(controls)
    
    def setup_connections(self):
        """Connect signals and slots."""
        self.open_btn.clicked.connect(self.open_file)
        self.play_btn.clicked.connect(self.toggle_play)
        self.stop_btn.clicked.connect(self.media_player.stop)
        self.repeat_checkbox.toggled.connect(self.set_repeat)
        
        self.seek_slider.sliderMoved.connect(self.media_player.setPosition)
        self.volume_slider.valueChanged.connect(
            lambda v: self.audio_output.setVolume(v / 100)
        )
        
        self.media_player.positionChanged.connect(self.position_changed)
        self.media_player.durationChanged.connect(self.duration_changed)
        self.media_player.playbackStateChanged.connect(self.state_changed)
        self.media_player.mediaStatusChanged.connect(self.media_status_changed)
    
    @Slot()
    def open_file(self):
        """Open a media file."""
        path, _ = QFileDialog.getOpenFileName(
            self, "Open Media",  "",
            "Media Files (*.mp4 *.avi *.mkv *.mp3 *.wav *.ogg);;All Files (*)"
        )
        if path:
            self.media_player.setSource(QUrl.fromLocalFile(path))
            self.setWindowTitle(f"Media Player - {Path(path).name}")
            self.media_player.play()
    
    @Slot()
    def toggle_play(self):
        """Toggle play/pause."""
        if self.media_player.playbackState() == QMediaPlayer.PlaybackState.PlayingState:
            self.media_player.pause()
        else:
            self.media_player.play()
    
    @Slot(bool)
    def set_repeat(self, enabled):
        """Enable or disable repeat mode."""
        self.is_repeat = enabled
    
    @Slot(int)
    def position_changed(self, position):
        """Update position slider and label."""
        self.seek_slider.setValue(position)
        self.position_label.setText(self.format_time(position))
    
    @Slot(int)
    def duration_changed(self, duration):
        """Update duration slider range and label."""
        self.seek_slider.setRange(0, duration)
        self.duration_label.setText(self.format_time(duration))
    
    @Slot(QMediaPlayer.PlaybackState)
    def state_changed(self, state):
        """Update play button icon based on state."""
        if state == QMediaPlayer.PlaybackState.PlayingState:
            self.play_btn.setIcon(
                self.style().standardIcon(QStyle.StandardPixmap.SP_MediaPause)
            )
        else:
            self.play_btn.setIcon(
                self.style().standardIcon(QStyle.StandardPixmap.SP_MediaPlay)
            )
    
    @Slot(QMediaPlayer.MediaStatus)
    def media_status_changed(self, status):
        """Handle end of media - restart if repeat is enabled."""
        if status == QMediaPlayer.MediaStatus.EndOfMedia and self.is_repeat:
            self.media_player.setPosition(0)
            self.media_player.play()
    
    def format_time(self, ms):
        """Format milliseconds as MM:SS."""
        time = QTime(0, 0, 0).addMSecs(ms)
        return time.toString("mm:ss") if ms < 3600000 else time.toString("hh:mm:ss")
    
    def keyPressEvent(self, event):
        """Handle keyboard shortcuts."""
        if event.key() == Qt.Key.Key_Space:
            self.toggle_play()
        elif event.key() == Qt.Key.Key_Left:
            self.media_player.setPosition(max(0, self.media_player.position() - 5000))
        elif event.key() == Qt.Key.Key_Right:
            self.media_player.setPosition(
                min(self.media_player.duration(), self.media_player.position() + 5000)
            )


if __name__ == "__main__":
    app = QApplication(sys.argv)
    player = MediaPlayer()
    player.show()
    sys.exit(app.exec())
```

**Key Features:**

1. **QMediaPlayer** - The core class for media playback
2. **QAudioOutput** - Handles audio output with volume control
3. **QVideoWidget** - Displays video content
4. **Repeat Mode** - Uses `mediaStatusChanged` signal to detect end of media and restart
5. **Keyboard Shortcuts** - Space for play/pause, arrow keys for seeking

**Supported Formats:**
- Video: MP4, AVI, MKV, MOV, WMV, WebM
- Audio: MP3, WAV, OGG, FLAC, AAC, M4A

> **Example File:** See `pyside6_examples/03_advanced/06_media_player.py` for a more complete implementation with dark theme and additional features.

### Camera Access

```python
from PySide6.QtMultimedia import QCamera, QMediaCaptureSession, QImageCapture
from PySide6.QtMultimediaWidgets import QVideoWidget

# Get available cameras
cameras = QMediaDevices.videoInputs()
for cam in cameras:
    print(f"Camera: {cam.description()}")

# Setup camera
camera = QCamera(cameras[0] if cameras else None)
capture_session = QMediaCaptureSession()
capture_session.setCamera(camera)

# Video preview
viewfinder = QVideoWidget()
capture_session.setVideoOutput(viewfinder)

# Image capture
image_capture = QImageCapture()
capture_session.setImageCapture(image_capture)

# Start camera
camera.start()
viewfinder.show()

# Capture image
image_capture.capture()
image_capture.imageCaptured.connect(lambda id, img: img.save("photo.jpg"))
```

---

## 21. Packaging and Deployment

### PyInstaller

Create standalone executables:

```bash
# Install PyInstaller
pip install pyinstaller

# Basic usage
pyinstaller main.py

# Single file executable
pyinstaller --onefile main.py

# Without console window (Windows)
pyinstaller --onefile --windowed main.py

# With icon
pyinstaller --onefile --windowed --icon=app.ico main.py
```

### PyInstaller Spec File

```python
# main.spec
# -*- mode: python ; coding: utf-8 -*-

block_cipher = None

a = Analysis(
    ['main.py'],
    pathex=[],
    binaries=[],
    datas=[
        ('icons/*.png', 'icons'),
        ('styles/*.qss', 'styles'),
        ('translations/*.qm', 'translations'),
    ],
    hiddenimports=['PySide6.QtSvg'],
    hookspath=[],
    hooksconfig={},
    runtime_hooks=[],
    excludes=[],
    win_no_prefer_redirects=False,
    win_private_assemblies=False,
    cipher=block_cipher,
    noarchive=False,
)

pyz = PYZ(a.pure, a.zipped_data, cipher=block_cipher)

exe = EXE(
    pyz,
    a.scripts,
    a.binaries,
    a.zipfiles,
    a.datas,
    [],
    name='MyApp',
    debug=False,
    bootloader_ignore_signals=False,
    strip=False,
    upx=True,
    upx_exclude=[],
    runtime_tmpdir=None,
    console=False,
    disable_windowed_traceback=False,
    argv_emulation=False,
    target_arch=None,
    codesign_identity=None,
    entitlements_file=None,
    icon='app.ico',
)

# For macOS app bundle
app = BUNDLE(
    exe,
    name='MyApp.app',
    icon='app.icns',
    bundle_identifier='com.mycompany.myapp',
    info_plist={
        'NSHighResolutionCapable': 'True',
        'CFBundleShortVersionString': '1.0.0',
    },
)
```

### Nuitka (Alternative Compiler)

```bash
# Install Nuitka
pip install nuitka

# Compile
python -m nuitka --standalone --enable-plugin=pyside6 main.py

# For Windows GUI app
python -m nuitka --standalone --enable-plugin=pyside6 --windows-disable-console main.py
```

### Resource Management

Include resources properly:

```python
import sys
import os

def resource_path(relative_path):
    """Get absolute path to resource, works for dev and for PyInstaller."""
    if hasattr(sys, '_MEIPASS'):
        # PyInstaller creates a temp folder and stores path in _MEIPASS
        base_path = sys._MEIPASS
    else:
        base_path = os.path.abspath(".")
    
    return os.path.join(base_path, relative_path)

# Usage
icon_path = resource_path("icons/app.png")
style_path = resource_path("styles/dark.qss")
```

### Qt Resource System

Create a resource file (resources.qrc):

```xml
<!DOCTYPE RCC>
<RCC version="1.0">
    <qresource>
        <file>icons/new.png</file>
        <file>icons/open.png</file>
        <file>icons/save.png</file>
        <file>styles/dark.qss</file>
    </qresource>
</RCC>
```

Compile and use:

```bash
pyside6-rcc resources.qrc -o resources_rc.py
```

```python
import resources_rc  # Import compiled resources

# Access resources with :/ prefix
icon = QIcon(":/icons/new.png")
with open(":/styles/dark.qss") as f:
    stylesheet = f.read()
```

---

## Summary

This comprehensive tutorial covered PySide6 from the basics to advanced topics:

### Beginner Level
- Qt architecture and installation
- Basic widgets and layouts
- Signals and slots
- Dialogs and event handling

### Intermediate Level
- Custom widgets with painting
- Model-View programming
- Multithreading
- Styling with QSS
- Menus and toolbars
- File handling and settings

### Advanced Level
- Graphics View Framework
- Animations and state machines
- QML integration
- Database connectivity
- Networking
- Multimedia
- Packaging and deployment

### Next Steps

1. **Practice**: Build small projects to reinforce concepts
2. **Official Docs**: Refer to [Qt for Python documentation](https://doc.qt.io/qtforpython)
3. **Examples**: Study the examples included with PySide6
4. **Community**: Join Qt forums and Python GUI communities

Happy coding with PySide6!
