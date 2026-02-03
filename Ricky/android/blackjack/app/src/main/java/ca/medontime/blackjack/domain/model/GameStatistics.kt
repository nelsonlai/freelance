package ca.medontime.blackjack.domain.model

/**
 * Represents game statistics for tracking player performance
 */
data class GameStatistics(
    val gamesPlayed: Int = 0,
    val gamesWon: Int = 0,
    val gamesLost: Int = 0,
    val gamesPushed: Int = 0,
    val blackJacks: Int = 0,
    val highestScore: Int = 0,
    val totalScore: Int = 0,
    val currentStreak: Int = 0,
    val isWinningStreak: Boolean = true
) {
    /**
     * Calculate win percentage
     */
    fun getWinPercentage(): Double {
        return if (gamesPlayed > 0) {
            (gamesWon.toDouble() / gamesPlayed.toDouble()) * 100.0
        } else {
            0.0
        }
    }
    
    /**
     * Calculate average score
     */
    fun getAverageScore(): Double {
        return if (gamesPlayed > 0) {
            totalScore.toDouble() / gamesPlayed.toDouble()
        } else {
            0.0
        }
    }
    
    /**
     * Get formatted win percentage string
     */
    fun getWinPercentageString(): String {
        return String.format("%.1f%%", getWinPercentage())
    }
    
    /**
     * Get formatted average score string
     */
    fun getAverageScoreString(): String {
        return String.format("%.1f", getAverageScore())
    }
    
    /**
     * Get formatted current streak string
     */
    fun getCurrentStreakString(): String {
        val prefix = if (isWinningStreak) "W" else "L"
        return "$prefix$currentStreak"
    }
}
