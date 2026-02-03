package ca.medontime.endlessrunner.domain.usecase

import ca.medontime.endlessrunner.domain.model.GameState
import ca.medontime.endlessrunner.domain.model.Obstacle
import ca.medontime.endlessrunner.domain.model.Coin
import ca.medontime.endlessrunner.domain.model.PowerUp
import ca.medontime.endlessrunner.domain.repository.GameRepository
import kotlinx.coroutines.flow.Flow
class GameUseCase(
    private val gameRepository: GameRepository
) {
    fun getGameState(): Flow<GameState> = gameRepository.getGameState()
    
    suspend fun startGame() = gameRepository.startGame()
    
    suspend fun pauseGame() = gameRepository.pauseGame()
    
    suspend fun resumeGame() = gameRepository.resumeGame()
    
    suspend fun endGame() = gameRepository.endGame()
    
    suspend fun updateScore(score: Int) = gameRepository.updateScore(score)
    
    suspend fun updateCoins(coins: Int) = gameRepository.updateCoins(coins)
    
    suspend fun updateHighScore(highScore: Int) = gameRepository.updateHighScore(highScore)
    
    suspend fun moveCharacterLane(lane: Int) = gameRepository.moveCharacterLane(lane)
    
    suspend fun setCharacterJumping(isJumping: Boolean) = gameRepository.setCharacterJumping(isJumping)
    
    suspend fun setCharacterSliding(isSliding: Boolean) = gameRepository.setCharacterSliding(isSliding)
    
    suspend fun updateGameSpeed(speed: Float) = gameRepository.updateGameSpeed(speed)
    
    suspend fun addObstacle(obstacle: Obstacle) = gameRepository.addObstacle(obstacle)
    
    suspend fun removeObstacle(obstacleId: String) = gameRepository.removeObstacle(obstacleId)
    
    suspend fun addCoin(coin: Coin) = gameRepository.addCoin(coin)
    
    suspend fun removeCoin(coinId: String) = gameRepository.removeCoin(coinId)
    
    suspend fun addPowerUp(powerUp: PowerUp) = gameRepository.addPowerUp(powerUp)
    
    suspend fun removePowerUp(powerUpId: String) = gameRepository.removePowerUp(powerUpId)
    
    suspend fun activatePowerUp(powerUp: PowerUp) = gameRepository.activatePowerUp(powerUp)
    
    suspend fun deactivatePowerUp(powerUpId: String) = gameRepository.deactivatePowerUp(powerUpId)
}
