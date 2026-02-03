# Android Development Exercises
## Hands-On Learning with the Blackjack App

### Exercise 1: Understanding the Card System
**Difficulty:** Beginner  
**Time:** 30 minutes  
**Goal:** Understand how cards are represented and displayed

#### Step 1: Examine the Card Model
1. Open `app/src/main/java/ca/medontime/blackjack/domain/model/Card.kt`
2. Read through the `Card` data class
3. Understand the `Suit` and `Rank` enums

#### Questions to Answer:
- What properties does a `Card` have?
- How does `getValue()` calculate card values?
- What does `getImageResourceName()` return?

#### Step 2: Check the Card Images
1. Open `app/src/main/res/drawable/` folder
2. Look at the card image files
3. Notice the naming pattern: `card_a_of_clubs`, `card_7_of_hearts`, etc.

#### Step 3: Trace Card Display
1. In `HomeFragment.kt`, find the `setCardImage()` function
2. Follow how a card goes from data to displayed image
3. Understand the `getCardResourceId()` function

#### Challenge:
- What happens if a card image is missing?
- How could you add a new suit (like "Stars")?

---

### Exercise 2: Following the Hit Button Flow
**Difficulty:** Beginner  
**Time:** 45 minutes  
**Goal:** Understand user interaction flow

#### Step 1: Find the Hit Button
1. Open `app/src/main/res/layout/fragment_home.xml`
2. Find the Hit button definition
3. Notice its ID: `android:id="@+id/hit_button"`

#### Step 2: Find the Click Listener
1. Open `HomeFragment.kt`
2. Find `setupClickListeners()` function
3. Look at the Hit button click listener

#### Step 3: Trace the Flow
1. Follow the call to `gameViewModel.playerHit()`
2. Open `GameViewModel.kt` and find `playerHit()` function
3. See how it calls `gameUseCase.playerHit()`

#### Step 4: Understand UI Updates
1. In `HomeFragment.kt`, find `observeGameState()`
2. See how the UI updates when game state changes
3. Look at `updateUI()` function

#### Questions to Answer:
- What happens when you click Hit?
- How does the app know to show a new card?
- What prevents invalid actions (like hitting when busted)?

#### Challenge:
- Add a "Double Down" button that doubles the bet and hits once
- Add sound effects when cards are dealt

---

### Exercise 3: Understanding Statistics
**Difficulty:** Intermediate  
**Time:** 60 minutes  
**Goal:** Learn about data persistence and filtering

#### Step 1: Examine Statistics Model
1. Open `GameStatistics.kt`
2. Understand what data is tracked
3. Look at the calculation methods

#### Step 2: Check Data Persistence
1. Open `GameStatisticsDataSource.kt`
2. See how statistics are saved/loaded
3. Understand DataStore usage

#### Step 3: Understand Filtering
1. Open `StatisticsViewModel.kt`
2. Look at `updateTimePeriod()` function
3. See how statistics are filtered for different time periods

#### Step 4: UI Updates
1. Open `DashboardFragment.kt`
2. Find `updateTimePeriodButtons()` function
3. See how button colors change

#### Questions to Answer:
- How are statistics stored?
- How does filtering work?
- Why do the numbers change when you switch time periods?

#### Challenge:
- Add a "Reset Statistics" confirmation dialog
- Add more statistics (average bet, longest winning streak)

---

### Exercise 4: Layout Analysis
**Difficulty:** Beginner  
**Time:** 45 minutes  
**Goal:** Understand Android layouts

#### Step 1: Examine Main Layout
1. Open `fragment_home.xml`
2. Identify the root layout (ConstraintLayout)
3. Understand the overall structure

#### Step 2: Understand Card Layout
1. Find the dealer and player card sections
2. See how cards are arranged horizontally
3. Notice the overlap with `android:layout_marginEnd="-20dp"`

#### Step 3: ScrollView Usage
1. Find the ScrollView
2. Understand why it's needed
3. See how it's constrained

#### Step 4: Button Layout
1. Find the game controls section
2. See how buttons are arranged
3. Understand the bottom margin for navigation

#### Questions to Answer:
- Why use ConstraintLayout vs LinearLayout?
- How do the cards overlap?
- What makes the layout scrollable?

#### Challenge:
- Add a "New Game" button
- Change the card overlap amount
- Add animations when cards are dealt

---

### Exercise 5: Adding a New Feature
**Difficulty:** Intermediate  
**Time:** 90 minutes  
**Goal:** Practice adding features to an existing app

#### Feature: Add Card Counting Display
Show the current count of cards remaining in the deck.

#### Step 1: Update the Game Model
1. Add a `cardsRemaining` property to the `Game` class
2. Update the `BlackJackGameUseCase` to track remaining cards

#### Step 2: Update the UI
1. Add a TextView to `fragment_home.xml` to display the count
2. Update `HomeFragment.kt` to show the count
3. Make sure it updates when cards are dealt

#### Step 3: Add Logic
1. Calculate remaining cards in the use case
2. Update the count when cards are dealt
3. Handle deck reshuffling when needed

