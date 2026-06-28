#include "Queue.h"

#include <random>

namespace welle::medialib {
    void Queue::playNow(const std::vector<types::Song> &songs, const int startIndex) {
        m_Queue = songs;
        playIndex(startIndex);
    }

    void Queue::addToQueue(std::vector<types::Song> songs, const bool atCurrentIndex) {
        const auto begin = atCurrentIndex ? m_Queue.begin() + m_CurrentIndex + 1 : m_Queue.end();
        m_Queue.insert(begin, songs.begin(), songs.end());
    }

    void Queue::next() {
        if (hasNext())
            playIndex(m_CurrentIndex + 1);
    }

    void Queue::previous() {
        if (hasPrevious())
            playIndex(m_CurrentIndex - 1);
    }

    void Queue::clear() {
        m_Queue.clear();
        m_CurrentIndex = -1;
    }

    void Queue::shuffle() {
        std::ranges::shuffle(m_Queue, std::default_random_engine{});
    }

    void Queue::fromStart() {
        m_CurrentIndex = 0;
        m_OnSongChanged(m_Queue.at(0));
    }

    const types::Song* Queue::currentSong() const {
        if (m_CurrentIndex < 0 || m_CurrentIndex >= m_Queue.size()) return nullptr;
        return &m_Queue.at(m_CurrentIndex);
    }

    void Queue::playIndex(const int index) {
        if (index < 0 || index >= m_Queue.size()) return;
        m_CurrentIndex = index;
        m_OnSongChanged(m_Queue.at(index));
    }
}
