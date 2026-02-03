package ca.medontime.blackjack.domain.model

/**
 * Represents the possible outcomes of a BlackJack game
 */
enum class GameResult {
    PLAYER_WINS,
    DEALER_WINS,
    PUSH, // Tie
    PLAYER_BLACKJACK,
    DEALER_BLACKJACK,
    PLAYER_BUST,
    DEALER_BUST
}

/**
 * Represents the current state of the game
 */
enum class GameState {
    DEALING,      // Initial deal of cards
    PLAYER_TURN,  // Player can hit or stand
    DEALER_TURN,  // Dealer is playing
    FINISHED      // Game is complete
}

/**
 * Represents the current game session
 */
data class Game(
    val playerHand: Hand = Hand(),
    val playerSplitHand: Hand? = null,
    val dealerHand: Hand = Hand(),
    val deck: MutableList<Card> = mutableListOf(),
    val state: GameState = GameState.DEALING,
    val result: GameResult? = null,
    val bet: Int = 100,
    val winnings: Int = 0,
    val isSplit: Boolean = false,
    val isDoubledDown: Boolean = false,
    val currentHand: Int = 0 // 0 = main hand, 1 = split hand
) {
    /**
     * Check if the game is finished
     */
    fun isFinished(): Boolean = state == GameState.FINISHED
    
    /**
     * Check if it's the player's turn
     */
    fun isPlayerTurn(): Boolean = state == GameState.PLAYER_TURN
    
    /**
     * Check if it's the dealer's turn
     */
    fun isDealerTurn(): Boolean = state == GameState.DEALER_TURN
    
    /**
     * Get the current active player hand
     */
    fun getCurrentPlayerHand(): Hand = if (currentHand == 1 && playerSplitHand != null) playerSplitHand else playerHand
    
    /**
     * Check if player can split (has two cards of same value and not already split)
     */
    fun canSplit(): Boolean {
        if (isSplit || playerHand.cards.size != 2) return false
        val card1 = playerHand.cards[0]
        val card2 = playerHand.cards[1]
        return card1.getValue() == card2.getValue()
    }
    
    /**
     * Check if player can double down (has exactly 2 cards in main hand, not already doubled down, and not in split hand)
     */
    fun canDoubleDown(): Boolean {
        return !isDoubledDown && 
               playerHand.cards.size == 2 && 
               state == GameState.PLAYER_TURN &&
               currentHand == 0 // Only allow on main hand, not split hand
    }
}
