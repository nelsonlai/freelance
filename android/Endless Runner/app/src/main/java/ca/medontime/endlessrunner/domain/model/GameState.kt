package ca.medontime.endlessrunner.domain.model

data class GameState(
    val isRunning: Boolean = false,
    val isPaused: Boolean = false,
    val score: Int = 0,
    val coins: Int = 0,
    val highScore: Int = 0,
    val characterLane: Int = 1, // 0 = left, 1 = center, 2 = right
    val isJumping: Boolean = false,
    val isSliding: Boolean = false,
    val speed: Float = 1.0f,
    val obstacles: List<Obstacle> = emptyList(),
    val coinsList: List<Coin> = emptyList(),
    val powerUps: List<PowerUp> = emptyList(),
    val activePowerUps: List<PowerUp> = emptyList()
)

data class Obstacle(
    val id: String,
    val lane: Int,
    val position: Float,
    val type: ObstacleType
)

enum class ObstacleType {
    STATIC_BLOCK,
    MOVING_BLOCK,
    SPIKES
}

data class Coin(
    val id: String,
    val lane: Int,
    val position: Float,
    val value: Int = 1
)

data class PowerUp(
    val id: String,
    val lane: Int,
    val position: Float,
    val type: PowerUpType,
    val duration: Long = 5000L // 5 seconds default
)

enum class PowerUpType {
    MAGNET,
    SHIELD,
    SPEED_BOOST
}
