"""
PyQt6 Advanced Example 04: Networking
=====================================

This example demonstrates:
- HTTP requests with QNetworkAccessManager
- Parsing JSON responses
- Error handling

Run: python 04_networking.py
"""

import sys
import json
from PyQt6.QtWidgets import (
    QApplication, QMainWindow, QWidget, QVBoxLayout, QHBoxLayout,
    QPushButton, QLabel, QLineEdit, QTextEdit, QProgressBar,
    QGroupBox, QComboBox
)
from PyQt6.QtCore import Qt, QUrl, QObject, pyqtSignal
from PyQt6.QtNetwork import QNetworkAccessManager, QNetworkRequest, QNetworkReply


class HttpClient(QObject):
    """HTTP client wrapper."""
    
    finished = pyqtSignal(str, int)
    error = pyqtSignal(str)
    
    def __init__(self):
        super().__init__()
        self.manager = QNetworkAccessManager()
        self.current_reply = None
    
    def get(self, url, headers=None):
        request = QNetworkRequest(QUrl(url))
        request.setHeader(
            QNetworkRequest.KnownHeaders.UserAgentHeader,
            "PyQt6 Network Demo"
        )
        
        if headers:
            for key, value in headers.items():
                request.setRawHeader(key.encode(), value.encode())
        
        self.current_reply = self.manager.get(request)
        self.current_reply.finished.connect(self._on_finished)
        self.current_reply.errorOccurred.connect(self._on_error)
    
    def _on_finished(self):
        if self.current_reply:
            status_code = self.current_reply.attribute(
                QNetworkRequest.Attribute.HttpStatusCodeAttribute
            )
            data = self.current_reply.readAll().data().decode()
            self.finished.emit(data, status_code or 0)
            self.current_reply.deleteLater()
            self.current_reply = None
    
    def _on_error(self, error):
        if self.current_reply:
            self.error.emit(self.current_reply.errorString())


class NetworkingDemo(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("PyQt6 Networking Demo")
        self.setMinimumSize(700, 500)
        
        self.http_client = HttpClient()
        self.http_client.finished.connect(self.on_finished)
        self.http_client.error.connect(self.on_error)
        
        central = QWidget()
        self.setCentralWidget(central)
        layout = QVBoxLayout(central)
        
        # Request group
        request_group = QGroupBox("API Request")
        request_layout = QVBoxLayout(request_group)
        
        url_layout = QHBoxLayout()
        url_layout.addWidget(QLabel("URL:"))
        self.url_input = QLineEdit()
        self.url_input.setText("https://api.github.com/users/octocat")
        url_layout.addWidget(self.url_input)
        request_layout.addLayout(url_layout)
        
        btn_layout = QHBoxLayout()
        self.send_btn = QPushButton("Send Request")
        self.send_btn.clicked.connect(self.send_request)
        btn_layout.addWidget(self.send_btn)
        
        self.progress = QProgressBar()
        self.progress.setRange(0, 0)
        self.progress.hide()
        btn_layout.addWidget(self.progress)
        
        self.status_label = QLabel("")
        btn_layout.addWidget(self.status_label)
        btn_layout.addStretch()
        request_layout.addLayout(btn_layout)
        
        layout.addWidget(request_group)
        
        # Response group
        response_group = QGroupBox("Response")
        response_layout = QVBoxLayout(response_group)
        
        self.response_text = QTextEdit()
        self.response_text.setReadOnly(True)
        response_layout.addWidget(self.response_text)
        
        layout.addWidget(response_group)
    
    def send_request(self):
        url = self.url_input.text().strip()
        if not url:
            self.status_label.setText("Enter a URL")
            return
        
        self.response_text.clear()
        self.progress.show()
        self.send_btn.setEnabled(False)
        self.status_label.setText("Sending...")
        
        self.http_client.get(url)
    
    def on_finished(self, data, status_code):
        self.progress.hide()
        self.send_btn.setEnabled(True)
        self.status_label.setText(f"Status: {status_code}")
        
        try:
            parsed = json.loads(data)
            formatted = json.dumps(parsed, indent=2)
            self.response_text.setPlainText(formatted)
        except:
            self.response_text.setPlainText(data)
    
    def on_error(self, error_string):
        self.progress.hide()
        self.send_btn.setEnabled(True)
        self.status_label.setText("Error!")
        self.response_text.setPlainText(f"Error: {error_string}")


def main():
    app = QApplication(sys.argv)
    window = NetworkingDemo()
    window.show()
    sys.exit(app.exec())


if __name__ == "__main__":
    main()
