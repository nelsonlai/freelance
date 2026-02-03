package ca.medontime.blackjack.ui.home

import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Button
import android.widget.ImageView
import android.widget.LinearLayout
import android.widget.TextView
import androidx.fragment.app.Fragment
import androidx.lifecycle.ViewModelProvider
import androidx.lifecycle.lifecycleScope
import androidx.lifecycle.repeatOnLifecycle
import androidx.navigation.fragment.findNavController
import kotlinx.coroutines.launch
import ca.medontime.blackjack.R
import ca.medontime.blackjack.di.AppModule
import ca.medontime.blackjack.domain.model.Card
import ca.medontime.blackjack.domain.model.Suit
import ca.medontime.blackjack.domain.model.Rank
import ca.medontime.blackjack.databinding.FragmentHomeBinding
import ca.medontime.blackjack.ui.screens.game.GameViewModel

class HomeFragment : Fragment() {

    private var _binding: FragmentHomeBinding? = null
    private val binding get() = _binding!!
    
    private lateinit var gameViewModel: GameViewModel
    
    // UI Components
    private lateinit var dealerCard1: ImageView
    private lateinit var dealerCard2: ImageView
    private lateinit var dealerCard3: ImageView
    private lateinit var dealerCard4: ImageView
    private lateinit var dealerCard5: ImageView
    private lateinit var playerCard1: ImageView
    private lateinit var playerCard2: ImageView
    private lateinit var playerCard3: ImageView
    private lateinit var playerCard4: ImageView
    private lateinit var playerCard5: ImageView
    private lateinit var playerSplitCard1: ImageView
    private lateinit var playerSplitCard2: ImageView
    private lateinit var playerSplitCard3: ImageView
    private lateinit var playerSplitCard4: ImageView
    private lateinit var playerSplitCard5: ImageView
    private lateinit var dealerValue: TextView
    private lateinit var playerValue: TextView
    private lateinit var playerSplitValue: TextView
    private lateinit var betAmount: TextView
    private lateinit var currentBetDisplay: TextView
    private lateinit var winningsAmount: TextView
    private lateinit var hitButton: Button
    private lateinit var standButton: Button
    private lateinit var splitButton: Button
    private lateinit var doubleDownButton: Button
    private lateinit var dealButton: Button
    private lateinit var betMinusButton: Button
    private lateinit var betPlusButton: Button
    private lateinit var gameStatus: TextView
    private lateinit var playerSplitSection: LinearLayout
    
    // Game state
    private var currentBet = 100

