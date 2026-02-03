# Software Requirements Specification (SRS)
## BlackJack Android Game Application

### 1. Introduction

#### 1.1 Purpose
This document specifies the requirements for a BlackJack card game Android application. The application will provide users with an interactive single-player BlackJack experience using traditional Android XML layouts and Fragments instead of Jetpack Compose.

#### 1.2 Scope
The BlackJack Android app will be a mobile game application that allows users to play BlackJack against a computer dealer. The application will include game statistics tracking, settings management, and a user-friendly interface optimized for mobile devices.

#### 1.3 Definitions, Acronyms, and Abbreviations
- **BlackJack**: A card game where the objective is to get cards totaling as close to 21 as possible without exceeding it
- **Dealer**: The computer-controlled opponent in the game
- **Hand**: A collection of cards held by either the player or dealer
- **Hit**: Action to request another card
- **Stand**: Action to keep current hand without requesting more cards
- **Bust**: When a hand exceeds 21 points
- **SRS**: Software Requirements Specification

#### 1.4 References
- Project Purpose.md
- Android Development Guidelines
- Material Design Guidelines

### 2. Overall Description

#### 2.1 Product Perspective
The BlackJack Android app is a standalone mobile application that will be distributed through the Google Play Store. It operates independently and does not require internet connectivity for core gameplay.

#### 2.2 Product Functions
The application will provide the following main functions:
- Interactive BlackJack gameplay
- Game statistics tracking and display
- Settings management
- Card deck management and shuffling
- Score calculation and game result determination

#### 2.3 User Characteristics
- **Primary Users**: Mobile game enthusiasts, card game players
- **Technical Level**: Basic Android device operation knowledge
- **Age Range**: 18+ (due to gambling-related content)
- **Device Requirements**: Android 7.0 (API level 24) or higher

#### 2.4 Constraints
- Must use XML layouts and Fragments (not Jetpack Compose)
- Must work on Android devices with API level 24+
- Must use provided poker card images from "./Poker Cards" folder
- Must follow Material Design guidelines
- Must be optimized for portrait orientation

### 3. Specific Requirements

#### 3.1 Functional Requirements

##### 3.1.1 Game Management
- **FR-001**: The system shall initialize a standard 52-card deck at the start of each game
- **FR-002**: The system shall shuffle the deck before dealing cards
- **FR-003**: The system shall deal two cards to the player and two cards to the dealer (one dealer card face down)
- **FR-004**: The system shall calculate hand values according to BlackJack rules (Ace = 1 or 11, Face cards = 10)
- **FR-005**: The system shall determine game outcomes (Win, Loss, Push, BlackJack)
- **FR-006**: The system shall display bet amount (e.g., "$100") and winnings (e.g., "$25") prominently

##### 3.1.2 Player Actions
- **FR-007**: The system shall allow players to "Hit" (request another card)
- **FR-008**: The system shall allow players to "Stand" (keep current hand)
- **FR-009**: The system shall allow players to "Deal" (start new game)
- **FR-010**: The system shall prevent invalid actions (e.g., Hit when busted)
- **FR-011**: The system shall automatically end the game when player busts

##### 3.1.3 Dealer Logic
- **FR-012**: The system shall implement dealer rules (Hit on 16 or less, Stand on 17 or more)
- **FR-013**: The system shall reveal dealer's face-down card after player stands
- **FR-014**: The system shall automatically play dealer's turn according to standard rules

##### 3.1.4 Game Screen User Interface
- **FR-015**: The system shall display "Blackjack Table" title in the top-left corner
- **FR-016**: The system shall display "Blackjack" as the main screen title
- **FR-017**: The system shall provide a settings gear icon in the top-right corner
- **FR-018**: The system shall display dealer's cards in a horizontal layout with one face-down card
- **FR-019**: The system shall display player's cards in a horizontal layout, all face-up
- **FR-020**: The system shall show current hand values for both player and dealer
- **FR-021**: The system shall provide Hit, Stand, and Deal buttons with vibrant green styling
- **FR-022**: The system shall display game status messages (e.g., "You Win!", "Bust!", "BlackJack!")
- **FR-023**: The system shall use dark green background for the main game area
- **FR-024**: The system shall use light gray text for labels and information

