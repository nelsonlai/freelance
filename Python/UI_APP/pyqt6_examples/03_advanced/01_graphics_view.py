"""
PyQt6 Advanced Example 01: Graphics View Framework
==================================================

This example demonstrates:
- QGraphicsScene for managing items
- QGraphicsView for displaying scenes
- Custom QGraphicsItem classes
- Interactive drawing

Run: python 01_graphics_view.py
"""

import sys
import math
from PyQt6.QtWidgets import (
    QApplication, QMainWindow, QWidget, QVBoxLayout, QHBoxLayout,
    QGraphicsView, QGraphicsScene, QGraphicsItem,
    QGraphicsRectItem, QGraphicsEllipseItem,
    QPushButton, QColorDialog, QSpinBox, QLabel, QToolBar
)
from PyQt6.QtCore import Qt, QRectF, QPointF
from PyQt6.QtGui import QPainter, QPen, QBrush, QColor, QPainterPath


class StarItem(QGraphicsItem):
    """A custom star-shaped graphics item."""
    
    def __init__(self, points=5, outer_radius=50, inner_radius=25, parent=None):
        super().__init__(parent)
        self.points = points
        self.outer_radius = outer_radius
        self.inner_radius = inner_radius
        self._color = QColor(255, 215, 0)
        
        self.setFlags(
            QGraphicsItem.GraphicsItemFlag.ItemIsMovable |
            QGraphicsItem.GraphicsItemFlag.ItemIsSelectable
        )
    
    def boundingRect(self):
        return QRectF(
            -self.outer_radius - 2,
            -self.outer_radius - 2,
            self.outer_radius * 2 + 4,
            self.outer_radius * 2 + 4
        )
    
    def _create_star_path(self):
        path = QPainterPath()
        angle_step = math.pi / self.points
        
        for i in range(self.points * 2):
            radius = self.outer_radius if i % 2 == 0 else self.inner_radius
            angle = i * angle_step - math.pi / 2
            
            x = radius * math.cos(angle)
            y = radius * math.sin(angle)
            
            if i == 0:
                path.moveTo(x, y)
            else:
                path.lineTo(x, y)
        
        path.closeSubpath()
        return path
    
    def paint(self, painter, option, widget):
        painter.setRenderHint(QPainter.RenderHint.Antialiasing)
        
        if self.isSelected():
            painter.setPen(QPen(Qt.GlobalColor.blue, 2, Qt.PenStyle.DashLine))
            painter.drawRect(self.boundingRect())
        
        painter.setPen(QPen(self._color.darker(120), 2))
        painter.setBrush(QBrush(self._color))
        painter.drawPath(self._create_star_path())
    
    def setColor(self, color):
        self._color = color
        self.update()


class DrawingScene(QGraphicsScene):
    """Scene that supports freehand drawing."""
    
    def __init__(self):
        super().__init__()
        self.setSceneRect(-500, -400, 1000, 800)
        
        self.drawing = False
        self.current_path = None
        self.current_path_item = None
        self.pen_color = QColor(Qt.GlobalColor.black)
        self.pen_width = 2
        self.draw_mode = False
    
    def set_draw_mode(self, enabled):
        self.draw_mode = enabled
    
    def mousePressEvent(self, event):
        if self.draw_mode and event.button() == Qt.MouseButton.LeftButton:
            self.drawing = True
            pos = event.scenePos()
            self.current_path = QPainterPath(pos)
            pen = QPen(self.pen_color, self.pen_width)
            pen.setCapStyle(Qt.PenCapStyle.RoundCap)
            self.current_path_item = self.addPath(self.current_path, pen)
            event.accept()
        else:
            super().mousePressEvent(event)
    
    def mouseMoveEvent(self, event):
        if self.drawing and self.current_path and self.current_path_item:
            self.current_path.lineTo(event.scenePos())
            self.current_path_item.setPath(self.current_path)
            event.accept()
        else:
            super().mouseMoveEvent(event)
    
    def mouseReleaseEvent(self, event):
        if self.drawing:
            self.drawing = False
            self.current_path = None
            event.accept()
        else:
            super().mouseReleaseEvent(event)


