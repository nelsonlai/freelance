"""
PySide6 Advanced Example 02: Animations
=======================================

This example demonstrates:
- QPropertyAnimation for property animations
- QSequentialAnimationGroup and QParallelAnimationGroup
- QEasingCurve for animation easing
- Custom animated properties using Property

Run: python 02_animations.py
"""

import sys
from PySide6.QtWidgets import (
    QApplication, QMainWindow, QWidget, QVBoxLayout, QHBoxLayout,
    QPushButton, QLabel, QGroupBox, QComboBox, QSlider, QFrame,
    QGraphicsView, QGraphicsScene, QGraphicsRectItem
)
from PySide6.QtCore import (
    Qt, Property, QPropertyAnimation, QSequentialAnimationGroup,
    QParallelAnimationGroup, QEasingCurve, QPoint, QSize, QRect,
    QTimer, Signal
)
from PySide6.QtGui import QPainter, QColor, QBrush, QPen


class AnimatedWidget(QWidget):
    """A widget with custom animatable properties."""
    
    def __init__(self, parent=None):
        super().__init__(parent)
        self._color = QColor(100, 149, 237)  # Cornflower blue
        self._radius = 50
        self._rotation = 0
        
        self.setMinimumSize(200, 200)
    
    # Color property
    def get_color(self):
        return self._color
    
    def set_color(self, color):
        self._color = color
        self.update()
    
    color = Property(QColor, get_color, set_color)
    
    # Radius property
    def get_radius(self):
        return self._radius
    
    def set_radius(self, radius):
        self._radius = radius
        self.update()
    
    radius = Property(int, get_radius, set_radius)
    
    # Rotation property
    def get_rotation(self):
        return self._rotation
    
    def set_rotation(self, rotation):
        self._rotation = rotation
        self.update()
    
    rotation = Property(int, get_rotation, set_rotation)
    
    def paintEvent(self, event):
        painter = QPainter(self)
        painter.setRenderHint(QPainter.RenderHint.Antialiasing)
        
        # Translate to center
        center = self.rect().center()
        painter.translate(center)
        painter.rotate(self._rotation)
        
        # Draw the shape
        painter.setBrush(QBrush(self._color))
        painter.setPen(QPen(self._color.darker(120), 2))
        painter.drawEllipse(-self._radius, -self._radius, 
                           self._radius * 2, self._radius * 2)


class MovableButton(QPushButton):
    """A button that can be animated."""
    
    def __init__(self, text, parent=None):
        super().__init__(text, parent)
        self.setFixedSize(120, 40)


class AnimatedCard(QFrame):
    """A card widget with animation support."""
    
    clicked = Signal()
    
    def __init__(self, title, color, parent=None):
        super().__init__(parent)
        self.title = title
        self._color = color
        self._scale = 1.0
        self._opacity = 1.0
        
        self.setFixedSize(150, 100)
        self.setStyleSheet(f"""
            QFrame {{
                background-color: {color.name()};
                border-radius: 10px;
            }}
        """)
        
        layout = QVBoxLayout(self)
        label = QLabel(title)
        label.setStyleSheet("color: white; font-size: 16px; font-weight: bold;")
        label.setAlignment(Qt.AlignmentFlag.AlignCenter)
        layout.addWidget(label)
    
    def get_scale(self):
        return self._scale
    
    def set_scale(self, scale):
        self._scale = scale
        self.setFixedSize(int(150 * scale), int(100 * scale))
    
    scale = Property(float, get_scale, set_scale)
    
    def mousePressEvent(self, event):
        self.clicked.emit()


