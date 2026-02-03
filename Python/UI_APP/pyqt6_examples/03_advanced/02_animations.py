"""
PyQt6 Advanced Example 02: Animations
=====================================

This example demonstrates:
- QPropertyAnimation for property animations
- QEasingCurve for animation easing
- Custom animated properties using pyqtProperty

Run: python 02_animations.py
"""

import sys
from PyQt6.QtWidgets import (
    QApplication, QMainWindow, QWidget, QVBoxLayout, QHBoxLayout,
    QPushButton, QLabel, QGroupBox, QComboBox, QSlider
)
from PyQt6.QtCore import (
    Qt, pyqtProperty, QPropertyAnimation, QEasingCurve, QPoint
)
from PyQt6.QtGui import QPainter, QColor, QBrush


class AnimatedWidget(QWidget):
    """A widget with custom animatable properties."""
    
    def __init__(self, parent=None):
        super().__init__(parent)
        self._color = QColor(100, 149, 237)
        self._radius = 50
        
        self.setMinimumSize(200, 200)
    
    def get_color(self):
        return self._color
    
    def set_color(self, color):
        self._color = color
        self.update()
    
    # Use pyqtProperty (PyQt6 syntax)
    color = pyqtProperty(QColor, get_color, set_color)
    
    def get_radius(self):
        return self._radius
    
    def set_radius(self, radius):
        self._radius = radius
        self.update()
    
    radius = pyqtProperty(int, get_radius, set_radius)
    
    def paintEvent(self, event):
        painter = QPainter(self)
        painter.setRenderHint(QPainter.RenderHint.Antialiasing)
        
        center = self.rect().center()
        painter.setBrush(QBrush(self._color))
        painter.drawEllipse(center, self._radius, self._radius)


class MovableButton(QPushButton):
    """A button that can be animated."""
    
    def __init__(self, text, parent=None):
        super().__init__(text, parent)
        self.setFixedSize(120, 40)


class AnimationsDemo(QMainWindow):
    """Main window demonstrating animations."""
    
    def __init__(self):
        super().__init__()
        self.setWindowTitle("PyQt6 Animations Demo")
        self.setMinimumSize(700, 500)
        
        central = QWidget()
        self.setCentralWidget(central)
        layout = QVBoxLayout(central)
        
        layout.addWidget(self.create_property_animation_group())
        layout.addWidget(self.create_easing_demo_group())
    
    def create_property_animation_group(self):
        group = QGroupBox("Property Animations")
        layout = QHBoxLayout(group)
        
        self.animated_widget = AnimatedWidget()
        layout.addWidget(self.animated_widget, stretch=1)
        
        controls = QVBoxLayout()
        
        color_btn = QPushButton("Animate Color")
        color_btn.clicked.connect(self.animate_color)
        controls.addWidget(color_btn)
        
        size_btn = QPushButton("Animate Size")
        size_btn.clicked.connect(self.animate_size)
        controls.addWidget(size_btn)
        
        controls.addStretch()
        layout.addLayout(controls)
        
        return group
    
    def create_easing_demo_group(self):
        group = QGroupBox("Easing Curves")
        layout = QVBoxLayout(group)
        
        control_row = QHBoxLayout()
        
        control_row.addWidget(QLabel("Easing:"))
        self.easing_combo = QComboBox()
        easings = [
            ("Linear", QEasingCurve.Type.Linear),
            ("OutBounce", QEasingCurve.Type.OutBounce),
            ("InOutQuad", QEasingCurve.Type.InOutQuad),
            ("OutElastic", QEasingCurve.Type.OutElastic),
            ("OutBack", QEasingCurve.Type.OutBack),
        ]
        for name, curve in easings:
            self.easing_combo.addItem(name, curve)
        control_row.addWidget(self.easing_combo)
        
        control_row.addWidget(QLabel("Duration:"))
        self.duration_slider = QSlider(Qt.Orientation.Horizontal)
        self.duration_slider.setRange(200, 2000)
        self.duration_slider.setValue(1000)
        control_row.addWidget(self.duration_slider)
        
        self.duration_label = QLabel("1000 ms")
        self.duration_slider.valueChanged.connect(
            lambda v: self.duration_label.setText(f"{v} ms")
        )
        control_row.addWidget(self.duration_label)
        
        animate_btn = QPushButton("Animate")
        animate_btn.clicked.connect(self.animate_with_easing)
        control_row.addWidget(animate_btn)
        
        layout.addLayout(control_row)
        
        self.easing_container = QWidget()
        self.easing_container.setMinimumHeight(60)
        layout.addWidget(self.easing_container)
        
        self.easing_button = MovableButton("Move Me")
        self.easing_button.setParent(self.easing_container)
        self.easing_button.move(10, 10)
        
        return group
    
    def animate_color(self):
        anim = QPropertyAnimation(self.animated_widget, b"color")
        anim.setDuration(1000)
        anim.setStartValue(QColor(100, 149, 237))
        anim.setKeyValueAt(0.5, QColor(255, 99, 71))
        anim.setEndValue(QColor(100, 149, 237))
        anim.setLoopCount(2)
        anim.start()
        self.current_anim = anim
    
    def animate_size(self):
        anim = QPropertyAnimation(self.animated_widget, b"radius")
        anim.setDuration(800)
        anim.setStartValue(50)
        anim.setKeyValueAt(0.5, 80)
        anim.setEndValue(50)
        anim.setEasingCurve(QEasingCurve.Type.InOutQuad)
        anim.start()
        self.current_anim = anim
    
    def animate_with_easing(self):
        easing = self.easing_combo.currentData()
        duration = self.duration_slider.value()
        
        container_width = self.easing_container.width()
        button_width = self.easing_button.width()
        
        current_x = self.easing_button.x()
        if current_x > container_width / 2:
            target_x = 10
        else:
            target_x = container_width - button_width - 10
        
        anim = QPropertyAnimation(self.easing_button, b"pos")
        anim.setDuration(duration)
        anim.setStartValue(self.easing_button.pos())
        anim.setEndValue(QPoint(target_x, 10))
        anim.setEasingCurve(easing)
        anim.start()
        self.current_anim = anim


def main():
    app = QApplication(sys.argv)
    window = AnimationsDemo()
    window.show()
    sys.exit(app.exec())


if __name__ == "__main__":
    main()
