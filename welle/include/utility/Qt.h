#pragma once
#include <vector>
#include <QList>
#include <ranges>

namespace welle::utility {
    class Qt {
    public:
        template <typename T>
        static QList<T> vectorToQList(std::vector<T> vector) {
            QList<T> qList;
            qList.reserve(vector.size());
            std::ranges::copy(vector, std::back_inserter(qList));
            return qList;
        }
    };
}