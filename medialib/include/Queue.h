#pragma once
#include <vector>

#include "types/Song.h"

namespace welle::medialib {
    class Queue {
    public:
        Queue() = default;
        static Queue& getInstance() {
            static Queue instance;
            return instance;
        }

        void playNow(const std::vector<types::Song> &songs, int startIndex = 0);
        void addToQueue(std::vector<types::Song> songs);
        void next();
        void previous();
        void clear();
        void shuffle();

        void setOnSongChanged(const std::function<void(const types::Song&)> &onSongChanged) { m_OnSongChanged = onSongChanged; }

        [[nodiscard]] bool hasNext() const { return m_CurrentIndex < m_Queue.size() - 1; }
        [[nodiscard]] bool hasPrevious() const { return m_CurrentIndex > 0; }
        [[nodiscard]] int currentIndex() const { return m_CurrentIndex; }
        [[nodiscard]] const types::Song* currentSong() const;
        [[nodiscard]] const std::vector<types::Song>& queue() const { return m_Queue; }

    private:
        void playIndex(int index);
        int m_CurrentIndex = -1;
        std::vector<types::Song> m_Queue;
        std::function<void(const types::Song&)> m_OnSongChanged;
    };
}
