"""
PySide6 Advanced Example 06: Audio/Video Media Player
======================================================

This example demonstrates:
- QMediaPlayer for audio and video playback
- QVideoWidget for video display
- Play, pause, stop controls
- Seek slider and volume control
- Repeat/loop functionality
- Opening files with QFileDialog

Requirements:
    pip install PySide6

Run: python 06_media_player.py
"""

import sys
from pathlib import Path
from PySide6.QtWidgets import (
    QApplication, QMainWindow, QWidget, QVBoxLayout, QHBoxLayout,
    QPushButton, QSlider, QLabel, QFileDialog, QStyle, QSizePolicy,
    QGroupBox, QCheckBox, QComboBox, QStatusBar
)
from PySide6.QtCore import Qt, QUrl, Slot, QTime
from PySide6.QtGui import QIcon, QAction, QKeySequence
from PySide6.QtMultimedia import QMediaPlayer, QAudioOutput
from PySide6.QtMultimediaWidgets import QVideoWidget


class MediaPlayer(QMainWindow):
    """A complete audio/video media player."""
    
    def __init__(self):
        super().__init__()
        self.setWindowTitle("PySide6 Media Player")
        self.setMinimumSize(800, 600)
        
        # Initialize media player
        self.media_player = QMediaPlayer()
        self.audio_output = QAudioOutput()
        self.media_player.setAudioOutput(self.audio_output)
        
        # Set default volume
        self.audio_output.setVolume(0.5)
        
        # Track state
        self.is_repeat = False
        self.current_file = None
        
        # Setup UI
        self.setup_ui()
        self.setup_menu()
        self.setup_connections()
        
        # Status bar
        self.statusBar().showMessage("Ready - Open a media file to begin")
    
    def setup_ui(self):
        """Create the user interface."""
        central_widget = QWidget()
        self.setCentralWidget(central_widget)
        main_layout = QVBoxLayout(central_widget)
        main_layout.setContentsMargins(10, 10, 10, 10)
        
        # Video widget
        self.video_widget = QVideoWidget()
        self.video_widget.setSizePolicy(QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Expanding)
        self.video_widget.setMinimumHeight(300)
        self.video_widget.setStyleSheet("background-color: #1a1a2e;")
        self.media_player.setVideoOutput(self.video_widget)
        main_layout.addWidget(self.video_widget)
        
        # Placeholder label (shown when no video)
        self.placeholder_label = QLabel("No media loaded\n\nClick 'Open File' or use File menu")
        self.placeholder_label.setAlignment(Qt.AlignmentFlag.AlignCenter)
        self.placeholder_label.setStyleSheet("""
            QLabel {
                color: #666;
                font-size: 16px;
                background-color: #1a1a2e;
            }
        """)
        
        # Position/seek slider
        seek_layout = QHBoxLayout()
        
        self.position_label = QLabel("00:00")
        self.position_label.setMinimumWidth(50)
        seek_layout.addWidget(self.position_label)
        
        self.seek_slider = QSlider(Qt.Orientation.Horizontal)
        self.seek_slider.setRange(0, 0)
        seek_layout.addWidget(self.seek_slider)
        
        self.duration_label = QLabel("00:00")
        self.duration_label.setMinimumWidth(50)
        seek_layout.addWidget(self.duration_label)
        
        main_layout.addLayout(seek_layout)
        
        # Controls layout
        controls_layout = QHBoxLayout()
        
        # Open file button
        self.open_btn = QPushButton("Open File")
        self.open_btn.setMinimumWidth(100)
        controls_layout.addWidget(self.open_btn)
        
        controls_layout.addSpacing(20)
        
        # Playback controls
        self.play_btn = QPushButton()
        self.play_btn.setIcon(self.style().standardIcon(QStyle.StandardPixmap.SP_MediaPlay))
        self.play_btn.setMinimumWidth(60)
        self.play_btn.setToolTip("Play (Space)")
        controls_layout.addWidget(self.play_btn)
        
        self.pause_btn = QPushButton()
        self.pause_btn.setIcon(self.style().standardIcon(QStyle.StandardPixmap.SP_MediaPause))
        self.pause_btn.setMinimumWidth(60)
        self.pause_btn.setToolTip("Pause")
        controls_layout.addWidget(self.pause_btn)
        
        self.stop_btn = QPushButton()
        self.stop_btn.setIcon(self.style().standardIcon(QStyle.StandardPixmap.SP_MediaStop))
        self.stop_btn.setMinimumWidth(60)
        self.stop_btn.setToolTip("Stop")
        controls_layout.addWidget(self.stop_btn)
        
        controls_layout.addSpacing(20)
        
        # Repeat checkbox
        self.repeat_checkbox = QCheckBox("Repeat")
        self.repeat_checkbox.setToolTip("Loop playback when finished")
        controls_layout.addWidget(self.repeat_checkbox)
        
        controls_layout.addStretch()
        
        # Volume controls
        volume_icon = QLabel()
        volume_icon.setPixmap(
            self.style().standardIcon(QStyle.StandardPixmap.SP_MediaVolume).pixmap(20, 20)
        )
        controls_layout.addWidget(volume_icon)
        
        self.volume_slider = QSlider(Qt.Orientation.Horizontal)
        self.volume_slider.setRange(0, 100)
        self.volume_slider.setValue(50)
        self.volume_slider.setMaximumWidth(120)
        self.volume_slider.setToolTip("Volume")
        controls_layout.addWidget(self.volume_slider)
        
        self.volume_label = QLabel("50%")
        self.volume_label.setMinimumWidth(40)
        controls_layout.addWidget(self.volume_label)
        
        main_layout.addLayout(controls_layout)
        
        # Apply dark theme
        self.setStyleSheet("""
            QMainWindow {
                background-color: #16213e;
            }
            QWidget {
                background-color: #16213e;
                color: #e8e8e8;
            }
            QPushButton {
                background-color: #0f3460;
                color: white;
                border: none;
                padding: 8px 16px;
                border-radius: 4px;
                min-height: 30px;
            }
            QPushButton:hover {
                background-color: #1a4a7a;
            }
            QPushButton:pressed {
                background-color: #0a2540;
            }
            QSlider::groove:horizontal {
                border: 1px solid #0f3460;
                height: 8px;
                background: #0f3460;
                border-radius: 4px;
            }
            QSlider::handle:horizontal {
                background: #e94560;
                border: none;
                width: 16px;
                margin: -4px 0;
                border-radius: 8px;
            }
            QSlider::sub-page:horizontal {
                background: #e94560;
                border-radius: 4px;
            }
            QCheckBox {
                spacing: 8px;
            }
            QCheckBox::indicator {
                width: 18px;
                height: 18px;
            }
            QStatusBar {
                background-color: #0f3460;
                color: #e8e8e8;
            }
            QMenuBar {
                background-color: #0f3460;
                color: #e8e8e8;
            }
            QMenuBar::item:selected {
                background-color: #1a4a7a;
            }
            QMenu {
                background-color: #16213e;
                color: #e8e8e8;
                border: 1px solid #0f3460;
            }
            QMenu::item:selected {
                background-color: #0f3460;
            }
        """)
    
    def setup_menu(self):
        """Create menu bar."""
        menubar = self.menuBar()
        
        # File menu
        file_menu = menubar.addMenu("&File")
        
        open_action = QAction("&Open File...", self)
        open_action.setShortcut(QKeySequence.StandardKey.Open)
        open_action.triggered.connect(self.open_file)
        file_menu.addAction(open_action)
        
        file_menu.addSeparator()
        
        exit_action = QAction("E&xit", self)
        exit_action.setShortcut(QKeySequence.StandardKey.Quit)
        exit_action.triggered.connect(self.close)
        file_menu.addAction(exit_action)
        
        # Playback menu
        playback_menu = menubar.addMenu("&Playback")
        
        play_action = QAction("&Play/Pause", self)
        play_action.setShortcut(Qt.Key.Key_Space)
        play_action.triggered.connect(self.toggle_play_pause)
        playback_menu.addAction(play_action)
        
        stop_action = QAction("&Stop", self)
        stop_action.setShortcut(Qt.Key.Key_S)
        stop_action.triggered.connect(self.stop)
        playback_menu.addAction(stop_action)
        
        playback_menu.addSeparator()
        
        repeat_action = QAction("&Repeat", self)
        repeat_action.setCheckable(True)
        repeat_action.setShortcut(Qt.Key.Key_R)
        repeat_action.triggered.connect(self.repeat_checkbox.setChecked)
        playback_menu.addAction(repeat_action)
        self.repeat_action = repeat_action
    
    def setup_connections(self):
        """Connect signals and slots."""
        # Button connections
        self.open_btn.clicked.connect(self.open_file)
        self.play_btn.clicked.connect(self.play)
        self.pause_btn.clicked.connect(self.pause)
        self.stop_btn.clicked.connect(self.stop)
        
        # Repeat checkbox
        self.repeat_checkbox.toggled.connect(self.set_repeat)
        
        # Seek slider
        self.seek_slider.sliderMoved.connect(self.set_position)
        self.seek_slider.sliderPressed.connect(self.slider_pressed)
        self.seek_slider.sliderReleased.connect(self.slider_released)
        
        # Volume slider
        self.volume_slider.valueChanged.connect(self.set_volume)
        
        # Media player signals
        self.media_player.positionChanged.connect(self.position_changed)
        self.media_player.durationChanged.connect(self.duration_changed)
        self.media_player.playbackStateChanged.connect(self.state_changed)
        self.media_player.mediaStatusChanged.connect(self.media_status_changed)
        self.media_player.errorOccurred.connect(self.handle_error)
        
        # Track if slider is being dragged
        self.slider_is_pressed = False
    
    @Slot()
    def open_file(self):
        """Open a media file."""
        file_filter = (
            "Media Files (*.mp4 *.avi *.mkv *.mov *.wmv *.flv *.webm "
            "*.mp3 *.wav *.ogg *.flac *.aac *.m4a *.wma);;"
            "Video Files (*.mp4 *.avi *.mkv *.mov *.wmv *.flv *.webm);;"
            "Audio Files (*.mp3 *.wav *.ogg *.flac *.aac *.m4a *.wma);;"
            "All Files (*.*)"
        )
        
        file_path, _ = QFileDialog.getOpenFileName(
            self,
            "Open Media File",
            "",
            file_filter
        )
        
        if file_path:
            self.load_media(file_path)
    
    def load_media(self, file_path):
        """Load a media file."""
        self.current_file = file_path
        self.media_player.setSource(QUrl.fromLocalFile(file_path))
        
        # Update window title
        file_name = Path(file_path).name
        self.setWindowTitle(f"PySide6 Media Player - {file_name}")
        
        # Update status
        self.statusBar().showMessage(f"Loaded: {file_name}")
        
        # Auto-play
        self.play()
    
    @Slot()
    def play(self):
        """Start playback."""
        if self.media_player.source().isEmpty():
            self.statusBar().showMessage("No media file loaded")
            return
        self.media_player.play()
    
    @Slot()
    def pause(self):
        """Pause playback."""
        self.media_player.pause()
    
    @Slot()
    def toggle_play_pause(self):
        """Toggle between play and pause."""
        if self.media_player.playbackState() == QMediaPlayer.PlaybackState.PlayingState:
            self.pause()
        else:
            self.play()
    
    @Slot()
    def stop(self):
        """Stop playback."""
        self.media_player.stop()
    
    @Slot(bool)
    def set_repeat(self, enabled):
        """Enable or disable repeat mode."""
        self.is_repeat = enabled
        self.repeat_action.setChecked(enabled)
        status = "Repeat enabled" if enabled else "Repeat disabled"
        self.statusBar().showMessage(status, 2000)
    
    @Slot(int)
    def set_position(self, position):
        """Set playback position."""
        self.media_player.setPosition(position)
    
    @Slot()
    def slider_pressed(self):
        """Track when slider is being dragged."""
        self.slider_is_pressed = True
    
    @Slot()
    def slider_released(self):
        """Handle slider release."""
        self.slider_is_pressed = False
        self.set_position(self.seek_slider.value())
    
    @Slot(int)
    def set_volume(self, value):
        """Set audio volume."""
        volume = value / 100.0
        self.audio_output.setVolume(volume)
        self.volume_label.setText(f"{value}%")
    
    @Slot(int)
    def position_changed(self, position):
        """Handle position change."""
        if not self.slider_is_pressed:
            self.seek_slider.setValue(position)
        self.position_label.setText(self.format_time(position))
    
    @Slot(int)
    def duration_changed(self, duration):
        """Handle duration change."""
        self.seek_slider.setRange(0, duration)
        self.duration_label.setText(self.format_time(duration))
    
    @Slot(QMediaPlayer.PlaybackState)
    def state_changed(self, state):
        """Handle playback state changes."""
        if state == QMediaPlayer.PlaybackState.PlayingState:
            self.play_btn.setIcon(
                self.style().standardIcon(QStyle.StandardPixmap.SP_MediaPause)
            )
            self.statusBar().showMessage("Playing")
        elif state == QMediaPlayer.PlaybackState.PausedState:
            self.play_btn.setIcon(
                self.style().standardIcon(QStyle.StandardPixmap.SP_MediaPlay)
            )
            self.statusBar().showMessage("Paused")
        else:  # Stopped
            self.play_btn.setIcon(
                self.style().standardIcon(QStyle.StandardPixmap.SP_MediaPlay)
            )
            self.statusBar().showMessage("Stopped")
    
    @Slot(QMediaPlayer.MediaStatus)
    def media_status_changed(self, status):
        """Handle media status changes."""
        if status == QMediaPlayer.MediaStatus.EndOfMedia:
            if self.is_repeat:
                # Restart from beginning
                self.media_player.setPosition(0)
                self.media_player.play()
                self.statusBar().showMessage("Repeating...")
            else:
                self.statusBar().showMessage("Playback finished")
        elif status == QMediaPlayer.MediaStatus.LoadedMedia:
            self.statusBar().showMessage("Media loaded - Ready to play")
        elif status == QMediaPlayer.MediaStatus.BufferingMedia:
            self.statusBar().showMessage("Buffering...")
        elif status == QMediaPlayer.MediaStatus.InvalidMedia:
            self.statusBar().showMessage("Error: Invalid media file")
    
    @Slot(QMediaPlayer.Error, str)
    def handle_error(self, error, error_string):
        """Handle media player errors."""
        self.statusBar().showMessage(f"Error: {error_string}")
    
    def format_time(self, ms):
        """Format milliseconds as MM:SS or HH:MM:SS."""
        time = QTime(0, 0, 0).addMSecs(ms)
        if ms >= 3600000:  # 1 hour or more
            return time.toString("hh:mm:ss")
        return time.toString("mm:ss")
    
    def keyPressEvent(self, event):
        """Handle keyboard shortcuts."""
        if event.key() == Qt.Key.Key_Space:
            self.toggle_play_pause()
        elif event.key() == Qt.Key.Key_Left:
            # Seek backward 5 seconds
            new_pos = max(0, self.media_player.position() - 5000)
            self.media_player.setPosition(new_pos)
        elif event.key() == Qt.Key.Key_Right:
            # Seek forward 5 seconds
            new_pos = min(self.media_player.duration(), 
                         self.media_player.position() + 5000)
            self.media_player.setPosition(new_pos)
        elif event.key() == Qt.Key.Key_Up:
            # Volume up
            new_vol = min(100, self.volume_slider.value() + 5)
            self.volume_slider.setValue(new_vol)
        elif event.key() == Qt.Key.Key_Down:
            # Volume down
            new_vol = max(0, self.volume_slider.value() - 5)
            self.volume_slider.setValue(new_vol)
        elif event.key() == Qt.Key.Key_M:
            # Mute toggle
            if self.audio_output.volume() > 0:
                self._last_volume = self.volume_slider.value()
                self.volume_slider.setValue(0)
            else:
                self.volume_slider.setValue(getattr(self, '_last_volume', 50))
        elif event.key() == Qt.Key.Key_F:
            # Toggle fullscreen
            if self.isFullScreen():
                self.showNormal()
            else:
                self.showFullScreen()
        elif event.key() == Qt.Key.Key_Escape:
            if self.isFullScreen():
                self.showNormal()
        else:
            super().keyPressEvent(event)
    
    def closeEvent(self, event):
        """Clean up on close."""
        self.media_player.stop()
        event.accept()


def main():
    app = QApplication(sys.argv)
    
    # Check if multimedia module is available
    try:
        from PySide6.QtMultimedia import QMediaPlayer
    except ImportError:
        print("Error: PySide6 Multimedia module not found.")
        print("Please install with: pip install PySide6")
        sys.exit(1)
    
    player = MediaPlayer()
    player.show()
    
    print("=" * 50)
    print("PySide6 Media Player")
    print("=" * 50)
    print("\nKeyboard Shortcuts:")
    print("  Space     - Play/Pause")
    print("  S         - Stop")
    print("  R         - Toggle Repeat")
    print("  Left/Right - Seek -/+ 5 seconds")
    print("  Up/Down   - Volume +/- 5%")
    print("  M         - Mute/Unmute")
    print("  F         - Toggle Fullscreen")
    print("  Ctrl+O    - Open File")
    print("  Esc       - Exit Fullscreen")
    print("=" * 50 + "\n")
    
    sys.exit(app.exec())


if __name__ == "__main__":
    main()
