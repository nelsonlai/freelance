"""
PyQt6 Intermediate Example 01: Custom Widgets
==============================================

This example demonstrates:
- Creating custom widgets by subclassing QWidget
- Custom painting with QPainter
- Defining custom properties with pyqtProperty

KEY DIFFERENCE FROM PySide6:
- Use pyqtProperty instead of Property
- Use pyqtSignal instead of Signal

Run: python 01_custom_widgets.py
"""

import sys
import math
from PyQt6.QtWidgets import (
    QApplication, QMainWindow, QWidget, QVBoxLayout, QHBoxLayout,
    QLabel, QPushButton, QSlider, QGroupBox
)
from PyQt6.QtCore import Qt, pyqtSignal, pyqtProperty, QTimer
from PyQt6.QtGui import QPainter, QColor, QPen, QBrush, QFont


class CircularProgressBar(QWidget):
    """A circular progress bar widget."""
    
    # Use pyqtSignal (PyQt6 syntax)
    valueChanged = pyqtSignal(int)
    
    def __init__(self, parent=None):
        super().__init__(parent)
        self._value = 0
        self._minimum = 0
        self._maximum = 100
        self._thickness = 15
        self._color = QColor(0, 150, 136)
        self._background_color = QColor(230, 230, 230)
        
        self.setMinimumSize(150, 150)
    
    # Use pyqtProperty (PyQt6 syntax)
    def getValue(self):
        return self._value
    
    def setValue(self, value):
        value = max(self._minimum, min(self._maximum, value))
        if self._value != value:
            self._value = value
            self.valueChanged.emit(value)
            self.update()
    
    value = pyqtProperty(int, getValue, setValue)
    
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
        
        margin = self._thickness + 5
        rect = self.rect().adjusted(margin, margin, -margin, -margin)
        
        # Background arc
        bg_pen = QPen(self._background_color, self._thickness)
        bg_pen.setCapStyle(Qt.PenCapStyle.RoundCap)
        painter.setPen(bg_pen)
        painter.drawArc(rect, 0, 360 * 16)
        
        # Progress arc
        if self._maximum > self._minimum:
            progress = (self._value - self._minimum) / (self._maximum - self._minimum)
            span_angle = int(progress * 360 * 16)
            
            progress_pen = QPen(self._color, self._thickness)
            progress_pen.setCapStyle(Qt.PenCapStyle.RoundCap)
            painter.setPen(progress_pen)
            painter.drawArc(rect, 90 * 16, -span_angle)
        
        # Percentage text
        painter.setPen(QColor(50, 50, 50))
        font = QFont()
        font.setPointSize(int(min(self.width(), self.height()) / 6))
        font.setBold(True)
        painter.setFont(font)
        
        percentage = int((self._value - self._minimum) / 
                        max(1, self._maximum - self._minimum) * 100)
        painter.drawText(rect, Qt.AlignmentFlag.AlignCenter, f"{percentage}%")


class ToggleSwitch(QWidget):
    """A toggle switch widget."""
    
    toggled = pyqtSignal(bool)
    
    def __init__(self, parent=None):
        super().__init__(parent)
        self._checked = False
        self._animation_position = 0.0
        
        self.setFixedSize(60, 30)
        self.setCursor(Qt.CursorShape.PointingHandCursor)
        
        self._timer = QTimer(self)
        self._timer.timeout.connect(self._animate)
    
    def isChecked(self):
        return self._checked
    
    def setChecked(self, checked):
        if self._checked != checked:
            self._checked = checked
            self._start_animation()
            self.toggled.emit(checked)
    
    checked = pyqtProperty(bool, isChecked, setChecked)
    
    def toggle(self):
        self.setChecked(not self._checked)
    
    def _start_animation(self):
        self._timer.start(16)
    
    def _animate(self):
        target = 1.0 if self._checked else 0.0
        diff = target - self._animation_position
        
        if abs(diff) < 0.05:
            self._animation_position = target
            self._timer.stop()
        else:
            self._animation_position += diff * 0.3
        
        self.update()
    
    def mousePressEvent(self, event):
        if event.button() == Qt.MouseButton.LeftButton:
            self.toggle()
    
    def paintEvent(self, event):
        painter = QPainter(self)
        painter.setRenderHint(QPainter.RenderHint.Antialiasing)
        
        # Track color interpolation
        off_color = QColor(180, 180, 180)
        on_color = QColor(0, 150, 136)
        
        r = int(off_color.red() + (on_color.red() - off_color.red()) * self._animation_position)
        g = int(off_color.green() + (on_color.green() - off_color.green()) * self._animation_position)
        b = int(off_color.blue() + (on_color.blue() - off_color.blue()) * self._animation_position)
        track_color = QColor(r, g, b)
        
        # Draw track
        painter.setPen(Qt.PenStyle.NoPen)
        painter.setBrush(QBrush(track_color))
        painter.drawRoundedRect(0, 5, 60, 20, 10, 10)
        
        # Draw thumb
        thumb_x = 3 + int(self._animation_position * 30)
        painter.setBrush(QBrush(Qt.GlobalColor.white))
        painter.drawEllipse(thumb_x, 1, 24, 24)


class CustomWidgetsDemo(QMainWindow):
    """Demo window for custom widgets."""
    
    def __init__(self):
        super().__init__()
        self.setWindowTitle("PyQt6 Custom Widgets Demo")
        self.setMinimumSize(700, 400)
        
        central = QWidget()
        self.setCentralWidget(central)
        layout = QHBoxLayout(central)
        
        # Circular progress
        left_group = QGroupBox("Circular Progress")
        left_layout = QVBoxLayout(left_group)
        
        self.circular_progress = CircularProgressBar()
        left_layout.addWidget(self.circular_progress, alignment=Qt.AlignmentFlag.AlignCenter)
        
        slider = QSlider(Qt.Orientation.Horizontal)
        slider.setRange(0, 100)
        slider.setValue(0)
        slider.valueChanged.connect(self.circular_progress.setValue)
        left_layout.addWidget(slider)
        
        # Color buttons
        color_layout = QHBoxLayout()
        for name, color in [("Teal", QColor(0, 150, 136)), 
                            ("Blue", QColor(33, 150, 243)),
                            ("Orange", QColor(255, 152, 0))]:
            btn = QPushButton(name)
            btn.clicked.connect(lambda checked, c=color: self.circular_progress.setColor(c))
            color_layout.addWidget(btn)
        left_layout.addLayout(color_layout)
        
        layout.addWidget(left_group)
        
        # Toggle switches
        right_group = QGroupBox("Toggle Switches")
        right_layout = QVBoxLayout(right_group)
        
        for label_text in ["Enable notifications", "Dark mode", "Auto-save"]:
            row = QHBoxLayout()
            label = QLabel(label_text)
            toggle = ToggleSwitch()
            toggle.toggled.connect(lambda checked, l=label_text: 
                print(f"{l}: {'ON' if checked else 'OFF'}"))
            row.addWidget(label)
            row.addStretch()
            row.addWidget(toggle)
            right_layout.addLayout(row)
        
        right_layout.addStretch()
        layout.addWidget(right_group)


def main():
    app = QApplication(sys.argv)
    window = CustomWidgetsDemo()
    window.show()
    sys.exit(app.exec())


if __name__ == "__main__":
    main()
