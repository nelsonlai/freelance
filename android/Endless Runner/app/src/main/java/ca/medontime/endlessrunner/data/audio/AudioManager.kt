package ca.medontime.endlessrunner.data.audio

import android.content.Context
import android.media.MediaPlayer
import android.media.SoundPool
class AudioManager {
    
    private var mediaPlayer: MediaPlayer? = null
    private var soundPool: SoundPool? = null
    private val soundMap = mutableMapOf<SoundType, Int>()
    
    private var isMusicEnabled = true
    private var isSoundEffectsEnabled = true
    
    fun initialize(context: Context) {
        // Initialize SoundPool for sound effects
        soundPool = SoundPool.Builder()
            .setMaxStreams(10)
            .build()
        
        // Load sound effects (placeholder IDs - would be actual sound files)
        soundMap[SoundType.COIN_COLLECT] = 1
        soundMap[SoundType.JUMP] = 2
        soundMap[SoundType.SLIDE] = 3
        soundMap[SoundType.COLLISION] = 4
        soundMap[SoundType.POWERUP] = 5
    }
    
    fun startBackgroundMusic(context: Context) {
        if (!isMusicEnabled) return
        
        // TODO: Add actual background music file to res/raw/ folder
        // For now, we'll skip background music until audio files are added
        // This prevents compilation errors
    }
    
    fun stopBackgroundMusic() {
        mediaPlayer?.stop()
        mediaPlayer?.release()
        mediaPlayer = null
    }
    
    fun pauseBackgroundMusic() {
        mediaPlayer?.pause()
    }
    
    fun resumeBackgroundMusic() {
        if (isMusicEnabled) {
            mediaPlayer?.start()
        }
    }
    
    fun playSoundEffect(soundType: SoundType) {
        if (!isSoundEffectsEnabled) return
        
        val soundId = soundMap[soundType] ?: return
        soundPool?.play(soundId, 1.0f, 1.0f, 1, 0, 1.0f)
    }
    
    fun setMusicEnabled(enabled: Boolean) {
        isMusicEnabled = enabled
        if (!enabled) {
            pauseBackgroundMusic()
        } else {
            resumeBackgroundMusic()
        }
    }
    
    fun setSoundEffectsEnabled(enabled: Boolean) {
        isSoundEffectsEnabled = enabled
    }
    
    fun release() {
        stopBackgroundMusic()
        soundPool?.release()
        soundPool = null
    }
}

enum class SoundType {
    COIN_COLLECT,
    JUMP,
    SLIDE,
    COLLISION,
    POWERUP
}
