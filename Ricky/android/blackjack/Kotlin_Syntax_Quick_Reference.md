# Kotlin Syntax Quick Reference
## Essential Kotlin Concepts for Android Development

### Variables and Data Types
```kotlin
// Immutable (read-only) variables
val name = "John"                    // String
val age = 25                         // Int
val isStudent = true                 // Boolean
val height = 5.9                     // Double

// Mutable variables
var count = 0                        // Can be changed
var message: String? = null          // Nullable String

// Late initialization (common in Android)
private lateinit var binding: FragmentHomeBinding
```

### Functions
```kotlin
// Simple function
fun greet(name: String): String {
    return "Hello, $name!"
}

// Single expression function
fun add(a: Int, b: Int) = a + b

// Function with default parameters
fun createUser(name: String, age: Int = 18) {
    // age defaults to 18 if not provided
}

// Extension function
fun String.isEmail(): Boolean {
    return this.contains("@")
}
```

### Classes and Objects
```kotlin
// Data class (automatically generates equals, hashCode, toString)
data class Person(
    val name: String,
    val age: Int
)

// Regular class
class Calculator {
    fun add(a: Int, b: Int): Int {
        return a + b
    }
}

// Object (singleton)
object AppConfig {
    const val API_URL = "https://api.example.com"
}
```

### Null Safety
```kotlin
// Nullable types
var name: String? = null

// Safe call operator
val length = name?.length  // Returns null if name is null

// Elvis operator (default value)
val length = name?.length ?: 0  // Returns 0 if name is null

// Not-null assertion (use carefully!)
val length = name!!.length  // Throws exception if name is null

// Safe cast
val number = value as? Int  // Returns null if cast fails
```

### Collections
```kotlin
// Lists
val numbers = listOf(1, 2, 3, 4, 5)
val mutableNumbers = mutableListOf(1, 2, 3)

// Maps
val ages = mapOf("John" to 25, "Jane" to 30)
val mutableAges = mutableMapOf("John" to 25)

// Sets
val uniqueNumbers = setOf(1, 2, 3, 3, 4)  // Result: [1, 2, 3, 4]
```

### Control Flow
```kotlin
// If expression
val max = if (a > b) a else b

// When expression (like switch)
when (day) {
    1 -> "Monday"
    2 -> "Tuesday"
    in 3..5 -> "Midweek"
    else -> "Weekend"
}

// For loops
for (i in 1..10) { }           // Range
for (item in list) { }         // Collection
for ((key, value) in map) { }  // Map entries
```

### Lambda Expressions
```kotlin
// Lambda syntax
val numbers = listOf(1, 2, 3, 4, 5)
val doubled = numbers.map { it * 2 }  // [2, 4, 6, 8, 10]
val evens = numbers.filter { it % 2 == 0 }  // [2, 4]

// Higher-order functions
fun processNumbers(numbers: List<Int>, processor: (Int) -> Int): List<Int> {
    return numbers.map(processor)
}

// Usage
val result = processNumbers(listOf(1, 2, 3)) { it * 2 }
```

### Coroutines (Async Programming)
```kotlin
// Suspend function
suspend fun fetchData(): String {
    delay(1000)  // Non-blocking delay
    return "Data loaded"
}

// Launch coroutine
lifecycleScope.launch {
    val data = fetchData()
    updateUI(data)
}

// Flow (reactive streams)
fun getNumbers(): Flow<Int> = flow {
    repeat(5) {
        emit(it)
        delay(1000)
    }
}

// Collect from Flow
lifecycleScope.launch {
    getNumbers().collect { number ->
        println(number)
    }
}
```

### Common Android Patterns
```kotlin
// ViewBinding
private var _binding: FragmentHomeBinding? = null
private val binding get() = _binding!!

override fun onCreateView(inflater: LayoutInflater, container: ViewGroup?, savedInstanceState: Bundle?): View {
    _binding = FragmentHomeBinding.inflate(inflater, container, false)
    return binding.root
}

override fun onDestroyView() {
    super.onDestroyView()
    _binding = null
}

// StateFlow in ViewModel
class MyViewModel : ViewModel() {
    private val _uiState = MutableStateFlow(UiState())
    val uiState: StateFlow<UiState> = _uiState.asStateFlow()
    
    fun updateState(newState: UiState) {
        _uiState.value = newState
    }
}

// Observing StateFlow in Fragment
viewLifecycleOwner.lifecycleScope.launch {
    repeatOnLifecycle(Lifecycle.State.STARTED) {
        viewModel.uiState.collect { state ->
            updateUI(state)
        }
    }
}
```

### String Templates
```kotlin
val name = "John"
val age = 25

// String interpolation
val message = "Hello, $name! You are $age years old."
val calculation = "The result is ${a + b}"

// Multi-line strings
val html = """
    <html>
        <body>
            <h1>Hello, $name!</h1>
        </body>
    </html>
""".trimIndent()
```

### Scope Functions
```kotlin
val person = Person("John", 25)

// let - execute block and return result
val result = person.let { it.age * 2 }

// apply - execute block and return object
person.apply {
    age = 26
    name = "Johnny"
}

// with - execute block with object as receiver
with(person) {
    println("Name: $name, Age: $age")
}

// run - execute block and return result
val fullInfo = person.run {
    "$name is $age years old"
}
```

### Exception Handling
```kotlin
// Try-catch
try {
    val result = riskyOperation()
} catch (e: Exception) {
    println("Error: ${e.message}")
} finally {
    println("Cleanup")
}

// Try as expression
val result = try {
    riskyOperation()
} catch (e: Exception) {
    defaultValue
}
```

This quick reference covers the most important Kotlin concepts you'll encounter in Android development. Practice these patterns and you'll be well on your way to becoming proficient in Kotlin!
