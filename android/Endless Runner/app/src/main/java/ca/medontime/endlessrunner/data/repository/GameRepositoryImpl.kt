package ca.medontime.endlessrunner.data.repository

import ca.medontime.endlessrunner.domain.model.GameState
import ca.medontime.endlessrunner.domain.model.Obstacle
import ca.medontime.endlessrunner.domain.model.Coin
import ca.medontime.endlessrunner.domain.model.PowerUp
import ca.medontime.endlessrunner.domain.repository.GameRepository
import kotlinx.coroutines.flow.Flow
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.StateFlow
import kotlinx.coroutines.flow.asStateFlow
class GameRepositoryImpl : GameRepository {
    
    private val _gameState = MutableStateFlow(GameState())
    private val gameState: StateFlow<GameState> = _gameState.asStateFlow()
    
    override fun getGameState(): Flow<GameState> = gameState
    
    override suspend fun startGame() {
        _gameState.value = _gameState.value.copy(
            isRunning = true,
            isPaused = false,
            score = 0,
            coins = 0,
            characterLane = 1,
            isJumping = false,
            isSliding = false,
            speed = 1.0f,
            obstacles = emptyList(),
            coinsList = emptyList(),
            powerUps = emptyList(),
            activePowerUps = emptyList()
        )
    }
    
    override suspend fun pauseGame() {
        _gameState.value = _gameState.value.copy(isPaused = true)
    }
    
    override suspend fun resumeGame() {
        _gameState.value = _gameState.value.copy(isPaused = false)
    }
    
    override suspend fun endGame() {
        val currentState = _gameState.value
        val newHighScore = if (currentState.score > currentState.highScore) {
            currentState.score
        } else {
            currentState.highScore
        }
        
        _gameState.value = currentState.copy(
            isRunning = false,
            isPaused = false,
            highScore = newHighScore
        )
    }
    
    override suspend fun updateScore(score: Int) {
        _gameState.value = _gameState.value.copy(score = score)
    }
    
    override suspend fun updateCoins(coins: Int) {
        _gameState.value = _gameState.value.copy(coins = coins)
    }
    
    override suspend fun updateHighScore(highScore: Int) {
        _gameState.value = _gameState.value.copy(highScore = highScore)
    }
    
    override suspend fun moveCharacterLane(lane: Int) {
        if (lane in 0..2) {
            _gameState.value = _gameState.value.copy(characterLane = lane)
        }
    }
    
    override suspend fun setCharacterJumping(isJumping: Boolean) {
        _gameState.value = _gameState.value.copy(isJumping = isJumping)
    }
    
    override suspend fun setCharacterSliding(isSliding: Boolean) {
        _gameState.value = _gameState.value.copy(isSliding = isSliding)
    }
    
    override suspend fun updateGameSpeed(speed: Float) {
        _gameState.value = _gameState.value.copy(speed = speed)
    }
    
    override suspend fun addObstacle(obstacle: Obstacle) {
        val currentObstacles = _gameState.value.obstacles.toMutableList()
        currentObstacles.add(obstacle)
        _gameState.value = _gameState.value.copy(obstacles = currentObstacles)
    }
    
    override suspend fun removeObstacle(obstacleId: String) {
        val currentObstacles = _gameState.value.obstacles.toMutableList()
        currentObstacles.removeAll { it.id == obstacleId }
        _gameState.value = _gameState.value.copy(obstacles = currentObstacles)
    }
    
    override suspend fun addCoin(coin: Coin) {
        val currentCoins = _gameState.value.coinsList.toMutableList()
        currentCoins.add(coin)
        _gameState.value = _gameState.value.copy(coinsList = currentCoins)
    }
    
    override suspend fun removeCoin(coinId: String) {
        val currentCoins = _gameState.value.coinsList.toMutableList()
        currentCoins.removeAll { it.id == coinId }
        _gameState.value = _gameState.value.copy(coinsList = currentCoins)
    }
    
    override suspend fun addPowerUp(powerUp: PowerUp) {
        val currentPowerUps = _gameState.value.powerUps.toMutableList()
        currentPowerUps.add(powerUp)
        _gameState.value = _gameState.value.copy(powerUps = currentPowerUps)
    }
    
    override suspend fun removePowerUp(powerUpId: String) {
        val currentPowerUps = _gameState.value.powerUps.toMutableList()
        currentPowerUps.removeAll { it.id == powerUpId }
        _gameState.value = _gameState.value.copy(powerUps = currentPowerUps)
    }
    
    override suspend fun activatePowerUp(powerUp: PowerUp) {
        val currentActivePowerUps = _gameState.value.activePowerUps.toMutableList()
        currentActivePowerUps.add(powerUp)
        _gameState.value = _gameState.value.copy(activePowerUps = currentActivePowerUps)
    }
    
    override suspend fun deactivatePowerUp(powerUpId: String) {
        val currentActivePowerUps = _gameState.value.activePowerUps.toMutableList()
        currentActivePowerUps.removeAll { it.id == powerUpId }
        _gameState.value = _gameState.value.copy(activePowerUps = currentActivePowerUps)
    }
}
