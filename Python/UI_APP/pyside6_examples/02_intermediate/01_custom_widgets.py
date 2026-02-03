"""
PySide6 Intermediate Example 01: Custom Widgets
================================================

This example demonstrates:
- Creating custom widgets by subclassing QWidget
- Custom painting with QPainter
- Defining custom properties
- Custom signals for widget state changes

Run: python 01_custom_widgets.py
"""

import sys
import math
from PySide6.QtWidgets import (
    QApplication, QMainWindow, QWidget, QVBoxLayout, QHBoxLayout,
    QLabel, QPushButton, QSlider, QGroupBox
)
from PySide6.QtCore import Qt, Signal, Property, QTimer, QPointF
from PySide6.QtGui import QPainter, QColor, QPen, QBrush, QFont, QLinearGradient


class CircularProgressBar(QWidget):
    """A circular progress bar widget."""
    
    valueChanged = Signal(int)
    
    def __init__(self, parent=None):
        super().__init__(parent)
        self._value = 0
        self._minimum = 0
        self._maximum = 100
        self._thickness = 15
        self._color = QColor(0, 150, 136)
        self._background_color = QColor(230, 230, 230)
        self._text_color = QColor(50, 50, 50)
        
        self.setMinimumSize(150, 150)
    
    # Properties
    def getValue(self):
        return self._value
    
    def setValue(self, value):
        value = max(self._minimum, min(self._maximum, value))
        if self._value != value:
            self._value = value
            self.valueChanged.emit(value)
            self.update()
    
    value = Property(int, getValue, setValue)
    
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
        margin = self._thickness + 5
        rect = self.rect().adjusted(margin, margin, -margin, -margin)
        
        # Draw background arc
        bg_pen = QPen(self._background_color, self._thickness)
        bg_pen.setCapStyle(Qt.PenCapStyle.RoundCap)
        painter.setPen(bg_pen)
        painter.drawArc(rect, 0, 360 * 16)
        
        # Draw progress arc
        if self._maximum > self._minimum:
            progress = (self._value - self._minimum) / (self._maximum - self._minimum)
            span_angle = int(progress * 360 * 16)
            
            progress_pen = QPen(self._color, self._thickness)
            progress_pen.setCapStyle(Qt.PenCapStyle.RoundCap)
            painter.setPen(progress_pen)
            painter.drawArc(rect, 90 * 16, -span_angle)
        
        # Draw percentage text
        painter.setPen(self._text_color)
        font = QFont()
        font.setPointSize(int(side / 6))
        font.setBold(True)
        painter.setFont(font)
        
        percentage = int((self._value - self._minimum) / 
                        max(1, self._maximum - self._minimum) * 100)
        painter.drawText(rect, Qt.AlignmentFlag.AlignCenter, f"{percentage}%")


class ToggleSwitch(QWidget):
    """A toggle switch widget."""
    
    toggled = Signal(bool)
    
    def __init__(self, parent=None):
        super().__init__(parent)
        self._checked = False
        self._animation_position = 0.0
        
        self.setFixedSize(60, 30)
        self.setCursor(Qt.CursorShape.PointingHandCursor)
        
        # Animation timer
        self._timer = QTimer(self)
        self._timer.timeout.connect(self._animate)
    
    def isChecked(self):
        return self._checked
    
    def setChecked(self, checked):
        if self._checked != checked:
            self._checked = checked
            self._start_animation()
            self.toggled.emit(checked)
    
    checked = Property(bool, isChecked, setChecked)
    
    def toggle(self):
        self.setChecked(not self._checked)
    
    def _start_animation(self):
        self._timer.start(16)  # ~60 FPS
    
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
        
        # Interpolate colors
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
        
        # Thumb shadow
        painter.setBrush(QBrush(QColor(0, 0, 0, 30)))
        painter.drawEllipse(thumb_x + 1, 2, 24, 24)
        
        # Thumb
        painter.setBrush(QBrush(Qt.GlobalColor.white))
        painter.drawEllipse(thumb_x, 1, 24, 24)


