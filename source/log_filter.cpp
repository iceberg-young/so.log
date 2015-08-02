/**
 * @copyright 2015 Iceberg YOUNG
 * @license GNU Lesser General Public License version 3
 */

#include "log_data.hpp"

namespace so {
    namespace {
        bool block_unspecified = false;
        log_label block_latch = static_cast<log_label>(-1);
        std::set<std::string> block_tags;

        bool any_of(const std::set<std::string>& tags) {
            auto e = block_tags.end();
            for (auto& t : tags) {
                if (block_tags.find(t) != e) return true;
            }
            return false;
        }

        const char label_lookup[]{
          ""
            "SPECIAL" "special"
            "FAILURE" "failure"
            "WARNING" "warning"
            "CAUTION" "caution"
            "SUCCESS" "success"
            "VERBOSE" "verbose"
        };
        constexpr size_t size_per_label = 14;
        constexpr size_t known_labels = static_cast<size_t>(log_label::count_known_labels);
        static_assert(
          size_per_label * known_labels == sizeof(label_lookup) - 1, // -'\0'
          "Lookup will be very simple if length of all labels are the same."
        );

        void set_latch(const std::string& value) {
            if (value.empty()) return;

            auto p = std::string{label_lookup}.find(value);
            if (p != std::string::npos) {
                block_latch = static_cast<log_label>(p / size_per_label);
            }

            char* e = nullptr;
            auto v = std::strtoul(value.c_str(), &e, 0);
            if (e == &*value.end()) {
                block_latch = static_cast<log_label>(v);
            }
        }
    }

    void log_filter::configure(const std::string& settings) {
        auto block_switch = settings.find_first_of("+-");
        if (block_switch == std::string::npos) {
            set_latch(settings);
            return;
        }
        set_latch(settings.substr(0, block_switch));
        block_unspecified = settings[block_switch] == '+';

        std::istringstream iss{settings.substr(block_switch + 1)};
        std::string tag;
        while (std::getline(iss, tag, ',')) {
            if (not tag.empty()) {
                block_tags.insert(tag);
            }
        }
    }

    void log_filter::on() {
        block_unspecified = true;
    }

    void log_filter::off() {
        block_unspecified = false;
    }

    void log_filter::append(const std::string& tag) {
        block_tags.insert(tag);
    }

    void log_filter::remove(const std::string& tag) {
        block_tags.erase(tag);
    }

    void log_filter::latch(log_label max) {
        block_latch = max;
    }

    std::ostream& operator<<(std::ostream& out, const log& message) {
        if (message.data->label <= block_latch
          and block_unspecified == any_of(message.data->tags)) {
            out << message.data->format(message.str());
        }
        return out;
    }
}
