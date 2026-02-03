/**
 * ADVANCED LEVEL - Lesson 1: Generics
 * 
 * This lesson covers:
 * - Generic classes
 * - Generic methods
 * - Bounded type parameters
 * - Wildcards (?, ? extends, ? super)
 * - Generic interfaces
 * - Type erasure
 */

// ========== GENERIC CLASS ==========

class Box<T> {
    private T item;
    
    public void setItem(T item) {
        this.item = item;
    }
    
    public T getItem() {
        return item;
    }
    
    public void displayType() {
        System.out.println("Type: " + item.getClass().getSimpleName());
    }
}

// ========== GENERIC CLASS WITH MULTIPLE TYPE PARAMETERS ==========

class Pair<K, V> {
    private K key;
    private V value;
    
    public Pair(K key, V value) {
        this.key = key;
        this.value = value;
    }
    
    public K getKey() {
        return key;
    }
    
    public V getValue() {
        return value;
    }
    
    public void setKey(K key) {
        this.key = key;
    }
    
    public void setValue(V value) {
        this.value = value;
    }
    
    @Override
    public String toString() {
        return "Pair{key=" + key + ", value=" + value + "}";
    }
}

// ========== BOUNDED TYPE PARAMETERS ==========

// T must be a subclass of Number
class NumberBox<T extends Number> {
    private T number;
    
    public NumberBox(T number) {
        this.number = number;
    }
    
    public T getNumber() {
        return number;
    }
    
    public double getDoubleValue() {
        return number.doubleValue();
    }
}

// Multiple bounds: T must extend Comparable AND be a Number
class ComparableNumber<T extends Number & Comparable<T>> {
    private T value;
    
    public ComparableNumber(T value) {
        this.value = value;
    }
    
    public boolean isGreaterThan(T other) {
        return value.compareTo(other) > 0;
    }
}

// ========== GENERIC METHODS ==========

class GenericMethods {
    // Generic method in non-generic class
    public static <T> void printArray(T[] array) {
        for (T element : array) {
            System.out.print(element + " ");
        }
        System.out.println();
    }
    
    // Generic method with bounded type
    public static <T extends Comparable<T>> T findMax(T[] array) {
        if (array == null || array.length == 0) {
            return null;
        }
        T max = array[0];
        for (T element : array) {
            if (element.compareTo(max) > 0) {
                max = element;
            }
        }
        return max;
    }
    
    // Generic method returning generic type
    public static <T> T getFirst(T[] array) {
        return array.length > 0 ? array[0] : null;
    }
}

// ========== GENERIC INTERFACE ==========

interface Container<T> {
    void add(T item);
    T get(int index);
    int size();
}

class ArrayListContainer<T> implements Container<T> {
    private T[] items;
    private int size;
    
    @SuppressWarnings("unchecked")
    public ArrayListContainer(int capacity) {
        items = (T[]) new Object[capacity];
        size = 0;
    }
    
    @Override
    public void add(T item) {
        if (size < items.length) {
            items[size++] = item;
        }
    }
    
    @Override
    public T get(int index) {
        if (index >= 0 && index < size) {
            return items[index];
        }
        return null;
    }
    
    @Override
    public int size() {
        return size;
    }
}

// ========== WILDCARDS ==========

import java.util.List;

class WildcardExamples {
    // Unbounded wildcard: accepts any type
    public static void printList(List<?> list) {
        for (Object item : list) {
            System.out.print(item + " ");
        }
        System.out.println();
    }
    
    // Upper bounded wildcard: accepts Number and its subclasses
    public static double sumNumbers(List<? extends Number> numbers) {
        double sum = 0.0;
        for (Number num : numbers) {
            sum += num.doubleValue();
        }
        return sum;
    }
    
    // Lower bounded wildcard: accepts Integer and its superclasses
    public static void addIntegers(List<? super Integer> list) {
        list.add(1);
        list.add(2);
        list.add(3);
    }
}

// ========== MAIN CLASS ==========

import java.util.*;

public class Generics {
    public static void main(String[] args) {
        System.out.println("=== Generic Classes ===");
        
        Box<String> stringBox = new Box<>();
        stringBox.setItem("Hello, Generics!");
        System.out.println("String box: " + stringBox.getItem());
        stringBox.displayType();
        
        Box<Integer> intBox = new Box<>();
        intBox.setItem(42);
        System.out.println("Integer box: " + intBox.getItem());
        intBox.displayType();
        
        System.out.println("\n=== Multiple Type Parameters ===");
        Pair<String, Integer> pair1 = new Pair<>("Age", 25);
        Pair<Integer, String> pair2 = new Pair<>(1, "One");
        System.out.println(pair1);
        System.out.println(pair2);
        
        System.out.println("\n=== Bounded Type Parameters ===");
        NumberBox<Integer> intNumberBox = new NumberBox<>(100);
        NumberBox<Double> doubleNumberBox = new NumberBox<>(3.14);
        System.out.println("Integer value: " + intNumberBox.getDoubleValue());
        System.out.println("Double value: " + doubleNumberBox.getDoubleValue());
        
        ComparableNumber<Integer> compNum = new ComparableNumber<>(10);
        System.out.println("Is 10 > 5? " + compNum.isGreaterThan(5));
        
        System.out.println("\n=== Generic Methods ===");
        Integer[] intArray = {1, 2, 3, 4, 5};
        String[] stringArray = {"apple", "banana", "cherry"};
        Double[] doubleArray = {1.1, 2.2, 3.3};
        
        GenericMethods.printArray(intArray);
        GenericMethods.printArray(stringArray);
        GenericMethods.printArray(doubleArray);
        
        System.out.println("Max in intArray: " + GenericMethods.findMax(intArray));
        System.out.println("Max in doubleArray: " + GenericMethods.findMax(doubleArray));
        
        System.out.println("\n=== Generic Interfaces ===");
        Container<String> container = new ArrayListContainer<>(10);
        container.add("First");
        container.add("Second");
        container.add("Third");
        
        for (int i = 0; i < container.size(); i++) {
            System.out.println("Item " + i + ": " + container.get(i));
        }
        
        System.out.println("\n=== Wildcards ===");
        List<Integer> intList = Arrays.asList(1, 2, 3, 4, 5);
        List<String> stringList = Arrays.asList("a", "b", "c");
        List<Double> doubleList = Arrays.asList(1.1, 2.2, 3.3);
        
        WildcardExamples.printList(intList);
        WildcardExamples.printList(stringList);
        
        System.out.println("Sum of numbers: " + WildcardExamples.sumNumbers(intList));
        System.out.println("Sum of doubles: " + WildcardExamples.sumNumbers(doubleList));
        
        List<Number> numberList = new ArrayList<>();
        WildcardExamples.addIntegers(numberList);
        System.out.println("Added integers: " + numberList);
        
        System.out.println("\n=== Type Erasure ===");
        System.out.println("At runtime, generic types are erased.");
        System.out.println("Box<String> and Box<Integer> both become Box<Object>");
        System.out.println("This is why you cannot do: if (obj instanceof Box<String>)");
    }
}

