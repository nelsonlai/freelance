"""
PySide6 Intermediate Example 03: Multithreading with QThread
============================================================

This example demonstrates:
- Using QThread with the worker pattern
- Communicating between threads using signals
- Progress reporting from background tasks
- Cancelling long-running operations
- Thread pool for multiple tasks

Run: python 03_threading.py
"""

import sys
import time
import random
from PySide6.QtWidgets import (
    QApplication, QMainWindow, QWidget, QVBoxLayout, QHBoxLayout,
    QPushButton, QProgressBar, QLabel, QTextEdit, QGroupBox,
    QSpinBox, QListWidget, QListWidgetItem
)
from PySide6.QtCore import Qt, QThread, QObject, Signal, QMutex, QThreadPool, QRunnable


class DownloadWorker(QObject):
    """Worker that simulates a download operation."""
    
    started = Signal()
    progress = Signal(int, str)  # percentage, status message
    finished = Signal(bool, str)  # success, result message
    
    def __init__(self):
        super().__init__()
        self._is_cancelled = False
        self._mutex = QMutex()
    
    def run(self):
        """Perform the download simulation."""
        self.started.emit()
        self._is_cancelled = False
        
        try:
            total_files = 10
            
            for i in range(total_files):
                # Check for cancellation
                self._mutex.lock()
                cancelled = self._is_cancelled
                self._mutex.unlock()
                
                if cancelled:
                    self.finished.emit(False, "Download cancelled by user")
                    return
                
                # Simulate downloading a file
                file_name = f"file_{i + 1}.dat"
                self.progress.emit(
                    int((i / total_files) * 100),
                    f"Downloading {file_name}..."
                )
                
                # Simulate variable download time
                time.sleep(random.uniform(0.2, 0.8))
            
            self.progress.emit(100, "Download complete!")
            self.finished.emit(True, f"Successfully downloaded {total_files} files")
            
        except Exception as e:
            self.finished.emit(False, f"Error: {str(e)}")
    
    def cancel(self):
        """Request cancellation of the operation."""
        self._mutex.lock()
        self._is_cancelled = True
        self._mutex.unlock()


class ComputeWorker(QObject):
    """Worker that performs heavy computation."""
    
    started = Signal()
    progress = Signal(int)
    result = Signal(float)
    finished = Signal()
    
    def __init__(self, iterations):
        super().__init__()
        self.iterations = iterations
        self._is_cancelled = False
    
    def run(self):
        """Perform computation."""
        self.started.emit()
        
        total = 0.0
        
        for i in range(self.iterations):
            if self._is_cancelled:
                break
            
            # Some computation
            total += (i ** 0.5) * random.random()
            
            # Report progress every 1000 iterations
            if i % 1000 == 0:
                progress = int((i / self.iterations) * 100)
                self.progress.emit(progress)
        
        self.progress.emit(100)
        self.result.emit(total)
        self.finished.emit()
    
    def cancel(self):
        self._is_cancelled = True


class TaskRunner(QRunnable):
    """Runnable task for thread pool."""
    
    class Signals(QObject):
        started = Signal(int)
        progress = Signal(int, int)  # task_id, progress
        finished = Signal(int, str)  # task_id, result
    
    def __init__(self, task_id, duration):
        super().__init__()
        self.task_id = task_id
        self.duration = duration
        self.signals = TaskRunner.Signals()
    
    def run(self):
        """Run the task."""
        self.signals.started.emit(self.task_id)
        
        steps = 10
        for i in range(steps):
            time.sleep(self.duration / steps)
            self.signals.progress.emit(self.task_id, int((i + 1) / steps * 100))
        
        self.signals.finished.emit(
            self.task_id, 
            f"Task {self.task_id} completed in {self.duration:.1f}s"
        )


