"""
PySide6 Advanced Example 05: Networking
=======================================

This example demonstrates:
- HTTP requests with QNetworkAccessManager
- Downloading files with progress
- Parsing JSON responses
- RESTful API client
- Error handling

Run: python 05_networking.py
"""

import sys
import json
from PySide6.QtWidgets import (
    QApplication, QMainWindow, QWidget, QVBoxLayout, QHBoxLayout,
    QPushButton, QLabel, QLineEdit, QTextEdit, QProgressBar,
    QGroupBox, QListWidget, QListWidgetItem, QTabWidget,
    QComboBox, QMessageBox, QFileDialog, QTableWidget, QTableWidgetItem
)
from PySide6.QtCore import Qt, QUrl, QObject, Signal, Slot
from PySide6.QtNetwork import (
    QNetworkAccessManager, QNetworkRequest, QNetworkReply
)


class HttpClient(QObject):
    """HTTP client wrapper for network requests."""
    
    finished = Signal(str, int)  # response data, status code
    error = Signal(str)
    progress = Signal(int, int)  # received, total
    
    def __init__(self):
        super().__init__()
        self.manager = QNetworkAccessManager()
        self.current_reply = None
    
    def get(self, url, headers=None):
        """Send GET request."""
        request = QNetworkRequest(QUrl(url))
        request.setHeader(
            QNetworkRequest.KnownHeaders.UserAgentHeader,
            "PySide6 Network Demo"
        )
        
        if headers:
            for key, value in headers.items():
                request.setRawHeader(key.encode(), value.encode())
        
        self.current_reply = self.manager.get(request)
        self._connect_reply_signals()
    
    def post(self, url, data, content_type="application/json"):
        """Send POST request."""
        request = QNetworkRequest(QUrl(url))
        request.setHeader(
            QNetworkRequest.KnownHeaders.ContentTypeHeader,
            content_type
        )
        
        if isinstance(data, dict):
            data = json.dumps(data).encode()
        elif isinstance(data, str):
            data = data.encode()
        
        self.current_reply = self.manager.post(request, data)
        self._connect_reply_signals()
    
    def _connect_reply_signals(self):
        """Connect signals for the current reply."""
        self.current_reply.finished.connect(self._on_finished)
        self.current_reply.downloadProgress.connect(self._on_progress)
        self.current_reply.errorOccurred.connect(self._on_error)
    
    def _on_finished(self):
        """Handle request completion."""
        if self.current_reply:
            status_code = self.current_reply.attribute(
                QNetworkRequest.Attribute.HttpStatusCodeAttribute
            )
            data = self.current_reply.readAll().data().decode()
            self.finished.emit(data, status_code or 0)
            self.current_reply.deleteLater()
            self.current_reply = None
    
    def _on_progress(self, received, total):
        """Handle download progress."""
        self.progress.emit(received, total)
    
    def _on_error(self, error):
        """Handle network errors."""
        if self.current_reply:
            self.error.emit(self.current_reply.errorString())
    
    def abort(self):
        """Abort current request."""
        if self.current_reply:
            self.current_reply.abort()


