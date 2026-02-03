class Student:
    school = "Python High School"  # class variable

    def __init__(self, name):
        self.name = name  # instance/object variable

    def print_name(self):   # instance method
        print(f"My name is {self.name}")

    @classmethod    # decorator
    def print_school(cls):      # class method
        print(f"Our school is {cls.school}")

    @staticmethod
    def print_info():   # static method
        print("This is a student class")

    def __repr__(self):
        return f"Student(name={self.name})"

    def __str__(self):
        return f"Student(name={self.name})"

    def __len__(self):
        return len(self.name)
    

if __name__ == "__main__":
    student_John = Student("John")
    print(student_John)
    print(repr(student_John))
    print(str(student_John))
    print(len(student_John))

    student_John.print_name()
    student_John.print_school()
    Student.print_info()