class Animal:
    def __init__(self, name):
        self.name = name

    def speak(self):
        print("The animal makes a sound.")

class Dog(Animal):
    def speak(self):
        super().speak()
        print(f"{self.name} says Woof!")

class Cat(Animal):
    def speak(self):
        super().speak()
        print(f"{self.name} says Meow!")

if __name__ == "__main__":
    dog = Dog("Buddy")
    cat = Cat("Whiskers")

    dog.speak()  # Output: Buddy says Woof!
    cat.speak()  # Output: Whiskers says Meow!