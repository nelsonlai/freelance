package ca.medontime.endlessrunner.ui.game

import android.os.Bundle
import android.view.GestureDetector
import android.view.LayoutInflater
import android.view.MotionEvent
import android.view.View
import android.view.ViewGroup
import androidx.fragment.app.Fragment
import androidx.lifecycle.lifecycleScope
import ca.medontime.endlessrunner.databinding.FragmentGameBinding
import ca.medontime.endlessrunner.data.game.GameEngine
import ca.medontime.endlessrunner.domain.model.GameState
import ca.medontime.endlessrunner.EndlessRunnerApplication
import kotlinx.coroutines.launch

class GameFragment : Fragment() {
    
    private lateinit var gameEngine: GameEngine
    
    private var _binding: FragmentGameBinding? = null
    private val binding get() = _binding!!
    
    private lateinit var gestureDetector: GestureDetector
    
    override fun onCreateView(
        inflater: LayoutInflater,
        container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View {
        _binding = FragmentGameBinding.inflate(inflater, container, false)
        return binding.root
    }
    
    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)
        
        // Initialize game engine
        gameEngine = (requireActivity().application as EndlessRunnerApplication).gameEngine
        
        setupGestureDetector()
        setupClickListeners()
        startGame()
    }
    
    private fun setupGestureDetector() {
        gestureDetector = GestureDetector(requireContext(), object : GestureDetector.SimpleOnGestureListener() {
            override fun onFling(
                e1: MotionEvent?,
                e2: MotionEvent,
                velocityX: Float,
                velocityY: Float
            ): Boolean {
                val deltaX = e2.x - (e1?.x ?: 0f)
                val deltaY = e2.y - (e1?.y ?: 0f)
                
                // Lower threshold for better emulator experience
                val threshold = 50f
                
                when {
                    kotlin.math.abs(deltaX) > kotlin.math.abs(deltaY) -> {
                        // Horizontal swipe
                        when {
                            deltaX > threshold -> {
                                android.util.Log.d("GameFragment", "Swipe Right detected")
                                moveRight()
                                return true
                            }
                            deltaX < -threshold -> {
                                android.util.Log.d("GameFragment", "Swipe Left detected")
                                moveLeft()
                                return true
                            }
                        }
                    }
                    else -> {
                        // Vertical swipe
                        when {
                            deltaY > threshold -> {
                                android.util.Log.d("GameFragment", "Swipe Down detected")
                                slideDown()
                                return true
                            }
                            deltaY < -threshold -> {
                                android.util.Log.d("GameFragment", "Swipe Up detected")
                                jumpUp()
                                return true
                            }
                        }
                    }
                }
                return false
            }
        })
        
        // Set touch listener on the entire game area, not just the game view
        binding.root.setOnTouchListener { _, event ->
            gestureDetector.onTouchEvent(event)
        }
    }
    
    private fun setupClickListeners() {
        binding.btnPause.setOnClickListener {
            pauseGame()
        }
        
        binding.btnResume.setOnClickListener {
            resumeGame()
        }
        
        binding.btnRestart.setOnClickListener {
            restartGame()
        }
        
        // Debug button controls for emulator
        binding.btnLeft.setOnClickListener {
            android.util.Log.d("GameFragment", "Left button clicked")
            moveLeft()
        }
        
        binding.btnRight.setOnClickListener {
            android.util.Log.d("GameFragment", "Right button clicked")
            moveRight()
        }
        
        binding.btnJump.setOnClickListener {
            android.util.Log.d("GameFragment", "Jump button clicked")
            jumpUp()
        }
        
        binding.btnSlide.setOnClickListener {
            android.util.Log.d("GameFragment", "Slide button clicked")
            slideDown()
        }
        
        // Game Over buttons
        binding.btnNewGame.setOnClickListener {
            android.util.Log.d("GameFragment", "New Game button clicked - STARTING NEW GAME")
            startNewGame()
        }
        
        binding.btnRestartGameOver.setOnClickListener {
            android.util.Log.d("GameFragment", "Restart Game Over button clicked - RESTARTING GAME")
            restartGame()
        }
        
        // Add additional debugging for button state
        android.util.Log.d("GameFragment", "Button setup complete - btnNewGame: ${binding.btnNewGame.isClickable}, btnRestartGameOver: ${binding.btnRestartGameOver.isClickable}")
    }
    
    private fun startGame() {
        gameEngine.startGame { gameState ->
            updateUI(gameState)
            binding.gameView.updateGameState(gameState)
        }
    }
    
    private fun pauseGame() {
        gameEngine.pauseGame()
        binding.btnPause.visibility = View.GONE
        binding.btnResume.visibility = View.VISIBLE
    }
    
    private fun resumeGame() {
        gameEngine.resumeGame()
        binding.btnPause.visibility = View.VISIBLE
        binding.btnResume.visibility = View.GONE
    }
    
    private fun restartGame() {
        android.util.Log.d("GameFragment", "restartGame() called - hiding overlay and restarting game")
        
        // Hide game over overlay
        binding.layoutGameOver.visibility = View.GONE
        binding.btnRestart.visibility = View.GONE
        binding.btnResume.visibility = View.GONE
        binding.btnPause.visibility = View.VISIBLE
        
        // Reset game state and start new game
        gameEngine.resetGame()
        startGame()
        
        android.util.Log.d("GameFragment", "restartGame() completed")
    }
    
    private fun moveLeft() {
        val currentLane = gameEngine.getCurrentGameState().characterLane
        if (currentLane > 0) {
            gameEngine.moveCharacterLane(currentLane - 1)
        }
    }
    
    private fun moveRight() {
        val currentLane = gameEngine.getCurrentGameState().characterLane
        if (currentLane < 2) {
            gameEngine.moveCharacterLane(currentLane + 1)
        }
    }
    
    private fun jumpUp() {
        gameEngine.setCharacterJumping(true)
        lifecycleScope.launch {
            kotlinx.coroutines.delay(500) // Jump duration
            gameEngine.setCharacterJumping(false)
        }
    }
    
    private fun slideDown() {
        gameEngine.setCharacterSliding(true)
        lifecycleScope.launch {
            kotlinx.coroutines.delay(500) // Slide duration
            gameEngine.setCharacterSliding(false)
        }
    }
    
    private fun updateUI(gameState: GameState) {
        binding.tvScore.text = "Score: ${gameState.score}"
        binding.tvCoins.text = "Coins: ${gameState.coins}"
        binding.tvHighScore.text = "High Score: ${gameState.highScore}"
        
        // Character position is now handled by GameView
        
        // Update game elements
        updateObstacles(gameState.obstacles)
        updateCoins(gameState.coinsList)
        updatePowerUps(gameState.powerUps)
        
        // Update power-up indicators
        updatePowerUpIndicators(gameState.activePowerUps)
        
        // Show game over if not running
        if (!gameState.isRunning && !gameState.isPaused) {
            showGameOverDialog(gameState.score, gameState.coins)
        }
    }
    
    
    private fun updateObstacles(obstacles: List<ca.medontime.endlessrunner.domain.model.Obstacle>) {
        // This would be implemented with a custom view or canvas drawing
        // For now, we'll just update the count
        binding.tvObstacles.text = "Obstacles: ${obstacles.size}"
    }
    
    private fun updateCoins(coins: List<ca.medontime.endlessrunner.domain.model.Coin>) {
        // This would be implemented with a custom view or canvas drawing
        // For now, we'll just update the count
        binding.tvCoinsCount.text = "Coins on screen: ${coins.size}"
    }
    
    private fun updatePowerUps(powerUps: List<ca.medontime.endlessrunner.domain.model.PowerUp>) {
        // This would be implemented with a custom view or canvas drawing
        // For now, we'll just update the count
        binding.tvPowerUps.text = "Power-ups: ${powerUps.size}"
    }
    
    private fun updatePowerUpIndicators(activePowerUps: List<ca.medontime.endlessrunner.domain.model.PowerUp>) {
        binding.ivMagnet.visibility = if (activePowerUps.any { it.type == ca.medontime.endlessrunner.domain.model.PowerUpType.MAGNET }) {
            View.VISIBLE
        } else {
            View.GONE
        }
        
        binding.ivShield.visibility = if (activePowerUps.any { it.type == ca.medontime.endlessrunner.domain.model.PowerUpType.SHIELD }) {
            View.VISIBLE
        } else {
            View.GONE
        }
        
        binding.ivSpeedBoost.visibility = if (activePowerUps.any { it.type == ca.medontime.endlessrunner.domain.model.PowerUpType.SPEED_BOOST }) {
            View.VISIBLE
        } else {
            View.GONE
        }
    }
    
    private fun showGameOverDialog(score: Int, coins: Int) {
        android.util.Log.d("GameFragment", "showGameOverDialog() called with score: $score, coins: $coins")
        
        // Show game over overlay
        binding.layoutGameOver.visibility = View.VISIBLE
        binding.tvFinalScore.text = "Final Score: $score"
        binding.tvFinalCoins.text = "Coins Collected: $coins"
        binding.btnRestart.visibility = View.VISIBLE
        
        // Debug button states
        android.util.Log.d("GameFragment", "Game Over buttons - btnNewGame: ${binding.btnNewGame.isClickable}, btnRestartGameOver: ${binding.btnRestartGameOver.isClickable}")
        android.util.Log.d("GameFragment", "Game Over overlay visible: ${binding.layoutGameOver.visibility == View.VISIBLE}")
    }
    
    private fun startNewGame() {
        android.util.Log.d("GameFragment", "startNewGame() called - hiding overlay and starting new game")
        
        // Hide game over overlay
        binding.layoutGameOver.visibility = View.GONE
        binding.btnRestart.visibility = View.GONE
        binding.btnResume.visibility = View.GONE
        binding.btnPause.visibility = View.VISIBLE
        
        // Reset game state and start new game
        gameEngine.resetGame()
        startGame()
        
        android.util.Log.d("GameFragment", "startNewGame() completed")
    }
    
    override fun onDestroyView() {
        super.onDestroyView()
        gameEngine.endGame()
        _binding = null
    }
}
