/**
 * @copyright 2015 Iceberg YOUNG
 * @license GNU Lesser General Public License version 3
 */

#include "log_data.hpp"

namespace so {
    namespace {
        // Hack! Only works if all labels have (been padded to) the same length.
        const char label_prints[][log_label_length]{
          "SPECIAL", "FAILURE", "WARNING", "CAUTION", "SUCCESS", "VERBOSE",
          "special", "failure", "warning", "caution", "success", "verbose",
        };
        static_assert(
          sizeof(label_prints) / log_label_length == log_known_labels * 2,
          "Elements should match enumerations in `log_label`."
        );

        const char label_colors[]{'4', '1', '5', '3', '2', '6', '7'};
        static_assert(
          sizeof(label_colors) == log_known_labels + 1, // +default
          "Elements should match enumerations in `log_label`."
        );

        const char sgr_reset[]{"\033[m"};
        const char sgr_underline[]{"\033[4m"};
    }

    const std::string log_data::label_lookup{
      reinterpret_cast<const char*>(label_prints),
      sizeof(label_prints)
    };

    std::string log_data::format(const std::string& content) const {
        std::string s{this->get_head()};
        if (content.empty()) return s;

        std::istringstream iss{std::move(content)};
        std::string line;
        auto e = this->color + " \xE2\x94\x82 " + sgr_reset;
        auto p = this->color + " \xE2\x94\x9C " + sgr_reset;
        while (not std::getline(iss, line).eof()) {
            s += '\n';
            line.empty() ? s += e : (s += p) += line;
        }
        s += '\n';
        ((s += this->color) += " \xE2\x94\x94 ") += sgr_reset;
        s += line;

        ((s += this->color) += "\xE2\x96\xA0") += sgr_reset;
        return s += '\n';
    }

    std::string log_data::get_head() const {
        return this->color + sgr_underline + this->get_label() + sgr_reset
          + ' ' + this->get_interval() + this->get_tags();
    }

    std::string log_data::get_interval() const {
        auto elapsed = std::chrono::steady_clock::now() - this->begin;
        return to_string(elapsed) + '/' + to_string(datetime::now());
    }

    std::string log_data::get_label() const {
        auto i = static_cast<size_t>(this->label);
        return i < log_known_labels ? label_prints[i] : std::to_string(i);
    }

    std::string log_data::get_tags() const {
        std::string s;
        if (not this->tags.empty()) {
            for (auto& t : this->tags) {
                s += " #" + this->color + t + sgr_reset;
            }
        }
        return s;
    }

    std::string log_data::get_color(log_label label) {
        auto i = std::min(static_cast<size_t>(label), log_known_labels);
        return std::string{"\033[3"} + label_colors[i] + 'm';
    }
}
