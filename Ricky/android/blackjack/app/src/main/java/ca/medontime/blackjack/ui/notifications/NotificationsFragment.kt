package ca.medontime.blackjack.ui.notifications

import android.app.AlertDialog
import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Button
import android.widget.ImageView
import androidx.fragment.app.Fragment
import androidx.lifecycle.lifecycleScope
import androidx.navigation.fragment.findNavController
import ca.medontime.blackjack.databinding.FragmentNotificationsBinding
import ca.medontime.blackjack.di.AppModule
import kotlinx.coroutines.launch

class NotificationsFragment : Fragment() {

    private var _binding: FragmentNotificationsBinding? = null
    private val binding get() = _binding!!

    override fun onCreateView(
        inflater: LayoutInflater,
        container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View {
        _binding = FragmentNotificationsBinding.inflate(inflater, container, false)
        val root: View = binding.root
        
        setupClickListeners()
        
        return root
    }
    
    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)
        
        // Handle system back button
        view.isFocusableInTouchMode = true
        view.requestFocus()
        view.setOnKeyListener { _, keyCode, event ->
            if (keyCode == android.view.KeyEvent.KEYCODE_BACK && event.action == android.view.KeyEvent.ACTION_UP) {
                navigateBack()
                true
            } else {
                false
            }
        }
    }
    
    private fun setupClickListeners() {
        binding.resetStatisticsButton.setOnClickListener {
            showResetConfirmationDialog()
        }
        
        binding.backArrow.setOnClickListener {
            navigateBack()
        }
    }
    
    private fun showResetConfirmationDialog() {
        AlertDialog.Builder(requireContext())
            .setTitle("Reset Statistics")
            .setMessage("Are you sure you want to reset all game statistics? This action cannot be undone.")
            .setPositiveButton("Reset") { _, _ ->
                resetStatistics()
            }
            .setNegativeButton("Cancel", null)
            .show()
    }
    
    private fun resetStatistics() {
        lifecycleScope.launch {
            val statisticsRepository = AppModule.getStatisticsRepository(requireContext())
            statisticsRepository.resetStatistics()
            
            // Show confirmation message
            AlertDialog.Builder(requireContext())
                .setTitle("Statistics Reset")
                .setMessage("All game statistics have been reset successfully.")
                .setPositiveButton("OK", null)
                .show()
        }
    }
    
    private fun navigateBack() {
        // Navigate back to the previous screen (Game screen)
        findNavController().navigateUp()
    }

    override fun onDestroyView() {
        super.onDestroyView()
        _binding = null
    }
}