package ca.medontime.blackjack.domain.model

/**
 * Represents a playing card with suit and rank
 */
data class Card(
    val suit: Suit,
    val rank: Rank
) {
    /**
     * Get the value of the card according to BlackJack rules
     * Ace can be 1 or 11, Face cards are 10, Number cards are their face value
     */
    fun getValue(): Int = when (rank) {
        Rank.ACE -> 11 // Will be adjusted to 1 if needed in hand calculation
        Rank.JACK, Rank.QUEEN, Rank.KING -> 10
        else -> rank.value
    }
    
    /**
     * Get the image resource name for this card
     * Format: "card_{rank}_of_{suit}" (all lowercase, no extension)
     */
    fun getImageResourceName(): String {
        val rankName = when (rank) {
            Rank.ACE -> "a"
            Rank.JACK -> "j"
            Rank.QUEEN -> "q"
            Rank.KING -> "k"
            else -> rank.value.toString()
        }
        val suitName = suit.name.lowercase()
        return "card_${rankName}_of_${suitName}"
    }
}

/**
 * Card suits
 */
enum class Suit {
    CLUBS, DIAMONDS, HEARTS, SPADES
}

/**
 * Card ranks with their numeric values
 */
enum class Rank(val value: Int) {
    ACE(1),
    TWO(2), THREE(3), FOUR(4), FIVE(5), SIX(6), SEVEN(7), EIGHT(8), NINE(9), TEN(10),
    JACK(11), QUEEN(12), KING(13)
}
