"""
PySide6 Intermediate Example 05: Menus, Toolbars, and Status Bars
================================================================

This example demonstrates:
- Creating menu bars with menus and actions
- Keyboard shortcuts
- Checkable menu items
- Context menus
- Toolbars with actions and widgets
- Status bar with permanent widgets

Run: python 05_menus_toolbars.py
"""

import sys
from PySide6.QtWidgets import (
    QApplication, QMainWindow, QWidget, QVBoxLayout, QHBoxLayout,
    QTextEdit, QLabel, QToolBar, QStatusBar, QMenu, QMessageBox,
    QFileDialog, QFontDialog, QColorDialog, QLineEdit, QComboBox
)
from PySide6.QtCore import Qt, QSize
from PySide6.QtGui import QAction, QActionGroup, QKeySequence, QFont, QColor


class TextEditor(QMainWindow):
    """Simple text editor demonstrating menus and toolbars."""
    
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Text Editor - Menus & Toolbars Demo")
        self.setMinimumSize(800, 600)
        
        # Current file path
        self.current_file = None
        self.is_modified = False
        
        # Create central widget
        self.text_edit = QTextEdit()
        self.text_edit.setFont(QFont("Consolas", 12))
        self.text_edit.textChanged.connect(self.on_text_changed)
        self.setCentralWidget(self.text_edit)
        
        # Create UI components
        self.create_actions()
        self.create_menus()
        self.create_toolbars()
        self.create_status_bar()
        self.create_context_menu()
        
        self.update_title()
    
    def create_actions(self):
        """Create all actions."""
        # File actions
        self.new_action = QAction("&New", self)
        self.new_action.setShortcut(QKeySequence.StandardKey.New)
        self.new_action.setStatusTip("Create a new file")
        self.new_action.triggered.connect(self.new_file)
        
        self.open_action = QAction("&Open...", self)
        self.open_action.setShortcut(QKeySequence.StandardKey.Open)
        self.open_action.setStatusTip("Open an existing file")
        self.open_action.triggered.connect(self.open_file)
        
        self.save_action = QAction("&Save", self)
        self.save_action.setShortcut(QKeySequence.StandardKey.Save)
        self.save_action.setStatusTip("Save the current file")
        self.save_action.triggered.connect(self.save_file)
        
        self.save_as_action = QAction("Save &As...", self)
        self.save_as_action.setShortcut(QKeySequence.StandardKey.SaveAs)
        self.save_as_action.setStatusTip("Save to a new file")
        self.save_as_action.triggered.connect(self.save_file_as)
        
        self.exit_action = QAction("E&xit", self)
        self.exit_action.setShortcut(QKeySequence.StandardKey.Quit)
        self.exit_action.setStatusTip("Exit the application")
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
        
        self.select_all_action = QAction("Select &All", self)
        self.select_all_action.setShortcut(QKeySequence.StandardKey.SelectAll)
        self.select_all_action.triggered.connect(self.text_edit.selectAll)
        
        # Format actions
        self.font_action = QAction("&Font...", self)
        self.font_action.setStatusTip("Change font")
        self.font_action.triggered.connect(self.choose_font)
        
        self.color_action = QAction("Text &Color...", self)
        self.color_action.setStatusTip("Change text color")
        self.color_action.triggered.connect(self.choose_color)
        
        self.bold_action = QAction("&Bold", self)
        self.bold_action.setShortcut("Ctrl+B")
        self.bold_action.setCheckable(True)
        self.bold_action.triggered.connect(self.toggle_bold)
        
        self.italic_action = QAction("&Italic", self)
        self.italic_action.setShortcut("Ctrl+I")
        self.italic_action.setCheckable(True)
        self.italic_action.triggered.connect(self.toggle_italic)
        
        self.underline_action = QAction("&Underline", self)
        self.underline_action.setShortcut("Ctrl+U")
        self.underline_action.setCheckable(True)
        self.underline_action.triggered.connect(self.toggle_underline)
        
        # View actions (checkable)
        self.toolbar_action = QAction("&Toolbar", self)
        self.toolbar_action.setCheckable(True)
        self.toolbar_action.setChecked(True)
        self.toolbar_action.triggered.connect(self.toggle_toolbar)
        
        self.statusbar_action = QAction("&Status Bar", self)
        self.statusbar_action.setCheckable(True)
        self.statusbar_action.setChecked(True)
        self.statusbar_action.triggered.connect(self.toggle_statusbar)
        
        self.wordwrap_action = QAction("&Word Wrap", self)
        self.wordwrap_action.setCheckable(True)
        self.wordwrap_action.setChecked(True)
        self.wordwrap_action.triggered.connect(self.toggle_wordwrap)
        
        # View size actions (exclusive group)
        self.zoom_group = QActionGroup(self)
        
        self.zoom_100_action = QAction("100%", self)
        self.zoom_100_action.setCheckable(True)
        self.zoom_100_action.setChecked(True)
        self.zoom_group.addAction(self.zoom_100_action)
        
        self.zoom_125_action = QAction("125%", self)
        self.zoom_125_action.setCheckable(True)
        self.zoom_group.addAction(self.zoom_125_action)
        
        self.zoom_150_action = QAction("150%", self)
        self.zoom_150_action.setCheckable(True)
        self.zoom_group.addAction(self.zoom_150_action)
        
        self.zoom_group.triggered.connect(self.change_zoom)
        
        # Help actions
        self.about_action = QAction("&About", self)
        self.about_action.setStatusTip("About this application")
        self.about_action.triggered.connect(self.show_about)
    
    def create_menus(self):
        """Create menu bar and menus."""
        menubar = self.menuBar()
        
        # File menu
        file_menu = menubar.addMenu("&File")
        file_menu.addAction(self.new_action)
        file_menu.addAction(self.open_action)
        file_menu.addAction(self.save_action)
        file_menu.addAction(self.save_as_action)
        file_menu.addSeparator()
        
        # Recent files submenu
        recent_menu = file_menu.addMenu("Recent Files")
        for i in range(1, 6):
            action = QAction(f"file{i}.txt", self)
            action.setEnabled(False)
            recent_menu.addAction(action)
        
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
        edit_menu.addSeparator()
        edit_menu.addAction(self.select_all_action)
        
        # Format menu
        format_menu = menubar.addMenu("F&ormat")
        format_menu.addAction(self.font_action)
        format_menu.addAction(self.color_action)
        format_menu.addSeparator()
        format_menu.addAction(self.bold_action)
        format_menu.addAction(self.italic_action)
        format_menu.addAction(self.underline_action)
        
        # View menu
        view_menu = menubar.addMenu("&View")
        view_menu.addAction(self.toolbar_action)
        view_menu.addAction(self.statusbar_action)
        view_menu.addAction(self.wordwrap_action)
        view_menu.addSeparator()
        
        # Zoom submenu
        zoom_menu = view_menu.addMenu("&Zoom")
        zoom_menu.addAction(self.zoom_100_action)
        zoom_menu.addAction(self.zoom_125_action)
        zoom_menu.addAction(self.zoom_150_action)
        
        # Help menu
        help_menu = menubar.addMenu("&Help")
        help_menu.addAction(self.about_action)
    
    def create_toolbars(self):
        """Create toolbars."""
        # Main toolbar
        self.main_toolbar = QToolBar("Main")
        self.main_toolbar.setIconSize(QSize(16, 16))
        self.main_toolbar.setMovable(True)
        self.addToolBar(Qt.ToolBarArea.TopToolBarArea, self.main_toolbar)
        
        self.main_toolbar.addAction(self.new_action)
        self.main_toolbar.addAction(self.open_action)
        self.main_toolbar.addAction(self.save_action)
        self.main_toolbar.addSeparator()
        self.main_toolbar.addAction(self.cut_action)
        self.main_toolbar.addAction(self.copy_action)
        self.main_toolbar.addAction(self.paste_action)
        self.main_toolbar.addSeparator()
        self.main_toolbar.addAction(self.undo_action)
        self.main_toolbar.addAction(self.redo_action)
        
        # Format toolbar
        self.format_toolbar = QToolBar("Format")
        self.format_toolbar.setMovable(True)
        self.addToolBar(Qt.ToolBarArea.TopToolBarArea, self.format_toolbar)
        
        self.format_toolbar.addAction(self.bold_action)
        self.format_toolbar.addAction(self.italic_action)
        self.format_toolbar.addAction(self.underline_action)
        self.format_toolbar.addSeparator()
        
        # Font size combo
        self.font_size_combo = QComboBox()
        self.font_size_combo.addItems(["8", "10", "12", "14", "16", "18", "20", "24", "28", "32"])
        self.font_size_combo.setCurrentText("12")
        self.font_size_combo.currentTextChanged.connect(self.change_font_size)
        self.format_toolbar.addWidget(QLabel(" Size: "))
        self.format_toolbar.addWidget(self.font_size_combo)
        
        # Search toolbar
        self.search_toolbar = QToolBar("Search")
        self.search_toolbar.setMovable(True)
        self.addToolBar(Qt.ToolBarArea.TopToolBarArea, self.search_toolbar)
        
        self.search_input = QLineEdit()
        self.search_input.setPlaceholderText("Search...")
        self.search_input.setMaximumWidth(200)
        self.search_input.returnPressed.connect(self.search_text)
        self.search_toolbar.addWidget(self.search_input)
        
        search_action = QAction("Find", self)
        search_action.triggered.connect(self.search_text)
        self.search_toolbar.addAction(search_action)
    
    def create_status_bar(self):
        """Create status bar with permanent widgets."""
        self.status_bar = QStatusBar()
        self.setStatusBar(self.status_bar)
        
        # Cursor position
        self.cursor_label = QLabel("Line: 1, Col: 1")
        self.status_bar.addPermanentWidget(self.cursor_label)
        
        # Word count
        self.word_count_label = QLabel("Words: 0")
        self.status_bar.addPermanentWidget(self.word_count_label)
        
        # Encoding
        self.encoding_label = QLabel("UTF-8")
        self.status_bar.addPermanentWidget(self.encoding_label)
        
        # Connect cursor position update
        self.text_edit.cursorPositionChanged.connect(self.update_cursor_position)
        
        # Initial message
        self.status_bar.showMessage("Ready", 3000)
    
    def create_context_menu(self):
        """Set up context menu for text editor."""
        self.text_edit.setContextMenuPolicy(Qt.ContextMenuPolicy.CustomContextMenu)
        self.text_edit.customContextMenuRequested.connect(self.show_context_menu)
    
    def show_context_menu(self, position):
        """Show context menu at position."""
        menu = QMenu(self)
        
        menu.addAction(self.undo_action)
        menu.addAction(self.redo_action)
        menu.addSeparator()
        menu.addAction(self.cut_action)
        menu.addAction(self.copy_action)
        menu.addAction(self.paste_action)
        menu.addSeparator()
        menu.addAction(self.select_all_action)
        
        menu.exec(self.text_edit.mapToGlobal(position))
    
    # File operations
    def new_file(self):
        """Create a new file."""
        if self.maybe_save():
            self.text_edit.clear()
            self.current_file = None
            self.is_modified = False
            self.update_title()
            self.status_bar.showMessage("New file created", 3000)
    
    def open_file(self):
        """Open a file."""
        if self.maybe_save():
            path, _ = QFileDialog.getOpenFileName(
                self, "Open File", "",
                "Text Files (*.txt);;All Files (*)"
            )
            if path:
                try:
                    with open(path, 'r', encoding='utf-8') as f:
                        self.text_edit.setPlainText(f.read())
                    self.current_file = path
                    self.is_modified = False
                    self.update_title()
                    self.status_bar.showMessage(f"Opened: {path}", 3000)
                except Exception as e:
                    QMessageBox.critical(self, "Error", f"Could not open file:\n{e}")
    
    def save_file(self):
        """Save the current file."""
        if self.current_file:
            return self.save_to_file(self.current_file)
        return self.save_file_as()
    
    def save_file_as(self):
        """Save to a new file."""
        path, _ = QFileDialog.getSaveFileName(
            self, "Save File", "",
            "Text Files (*.txt);;All Files (*)"
        )
        if path:
            return self.save_to_file(path)
        return False
    
    def save_to_file(self, path):
        """Save content to file."""
        try:
            with open(path, 'w', encoding='utf-8') as f:
                f.write(self.text_edit.toPlainText())
            self.current_file = path
            self.is_modified = False
            self.update_title()
            self.status_bar.showMessage(f"Saved: {path}", 3000)
            return True
        except Exception as e:
            QMessageBox.critical(self, "Error", f"Could not save file:\n{e}")
            return False
    
    def maybe_save(self):
        """Ask to save if modified."""
        if not self.is_modified:
            return True
        
        result = QMessageBox.warning(
            self, "Unsaved Changes",
            "The document has been modified.\nDo you want to save your changes?",
            QMessageBox.StandardButton.Save |
            QMessageBox.StandardButton.Discard |
            QMessageBox.StandardButton.Cancel
        )
        
        if result == QMessageBox.StandardButton.Save:
            return self.save_file()
        elif result == QMessageBox.StandardButton.Cancel:
            return False
        return True
    
    # Format operations
    def choose_font(self):
        """Open font dialog."""
        font, ok = QFontDialog.getFont(self.text_edit.font(), self)
        if ok:
            self.text_edit.setFont(font)
    
    def choose_color(self):
        """Open color dialog."""
        color = QColorDialog.getColor(self.text_edit.textColor(), self)
        if color.isValid():
            self.text_edit.setTextColor(color)
    
    def toggle_bold(self, checked):
        """Toggle bold text."""
        font = self.text_edit.font()
        font.setBold(checked)
        self.text_edit.setFont(font)
    
    def toggle_italic(self, checked):
        """Toggle italic text."""
        font = self.text_edit.font()
        font.setItalic(checked)
        self.text_edit.setFont(font)
    
    def toggle_underline(self, checked):
        """Toggle underline text."""
        font = self.text_edit.font()
        font.setUnderline(checked)
        self.text_edit.setFont(font)
    
    def change_font_size(self, size_str):
        """Change font size."""
        font = self.text_edit.font()
        font.setPointSize(int(size_str))
        self.text_edit.setFont(font)
    
    # View operations
    def toggle_toolbar(self, visible):
        """Toggle main toolbar visibility."""
        self.main_toolbar.setVisible(visible)
        self.format_toolbar.setVisible(visible)
        self.search_toolbar.setVisible(visible)
    
    def toggle_statusbar(self, visible):
        """Toggle status bar visibility."""
        self.status_bar.setVisible(visible)
    
    def toggle_wordwrap(self, checked):
        """Toggle word wrap."""
        if checked:
            self.text_edit.setLineWrapMode(QTextEdit.LineWrapMode.WidgetWidth)
        else:
            self.text_edit.setLineWrapMode(QTextEdit.LineWrapMode.NoWrap)
    
    def change_zoom(self, action):
        """Change zoom level."""
        zoom_text = action.text().replace("%", "")
        zoom = int(zoom_text) / 100.0
        
        font = self.text_edit.font()
        base_size = 12
        font.setPointSize(int(base_size * zoom))
        self.text_edit.setFont(font)
    
    # Search
    def search_text(self):
        """Search for text."""
        search_term = self.search_input.text()
        if search_term:
            if self.text_edit.find(search_term):
                self.status_bar.showMessage(f"Found: '{search_term}'", 3000)
            else:
                # Wrap around
                cursor = self.text_edit.textCursor()
                cursor.movePosition(cursor.MoveOperation.Start)
                self.text_edit.setTextCursor(cursor)
                
                if self.text_edit.find(search_term):
                    self.status_bar.showMessage(f"Found: '{search_term}' (wrapped)", 3000)
                else:
                    self.status_bar.showMessage(f"Not found: '{search_term}'", 3000)
    
    # Help
    def show_about(self):
        """Show about dialog."""
        QMessageBox.about(
            self, "About Text Editor",
            "<h2>Text Editor Demo</h2>"
            "<p>Version 1.0</p>"
            "<p>A demonstration of menus, toolbars, and status bars in PySide6.</p>"
            "<p>This example shows how to create:</p>"
            "<ul>"
            "<li>Menu bar with nested menus</li>"
            "<li>Keyboard shortcuts</li>"
            "<li>Checkable and exclusive actions</li>"
            "<li>Context menus</li>"
            "<li>Multiple toolbars</li>"
            "<li>Status bar with widgets</li>"
            "</ul>"
        )
    
    # Event handlers
    def on_text_changed(self):
        """Handle text changes."""
        self.is_modified = True
        self.update_title()
        self.update_word_count()
    
    def update_title(self):
        """Update window title."""
        file_name = self.current_file or "Untitled"
        modified = "*" if self.is_modified else ""
        self.setWindowTitle(f"{file_name}{modified} - Text Editor")
    
    def update_cursor_position(self):
        """Update cursor position in status bar."""
        cursor = self.text_edit.textCursor()
        line = cursor.blockNumber() + 1
        col = cursor.columnNumber() + 1
        self.cursor_label.setText(f"Line: {line}, Col: {col}")
    
    def update_word_count(self):
        """Update word count in status bar."""
        text = self.text_edit.toPlainText()
        words = len(text.split()) if text.strip() else 0
        self.word_count_label.setText(f"Words: {words}")
    
    def closeEvent(self, event):
        """Handle window close."""
        if self.maybe_save():
            event.accept()
        else:
            event.ignore()


def main():
    app = QApplication(sys.argv)
    window = TextEditor()
    window.show()
    sys.exit(app.exec())


if __name__ == "__main__":
    main()
