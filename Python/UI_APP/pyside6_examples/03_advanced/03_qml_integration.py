"""
PySide6 Advanced Example 03: QML Integration
=============================================

This example demonstrates:
- Loading QML from strings and files
- Python-QML communication
- Exposing Python objects to QML
- Custom QML types from Python
- Signals between Python and QML

Run: python 03_qml_integration.py
"""

import sys
import os

# Set Qt Quick Controls style to avoid native style warnings
os.environ["QT_QUICK_CONTROLS_STYLE"] = "Basic"

from PySide6.QtWidgets import QApplication
from PySide6.QtCore import QObject, Signal, Slot, Property, QUrl
from PySide6.QtGui import QGuiApplication
from PySide6.QtQml import QQmlApplicationEngine, qmlRegisterType


# QML content as a string (normally you'd load from a file)
QML_CONTENT = '''
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    id: window
    width: 500
    height: 600
    visible: true
    title: "QML Integration Demo"
    
    color: "#1e1e2e"
    
    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 20
        
        // Header
        Text {
            text: "PySide6 + QML Demo"
            font.pixelSize: 28
            font.bold: true
            color: "#cdd6f4"
            Layout.alignment: Qt.AlignHCenter
        }
        
        // Counter Section
        Rectangle {
            Layout.fillWidth: true
            height: 150
            color: "#313244"
            radius: 12
            
            ColumnLayout {
                anchors.centerIn: parent
                spacing: 15
                
                Text {
                    text: "Counter from Python: " + backend.count
                    font.pixelSize: 20
                    color: "#f5c2e7"
                    Layout.alignment: Qt.AlignHCenter
                }
                
                RowLayout {
                    spacing: 10
                    Layout.alignment: Qt.AlignHCenter
                    
                    Button {
                        text: "-"
                        font.pixelSize: 20
                        implicitWidth: 60
                        onClicked: backend.decrement()
                        
                        background: Rectangle {
                            color: parent.down ? "#f38ba8" : "#eba0ac"
                            radius: 8
                        }
                    }
                    
                    Button {
                        text: "+"
                        font.pixelSize: 20
                        implicitWidth: 60
                        onClicked: backend.increment()
                        
                        background: Rectangle {
                            color: parent.down ? "#a6e3a1" : "#94e2d5"
                            radius: 8
                        }
                    }
                    
                    Button {
                        text: "Reset"
                        onClicked: backend.reset()
                        
                        background: Rectangle {
                            color: parent.down ? "#585b70" : "#45475a"
                            radius: 8
                        }
                        
                        contentItem: Text {
                            text: parent.text
                            color: "#cdd6f4"
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }
                    }
                }
            }
        }
        
        // Text Processing Section
        Rectangle {
            Layout.fillWidth: true
            height: 180
            color: "#313244"
            radius: 12
            
            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 15
                spacing: 10
                
                Text {
                    text: "Text Processing"
                    font.pixelSize: 16
                    font.bold: true
                    color: "#89b4fa"
                }
                
                TextField {
                    id: inputField
                    Layout.fillWidth: true
                    placeholderText: "Enter text to process..."
                    font.pixelSize: 14
                    
                    background: Rectangle {
                        color: "#45475a"
                        radius: 6
                        border.color: inputField.focus ? "#89b4fa" : "transparent"
                        border.width: 2
                    }
                    
                    color: "#cdd6f4"
                }
                
                RowLayout {
                    spacing: 10
                    
                    Button {
                        text: "Uppercase"
                        onClicked: resultText.text = backend.toUpperCase(inputField.text)
                        
                        background: Rectangle {
                            color: parent.down ? "#74c7ec" : "#89dceb"
                            radius: 6
                        }
                    }
                    
                    Button {
                        text: "Lowercase"
                        onClicked: resultText.text = backend.toLowerCase(inputField.text)
                        
                        background: Rectangle {
                            color: parent.down ? "#74c7ec" : "#89dceb"
                            radius: 6
                        }
                    }
                    
                    Button {
                        text: "Reverse"
                        onClicked: resultText.text = backend.reverse(inputField.text)
                        
                        background: Rectangle {
                            color: parent.down ? "#74c7ec" : "#89dceb"
                            radius: 6
                        }
                    }
                }
                
                Text {
                    id: resultText
                    text: ""
                    font.pixelSize: 14
                    color: "#a6e3a1"
                    wrapMode: Text.Wrap
                    Layout.fillWidth: true
                }
            }
        }
        
        // Calculator Section
        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "#313244"
            radius: 12
            
            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 15
                spacing: 10
                
                Text {
                    text: "Calculator (via Python)"
                    font.pixelSize: 16
                    font.bold: true
                    color: "#89b4fa"
                }
                
                RowLayout {
                    spacing: 10
                    
                    TextField {
                        id: numA
                        placeholderText: "Number A"
                        inputMethodHints: Qt.ImhDigitsOnly
                        Layout.fillWidth: true
                        
                        background: Rectangle {
                            color: "#45475a"
                            radius: 6
                        }
                        color: "#cdd6f4"
                    }
                    
                    TextField {
                        id: numB
                        placeholderText: "Number B"
                        inputMethodHints: Qt.ImhDigitsOnly
                        Layout.fillWidth: true
                        
                        background: Rectangle {
                            color: "#45475a"
                            radius: 6
                        }
                        color: "#cdd6f4"
                    }
                }
                
                GridLayout {
                    columns: 4
                    Layout.fillWidth: true
                    
                    Repeater {
                        model: ["+", "-", "*", "/"]
                        
                        Button {
                            text: modelData
                            Layout.fillWidth: true
                            font.pixelSize: 18
                            
                            onClicked: {
                                var a = parseFloat(numA.text) || 0
                                var b = parseFloat(numB.text) || 0
                                calcResult.text = "Result: " + backend.calculate(a, b, modelData)
                            }
                            
                            background: Rectangle {
                                color: parent.down ? "#f9e2af" : "#fab387"
                                radius: 6
                            }
                        }
                    }
                }
                
                Text {
                    id: calcResult
                    text: "Result: --"
                    font.pixelSize: 18
                    color: "#f5c2e7"
                    Layout.alignment: Qt.AlignHCenter
                }
            }
        }
        
        // Message from Python
        Text {
            text: backend.message
            font.pixelSize: 12
            color: "#6c7086"
            Layout.alignment: Qt.AlignHCenter
        }
    }
    
    // Handle signal from Python
    Connections {
        target: backend
        function onCountChanged() {
            console.log("Count changed to:", backend.count)
        }
    }
}
'''


