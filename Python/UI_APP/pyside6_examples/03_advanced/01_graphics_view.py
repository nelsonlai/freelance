"""
PySide6 Advanced Example 01: Graphics View Framework
====================================================

This example demonstrates:
- QGraphicsScene for managing items
- QGraphicsView for displaying scenes
- Custom QGraphicsItem classes
- Interactive items (movable, selectable)
- Drawing application basics

Run: python 01_graphics_view.py
"""

import sys
import math
from PySide6.QtWidgets import (
    QApplication, QMainWindow, QWidget, QVBoxLayout, QHBoxLayout,
    QGraphicsView, QGraphicsScene, QGraphicsItem,
    QGraphicsRectItem, QGraphicsEllipseItem, QGraphicsLineItem,
    QGraphicsTextItem, QGraphicsPathItem,
    QPushButton, QColorDialog, QSpinBox, QLabel, QToolBar,
    QComboBox
)
from PySide6.QtCore import Qt, QRectF, QPointF
from PySide6.QtGui import (
    QPainter, QPen, QBrush, QColor, QFont, QPainterPath,
    QTransform
)


class ResizableRectItem(QGraphicsRectItem):
    """A rectangle that can be resized by dragging corners."""
    
    HANDLE_SIZE = 8
    
    def __init__(self, rect, parent=None):
        super().__init__(rect, parent)
        self.setFlags(
            QGraphicsItem.GraphicsItemFlag.ItemIsMovable |
            QGraphicsItem.GraphicsItemFlag.ItemIsSelectable |
            QGraphicsItem.GraphicsItemFlag.ItemSendsGeometryChanges
        )
        self.setAcceptHoverEvents(True)
        self._resize_handle = None
        self._start_rect = None
    
    def hoverMoveEvent(self, event):
        """Update cursor when hovering over resize handles."""
        handle = self._get_handle_at(event.pos())
        if handle:
            self.setCursor(Qt.CursorShape.SizeFDiagCursor)
        else:
            self.setCursor(Qt.CursorShape.ArrowCursor)
        super().hoverMoveEvent(event)
    
    def mousePressEvent(self, event):
        """Start resize if clicking on a handle."""
        if event.button() == Qt.MouseButton.LeftButton:
            handle = self._get_handle_at(event.pos())
            if handle:
                self._resize_handle = handle
                self._start_rect = self.rect()
                event.accept()
                return
        super().mousePressEvent(event)
    
    def mouseMoveEvent(self, event):
        """Handle resize dragging."""
        if self._resize_handle:
            rect = self._start_rect
            pos = event.pos()
            
            if self._resize_handle == "bottom-right":
                new_rect = QRectF(
                    rect.topLeft(),
                    QPointF(max(20, pos.x()), max(20, pos.y()))
                )
                self.setRect(new_rect)
            
            event.accept()
            return
        super().mouseMoveEvent(event)
    
    def mouseReleaseEvent(self, event):
        """End resize operation."""
        self._resize_handle = None
        self._start_rect = None
        super().mouseReleaseEvent(event)
    
    def _get_handle_at(self, pos):
        """Get resize handle at position."""
        rect = self.rect()
        handle_rect = QRectF(
            rect.right() - self.HANDLE_SIZE,
            rect.bottom() - self.HANDLE_SIZE,
            self.HANDLE_SIZE,
            self.HANDLE_SIZE
        )
        if handle_rect.contains(pos):
            return "bottom-right"
        return None
    
    def paint(self, painter, option, widget):
        """Draw the rectangle with resize handles."""
        super().paint(painter, option, widget)
        
        if self.isSelected():
            # Draw resize handle
            rect = self.rect()
            handle_rect = QRectF(
                rect.right() - self.HANDLE_SIZE,
                rect.bottom() - self.HANDLE_SIZE,
                self.HANDLE_SIZE,
                self.HANDLE_SIZE
            )
            painter.fillRect(handle_rect, QColor(0, 120, 215))


