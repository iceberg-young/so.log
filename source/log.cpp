#include "log.hpp"
#include "log_data.hpp"

namespace so {
    log::log(log_filter::label label) :
      data(new log_data(label)) {
    }

    void log::append_tag(const std::string& tag) {
        this->data->tags.insert(tag);
    }

    void log::remove_tag(const std::string& tag) {
        this->data->tags.insert(tag);
    }

    void log::clear_tags() {
        this->data->tags.clear();
    }

    std::string log::str() const {
        std::istringstream iss{std::ostringstream::str()};
        std::string line;
        if (!std::getline(iss, line)) return "";

        auto s = this->data->get_head_prefix() + line;
        auto lacuna = this->data->get_body_lacuna();
        auto prefix = this->data->get_body_prefix();
        while (std::getline(iss, line)) {
            line.empty() ? s += lacuna : (s += prefix) += line;
        }
        return s + this->data->get_tail_prefix() + this->data->get_time_summary() + this->data->get_tags();
    }
}
