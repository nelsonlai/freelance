package ca.medontime.endlessrunner.domain.repository

import ca.medontime.endlessrunner.domain.model.GameState
import kotlinx.coroutines.flow.Flow

interface GameRepository {
    fun getGameState(): Flow<GameState>
    suspend fun startGame()
    suspend fun pauseGame()
    suspend fun resumeGame()
    suspend fun endGame()
    suspend fun updateScore(score: Int)
    suspend fun updateCoins(coins: Int)
    suspend fun updateHighScore(highScore: Int)
    suspend fun moveCharacterLane(lane: Int)
    suspend fun setCharacterJumping(isJumping: Boolean)
    suspend fun setCharacterSliding(isSliding: Boolean)
    suspend fun updateGameSpeed(speed: Float)
    suspend fun addObstacle(obstacle: ca.medontime.endlessrunner.domain.model.Obstacle)
    suspend fun removeObstacle(obstacleId: String)
    suspend fun addCoin(coin: ca.medontime.endlessrunner.domain.model.Coin)
    suspend fun removeCoin(coinId: String)
    suspend fun addPowerUp(powerUp: ca.medontime.endlessrunner.domain.model.PowerUp)
    suspend fun removePowerUp(powerUpId: String)
    suspend fun activatePowerUp(powerUp: ca.medontime.endlessrunner.domain.model.PowerUp)
    suspend fun deactivatePowerUp(powerUpId: String)
}
