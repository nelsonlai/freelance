package ca.medontime.blackjack.domain.model

/**
 * Represents a hand of cards held by either player or dealer
 */
data class Hand(
    val cards: MutableList<Card> = mutableListOf()
) {
    /**
     * Add a card to the hand
     */
    fun addCard(card: Card) {
        cards.add(card)
    }
    
    /**
     * Clear all cards from the hand
     */
    fun clear() {
        cards.clear()
    }
    
    /**
     * Get the total value of the hand according to BlackJack rules
     * Automatically adjusts Ace values to prevent busting
     */
    fun getTotalValue(): Int {
        var total = 0
        var aces = 0
        
        // First pass: count all non-Ace cards
        for (card in cards) {
            if (card.rank == Rank.ACE) {
                aces++
            } else {
                total += card.getValue()
            }
        }
        
        // Second pass: handle Aces
        for (i in 1..aces) {
            if (total + 11 <= 21) {
                total += 11
            } else {
                total += 1
            }
        }
        
        return total
    }
    
    /**
     * Check if the hand is busted (over 21)
     */
    fun isBusted(): Boolean = getTotalValue() > 21
    
    /**
     * Check if the hand is a BlackJack (exactly 21 with 2 cards)
     */
    fun isBlackJack(): Boolean = cards.size == 2 && getTotalValue() == 21
    
    /**
     * Check if the hand is empty
     */
    fun isEmpty(): Boolean = cards.isEmpty()
    
    /**
     * Get the number of cards in the hand
     */
    fun size(): Int = cards.size
}