class ThreadingDemo(QMainWindow):
    """Main window demonstrating threading patterns."""
    
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Multithreading Demo")
        self.setMinimumSize(700, 600)
        
        # Thread management
        self.download_thread = None
        self.download_worker = None
        self.compute_thread = None
        self.compute_worker = None
        self.thread_pool = QThreadPool.globalInstance()
        
        central = QWidget()
        self.setCentralWidget(central)
        layout = QVBoxLayout(central)
        
        layout.addWidget(self.create_download_group())
        layout.addWidget(self.create_compute_group())
        layout.addWidget(self.create_pool_group())
        layout.addWidget(self.create_log_group())
    
    def create_download_group(self):
        """Download simulation section."""
        group = QGroupBox("Simulated Download (Worker Pattern)")
        layout = QVBoxLayout(group)
        
        # Status
        status_layout = QHBoxLayout()
        self.download_status = QLabel("Ready to download")
        status_layout.addWidget(self.download_status)
        layout.addLayout(status_layout)
        
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
    
    def create_compute_group(self):
        """Heavy computation section."""
        group = QGroupBox("Heavy Computation (Worker Pattern)")
        layout = QVBoxLayout(group)
        
        # Settings
        settings_layout = QHBoxLayout()
        settings_layout.addWidget(QLabel("Iterations:"))
        self.iterations_spin = QSpinBox()
        self.iterations_spin.setRange(10000, 10000000)
        self.iterations_spin.setSingleStep(10000)
        self.iterations_spin.setValue(100000)
        settings_layout.addWidget(self.iterations_spin)
        settings_layout.addStretch()
        layout.addLayout(settings_layout)
        
        # Progress
        self.compute_progress = QProgressBar()
        layout.addWidget(self.compute_progress)
        
        # Result
        self.compute_result = QLabel("Result: --")
        layout.addWidget(self.compute_result)
        
        # Buttons
        btn_layout = QHBoxLayout()
        self.compute_start_btn = QPushButton("Start Computation")
        self.compute_start_btn.clicked.connect(self.start_computation)
        btn_layout.addWidget(self.compute_start_btn)
        
        self.compute_cancel_btn = QPushButton("Cancel")
        self.compute_cancel_btn.setEnabled(False)
        self.compute_cancel_btn.clicked.connect(self.cancel_computation)
        btn_layout.addWidget(self.compute_cancel_btn)
        
        layout.addLayout(btn_layout)
        
        return group
    
    def create_pool_group(self):
        """Thread pool section."""
        group = QGroupBox(f"Thread Pool (Max: {self.thread_pool.maxThreadCount()} threads)")
        layout = QHBoxLayout(group)
        
        # Left side - controls
        left_layout = QVBoxLayout()
        
        add_task_btn = QPushButton("Add Random Task")
        add_task_btn.clicked.connect(self.add_pool_task)
        left_layout.addWidget(add_task_btn)
        
        add_many_btn = QPushButton("Add 5 Tasks")
        add_many_btn.clicked.connect(lambda: [self.add_pool_task() for _ in range(5)])
        left_layout.addWidget(add_many_btn)
        
        left_layout.addStretch()
        layout.addLayout(left_layout)
        
        # Right side - task list
        self.task_list = QListWidget()
        layout.addWidget(self.task_list, stretch=1)
        
        self.task_counter = 0
        
        return group
    
    def create_log_group(self):
        """Log display section."""
        group = QGroupBox("Event Log")
        layout = QVBoxLayout(group)
        
        self.log_display = QTextEdit()
        self.log_display.setReadOnly(True)
        self.log_display.setMaximumHeight(120)
        layout.addWidget(self.log_display)
        
        return group
    
    def log(self, message):
        """Add message to log."""
        self.log_display.append(f"[{time.strftime('%H:%M:%S')}] {message}")
    
    # Download methods
    def start_download(self):
        """Start the download simulation."""
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
        """Cancel the download."""
        if self.download_worker:
            self.download_worker.cancel()
            self.log("Download cancellation requested")
    
    def on_download_started(self):
        """Handle download started."""
        self.download_start_btn.setEnabled(False)
        self.download_cancel_btn.setEnabled(True)
        self.download_progress.setValue(0)
        self.log("Download started")
    
    def on_download_progress(self, percentage, status):
        """Handle download progress."""
        self.download_progress.setValue(percentage)
        self.download_status.setText(status)
    
    def on_download_finished(self, success, message):
        """Handle download finished."""
        self.download_start_btn.setEnabled(True)
        self.download_cancel_btn.setEnabled(False)
        self.download_status.setText(message)
        self.log(f"Download {'succeeded' if success else 'failed'}: {message}")
    
    # Computation methods
    def start_computation(self):
        """Start the computation."""
        iterations = self.iterations_spin.value()
        
        self.compute_thread = QThread()
        self.compute_worker = ComputeWorker(iterations)
        self.compute_worker.moveToThread(self.compute_thread)
        
        # Connect signals
        self.compute_thread.started.connect(self.compute_worker.run)
        self.compute_worker.started.connect(self.on_compute_started)
        self.compute_worker.progress.connect(self.compute_progress.setValue)
        self.compute_worker.result.connect(self.on_compute_result)
        self.compute_worker.finished.connect(self.on_compute_finished)
        self.compute_worker.finished.connect(self.compute_thread.quit)
        self.compute_worker.finished.connect(self.compute_worker.deleteLater)
        self.compute_thread.finished.connect(self.compute_thread.deleteLater)
        
        self.compute_thread.start()
    
    def cancel_computation(self):
        """Cancel the computation."""
        if self.compute_worker:
            self.compute_worker.cancel()
            self.log("Computation cancelled")
    
    def on_compute_started(self):
        """Handle computation started."""
        self.compute_start_btn.setEnabled(False)
        self.compute_cancel_btn.setEnabled(True)
        self.compute_progress.setValue(0)
        self.compute_result.setText("Computing...")
        self.log(f"Computation started ({self.iterations_spin.value():,} iterations)")
    
    def on_compute_result(self, result):
        """Handle computation result."""
        self.compute_result.setText(f"Result: {result:,.2f}")
    
    def on_compute_finished(self):
        """Handle computation finished."""
        self.compute_start_btn.setEnabled(True)
        self.compute_cancel_btn.setEnabled(False)
        self.log("Computation finished")
    
    # Thread pool methods
    def add_pool_task(self):
        """Add a task to the thread pool."""
        self.task_counter += 1
        task_id = self.task_counter
        duration = random.uniform(1.0, 3.0)
        
        # Create list item for tracking
        item = QListWidgetItem(f"Task {task_id}: Waiting...")
        item.setData(Qt.ItemDataRole.UserRole, task_id)
        self.task_list.addItem(item)
        
        # Create and submit task
        task = TaskRunner(task_id, duration)
        task.signals.started.connect(
            lambda tid: self.update_task_item(tid, "Running... 0%")
        )
        task.signals.progress.connect(
            lambda tid, p: self.update_task_item(tid, f"Running... {p}%")
        )
        task.signals.finished.connect(
            lambda tid, result: self.finish_task_item(tid, result)
        )
        
        self.thread_pool.start(task)
        self.log(f"Task {task_id} queued (duration: {duration:.1f}s)")
    
    def update_task_item(self, task_id, text):
        """Update task list item."""
        for i in range(self.task_list.count()):
            item = self.task_list.item(i)
            if item.data(Qt.ItemDataRole.UserRole) == task_id:
                item.setText(f"Task {task_id}: {text}")
                break
    
    def finish_task_item(self, task_id, result):
        """Mark task as finished."""
        for i in range(self.task_list.count()):
            item = self.task_list.item(i)
            if item.data(Qt.ItemDataRole.UserRole) == task_id:
                item.setText(f"Task {task_id}: ✓ Complete")
                item.setBackground(Qt.GlobalColor.green)
                break
        self.log(result)
    
    def closeEvent(self, event):
        """Clean up threads on close."""
        # Wait for thread pool
        self.thread_pool.waitForDone(1000)
        
        # Stop other threads (use try/except as Qt may have already deleted objects)
        try:
            if self.download_worker:
                self.download_worker.cancel()
        except RuntimeError:
            pass
        
        try:
            if self.compute_worker:
                self.compute_worker.cancel()
        except RuntimeError:
            pass
        
        try:
            if self.download_thread and self.download_thread.isRunning():
                self.download_thread.quit()
                self.download_thread.wait(1000)
        except RuntimeError:
            pass
        
        try:
            if self.compute_thread and self.compute_thread.isRunning():
                self.compute_thread.quit()
                self.compute_thread.wait(1000)
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
