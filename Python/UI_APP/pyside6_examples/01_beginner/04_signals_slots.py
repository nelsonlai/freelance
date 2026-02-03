"""
PySide6 Beginner Example 04: Signals and Slots
==============================================

This example demonstrates:
- Connecting signals to slot methods
- Using lambda functions for connections
- Custom signals with Signal class
- Passing data through signals
- Disconnecting signals

Run: python 04_signals_slots.py
"""

import sys
from PySide6.QtWidgets import (
    QApplication, QMainWindow, QWidget, QVBoxLayout, QHBoxLayout,
    QLabel, QPushButton, QLineEdit, QSlider, QProgressBar,
    QSpinBox, QGroupBox, QTextEdit
)
from PySide6.QtCore import Qt, Signal, QObject


class DataEmitter(QObject):
    """Custom class that emits signals with data."""
    
    # Define custom signals
    message_sent = Signal(str)
    progress_updated = Signal(int)
    calculation_done = Signal(float, float, float)  # a, b, result
    
    def send_message(self, text):
        """Send a message signal."""
        self.message_sent.emit(text)
    
    def update_progress(self, value):
        """Update progress signal."""
        self.progress_updated.emit(value)
    
    def calculate(self, a, b):
        """Perform calculation and emit result."""
        result = a + b
        self.calculation_done.emit(a, b, result)


