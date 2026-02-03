"""
PyQt6 Beginner Example 04: Signals and Slots
============================================

This example demonstrates:
- Connecting signals to slot methods
- Custom signals with pyqtSignal
- Passing data through signals

KEY DIFFERENCE FROM PySide6:
- Use pyqtSignal instead of Signal
- Use pyqtSlot instead of Slot (optional, for optimization)

Run: python 04_signals_slots.py
"""

import sys
from PyQt6.QtWidgets import (
    QApplication, QMainWindow, QWidget, QVBoxLayout, QHBoxLayout,
    QLabel, QPushButton, QLineEdit, QSlider, QProgressBar,
    QSpinBox, QGroupBox, QTextEdit
)
from PyQt6.QtCore import Qt, pyqtSignal, QObject


class DataEmitter(QObject):
    """Custom class that emits signals with data."""
    
    # Define custom signals using pyqtSignal (NOT Signal like in PySide6)
    message_sent = pyqtSignal(str)
    progress_updated = pyqtSignal(int)
    calculation_done = pyqtSignal(float, float, float)  # a, b, result
    
    def send_message(self, text):
        self.message_sent.emit(text)
    
    def update_progress(self, value):
        self.progress_updated.emit(value)
    
    def calculate(self, a, b):
        result = a + b
        self.calculation_done.emit(a, b, result)


class SignalSlotsDemo(QMainWindow):
    """Demonstrates signals and slots mechanism."""
    
    # Custom signal for this class (PyQt6 syntax)
    counter_changed = pyqtSignal(int)
    
    def __init__(self):
        super().__init__()
        self.setWindowTitle("PyQt6 Signals and Slots Demo")
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
        
        self.setup_connections()
    
    def create_basic_signals_group(self):
        group = QGroupBox("Basic Signals")
        layout = QVBoxLayout(group)
        
        btn_layout = QHBoxLayout()
        
        self.count_btn = QPushButton("Click me (0)")
        self.count_btn.clicked.connect(self.on_button_clicked)
        btn_layout.addWidget(self.count_btn)
        
        reset_btn = QPushButton("Reset")
        reset_btn.clicked.connect(lambda: self.reset_counter())
        btn_layout.addWidget(reset_btn)
        
        layout.addLayout(btn_layout)
        
        text_layout = QHBoxLayout()
        text_layout.addWidget(QLabel("Type here:"))
        self.text_input = QLineEdit()
        self.text_input.textChanged.connect(self.on_text_changed)
        text_layout.addWidget(self.text_input)
        layout.addLayout(text_layout)
        
        self.text_display = QLabel("You typed: ")
        layout.addWidget(self.text_display)
        
        return group
    
    def create_slider_signals_group(self):
        group = QGroupBox("Synchronized Widgets")
        layout = QVBoxLayout(group)
        
        sync_layout = QHBoxLayout()
        
        self.slider = QSlider(Qt.Orientation.Horizontal)
        self.slider.setRange(0, 100)
        self.slider.setValue(50)
        sync_layout.addWidget(self.slider)
        
        self.spinbox = QSpinBox()
        self.spinbox.setRange(0, 100)
        self.spinbox.setValue(50)
        sync_layout.addWidget(self.spinbox)
        
        self.progress = QProgressBar()
        self.progress.setRange(0, 100)
        self.progress.setValue(50)
        sync_layout.addWidget(self.progress)
        
        # Bidirectional connection
        self.slider.valueChanged.connect(self.spinbox.setValue)
        self.slider.valueChanged.connect(self.progress.setValue)
        self.spinbox.valueChanged.connect(self.slider.setValue)
        
        layout.addLayout(sync_layout)
        
        return group
    
    def create_custom_signals_group(self):
        group = QGroupBox("Custom Signals (pyqtSignal)")
        layout = QVBoxLayout(group)
        
        msg_layout = QHBoxLayout()
        self.msg_input = QLineEdit()
        self.msg_input.setPlaceholderText("Enter a message...")
        msg_layout.addWidget(self.msg_input)
        
        send_btn = QPushButton("Send Message")
        send_btn.clicked.connect(self.send_message)
        msg_layout.addWidget(send_btn)
        layout.addLayout(msg_layout)
        
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
        calc_layout.addWidget(self.result_label)
        calc_layout.addStretch()
        
        layout.addLayout(calc_layout)
        
        return group
    
    def create_log_group(self):
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
        self.emitter.message_sent.connect(self.on_message_received)
        self.emitter.calculation_done.connect(self.on_calculation_done)
        self.counter_changed.connect(self.on_counter_changed)
    
    def log(self, message):
        self.log_display.append(message)
    
    def on_button_clicked(self):
        self.click_count += 1
        self.count_btn.setText(f"Click me ({self.click_count})")
        self.counter_changed.emit(self.click_count)
        self.log(f"Button clicked! Count: {self.click_count}")
    
    def reset_counter(self):
        self.click_count = 0
        self.count_btn.setText("Click me (0)")
        self.counter_changed.emit(0)
        self.log("Counter reset to 0")
    
    def on_text_changed(self, text):
        self.text_display.setText(f"You typed: {text}")
    
    def on_counter_changed(self, value):
        if value > 0 and value % 5 == 0:
            self.log(f"🎉 Counter milestone reached: {value}")
    
    def send_message(self):
        text = self.msg_input.text()
        if text:
            self.emitter.send_message(text)
            self.msg_input.clear()
    
    def on_message_received(self, message):
        self.log(f"📨 Message received: '{message}'")
    
    def do_calculation(self):
        a = self.num_a.value()
        b = self.num_b.value()
        self.emitter.calculate(a, b)
    
    def on_calculation_done(self, a, b, result):
        self.result_label.setText(str(int(result)))
        self.log(f"🔢 Calculation: {a} + {b} = {result}")


def main():
    app = QApplication(sys.argv)
    window = SignalSlotsDemo()
    window.show()
    sys.exit(app.exec())


if __name__ == "__main__":
    main()