##### 3.1.5 Statistics Tracking
- **FR-025**: The system shall track total games played
- **FR-026**: The system shall track games won
- **FR-027**: The system shall track games lost
- **FR-028**: The system shall track games pushed (tied)
- **FR-029**: The system shall track BlackJack occurrences
- **FR-030**: The system shall calculate and display win percentage
- **FR-031**: The system shall track highest score achieved
- **FR-032**: The system shall track average score
- **FR-033**: The system shall track current winning/losing streak

##### 3.1.6 Statistics Screen User Interface
- **FR-034**: The system shall display "Statistics" as the screen title
- **FR-035**: The system shall provide a back arrow navigation icon
- **FR-036**: The system shall display "Overall Record" in a large rounded card
- **FR-037**: The system shall show win/loss ratio with a horizontal progress bar
- **FR-038**: The system shall display win percentage in vibrant green text
- **FR-039**: The system shall show total wins and losses prominently
- **FR-040**: The system shall provide time period selector (All Time, Past Week, Past Month)
- **FR-041**: The system shall highlight the selected time period with vibrant green background
- **FR-042**: The system shall display individual statistics in a 2x2 grid of rounded cards
- **FR-043**: The system shall show "Highest Score" in vibrant green text
- **FR-044**: The system shall show "Current Streak" in vibrant green text for winning streaks

##### 3.1.7 Help Screen User Interface
- **FR-045**: The system shall display "Blackjack Help" as the screen title
- **FR-046**: The system shall provide a back arrow navigation icon
- **FR-047**: The system shall display "Rules of Blackjack" section with clear explanation
- **FR-048**: The system shall display "How to Play" section with numbered steps
- **FR-049**: The system shall explain card values (Number cards = face value, Face cards = 10, Ace = 1 or 11)
- **FR-050**: The system shall explain game flow (Hit/Stand, Bust, Dealer rules)
- **FR-051**: The system shall explain win conditions and push scenarios

##### 3.1.8 Navigation
- **FR-052**: The system shall provide bottom navigation with Game, Stats, and Help tabs
- **FR-053**: The system shall highlight the active tab with vibrant green background
- **FR-054**: The system shall use appropriate icons (dice for Game, bar chart for Stats, question mark for Help)
- **FR-055**: The system shall maintain navigation state during gameplay
- **FR-056**: The system shall allow switching between tabs without losing game state

##### 3.1.9 Settings
- **FR-057**: The system shall allow resetting game statistics
- **FR-058**: The system shall provide game rules information
- **FR-059**: The system shall allow adjusting game preferences (if applicable)

#### 3.2 Non-Functional Requirements

##### 3.2.1 Performance
- **NFR-001**: The application shall respond to user input within 100ms
- **NFR-002**: The application shall load within 3 seconds on average Android devices
- **NFR-003**: The application shall maintain smooth 60fps during card animations

##### 3.2.2 Usability
- **NFR-004**: The interface shall be intuitive for users familiar with BlackJack
- **NFR-005**: The application shall provide clear visual feedback for all actions
- **NFR-006**: The application shall support one-handed operation

##### 3.2.3 Reliability
- **NFR-007**: The application shall not crash during normal gameplay
- **NFR-008**: The application shall preserve game statistics across app restarts
- **NFR-009**: The application shall handle unexpected interruptions gracefully

##### 3.2.4 Compatibility
- **NFR-010**: The application shall run on Android 7.0 (API 24) and higher
- **NFR-011**: The application shall support various screen sizes (phone and tablet)
- **NFR-012**: The application shall work in both light and dark themes

##### 3.2.5 Security
- **NFR-013**: The application shall not collect or transmit personal data
- **NFR-014**: The application shall store data locally on the device only

### 4. System Features

#### 4.1 Game Screen
- **Description**: Main gameplay interface showing cards, scores, and controls
- **Input**: Touch interactions for Hit, Stand, New Game buttons
- **Output**: Visual display of cards, scores, and game status
- **Processing**: Card dealing, score calculation, game logic

#### 4.2 Statistics Screen
- **Description**: Display of game statistics and performance metrics
- **Input**: Navigation from other screens
- **Output**: Statistics display with charts/graphs
- **Processing**: Data aggregation and calculation

#### 4.3 Settings Screen
- **Description**: Configuration options and game information
- **Input**: User preferences and settings changes
- **Output**: Updated settings and confirmation messages
- **Processing**: Settings validation and persistence

### 5. External Interface Requirements

#### 5.1 User Interfaces

