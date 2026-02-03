# PyQt6 Complete Tutorial
## From Beginner to Advanced

---

# Table of Contents

## Part 1: Beginner Level
1. [Introduction to PyQt6](#1-introduction-to-pyqt6)
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
17. [Database Connectivity](#17-database-connectivity)
18. [Networking](#18-networking)
19. [Multimedia](#19-multimedia)
20. [Packaging and Deployment](#20-packaging-and-deployment)

---

# Part 1: Beginner Level

---

## 1. Introduction to PyQt6

### What is PyQt6?

PyQt6 is a comprehensive set of Python bindings for Qt 6, developed by Riverbank Computing. It enables you to create professional desktop applications using Python.

### Key Differences from PySide6

| Aspect | PyQt6 | PySide6 |
|--------|-------|---------|
| Maintainer | Riverbank Computing | The Qt Company |
| License | GPL v3 | LGPL |
| Enum Access | `Qt.AlignmentFlag.AlignCenter` | Same |
| Signal Syntax | `pyqtSignal` | `Signal` |
| Slot Decorator | `@pyqtSlot` | `@Slot` |
| exec() | `app.exec()` | `app.exec()` |

### Installation

```bash
pip install PyQt6
```

For additional tools:
```bash
pip install PyQt6-tools  # Includes Qt Designer
```

### Module Overview

```python
# Core modules
from PyQt6.QtWidgets import *  # UI widgets
from PyQt6.QtCore import *     # Core non-GUI classes
from PyQt6.QtGui import *      # GUI primitives

# Additional modules
from PyQt6.QtSql import *          # Database
from PyQt6.QtNetwork import *      # Networking
from PyQt6.QtMultimedia import *   # Audio/Video
from PyQt6.QtCharts import *       # Charts (separate package)
from PyQt6.QtWebEngineWidgets import *  # Web browser (separate package)
```

### Qt Architecture

```
┌─────────────────────────────────────────────────────────────┐
│                    Your Python Application                   │
├─────────────────────────────────────────────────────────────┤
│                          PyQt6                               │
├───────────┬───────────┬───────────┬───────────┬─────────────┤
│ QtWidgets │  QtCore   │   QtGui   │   QtSql   │ QtNetwork   │
├───────────┴───────────┴───────────┴───────────┴─────────────┤
│                      Qt Framework (C++)                      │
├─────────────────────────────────────────────────────────────┤
│            Operating System (Windows/macOS/Linux)            │
└─────────────────────────────────────────────────────────────┘
```

---

## 2. Your First Application

### The Minimal Application

```python
import sys
from PyQt6.QtWidgets import QApplication, QLabel

# Create the application (one per app)
app = QApplication(sys.argv)

# Create a widget
label = QLabel("Hello, PyQt6!")
label.show()

# Start the event loop
sys.exit(app.exec())
```

### Main Window Application

```python
import sys
from PyQt6.QtWidgets import QApplication, QMainWindow, QLabel
from PyQt6.QtCore import Qt

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        
        # Window setup
        self.setWindowTitle("My First PyQt6 App")
        self.setGeometry(100, 100, 600, 400)
        
        # Central widget
        label = QLabel("Welcome to PyQt6!")
        label.setAlignment(Qt.AlignmentFlag.AlignCenter)
        self.setCentralWidget(label)

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec())
```

### Understanding the Application Structure

1. **QApplication**: Manages application-wide resources
2. **QMainWindow**: Main application window with menu, toolbar, status bar support
3. **Widgets**: Visual components (buttons, labels, etc.)
4. **Event Loop**: `app.exec()` starts processing events

---

## 3. Understanding Qt Widgets

### Common Widgets Reference

#### QPushButton

```python
from PyQt6.QtWidgets import QPushButton

button = QPushButton("Click Me!")
button.setToolTip("This is a button")
button.setEnabled(True)
button.setCheckable(True)  # Toggle button

# Signals
button.clicked.connect(lambda: print("Clicked!"))
button.pressed.connect(lambda: print("Pressed!"))
button.released.connect(lambda: print("Released!"))
```

#### QLabel

```python
from PyQt6.QtWidgets import QLabel
from PyQt6.QtCore import Qt
from PyQt6.QtGui import QPixmap

# Text label
label = QLabel("Hello World")
label.setAlignment(Qt.AlignmentFlag.AlignCenter)
label.setWordWrap(True)

# Rich text
label.setText("<h1>Title</h1><p>Paragraph with <b>bold</b> text</p>")

# Image label
image_label = QLabel()
pixmap = QPixmap("image.png")
image_label.setPixmap(pixmap.scaled(200, 200, Qt.AspectRatioMode.KeepAspectRatio))
```

#### QLineEdit

```python
from PyQt6.QtWidgets import QLineEdit

line_edit = QLineEdit()
line_edit.setPlaceholderText("Enter text here...")
line_edit.setMaxLength(100)

# Password mode
line_edit.setEchoMode(QLineEdit.EchoMode.Password)

# Read-only
line_edit.setReadOnly(True)

# Get/Set text
text = line_edit.text()
line_edit.setText("Default value")
line_edit.clear()

# Signals
line_edit.textChanged.connect(lambda text: print(f"Changed: {text}"))
line_edit.returnPressed.connect(lambda: print("Enter pressed!"))
```

#### QTextEdit

```python
from PyQt6.QtWidgets import QTextEdit

text_edit = QTextEdit()
text_edit.setPlainText("Plain text content")
text_edit.setHtml("<b>Bold</b> and <i>italic</i>")
text_edit.setReadOnly(False)

# Get content
plain = text_edit.toPlainText()
html = text_edit.toHtml()
```

#### QCheckBox

```python
from PyQt6.QtWidgets import QCheckBox
from PyQt6.QtCore import Qt

checkbox = QCheckBox("Enable feature")
checkbox.setChecked(True)

# Tri-state checkbox
checkbox.setTristate(True)
state = checkbox.checkState()
# Qt.CheckState.Unchecked, Qt.CheckState.PartiallyChecked, Qt.CheckState.Checked

checkbox.stateChanged.connect(lambda state: print(f"State: {state}"))
```

#### QRadioButton

```python
from PyQt6.QtWidgets import QRadioButton, QButtonGroup, QVBoxLayout, QWidget

widget = QWidget()
layout = QVBoxLayout(widget)

radio1 = QRadioButton("Option 1")
radio2 = QRadioButton("Option 2")
radio3 = QRadioButton("Option 3")
radio1.setChecked(True)

layout.addWidget(radio1)
layout.addWidget(radio2)
layout.addWidget(radio3)

# Button group for exclusive selection
group = QButtonGroup(widget)
group.addButton(radio1, 1)
group.addButton(radio2, 2)
group.addButton(radio3, 3)

group.buttonClicked.connect(lambda btn: print(f"Selected: {btn.text()}"))
```

#### QComboBox

```python
from PyQt6.QtWidgets import QComboBox

combo = QComboBox()
combo.addItem("Option 1")
combo.addItems(["Option 2", "Option 3", "Option 4"])

combo.setCurrentIndex(0)
combo.setEditable(True)  # Allow custom input

# Get selection
text = combo.currentText()
index = combo.currentIndex()

combo.currentIndexChanged.connect(lambda i: print(f"Index: {i}"))
combo.currentTextChanged.connect(lambda t: print(f"Text: {t}"))
```

#### QSpinBox and QDoubleSpinBox

```python
from PyQt6.QtWidgets import QSpinBox, QDoubleSpinBox

# Integer
spin = QSpinBox()
spin.setRange(0, 100)
spin.setValue(50)
spin.setSingleStep(5)
spin.setPrefix("$ ")
spin.setSuffix(" items")

# Float
double_spin = QDoubleSpinBox()
double_spin.setRange(0.0, 100.0)
double_spin.setDecimals(2)
double_spin.setSingleStep(0.1)

spin.valueChanged.connect(lambda v: print(f"Value: {v}"))
```

#### QSlider

```python
from PyQt6.QtWidgets import QSlider
from PyQt6.QtCore import Qt

slider = QSlider(Qt.Orientation.Horizontal)
slider.setRange(0, 100)
slider.setValue(50)
slider.setTickPosition(QSlider.TickPosition.TicksBelow)
slider.setTickInterval(10)

slider.valueChanged.connect(lambda v: print(f"Value: {v}"))
```

#### QProgressBar

```python
from PyQt6.QtWidgets import QProgressBar

progress = QProgressBar()
progress.setRange(0, 100)
progress.setValue(75)
progress.setTextVisible(True)

# Indeterminate (busy) mode
progress.setRange(0, 0)
```

### Complete Widget Example

```python
import sys
from PyQt6.QtWidgets import (
    QApplication, QMainWindow, QWidget, QVBoxLayout, QHBoxLayout,
    QLabel, QPushButton, QLineEdit, QCheckBox, QComboBox, QSpinBox
)

class WidgetDemo(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Widget Demo")
        
        central = QWidget()
        self.setCentralWidget(central)
        layout = QVBoxLayout(central)
        
        # Name input
        name_row = QHBoxLayout()
        name_row.addWidget(QLabel("Name:"))
        self.name_input = QLineEdit()
        self.name_input.setPlaceholderText("Enter your name")
        name_row.addWidget(self.name_input)
        layout.addLayout(name_row)
        
        # Age spinner
        age_row = QHBoxLayout()
        age_row.addWidget(QLabel("Age:"))
        self.age_spin = QSpinBox()
        self.age_spin.setRange(0, 150)
        age_row.addWidget(self.age_spin)
        age_row.addStretch()
        layout.addLayout(age_row)
        
        # Country dropdown
        country_row = QHBoxLayout()
        country_row.addWidget(QLabel("Country:"))
        self.country_combo = QComboBox()
        self.country_combo.addItems(["USA", "UK", "Canada", "Australia"])
        country_row.addWidget(self.country_combo)
        layout.addLayout(country_row)
        
        # Newsletter checkbox
        self.newsletter = QCheckBox("Subscribe to newsletter")
        layout.addWidget(self.newsletter)
        
        # Submit button
        self.submit_btn = QPushButton("Submit")
        self.submit_btn.clicked.connect(self.on_submit)
        layout.addWidget(self.submit_btn)
        
        # Result
        self.result = QLabel("")
        layout.addWidget(self.result)
        
        layout.addStretch()
    
    def on_submit(self):
        info = (f"Name: {self.name_input.text()}, "
                f"Age: {self.age_spin.value()}, "
                f"Country: {self.country_combo.currentText()}, "
                f"Newsletter: {'Yes' if self.newsletter.isChecked() else 'No'}")
        self.result.setText(info)

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = WidgetDemo()
    window.show()
    sys.exit(app.exec())
```

---

## 4. Layout Management

### QVBoxLayout - Vertical

```python
from PyQt6.QtWidgets import QWidget, QVBoxLayout, QPushButton

widget = QWidget()
layout = QVBoxLayout(widget)

layout.addWidget(QPushButton("Button 1"))
layout.addWidget(QPushButton("Button 2"))
layout.addWidget(QPushButton("Button 3"))
```

### QHBoxLayout - Horizontal

```python
from PyQt6.QtWidgets import QWidget, QHBoxLayout, QPushButton

widget = QWidget()
layout = QHBoxLayout(widget)

layout.addWidget(QPushButton("Left"))
layout.addStretch()  # Flexible space
layout.addWidget(QPushButton("Right"))
```

### QGridLayout - Grid

```python
from PyQt6.QtWidgets import QWidget, QGridLayout, QPushButton

widget = QWidget()
layout = QGridLayout(widget)

# addWidget(widget, row, column, rowSpan, colSpan)
layout.addWidget(QPushButton("1"), 0, 0)
layout.addWidget(QPushButton("2"), 0, 1)
layout.addWidget(QPushButton("3"), 0, 2)
layout.addWidget(QPushButton("4"), 1, 0, 1, 3)  # Spans 3 columns
```

### QFormLayout - Forms

```python
from PyQt6.QtWidgets import QWidget, QFormLayout, QLineEdit, QSpinBox

widget = QWidget()
layout = QFormLayout(widget)

layout.addRow("Name:", QLineEdit())
layout.addRow("Age:", QSpinBox())
layout.addRow("Email:", QLineEdit())
```

### Nested Layouts

```python
from PyQt6.QtWidgets import (
    QWidget, QVBoxLayout, QHBoxLayout, QFormLayout,
    QLabel, QLineEdit, QPushButton
)

widget = QWidget()
main_layout = QVBoxLayout(widget)

# Form section
form = QFormLayout()
form.addRow("Username:", QLineEdit())
form.addRow("Password:", QLineEdit())
main_layout.addLayout(form)

# Button section
buttons = QHBoxLayout()
buttons.addStretch()
buttons.addWidget(QPushButton("Cancel"))
buttons.addWidget(QPushButton("Login"))
main_layout.addLayout(buttons)
```

### Spacing and Margins

```python
layout = QVBoxLayout()
layout.setSpacing(10)  # Space between widgets
layout.setContentsMargins(20, 20, 20, 20)  # left, top, right, bottom
```

---

## 5. Signals and Slots

### Basic Connection

```python
from PyQt6.QtWidgets import QPushButton

button = QPushButton("Click")
button.clicked.connect(lambda: print("Clicked!"))
```

### Connecting to Methods

```python
class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        
        button = QPushButton("Click")
        button.clicked.connect(self.handle_click)
        self.setCentralWidget(button)
    
    def handle_click(self):
        print("Button clicked!")
```

### Signals with Data

```python
from PyQt6.QtWidgets import QLineEdit, QSlider

# Text change
line_edit = QLineEdit()
line_edit.textChanged.connect(lambda text: print(f"Text: {text}"))

# Slider value
slider = QSlider()
slider.valueChanged.connect(lambda value: print(f"Value: {value}"))
```

### Custom Signals (PyQt6 Syntax)

```python
from PyQt6.QtCore import QObject, pyqtSignal

class Worker(QObject):
    # Define signals with pyqtSignal
    started = pyqtSignal()
    progress = pyqtSignal(int)
    finished = pyqtSignal(str)
    data_ready = pyqtSignal(str, int)  # Multiple arguments
    
    def do_work(self):
        self.started.emit()
        
        for i in range(100):
            self.progress.emit(i)
        
        self.data_ready.emit("Complete", 100)
        self.finished.emit("Done!")

# Usage
worker = Worker()
worker.started.connect(lambda: print("Started"))
worker.progress.connect(lambda p: print(f"Progress: {p}%"))
worker.finished.connect(lambda msg: print(msg))
```

### Disconnecting Signals

```python
# Disconnect specific slot
button.clicked.disconnect(self.handle_click)

# Disconnect all
button.clicked.disconnect()
```

---

## 6. Dialog Boxes

### Message Boxes

```python
from PyQt6.QtWidgets import QMessageBox

# Information
QMessageBox.information(self, "Info", "Operation completed!")

# Warning
QMessageBox.warning(self, "Warning", "Proceed with caution!")

# Error
QMessageBox.critical(self, "Error", "Something went wrong!")

# Question
result = QMessageBox.question(
    self, "Confirm", "Are you sure?",
    QMessageBox.StandardButton.Yes | QMessageBox.StandardButton.No
)

if result == QMessageBox.StandardButton.Yes:
    print("User said Yes")
```

### Input Dialogs

```python
from PyQt6.QtWidgets import QInputDialog

# Text
text, ok = QInputDialog.getText(self, "Input", "Enter name:")
if ok and text:
    print(f"Name: {text}")

# Integer
num, ok = QInputDialog.getInt(self, "Input", "Enter number:", 
                               value=50, min=0, max=100)

# Selection
items = ["Option 1", "Option 2", "Option 3"]
item, ok = QInputDialog.getItem(self, "Select", "Choose:", items)
```

### File Dialogs

```python
from PyQt6.QtWidgets import QFileDialog

# Open file
path, _ = QFileDialog.getOpenFileName(
    self, "Open File", "",
    "Text Files (*.txt);;All Files (*)"
)

# Save file
path, _ = QFileDialog.getSaveFileName(
    self, "Save File", "",
    "Text Files (*.txt);;All Files (*)"
)

# Select directory
directory = QFileDialog.getExistingDirectory(self, "Select Folder")
```

### Color and Font Dialogs

```python
from PyQt6.QtWidgets import QColorDialog, QFontDialog

# Color
color = QColorDialog.getColor()
if color.isValid():
    print(f"Color: {color.name()}")

# Font
font, ok = QFontDialog.getFont()
if ok:
    print(f"Font: {font.family()}, {font.pointSize()}pt")
```

### Custom Dialogs

```python
from PyQt6.QtWidgets import (
    QDialog, QVBoxLayout, QFormLayout, QLineEdit, 
    QDialogButtonBox
)

class LoginDialog(QDialog):
    def __init__(self, parent=None):
        super().__init__(parent)
        self.setWindowTitle("Login")
        
        layout = QVBoxLayout(self)
        
        form = QFormLayout()
        self.username = QLineEdit()
        self.password = QLineEdit()
        self.password.setEchoMode(QLineEdit.EchoMode.Password)
        form.addRow("Username:", self.username)
        form.addRow("Password:", self.password)
        layout.addLayout(form)
        
        buttons = QDialogButtonBox(
            QDialogButtonBox.StandardButton.Ok | 
            QDialogButtonBox.StandardButton.Cancel
        )
        buttons.accepted.connect(self.accept)
        buttons.rejected.connect(self.reject)
        layout.addWidget(buttons)
    
    def get_credentials(self):
        return self.username.text(), self.password.text()

# Usage
dialog = LoginDialog(self)
if dialog.exec() == QDialog.DialogCode.Accepted:
    username, password = dialog.get_credentials()
    print(f"Login: {username}")
```

---

## 7. Basic Event Handling

### Mouse Events

```python
from PyQt6.QtWidgets import QWidget
from PyQt6.QtCore import Qt

class MouseWidget(QWidget):
    def mousePressEvent(self, event):
        if event.button() == Qt.MouseButton.LeftButton:
            pos = event.position()
            print(f"Left click at ({pos.x()}, {pos.y()})")
        super().mousePressEvent(event)
    
    def mouseDoubleClickEvent(self, event):
        print("Double click!")
        super().mouseDoubleClickEvent(event)
    
    def mouseMoveEvent(self, event):
        print(f"Mouse at ({event.position().x()}, {event.position().y()})")
        super().mouseMoveEvent(event)
    
    def wheelEvent(self, event):
        delta = event.angleDelta().y()
        print(f"Scroll: {'up' if delta > 0 else 'down'}")
        super().wheelEvent(event)
```

### Keyboard Events

```python
from PyQt6.QtWidgets import QWidget
from PyQt6.QtCore import Qt

class KeyWidget(QWidget):
    def keyPressEvent(self, event):
        key = event.key()
        modifiers = event.modifiers()
        
        if key == Qt.Key.Key_Escape:
            print("Escape pressed")
        elif key == Qt.Key.Key_Return:
            print("Enter pressed")
        
        # Ctrl+S
        if modifiers & Qt.KeyboardModifier.ControlModifier:
            if key == Qt.Key.Key_S:
                print("Ctrl+S pressed")
        
        super().keyPressEvent(event)
```

### Window Events

```python
from PyQt6.QtWidgets import QMainWindow, QMessageBox

class MainWindow(QMainWindow):
    def resizeEvent(self, event):
        size = event.size()
        print(f"Resized to {size.width()}x{size.height()}")
        super().resizeEvent(event)
    
    def closeEvent(self, event):
        reply = QMessageBox.question(
            self, "Exit", "Are you sure?",
            QMessageBox.StandardButton.Yes | QMessageBox.StandardButton.No
        )
        
        if reply == QMessageBox.StandardButton.Yes:
            event.accept()
        else:
            event.ignore()
```

### Drag and Drop

```python
from PyQt6.QtWidgets import QLabel
from PyQt6.QtCore import Qt

class DropZone(QLabel):
    def __init__(self):
        super().__init__("Drop files here")
        self.setAcceptDrops(True)
        self.setAlignment(Qt.AlignmentFlag.AlignCenter)
        self.setStyleSheet("border: 2px dashed gray; padding: 40px;")
    
    def dragEnterEvent(self, event):
        if event.mimeData().hasUrls():
            event.acceptProposedAction()
            self.setStyleSheet("border: 2px dashed green; background: lightgreen; padding: 40px;")
    
    def dragLeaveEvent(self, event):
        self.setStyleSheet("border: 2px dashed gray; padding: 40px;")
    
    def dropEvent(self, event):
        for url in event.mimeData().urls():
            print(f"Dropped: {url.toLocalFile()}")
        self.setStyleSheet("border: 2px dashed gray; padding: 40px;")
        event.acceptProposedAction()
```

---

# Part 2: Intermediate Level

---

## 8. Custom Widgets

### Creating Custom Widgets

```python
from PyQt6.QtWidgets import QWidget
from PyQt6.QtCore import Qt, pyqtSignal, pyqtProperty
from PyQt6.QtGui import QPainter, QColor, QPen, QBrush

class CircularProgress(QWidget):
    valueChanged = pyqtSignal(int)
    
    def __init__(self, parent=None):
        super().__init__(parent)
        self._value = 0
        self._max = 100
        self._color = QColor(0, 120, 215)
        self.setMinimumSize(100, 100)
    
    def getValue(self):
        return self._value
    
    def setValue(self, value):
        if 0 <= value <= self._max:
            self._value = value
            self.valueChanged.emit(value)
            self.update()
    
    value = pyqtProperty(int, getValue, setValue)
    
    def paintEvent(self, event):
        painter = QPainter(self)
        painter.setRenderHint(QPainter.RenderHint.Antialiasing)
        
        # Draw background
        rect = self.rect().adjusted(10, 10, -10, -10)
        painter.setPen(QPen(QColor(220, 220, 220), 8))
        painter.drawArc(rect, 0, 360 * 16)
        
        # Draw progress
        progress_pen = QPen(self._color, 8)
        progress_pen.setCapStyle(Qt.PenCapStyle.RoundCap)
        painter.setPen(progress_pen)
        span = int((self._value / self._max) * 360 * 16)
        painter.drawArc(rect, 90 * 16, -span)
        
        # Draw text
        painter.setPen(Qt.GlobalColor.black)
        painter.drawText(rect, Qt.AlignmentFlag.AlignCenter, f"{self._value}%")
```

### Toggle Switch Widget

```python
from PyQt6.QtWidgets import QWidget
from PyQt6.QtCore import Qt, pyqtSignal
from PyQt6.QtGui import QPainter, QColor, QBrush

class ToggleSwitch(QWidget):
    toggled = pyqtSignal(bool)
    
    def __init__(self, parent=None):
        super().__init__(parent)
        self._checked = False
        self.setFixedSize(50, 26)
        self.setCursor(Qt.CursorShape.PointingHandCursor)
    
    def isChecked(self):
        return self._checked
    
    def setChecked(self, checked):
        self._checked = checked
        self.toggled.emit(checked)
        self.update()
    
    def mousePressEvent(self, event):
        self.setChecked(not self._checked)
    
    def paintEvent(self, event):
        painter = QPainter(self)
        painter.setRenderHint(QPainter.RenderHint.Antialiasing)
        
        # Track
        track_color = QColor(0, 120, 215) if self._checked else QColor(180, 180, 180)
        painter.setBrush(QBrush(track_color))
        painter.setPen(Qt.PenStyle.NoPen)
        painter.drawRoundedRect(0, 3, 50, 20, 10, 10)
        
        # Thumb
        thumb_x = 26 if self._checked else 2
        painter.setBrush(QBrush(Qt.GlobalColor.white))
        painter.drawEllipse(thumb_x, 1, 22, 22)
```

---

## 9. Model-View Programming

### QStringListModel

```python
from PyQt6.QtWidgets import QListView
from PyQt6.QtCore import QStringListModel

model = QStringListModel()
model.setStringList(["Apple", "Banana", "Cherry"])

view = QListView()
view.setModel(model)

# Add item
items = model.stringList()
items.append("Date")
model.setStringList(items)
```

### Custom Table Model

```python
from PyQt6.QtCore import Qt, QAbstractTableModel, QModelIndex

class TableModel(QAbstractTableModel):
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
        
        if role == Qt.ItemDataRole.DisplayRole:
            return self._data[index.row()][index.column()]
        
        return None
    
    def headerData(self, section, orientation, role=Qt.ItemDataRole.DisplayRole):
        if role == Qt.ItemDataRole.DisplayRole:
            if orientation == Qt.Orientation.Horizontal:
                return self._headers[section]
        return None
    
    def flags(self, index):
        return (Qt.ItemFlag.ItemIsEnabled | 
                Qt.ItemFlag.ItemIsSelectable | 
                Qt.ItemFlag.ItemIsEditable)
    
    def setData(self, index, value, role=Qt.ItemDataRole.EditRole):
        if role == Qt.ItemDataRole.EditRole:
            self._data[index.row()][index.column()] = value
            self.dataChanged.emit(index, index, [role])
            return True
        return False

# Usage
data = [
    ["Alice", "30", "NYC"],
    ["Bob", "25", "LA"],
]
model = TableModel(data)

from PyQt6.QtWidgets import QTableView
view = QTableView()
view.setModel(model)
```

### Sorting and Filtering

```python
from PyQt6.QtCore import QSortFilterProxyModel, Qt

proxy = QSortFilterProxyModel()
proxy.setSourceModel(model)
proxy.setFilterKeyColumn(0)  # Filter by first column
proxy.setFilterCaseSensitivity(Qt.CaseSensitivity.CaseInsensitive)

# Apply filter
proxy.setFilterFixedString("ali")

# Use proxy with view
view.setModel(proxy)
view.setSortingEnabled(True)
```

---

## 10. Multithreading with QThread

### Worker Pattern

```python
from PyQt6.QtCore import QObject, QThread, pyqtSignal
import time

class Worker(QObject):
    started = pyqtSignal()
    progress = pyqtSignal(int)
    finished = pyqtSignal(str)
    
    def __init__(self):
        super().__init__()
        self._running = True
    
    def run(self):
        self.started.emit()
        
        for i in range(101):
            if not self._running:
                break
            time.sleep(0.05)
            self.progress.emit(i)
        
        self.finished.emit("Complete!")
    
    def stop(self):
        self._running = False

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.thread = None
        self.worker = None
        self.setup_ui()
    
    def setup_ui(self):
        central = QWidget()
        self.setCentralWidget(central)
        layout = QVBoxLayout(central)
        
        self.progress = QProgressBar()
        self.start_btn = QPushButton("Start")
        self.stop_btn = QPushButton("Stop")
        self.stop_btn.setEnabled(False)
        
        layout.addWidget(self.progress)
        layout.addWidget(self.start_btn)
        layout.addWidget(self.stop_btn)
        
        self.start_btn.clicked.connect(self.start_task)
        self.stop_btn.clicked.connect(self.stop_task)
    
    def start_task(self):
        self.thread = QThread()
        self.worker = Worker()
        self.worker.moveToThread(self.thread)
        
        self.thread.started.connect(self.worker.run)
        self.worker.started.connect(lambda: self.start_btn.setEnabled(False))
        self.worker.started.connect(lambda: self.stop_btn.setEnabled(True))
        self.worker.progress.connect(self.progress.setValue)
        self.worker.finished.connect(self.on_finished)
        self.worker.finished.connect(self.thread.quit)
        
        self.thread.start()
    
    def stop_task(self):
        if self.worker:
            self.worker.stop()
    
    def on_finished(self, message):
        self.start_btn.setEnabled(True)
        self.stop_btn.setEnabled(False)
        print(message)
```

---

## 11. Styling with Qt Style Sheets

### Basic Styling

```python
# Single widget
button.setStyleSheet("""
    QPushButton {
        background-color: #0078d4;
        color: white;
        border: none;
        padding: 10px 20px;
        border-radius: 5px;
    }
    QPushButton:hover {
        background-color: #1084d8;
    }
    QPushButton:pressed {
        background-color: #006cbd;
    }
""")

# Application-wide
app.setStyleSheet("""
    QMainWindow {
        background-color: #f0f0f0;
    }
    QLabel {
        font-size: 14px;
    }
""")
```

### Complete Dark Theme

```python
DARK_STYLE = """
QWidget {
    background-color: #1e1e1e;
    color: #d4d4d4;
    font-family: "Segoe UI", Arial;
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

QPushButton:pressed {
    background-color: #0d5a8c;
}

QPushButton:disabled {
    background-color: #3c3c3c;
    color: #808080;
}

QLineEdit, QTextEdit {
    background-color: #3c3c3c;
    border: 1px solid #3c3c3c;
    border-radius: 4px;
    padding: 6px;
    color: #d4d4d4;
}

QLineEdit:focus, QTextEdit:focus {
    border: 1px solid #0e639c;
}

QComboBox {
    background-color: #3c3c3c;
    border: 1px solid #3c3c3c;
    border-radius: 4px;
    padding: 6px;
}

QScrollBar:vertical {
    background: #1e1e1e;
    width: 12px;
}

QScrollBar::handle:vertical {
    background: #5a5a5a;
    border-radius: 6px;
    min-height: 20px;
}

QTableView {
    background-color: #252526;
    gridline-color: #3c3c3c;
}

QTableView::item:selected {
    background-color: #0e639c;
}

QHeaderView::section {
    background-color: #333333;
    padding: 8px;
    border: none;
}

QTabWidget::pane {
    border: 1px solid #3c3c3c;
}

QTabBar::tab {
    background-color: #2d2d2d;
    padding: 10px 20px;
    color: #808080;
}

QTabBar::tab:selected {
    background-color: #1e1e1e;
    color: #d4d4d4;
    border-bottom: 2px solid #0e639c;
}
"""

app.setStyleSheet(DARK_STYLE)
```

---

## 12. Menus, Toolbars, and Status Bars

### Menu Bar

```python
from PyQt6.QtWidgets import QMainWindow
from PyQt6.QtGui import QAction, QKeySequence

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.create_menus()
    
    def create_menus(self):
        menubar = self.menuBar()
        
        # File menu
        file_menu = menubar.addMenu("&File")
        
        new_action = QAction("&New", self)
        new_action.setShortcut(QKeySequence.StandardKey.New)
        new_action.triggered.connect(self.new_file)
        file_menu.addAction(new_action)
        
        open_action = QAction("&Open...", self)
        open_action.setShortcut(QKeySequence.StandardKey.Open)
        file_menu.addAction(open_action)
        
        file_menu.addSeparator()
        
        exit_action = QAction("E&xit", self)
        exit_action.setShortcut(QKeySequence.StandardKey.Quit)
        exit_action.triggered.connect(self.close)
        file_menu.addAction(exit_action)
        
        # Edit menu
        edit_menu = menubar.addMenu("&Edit")
        edit_menu.addAction(QAction("&Undo", self))
        edit_menu.addAction(QAction("&Redo", self))
        
        # View menu with checkable items
        view_menu = menubar.addMenu("&View")
        
        toolbar_action = QAction("&Toolbar", self)
        toolbar_action.setCheckable(True)
        toolbar_action.setChecked(True)
        view_menu.addAction(toolbar_action)
    
    def new_file(self):
        print("New file")
```

### Toolbar

```python
from PyQt6.QtWidgets import QToolBar
from PyQt6.QtCore import Qt

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.create_toolbar()
    
    def create_toolbar(self):
        toolbar = QToolBar("Main")
        toolbar.setMovable(True)
        self.addToolBar(Qt.ToolBarArea.TopToolBarArea, toolbar)
        
        # Add actions
        toolbar.addAction(QAction("New", self))
        toolbar.addAction(QAction("Open", self))
        toolbar.addAction(QAction("Save", self))
        toolbar.addSeparator()
        
        # Add widget
        from PyQt6.QtWidgets import QLineEdit
        search = QLineEdit()
        search.setPlaceholderText("Search...")
        search.setMaximumWidth(200)
        toolbar.addWidget(search)
```

### Status Bar

```python
from PyQt6.QtWidgets import QLabel, QProgressBar

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.create_statusbar()
    
    def create_statusbar(self):
        status = self.statusBar()
        
        # Temporary message
        status.showMessage("Ready", 3000)
        
        # Permanent widgets
        self.pos_label = QLabel("Line: 1, Col: 1")
        status.addPermanentWidget(self.pos_label)
```

---

## 13. Working with Files

### Text File Operations

```python
from PyQt6.QtWidgets import QMainWindow, QTextEdit, QFileDialog, QMessageBox

class TextEditor(QMainWindow):
    def __init__(self):
        super().__init__()
        self.current_file = None
        self.editor = QTextEdit()
        self.setCentralWidget(self.editor)
    
    def open_file(self):
        path, _ = QFileDialog.getOpenFileName(
            self, "Open", "", "Text Files (*.txt);;All Files (*)"
        )
        if path:
            try:
                with open(path, 'r', encoding='utf-8') as f:
                    self.editor.setPlainText(f.read())
                self.current_file = path
                self.setWindowTitle(path)
            except Exception as e:
                QMessageBox.critical(self, "Error", str(e))
    
    def save_file(self):
        if not self.current_file:
            return self.save_as()
        
        try:
            with open(self.current_file, 'w', encoding='utf-8') as f:
                f.write(self.editor.toPlainText())
            return True
        except Exception as e:
            QMessageBox.critical(self, "Error", str(e))
            return False
    
    def save_as(self):
        path, _ = QFileDialog.getSaveFileName(
            self, "Save As", "", "Text Files (*.txt);;All Files (*)"
        )
        if path:
            self.current_file = path
            return self.save_file()
        return False
```

---

## 14. Settings and Preferences

### QSettings

```python
from PyQt6.QtCore import QSettings

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.settings = QSettings("MyCompany", "MyApp")
        self.load_settings()
    
    def load_settings(self):
        # Window geometry
        geometry = self.settings.value("geometry")
        if geometry:
            self.restoreGeometry(geometry)
        
        # Custom settings
        self.theme = self.settings.value("theme", "light")
        self.font_size = int(self.settings.value("fontSize", 12))
    
    def save_settings(self):
        self.settings.setValue("geometry", self.saveGeometry())
        self.settings.setValue("theme", self.theme)
        self.settings.setValue("fontSize", self.font_size)
    
    def closeEvent(self, event):
        self.save_settings()
        event.accept()
```

---

# Part 3: Advanced Level

---

## 15. Graphics View Framework

### Basic Setup

```python
from PyQt6.QtWidgets import (
    QGraphicsView, QGraphicsScene, 
    QGraphicsRectItem, QGraphicsEllipseItem
)
from PyQt6.QtCore import Qt
from PyQt6.QtGui import QBrush, QPen, QColor, QPainter

# Create scene
scene = QGraphicsScene()
scene.setSceneRect(-400, -300, 800, 600)

# Add shapes
rect = QGraphicsRectItem(0, 0, 100, 60)
rect.setBrush(QBrush(QColor(100, 149, 237)))
rect.setPen(QPen(Qt.GlobalColor.black, 2))
rect.setPos(-50, -30)
rect.setFlag(QGraphicsRectItem.GraphicsItemFlag.ItemIsMovable)
scene.addItem(rect)

ellipse = QGraphicsEllipseItem(0, 0, 80, 80)
ellipse.setBrush(QBrush(QColor(255, 165, 0)))
ellipse.setPos(100, 50)
scene.addItem(ellipse)

# Create view
view = QGraphicsView(scene)
view.setRenderHint(QPainter.RenderHint.Antialiasing)
view.setDragMode(QGraphicsView.DragMode.ScrollHandDrag)
view.show()
```

### Custom Graphics Item

```python
from PyQt6.QtWidgets import QGraphicsItem
from PyQt6.QtCore import QRectF, Qt
from PyQt6.QtGui import QPainter, QBrush, QPen

class CustomItem(QGraphicsItem):
    def __init__(self):
        super().__init__()
        self.setFlag(QGraphicsItem.GraphicsItemFlag.ItemIsMovable)
        self.setFlag(QGraphicsItem.GraphicsItemFlag.ItemIsSelectable)
        self._color = QColor(100, 149, 237)
    
    def boundingRect(self):
        return QRectF(-50, -30, 100, 60)
    
    def paint(self, painter, option, widget):
        painter.setRenderHint(QPainter.RenderHint.Antialiasing)
        
        if self.isSelected():
            painter.setPen(QPen(Qt.GlobalColor.blue, 2, Qt.PenStyle.DashLine))
        else:
            painter.setPen(QPen(Qt.GlobalColor.black, 1))
        
        painter.setBrush(QBrush(self._color))
        painter.drawRoundedRect(self.boundingRect(), 10, 10)
```

---

## 16. Animations and State Machines

### Property Animation

```python
from PyQt6.QtCore import QPropertyAnimation, QEasingCurve, QPoint

button = QPushButton("Animate")

# Animate position
anim = QPropertyAnimation(button, b"pos")
anim.setDuration(1000)
anim.setStartValue(QPoint(0, 0))
anim.setEndValue(QPoint(200, 100))
anim.setEasingCurve(QEasingCurve.Type.OutBounce)
anim.start()
```

### Animation Groups

```python
from PyQt6.QtCore import QSequentialAnimationGroup, QParallelAnimationGroup

# Sequential
seq = QSequentialAnimationGroup()
seq.addAnimation(move_right_anim)
seq.addAnimation(move_down_anim)
seq.start()

# Parallel
par = QParallelAnimationGroup()
par.addAnimation(pos_anim)
par.addAnimation(size_anim)
par.start()
```

### Custom Animated Widget

```python
from PyQt6.QtWidgets import QWidget
from PyQt6.QtCore import pyqtProperty, QPropertyAnimation, QEasingCurve
from PyQt6.QtGui import QPainter, QColor

class PulsingCircle(QWidget):
    def __init__(self):
        super().__init__()
        self._radius = 50
        self.setMinimumSize(200, 200)
        
        self.anim = QPropertyAnimation(self, b"radius")
        self.anim.setDuration(1000)
        self.anim.setStartValue(30)
        self.anim.setEndValue(80)
        self.anim.setEasingCurve(QEasingCurve.Type.InOutSine)
        self.anim.setLoopCount(-1)
        self.anim.start()
    
    def getRadius(self):
        return self._radius
    
    def setRadius(self, value):
        self._radius = value
        self.update()
    
    radius = pyqtProperty(int, getRadius, setRadius)
    
    def paintEvent(self, event):
        painter = QPainter(self)
        painter.setRenderHint(QPainter.RenderHint.Antialiasing)
        painter.setBrush(QColor(100, 149, 237))
        center = self.rect().center()
        painter.drawEllipse(center, self._radius, self._radius)
```

---

## 17. Database Connectivity

### SQLite with PyQt6

```python
from PyQt6.QtSql import QSqlDatabase, QSqlQuery, QSqlTableModel
from PyQt6.QtWidgets import QTableView
from PyQt6.QtCore import Qt

# Connect
db = QSqlDatabase.addDatabase("QSQLITE")
db.setDatabaseName("app.db")
if not db.open():
    print(f"Error: {db.lastError().text()}")

# Create table
query = QSqlQuery()
query.exec("""
    CREATE TABLE IF NOT EXISTS users (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        name TEXT NOT NULL,
        email TEXT UNIQUE
    )
""")

# Insert
query.prepare("INSERT INTO users (name, email) VALUES (?, ?)")
query.addBindValue("Alice")
query.addBindValue("alice@example.com")
query.exec()

# Query
query.exec("SELECT * FROM users")
while query.next():
    print(f"{query.value(0)}: {query.value(1)}, {query.value(2)}")

# Table model
model = QSqlTableModel()
model.setTable("users")
model.select()

view = QTableView()
view.setModel(model)
```

---

## 18. Networking

### HTTP Client

```python
from PyQt6.QtNetwork import QNetworkAccessManager, QNetworkRequest, QNetworkReply
from PyQt6.QtCore import QUrl, QObject, pyqtSignal

class HttpClient(QObject):
    finished = pyqtSignal(str)
    error = pyqtSignal(str)
    
    def __init__(self):
        super().__init__()
        self.manager = QNetworkAccessManager()
        self.manager.finished.connect(self._on_finished)
    
    def get(self, url):
        request = QNetworkRequest(QUrl(url))
        self.manager.get(request)
    
    def _on_finished(self, reply):
        if reply.error() == QNetworkReply.NetworkError.NoError:
            data = reply.readAll().data().decode()
            self.finished.emit(data)
        else:
            self.error.emit(reply.errorString())
        reply.deleteLater()

# Usage
client = HttpClient()
client.finished.connect(lambda data: print(data))
client.get("https://api.github.com/users/octocat")
```

### File Download

```python
from PyQt6.QtNetwork import QNetworkAccessManager, QNetworkRequest
from PyQt6.QtCore import QUrl, QFile, QIODevice, pyqtSignal, QObject

class Downloader(QObject):
    progress = pyqtSignal(int, int)
    finished = pyqtSignal(str)
    
    def __init__(self):
        super().__init__()
        self.manager = QNetworkAccessManager()
        self.file = None
    
    def download(self, url, path):
        self.file = QFile(path)
        self.file.open(QIODevice.OpenModeFlag.WriteOnly)
        
        reply = self.manager.get(QNetworkRequest(QUrl(url)))
        reply.downloadProgress.connect(self._on_progress)
        reply.readyRead.connect(lambda: self.file.write(reply.readAll()))
        reply.finished.connect(self._on_finished)
        self.reply = reply
    
    def _on_progress(self, received, total):
        self.progress.emit(received, total)
    
    def _on_finished(self):
        self.file.close()
        self.finished.emit(self.file.fileName())
```

---

## 19. Multimedia

### Audio Player

```python
from PyQt6.QtMultimedia import QMediaPlayer, QAudioOutput
from PyQt6.QtCore import QUrl

player = QMediaPlayer()
audio = QAudioOutput()
player.setAudioOutput(audio)

# Load and play
player.setSource(QUrl.fromLocalFile("music.mp3"))
audio.setVolume(0.5)
player.play()

# Controls
player.pause()
player.stop()
player.setPosition(30000)  # 30 seconds
```

### Video Player

```python
from PyQt6.QtMultimedia import QMediaPlayer, QAudioOutput
from PyQt6.QtMultimediaWidgets import QVideoWidget

video_widget = QVideoWidget()

player = QMediaPlayer()
audio = QAudioOutput()
player.setAudioOutput(audio)
player.setVideoOutput(video_widget)

player.setSource(QUrl.fromLocalFile("video.mp4"))
video_widget.show()
player.play()
```

---

## 20. Packaging and Deployment

### PyInstaller

```bash
pip install pyinstaller

# Basic
pyinstaller main.py

# Single file, no console
pyinstaller --onefile --windowed --icon=app.ico main.py
```

### Spec File

```python
# main.spec
a = Analysis(
    ['main.py'],
    datas=[
        ('icons/*.png', 'icons'),
        ('styles/*.qss', 'styles'),
    ],
    hiddenimports=['PyQt6.QtSvg'],
)

pyz = PYZ(a.pure)

exe = EXE(
    pyz,
    a.scripts,
    a.binaries,
    a.datas,
    name='MyApp',
    console=False,
    icon='app.ico',
)
```

### Resource Path Helper

```python
import sys
import os

def resource_path(relative):
    if hasattr(sys, '_MEIPASS'):
        return os.path.join(sys._MEIPASS, relative)
    return os.path.join(os.path.abspath("."), relative)

# Usage
icon = resource_path("icons/app.png")
```

### Qt Resource System

Create `resources.qrc`:
```xml
<!DOCTYPE RCC>
<RCC version="1.0">
    <qresource>
        <file>icons/app.png</file>
        <file>styles/dark.qss</file>
    </qresource>
</RCC>
```

Compile and use:
```bash
pyrcc6 resources.qrc -o resources_rc.py
```

```python
import resources_rc
icon = QIcon(":/icons/app.png")
```

---

## Key Differences: PyQt6 vs PySide6

| Feature | PyQt6 | PySide6 |
|---------|-------|---------|
| Signal | `pyqtSignal` | `Signal` |
| Slot | `@pyqtSlot` | `@Slot` |
| Property | `pyqtProperty` | `Property` |
| Resource Compiler | `pyrcc6` | `pyside6-rcc` |
| UIC Compiler | `pyuic6` | `pyside6-uic` |

### Migration Example

```python
# PyQt6
from PyQt6.QtCore import pyqtSignal, pyqtSlot, pyqtProperty

class MyClass(QObject):
    my_signal = pyqtSignal(str)
    
    @pyqtSlot()
    def my_slot(self):
        pass

# PySide6
from PySide6.QtCore import Signal, Slot, Property

class MyClass(QObject):
    my_signal = Signal(str)
    
    @Slot()
    def my_slot(self):
        pass
```

---

## Summary

This tutorial covered PyQt6 comprehensively:

### Beginner
- Application structure
- Widgets and layouts
- Signals and slots
- Dialogs and events

### Intermediate
- Custom widgets
- Model-View architecture
- Threading
- Styling
- Menus and toolbars

### Advanced
- Graphics View
- Animations
- Database
- Networking
- Multimedia
- Deployment

### Resources

- [PyQt6 Documentation](https://www.riverbankcomputing.com/static/Docs/PyQt6/)
- [Qt 6 Documentation](https://doc.qt.io/qt-6/)
- [Python GUIs Tutorials](https://pythonguis.com)

Happy coding with PyQt6!
