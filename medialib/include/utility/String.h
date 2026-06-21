#pragma once
#include <sstream>
#include <vector>

namespace welle::medialib::utility {
    class String {
    public:
        template<typename T>
        static std::string join(std::vector<T> items, const std::string &delimiter = "") {
            std::ostringstream oss;
            for (size_t i = 0; i < items.size(); i++) {
                if (i > 0) oss << delimiter;
                oss << items[i];
            }
            return oss.str();
        }

        static std::string join(const std::vector<types::Artist> &items, const std::string &delimiter = "") {
            std::ostringstream oss;
            for (size_t i = 0; i < items.size(); i++) {
                if (i > 0) oss << delimiter;
                oss << items[i].name;
            }
            return oss.str();
        }
    };
}
