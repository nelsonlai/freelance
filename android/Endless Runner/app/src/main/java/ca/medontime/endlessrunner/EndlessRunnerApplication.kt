package ca.medontime.endlessrunner

import android.app.Application
import ca.medontime.endlessrunner.data.audio.AudioManager
import ca.medontime.endlessrunner.data.game.GameEngine
import ca.medontime.endlessrunner.data.repository.GameRepositoryImpl
import ca.medontime.endlessrunner.domain.repository.GameRepository
import ca.medontime.endlessrunner.domain.usecase.GameUseCase

class EndlessRunnerApplication : Application() {
    
    // Simple dependency injection (in a real app, you'd use Dagger/Hilt)
    lateinit var gameRepository: GameRepository
    lateinit var gameUseCase: GameUseCase
    lateinit var gameEngine: GameEngine
    lateinit var audioManager: AudioManager
    
    override fun onCreate() {
        super.onCreate()
        
        // Initialize dependencies
        gameRepository = GameRepositoryImpl()
        gameUseCase = GameUseCase(gameRepository)
        gameEngine = GameEngine()
        audioManager = AudioManager()
        
        // Initialize audio manager
        audioManager.initialize(this)
    }
}
