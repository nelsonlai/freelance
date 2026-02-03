class Animal:
    def speak(self):
        print("Some generic animal sound")

class Dog(Animal):
    def speak(self):
        print("Woof!")

    def fetch(self):
        print("Dog is fetching the ball!")

class Cat(Animal):
    def speak(self):
        print("Meow!")

    def scratch(self):
        print("Cat is scratching the post!")

def interact_with_animal(animal):
    animal.speak()

    if isinstance(animal, Dog):
        animal.fetch()  # Cast to Dog and call Dog-specific method
    elif isinstance(animal, Cat):
        animal.scratch()  # Cast to Cat and call Cat-specific method
    else:
        print("Unknown animal type.")

if __name__ == "__main__":
    # Test the polymorphism and casting
    animals = [Dog(), Cat(), Animal()]

    for a in animals:
        a.speak()
        interact_with_animal(a)