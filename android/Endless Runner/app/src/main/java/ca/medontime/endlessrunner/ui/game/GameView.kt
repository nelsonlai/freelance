package ca.medontime.endlessrunner.ui.game

import android.content.Context
import android.graphics.*
import android.util.AttributeSet
import android.view.View
import ca.medontime.endlessrunner.domain.model.GameState
import ca.medontime.endlessrunner.domain.model.Obstacle
import ca.medontime.endlessrunner.domain.model.Coin
import ca.medontime.endlessrunner.domain.model.PowerUp
import ca.medontime.endlessrunner.domain.model.ObstacleType
import ca.medontime.endlessrunner.domain.model.PowerUpType

class GameView @JvmOverloads constructor(
    context: Context,
    attrs: AttributeSet? = null,
    defStyleAttr: Int = 0
) : View(context, attrs, defStyleAttr) {
    
    private val paint = Paint()
    private val backgroundPaint = Paint()
    private val characterPaint = Paint()
    private val obstaclePaint = Paint()
    private val coinPaint = Paint()
    private val powerUpPaint = Paint()
    
    private var gameState: GameState? = null
    private var screenWidth = 0f
    private var screenHeight = 0f
    private var laneWidth = 0f
    
    init {
        setupPaints()
    }
    
    private fun setupPaints() {
        // Background paint
        backgroundPaint.color = Color.parseColor("#F5F5F5")
        
        // Character paint
        characterPaint.color = Color.parseColor("#2196F3")
        characterPaint.style = Paint.Style.FILL
        
        // Obstacle paint
        obstaclePaint.color = Color.parseColor("#8B4513")
        obstaclePaint.style = Paint.Style.FILL
        
        // Coin paint
        coinPaint.color = Color.parseColor("#FFD700")
        coinPaint.style = Paint.Style.FILL
        
        // Power-up paint
        powerUpPaint.color = Color.parseColor("#9C27B0")
        powerUpPaint.style = Paint.Style.FILL
    }
    
    override fun onSizeChanged(w: Int, h: Int, oldw: Int, oldh: Int) {
        super.onSizeChanged(w, h, oldw, oldh)
        screenWidth = w.toFloat()
        screenHeight = h.toFloat()
        laneWidth = screenWidth / 3f
    }
    
    override fun onDraw(canvas: Canvas) {
        super.onDraw(canvas)
        
        // Draw background
        canvas.drawRect(0f, 0f, screenWidth, screenHeight, backgroundPaint)
        
        // Draw lanes
        drawLanes(canvas)
        
        // Draw game elements
        gameState?.let { state ->
            drawCharacter(canvas, state)
            drawObstacles(canvas, state.obstacles)
            drawCoins(canvas, state.coinsList)
            drawPowerUps(canvas, state.powerUps)
        }
    }
    
    private fun drawLanes(canvas: Canvas) {
        paint.color = Color.parseColor("#E0E0E0")
        paint.strokeWidth = 2f
        
        // Draw lane dividers
        canvas.drawLine(laneWidth, 0f, laneWidth, screenHeight, paint)
        canvas.drawLine(laneWidth * 2, 0f, laneWidth * 2, screenHeight, paint)
    }
    
    private fun drawCharacter(canvas: Canvas, gameState: GameState) {
        val characterX = (gameState.characterLane * laneWidth) + (laneWidth / 2f)
        val characterY = screenHeight - 100f
        
        // Draw character
        canvas.drawCircle(characterX, characterY, 25f, characterPaint)
        
        // Draw character state indicators
        if (gameState.isJumping) {
            // Draw jump indicator
            paint.color = Color.parseColor("#4CAF50")
            canvas.drawRect(characterX - 15f, characterY - 40f, characterX + 15f, characterY - 20f, paint)
        }
        
        if (gameState.isSliding) {
            // Draw slide indicator
            paint.color = Color.parseColor("#FF9800")
            canvas.drawRect(characterX - 20f, characterY + 10f, characterX + 20f, characterY + 30f, paint)
        }
    }
    
    private fun drawObstacles(canvas: Canvas, obstacles: List<Obstacle>) {
        obstacles.forEach { obstacle ->
            val obstacleX = (obstacle.lane * laneWidth) + (laneWidth / 2f)
            val obstacleY = screenHeight - obstacle.position
            
            when (obstacle.type) {
                ObstacleType.STATIC_BLOCK -> {
                    canvas.drawRect(
                        obstacleX - 20f, obstacleY - 40f,
                        obstacleX + 20f, obstacleY + 40f,
                        obstaclePaint
                    )
                }
                ObstacleType.MOVING_BLOCK -> {
                    canvas.drawRect(
                        obstacleX - 15f, obstacleY - 30f,
                        obstacleX + 15f, obstacleY + 30f,
                        obstaclePaint
                    )
                }
                ObstacleType.SPIKES -> {
                    // Draw spikes as triangles
                    val path = Path()
                    path.moveTo(obstacleX, obstacleY - 20f)
                    path.lineTo(obstacleX - 15f, obstacleY + 20f)
                    path.lineTo(obstacleX + 15f, obstacleY + 20f)
                    path.close()
                    canvas.drawPath(path, obstaclePaint)
                }
            }
        }
    }
    
    private fun drawCoins(canvas: Canvas, coins: List<Coin>) {
        coins.forEach { coin ->
            val coinX = (coin.lane * laneWidth) + (laneWidth / 2f)
            val coinY = screenHeight - coin.position
            
            // Draw coin as circle
            canvas.drawCircle(coinX, coinY, 15f, coinPaint)
            
            // Draw coin value
            paint.color = Color.BLACK
            paint.textSize = 12f
            paint.textAlign = Paint.Align.CENTER
            canvas.drawText(coin.value.toString(), coinX, coinY + 4f, paint)
        }
    }
    
    private fun drawPowerUps(canvas: Canvas, powerUps: List<PowerUp>) {
        powerUps.forEach { powerUp ->
            val powerUpX = (powerUp.lane * laneWidth) + (laneWidth / 2f)
            val powerUpY = screenHeight - powerUp.position
            
            when (powerUp.type) {
                PowerUpType.MAGNET -> {
                    // Draw magnet as diamond
                    val path = Path()
                    path.moveTo(powerUpX, powerUpY - 15f)
                    path.lineTo(powerUpX + 15f, powerUpY)
                    path.lineTo(powerUpX, powerUpY + 15f)
                    path.lineTo(powerUpX - 15f, powerUpY)
                    path.close()
                    canvas.drawPath(path, powerUpPaint)
                }
                PowerUpType.SHIELD -> {
                    // Draw shield as circle
                    canvas.drawCircle(powerUpX, powerUpY, 18f, powerUpPaint)
                }
                PowerUpType.SPEED_BOOST -> {
                    // Draw speed boost as star
                    val path = Path()
                    val outerRadius = 15f
                    val innerRadius = 8f
                    val points = 5
                    
                    for (i in 0 until points * 2) {
                        val angle = (i * Math.PI / points).toFloat()
                        val radius = if (i % 2 == 0) outerRadius else innerRadius
                        val x = powerUpX + radius * kotlin.math.cos(angle.toDouble()).toFloat()
                        val y = powerUpY + radius * kotlin.math.sin(angle.toDouble()).toFloat()
                        
                        if (i == 0) {
                            path.moveTo(x, y)
                        } else {
                            path.lineTo(x, y)
                        }
                    }
                    path.close()
                    canvas.drawPath(path, powerUpPaint)
                }
            }
        }
    }
    
    fun updateGameState(gameState: GameState) {
        this.gameState = gameState
        invalidate()
    }
}
