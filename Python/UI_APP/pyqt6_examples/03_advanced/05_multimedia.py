"""
PyQt6 Advanced Example 05: Multimedia
=====================================

This example demonstrates:
- Audio playback with QMediaPlayer
- Basic media controls

Note: Requires PyQt6-Multimedia package

Run: python 05_multimedia.py
"""

import sys
from PyQt6.QtWidgets import (
    QApplication, QMainWindow, QWidget, QVBoxLayout, QHBoxLayout,
    QPushButton, QSlider, QLabel, QFileDialog, QGroupBox
)
from PyQt6.QtCore import Qt, QUrl

try:
    from PyQt6.QtMultimedia import QMediaPlayer, QAudioOutput
    MULTIMEDIA_AVAILABLE = True
except ImportError:
    MULTIMEDIA_AVAILABLE = False


class AudioPlayerDemo(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("PyQt6 Multimedia Demo")
        self.setMinimumSize(500, 250)
        
        central = QWidget()
        self.setCentralWidget(central)
        layout = QVBoxLayout(central)
        
        if not MULTIMEDIA_AVAILABLE:
            layout.addWidget(QLabel(
                "PyQt6-Multimedia is not installed.\n"
                "Install with: pip install PyQt6-Multimedia"
            ))
            return
        
        # Create media player
        self.player = QMediaPlayer()
        self.audio_output = QAudioOutput()
        self.player.setAudioOutput(self.audio_output)
        
        # Player group
        player_group = QGroupBox("Audio Player")
        player_layout = QVBoxLayout(player_group)
        
        # File info
        self.file_label = QLabel("No file loaded")
        player_layout.addWidget(self.file_label)
        
        # Position slider
        self.position_slider = QSlider(Qt.Orientation.Horizontal)
        self.position_slider.sliderMoved.connect(self.set_position)
        player_layout.addWidget(self.position_slider)
        
        # Time labels
        time_layout = QHBoxLayout()
        self.current_time = QLabel("0:00")
        self.total_time = QLabel("0:00")
        time_layout.addWidget(self.current_time)
        time_layout.addStretch()
        time_layout.addWidget(self.total_time)
        player_layout.addLayout(time_layout)
        
        # Controls
        controls = QHBoxLayout()
        
        open_btn = QPushButton("Open File")
        open_btn.clicked.connect(self.open_file)
        controls.addWidget(open_btn)
        
        self.play_btn = QPushButton("Play")
        self.play_btn.clicked.connect(self.toggle_play)
        controls.addWidget(self.play_btn)
        
        stop_btn = QPushButton("Stop")
        stop_btn.clicked.connect(self.stop)
        controls.addWidget(stop_btn)
        
        controls.addWidget(QLabel("Volume:"))
        self.volume_slider = QSlider(Qt.Orientation.Horizontal)
        self.volume_slider.setRange(0, 100)
        self.volume_slider.setValue(50)
        self.volume_slider.valueChanged.connect(self.set_volume)
        self.volume_slider.setMaximumWidth(100)
        controls.addWidget(self.volume_slider)
        
        player_layout.addLayout(controls)
        layout.addWidget(player_group)
        
        # Connect signals
        self.player.positionChanged.connect(self.update_position)
        self.player.durationChanged.connect(self.update_duration)
        
        # Set initial volume
        self.audio_output.setVolume(0.5)
    
    def open_file(self):
        path, _ = QFileDialog.getOpenFileName(
            self, "Open Audio File", "",
            "Audio Files (*.mp3 *.wav *.ogg *.m4a);;All Files (*)"
        )
        if path:
            self.player.setSource(QUrl.fromLocalFile(path))
            self.file_label.setText(path.split("/")[-1])
    
    def toggle_play(self):
        if self.player.playbackState() == QMediaPlayer.PlaybackState.PlayingState:
            self.player.pause()
            self.play_btn.setText("Play")
        else:
            self.player.play()
            self.play_btn.setText("Pause")
    
    def stop(self):
        self.player.stop()
        self.play_btn.setText("Play")
    
    def set_position(self, position):
        self.player.setPosition(position)
    
    def set_volume(self, value):
        self.audio_output.setVolume(value / 100)
    
    def update_position(self, position):
        self.position_slider.setValue(position)
        self.current_time.setText(self.format_time(position))
    
    def update_duration(self, duration):
        self.position_slider.setRange(0, duration)
        self.total_time.setText(self.format_time(duration))
    
    def format_time(self, ms):
        s = ms // 1000
        m = s // 60
        s = s % 60
        return f"{m}:{s:02d}"


def main():
    app = QApplication(sys.argv)
    window = AudioPlayerDemo()
    window.show()
    sys.exit(app.exec())


if __name__ == "__main__":
    main()
