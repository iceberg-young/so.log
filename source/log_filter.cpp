#include <map>
#include <limits>
#include "log_data.hpp"

namespace so {
    namespace {
        bool block_unspecified = false;

        log_filter::label block_level = std::numeric_limits<log_filter::label>::max();

        std::map<std::string, bool> block_tags;

        bool any_of(const std::set<std::string>& tags, bool flag) {
            auto e = block_tags.end();
            for (auto& t : tags) {
                auto f = block_tags.find(t);
                if (f != e and f->second == flag) return true;
            }
            return false;
        }
    }

    void log_filter::configure(const std::string& settings) {
        // TODO
    }

    void log_filter::on() {
        block_unspecified = true;
    }

    void log_filter::off() {
        block_unspecified = false;
    }

    void log_filter::block(const std::string& tag) {
        block_tags[tag] = true;
    }

    void log_filter::pass(const std::string& tag) {
        block_tags[tag] = false;
    }

    void log_filter::level(label max) {
        block_level = max;
    }

    std::ostream& operator<<(std::ostream& out, const log& message) {
        if (message.data->label <= block_level) {
            auto pass = block_unspecified
              ? any_of(message.data->tags, false)
              : not any_of(message.data->tags, true);
            if (pass) {
                out << message.str();
            }
        }
        return out;
    }
}
