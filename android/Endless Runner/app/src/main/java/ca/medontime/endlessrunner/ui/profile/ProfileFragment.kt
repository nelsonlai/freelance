package ca.medontime.endlessrunner.ui.profile

import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import androidx.fragment.app.Fragment
import ca.medontime.endlessrunner.databinding.FragmentProfileBinding

class ProfileFragment : Fragment() {
    
    private var _binding: FragmentProfileBinding? = null
    private val binding get() = _binding!!
    
    override fun onCreateView(
        inflater: LayoutInflater,
        container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View {
        _binding = FragmentProfileBinding.inflate(inflater, container, false)
        return binding.root
    }
    
    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)
        setupProfile()
    }
    
    private fun setupProfile() {
        // TODO: Implement profile functionality
        binding.tvProfileName.text = "Player"
        binding.tvTotalScore.text = "Total Score: 0"
        binding.tvTotalCoins.text = "Total Coins: 0"
        binding.tvGamesPlayed.text = "Games Played: 0"
    }
    
    override fun onDestroyView() {
        super.onDestroyView()
        _binding = null
    }
}
