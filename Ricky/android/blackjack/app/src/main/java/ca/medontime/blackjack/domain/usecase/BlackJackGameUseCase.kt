package ca.medontime.blackjack.domain.usecase

import ca.medontime.blackjack.domain.model.*

/**
 * Use case for managing BlackJack game logic
 */
class BlackJackGameUseCase {
    
    /**
     * Create a standard 52-card deck
     */
    fun createDeck(): MutableList<Card> {
        val deck = mutableListOf<Card>()
        
        for (suit in Suit.values()) {
            for (rank in Rank.values()) {
                deck.add(Card(suit, rank))
            }
        }
        
        return deck
    }
    
    /**
     * Shuffle the deck using Fisher-Yates algorithm
     */
    fun shuffleDeck(deck: MutableList<Card>) {
        for (i in deck.size - 1 downTo 1) {
            val j = (0..i).random()
            deck[i] = deck[j].also { deck[j] = deck[i] }
        }
    }
    
    /**
     * Deal initial cards to player and dealer
     */
    fun dealInitialCards(game: Game): Game {
        val newPlayerHand = Hand()
        val newDealerHand = Hand()
        val newDeck = game.deck.toMutableList()
        
        // Deal two cards to player
        newPlayerHand.addCard(newDeck.removeAt(0))
        newPlayerHand.addCard(newDeck.removeAt(0))
        
        // Deal two cards to dealer (one face down)
        newDealerHand.addCard(newDeck.removeAt(0))
        newDealerHand.addCard(newDeck.removeAt(0))
        
        return game.copy(
            playerHand = newPlayerHand,
            dealerHand = newDealerHand,
            deck = newDeck,
            state = GameState.PLAYER_TURN
        )
    }
    
    /**
     * Player hits (takes another card)
     */
    fun playerHit(game: Game): Game {
        if (game.state != GameState.PLAYER_TURN || game.deck.isEmpty()) {
            return game
        }
        
        val newPlayerHand = Hand(game.playerHand.cards.toMutableList())
        val newDeck = game.deck.toMutableList()
        
        newPlayerHand.addCard(newDeck.removeAt(0))
        
        val newState = if (newPlayerHand.isBusted()) {
            GameState.FINISHED
        } else {
            GameState.PLAYER_TURN
        }
        
        return game.copy(
            playerHand = newPlayerHand,
            deck = newDeck,
            state = newState
        )
    }
    
    /**
     * Player stands (ends their turn)
     */
    fun playerStand(game: Game): Game {
        if (game.state != GameState.PLAYER_TURN) {
            return game
        }
        
        return game.copy(state = GameState.DEALER_TURN)
    }
    
    /**
     * Dealer plays according to standard rules (hit on 16 or less, stand on 17 or more)
     */
    fun dealerPlay(game: Game): Game {
        if (game.state != GameState.DEALER_TURN) {
            return game
        }
        
        var newDealerHand = Hand(game.dealerHand.cards.toMutableList())
        var newDeck = game.deck.toMutableList()
        
        // Dealer must hit until they have 17 or more
        while (newDealerHand.getTotalValue() < 17 && newDeck.isNotEmpty()) {
            newDealerHand.addCard(newDeck.removeAt(0))
        }
        
        return game.copy(
            dealerHand = newDealerHand,
            deck = newDeck,
            state = GameState.FINISHED
        )
    }
    
    /**
     * Determine the game result
     */
    fun determineGameResult(playerHand: Hand, dealerHand: Hand): GameResult {
        val playerValue = playerHand.getTotalValue()
        val dealerValue = dealerHand.getTotalValue()
        
        // Check for BlackJacks first
        if (playerHand.isBlackJack() && dealerHand.isBlackJack()) {
            return GameResult.PUSH
        } else if (playerHand.isBlackJack()) {
            return GameResult.PLAYER_BLACKJACK
        } else if (dealerHand.isBlackJack()) {
            return GameResult.DEALER_BLACKJACK
        }
        
        // Check for busts
        if (playerHand.isBusted()) {
            return GameResult.PLAYER_BUST
        } else if (dealerHand.isBusted()) {
            return GameResult.DEALER_BUST
        }
        
        // Compare values
        return when {
            playerValue > dealerValue -> GameResult.PLAYER_WINS
            dealerValue > playerValue -> GameResult.DEALER_WINS
            else -> GameResult.PUSH
        }
    }
    
