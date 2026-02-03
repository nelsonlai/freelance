class Person:
    def __init__(self, name, age):  # constructor
        self.name = name
        self.age = age
        print("Person object created.")

    def greet(self):
        print(f"Hi, I'm {self.name} and I'm {self.age} years old.")

    def __del__(self):  # destructor
        print("Person object deleted.")
    ## End class definition

if __name__ == "__main__":      # main function <- program entry point
    person_john = Person("John", 30)    # object instantiation, instance to an object
    person_vicky = Person("Vicky", 25)   # object instantiation, instance to an object

    person_john.greet()
    person_vicky.greet()