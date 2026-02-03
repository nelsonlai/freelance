package ca.medontime.blackjack.ui.dashboard

import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Button
import android.widget.ProgressBar
import android.widget.TextView
import androidx.fragment.app.Fragment
import androidx.lifecycle.lifecycleScope
import androidx.lifecycle.repeatOnLifecycle
import kotlinx.coroutines.launch
import ca.medontime.blackjack.databinding.FragmentStatisticsBinding
import ca.medontime.blackjack.di.AppModule
import ca.medontime.blackjack.ui.screens.statistics.StatisticsViewModel
import ca.medontime.blackjack.ui.screens.statistics.TimePeriod

class DashboardFragment : Fragment() {

    private var _binding: FragmentStatisticsBinding? = null
    private val binding get() = _binding!!
    
    private lateinit var statisticsViewModel: StatisticsViewModel
    
    // UI Components
    private lateinit var winLossProgress: ProgressBar
    private lateinit var winPercentage: TextView
    private lateinit var totalWins: TextView
    private lateinit var totalLosses: TextView
    private lateinit var allTimeButton: Button
    private lateinit var pastWeekButton: Button
    private lateinit var pastMonthButton: Button
    private lateinit var highestScore: TextView
    private lateinit var totalGames: TextView
    private lateinit var averageScore: TextView
    private lateinit var currentStreak: TextView

    override fun onCreateView(
        inflater: LayoutInflater,
        container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View {
        _binding = FragmentStatisticsBinding.inflate(inflater, container, false)
        val root: View = binding.root
        
        initializeViews()
        setupViewModel()
        setupClickListeners()
        observeStatistics()
        
        return root
    }
    
    private fun initializeViews() {
        winLossProgress = binding.winLossProgress
        winPercentage = binding.winPercentage
        totalWins = binding.totalWins
        totalLosses = binding.totalLosses
        allTimeButton = binding.allTimeButton
        pastWeekButton = binding.pastWeekButton
        pastMonthButton = binding.pastMonthButton
        highestScore = binding.highestScore
        totalGames = binding.totalGames
        averageScore = binding.averageScore
        currentStreak = binding.currentStreak
    }
    
    private fun setupViewModel() {
        val statisticsRepository = AppModule.getStatisticsRepository(requireContext())
        statisticsViewModel = StatisticsViewModel(statisticsRepository)
    }
    
    private fun setupClickListeners() {
        allTimeButton.setOnClickListener {
            statisticsViewModel.updateTimePeriod(TimePeriod.ALL_TIME)
            updateTimePeriodButtons(TimePeriod.ALL_TIME)
        }
        
        pastWeekButton.setOnClickListener {
            statisticsViewModel.updateTimePeriod(TimePeriod.PAST_WEEK)
            updateTimePeriodButtons(TimePeriod.PAST_WEEK)
        }
        
        pastMonthButton.setOnClickListener {
            statisticsViewModel.updateTimePeriod(TimePeriod.PAST_MONTH)
            updateTimePeriodButtons(TimePeriod.PAST_MONTH)
        }
    }
    
    private fun observeStatistics() {
        viewLifecycleOwner.lifecycleScope.launch {
            repeatOnLifecycle(androidx.lifecycle.Lifecycle.State.STARTED) {
                statisticsViewModel.statistics.collect { stats ->
                    updateStatisticsUI(stats)
                }
            }
        }
    }
    
    private fun updateStatisticsUI(stats: ca.medontime.blackjack.domain.model.GameStatistics) {
        // Update win/loss progress bar
        val winPercentage = stats.getWinPercentage().toInt()
        winLossProgress.progress = winPercentage
        
        // Update text values
        this.winPercentage.text = stats.getWinPercentageString()
        totalWins.text = stats.gamesWon.toString()
        totalLosses.text = stats.gamesLost.toString()
        highestScore.text = stats.highestScore.toString()
        totalGames.text = stats.gamesPlayed.toString()
        averageScore.text = stats.getAverageScoreString()
        currentStreak.text = stats.getCurrentStreakString()
        
        // Update colors for positive metrics
        this.winPercentage.setTextColor(resources.getColor(android.R.color.holo_green_light, null))
        highestScore.setTextColor(resources.getColor(android.R.color.holo_green_light, null))
        
        if (stats.isWinningStreak) {
            currentStreak.setTextColor(resources.getColor(android.R.color.holo_green_light, null))
        } else {
            currentStreak.setTextColor(resources.getColor(android.R.color.holo_red_light, null))
        }
    }
    
    private fun updateTimePeriodButtons(selectedPeriod: TimePeriod) {
        // Reset all buttons to dark background
        allTimeButton.setBackgroundResource(ca.medontime.blackjack.R.drawable.button_dark_background)
        pastWeekButton.setBackgroundResource(ca.medontime.blackjack.R.drawable.button_dark_background)
        pastMonthButton.setBackgroundResource(ca.medontime.blackjack.R.drawable.button_dark_background)
        
        // Set selected button to green background
        when (selectedPeriod) {
            TimePeriod.ALL_TIME -> allTimeButton.setBackgroundResource(ca.medontime.blackjack.R.drawable.button_green_background)
            TimePeriod.PAST_WEEK -> pastWeekButton.setBackgroundResource(ca.medontime.blackjack.R.drawable.button_green_background)
            TimePeriod.PAST_MONTH -> pastMonthButton.setBackgroundResource(ca.medontime.blackjack.R.drawable.button_green_background)
        }
    }

    override fun onDestroyView() {
        super.onDestroyView()
        _binding = null
    }
}