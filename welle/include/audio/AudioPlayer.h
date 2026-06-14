#pragma once

#include "types/Song.h"
#include <miniaudio.h>

namespace welle::audio {
    class AudioPlayer {
    public:
        AudioPlayer() = default;
        static AudioPlayer& getInstance() {
            static AudioPlayer instance;
            return instance;
        }

        void initialize(const std::function<void(const medialib::types::Song&)>& downloadSong);
        void setAfterPlayCallback(const std::function<void()>& callback) { m_AfterPlayCallback = callback; }
        void play(const medialib::types::Song& song);
        void stop();

        medialib::types::Song getCurrentlyPlayingSong() { return m_CurrentlyPlayingSong; }
        float position() const;
        void seek(float position) const;

        const ma_sound* sound() const { return m_Sound.get(); }

        [[nodiscard]] bool stopRequested() const { return m_StopRequested; }

    private:
        ma_engine m_Engine{};
        std::unique_ptr<ma_sound> m_Sound{};
        std::atomic<bool> m_StopRequested{false};
        medialib::types::Song m_CurrentlyPlayingSong{};
        ma_resource_manager_config m_ResourceManagerConfig{};
        ma_resource_manager m_ResourceManager{};
        ma_engine_config m_EngineConfig{};
        std::function<void(const medialib::types::Song &)> m_DownloadSong{};
        std::function<void()> m_AfterPlayCallback{};
    };
}