#### Challenge Extensions:
- Add a "Shuffle" button
- Show card counting statistics
- Add deck visualization

---

### Exercise 6: Understanding Navigation
**Difficulty:** Beginner  
**Time:** 30 minutes  
**Goal:** Learn Android navigation

#### Step 1: Examine Navigation Graph
1. Open `app/src/main/res/navigation/mobile_navigation.xml`
2. See how fragments are connected
3. Understand the navigation structure

#### Step 2: Check Bottom Navigation
1. Open `app/src/main/res/menu/bottom_nav_menu.xml`
2. See the menu items
3. Understand how they map to fragments

#### Step 3: MainActivity Setup
1. Open `MainActivity.kt`
2. See how navigation is configured
3. Understand the AppBarConfiguration

#### Questions to Answer:
- How does navigation between screens work?
- What happens when you tap a bottom navigation item?
- How could you add a new screen?

#### Challenge:
- Add a "Settings" screen
- Add navigation between game and settings
- Implement back button handling

---

### Exercise 7: Error Handling
**Difficulty:** Intermediate  
**Time:** 60 minutes  
**Goal:** Learn proper error handling

#### Step 1: Find Error Handling Examples
1. Look at `getCardResourceId()` in `HomeFragment.kt`
2. See how it handles missing resources
3. Understand the fallback mechanism

#### Step 2: Add Error Handling
1. Add try-catch blocks around risky operations
2. Provide user-friendly error messages
3. Log errors for debugging

#### Step 3: Test Error Scenarios
1. Remove a card image file
2. See how the app handles it
3. Test with invalid data

#### Questions to Answer:
- What happens when an error occurs?
- How can you prevent crashes?
- What information should you log?

#### Challenge:
- Add network error handling
- Implement retry mechanisms
- Add error reporting

---

### Exercise 8: Performance Optimization
**Difficulty:** Advanced  
**Time:** 120 minutes  
**Goal:** Learn performance best practices

#### Step 1: Identify Performance Issues
1. Look for memory leaks
2. Check for inefficient operations
3. Find unnecessary UI updates

#### Step 2: Optimize Image Loading
1. Implement image caching
2. Use appropriate image sizes
3. Lazy load images

#### Step 3: Optimize Data Operations
1. Use background threads for heavy operations
2. Implement data caching
3. Minimize database operations

#### Questions to Answer:
- What causes performance issues?
- How can you measure performance?
- What are common optimization techniques?

#### Challenge:
- Add performance monitoring
- Implement lazy loading
- Optimize memory usage

---

### Exercise 9: Testing
**Difficulty:** Intermediate  
**Time:** 90 minutes  
**Goal:** Learn Android testing

#### Step 1: Write Unit Tests
1. Test the `Card` class methods
2. Test the `Hand` class calculations
3. Test the game logic

#### Step 2: Write Integration Tests
1. Test ViewModel functionality
2. Test data persistence
3. Test navigation

#### Step 3: Write UI Tests
1. Test button clicks
2. Test navigation
3. Test error scenarios

#### Questions to Answer:
- What should you test?
- How do you test UI components?
- What's the difference between unit and integration tests?

#### Challenge:
- Add test coverage reporting
- Implement automated testing
- Add performance tests

---

### Exercise 10: Customization Project
**Difficulty:** Advanced  
**Time:** 180 minutes  
**Goal:** Apply all learned concepts

#### Project: Create a Custom Card Game
Using the Blackjack app as a foundation, create a simple card game like "War" or "Go Fish".

#### Requirements:
1. **New Game Logic**: Implement different game rules
2. **Custom UI**: Modify the layout for the new game
3. **Statistics**: Track game-specific statistics
4. **Navigation**: Add the new game to navigation
5. **Testing**: Write tests for the new features

#### Deliverables:
1. Working custom card game
2. Updated UI and navigation
3. Game-specific statistics
4. Unit tests for game logic
5. Documentation of changes

#### Evaluation Criteria:
- Code quality and organization
- UI/UX design
- Functionality completeness
- Test coverage
- Documentation quality

---

## Learning Progression

### Beginner Level (Exercises 1-4)
- Understand basic Android concepts
- Learn Kotlin syntax
- Familiarize with project structure
- Practice reading and understanding code

### Intermediate Level (Exercises 5-7)
- Add new features
- Implement error handling
- Understand navigation
- Practice debugging

### Advanced Level (Exercises 8-10)
- Performance optimization
- Testing strategies
- Complete project development
- Best practices implementation

## Tips for Success

1. **Start Small**: Begin with simple modifications
2. **Read Documentation**: Use official Android docs
3. **Experiment**: Try breaking things and fixing them
4. **Ask Questions**: Don't hesitate to seek help
5. **Practice Regularly**: Consistent practice is key
6. **Build Projects**: Apply what you learn in real projects

## Resources

- **Official Android Documentation**: developer.android.com
- **Kotlin Documentation**: kotlinlang.org
- **Android Developers YouTube**: Official Google channel
- **Stack Overflow**: Community help
- **GitHub**: Open source examples

Remember: The best way to learn Android development is by building apps. Use these exercises as stepping stones to create your own projects!
