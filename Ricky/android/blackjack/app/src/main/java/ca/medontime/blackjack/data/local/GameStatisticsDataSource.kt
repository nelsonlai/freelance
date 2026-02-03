package ca.medontime.blackjack.data.local

import android.content.Context
import androidx.datastore.core.DataStore
import androidx.datastore.preferences.core.*
import androidx.datastore.preferences.preferencesDataStore
import ca.medontime.blackjack.domain.model.GameStatistics
import ca.medontime.blackjack.domain.repository.GameStatisticsRepository
import kotlinx.coroutines.flow.Flow
import kotlinx.coroutines.flow.first
import kotlinx.coroutines.flow.map

private val Context.dataStore: DataStore<Preferences> by preferencesDataStore(name = "game_statistics")

/**
 * Data source for game statistics using DataStore Preferences
 */
class GameStatisticsDataSource(
    private val context: Context
) {
    
    private val dataStore: DataStore<Preferences> = context.dataStore
    
    private object PreferencesKeys {
        val GAMES_PLAYED = intPreferencesKey("games_played")
        val GAMES_WON = intPreferencesKey("games_won")
        val GAMES_LOST = intPreferencesKey("games_lost")
        val GAMES_PUSHED = intPreferencesKey("games_pushed")
        val BLACK_JACKS = intPreferencesKey("black_jacks")
        val HIGHEST_SCORE = intPreferencesKey("highest_score")
        val TOTAL_SCORE = intPreferencesKey("total_score")
        val CURRENT_STREAK = intPreferencesKey("current_streak")
        val IS_WINNING_STREAK = booleanPreferencesKey("is_winning_streak")
    }
    
    /**
     * Get current statistics
     */
    suspend fun getStatistics(): GameStatistics {
        val preferences = dataStore.data.first()
        return GameStatistics(
            gamesPlayed = preferences[PreferencesKeys.GAMES_PLAYED] ?: 0,
            gamesWon = preferences[PreferencesKeys.GAMES_WON] ?: 0,
            gamesLost = preferences[PreferencesKeys.GAMES_LOST] ?: 0,
            gamesPushed = preferences[PreferencesKeys.GAMES_PUSHED] ?: 0,
            blackJacks = preferences[PreferencesKeys.BLACK_JACKS] ?: 0,
            highestScore = preferences[PreferencesKeys.HIGHEST_SCORE] ?: 0,
            totalScore = preferences[PreferencesKeys.TOTAL_SCORE] ?: 0,
            currentStreak = preferences[PreferencesKeys.CURRENT_STREAK] ?: 0,
            isWinningStreak = preferences[PreferencesKeys.IS_WINNING_STREAK] ?: true
        )
    }
    
    /**
     * Observe statistics changes
     */
    fun observeStatistics(): Flow<GameStatistics> {
        return dataStore.data.map { preferences ->
            GameStatistics(
                gamesPlayed = preferences[PreferencesKeys.GAMES_PLAYED] ?: 0,
                gamesWon = preferences[PreferencesKeys.GAMES_WON] ?: 0,
                gamesLost = preferences[PreferencesKeys.GAMES_LOST] ?: 0,
                gamesPushed = preferences[PreferencesKeys.GAMES_PUSHED] ?: 0,
                blackJacks = preferences[PreferencesKeys.BLACK_JACKS] ?: 0,
                highestScore = preferences[PreferencesKeys.HIGHEST_SCORE] ?: 0,
                totalScore = preferences[PreferencesKeys.TOTAL_SCORE] ?: 0,
                currentStreak = preferences[PreferencesKeys.CURRENT_STREAK] ?: 0,
                isWinningStreak = preferences[PreferencesKeys.IS_WINNING_STREAK] ?: true
            )
        }
    }
    
    /**
     * Update statistics
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
    ) {
        dataStore.edit { preferences ->
            val currentStats = GameStatistics(
                gamesPlayed = preferences[PreferencesKeys.GAMES_PLAYED] ?: 0,
                gamesWon = preferences[PreferencesKeys.GAMES_WON] ?: 0,
                gamesLost = preferences[PreferencesKeys.GAMES_LOST] ?: 0,
                gamesPushed = preferences[PreferencesKeys.GAMES_PUSHED] ?: 0,
                blackJacks = preferences[PreferencesKeys.BLACK_JACKS] ?: 0,
                highestScore = preferences[PreferencesKeys.HIGHEST_SCORE] ?: 0,
                totalScore = preferences[PreferencesKeys.TOTAL_SCORE] ?: 0,
                currentStreak = preferences[PreferencesKeys.CURRENT_STREAK] ?: 0,
                isWinningStreak = preferences[PreferencesKeys.IS_WINNING_STREAK] ?: true
            )
            
            preferences[PreferencesKeys.GAMES_PLAYED] = currentStats.gamesPlayed + gamesPlayed
            preferences[PreferencesKeys.GAMES_WON] = currentStats.gamesWon + gamesWon
            preferences[PreferencesKeys.GAMES_LOST] = currentStats.gamesLost + gamesLost
            preferences[PreferencesKeys.GAMES_PUSHED] = currentStats.gamesPushed + gamesPushed
            preferences[PreferencesKeys.BLACK_JACKS] = currentStats.blackJacks + blackJacks
            
            // Update highest score if new score is higher
            if (highestScore > currentStats.highestScore) {
                preferences[PreferencesKeys.HIGHEST_SCORE] = highestScore
            }
            
            preferences[PreferencesKeys.TOTAL_SCORE] = currentStats.totalScore + totalScore
            preferences[PreferencesKeys.CURRENT_STREAK] = currentStreak
            preferences[PreferencesKeys.IS_WINNING_STREAK] = isWinningStreak
        }
    }
    
    /**
     * Reset all statistics
     */
    suspend fun resetStatistics() {
        dataStore.edit { preferences ->
            preferences.clear()
        }
    }
}