    /**
     * Calculate winnings based on game result and bet
     */
    fun calculateWinnings(result: GameResult, bet: Int): Int {
        return when (result) {
            GameResult.PLAYER_WINS -> bet
            GameResult.PLAYER_BLACKJACK -> (bet * 1.5).toInt()
            GameResult.DEALER_BUST -> bet
            GameResult.PUSH -> 0
            else -> 0
        }
    }
    
    /**
     * Player splits their hand (if they have two cards of the same value)
     */
    fun playerSplit(game: Game): Game {
        if (!game.canSplit() || game.deck.size < 2) {
            return game
        }
        
        val newDeck = game.deck.toMutableList()
        val firstCard = game.playerHand.cards[0]
        val secondCard = game.playerHand.cards[1]
        
        // Create split hand with second card
        val splitHand = Hand(mutableListOf(secondCard))
        
        // Update main hand to only have first card
        val newPlayerHand = Hand(mutableListOf(firstCard))
        
        // Deal one card to each hand
        newPlayerHand.addCard(newDeck.removeAt(0))
        splitHand.addCard(newDeck.removeAt(0))
        
        return game.copy(
            playerHand = newPlayerHand,
            playerSplitHand = splitHand,
            deck = newDeck,
            isSplit = true,
            state = GameState.PLAYER_TURN,
            currentHand = 0
        )
    }
    
    /**
     * Player doubles down (doubles bet and takes exactly one more card)
     * Only allowed on main hand after first two cards
     */
    fun playerDoubleDown(game: Game): Game {
        if (!game.canDoubleDown() || game.deck.isEmpty()) {
            return game
        }
        
        // Double down only works on main hand (currentHand == 0)
        val newPlayerHand = Hand(game.playerHand.cards.toMutableList())
        val newDeck = game.deck.toMutableList()
        
        // Add exactly one card
        newPlayerHand.addCard(newDeck.removeAt(0))
        
        // Double the bet
        val newBet = game.bet * 2
        
        // Update main hand and end player turn
        return game.copy(
            playerHand = newPlayerHand,
            deck = newDeck,
            bet = newBet,
            isDoubledDown = true,
            state = GameState.DEALER_TURN
        )
    }
    
    /**
     * Switch to the next hand (for split hands)
     */
    fun switchToNextHand(game: Game): Game {
        if (!game.isSplit || game.currentHand != 0) {
            return game
        }
        
        return game.copy(currentHand = 1, state = GameState.PLAYER_TURN)
    }
    
    /**
     * Determine the game result for split hands
     */
    fun determineSplitGameResult(game: Game): List<GameResult> {
        val results = mutableListOf<GameResult>()
        
        // Check main hand
        results.add(determineGameResult(game.playerHand, game.dealerHand))
        
        // Check split hand if it exists
        if (game.playerSplitHand != null) {
            results.add(determineGameResult(game.playerSplitHand, game.dealerHand))
        }
        
        return results
    }
    
    /**
     * Calculate total winnings for split hands
     */
    fun calculateSplitWinnings(game: Game): Int {
        val results = determineSplitGameResult(game)
        var totalWinnings = 0
        
        results.forEach { result ->
            totalWinnings += calculateWinnings(result, game.bet)
        }
        
        return totalWinnings
    }
    
    /**
     * Start a new game
     */
    fun startNewGame(): Game {
        val deck = createDeck()
        shuffleDeck(deck)
        
        return Game(
            deck = deck,
            state = GameState.DEALING,
            bet = 100,
            winnings = 0
        )
    }
}