class SignalSlotsDemo(QMainWindow):
    """Demonstrates signals and slots mechanism."""
    
    # Custom signal for this class
    counter_changed = Signal(int)
    
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Signals and Slots Demo")
        self.setMinimumSize(600, 600)
        
        self.click_count = 0
        self.emitter = DataEmitter()
        
        central = QWidget()
        self.setCentralWidget(central)
        layout = QVBoxLayout(central)
        
        layout.addWidget(self.create_basic_signals_group())
        layout.addWidget(self.create_slider_signals_group())
        layout.addWidget(self.create_custom_signals_group())
        layout.addWidget(self.create_log_group())
        
        # Connect custom signals
        self.setup_connections()
    
    def create_basic_signals_group(self):
        """Basic signal connections."""
        group = QGroupBox("Basic Signals")
        layout = QVBoxLayout(group)
        
        # Button signals
        btn_layout = QHBoxLayout()
        
        # Method connection
        self.count_btn = QPushButton("Click me (0)")
        self.count_btn.clicked.connect(self.on_button_clicked)
        btn_layout.addWidget(self.count_btn)
        
        # Lambda connection
        reset_btn = QPushButton("Reset")
        reset_btn.clicked.connect(lambda: self.reset_counter())
        btn_layout.addWidget(reset_btn)
        
        layout.addLayout(btn_layout)
        
        # Text input signals
        text_layout = QHBoxLayout()
        text_layout.addWidget(QLabel("Type here:"))
        self.text_input = QLineEdit()
        self.text_input.setPlaceholderText("Text changes are tracked...")
        
        # Connect to multiple slots
        self.text_input.textChanged.connect(self.on_text_changed)
        self.text_input.returnPressed.connect(self.on_return_pressed)
        text_layout.addWidget(self.text_input)
        
        layout.addLayout(text_layout)
        
        # Display
        self.text_display = QLabel("You typed: ")
        layout.addWidget(self.text_display)
        
        return group
    
    def create_slider_signals_group(self):
        """Slider and spinbox synchronization."""
        group = QGroupBox("Synchronized Widgets (Slider ↔ SpinBox)")
        layout = QVBoxLayout(group)
        
        sync_layout = QHBoxLayout()
        
        # Slider
        self.slider = QSlider(Qt.Orientation.Horizontal)
        self.slider.setRange(0, 100)
        self.slider.setValue(50)
        sync_layout.addWidget(self.slider)
        
        # SpinBox
        self.spinbox = QSpinBox()
        self.spinbox.setRange(0, 100)
        self.spinbox.setValue(50)
        sync_layout.addWidget(self.spinbox)
        
        # Progress bar
        self.progress = QProgressBar()
        self.progress.setRange(0, 100)
        self.progress.setValue(50)
        sync_layout.addWidget(self.progress)
        
        # Connect them together (bidirectional)
        self.slider.valueChanged.connect(self.spinbox.setValue)
        self.slider.valueChanged.connect(self.progress.setValue)
        self.spinbox.valueChanged.connect(self.slider.setValue)
        
        layout.addLayout(sync_layout)
        
        # Value label
        self.value_label = QLabel("Current value: 50")
        self.slider.valueChanged.connect(
            lambda v: self.value_label.setText(f"Current value: {v}")
        )
        layout.addWidget(self.value_label)
        
        return group
    
    def create_custom_signals_group(self):
        """Custom signal demonstrations."""
        group = QGroupBox("Custom Signals")
        layout = QVBoxLayout(group)
        
        # Message signal
        msg_layout = QHBoxLayout()
        self.msg_input = QLineEdit()
        self.msg_input.setPlaceholderText("Enter a message...")
        msg_layout.addWidget(self.msg_input)
        
        send_btn = QPushButton("Send Message")
        send_btn.clicked.connect(self.send_message)
        msg_layout.addWidget(send_btn)
        layout.addLayout(msg_layout)
        
        # Calculation signal
        calc_layout = QHBoxLayout()
        calc_layout.addWidget(QLabel("Calculate:"))
        
        self.num_a = QSpinBox()
        self.num_a.setRange(-100, 100)
        self.num_a.setValue(5)
        calc_layout.addWidget(self.num_a)
        
        calc_layout.addWidget(QLabel("+"))
        
        self.num_b = QSpinBox()
        self.num_b.setRange(-100, 100)
        self.num_b.setValue(3)
        calc_layout.addWidget(self.num_b)
        
        calc_btn = QPushButton("=")
        calc_btn.clicked.connect(self.do_calculation)
        calc_layout.addWidget(calc_btn)
        
        self.result_label = QLabel("?")
        self.result_label.setStyleSheet("font-weight: bold; min-width: 50px;")
        calc_layout.addWidget(self.result_label)
        calc_layout.addStretch()
        
        layout.addLayout(calc_layout)
        
        return group
    
    def create_log_group(self):
        """Log display."""
        group = QGroupBox("Event Log")
        layout = QVBoxLayout(group)
        
        self.log_display = QTextEdit()
        self.log_display.setReadOnly(True)
        self.log_display.setMaximumHeight(150)
        layout.addWidget(self.log_display)
        
        clear_btn = QPushButton("Clear Log")
        clear_btn.clicked.connect(self.log_display.clear)
        layout.addWidget(clear_btn)
        
        return group
    
    def setup_connections(self):
        """Set up custom signal connections."""
        # Connect custom signals from emitter
        self.emitter.message_sent.connect(self.on_message_received)
        self.emitter.calculation_done.connect(self.on_calculation_done)
        
        # Connect class signal
        self.counter_changed.connect(self.on_counter_changed)
    
    def log(self, message):
        """Add message to log."""
        self.log_display.append(message)
    
    # Slot methods
    def on_button_clicked(self):
        """Handle button click."""
        self.click_count += 1
        self.count_btn.setText(f"Click me ({self.click_count})")
        self.counter_changed.emit(self.click_count)
        self.log(f"Button clicked! Count: {self.click_count}")
    
    def reset_counter(self):
        """Reset the counter."""
        self.click_count = 0
        self.count_btn.setText("Click me (0)")
        self.counter_changed.emit(0)
        self.log("Counter reset to 0")
    
    def on_text_changed(self, text):
        """Handle text change."""
        self.text_display.setText(f"You typed: {text}")
    
    def on_return_pressed(self):
        """Handle Enter key press."""
        text = self.text_input.text()
        self.log(f"Enter pressed! Text: '{text}'")
        self.text_input.clear()
    
    def on_counter_changed(self, value):
        """Handle counter change signal."""
        if value > 0 and value % 5 == 0:
            self.log(f"🎉 Counter milestone reached: {value}")
    
    def send_message(self):
        """Send message through custom signal."""
        text = self.msg_input.text()
        if text:
            self.emitter.send_message(text)
            self.msg_input.clear()
    
    def on_message_received(self, message):
        """Handle received message."""
        self.log(f"📨 Message received: '{message}'")
    
    def do_calculation(self):
        """Trigger calculation."""
        a = self.num_a.value()
        b = self.num_b.value()
        self.emitter.calculate(a, b)
    
    def on_calculation_done(self, a, b, result):
        """Handle calculation result."""
        self.result_label.setText(str(int(result)))
        self.log(f"🔢 Calculation: {a} + {b} = {result}")


def main():
    app = QApplication(sys.argv)
    window = SignalSlotsDemo()
    window.show()
    sys.exit(app.exec())


if __name__ == "__main__":
    main()
