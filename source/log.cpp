/**
 * @copyright 2015 Iceberg YOUNG
 * @license GNU Lesser General Public License version 3
 */

#include "log_data.hpp"

namespace so {
    log::log(log_label label) :
      data(std::make_shared<log_data>(label)) {
    }

    void log::assign(const std::string& tag) {
        this->data->tags.insert(tag);
    }

    void log::revoke(const std::string& tag) {
        this->data->tags.erase(tag);
    }

    void log::clear_tags() {
        this->data->tags.clear();
    }
}
