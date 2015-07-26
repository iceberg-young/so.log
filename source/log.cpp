#include "log_data.hpp"

namespace so {
    log::log(log_label label) :
      data(std::make_shared<log_data>(label)) {
    }

    void log::append_tag(const std::string& tag) {
        this->data->tags.insert(tag);
    }

    void log::remove_tag(const std::string& tag) {
        this->data->tags.erase(tag);
    }

    void log::clear_tags() {
        this->data->tags.clear();
    }
}
