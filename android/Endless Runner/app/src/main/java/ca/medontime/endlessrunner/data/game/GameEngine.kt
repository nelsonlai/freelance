package ca.medontime.endlessrunner.data.game

import ca.medontime.endlessrunner.domain.model.GameState
import ca.medontime.endlessrunner.domain.model.Obstacle
import ca.medontime.endlessrunner.domain.model.Coin
import ca.medontime.endlessrunner.domain.model.PowerUp
import ca.medontime.endlessrunner.domain.model.ObstacleType
import ca.medontime.endlessrunner.domain.model.PowerUpType
import kotlinx.coroutines.*
import kotlin.random.Random
class GameEngine {
    
    private var gameJob: Job? = null
    private val gameScope = CoroutineScope(Dispatchers.Main + SupervisorJob())
    
    private var gameStateCallback: ((GameState) -> Unit)? = null
    private var currentGameState = GameState()
    
    private val obstacleGenerationInterval = 2000L // 2 seconds
    private val coinGenerationInterval = 1000L // 1 second
    private val powerUpGenerationInterval = 10000L // 10 seconds
    
    fun startGame(onGameStateUpdate: (GameState) -> Unit) {
        gameStateCallback = onGameStateUpdate
        currentGameState = currentGameState.copy(isRunning = true, isPaused = false)
        
        gameJob = gameScope.launch {
            while (currentGameState.isRunning && !currentGameState.isPaused) {
                updateGame()
                delay(16) // ~60 FPS
            }
        }
        
        // Start generation coroutines
        startObstacleGeneration()
        startCoinGeneration()
        startPowerUpGeneration()
    }
    
    fun pauseGame() {
        currentGameState = currentGameState.copy(isPaused = true)
        gameJob?.cancel()
    }
    
    fun resumeGame() {
        currentGameState = currentGameState.copy(isPaused = false)
        startGame(gameStateCallback ?: return)
    }
    
    fun endGame() {
        currentGameState = currentGameState.copy(isRunning = false, isPaused = false)
        gameJob?.cancel()
        gameJob = null
    }
    
    fun resetGame() {
        // Cancel any running game
        gameJob?.cancel()
        gameJob = null
        
        // Reset to initial state
        currentGameState = GameState()
    }
    
    fun moveCharacterLane(lane: Int) {
        if (lane in 0..2) {
            currentGameState = currentGameState.copy(characterLane = lane)
            notifyGameStateUpdate()
        }
    }
    
    fun setCharacterJumping(isJumping: Boolean) {
        currentGameState = currentGameState.copy(isJumping = isJumping)
        notifyGameStateUpdate()
    }
    
    fun setCharacterSliding(isSliding: Boolean) {
        currentGameState = currentGameState.copy(isSliding = isSliding)
        notifyGameStateUpdate()
    }
    
    private fun updateGame() {
        // Update obstacle positions
        updateObstacles()
        
        // Update coin positions
        updateCoins()
        
        // Update power-up positions
        updatePowerUps()
        
        // Check collisions
        checkCollisions()
        
        // Update score
        updateScore()
        
        notifyGameStateUpdate()
    }
    
    private fun updateObstacles() {
        val updatedObstacles = currentGameState.obstacles.map { obstacle ->
            obstacle.copy(position = obstacle.position - (2.0f * currentGameState.speed))
        }.filter { it.position > -100 } // Remove obstacles that are off-screen
        
        currentGameState = currentGameState.copy(obstacles = updatedObstacles)
    }
    
    private fun updateCoins() {
        val updatedCoins = currentGameState.coinsList.map { coin ->
            coin.copy(position = coin.position - (2.0f * currentGameState.speed))
        }.filter { it.position > -100 } // Remove coins that are off-screen
        
        currentGameState = currentGameState.copy(coinsList = updatedCoins)
    }
    
    private fun updatePowerUps() {
        val updatedPowerUps = currentGameState.powerUps.map { powerUp ->
            powerUp.copy(position = powerUp.position - (2.0f * currentGameState.speed))
        }.filter { it.position > -100 } // Remove power-ups that are off-screen
        
        currentGameState = currentGameState.copy(powerUps = updatedPowerUps)
    }
    
