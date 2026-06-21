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

    private:
        static std::unique_ptr<mpris::Server> m_Server;
    };
}
