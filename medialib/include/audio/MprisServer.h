#pragma once

#include <mpris_server.hpp>
#include "types/Song.h"

namespace welle::medialib::audio {
    class MprisServer {
    public:
        static void start();
        static void stop();
        static void fromSong(const types::Song &song);
        static void update(float position, bool seeked);
        static void setPlaybackStatusChanged(const std::function<void()>& callback) { m_PlaybackStatusChanged = callback; }
        static void setPlaybackStatus(mpris::PlaybackStatus status);

    private:
        static std::unique_ptr<mpris::Server> m_Server;
        static std::function<void()> m_PlaybackStatusChanged;
    };
}