class SpeedometerWidget(QWidget):
    """A speedometer-style gauge widget."""
    
    valueChanged = Signal(float)
    
    def __init__(self, parent=None):
        super().__init__(parent)
        self._value = 0
        self._minimum = 0
        self._maximum = 100
        self._label = "Speed"
        self._unit = "km/h"
        
        self.setMinimumSize(200, 200)
    
    def getValue(self):
        return self._value
    
    def setValue(self, value):
        value = max(self._minimum, min(self._maximum, value))
        if self._value != value:
            self._value = value
            self.valueChanged.emit(value)
            self.update()
    
    value = Property(float, getValue, setValue)
    
    def setRange(self, minimum, maximum):
        self._minimum = minimum
        self._maximum = maximum
        self.update()
    
    def setLabel(self, label, unit=""):
        self._label = label
        self._unit = unit
        self.update()
    
    def paintEvent(self, event):
        painter = QPainter(self)
        painter.setRenderHint(QPainter.RenderHint.Antialiasing)
        
        side = min(self.width(), self.height())
        center = QPointF(self.width() / 2, self.height() / 2)
        radius = side / 2 - 20
        
        # Draw background arc
        bg_pen = QPen(QColor(220, 220, 220), 15)
        bg_pen.setCapStyle(Qt.PenCapStyle.RoundCap)
        painter.setPen(bg_pen)
        arc_rect = self.rect().adjusted(25, 25, -25, -25)
        painter.drawArc(arc_rect, 225 * 16, -270 * 16)
        
        # Draw colored arc (gradient from green to red)
        if self._maximum > self._minimum:
            progress = (self._value - self._minimum) / (self._maximum - self._minimum)
            
            # Color based on value
            if progress < 0.5:
                color = QColor(76, 175, 80)  # Green
            elif progress < 0.75:
                color = QColor(255, 193, 7)  # Yellow
            else:
                color = QColor(244, 67, 54)  # Red
            
            arc_pen = QPen(color, 15)
            arc_pen.setCapStyle(Qt.PenCapStyle.RoundCap)
            painter.setPen(arc_pen)
            span_angle = int(progress * 270 * 16)
            painter.drawArc(arc_rect, 225 * 16, -span_angle)
        
        # Draw tick marks
        painter.setPen(QPen(QColor(100, 100, 100), 2))
        for i in range(11):
            angle = math.radians(225 - i * 27)
            inner_radius = radius - 25
            outer_radius = radius - 15
            
            x1 = center.x() + inner_radius * math.cos(angle)
            y1 = center.y() - inner_radius * math.sin(angle)
            x2 = center.x() + outer_radius * math.cos(angle)
            y2 = center.y() - outer_radius * math.sin(angle)
            
            painter.drawLine(QPointF(x1, y1), QPointF(x2, y2))
        
        # Draw needle
        if self._maximum > self._minimum:
            progress = (self._value - self._minimum) / (self._maximum - self._minimum)
            angle = math.radians(225 - progress * 270)
            
            needle_length = radius - 35
            x = center.x() + needle_length * math.cos(angle)
            y = center.y() - needle_length * math.sin(angle)
            
            painter.setPen(QPen(QColor(220, 50, 50), 3))
            painter.drawLine(center, QPointF(x, y))
            
            # Needle center
            painter.setBrush(QBrush(QColor(60, 60, 60)))
            painter.setPen(Qt.PenStyle.NoPen)
            painter.drawEllipse(center, 8, 8)
        
        # Draw value text
        painter.setPen(QColor(50, 50, 50))
        font = QFont()
        font.setPointSize(int(side / 8))
        font.setBold(True)
        painter.setFont(font)
        
        text = f"{self._value:.0f}"
        text_rect = arc_rect.adjusted(0, side / 3, 0, 0)
        painter.drawText(text_rect, Qt.AlignmentFlag.AlignHCenter | Qt.AlignmentFlag.AlignTop, text)
        
        # Draw unit
        font.setPointSize(int(side / 15))
        font.setBold(False)
        painter.setFont(font)
        painter.setPen(QColor(120, 120, 120))
        
        unit_rect = arc_rect.adjusted(0, side / 2.2, 0, 0)
        painter.drawText(unit_rect, Qt.AlignmentFlag.AlignHCenter | Qt.AlignmentFlag.AlignTop, self._unit)


class CustomWidgetsDemo(QMainWindow):
    """Demo window for custom widgets."""
    
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Custom Widgets Demo")
        self.setMinimumSize(700, 500)
        
        central = QWidget()
        self.setCentralWidget(central)
        layout = QHBoxLayout(central)
        
        # Left column - Circular progress
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
                            ("Purple", QColor(156, 39, 176)),
                            ("Orange", QColor(255, 152, 0))]:
            btn = QPushButton(name)
            btn.clicked.connect(lambda checked, c=color: self.circular_progress.setColor(c))
            color_layout.addWidget(btn)
        left_layout.addLayout(color_layout)
        
        layout.addWidget(left_group)
        
        # Center column - Toggle switches
        center_group = QGroupBox("Toggle Switches")
        center_layout = QVBoxLayout(center_group)
        
        for label_text in ["Enable notifications", "Dark mode", "Auto-save", "Sound effects"]:
            row = QHBoxLayout()
            label = QLabel(label_text)
            toggle = ToggleSwitch()
            toggle.toggled.connect(lambda checked, l=label_text: 
                print(f"{l}: {'ON' if checked else 'OFF'}"))
            row.addWidget(label)
            row.addStretch()
            row.addWidget(toggle)
            center_layout.addLayout(row)
        
        center_layout.addStretch()
        layout.addWidget(center_group)
        
        # Right column - Speedometer
        right_group = QGroupBox("Speedometer Gauge")
        right_layout = QVBoxLayout(right_group)
        
        self.speedometer = SpeedometerWidget()
        self.speedometer.setRange(0, 200)
        self.speedometer.setLabel("Speed", "km/h")
        right_layout.addWidget(self.speedometer, alignment=Qt.AlignmentFlag.AlignCenter)
        
        speed_slider = QSlider(Qt.Orientation.Horizontal)
        speed_slider.setRange(0, 200)
        speed_slider.setValue(0)
        speed_slider.valueChanged.connect(self.speedometer.setValue)
        right_layout.addWidget(speed_slider)
        
        layout.addWidget(right_group)


def main():
    app = QApplication(sys.argv)
    window = CustomWidgetsDemo()
    window.show()
    sys.exit(app.exec())


if __name__ == "__main__":
    main()
