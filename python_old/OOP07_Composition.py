class Engine:
    def start(self):
        print("Engine started.")

class Car:
    def __init__(self):
        self.engine = Engine()  # Composition - A car has an engine, A car is NOT an engine

    def start(self):
        self.engine.start()
        print("Car is running.")

if __name__ == "__main__":
    car = Car()
    car.start()