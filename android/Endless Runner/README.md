# Endless Runner Android Game

A mobile endless runner game built for Android devices following clean architecture principles and Material Design guidelines.

## Features

### Core Gameplay
- **Character Control**: Swipe gestures to control character movement
  - Left/Right: Change lanes
  - Up: Jump over obstacles
  - Down: Slide under obstacles
- **Endless Running**: Character automatically runs forward in an endless loop
- **Obstacle Avoidance**: Random obstacles that must be avoided using swipes
- **Coin Collection**: Collect coins for points as you run

### Power-ups
- **Magnet**: Attracts nearby coins automatically
- **Shield**: Protects character from one obstacle collision
- **Speed Boost**: Temporarily increases running speed

### Audio/Visual Features
- Background music that loops continuously during gameplay
- Sound effects for actions (coin collection, jumps, collisions, power-up activation)
- Repeating background environment for endless running feel
- Custom game view with canvas-based rendering

### User Interface
- **Home Screen**: Start game, settings, and profile options
- **Game Screen**: Real-time game view with score, coins, and power-up indicators
- **Pause/Resume**: Ability to pause and resume gameplay
- **Game Over Screen**: Displays final score, coins collected, and restart option
- **Profile Screen**: View player statistics
- **Settings Screen**: Configure audio and game preferences

## Architecture

The app follows clean architecture principles with clear separation of concerns:

### Domain Layer
- `GameState`: Core game state data model
- `GameRepository`: Repository interface for game data operations
- `GameUseCase`: Business logic for game operations

### Data Layer
- `GameRepositoryImpl`: Implementation of game repository
- `GameEngine`: Core game engine handling game loop, collision detection, and object generation
- `AudioManager`: Handles background music and sound effects

### Presentation Layer
- `MainActivity`: Main activity with bottom navigation
- `HomeFragment`: Home screen with game start options
- `GameFragment`: Game screen with swipe gesture handling
- `ProfileFragment`: Player profile and statistics
- `SettingsFragment`: Game settings and preferences
- `GameView`: Custom view for rendering game elements

## Technical Implementation

### Dependencies
- **Navigation Component**: For fragment navigation
- **Material Design**: For UI components and theming
- **ViewBinding**: For type-safe view access
- **Coroutines**: For asynchronous operations and game loop
- **Custom Canvas Drawing**: For game rendering

### Game Engine Features
- **Game Loop**: Runs at ~60 FPS for smooth gameplay
- **Collision Detection**: Real-time collision detection between character and obstacles
- **Object Generation**: Random generation of obstacles, coins, and power-ups
- **State Management**: Reactive state management using StateFlow
- **Gesture Handling**: Swipe gesture detection for character control

### Performance Considerations
- Optimized rendering with custom canvas drawing
- Efficient collision detection algorithms
- Memory management for game objects
- Smooth 60 FPS gameplay on mid-range devices

## Requirements Met

✅ **Functional Requirements**
- Character automatically runs forward
- Swipe controls for movement (left/right lanes, up jump, down slide)
- Random obstacle generation and avoidance
- Coin collection system
- Power-up system (Magnet, Shield, Speed Boost)
- Background music and sound effects
- Repeating background environment

✅ **Non-Functional Requirements**
- Performance: Smooth gameplay at 60 FPS
- Usability: Responsive swipe gestures with minimal input lag
- Scalability: Modular architecture for easy expansion
- Compatibility: Supports Android 10+ (API 24+)

✅ **User Interface Requirements**
- Home screen with navigation options
- Game screen with real-time gameplay
- Pause/resume functionality
- Game over screen with restart option

## Future Enhancements

The architecture supports easy addition of:
- Leaderboards and achievements
- Customizable characters and skins
- Social sharing of scores
- Additional power-ups and obstacles
- Multiple game themes/levels
- Online multiplayer features

## Getting Started

1. Clone the repository
2. Open in Android Studio
3. Build and run on Android device or emulator
4. Use swipe gestures to control the character and avoid obstacles

## Controls

- **Swipe Left/Right**: Move between lanes
- **Swipe Up**: Jump over obstacles
- **Swipe Down**: Slide under obstacles
- **Tap Pause**: Pause/resume game
- **Tap Restart**: Restart after game over