    override fun onCreateView(
        inflater: LayoutInflater,
        container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View {
        _binding = FragmentHomeBinding.inflate(inflater, container, false)
        val root: View = binding.root
        
        initializeViews()
        setupViewModel()
        setupClickListeners()
        observeGameState()
        updateBetDisplay() // Initialize bet display
        hideAllCards() // Ensure cards are hidden initially
        
        return root
    }
    
    private fun initializeViews() {
        dealerCard1 = binding.dealerCard1
        dealerCard2 = binding.dealerCard2
        dealerCard3 = binding.dealerCard3
        dealerCard4 = binding.dealerCard4
        dealerCard5 = binding.dealerCard5
        playerCard1 = binding.playerCard1
        playerCard2 = binding.playerCard2
        playerCard3 = binding.playerCard3
        playerCard4 = binding.playerCard4
        playerCard5 = binding.playerCard5
        playerSplitCard1 = binding.playerSplitCard1
        playerSplitCard2 = binding.playerSplitCard2
        playerSplitCard3 = binding.playerSplitCard3
        playerSplitCard4 = binding.playerSplitCard4
        playerSplitCard5 = binding.playerSplitCard5
        dealerValue = binding.dealerValue
        playerValue = binding.playerValue
        playerSplitValue = binding.playerSplitValue
        betAmount = binding.betAmount
        currentBetDisplay = binding.currentBetDisplay
        winningsAmount = binding.winningsAmount
        hitButton = binding.hitButton
        standButton = binding.standButton
        splitButton = binding.splitButton
        doubleDownButton = binding.doubleDownButton
        dealButton = binding.dealButton
        betMinusButton = binding.betMinusButton
        betPlusButton = binding.betPlusButton
        gameStatus = binding.gameStatus
        playerSplitSection = binding.playerSplitSection
    }
    
    private fun setupViewModel() {
        val gameUseCase = AppModule.getGameUseCase()
        val statisticsRepository = AppModule.getStatisticsRepository(requireContext())
        
        gameViewModel = GameViewModel(gameUseCase, statisticsRepository)
    }
    
    private fun setupClickListeners() {
        hitButton.setOnClickListener {
            gameViewModel.playerHit()
        }
        
        standButton.setOnClickListener {
            gameViewModel.playerStand()
        }
        
        splitButton.setOnClickListener {
            gameViewModel.playerSplit()
        }
        
        doubleDownButton.setOnClickListener {
            gameViewModel.playerDoubleDown()
        }
        
        dealButton.setOnClickListener {
            gameViewModel.deal()
        }
        
        betMinusButton.setOnClickListener {
            if (currentBet > 10) {
                currentBet -= 10
                updateBetDisplay()
                gameViewModel.updateBet(currentBet)
            }
        }
        
        betPlusButton.setOnClickListener {
            if (currentBet < 1000) {
                currentBet += 10
                updateBetDisplay()
                gameViewModel.updateBet(currentBet)
            }
        }
    }
    
    private fun observeGameState() {
        viewLifecycleOwner.lifecycleScope.launch {
            repeatOnLifecycle(androidx.lifecycle.Lifecycle.State.STARTED) {
                gameViewModel.gameState.collect { game ->
                    updateUI(game)
                }
            }
        }
        
        viewLifecycleOwner.lifecycleScope.launch {
            repeatOnLifecycle(androidx.lifecycle.Lifecycle.State.STARTED) {
                gameViewModel.gameMessage.collect { message ->
                    gameStatus.text = message
                }
            }
        }
    }
    
    private fun updateUI(game: ca.medontime.blackjack.domain.model.Game) {
        // Check if game has started (has cards)
        val gameStarted = game.playerHand.cards.isNotEmpty() || game.dealerHand.cards.isNotEmpty()
        
        if (gameStarted) {
            // Update dealer cards
            updateDealerCards(game.dealerHand)
            
            // Update player cards
            updatePlayerCards(game.playerHand)
            
            // Update split hand if it exists
            if (game.isSplit && game.playerSplitHand != null) {
                updatePlayerSplitCards(game.playerSplitHand)
                playerSplitSection.visibility = View.VISIBLE
                playerSplitValue.text = "Value: ${game.playerSplitHand.getTotalValue()}"
            } else {
                playerSplitSection.visibility = View.GONE
            }
            
            // Update values
            dealerValue.text = "Value: ${if (game.isFinished()) game.dealerHand.getTotalValue() else "?"}"
            playerValue.text = "Value: ${game.playerHand.getTotalValue()}"
        } else {
            // Empty table - hide cards
            hideAllCards()
            playerSplitSection.visibility = View.GONE
            dealerValue.text = "Value: ?"
            playerValue.text = "Value: 0"
        }
        
        // Update bet and winnings
        betAmount.text = "$${game.bet}"
        currentBetDisplay.text = "$${game.bet}"
        winningsAmount.text = "$${game.winnings}"
        
        // Update button states
        val isPlayerTurn = game.isPlayerTurn()
        val gameFinished = game.isFinished()
        
        hitButton.isEnabled = isPlayerTurn
        standButton.isEnabled = isPlayerTurn
        splitButton.isEnabled = isPlayerTurn && gameViewModel.canSplit()
        doubleDownButton.isEnabled = isPlayerTurn && gameViewModel.canDoubleDown()
        dealButton.isEnabled = gameFinished || !gameStarted
        
        // Enable/disable bet controls based on game state
        betMinusButton.isEnabled = !gameStarted || gameFinished
        betPlusButton.isEnabled = !gameStarted || gameFinished
        
        // Update game status
        gameStatus.text = gameViewModel.getGameStatusMessage()
    }
    
    private fun updateDealerCards(hand: ca.medontime.blackjack.domain.model.Hand) {
        val cards = hand.cards
        val cardViews = listOf(dealerCard1, dealerCard2, dealerCard3, dealerCard4, dealerCard5)
        
        // Hide all cards first
        cardViews.forEach { it.visibility = View.INVISIBLE }
        
        // Show cards based on hand size
        cards.forEachIndexed { index, card ->
            if (index < cardViews.size) {
                cardViews[index].visibility = View.VISIBLE
                if (index == 1 && !gameViewModel.gameState.value.isFinished()) {
                    // Second dealer card is face down during player turn
                    cardViews[index].setImageResource(R.drawable.cover)
                } else {
                    // All other cards are face up
                    setCardImage(cardViews[index], card)
                }
            }
        }
    }
    
    private fun updatePlayerCards(hand: ca.medontime.blackjack.domain.model.Hand) {
        val cards = hand.cards
        val cardViews = listOf(playerCard1, playerCard2, playerCard3, playerCard4, playerCard5)
        
        // Hide all cards first
        cardViews.forEach { it.visibility = View.INVISIBLE }
        
        // Show cards based on hand size - all player cards are face up
        cards.forEachIndexed { index, card ->
            if (index < cardViews.size) {
                cardViews[index].visibility = View.VISIBLE
                setCardImage(cardViews[index], card)
            }
        }
    }
    
    private fun setCardImage(imageView: ImageView, card: Card) {
        val resourceName = card.getImageResourceName()
        val resourceId = getCardResourceId(resourceName)
        imageView.setImageResource(resourceId)
        
        // Debug logging
        android.util.Log.d("CardDisplay", "Card: ${card.rank} of ${card.suit} -> Resource: $resourceName -> ID: $resourceId")
    }
    
    private fun getCardResourceId(resourceName: String): Int {
        val resourceId = resources.getIdentifier(resourceName, "drawable", requireContext().packageName)
        if (resourceId == 0) {
            // Fallback to cover if resource not found
            return R.drawable.cover
        }
        return resourceId
    }
    
    private fun updatePlayerSplitCards(hand: ca.medontime.blackjack.domain.model.Hand) {
        val cards = hand.cards
        val cardViews = listOf(playerSplitCard1, playerSplitCard2, playerSplitCard3, playerSplitCard4, playerSplitCard5)
        
        // Hide all cards first
        cardViews.forEach { it.visibility = View.INVISIBLE }
        
        // Show cards based on hand size - all split cards are face up
        cards.forEachIndexed { index, card ->
            if (index < cardViews.size) {
                cardViews[index].visibility = View.VISIBLE
                setCardImage(cardViews[index], card)
            }
        }
    }
    
    private fun hideAllCards() {
        dealerCard1.visibility = View.INVISIBLE
        dealerCard2.visibility = View.INVISIBLE
        dealerCard3.visibility = View.INVISIBLE
        dealerCard4.visibility = View.INVISIBLE
        dealerCard5.visibility = View.INVISIBLE
        playerCard1.visibility = View.INVISIBLE
        playerCard2.visibility = View.INVISIBLE
        playerCard3.visibility = View.INVISIBLE
        playerCard4.visibility = View.INVISIBLE
        playerCard5.visibility = View.INVISIBLE
        playerSplitCard1.visibility = View.INVISIBLE
        playerSplitCard2.visibility = View.INVISIBLE
        playerSplitCard3.visibility = View.INVISIBLE
        playerSplitCard4.visibility = View.INVISIBLE
        playerSplitCard5.visibility = View.INVISIBLE
    }
    
    private fun updateBetDisplay() {
        betAmount.text = "$$currentBet"
        currentBetDisplay.text = "$$currentBet"
    }
    
    override fun onDestroyView() {
        super.onDestroyView()
        _binding = null
    }
}