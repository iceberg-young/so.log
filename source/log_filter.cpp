#include "log_data.hpp"

namespace so {
    namespace {
        bool block_unspecified = false;
        log_label block_latch = log_label::verbose;
        std::set<std::string> block_tags;

        bool any_of(const std::set<std::string>& tags) {
            auto e = block_tags.end();
            for (auto& t : tags) {
                if (block_tags.find(t) != e) return true;
            }
            return false;
        }
    }

    void log_filter::configure(const std::string& settings) {
        // TODO <label>[(+/-)(tag,)+]
    }

    void log_filter::on() {
        block_unspecified = true;
    }

    void log_filter::off() {
        block_unspecified = false;
    }

    void log_filter::notice(const std::string& tag) {
        block_tags.insert(tag);
    }

    void log_filter::ignore(const std::string& tag) {
        block_tags.erase(tag);
    }

    void log_filter::latch(log_label max) {
        block_latch = max;
    }

    std::ostream& operator<<(std::ostream& out, const log& message) {
        if (message.data->label <= block_latch
          and block_unspecified == any_of(message.data->tags)) {
            out << message.data->format(message.str()) << '\n';
        }
        return out;
    }
}