class Backend(QObject):
    """Python backend exposed to QML."""
    
    countChanged = Signal()
    messageChanged = Signal()
    
    def __init__(self):
        super().__init__()
        self._count = 0
        self._message = "Python Backend v1.0"
    
    # Count property
    @Property(int, notify=countChanged)
    def count(self):
        return self._count
    
    @count.setter
    def count(self, value):
        if self._count != value:
            self._count = value
            self.countChanged.emit()
    
    # Message property
    @Property(str, notify=messageChanged)
    def message(self):
        return self._message
    
    # Slots callable from QML
    @Slot()
    def increment(self):
        """Increment the counter."""
        self.count += 1
    
    @Slot()
    def decrement(self):
        """Decrement the counter."""
        self.count -= 1
    
    @Slot()
    def reset(self):
        """Reset the counter to zero."""
        self.count = 0
    
    @Slot(str, result=str)
    def toUpperCase(self, text):
        """Convert text to uppercase."""
        return text.upper()
    
    @Slot(str, result=str)
    def toLowerCase(self, text):
        """Convert text to lowercase."""
        return text.lower()
    
    @Slot(str, result=str)
    def reverse(self, text):
        """Reverse the text."""
        return text[::-1]
    
    @Slot(float, float, str, result=str)
    def calculate(self, a, b, operation):
        """Perform a calculation."""
        try:
            if operation == "+":
                result = a + b
            elif operation == "-":
                result = a - b
            elif operation == "*":
                result = a * b
            elif operation == "/":
                if b == 0:
                    return "Error: Division by zero"
                result = a / b
            else:
                return "Unknown operation"
            
            # Format result nicely
            if result == int(result):
                return str(int(result))
            return f"{result:.4f}"
        except Exception as e:
            return f"Error: {e}"


def main():
    """Main entry point."""
    # Use QGuiApplication for QML
    app = QGuiApplication(sys.argv)
    
    # Create QML engine
    engine = QQmlApplicationEngine()
    
    # Create and expose backend
    backend = Backend()
    engine.rootContext().setContextProperty("backend", backend)
    
    # Load QML from string
    # In production, you'd typically use: engine.load(QUrl.fromLocalFile("main.qml"))
    engine.loadData(QML_CONTENT.encode())
    
    if not engine.rootObjects():
        print("Failed to load QML")
        sys.exit(-1)
    
    sys.exit(app.exec())


if __name__ == "__main__":
    print("=" * 50)
    print("PySide6 QML Integration Demo")
    print("=" * 50)
    print("\nThis example demonstrates Python-QML integration.")
    print("Features:")
    print("  - Counter controlled from QML, managed in Python")
    print("  - Text processing functions in Python")
    print("  - Calculator with Python backend")
    print("\nNote: This requires Qt Quick modules to be installed.")
    print("If you see errors, install with: pip install PySide6")
    print("=" * 50 + "\n")
    
    main()
