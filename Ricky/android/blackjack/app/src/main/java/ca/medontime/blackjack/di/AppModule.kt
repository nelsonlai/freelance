package ca.medontime.blackjack.di

import android.content.Context
import ca.medontime.blackjack.data.local.GameStatisticsDataSource
import ca.medontime.blackjack.data.repository.GameStatisticsRepositoryImpl
import ca.medontime.blackjack.domain.repository.GameStatisticsRepository
import ca.medontime.blackjack.domain.usecase.BlackJackGameUseCase

/**
 * Simple dependency injection module
 * In a real app, you would use Dagger Hilt or Koin
 */
object AppModule {
    
    private var gameUseCase: BlackJackGameUseCase? = null
    private var statisticsRepository: GameStatisticsRepository? = null
    
    fun getGameUseCase(): BlackJackGameUseCase {
        if (gameUseCase == null) {
            gameUseCase = BlackJackGameUseCase()
        }
        return gameUseCase!!
    }
    
    fun getStatisticsRepository(context: Context): GameStatisticsRepository {
        if (statisticsRepository == null) {
            val dataSource = GameStatisticsDataSource(context)
            statisticsRepository = GameStatisticsRepositoryImpl(dataSource)
        }
        return statisticsRepository!!
    }
}
