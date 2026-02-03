"""
PyQt6 Intermediate Example 03: Multithreading with QThread
==========================================================

This example demonstrates:
- Using QThread with the worker pattern
- Communicating between threads using signals
- Progress reporting from background tasks

KEY DIFFERENCE FROM PySide6:
- Use pyqtSignal instead of Signal

Run: python 03_threading.py
"""

import sys
import time
import random
from PyQt6.QtWidgets import (
    QApplication, QMainWindow, QWidget, QVBoxLayout, QHBoxLayout,
    QPushButton, QProgressBar, QLabel, QTextEdit, QGroupBox
)
from PyQt6.QtCore import Qt, QThread, QObject, pyqtSignal, QMutex


class DownloadWorker(QObject):
    """Worker that simulates a download operation."""
    
    # Use pyqtSignal (PyQt6 syntax)
    started = pyqtSignal()
    progress = pyqtSignal(int, str)
    finished = pyqtSignal(bool, str)
    
    def __init__(self):
        super().__init__()
        self._is_cancelled = False
        self._mutex = QMutex()
    
    def run(self):
        self.started.emit()
        self._is_cancelled = False
        
        try:
            total_files = 10
            
            for i in range(total_files):
                self._mutex.lock()
                cancelled = self._is_cancelled
                self._mutex.unlock()
                
                if cancelled:
                    self.finished.emit(False, "Download cancelled")
                    return
                
                file_name = f"file_{i + 1}.dat"
                self.progress.emit(
                    int((i / total_files) * 100),
                    f"Downloading {file_name}..."
                )
                
                time.sleep(random.uniform(0.2, 0.8))
            
            self.progress.emit(100, "Download complete!")
            self.finished.emit(True, f"Downloaded {total_files} files")
            
        except Exception as e:
            self.finished.emit(False, f"Error: {str(e)}")
    
    def cancel(self):
        self._mutex.lock()
        self._is_cancelled = True
        self._mutex.unlock()


class ThreadingDemo(QMainWindow):
    """Main window demonstrating threading patterns."""
    
    def __init__(self):
        super().__init__()
        self.setWindowTitle("PyQt6 Threading Demo")
        self.setMinimumSize(600, 400)
        
        self.download_thread = None
        self.download_worker = None
        
        central = QWidget()
        self.setCentralWidget(central)
        layout = QVBoxLayout(central)
        
        layout.addWidget(self.create_download_group())
        layout.addWidget(self.create_log_group())
    
    def create_download_group(self):
        group = QGroupBox("Download Simulation (Worker Pattern)")
        layout = QVBoxLayout(group)
        
        # Status
        self.download_status = QLabel("Ready to download")
        layout.addWidget(self.download_status)
        
        # Progress bar
        self.download_progress = QProgressBar()
        self.download_progress.setRange(0, 100)
        layout.addWidget(self.download_progress)
        
        # Buttons
        btn_layout = QHBoxLayout()
        
        self.download_start_btn = QPushButton("Start Download")
        self.download_start_btn.clicked.connect(self.start_download)
        btn_layout.addWidget(self.download_start_btn)
        
        self.download_cancel_btn = QPushButton("Cancel")
        self.download_cancel_btn.setEnabled(False)
        self.download_cancel_btn.clicked.connect(self.cancel_download)
        btn_layout.addWidget(self.download_cancel_btn)
        
        layout.addLayout(btn_layout)
        
        return group
    
    def create_log_group(self):
        group = QGroupBox("Event Log")
        layout = QVBoxLayout(group)
        
        self.log_display = QTextEdit()
        self.log_display.setReadOnly(True)
        layout.addWidget(self.log_display)
        
        return group
    
    def log(self, message):
        self.log_display.append(f"[{time.strftime('%H:%M:%S')}] {message}")
    
    def start_download(self):
        self.download_thread = QThread()
        self.download_worker = DownloadWorker()
        self.download_worker.moveToThread(self.download_thread)
        
        # Connect signals
        self.download_thread.started.connect(self.download_worker.run)
        self.download_worker.started.connect(self.on_download_started)
        self.download_worker.progress.connect(self.on_download_progress)
        self.download_worker.finished.connect(self.on_download_finished)
        self.download_worker.finished.connect(self.download_thread.quit)
        self.download_worker.finished.connect(self.download_worker.deleteLater)
        self.download_thread.finished.connect(self.download_thread.deleteLater)
        
        self.download_thread.start()
    
    def cancel_download(self):
        if self.download_worker:
            self.download_worker.cancel()
            self.log("Download cancellation requested")
    
    def on_download_started(self):
        self.download_start_btn.setEnabled(False)
        self.download_cancel_btn.setEnabled(True)
        self.download_progress.setValue(0)
        self.log("Download started")
    
    def on_download_progress(self, percentage, status):
        self.download_progress.setValue(percentage)
        self.download_status.setText(status)
    
    def on_download_finished(self, success, message):
        self.download_start_btn.setEnabled(True)
        self.download_cancel_btn.setEnabled(False)
        self.download_status.setText(message)
        self.log(f"Download {'succeeded' if success else 'failed'}: {message}")
    
    def closeEvent(self, event):
        # Use try/except as Qt may have already deleted objects
        try:
            if self.download_worker:
                self.download_worker.cancel()
        except RuntimeError:
            pass
        
        try:
            if self.download_thread and self.download_thread.isRunning():
                self.download_thread.quit()
                self.download_thread.wait(1000)
        except RuntimeError:
            pass
        
        event.accept()


def main():
    app = QApplication(sys.argv)
    window = ThreadingDemo()
    window.show()
    sys.exit(app.exec())


if __name__ == "__main__":
    main()
