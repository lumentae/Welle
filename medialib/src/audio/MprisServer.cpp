#include "audio/MprisServer.h"

#include "Queue.h"
#include "audio/AudioPlayer.h"
#include "types/Song.h"
#include "utility/String.h"

namespace welle::medialib::audio {
    std::unique_ptr<mpris::Server> MprisServer::m_Server;
    std::function<void()> MprisServer::m_PlaybackStatusChanged;
    void MprisServer::start() {
        auto server = mpris::Server::make("welle");
        if (!server) {
            throw std::runtime_error("Could not start mpris server");
        }

        m_Server = std::move(server);
        m_Server->set_supported_uri_schemes({ "file" });
        m_Server->set_supported_mime_types({ "application/octet-stream", "text/plain" });

        auto& queue = Queue::getInstance();
        auto& audioPlayer = AudioPlayer::getInstance();
        m_Server->on_next([&] { queue.next(); });
        m_Server->on_previous([&] { queue.previous(); });
        m_Server->on_pause([&] {
            audioPlayer.pause();
            setPlaybackStatus(mpris::PlaybackStatus::Paused);
        });
        m_Server->on_play([&] {
            audioPlayer.play();
            setPlaybackStatus(mpris::PlaybackStatus::Playing);
        });
        m_Server->on_play_pause([&] {
            if (ma_sound_is_playing(audioPlayer.sound())) {
                audioPlayer.pause();
                setPlaybackStatus(mpris::PlaybackStatus::Paused);
            } else {
                audioPlayer.play();
                setPlaybackStatus(mpris::PlaybackStatus::Playing);
            }
        });
        m_Server->on_stop([&] {
            audioPlayer.destroy();
            setPlaybackStatus(mpris::PlaybackStatus::Stopped);
        });
        m_Server->on_seek([&](const int64_t position) {
            audioPlayer.seek(audioPlayer.position() + position / 1e6);
            m_Server->set_position(audioPlayer.position());
        });
        m_Server->on_set_position([&](const int64_t position) {
            audioPlayer.seek(position / 1e6);
            m_Server->set_position(audioPlayer.position());
        });

        m_Server->on_loop_status_changed([&] (const mpris::LoopStatus status) {
            switch (status) {
                case mpris::LoopStatus::None:
                    audioPlayer.setRepeatMode(AudioPlayer::RepeatMode::Disabled);
                    break;
                case mpris::LoopStatus::Track:
                    audioPlayer.setRepeatMode(AudioPlayer::RepeatMode::One);
                    break;
                case mpris::LoopStatus::Playlist:
                    audioPlayer.setRepeatMode(AudioPlayer::RepeatMode::Enabled);
                    break;
            }
            m_Server->set_loop_status(status);
        });
        m_Server->on_rate_changed([&] (double rate) { });
        m_Server->on_shuffle_changed([&] (bool shuffle) { });
        m_Server->on_volume_changed([&] (double vol) { });

        m_Server->start_loop_async();
    }

    void MprisServer::stop() {
        setPlaybackStatus(mpris::PlaybackStatus::Stopped);
    }

    void MprisServer::fromSong(const types::Song& song) {
        m_Server->set_metadata({
            { mpris::Field::Album, sdbus::Variant(song.album) },
            { mpris::Field::AlbumArtist, sdbus::Variant(utility::String::join(song.albumArtists)) },
            { mpris::Field::ArtUrl, sdbus::Variant("file://" + std::filesystem::absolute(std::filesystem::path{"cache/" + song.coverArt}).string()) },
            { mpris::Field::Artist, sdbus::Variant(song.artist) },
            { mpris::Field::Comment, sdbus::Variant(song.comment) },
            { mpris::Field::Composer, sdbus::Variant(song.displayComposer) },
            { mpris::Field::ContentCreated, sdbus::Variant(song.created) },
            { mpris::Field::Genre, sdbus::Variant(song.genre) },
            { mpris::Field::LastUsed, sdbus::Variant(song.played) },
            { mpris::Field::Length, sdbus::Variant(static_cast<int64_t>(song.duration * 1e6)) },
            { mpris::Field::Title, sdbus::Variant(song.title) },
            { mpris::Field::TrackId, sdbus::Variant(sdbus::ObjectPath("/org/welle/track/" + song.id)) },
            { mpris::Field::UseCount, sdbus::Variant(song.playCount) },
        });
        setPlaybackStatus(mpris::PlaybackStatus::Playing);
        m_Server->set_rate(1.0);
        m_Server->set_position(0);
    }

    void MprisServer::update(const float position, const bool seeked) {
        const auto newPos = static_cast<int64_t>(position * 1e6);
        m_Server->set_position(newPos);
        if (seeked)
            m_Server->send_seeked_signal(newPos);
    }

    void MprisServer::setPlaybackStatus(const mpris::PlaybackStatus status) {
        m_Server->set_playback_status(status);
        if (m_PlaybackStatusChanged)
            m_PlaybackStatusChanged();
    }
}
