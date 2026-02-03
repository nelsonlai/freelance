# Python Qt GUI Development - Complete Learning Guide

## PySide6 & PyQt6 Comprehensive Tutorial

Welcome to the comprehensive guide for building desktop applications with Python using Qt frameworks. This repository contains complete teaching materials covering **PySide6** and **PyQt6** from beginner to advanced levels.

---

## Table of Contents

1. [Overview & Comparison](#overview--comparison)
2. [Installation Guide](#installation-guide)
3. [Tutorial Structure](#tutorial-structure)
4. [Quick Start](#quick-start)

---

## Overview & Comparison

### What is Qt?

Qt is a powerful, cross-platform C++ framework for developing graphical user interfaces (GUIs) and applications. Both **PySide6** and **PyQt6** are Python bindings that allow you to use Qt 6 with Python.

### PySide6 vs PyQt6

| Feature | PySide6 | PyQt6 |
|---------|---------|-------|
| **Maintainer** | The Qt Company (Official) | Riverbank Computing |
| **Current Version** | 6.10.1 | 6.10.2 |
| **License** | LGPL/GPL (Commercial friendly) | GPL v3 (Commercial requires license) |
| **Python Support** | 3.9 - 3.14 | 3.9+ |
| **Documentation** | [doc.qt.io/qtforpython](https://doc.qt.io/qtforpython) | [riverbankcomputing.com](https://www.riverbankcomputing.com/static/Docs/PyQt6/) |
| **API Compatibility** | Nearly identical | Nearly identical |
| **Commercial Use** | Free for commercial apps | Requires commercial license |

### Which Should You Choose?

- **PySide6**: Recommended for commercial projects due to LGPL licensing
- **PyQt6**: Great for open-source projects; extensive community resources
- **Both**: API is 99% identical, skills transfer easily between them

---

## Installation Guide

### Prerequisites

- Python 3.9 or higher
- pip (Python package manager)

### Installing PySide6

```bash
pip install PySide6
```

### Installing PyQt6

```bash
pip install PyQt6
```

### Verify Installation

```python
# For PySide6
from PySide6.QtWidgets import QApplication
print(f"PySide6 installed successfully!")

# For PyQt6
from PyQt6.QtWidgets import QApplication
print(f"PyQt6 installed successfully!")
```

---

## Tutorial Structure

```
UI_APP/
├── README.md                           # This file
├── requirements.txt                    # Dependencies
│
├── docs/
│   ├── PySide6_Tutorial.md            # Complete PySide6 Guide
│   └── PyQt6_Tutorial.md              # Complete PyQt6 Guide
│
├── pyside6_examples/
│   ├── 01_beginner/                   # Beginner examples
│   │   ├── 01_hello_world.py
│   │   ├── 02_widgets_basic.py
│   │   ├── 03_layouts.py
│   │   ├── 04_signals_slots.py
│   │   └── 05_dialogs.py
│   │
│   ├── 02_intermediate/               # Intermediate examples
│   │   ├── 01_custom_widgets.py
│   │   ├── 02_model_view.py
│   │   ├── 03_threading.py
│   │   ├── 04_styling.py
│   │   └── 05_menus_toolbars.py
│   │
│   └── 03_advanced/                   # Advanced examples
│       ├── 01_graphics_view.py
│       ├── 02_animations.py
│       ├── 03_qml_integration.py
│       ├── 04_database.py
│       ├── 05_networking.py
│       └── 06_media_player.py        # Audio/Video player with repeat
│
└── pyqt6_examples/
    ├── 01_beginner/                   # Beginner examples
    ├── 02_intermediate/               # Intermediate examples
    └── 03_advanced/                   # Advanced examples
```

---

## Quick Start

### Your First Application (PySide6)

```python
import sys
from PySide6.QtWidgets import QApplication, QMainWindow, QLabel

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("My First PySide6 App")
        self.setGeometry(100, 100, 400, 300)
        
        label = QLabel("Hello, PySide6!", self)
        label.setGeometry(150, 130, 200, 40)

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec())
```

### Your First Application (PyQt6)

```python
import sys
from PyQt6.QtWidgets import QApplication, QMainWindow, QLabel

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("My First PyQt6 App")
        self.setGeometry(100, 100, 400, 300)
        
        label = QLabel("Hello, PyQt6!", self)
        label.setGeometry(150, 130, 200, 40)

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec())
```

---

## Learning Path

### Beginner Level (1-2 weeks)
- Understanding Qt architecture
- Basic widgets (buttons, labels, text fields)
- Layout management
- Signals and slots mechanism
- Dialog boxes and message boxes

### Intermediate Level (2-4 weeks)
- Custom widgets and painting
- Model-View programming
- Multithreading with QThread
- Styling with Qt Style Sheets (QSS)
- Menus, toolbars, and status bars

### Advanced Level (4+ weeks)
- Graphics View Framework
- Animations and transitions
- QML and Qt Quick integration
- Database connectivity
- Networking and web services
- Application packaging and deployment

---

## Next Steps

1. **Read the detailed tutorials:**
   - [PySide6 Complete Tutorial](docs/PySide6_Tutorial.md)
   - [PyQt6 Complete Tutorial](docs/PyQt6_Tutorial.md)

2. **Run the examples** in the respective example folders

3. **Build your own project** using the patterns learned

---

## Resources

### Official Documentation
- [Qt for Python (PySide6)](https://doc.qt.io/qtforpython)
- [PyQt6 Documentation](https://www.riverbankcomputing.com/static/Docs/PyQt6/)
- [Qt 6 Documentation](https://doc.qt.io/qt-6/)

### Community
- [Python GUIs](https://pythonguis.com)
- [Qt Forum](https://forum.qt.io/)
- [Stack Overflow - PySide6](https://stackoverflow.com/questions/tagged/pyside6)
- [Stack Overflow - PyQt6](https://stackoverflow.com/questions/tagged/pyqt6)

---

*Happy coding! Build amazing desktop applications with Python and Qt.*
