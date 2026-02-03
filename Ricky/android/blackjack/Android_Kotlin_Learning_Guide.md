# Android App Development with Kotlin - Learning Guide
## Using the Blackjack Game as a Practical Example

### Table of Contents
1. [Introduction to Android Development](#introduction)
2. [Kotlin Basics for Android](#kotlin-basics)
3. [Android Project Structure](#project-structure)
4. [Understanding the Blackjack App Architecture](#architecture)
5. [Step-by-Step Code Walkthrough](#code-walkthrough)
6. [Key Android Concepts Explained](#android-concepts)
7. [Hands-On Exercises](#exercises)
8. [Common Patterns and Best Practices](#best-practices)
9. [Debugging and Testing](#debugging)
10. [Next Steps](#next-steps)

---

## 1. Introduction to Android Development {#introduction}

### What is Android Development?
Android development is the process of creating applications for Android devices using the Android SDK (Software Development Kit). Our Blackjack app is a perfect example because it demonstrates many core Android concepts in a practical, engaging way.

### Why This Blackjack App?
- **Real-world application**: A complete, functional game
- **Multiple screens**: Game, Statistics, Help
- **User interaction**: Buttons, navigation, data persistence
- **Modern Android patterns**: MVVM architecture, ViewBinding, Navigation Component
- **Visual elements**: Custom layouts, images, animations

### Prerequisites
- Basic programming knowledge (any language)
- Understanding of object-oriented programming concepts
- Android Studio installed
- Android device or emulator

---

## 2. Kotlin Basics for Android {#kotlin-basics}

### What is Kotlin?
Kotlin is a modern programming language that runs on the Java Virtual Machine (JVM). Google officially supports Kotlin for Android development, and it's now the preferred language for Android apps.

### Key Kotlin Concepts Used in Our App

#### 2.1 Variables and Data Types
```kotlin
// In HomeFragment.kt
private lateinit var gameViewModel: GameViewModel  // Late initialization
private var currentBet = 100                        // Mutable variable
val cards = hand.cards                              // Immutable reference
```

**Explanation:**
- `lateinit var`: Declares a variable that will be initialized later (common in Android)
- `var`: Mutable variable (can be changed)
- `val`: Immutable variable (cannot be changed after initialization)

#### 2.2 Data Classes
```kotlin
// In Card.kt
data class Card(
    val suit: Suit,
    val rank: Rank
) {
    fun getValue(): Int = when (rank) {
        Rank.ACE -> 11
        Rank.JACK, Rank.QUEEN, Rank.KING -> 10
        else -> rank.value
    }
}
```

**Explanation:**
- `data class`: Automatically generates useful methods (equals, hashCode, toString)
- `when` expression: Similar to switch statements in other languages
- Functions can be defined inside classes

#### 2.3 Enums
```kotlin
// In Card.kt
enum class Suit {
    CLUBS, DIAMONDS, HEARTS, SPADES
}

enum class Rank(val value: Int) {
    ACE(1),
    TWO(2), THREE(3), FOUR(4), FIVE(5), SIX(6), SEVEN(7), EIGHT(8), NINE(9), TEN(10),
    JACK(11), QUEEN(12), KING(13)
}
```

**Explanation:**
- `enum class`: Defines a set of constants
- Can have properties and methods
- Type-safe way to represent fixed values

#### 2.4 Null Safety
```kotlin
// In HomeFragment.kt
private var _binding: FragmentHomeBinding? = null
private val binding get() = _binding!!

// Safe call
binding?.dealerCard1?.visibility = View.VISIBLE
```

**Explanation:**
- `?`: Nullable type
- `!!`: Not-null assertion (use carefully)
- `?.`: Safe call operator (only calls if not null)

#### 2.5 Lambda Expressions and Higher-Order Functions
```kotlin
// In HomeFragment.kt
cards.forEachIndexed { index, card ->
    if (index < cardViews.size) {
        cardViews[index].visibility = View.VISIBLE
        setCardImage(cardViews[index], card)
    }
}
```

**Explanation:**
- `forEachIndexed`: Higher-order function that takes a lambda
- `{ index, card -> ... }`: Lambda expression
- Concise way to iterate with both index and element

---

## 3. Android Project Structure {#project-structure}

### Understanding the Project Layout
```
app/
├── src/main/
│   ├── java/ca/medontime/blackjack/     # Kotlin source code
│   │   ├── MainActivity.kt              # Main activity
│   │   ├── ui/                          # User interface code
│   │   │   ├── home/                    # Game screen
│   │   │   ├── dashboard/               # Statistics screen
│   │   │   └── notifications/           # Help screen
│   │   ├── domain/model/                # Data models
│   │   ├── data/                        # Data layer
│   │   └── di/                          # Dependency injection
│   ├── res/                             # Resources
│   │   ├── layout/                      # XML layout files
│   │   ├── drawable/                    # Images and shapes
│   │   ├── values/                      # Strings, colors, styles
│   │   ├── navigation/                  # Navigation graphs
│   │   └── menu/                        # Menu definitions
│   └── AndroidManifest.xml              # App configuration
├── build.gradle.kts                     # Build configuration
└── proguard-rules.pro                   # Code obfuscation rules
```

### Key Files Explained

#### 3.1 AndroidManifest.xml
```xml
<manifest xmlns:android="http://schemas.android.com/apk/res/android">
    <application
        android:allowBackup="true"
        android:icon="@mipmap/ic_launcher"
        android:label="@string/app_name"
        android:theme="@style/Theme.BlackJack">
        <activity
            android:name=".MainActivity"
            android:exported="true">
            <intent-filter>
                <action android:name="android.intent.action.MAIN" />
                <category android:name="android.intent.category.LAUNCHER" />
            </intent-filter>
        </activity>
    </application>
</manifest>
```

**What this does:**
- Declares the app's main activity (entry point)
- Sets app icon, name, and theme
- Defines permissions and features

#### 3.2 build.gradle.kts
```kotlin
android {
    namespace = "ca.medontime.blackjack"
    compileSdk = 36
    
    defaultConfig {
        applicationId = "ca.medontime.blackjack"
        minSdk = 24
        targetSdk = 36
        versionCode = 1
        versionName = "1.0"
    }
    
    buildFeatures {
        viewBinding = true  // Enables ViewBinding
    }
}

dependencies {
    implementation(libs.androidx.core.ktx)
    implementation(libs.androidx.appcompat)
    implementation(libs.material)
    // ... more dependencies
}
```

**What this does:**
- Configures Android build settings
- Defines minimum and target Android versions
- Lists external libraries (dependencies)
- Enables features like ViewBinding

---

## 4. Understanding the Blackjack App Architecture {#architecture}

### MVVM Architecture Pattern
Our app follows the **Model-View-ViewModel (MVVM)** pattern:

```
┌─────────────┐    ┌──────────────┐    ┌─────────────┐
│    View     │◄──►│  ViewModel   │◄──►│    Model    │
│ (Fragment)  │    │              │    │ (Data/Logic) │
└─────────────┘    └──────────────┘    └─────────────┘
```

### Components in Our App

#### 4.1 Model Layer
- **Card.kt**: Represents a playing card
- **Hand.kt**: Represents a collection of cards
- **Game.kt**: Represents the game state
- **GameStatistics.kt**: Represents player statistics

#### 4.2 View Layer
- **HomeFragment.kt**: Game screen UI
- **DashboardFragment.kt**: Statistics screen UI
- **NotificationsFragment.kt**: Help screen UI
- **Layout files**: XML files defining UI structure

#### 4.3 ViewModel Layer
- **GameViewModel.kt**: Manages game logic and state
- **StatisticsViewModel.kt**: Manages statistics data

### Data Flow Example
1. User clicks "Hit" button in HomeFragment
2. HomeFragment calls GameViewModel.playerHit()
3. GameViewModel updates game state
4. HomeFragment observes the change and updates UI

---

## 5. Step-by-Step Code Walkthrough {#code-walkthrough}

### 5.1 MainActivity - The App Entry Point

```kotlin
class MainActivity : AppCompatActivity() {
    private lateinit var binding: ActivityMainBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        
        // Inflate the layout using ViewBinding
        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)
        
        // Set up bottom navigation
        val navView: BottomNavigationView = binding.navView
        val navController = findNavController(R.id.nav_host_fragment_activity_main)
        navView.setupWithNavController(navController)
    }
}
```

**Key Concepts:**
- `AppCompatActivity`: Base class for activities with modern Android features
- `onCreate()`: Called when activity is created
- `ViewBinding`: Safe way to access views (replaces findViewById)
- `BottomNavigationView`: Material Design navigation component

### 5.2 Card Model - Data Representation

```kotlin
data class Card(
    val suit: Suit,
    val rank: Rank
) {
    fun getValue(): Int = when (rank) {
        Rank.ACE -> 11
        Rank.JACK, Rank.QUEEN, Rank.KING -> 10
        else -> rank.value
    }
    
    fun getImageResourceName(): String {
        val rankName = when (rank) {
            Rank.ACE -> "a"
            Rank.JACK -> "j"
            Rank.QUEEN -> "q"
            Rank.KING -> "k"
            else -> rank.value.toString()
        }
        val suitName = suit.name.lowercase()
        return "card_${rankName}_of_${suitName}"
    }
}
```

**Key Concepts:**
- `data class`: Immutable data container
- `when` expression: Pattern matching
- String interpolation: `"card_${rankName}_of_${suitName}"`
- Function overloading: Multiple functions with same name

### 5.3 GameViewModel - Business Logic

```kotlin
class GameViewModel(
    private val gameUseCase: BlackJackGameUseCase,
    private val statisticsRepository: GameStatisticsRepository
) : ViewModel() {
    
    private val _gameState = MutableStateFlow(Game())
    val gameState: StateFlow<Game> = _gameState.asStateFlow()
    
    private val _gameMessage = MutableStateFlow("Place your bet and click Deal to start")
    val gameMessage: StateFlow<String> = _gameMessage.asStateFlow()
    
    fun playerHit() {
        val currentGame = _gameState.value
        if (currentGame.isPlayerTurn()) {
            val updatedGame = gameUseCase.playerHit(currentGame)
            _gameState.value = updatedGame
            
            if (updatedGame.isFinished()) {
                finishGame(updatedGame)
            }
        }
    }
}
```

**Key Concepts:**
- `ViewModel`: Survives configuration changes
- `StateFlow`: Reactive data stream
- `MutableStateFlow`: Mutable version of StateFlow
- Dependency injection: Dependencies passed in constructor

### 5.4 HomeFragment - User Interface

```kotlin
class HomeFragment : Fragment() {
    private var _binding: FragmentHomeBinding? = null
    private val binding get() = _binding!!
    
    private lateinit var gameViewModel: GameViewModel
    private lateinit var dealerCard1: ImageView
    private lateinit var playerCard1: ImageView
    // ... more UI components
    
    override fun onCreateView(
        inflater: LayoutInflater,
        container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View {
        _binding = FragmentHomeBinding.inflate(inflater, container, false)
        val root: View = binding.root
        
        initializeViews()
        setupViewModel()
        setupClickListeners()
        observeGameState()
        
        return root
    }
    
    private fun setupClickListeners() {
        binding.hitButton.setOnClickListener {
            gameViewModel.playerHit()
        }
        
        binding.standButton.setOnClickListener {
            gameViewModel.playerStand()
        }
        
        binding.dealButton.setOnClickListener {
            gameViewModel.deal()
        }
    }
    
    private fun observeGameState() {
        viewLifecycleOwner.lifecycleScope.launch {
            repeatOnLifecycle(Lifecycle.State.STARTED) {
                gameViewModel.gameState.collect { game ->
                    updateUI(game)
                }
            }
        }
    }
}
```

**Key Concepts:**
- `Fragment`: Reusable UI component
- `ViewBinding`: Type-safe view access
- `lifecycleScope`: Coroutine scope tied to fragment lifecycle
- `repeatOnLifecycle`: Ensures coroutines respect lifecycle
- `collect`: Subscribes to StateFlow updates

### 5.5 Layout File - UI Definition

```xml
<!-- fragment_home.xml -->
<androidx.constraintlayout.widget.ConstraintLayout
    xmlns:android="http://schemas.android.com/apk/res/android"
    xmlns:app="http://schemas.android.com/apk/res-auto"
    android:layout_width="match_parent"
    android:layout_height="match_parent"
    android:background="#1B5E20">

    <ScrollView
        android:id="@+id/scroll_view"
        android:layout_width="match_parent"
        android:layout_height="0dp"
        app:layout_constraintTop_toTopOf="parent"
        app:layout_constraintBottom_toTopOf="@id/game_controls">

        <LinearLayout
            android:layout_width="match_parent"
            android:layout_height="wrap_content"
            android:orientation="vertical"
            android:padding="16dp">

            <!-- Dealer's Hand -->
            <LinearLayout
                android:id="@+id/dealer_section"
                android:layout_width="match_parent"
                android:layout_height="wrap_content"
                android:orientation="vertical"
                android:padding="16dp">

                <TextView
                    android:layout_width="wrap_content"
                    android:layout_height="wrap_content"
                    android:text="Dealer's Hand"
                    android:textColor="#BDBDBD"
                    android:textSize="16sp" />

                <LinearLayout
                    android:layout_width="wrap_content"
                    android:layout_height="wrap_content"
                    android:orientation="horizontal">

                    <ImageView
                        android:id="@+id/dealer_card_1"
                        android:layout_width="96dp"
                        android:layout_height="134dp"
                        android:layout_marginEnd="-20dp"
                        android:visibility="invisible"
                        android:scaleType="centerCrop" />

                    <!-- More cards... -->
                </LinearLayout>
            </LinearLayout>
        </LinearLayout>
    </ScrollView>
</androidx.constraintlayout.widget.ConstraintLayout>
```

**Key Concepts:**
- `ConstraintLayout`: Flexible layout system
- `ScrollView`: Makes content scrollable
- `LinearLayout`: Arranges views in a line
- `ImageView`: Displays images
- `android:id`: Unique identifier for views
- `app:layout_constraint*`: ConstraintLayout attributes

---

## 6. Key Android Concepts Explained {#android-concepts}

### 6.1 Activities vs Fragments

**Activity:**
- Represents a single screen with a user interface
- Has a lifecycle (created, started, resumed, paused, stopped, destroyed)
- Example: MainActivity hosts our entire app

**Fragment:**
- Reusable piece of UI
- Can be added/removed from activities
- Has its own lifecycle
- Example: HomeFragment, DashboardFragment, NotificationsFragment

### 6.2 ViewBinding vs findViewById

**Old way (findViewById):**
```kotlin
val button = findViewById<Button>(R.id.my_button)
button.setOnClickListener { /* ... */ }
```

**New way (ViewBinding):**
```kotlin
binding.myButton.setOnClickListener { /* ... */ }
```

**Benefits of ViewBinding:**
- Type safety (no ClassCastException)
- Null safety
- Better performance
- Easier refactoring

### 6.3 Lifecycle Awareness

```kotlin
viewLifecycleOwner.lifecycleScope.launch {
    repeatOnLifecycle(Lifecycle.State.STARTED) {
        gameViewModel.gameState.collect { game ->
            updateUI(game)
        }
    }
}
```

**Why this matters:**
- Prevents memory leaks
- Ensures UI updates only when fragment is visible
- Automatically cancels coroutines when fragment is destroyed

### 6.4 StateFlow vs LiveData

**StateFlow (used in our app):**
```kotlin
private val _gameState = MutableStateFlow(Game())
val gameState: StateFlow<Game> = _gameState.asStateFlow()
```

**Benefits:**
- Part of Kotlin Coroutines
- Better integration with coroutines
- More modern and recommended

### 6.5 Navigation Component

```xml
<!-- mobile_navigation.xml -->
<navigation xmlns:android="http://schemas.android.com/apk/res/android"
    android:id="@+id/mobile_navigation"
    app:startDestination="@+id/navigation_home">

    <fragment
        android:id="@+id/navigation_home"
        android:name="ca.medontime.blackjack.ui.home.HomeFragment"
        android:label="@string/title_home" />

    <fragment
        android:id="@+id/navigation_dashboard"
        android:name="ca.medontime.blackjack.ui.dashboard.DashboardFragment"
        android:label="@string/title_dashboard" />
</navigation>
```

**Benefits:**
- Type-safe navigation
- Visual navigation graph
- Handles back stack automatically
- Deep linking support

---

## 7. Hands-On Exercises {#exercises}

### Exercise 1: Understanding the Card System
**Goal:** Understand how cards are represented and displayed

1. Open `Card.kt` and examine the `Card` data class
2. Look at the `getImageResourceName()` function
3. Check the `drawable` folder to see the card images
4. Trace how a card goes from data to displayed image

**Questions to answer:**
- How does the app know which image to show for each card?
- What happens if a card image is missing?
- How are card values calculated?

### Exercise 2: Following the Hit Button Flow
**Goal:** Understand user interaction flow

1. Find the Hit button in `fragment_home.xml`
2. Find the click listener in `HomeFragment.kt`
3. Trace the call to `GameViewModel.playerHit()`
4. See how the UI updates when the game state changes

**Questions to answer:**
- What happens when you click Hit?
- How does the app know to show a new card?
- What prevents invalid actions (like hitting when busted)?

### Exercise 3: Understanding Statistics
**Goal:** Learn about data persistence and filtering

1. Open `StatisticsViewModel.kt`
2. Look at the `updateTimePeriod()` function
3. See how statistics are filtered for different time periods
4. Check how the UI updates when filters change

**Questions to answer:**
- How are statistics stored?
- How does filtering work?
- Why do the numbers change when you switch time periods?

### Exercise 4: Layout Analysis
**Goal:** Understand Android layouts

1. Open `fragment_home.xml`
2. Identify different layout types used
3. Understand how views are positioned
4. See how the layout responds to different screen sizes

**Questions to answer:**
- Why use ConstraintLayout vs LinearLayout?
- How do the cards overlap?
- What makes the layout scrollable?

---

## 8. Common Patterns and Best Practices {#best-practices}

### 8.1 MVVM Pattern Benefits
- **Separation of concerns**: UI logic separate from business logic
- **Testability**: ViewModels can be tested independently
- **Lifecycle awareness**: Survives configuration changes
- **Reactive programming**: UI automatically updates when data changes

### 8.2 Dependency Injection
```kotlin
// In AppModule.kt
object AppModule {
    fun getGameUseCase(): BlackJackGameUseCase {
        return BlackJackGameUseCase()
    }
    
    fun getStatisticsRepository(context: Context): GameStatisticsRepository {
        return GameStatisticsRepositoryImpl(
            GameStatisticsDataSource(context)
        )
    }
}
```

**Benefits:**
- Easier testing (can inject mock objects)
- Loose coupling between components
- Centralized object creation

### 8.3 Error Handling
```kotlin
private fun getCardResourceId(resourceName: String): Int {
    val resourceId = resources.getIdentifier(resourceName, "drawable", requireContext().packageName)
    if (resourceId == 0) {
        // Fallback to cover if resource not found
        return R.drawable.cover
    }
    return resourceId
}
```

**Best practices:**
- Always handle potential errors
- Provide fallback behavior
- Log errors for debugging
- Don't crash the app

### 8.4 Resource Management
- Use string resources instead of hardcoded strings
- Define colors in `colors.xml`
- Use drawable resources for images
- Support different screen densities

---

## 9. Debugging and Testing {#debugging}

### 9.1 Using Logcat
```kotlin
android.util.Log.d("CardDisplay", "Card: ${card.rank} of ${card.suit}")
```

**Log levels:**
- `Log.v()`: Verbose (most detailed)
- `Log.d()`: Debug
- `Log.i()`: Info
- `Log.w()`: Warning
- `Log.e()`: Error

### 9.2 Common Debugging Techniques
1. **Breakpoints**: Pause execution to inspect variables
2. **Logging**: Print values to see what's happening
3. **Step through code**: Execute line by line
4. **Inspect variables**: See current values
5. **Evaluate expressions**: Test code snippets

### 9.3 Testing Strategy
```kotlin
// Example unit test
@Test
fun testCardValue() {
    val aceCard = Card(Suit.HEARTS, Rank.ACE)
    assertEquals(11, aceCard.getValue())
    
    val kingCard = Card(Suit.SPADES, Rank.KING)
    assertEquals(10, kingCard.getValue())
}
```

**Types of tests:**
- **Unit tests**: Test individual functions/classes
- **Integration tests**: Test component interactions
- **UI tests**: Test user interface behavior

---

## 10. Next Steps {#next-steps}

### 10.1 Immediate Learning Goals
1. **Run the app**: Get it running on your device/emulator
2. **Modify the UI**: Change colors, text, or layout
3. **Add a new button**: Create a new feature
4. **Understand the flow**: Trace through the code execution

### 10.2 Intermediate Goals
1. **Add sound effects**: Play sounds for card dealing
2. **Implement animations**: Animate card dealing
3. **Add more statistics**: Track additional metrics
4. **Improve UI**: Add more visual polish

### 10.3 Advanced Goals
1. **Add multiplayer**: Support multiple players
2. **Implement betting**: Add chip system
3. **Add achievements**: Reward system
4. **Optimize performance**: Improve app speed

### 10.4 Recommended Resources
- **Official Android Documentation**: developer.android.com
- **Kotlin Documentation**: kotlinlang.org
- **Material Design Guidelines**: material.io
- **Android Developers YouTube**: Official Google channel
- **Kotlin Koans**: Interactive Kotlin learning

### 10.5 Practice Projects
1. **Calculator app**: Practice UI and basic logic
2. **Todo list**: Learn data persistence
3. **Weather app**: Practice API integration
4. **Chat app**: Learn networking and real-time updates

---

## Conclusion

This Blackjack app demonstrates many essential Android development concepts:
- **Kotlin language features** (data classes, lambdas, null safety)
- **Android architecture** (MVVM, fragments, activities)
- **UI development** (layouts, ViewBinding, Material Design)
- **Data management** (StateFlow, persistence, filtering)
- **Navigation** (Navigation Component, bottom navigation)
- **Best practices** (lifecycle awareness, error handling, testing)

By studying this codebase and following this guide, you'll gain a solid foundation in Android development with Kotlin. Remember to experiment, break things, and rebuild them - that's how you learn!

Happy coding! 🎯📱
