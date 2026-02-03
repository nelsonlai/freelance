class Shape:
    def area(self):
        pass

class Circle(Shape):
    def __init__(self, radius):
        self.radius = radius

    def area(self):
        return 3.14 * self.radius ** 2

class Square(Shape):
    def __init__(self, side):
        self.side = side

    def area(self):
        return self.side ** 2

class Rectangle(Shape):
    def __init__(self, length, width):
        self.length = length
        self.width = width

    def area(self):
        return self.length * self.width

if __name__ == "__main__":
    circle = Circle(5)
    square = Square(4)
    rectangle = Rectangle(3, 6)

    shapes = [circle, square, rectangle]

    for shape in shapes:
        print(f"Area of {type(shape).__name__}: {shape.area()}")

    # Output:
    # Area of Circle: 78.5
    # Area of Square: 16
    # Area of Rectangle: 18
