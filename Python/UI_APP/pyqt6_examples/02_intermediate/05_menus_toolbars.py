"""
PyQt6 Intermediate Example 05: Menus, Toolbars, and Status Bars
===============================================================

This example demonstrates:
- Creating menu bars with menus and actions
- Keyboard shortcuts
- Toolbars with actions
- Status bar

Run: python 05_menus_toolbars.py
"""

import sys
from PyQt6.QtWidgets import (
    QApplication, QMainWindow, QTextEdit, QToolBar, QStatusBar, QLabel
)
from PyQt6.QtCore import Qt, QSize
from PyQt6.QtGui import QAction, QKeySequence


class TextEditor(QMainWindow):
    """Simple text editor demonstrating menus and toolbars."""
    
    def __init__(self):
        super().__init__()
        self.setWindowTitle("PyQt6 Text Editor Demo")
        self.setMinimumSize(700, 500)
        
        self.text_edit = QTextEdit()
        self.setCentralWidget(self.text_edit)
        
        self.create_actions()
        self.create_menus()
        self.create_toolbars()
        self.create_status_bar()
        
        self.text_edit.cursorPositionChanged.connect(self.update_cursor_position)
    
    def create_actions(self):
        # File actions
        self.new_action = QAction("&New", self)
        self.new_action.setShortcut(QKeySequence.StandardKey.New)
        self.new_action.triggered.connect(self.text_edit.clear)
        
        self.exit_action = QAction("E&xit", self)
        self.exit_action.setShortcut(QKeySequence.StandardKey.Quit)
        self.exit_action.triggered.connect(self.close)
        
        # Edit actions
        self.undo_action = QAction("&Undo", self)
        self.undo_action.setShortcut(QKeySequence.StandardKey.Undo)
        self.undo_action.triggered.connect(self.text_edit.undo)
        
        self.redo_action = QAction("&Redo", self)
        self.redo_action.setShortcut(QKeySequence.StandardKey.Redo)
        self.redo_action.triggered.connect(self.text_edit.redo)
        
        self.cut_action = QAction("Cu&t", self)
        self.cut_action.setShortcut(QKeySequence.StandardKey.Cut)
        self.cut_action.triggered.connect(self.text_edit.cut)
        
        self.copy_action = QAction("&Copy", self)
        self.copy_action.setShortcut(QKeySequence.StandardKey.Copy)
        self.copy_action.triggered.connect(self.text_edit.copy)
        
        self.paste_action = QAction("&Paste", self)
        self.paste_action.setShortcut(QKeySequence.StandardKey.Paste)
        self.paste_action.triggered.connect(self.text_edit.paste)
        
        # View actions
        self.wordwrap_action = QAction("&Word Wrap", self)
        self.wordwrap_action.setCheckable(True)
        self.wordwrap_action.setChecked(True)
        self.wordwrap_action.triggered.connect(self.toggle_wordwrap)
    
    def create_menus(self):
        menubar = self.menuBar()
        
        # File menu
        file_menu = menubar.addMenu("&File")
        file_menu.addAction(self.new_action)
        file_menu.addSeparator()
        file_menu.addAction(self.exit_action)
        
        # Edit menu
        edit_menu = menubar.addMenu("&Edit")
        edit_menu.addAction(self.undo_action)
        edit_menu.addAction(self.redo_action)
        edit_menu.addSeparator()
        edit_menu.addAction(self.cut_action)
        edit_menu.addAction(self.copy_action)
        edit_menu.addAction(self.paste_action)
        
        # View menu
        view_menu = menubar.addMenu("&View")
        view_menu.addAction(self.wordwrap_action)
    
    def create_toolbars(self):
        toolbar = QToolBar("Main")
        toolbar.setIconSize(QSize(16, 16))
        self.addToolBar(Qt.ToolBarArea.TopToolBarArea, toolbar)
        
        toolbar.addAction(self.new_action)
        toolbar.addSeparator()
        toolbar.addAction(self.cut_action)
        toolbar.addAction(self.copy_action)
        toolbar.addAction(self.paste_action)
        toolbar.addSeparator()
        toolbar.addAction(self.undo_action)
        toolbar.addAction(self.redo_action)
    
    def create_status_bar(self):
        status = QStatusBar()
        self.setStatusBar(status)
        
        self.cursor_label = QLabel("Line: 1, Col: 1")
        status.addPermanentWidget(self.cursor_label)
        
        status.showMessage("Ready", 3000)
    
    def toggle_wordwrap(self, checked):
        if checked:
            self.text_edit.setLineWrapMode(QTextEdit.LineWrapMode.WidgetWidth)
        else:
            self.text_edit.setLineWrapMode(QTextEdit.LineWrapMode.NoWrap)
    
    def update_cursor_position(self):
        cursor = self.text_edit.textCursor()
        line = cursor.blockNumber() + 1
        col = cursor.columnNumber() + 1
        self.cursor_label.setText(f"Line: {line}, Col: {col}")


def main():
    app = QApplication(sys.argv)
    window = TextEditor()
    window.show()
    sys.exit(app.exec())


if __name__ == "__main__":
    main()
