from abc import ABC, abstractmethod

class Shape(ABC):
    @abstractmethod
    def area(self):
        pass

class Rectangle(Shape): # Rectangle is a type of Shape
    def __init__(self, w, h):
        self.w = w
        self.h = h

    def area(self):     # must implement abstract method
        return self.w * self.h

class Circle(Shape):
    def __init__(self, r):
        self.r = r

    def area(self):     # must implement abstract method
        return 3.14 * self.r ** 2

if __name__ == "__main__":
    # s = Shape()  # Abstract class cannot be instantiated
    r = Rectangle(3, 4)
    c = Circle(5)

    print(r.area())
    print(c.area())