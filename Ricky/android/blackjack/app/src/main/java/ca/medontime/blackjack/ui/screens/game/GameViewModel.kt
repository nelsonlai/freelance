package ca.medontime.blackjack.ui.screens.game

import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import ca.medontime.blackjack.domain.model.*
import ca.medontime.blackjack.domain.repository.GameStatisticsRepository
import ca.medontime.blackjack.domain.usecase.BlackJackGameUseCase
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.StateFlow
import kotlinx.coroutines.flow.asStateFlow
import kotlinx.coroutines.launch

/**
 * ViewModel for the Game screen
 */
class GameViewModel(
    private val gameUseCase: BlackJackGameUseCase,
    private val statisticsRepository: GameStatisticsRepository
) : ViewModel() {
    
    private val _gameState = MutableStateFlow(Game())
    val gameState: StateFlow<Game> = _gameState.asStateFlow()
    
    private val _gameMessage = MutableStateFlow("")
    val gameMessage: StateFlow<String> = _gameMessage.asStateFlow()
    
    init {
        initializeGame()
    }
    
    /**
     * Initialize a new game (empty table)
     */
    fun initializeGame() {
        val newGame = gameUseCase.startNewGame()
        _gameState.value = newGame
        _gameMessage.value = "Place your bet and click Deal to start"
    }
    
    /**
     * Start a new game with initial cards
     */
    fun startNewGame() {
        // Create a completely fresh game to reset all flags
        val freshGame = gameUseCase.startNewGame()
        val gameWithCards = gameUseCase.dealInitialCards(freshGame)
        _gameState.value = gameWithCards
        _gameMessage.value = "Choose Hit or Stand"
    }
    
    /**
     * Player hits (takes another card)
     */
    fun playerHit() {
        val currentGame = _gameState.value
        if (currentGame.isPlayerTurn()) {
            val updatedGame = gameUseCase.playerHit(currentGame)
            _gameState.value = updatedGame
            
            if (updatedGame.isFinished()) {
                finishGame(updatedGame)
            } else {
                _gameMessage.value = "Choose Hit or Stand"
            }
        }
    }
    
    /**
     * Player stands (ends their turn)
     */
    fun playerStand() {
        val currentGame = _gameState.value
        if (currentGame.isPlayerTurn()) {
            if (currentGame.isSplit && currentGame.currentHand == 0) {
                // Switch to split hand
                val gameAfterStand = gameUseCase.switchToNextHand(currentGame)
                _gameState.value = gameAfterStand
                _gameMessage.value = "Playing split hand - Choose Hit or Stand"
            } else {
                // End player turn and let dealer play
                val gameAfterStand = gameUseCase.playerStand(currentGame)
                val finalGame = gameUseCase.dealerPlay(gameAfterStand)
                _gameState.value = finalGame
                finishGame(finalGame)
            }
        }
    }
    
    /**
     * Player splits their hand
     */
    fun playerSplit() {
        val currentGame = _gameState.value
        if (currentGame.canSplit()) {
            val updatedGame = gameUseCase.playerSplit(currentGame)
            _gameState.value = updatedGame
            _gameMessage.value = "Hand split! Playing first hand - Choose Hit or Stand"
        }
    }
    
    /**
     * Player doubles down
     */
    fun playerDoubleDown() {
        val currentGame = _gameState.value
        if (currentGame.canDoubleDown()) {
            val updatedGame = gameUseCase.playerDoubleDown(currentGame)
            _gameState.value = updatedGame
            _gameMessage.value = "Doubled down! Dealer's turn..."
            
            // After doubling down, dealer plays immediately
            val finalGame = gameUseCase.dealerPlay(updatedGame)
            _gameState.value = finalGame
            finishGame(finalGame)
        }
    }
    
    /**
     * Deal new cards (start new game)
     */
    fun deal() {
        startNewGame()
    }
    
    /**
     * Update bet amount
     */
    fun updateBet(newBet: Int) {
        val currentGame = _gameState.value
        val updatedGame = currentGame.copy(bet = newBet)
        _gameState.value = updatedGame
    }
    
    /**
     * Finish the game and update statistics
     */
    private fun finishGame(game: Game) {
        val result: GameResult
        val winnings: Int
        
        if (game.isSplit) {
            // Handle split hands
            val results = gameUseCase.determineSplitGameResult(game)
            winnings = gameUseCase.calculateSplitWinnings(game)
            
            // Use the first result for display purposes
            result = results.first()
            
            // Update game message for split hands
            _gameMessage.value = when {
                results.all { it == GameResult.PLAYER_WINS } -> "Both hands win!"
                results.all { it == GameResult.DEALER_WINS } -> "Both hands lose!"
                results.any { it == GameResult.PLAYER_WINS } && results.any { it == GameResult.DEALER_WINS } -> "Mixed results!"
                else -> "Push on both hands!"
            }
        } else {
            // Handle single hand
            result = gameUseCase.determineGameResult(game.playerHand, game.dealerHand)
            winnings = gameUseCase.calculateWinnings(result, game.bet)
            
            // Update game message based on result
            _gameMessage.value = when (result) {
                GameResult.PLAYER_WINS -> "You Win!"
                GameResult.DEALER_WINS -> "Dealer Wins!"
                GameResult.PUSH -> "Push (Tie)!"
                GameResult.PLAYER_BLACKJACK -> "BlackJack! You Win!"
                GameResult.DEALER_BLACKJACK -> "Dealer BlackJack!"
                GameResult.PLAYER_BUST -> "Bust! You Lose!"
                GameResult.DEALER_BUST -> "Dealer Bust! You Win!"
            }
        }
        
        val finalGame = game.copy(
            result = result,
            winnings = winnings
        )
        _gameState.value = finalGame
        
        // Update statistics
        viewModelScope.launch {
            statisticsRepository.updateStatisticsFromGameResult(
                result = result,
                playerScore = game.playerHand.getTotalValue(),
                isBlackJack = game.playerHand.isBlackJack()
            )
        }
    }
    
    /**
     * Get the current game status message
     */
    fun getGameStatusMessage(): String {
        val game = _gameState.value
        return when {
            game.isFinished() -> _gameMessage.value
            game.isPlayerTurn() -> {
                if (game.isSplit) {
                    "Hand ${game.currentHand + 1} - Hit or Stand?"
                } else {
                    "Your turn - Hit or Stand?"
                }
            }
            game.isDealerTurn() -> "Dealer's turn..."
            else -> "Dealing cards..."
        }
    }
    
    /**
     * Check if split button should be enabled
     */
    fun canSplit(): Boolean {
        return _gameState.value.canSplit()
    }
    
    /**
     * Check if double down button should be enabled
     */
    fun canDoubleDown(): Boolean {
        return _gameState.value.canDoubleDown()
    }
}
