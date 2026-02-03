class A:
    def show(self):
        print("A.show() called")

class B(A):
    def show(self):
        print("B.show() called")

class C(A):
    def show(self):
        print("C.show() called")

class D(B, C):
    def show(self):
        print("D.show() called")

if __name__ == "__main__":
    obj = D()
    obj.show()  # Which class's show() will be called?

    # Print the MRO order
    print("MRO of D:", D.__mro__)