class AnimationsDemo(QMainWindow):
    """Main window demonstrating animations."""
    
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Animations Demo")
        self.setMinimumSize(900, 700)
        
        central = QWidget()
        self.setCentralWidget(central)
        layout = QVBoxLayout(central)
        
        # Create demo sections
        layout.addWidget(self.create_property_animation_group())
        layout.addWidget(self.create_easing_demo_group())
        layout.addWidget(self.create_group_animation_group())
    
    def create_property_animation_group(self):
        """Property animation demonstrations."""
        group = QGroupBox("Property Animations")
        layout = QHBoxLayout(group)
        
        # Animated widget
        self.animated_widget = AnimatedWidget()
        layout.addWidget(self.animated_widget, stretch=1)
        
        # Controls
        controls = QVBoxLayout()
        
        # Color animation
        color_btn = QPushButton("Animate Color")
        color_btn.clicked.connect(self.animate_color)
        controls.addWidget(color_btn)
        
        # Size animation
        size_btn = QPushButton("Animate Size")
        size_btn.clicked.connect(self.animate_size)
        controls.addWidget(size_btn)
        
        # Rotation animation
        rotate_btn = QPushButton("Animate Rotation")
        rotate_btn.clicked.connect(self.animate_rotation)
        controls.addWidget(rotate_btn)
        
        # Combined animation
        combined_btn = QPushButton("Combined Animation")
        combined_btn.clicked.connect(self.animate_combined)
        controls.addWidget(combined_btn)
        
        controls.addStretch()
        layout.addLayout(controls)
        
        return group
    
    def create_easing_demo_group(self):
        """Easing curves demonstration."""
        group = QGroupBox("Easing Curves")
        layout = QVBoxLayout(group)
        
        # Controls row
        control_row = QHBoxLayout()
        
        control_row.addWidget(QLabel("Easing:"))
        self.easing_combo = QComboBox()
        easings = [
            ("Linear", QEasingCurve.Type.Linear),
            ("InQuad", QEasingCurve.Type.InQuad),
            ("OutQuad", QEasingCurve.Type.OutQuad),
            ("InOutQuad", QEasingCurve.Type.InOutQuad),
            ("InCubic", QEasingCurve.Type.InCubic),
            ("OutCubic", QEasingCurve.Type.OutCubic),
            ("InOutCubic", QEasingCurve.Type.InOutCubic),
            ("InBounce", QEasingCurve.Type.InBounce),
            ("OutBounce", QEasingCurve.Type.OutBounce),
            ("InOutBounce", QEasingCurve.Type.InOutBounce),
            ("InElastic", QEasingCurve.Type.InElastic),
            ("OutElastic", QEasingCurve.Type.OutElastic),
            ("InBack", QEasingCurve.Type.InBack),
            ("OutBack", QEasingCurve.Type.OutBack),
        ]
        for name, curve in easings:
            self.easing_combo.addItem(name, curve)
        control_row.addWidget(self.easing_combo)
        
        control_row.addWidget(QLabel("Duration:"))
        self.duration_slider = QSlider(Qt.Orientation.Horizontal)
        self.duration_slider.setRange(200, 3000)
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
        
        # Animation area
        self.easing_container = QWidget()
        self.easing_container.setMinimumHeight(60)
        layout.addWidget(self.easing_container)
        
        self.easing_button = MovableButton("Move Me")
        self.easing_button.setParent(self.easing_container)
        self.easing_button.move(10, 10)
        
        return group
    
    def create_group_animation_group(self):
        """Group animations demonstration."""
        group = QGroupBox("Animation Groups")
        layout = QVBoxLayout(group)
        
        # Cards container
        cards_layout = QHBoxLayout()
        
        self.cards = []
        colors = [
            QColor(231, 76, 60),   # Red
            QColor(46, 204, 113),  # Green
            QColor(52, 152, 219),  # Blue
            QColor(155, 89, 182),  # Purple
        ]
        
        for i, color in enumerate(colors):
            card = AnimatedCard(f"Card {i + 1}", color)
            card.clicked.connect(lambda idx=i: self.bounce_card(idx))
            cards_layout.addWidget(card)
            self.cards.append(card)
        
        layout.addLayout(cards_layout)
        
        # Buttons
        btn_layout = QHBoxLayout()
        
        seq_btn = QPushButton("Sequential Animation")
        seq_btn.clicked.connect(self.animate_sequential)
        btn_layout.addWidget(seq_btn)
        
        par_btn = QPushButton("Parallel Animation")
        par_btn.clicked.connect(self.animate_parallel)
        btn_layout.addWidget(par_btn)
        
        wave_btn = QPushButton("Wave Animation")
        wave_btn.clicked.connect(self.animate_wave)
        btn_layout.addWidget(wave_btn)
        
        reset_btn = QPushButton("Reset")
        reset_btn.clicked.connect(self.reset_cards)
        btn_layout.addWidget(reset_btn)
        
        layout.addLayout(btn_layout)
        
        return group
    
    # Property animation methods
    def animate_color(self):
        """Animate the color property."""
        anim = QPropertyAnimation(self.animated_widget, b"color")
        anim.setDuration(1000)
        anim.setStartValue(QColor(100, 149, 237))  # Blue
        anim.setKeyValueAt(0.5, QColor(255, 99, 71))  # Red
        anim.setEndValue(QColor(100, 149, 237))  # Blue
        anim.setLoopCount(2)
        anim.start()
        
        # Keep reference
        self.current_anim = anim
    
    def animate_size(self):
        """Animate the radius property."""
        anim = QPropertyAnimation(self.animated_widget, b"radius")
        anim.setDuration(800)
        anim.setStartValue(50)
        anim.setKeyValueAt(0.5, 80)
        anim.setEndValue(50)
        anim.setEasingCurve(QEasingCurve.Type.InOutQuad)
        anim.start()
        
        self.current_anim = anim
    
    def animate_rotation(self):
        """Animate the rotation property."""
        anim = QPropertyAnimation(self.animated_widget, b"rotation")
        anim.setDuration(1500)
        anim.setStartValue(0)
        anim.setEndValue(360)
        anim.setEasingCurve(QEasingCurve.Type.InOutCubic)
        anim.start()
        
        self.current_anim = anim
    
    def animate_combined(self):
        """Animate multiple properties in parallel."""
        group = QParallelAnimationGroup()
        
        # Color
        color_anim = QPropertyAnimation(self.animated_widget, b"color")
        color_anim.setDuration(1500)
        color_anim.setStartValue(QColor(100, 149, 237))
        color_anim.setKeyValueAt(0.5, QColor(50, 205, 50))
        color_anim.setEndValue(QColor(100, 149, 237))
        group.addAnimation(color_anim)
        
        # Size
        size_anim = QPropertyAnimation(self.animated_widget, b"radius")
        size_anim.setDuration(1500)
        size_anim.setStartValue(50)
        size_anim.setKeyValueAt(0.5, 80)
        size_anim.setEndValue(50)
        size_anim.setEasingCurve(QEasingCurve.Type.InOutQuad)
        group.addAnimation(size_anim)
        
        # Rotation
        rotate_anim = QPropertyAnimation(self.animated_widget, b"rotation")
        rotate_anim.setDuration(1500)
        rotate_anim.setStartValue(0)
        rotate_anim.setEndValue(360)
        group.addAnimation(rotate_anim)
        
        group.start()
        self.current_anim = group
    
    # Easing demo methods
    def animate_with_easing(self):
        """Animate with selected easing curve."""
        easing = self.easing_combo.currentData()
        duration = self.duration_slider.value()
        
        container_width = self.easing_container.width()
        button_width = self.easing_button.width()
        
        end_x = container_width - button_width - 20
        start_x = 10
        
        # Determine direction based on current position
        current_x = self.easing_button.x()
        if current_x > container_width / 2:
            target_x = start_x
        else:
            target_x = end_x
        
        anim = QPropertyAnimation(self.easing_button, b"pos")
        anim.setDuration(duration)
        anim.setStartValue(self.easing_button.pos())
        anim.setEndValue(QPoint(target_x, 10))
        anim.setEasingCurve(easing)
        anim.start()
        
        self.current_anim = anim
    
    # Group animation methods
    def bounce_card(self, index):
        """Bounce animation for a card."""
        card = self.cards[index]
        
        anim = QPropertyAnimation(card, b"scale")
        anim.setDuration(300)
        anim.setStartValue(1.0)
        anim.setKeyValueAt(0.5, 1.15)
        anim.setEndValue(1.0)
        anim.setEasingCurve(QEasingCurve.Type.OutBounce)
        anim.start()
        
        self.current_anim = anim
    
    def animate_sequential(self):
        """Animate cards one after another."""
        group = QSequentialAnimationGroup()
        
        for card in self.cards:
            anim = QPropertyAnimation(card, b"pos")
            anim.setDuration(300)
            current_pos = card.pos()
            anim.setStartValue(current_pos)
            anim.setKeyValueAt(0.5, QPoint(current_pos.x(), current_pos.y() - 30))
            anim.setEndValue(current_pos)
            anim.setEasingCurve(QEasingCurve.Type.OutBounce)
            group.addAnimation(anim)
        
        group.start()
        self.current_anim = group
    
    def animate_parallel(self):
        """Animate all cards at once."""
        group = QParallelAnimationGroup()
        
        for card in self.cards:
            anim = QPropertyAnimation(card, b"pos")
            anim.setDuration(500)
            current_pos = card.pos()
            anim.setStartValue(current_pos)
            anim.setKeyValueAt(0.5, QPoint(current_pos.x(), current_pos.y() - 40))
            anim.setEndValue(current_pos)
            anim.setEasingCurve(QEasingCurve.Type.OutBounce)
            group.addAnimation(anim)
        
        group.start()
        self.current_anim = group
    
    def animate_wave(self):
        """Create a wave effect across cards."""
        group = QSequentialAnimationGroup()
        
        # First wave
        for i, card in enumerate(self.cards):
            inner_group = QSequentialAnimationGroup()
            
            # Delay based on position
            if i > 0:
                from PySide6.QtCore import QPauseAnimation
                inner_group.addPause(100)
            
            anim = QPropertyAnimation(card, b"pos")
            anim.setDuration(400)
            current_pos = card.pos()
            anim.setStartValue(current_pos)
            anim.setKeyValueAt(0.5, QPoint(current_pos.x(), current_pos.y() - 50))
            anim.setEndValue(current_pos)
            anim.setEasingCurve(QEasingCurve.Type.OutQuad)
            
            # Add to parallel group that starts immediately
            if i == 0:
                group.addAnimation(anim)
            else:
                # Use timer for delayed start
                QTimer.singleShot(i * 100, lambda a=anim: a.start())
                self._wave_anims = getattr(self, '_wave_anims', [])
                self._wave_anims.append(anim)
        
        group.start()
        self.current_anim = group
    
    def reset_cards(self):
        """Reset card positions and scales."""
        for card in self.cards:
            card.set_scale(1.0)


def main():
    app = QApplication(sys.argv)
    window = AnimationsDemo()
    window.show()
    sys.exit(app.exec())


if __name__ == "__main__":
    main()