    private fun checkCollisions() {
        val characterLane = currentGameState.characterLane
        val characterPosition = 0f // Character is always at position 0
        
        // Check obstacle collisions
        val collidingObstacles = currentGameState.obstacles.filter { obstacle ->
            obstacle.lane == characterLane && 
            obstacle.position <= characterPosition + 50 && 
            obstacle.position >= characterPosition - 50 &&
            !currentGameState.isJumping && 
            !currentGameState.isSliding
        }
        
        if (collidingObstacles.isNotEmpty()) {
            endGame()
            return
        }
        
        // Check coin collections
        val collectedCoins = currentGameState.coinsList.filter { coin ->
            coin.lane == characterLane && 
            coin.position <= characterPosition + 30 && 
            coin.position >= characterPosition - 30
        }
        
        if (collectedCoins.isNotEmpty()) {
            val newCoins = currentGameState.coins - collectedCoins.size
            val newCoinsList = currentGameState.coinsList.filter { coin ->
                !collectedCoins.contains(coin)
            }
            currentGameState = currentGameState.copy(
                coins = newCoins,
                coinsList = newCoinsList
            )
        }
        
        // Check power-up collections
        val collectedPowerUps = currentGameState.powerUps.filter { powerUp ->
            powerUp.lane == characterLane && 
            powerUp.position <= characterPosition + 30 && 
            powerUp.position >= characterPosition - 30
        }
        
        if (collectedPowerUps.isNotEmpty()) {
            val newPowerUpsList = currentGameState.powerUps.filter { powerUp ->
                !collectedPowerUps.contains(powerUp)
            }
            val newActivePowerUps = currentGameState.activePowerUps.toMutableList()
            newActivePowerUps.addAll(collectedPowerUps)
            
            currentGameState = currentGameState.copy(
                powerUps = newPowerUpsList,
                activePowerUps = newActivePowerUps
            )
            
            // Apply power-up effects
            collectedPowerUps.forEach { powerUp ->
                applyPowerUpEffect(powerUp)
            }
        }
    }
    
    private fun applyPowerUpEffect(powerUp: PowerUp) {
        when (powerUp.type) {
            PowerUpType.MAGNET -> {
                // Attract nearby coins
                val nearbyCoins = currentGameState.coinsList.filter { coin ->
                    kotlin.math.abs(coin.position - 0f) <= 200
                }
                val newCoins = currentGameState.coins + nearbyCoins.size
                val newCoinsList = currentGameState.coinsList.filter { coin ->
                    !nearbyCoins.contains(coin)
                }
                currentGameState = currentGameState.copy(
                    coins = newCoins,
                    coinsList = newCoinsList
                )
            }
            PowerUpType.SHIELD -> {
                // Shield effect is handled in collision detection
            }
            PowerUpType.SPEED_BOOST -> {
                currentGameState = currentGameState.copy(speed = currentGameState.speed * 1.5f)
            }
        }
    }
    
    private fun updateScore() {
        val scoreIncrease = (currentGameState.speed * 0.1f).toInt()
        currentGameState = currentGameState.copy(score = currentGameState.score + scoreIncrease)
    }
    
    private fun startObstacleGeneration() {
        gameScope.launch {
            while (currentGameState.isRunning) {
                if (!currentGameState.isPaused) {
                    generateObstacle()
                }
                delay(obstacleGenerationInterval)
            }
        }
    }
    
    private fun startCoinGeneration() {
        gameScope.launch {
            while (currentGameState.isRunning) {
                if (!currentGameState.isPaused) {
                    generateCoin()
                }
                delay(coinGenerationInterval)
            }
        }
    }
    
    private fun startPowerUpGeneration() {
        gameScope.launch {
            while (currentGameState.isRunning) {
                if (!currentGameState.isPaused) {
                    generatePowerUp()
                }
                delay(powerUpGenerationInterval)
            }
        }
    }
    
    private fun generateObstacle() {
        val obstacle = Obstacle(
            id = "obstacle_${System.currentTimeMillis()}",
            lane = Random.nextInt(0, 3),
            position = 1000f,
            type = ObstacleType.values()[Random.nextInt(ObstacleType.values().size)]
        )
        
        val newObstacles = currentGameState.obstacles.toMutableList()
        newObstacles.add(obstacle)
        currentGameState = currentGameState.copy(obstacles = newObstacles)
    }
    
    private fun generateCoin() {
        val coin = Coin(
            id = "coin_${System.currentTimeMillis()}",
            lane = Random.nextInt(0, 3),
            position = 1000f,
            value = 1
        )
        
        val newCoins = currentGameState.coinsList.toMutableList()
        newCoins.add(coin)
        currentGameState = currentGameState.copy(coinsList = newCoins)
    }
    
    private fun generatePowerUp() {
        val powerUp = PowerUp(
            id = "powerup_${System.currentTimeMillis()}",
            lane = Random.nextInt(0, 3),
            position = 1000f,
            type = PowerUpType.values()[Random.nextInt(PowerUpType.values().size)]
        )
        
        val newPowerUps = currentGameState.powerUps.toMutableList()
        newPowerUps.add(powerUp)
        currentGameState = currentGameState.copy(powerUps = newPowerUps)
    }
    
    private fun notifyGameStateUpdate() {
        gameStateCallback?.invoke(currentGameState)
    }
    
    fun getCurrentGameState(): GameState = currentGameState
}
