#include <iostream>
#include <QDir>
#include <audio/AudioPlayer.h>

#include "extras/decoders/libopus/miniaudio_libopus.h"

namespace welle::audio {
    void AudioPlayer::initialize(const std::function<void(const medialib::types::Song&)>& downloadSong) {
        ma_decoding_backend_vtable* pCustomBackendVTables[] =
        {
            ma_decoding_backend_libopus,
        };

        m_ResourceManagerConfig = ma_resource_manager_config_init();
        m_ResourceManagerConfig.ppCustomDecodingBackendVTables = pCustomBackendVTables;
        m_ResourceManagerConfig.customDecodingBackendCount     = std::size(pCustomBackendVTables);
        m_ResourceManagerConfig.pCustomDecodingBackendUserData = nullptr;  /* <-- This will be passed in to the pUserData parameter of each function in the decoding backend vtables. */

        ma_result result = ma_resource_manager_init(&m_ResourceManagerConfig, &m_ResourceManager);
        if (result != MA_SUCCESS) {
            throw std::runtime_error("Failed to initialize miniaudio resource manager!");
        }

        /* Once we have a resource manager we can create the engine. */
        m_EngineConfig = ma_engine_config_init();
        m_EngineConfig.pResourceManager = &m_ResourceManager;

        if (result = ma_engine_init(&m_EngineConfig, &m_Engine); result != MA_SUCCESS)
        {
            throw std::runtime_error("Failed to initialize miniaudio engine!");
        }

        m_DownloadSong = downloadSong;
    }

    void AudioPlayer::play(const medialib::types::Song& song) {
        const auto soundPath = std::filesystem::path{"songs/" + song.id + "." + song.suffix};
        if (!std::filesystem::exists(soundPath))
            m_DownloadSong(song);

        stop();

        m_Sound = std::make_unique<ma_sound>();
        m_CurrentlyPlayingSong = song;

        if (const auto r = ma_sound_init_from_file(
            &m_Engine,
            soundPath.string().c_str(),
            MA_SOUND_FLAG_STREAM,
            nullptr,
            nullptr,
            m_Sound.get()
        ); r != MA_SUCCESS)
            throw std::runtime_error("Failed to load sound " + soundPath.string() + ": " + ma_result_description(r));

        if (const ma_result r = ma_sound_seek_to_second(m_Sound.get(), 0); r != MA_SUCCESS)
            throw std::runtime_error("ma_sound_start failed");

        if (const ma_result r = ma_sound_start(m_Sound.get()); r != MA_SUCCESS)
            throw std::runtime_error("ma_sound_start failed");

        ma_sound_set_end_callback(m_Sound.get(), [](void *pUserData, ma_sound *pSound) {
            auto* player = static_cast<AudioPlayer*>(pUserData);
            player->stop();
        }, this);

        m_AfterPlayCallback();
    }

    void AudioPlayer::stop() {
        if (m_Sound) {
            ma_sound_stop(m_Sound.get());
            ma_sound_uninit(m_Sound.get());
            m_Sound.reset();
        }
        m_CurrentlyPlayingSong = {};
    }
}