class GraphicsViewDemo(QMainWindow):
    """Main window for Graphics View demo."""
    
    def __init__(self):
        super().__init__()
        self.setWindowTitle("PyQt6 Graphics View Demo")
        self.setMinimumSize(800, 600)
        
        self.scene = DrawingScene()
        self.view = QGraphicsView(self.scene)
        self.view.setRenderHint(QPainter.RenderHint.Antialiasing)
        self.view.setDragMode(QGraphicsView.DragMode.RubberBandDrag)
        
        self.add_initial_items()
        
        central = QWidget()
        self.setCentralWidget(central)
        layout = QVBoxLayout(central)
        
        toolbar = self.create_toolbar()
        layout.addWidget(toolbar)
        layout.addWidget(self.view)
    
    def create_toolbar(self):
        toolbar = QToolBar()
        
        select_btn = QPushButton("Select Mode")
        select_btn.setCheckable(True)
        select_btn.setChecked(True)
        select_btn.clicked.connect(lambda: self.set_mode("select"))
        toolbar.addWidget(select_btn)
        self.select_btn = select_btn
        
        draw_btn = QPushButton("Draw Mode")
        draw_btn.setCheckable(True)
        draw_btn.clicked.connect(lambda: self.set_mode("draw"))
        toolbar.addWidget(draw_btn)
        self.draw_btn = draw_btn
        
        toolbar.addSeparator()
        
        rect_btn = QPushButton("Add Rectangle")
        rect_btn.clicked.connect(self.add_rectangle)
        toolbar.addWidget(rect_btn)
        
        ellipse_btn = QPushButton("Add Ellipse")
        ellipse_btn.clicked.connect(self.add_ellipse)
        toolbar.addWidget(ellipse_btn)
        
        star_btn = QPushButton("Add Star")
        star_btn.clicked.connect(self.add_star)
        toolbar.addWidget(star_btn)
        
        toolbar.addSeparator()
        
        clear_btn = QPushButton("Clear All")
        clear_btn.clicked.connect(self.scene.clear)
        toolbar.addWidget(clear_btn)
        
        return toolbar
    
    def add_initial_items(self):
        # Grid
        pen = QPen(QColor(230, 230, 230), 1)
        for x in range(-500, 501, 50):
            self.scene.addLine(x, -400, x, 400, pen)
        for y in range(-400, 401, 50):
            self.scene.addLine(-500, y, 500, y, pen)
        
        # Sample shapes
        rect = QGraphicsRectItem(0, 0, 100, 60)
        rect.setBrush(QBrush(QColor(100, 149, 237)))
        rect.setPos(-200, -100)
        rect.setFlags(
            QGraphicsItem.GraphicsItemFlag.ItemIsMovable |
            QGraphicsItem.GraphicsItemFlag.ItemIsSelectable
        )
        self.scene.addItem(rect)
        
        ellipse = QGraphicsEllipseItem(0, 0, 80, 80)
        ellipse.setBrush(QBrush(QColor(255, 165, 0)))
        ellipse.setPos(100, -50)
        ellipse.setFlags(
            QGraphicsItem.GraphicsItemFlag.ItemIsMovable |
            QGraphicsItem.GraphicsItemFlag.ItemIsSelectable
        )
        self.scene.addItem(ellipse)
        
        star = StarItem(5, 50, 25)
        star.setPos(0, 100)
        self.scene.addItem(star)
    
    def set_mode(self, mode):
        if mode == "select":
            self.select_btn.setChecked(True)
            self.draw_btn.setChecked(False)
            self.view.setDragMode(QGraphicsView.DragMode.RubberBandDrag)
            self.scene.set_draw_mode(False)
        else:
            self.select_btn.setChecked(False)
            self.draw_btn.setChecked(True)
            self.view.setDragMode(QGraphicsView.DragMode.NoDrag)
            self.scene.set_draw_mode(True)
    
    def add_rectangle(self):
        rect = QGraphicsRectItem(0, 0, 100, 60)
        rect.setBrush(QBrush(self.scene.pen_color.lighter(150)))
        rect.setPen(QPen(self.scene.pen_color, 2))
        rect.setPos(0, 0)
        rect.setFlags(
            QGraphicsItem.GraphicsItemFlag.ItemIsMovable |
            QGraphicsItem.GraphicsItemFlag.ItemIsSelectable
        )
        self.scene.addItem(rect)
    
    def add_ellipse(self):
        ellipse = QGraphicsEllipseItem(0, 0, 80, 60)
        ellipse.setBrush(QBrush(self.scene.pen_color.lighter(150)))
        ellipse.setPen(QPen(self.scene.pen_color, 2))
        ellipse.setPos(0, 0)
        ellipse.setFlags(
            QGraphicsItem.GraphicsItemFlag.ItemIsMovable |
            QGraphicsItem.GraphicsItemFlag.ItemIsSelectable
        )
        self.scene.addItem(ellipse)
    
    def add_star(self):
        star = StarItem(5, 50, 25)
        star.setColor(self.scene.pen_color)
        star.setPos(0, 0)
        self.scene.addItem(star)


def main():
    app = QApplication(sys.argv)
    window = GraphicsViewDemo()
    window.show()
    sys.exit(app.exec())


if __name__ == "__main__":
    main()
