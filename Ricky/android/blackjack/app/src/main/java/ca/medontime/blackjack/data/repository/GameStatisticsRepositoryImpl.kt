package ca.medontime.blackjack.data.repository

import ca.medontime.blackjack.domain.model.GameResult
import ca.medontime.blackjack.domain.model.GameStatistics
import ca.medontime.blackjack.domain.repository.GameStatisticsRepository
import ca.medontime.blackjack.data.local.GameStatisticsDataSource
import kotlinx.coroutines.flow.Flow

/**
 * Repository implementation for game statistics
 */
class GameStatisticsRepositoryImpl(
    private val dataSource: GameStatisticsDataSource
) : GameStatisticsRepository {
    
    override suspend fun getStatistics(): GameStatistics {
        return dataSource.getStatistics()
    }
    
    override fun observeStatistics(): Flow<GameStatistics> {
        return dataSource.observeStatistics()
    }
    
    override suspend fun updateStatistics(
        gamesPlayed: Int,
        gamesWon: Int,
        gamesLost: Int,
        gamesPushed: Int,
        blackJacks: Int,
        highestScore: Int,
        totalScore: Int,
        currentStreak: Int,
        isWinningStreak: Boolean
    ) {
        dataSource.updateStatistics(
            gamesPlayed = gamesPlayed,
            gamesWon = gamesWon,
            gamesLost = gamesLost,
            gamesPushed = gamesPushed,
            blackJacks = blackJacks,
            highestScore = highestScore,
            totalScore = totalScore,
            currentStreak = currentStreak,
            isWinningStreak = isWinningStreak
        )
    }
    
    override suspend fun resetStatistics() {
        dataSource.resetStatistics()
    }
    
    override suspend fun updateStatisticsFromGameResult(
        result: GameResult,
        playerScore: Int,
        isBlackJack: Boolean
    ) {
        val currentStats = getStatistics()
        
        val gamesPlayed = 1
        val gamesWon = if (isWinResult(result)) 1 else 0
        val gamesLost = if (isLossResult(result)) 1 else 0
        val gamesPushed = if (result == GameResult.PUSH) 1 else 0
        val blackJacks = if (isBlackJack) 1 else 0
        
        // Calculate new streak
        val newStreak: Int
        val newIsWinningStreak: Boolean
        
        if (isWinResult(result)) {
            if (currentStats.isWinningStreak) {
                newStreak = currentStats.currentStreak + 1
                newIsWinningStreak = true
            } else {
                newStreak = 1
                newIsWinningStreak = true
            }
        } else if (isLossResult(result)) {
            if (!currentStats.isWinningStreak) {
                newStreak = currentStats.currentStreak + 1
                newIsWinningStreak = false
            } else {
                newStreak = 1
                newIsWinningStreak = false
            }
        } else {
            // Push - maintain current streak
            newStreak = currentStats.currentStreak
            newIsWinningStreak = currentStats.isWinningStreak
        }
        
        updateStatistics(
            gamesPlayed = gamesPlayed,
            gamesWon = gamesWon,
            gamesLost = gamesLost,
            gamesPushed = gamesPushed,
            blackJacks = blackJacks,
            highestScore = playerScore,
            totalScore = playerScore,
            currentStreak = newStreak,
            isWinningStreak = newIsWinningStreak
        )
    }
    
    private fun isWinResult(result: GameResult): Boolean {
        return result == GameResult.PLAYER_WINS || 
               result == GameResult.PLAYER_BLACKJACK || 
               result == GameResult.DEALER_BUST
    }
    
    private fun isLossResult(result: GameResult): Boolean {
        return result == GameResult.DEALER_WINS || 
               result == GameResult.DEALER_BLACKJACK || 
               result == GameResult.PLAYER_BUST
    }
}