class StarItem(QGraphicsItem):
    """A custom star-shaped graphics item."""
    
    def __init__(self, points=5, outer_radius=50, inner_radius=25, parent=None):
        super().__init__(parent)
        self.points = points
        self.outer_radius = outer_radius
        self.inner_radius = inner_radius
        self._color = QColor(255, 215, 0)  # Gold
        
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
    
    def shape(self):
        path = QPainterPath()
        path.addPath(self._create_star_path())
        return path
    
    def _create_star_path(self):
        """Create the star path."""
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
        
        # Selection highlight
        if self.isSelected():
            painter.setPen(QPen(Qt.GlobalColor.blue, 2, Qt.PenStyle.DashLine))
            painter.drawRect(self.boundingRect())
        
        # Draw star
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
        """Enable or disable draw mode."""
        self.draw_mode = enabled
    
    def mousePressEvent(self, event):
        if self.draw_mode and event.button() == Qt.MouseButton.LeftButton:
            self.drawing = True
            pos = event.scenePos()
            self.current_path = QPainterPath(pos)
            # Create pen and set cap style separately (PySide6 doesn't support cap= keyword)
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
            self.current_path_item = None
            event.accept()
        else:
            super().mouseReleaseEvent(event)


class GraphicsViewDemo(QMainWindow):
    """Main window for Graphics View demo."""
    
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Graphics View Framework Demo")
        self.setMinimumSize(900, 700)
        
        # Create scene and view
        self.scene = DrawingScene()
        self.view = QGraphicsView(self.scene)
        self.view.setRenderHint(QPainter.RenderHint.Antialiasing)
        self.view.setDragMode(QGraphicsView.DragMode.RubberBandDrag)
        self.view.setViewportUpdateMode(
            QGraphicsView.ViewportUpdateMode.FullViewportUpdate
        )
        
        # Create UI first (before adding items, since update_item_count needs the label)
        central = QWidget()
        self.setCentralWidget(central)
        layout = QVBoxLayout(central)
        
        # Toolbar
        toolbar = self.create_toolbar()
        layout.addWidget(toolbar)
        
        layout.addWidget(self.view)
        
        # Bottom controls
        controls = self.create_controls()
        layout.addLayout(controls)
        
        # Add initial items after UI is created
        self.add_initial_items()
    
    def create_toolbar(self):
        """Create the toolbar."""
        toolbar = QToolBar()
        
        # Selection mode
        select_btn = QPushButton("Select Mode")
        select_btn.setCheckable(True)
        select_btn.setChecked(True)
        select_btn.clicked.connect(lambda: self.set_mode("select"))
        toolbar.addWidget(select_btn)
        self.select_btn = select_btn
        
        # Draw mode
        draw_btn = QPushButton("Draw Mode")
        draw_btn.setCheckable(True)
        draw_btn.clicked.connect(lambda: self.set_mode("draw"))
        toolbar.addWidget(draw_btn)
        self.draw_btn = draw_btn
        
        toolbar.addSeparator()
        
        # Add shapes
        toolbar.addWidget(QLabel(" Add: "))
        
        rect_btn = QPushButton("Rectangle")
        rect_btn.clicked.connect(self.add_rectangle)
        toolbar.addWidget(rect_btn)
        
        ellipse_btn = QPushButton("Ellipse")
        ellipse_btn.clicked.connect(self.add_ellipse)
        toolbar.addWidget(ellipse_btn)
        
        star_btn = QPushButton("Star")
        star_btn.clicked.connect(self.add_star)
        toolbar.addWidget(star_btn)
        
        text_btn = QPushButton("Text")
        text_btn.clicked.connect(self.add_text)
        toolbar.addWidget(text_btn)
        
        toolbar.addSeparator()
        
        # Delete
        delete_btn = QPushButton("Delete Selected")
        delete_btn.clicked.connect(self.delete_selected)
        toolbar.addWidget(delete_btn)
        
        # Clear
        clear_btn = QPushButton("Clear All")
        clear_btn.clicked.connect(self.scene.clear)
        toolbar.addWidget(clear_btn)
        
        return toolbar
    
    def create_controls(self):
        """Create bottom controls."""
        layout = QHBoxLayout()
        
        # Color picker
        layout.addWidget(QLabel("Color:"))
        self.color_btn = QPushButton()
        self.color_btn.setFixedSize(30, 30)
        self.color_btn.setStyleSheet("background-color: black;")
        self.color_btn.clicked.connect(self.choose_color)
        layout.addWidget(self.color_btn)
        
        # Pen width
        layout.addWidget(QLabel("Pen Width:"))
        self.width_spin = QSpinBox()
        self.width_spin.setRange(1, 20)
        self.width_spin.setValue(2)
        self.width_spin.valueChanged.connect(self.update_pen)
        layout.addWidget(self.width_spin)
        
        layout.addStretch()
        
        # Zoom
        layout.addWidget(QLabel("Zoom:"))
        zoom_combo = QComboBox()
        zoom_combo.addItems(["50%", "75%", "100%", "125%", "150%", "200%"])
        zoom_combo.setCurrentText("100%")
        zoom_combo.currentTextChanged.connect(self.set_zoom)
        layout.addWidget(zoom_combo)
        
        # Item count
        self.item_count_label = QLabel("Items: 0")
        layout.addWidget(self.item_count_label)
        
        return layout
    
    def add_initial_items(self):
        """Add some initial items to the scene."""
        # Background grid
        pen = QPen(QColor(230, 230, 230), 1)
        for x in range(-500, 501, 50):
            self.scene.addLine(x, -400, x, 400, pen)
        for y in range(-400, 401, 50):
            self.scene.addLine(-500, y, 500, y, pen)
        
        # Add sample shapes
        rect = ResizableRectItem(QRectF(0, 0, 100, 60))
        rect.setBrush(QBrush(QColor(100, 149, 237)))
        rect.setPen(QPen(QColor(70, 130, 180), 2))
        rect.setPos(-200, -100)
        self.scene.addItem(rect)
        
        ellipse = QGraphicsEllipseItem(0, 0, 80, 80)
        ellipse.setBrush(QBrush(QColor(255, 165, 0)))
        ellipse.setPen(QPen(QColor(255, 140, 0), 2))
        ellipse.setPos(100, -50)
        ellipse.setFlags(
            QGraphicsItem.GraphicsItemFlag.ItemIsMovable |
            QGraphicsItem.GraphicsItemFlag.ItemIsSelectable
        )
        self.scene.addItem(ellipse)
        
        star = StarItem(5, 50, 25)
        star.setPos(0, 100)
        self.scene.addItem(star)
        
        self.update_item_count()
    
    def set_mode(self, mode):
        """Set the interaction mode."""
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
        """Add a rectangle to the scene."""
        rect = ResizableRectItem(QRectF(0, 0, 100, 60))
        rect.setBrush(QBrush(self.scene.pen_color.lighter(150)))
        rect.setPen(QPen(self.scene.pen_color, 2))
        rect.setPos(0, 0)
        self.scene.addItem(rect)
        self.update_item_count()
    
    def add_ellipse(self):
        """Add an ellipse to the scene."""
        ellipse = QGraphicsEllipseItem(0, 0, 80, 60)
        ellipse.setBrush(QBrush(self.scene.pen_color.lighter(150)))
        ellipse.setPen(QPen(self.scene.pen_color, 2))
        ellipse.setPos(0, 0)
        ellipse.setFlags(
            QGraphicsItem.GraphicsItemFlag.ItemIsMovable |
            QGraphicsItem.GraphicsItemFlag.ItemIsSelectable
        )
        self.scene.addItem(ellipse)
        self.update_item_count()
    
    def add_star(self):
        """Add a star to the scene."""
        star = StarItem(5, 50, 25)
        star.setColor(self.scene.pen_color)
        star.setPos(0, 0)
        self.scene.addItem(star)
        self.update_item_count()
    
    def add_text(self):
        """Add text to the scene."""
        text = QGraphicsTextItem("Hello!")
        text.setFont(QFont("Arial", 24))
        text.setDefaultTextColor(self.scene.pen_color)
        text.setPos(0, 0)
        text.setFlags(
            QGraphicsItem.GraphicsItemFlag.ItemIsMovable |
            QGraphicsItem.GraphicsItemFlag.ItemIsSelectable
        )
        self.scene.addItem(text)
        self.update_item_count()
    
    def delete_selected(self):
        """Delete selected items."""
        for item in self.scene.selectedItems():
            self.scene.removeItem(item)
        self.update_item_count()
    
    def choose_color(self):
        """Open color picker."""
        color = QColorDialog.getColor(self.scene.pen_color, self)
        if color.isValid():
            self.scene.pen_color = color
            self.color_btn.setStyleSheet(f"background-color: {color.name()};")
    
    def update_pen(self, width):
        """Update pen width."""
        self.scene.pen_width = width
    
    def set_zoom(self, zoom_text):
        """Set view zoom level."""
        zoom = int(zoom_text.replace("%", "")) / 100.0
        self.view.resetTransform()
        self.view.scale(zoom, zoom)
    
    def update_item_count(self):
        """Update item count label."""
        # Count only user items (skip grid lines)
        count = len([item for item in self.scene.items() 
                    if not isinstance(item, QGraphicsLineItem) or 
                    item.pen().color() != QColor(230, 230, 230)])
        self.item_count_label.setText(f"Items: {count}")


def main():
    app = QApplication(sys.argv)
    window = GraphicsViewDemo()
    window.show()
    sys.exit(app.exec())


if __name__ == "__main__":
    main()