class NetworkingDemo(QMainWindow):
    """Main window for networking demo."""
    
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Networking Demo")
        self.setMinimumSize(900, 700)
        
        self.http_client = HttpClient()
        self.http_client.finished.connect(self.on_request_finished)
        self.http_client.error.connect(self.on_request_error)
        self.http_client.progress.connect(self.on_progress)
        
        central = QWidget()
        self.setCentralWidget(central)
        layout = QVBoxLayout(central)
        
        tabs = QTabWidget()
        tabs.addTab(self.create_api_tab(), "REST API")
        tabs.addTab(self.create_json_tab(), "JSON Placeholder")
        tabs.addTab(self.create_custom_tab(), "Custom Request")
        
        layout.addWidget(tabs)
    
    def create_api_tab(self):
        """Create REST API demonstration tab."""
        widget = QWidget()
        layout = QVBoxLayout(widget)
        
        # Explanation
        info = QLabel(
            "This tab demonstrates calling a public REST API.\n"
            "We'll use httpbin.org which echoes back request information."
        )
        info.setWordWrap(True)
        layout.addWidget(info)
        
        # Request section
        request_group = QGroupBox("API Request")
        request_layout = QVBoxLayout(request_group)
        
        # Method and URL
        row1 = QHBoxLayout()
        row1.addWidget(QLabel("Method:"))
        self.method_combo = QComboBox()
        self.method_combo.addItems(["GET", "POST"])
        row1.addWidget(self.method_combo)
        
        row1.addWidget(QLabel("Endpoint:"))
        self.endpoint_combo = QComboBox()
        self.endpoint_combo.addItems([
            "/get",
            "/post",
            "/ip",
            "/user-agent",
            "/headers",
            "/uuid",
            "/delay/2",
        ])
        row1.addWidget(self.endpoint_combo)
        request_layout.addLayout(row1)
        
        # Send button
        row2 = QHBoxLayout()
        self.send_btn = QPushButton("Send Request")
        self.send_btn.clicked.connect(self.send_api_request)
        row2.addWidget(self.send_btn)
        
        self.api_progress = QProgressBar()
        self.api_progress.setRange(0, 0)  # Indeterminate
        self.api_progress.hide()
        row2.addWidget(self.api_progress)
        
        self.api_status = QLabel("")
        row2.addWidget(self.api_status)
        row2.addStretch()
        request_layout.addLayout(row2)
        
        layout.addWidget(request_group)
        
        # Response section
        response_group = QGroupBox("Response")
        response_layout = QVBoxLayout(response_group)
        
        self.api_response = QTextEdit()
        self.api_response.setReadOnly(True)
        self.api_response.setPlaceholderText("Response will appear here...")
        response_layout.addWidget(self.api_response)
        
        layout.addWidget(response_group)
        
        return widget
    
    def create_json_tab(self):
        """Create JSON Placeholder API tab."""
        widget = QWidget()
        layout = QVBoxLayout(widget)
        
        info = QLabel(
            "Fetch data from JSONPlaceholder, a free fake API for testing.\n"
            "Click buttons to fetch different types of data."
        )
        info.setWordWrap(True)
        layout.addWidget(info)
        
        # Buttons
        btn_layout = QHBoxLayout()
        
        users_btn = QPushButton("Fetch Users")
        users_btn.clicked.connect(lambda: self.fetch_json("users"))
        btn_layout.addWidget(users_btn)
        
        posts_btn = QPushButton("Fetch Posts")
        posts_btn.clicked.connect(lambda: self.fetch_json("posts"))
        btn_layout.addWidget(posts_btn)
        
        todos_btn = QPushButton("Fetch Todos")
        todos_btn.clicked.connect(lambda: self.fetch_json("todos"))
        btn_layout.addWidget(todos_btn)
        
        btn_layout.addStretch()
        layout.addLayout(btn_layout)
        
        # Progress
        self.json_progress = QProgressBar()
        self.json_progress.setRange(0, 0)
        self.json_progress.hide()
        layout.addWidget(self.json_progress)
        
        # Results table
        self.json_table = QTableWidget()
        self.json_table.setAlternatingRowColors(True)
        layout.addWidget(self.json_table)
        
        return widget
    
    def create_custom_tab(self):
        """Create custom request tab."""
        widget = QWidget()
        layout = QVBoxLayout(widget)
        
        # URL input
        url_layout = QHBoxLayout()
        url_layout.addWidget(QLabel("URL:"))
        self.custom_url = QLineEdit()
        self.custom_url.setText("https://api.github.com/users/octocat")
        self.custom_url.setPlaceholderText("Enter URL...")
        url_layout.addWidget(self.custom_url)
        layout.addLayout(url_layout)
        
        # Headers
        headers_layout = QHBoxLayout()
        headers_layout.addWidget(QLabel("Accept:"))
        self.accept_combo = QComboBox()
        self.accept_combo.addItems([
            "application/json",
            "text/html",
            "text/plain",
            "*/*"
        ])
        headers_layout.addWidget(self.accept_combo)
        headers_layout.addStretch()
        layout.addLayout(headers_layout)
        
        # Send button
        btn_layout = QHBoxLayout()
        
        send_btn = QPushButton("Send Request")
        send_btn.clicked.connect(self.send_custom_request)
        btn_layout.addWidget(send_btn)
        
        self.custom_progress = QProgressBar()
        self.custom_progress.setRange(0, 100)
        self.custom_progress.hide()
        btn_layout.addWidget(self.custom_progress)
        
        self.custom_status = QLabel("")
        btn_layout.addWidget(self.custom_status)
        btn_layout.addStretch()
        layout.addLayout(btn_layout)
        
        # Response
        self.custom_response = QTextEdit()
        self.custom_response.setReadOnly(True)
        layout.addWidget(self.custom_response)
        
        return widget
    
    # Request handlers
    def send_api_request(self):
        """Send API request to httpbin."""
        method = self.method_combo.currentText()
        endpoint = self.endpoint_combo.currentText()
        url = f"https://httpbin.org{endpoint}"
        
        self.api_response.clear()
        self.api_progress.show()
        self.api_status.setText("Sending request...")
        self.send_btn.setEnabled(False)
        self._current_tab = "api"
        
        if method == "GET":
            self.http_client.get(url)
        else:
            self.http_client.post(url, {"demo": "PySide6 Network Demo"})
    
    def fetch_json(self, resource):
        """Fetch data from JSONPlaceholder."""
        url = f"https://jsonplaceholder.typicode.com/{resource}"
        
        self.json_progress.show()
        self.json_table.clear()
        self._current_tab = "json"
        self._json_resource = resource
        
        self.http_client.get(url)
    
    def send_custom_request(self):
        """Send custom request."""
        url = self.custom_url.text().strip()
        if not url:
            QMessageBox.warning(self, "Error", "Please enter a URL")
            return
        
        headers = {"Accept": self.accept_combo.currentText()}
        
        self.custom_response.clear()
        self.custom_progress.show()
        self.custom_progress.setRange(0, 0)
        self.custom_status.setText("Sending request...")
        self._current_tab = "custom"
        
        self.http_client.get(url, headers)
    
    # Response handlers
    def on_request_finished(self, data, status_code):
        """Handle completed request."""
        tab = getattr(self, '_current_tab', 'api')
        
        if tab == "api":
            self.api_progress.hide()
            self.send_btn.setEnabled(True)
            self.api_status.setText(f"Status: {status_code}")
            
            # Pretty print JSON
            try:
                parsed = json.loads(data)
                formatted = json.dumps(parsed, indent=2)
                self.api_response.setPlainText(formatted)
            except:
                self.api_response.setPlainText(data)
        
        elif tab == "json":
            self.json_progress.hide()
            self.display_json_data(data)
        
        elif tab == "custom":
            self.custom_progress.hide()
            self.custom_progress.setRange(0, 100)
            self.custom_status.setText(f"Status: {status_code}")
            
            # Try to format as JSON
            try:
                parsed = json.loads(data)
                formatted = json.dumps(parsed, indent=2)
                self.custom_response.setPlainText(formatted)
            except:
                self.custom_response.setPlainText(data)
    
    def on_request_error(self, error_string):
        """Handle request error."""
        tab = getattr(self, '_current_tab', 'api')
        
        if tab == "api":
            self.api_progress.hide()
            self.send_btn.setEnabled(True)
            self.api_status.setText("Error!")
            self.api_response.setPlainText(f"Error: {error_string}")
        
        elif tab == "json":
            self.json_progress.hide()
            QMessageBox.critical(self, "Error", f"Request failed: {error_string}")
        
        elif tab == "custom":
            self.custom_progress.hide()
            self.custom_status.setText("Error!")
            self.custom_response.setPlainText(f"Error: {error_string}")
    
    def on_progress(self, received, total):
        """Handle download progress."""
        tab = getattr(self, '_current_tab', 'api')
        
        if tab == "custom" and total > 0:
            self.custom_progress.setRange(0, total)
            self.custom_progress.setValue(received)
    
    def display_json_data(self, data):
        """Display JSON data in table."""
        try:
            items = json.loads(data)
            
            if not items:
                return
            
            # Limit to first 20 items
            items = items[:20]
            
            # Get column headers from first item
            headers = list(items[0].keys())[:6]  # Limit columns
            
            self.json_table.setRowCount(len(items))
            self.json_table.setColumnCount(len(headers))
            self.json_table.setHorizontalHeaderLabels(headers)
            
            for row, item in enumerate(items):
                for col, key in enumerate(headers):
                    value = item.get(key, "")
                    if isinstance(value, dict):
                        value = json.dumps(value)
                    self.json_table.setItem(
                        row, col, 
                        QTableWidgetItem(str(value)[:50])  # Truncate long values
                    )
            
            self.json_table.resizeColumnsToContents()
            
        except Exception as e:
            QMessageBox.critical(self, "Error", f"Failed to parse JSON: {e}")


def main():
    app = QApplication(sys.argv)
    window = NetworkingDemo()
    window.show()
    sys.exit(app.exec())


if __name__ == "__main__":
    main()
