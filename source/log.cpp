#include "log.hpp"
#include "log_data.hpp"

namespace so {
    namespace {
        std::string packed_tag(const std::string& tag) {
            // TODO tag should be formatted as identifier.
            return '#' + tag + ' ';
        }
    }

    log::log(label head) :
      data(new log_data(head)) {
    }

    void log::append_tag(const std::string& tag) {
        auto piece = packed_tag(tag);
        if (std::string::npos == this->data->tags.find(piece)) {
            this->data->tags += piece;
        }
    }

    void log::remove_tag(const std::string& tag) {
        auto piece = packed_tag(tag);
        auto begin = this->data->tags.find(piece);
        if (begin != std::string::npos) {
            this->data->tags.erase(begin, piece.length());
        }
    }

    void log::clear_tags() {
        this->data->tags.clear();
    }

    std::string log::str() const {
        std::istringstream iss{std::ostringstream::str()};
        std::string line;
        if (!std::getline(iss, line)) return "";

        auto s = this->data->get_head_prefix() + line;
        auto prefix = this->data->get_body_prefix();
        while (std::getline(iss, line)) {
            s += prefix + line;
        }
        return s + this->data->get_tail_prefix() + this->data->get_time_summary() + this->data->get_tags();
    }
}
