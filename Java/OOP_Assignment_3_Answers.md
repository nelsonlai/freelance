
# Object-Oriented Programming (CCIT4023)
## Assignment 3 – Detailed Answers

---

## Section A (20 marks)

1. **Answer:** A) Array of String  
   The `main` method signature is `public static void main(String[] args)`.

2. **Answer:** C) Constructors  
   Constructors are not inherited in Java.

3. **Answer:** B) Field  
   Identifier resolution order: local variable → parameter → field.

4. **Answer:** D) All of the other answers  
   `ee.dept` is a package, `import` is a keyword, and `Div` is a class.

5. **Answer:** D) this  
   Used to call another constructor in the same class.

6. **Answer:** D) Overriding  
   Allows a subclass to reimplement a superclass method.

7. **Answer:** B) It declares and creates an object of Pet array  
   The array is created, elements are initialized to `null`.

8. **Answer:** B) "06"  
   `36 % 6 = 0`, then `0 + "6"` results in `"06"`.

9. **Answer:** D) All of the other answers  
   All options declare arrays.

10. **Answer:** A) 412  
    `doubleA.length = 4`, `"4" + "12"` results in `"412"`.

---

## Section B (40 marks)

### 1(a) Three Major OOP Features (6 marks)

- **Encapsulation:** Bundling data and methods together while restricting access using access modifiers.
- **Inheritance:** Allowing a subclass to reuse and extend the properties and methods of a superclass.
- **Polymorphism:** Allowing objects to take multiple forms through method overriding.

---

### 1(b) Operator Evaluation (4 marks)

i. `d >= c && e != a - c <= d + b`  
- First evaluated operator: `-`  
- Last evaluated operator: `&&`

ii. `a == d % b || d < b && c <= b`  
- First evaluated operator: `%`  
- Last evaluated operator: `||`

---

## 2. Class Card (15 marks)

```java
public class Card {
    public String cName;
    protected int cCode;

    Card(String inName, int inCode){
        cName = inName;
        cCode = inCode;
    }
}
```

### 2(a) Visibility Modifiers (2 marks)
- `public`
- `protected`
- default (package-private)

### 2(b) Primitive and Reference Types (2 marks)
- Primitive: `int`
- Reference: `String`, `Card`

### 2(c) UML Class Diagram (5 marks)

```
-------------------------
|        Card           |
-------------------------
| + cName : String      |
| # cCode : int         |
-------------------------
| Card(String, int)     |
-------------------------
```

### 2(d) getInfo() Method (3 marks)

```java
public String[] getInfo() {
    String[] info = new String[2];
    info[0] = cName;
    info[1] = String.valueOf(cCode);
    return info;
}
```
String str = "456";
int num = Integer.valueOf(str);

### 2(e) dspInfo() Method (3 marks)

```java
public void dspInfo() {
    System.out.println("Card Name: " + cName + "; Card Code: " + cCode);
}
```

---

## 3. Subclass MyCard (15 marks)

```java
public class MyCard extends Card {  // MyCard inherits Card class

    public static final int DEF_CCODE = 23357;
    public String abc;
    public MyCard(String name, int code) {
        super(name, code);
    }

    public MyCard(String name) {
        this(name, DEF_CCODE);  // this.MyCard(name, DEF_CODE);
        this.abc = "sdfsdf";
    }

    public static void main(String[] args) {
        Card[] cards = new Card[4];
        Card newCard = new MyCard("TestCard", 2200);
        newCard.abc = "sfsdfa";

        cards[0] = new Card("cdA", 2134);
        cards[1] = new Card("cdB", 2135);
        cards[2] = new Card("cdC", 2136);
        cards[3] = new MyCard("cdD");

        for (int i = 0; i < cards.length; i++) {
            cards[i].dspInfo();
        }
    }
}
```

### Sample Output
```
Card Name: cdA; Card Code: 2134
Card Name: cdB; Card Code: 2135
Card Name: cdC; Card Code: 2136
Card Name: cdD; Card Code: 23357
```

---
