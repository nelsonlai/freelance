package ca.medontime.blackjack.domain.repository

import ca.medontime.blackjack.domain.model.GameStatistics
import kotlinx.coroutines.flow.Flow

/**
 * Repository interface for managing game statistics
 */
interface GameStatisticsRepository {
    
    /**
     * Get current game statistics
     */
    suspend fun getStatistics(): GameStatistics
    
    /**
     * Observe game statistics changes
     */
    fun observeStatistics(): Flow<GameStatistics>
    
    /**
     * Update statistics after a game
     */
    suspend fun updateStatistics(
        gamesPlayed: Int = 0,
        gamesWon: Int = 0,
        gamesLost: Int = 0,
        gamesPushed: Int = 0,
        blackJacks: Int = 0,
        highestScore: Int = 0,
        totalScore: Int = 0,
        currentStreak: Int = 0,
        isWinningStreak: Boolean = true
    )
    
    /**
     * Reset all statistics
     */
    suspend fun resetStatistics()
    
    /**
     * Update statistics based on game result
     */
    suspend fun updateStatisticsFromGameResult(
        result: ca.medontime.blackjack.domain.model.GameResult,
        playerScore: Int,
        isBlackJack: Boolean
    )
}
