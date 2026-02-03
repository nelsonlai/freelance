package ca.medontime.endlessrunner.ui.home

import androidx.navigation.ActionOnlyNavDirections
import androidx.navigation.NavDirections
import ca.medontime.endlessrunner.R

public class HomeFragmentDirections private constructor() {
  public companion object {
    public fun actionHomeFragmentToGameFragment(): NavDirections =
        ActionOnlyNavDirections(R.id.action_homeFragment_to_gameFragment)
    
    public fun actionHomeFragmentToProfileFragment(): NavDirections =
        ActionOnlyNavDirections(R.id.action_homeFragment_to_profileFragment)
    
    public fun actionHomeFragmentToSettingsFragment(): NavDirections =
        ActionOnlyNavDirections(R.id.action_homeFragment_to_settingsFragment)
  }
}