##### 5.1.1 Visual Design Theme
- **UI-001**: Dark theme with dark green (#1B5E20) background for main game area
- **UI-002**: Dark gray (#424242) background for top and bottom bars
- **UI-003**: Light gray (#BDBDBD) text for labels and secondary information
- **UI-004**: Vibrant green (#4CAF50) for interactive elements and highlights
- **UI-005**: White (#FFFFFF) text for primary content and titles
- **UI-006**: Subtle dotted pattern texture on screen edges
- **UI-007**: Rounded rectangular cards for information grouping

##### 5.1.2 Game Screen Layout
- **UI-008**: "Blackjack Table" title in top-left corner (light gray text)
- **UI-009**: "Blackjack" main title centered in header (white, bold text)
- **UI-010**: Settings gear icon in top-right corner (white)
- **UI-011**: Dealer's hand section with "Dealer's Hand" label (light gray)
- **UI-012**: Player's hand section with "Your Hand" label (light gray)
- **UI-013**: Cards displayed horizontally with slight overlap
- **UI-014**: Face-down card showing plain light beige back with rounded corners
- **UI-015**: Face-up cards showing detailed card designs (Ace of Spades, King of Hearts, 7 of Diamonds)
- **UI-016**: Bet and Winnings display side-by-side (light gray labels and values)
- **UI-017**: Hit and Stand buttons (vibrant green background, white text, rounded corners)
- **UI-018**: Deal button (darker green background, white text, wider than Hit/Stand)

##### 5.1.3 Statistics Screen Layout
- **UI-019**: "Statistics" title centered in header (white, bold text)
- **UI-020**: Back arrow icon in top-left corner (white)
- **UI-021**: "Overall Record" large rounded card (dark background)
- **UI-022**: Win/Loss progress bar (vibrant green for wins, dark for losses)
- **UI-023**: Win percentage display (vibrant green text, e.g., "66.7%")
- **UI-024**: Total wins and losses prominently displayed (large white numbers)
- **UI-025**: Time period selector buttons (All Time, Past Week, Past Month)
- **UI-026**: Selected time period highlighted (vibrant green background, white text)
- **UI-027**: Unselected time periods (dark background, white text)
- **UI-028**: 2x2 grid of statistics cards (dark rounded rectangles)
- **UI-029**: "Highest Score" and "Current Streak" in vibrant green text
- **UI-030**: Other statistics in white text

##### 5.1.4 Help Screen Layout
- **UI-031**: "Blackjack Help" title centered in header (white, bold text)
- **UI-032**: Back arrow icon in top-left corner (white)
- **UI-033**: "Rules of Blackjack" section heading (large, bold, white text)
- **UI-034**: "How to Play" section heading (large, bold, white text)
- **UI-035**: Numbered list items (white text, clear typography)
- **UI-036**: Scrollable content area for longer text content

##### 5.1.5 Bottom Navigation
- **UI-037**: Dark green/gray navigation bar at bottom
- **UI-038**: Three navigation items: Game, Stats, Help
- **UI-039**: Dice icon for Game tab
- **UI-040**: Bar chart icon for Stats tab
- **UI-041**: Question mark icon for Help tab
- **UI-042**: Active tab highlighted with vibrant green background
- **UI-043**: Inactive tabs with light gray icons and text
- **UI-044**: Tab labels below icons (white text for active, light gray for inactive)

##### 5.1.6 Card Design Integration
- **UI-045**: Integration of poker card images from "./Poker Cards" folder
- **UI-046**: Classic card designs (Ace of Spades with ornate black spade)
- **UI-047**: Detailed face cards (King of Hearts with bearded king illustration)
- **UI-048**: Standard pip cards (7 of Diamonds with seven red diamond pips)
- **UI-049**: Card back design (plain light beige with rounded corners)
- **UI-050**: Consistent card sizing and aspect ratio

#### 5.2 Hardware Interfaces
- **HI-001**: Touch screen input support
- **HI-002**: Device orientation support (primarily portrait)
- **HI-003**: Standard Android hardware button support

### 6. Other Non-Functional Requirements

#### 6.1 Localization
- **L-001**: The application shall support English language
- **L-002**: The application shall be prepared for future localization

#### 6.2 Legal and Regulatory
- **LR-001**: The application shall include appropriate age restrictions
- **LR-002**: The application shall comply with Google Play Store policies

### 7. UI/UX Design Specifications

#### 7.1 Color Palette
- **Primary Dark Green**: #1B5E20 (main game area background)
- **Secondary Dark Gray**: #424242 (top/bottom bars)
- **Accent Vibrant Green**: #4CAF50 (interactive elements, highlights)
- **Text Light Gray**: #BDBDBD (labels, secondary information)
- **Text White**: #FFFFFF (primary content, titles)
- **Card Back Beige**: #F5F5DC (face-down card background)

#### 7.2 Typography
- **Screen Titles**: Bold, white, large size (e.g., "Blackjack", "Statistics", "Blackjack Help")
- **Section Headings**: Bold, white, medium size (e.g., "Rules of Blackjack", "How to Play")
- **Labels**: Light gray, regular weight (e.g., "Dealer's Hand", "Your Hand", "Bet", "Winnings")
- **Statistics Values**: Large, white numbers for prominence
- **Highlighted Values**: Vibrant green for positive metrics (win percentage, highest score, winning streaks)
- **Body Text**: White, regular weight for readability

#### 7.3 Layout Specifications
- **Card Spacing**: Horizontal layout with slight overlap (approximately 20% overlap)
- **Button Styling**: Rounded corners (8dp radius), vibrant green background, white text
- **Card Containers**: Rounded rectangles (12dp radius) with dark backgrounds
- **Progress Bars**: Horizontal bars with vibrant green fill for positive metrics
- **Navigation Icons**: 24dp size, white for inactive, vibrant green for active

#### 7.4 Screen-Specific Layouts

##### 7.4.1 Game Screen
- **Header**: "Blackjack Table" (top-left), "Blackjack" (center), Settings icon (top-right)
- **Dealer Section**: "Dealer's Hand" label, two cards (one face-down)
- **Player Section**: "Your Hand" label, two cards (both face-up)
- **Game Info**: Bet and Winnings displayed side-by-side
- **Controls**: Hit and Stand buttons side-by-side, Deal button below (centered)

##### 7.4.2 Statistics Screen
- **Header**: Back arrow (left), "Statistics" (center)
- **Overall Record Card**: Large rounded card with win/loss progress bar
- **Time Period Selector**: Three buttons (All Time, Past Week, Past Month)
- **Statistics Grid**: 2x2 grid of rounded cards showing individual metrics
- **Navigation**: Bottom bar with Stats tab highlighted

##### 7.4.3 Help Screen
- **Header**: Back arrow (left), "Blackjack Help" (center)
- **Content**: Scrollable area with "Rules of Blackjack" and "How to Play" sections
- **Navigation**: Bottom bar with Help tab highlighted

#### 7.5 Card Design Specifications
- **Card Dimensions**: Standard playing card aspect ratio (2.5:3.5)
- **Card Back**: Plain light beige background with rounded corners
- **Face Cards**: Detailed illustrations (King of Hearts with ornate design)
- **Number Cards**: Standard pip arrangements (7 of Diamonds with seven red diamonds)
- **Ace Cards**: Large ornate suit symbols (Ace of Spades with black spade)
- **Card Overlap**: Approximately 20% horizontal overlap for visual appeal

### 8. Appendices

#### 8.1 Card Image Assets
The application will use the following card images from the "./Poker Cards" folder:
- Standard 52-card deck (A, 2-10, J, Q, K for each suit: Clubs, Diamonds, Hearts, Spades)
- Card back image (cover.jpg)
- All images in JPG format
- Specific card designs referenced in UI specifications:
  - Ace of Spades: Ornate black spade design
  - King of Hearts: Detailed bearded king illustration
  - 7 of Diamonds: Seven red diamond pips in standard arrangement

#### 8.2 Technical Architecture
- **Architecture Pattern**: MVVM (Model-View-ViewModel)
- **UI Framework**: Android XML Layouts with Fragments
- **Data Persistence**: SharedPreferences for statistics
- **Navigation**: Android Navigation Component
- **Image Loading**: Android ImageView with local resources
- **Theme**: Custom dark theme with specified color palette

#### 8.3 Development Guidelines
- Follow Android development best practices
- Use Kotlin as the primary programming language
- Implement proper error handling and logging
- Follow Material Design guidelines for UI/UX
- Ensure accessibility compliance
- Maintain consistent color scheme and typography
- Use rounded corners and card-based layouts for modern appearance

---

**Document Version**: 1.0  
**Last Updated**: [Current Date]  
**Prepared By**: Development Team  
**Approved By**: Project Stakeholder