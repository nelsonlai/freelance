package ca.medontime.blackjack.ui.screens.statistics

import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import ca.medontime.blackjack.domain.model.GameStatistics
import ca.medontime.blackjack.domain.repository.GameStatisticsRepository
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.StateFlow
import kotlinx.coroutines.flow.asStateFlow
import kotlinx.coroutines.flow.stateIn
import kotlinx.coroutines.launch

/**
 * ViewModel for the Statistics screen
 */
class StatisticsViewModel(
    private val statisticsRepository: GameStatisticsRepository
) : ViewModel() {
    
    private val _selectedTimePeriod = MutableStateFlow(TimePeriod.ALL_TIME)
    val selectedTimePeriod: StateFlow<TimePeriod> = _selectedTimePeriod.asStateFlow()
    
    private val _statistics = MutableStateFlow(GameStatistics())
    val statistics: StateFlow<GameStatistics> = _statistics.asStateFlow()
    
    init {
        // Load initial statistics
        loadStatistics()
    }
    
    private fun loadStatistics() {
        viewModelScope.launch {
            statisticsRepository.observeStatistics().collect { stats ->
                _statistics.value = getFilteredStatisticsForPeriod(stats, _selectedTimePeriod.value)
            }
        }
    }
    
    /**
     * Update the selected time period
     */
    fun updateTimePeriod(period: TimePeriod) {
        _selectedTimePeriod.value = period
        // Reload statistics with new filter
        loadStatistics()
    }
    
    /**
     * Reset all statistics
     */
    fun resetStatistics() {
        viewModelScope.launch {
            statisticsRepository.resetStatistics()
        }
    }
    
    /**
     * Get filtered statistics based on time period
     * For now, we'll simulate different statistics for each period
     */
    private fun getFilteredStatisticsForPeriod(stats: GameStatistics, period: TimePeriod): GameStatistics {
        return when (period) {
            TimePeriod.ALL_TIME -> stats
            TimePeriod.PAST_WEEK -> GameStatistics(
                gamesPlayed = (stats.gamesPlayed * 0.3).toInt().coerceAtLeast(0),
                gamesWon = (stats.gamesWon * 0.3).toInt().coerceAtLeast(0),
                gamesLost = (stats.gamesLost * 0.3).toInt().coerceAtLeast(0),
                gamesPushed = (stats.gamesPushed * 0.3).toInt().coerceAtLeast(0),
                blackJacks = (stats.blackJacks * 0.3).toInt().coerceAtLeast(0),
                highestScore = stats.highestScore,
                totalScore = (stats.totalScore * 0.3).toInt().coerceAtLeast(0),
                currentStreak = stats.currentStreak,
                isWinningStreak = stats.isWinningStreak
            )
            TimePeriod.PAST_MONTH -> GameStatistics(
                gamesPlayed = (stats.gamesPlayed * 0.7).toInt().coerceAtLeast(0),
                gamesWon = (stats.gamesWon * 0.7).toInt().coerceAtLeast(0),
                gamesLost = (stats.gamesLost * 0.7).toInt().coerceAtLeast(0),
                gamesPushed = (stats.gamesPushed * 0.7).toInt().coerceAtLeast(0),
                blackJacks = (stats.blackJacks * 0.7).toInt().coerceAtLeast(0),
                highestScore = stats.highestScore,
                totalScore = (stats.totalScore * 0.7).toInt().coerceAtLeast(0),
                currentStreak = stats.currentStreak,
                isWinningStreak = stats.isWinningStreak
            )
        }
    }
    
    /**
     * Get filtered statistics based on time period
     * For now, we'll return all-time statistics as we don't have time-based filtering implemented
     */
    fun getFilteredStatistics(): StateFlow<GameStatistics> {
        return statistics
    }
}

/**
 * Enum for time period selection
 */
enum class TimePeriod {
    ALL_TIME,
    PAST_WEEK,
    PAST_MONTH
}