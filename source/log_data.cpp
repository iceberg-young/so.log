#include "log_data.hpp"

namespace so {
    namespace {
        const std::string log_label_literals[]{
          "SPECIAL", "FAILURE", "WARNING", "CAUTION", "SUCCESS", "VERBOSE"
        };
        const std::string log_label_colors[]{
          "34", "31", "35", "33", "32", "36", "37"
        };
        constexpr unsigned log_label_amount = sizeof(log_label_literals) / sizeof(log_label_literals[0]);

        const std::string sgr_reset{"\033[m"};
        const std::string sgr_underline{"\033[4m"};
    }

    std::string log_data::format(const std::string& content) const {
        std::string s{this->get_head()};
        if (content.empty()) return s;

        auto e = this->get_prefix(prefix::none);
        auto p = this->get_prefix(prefix::body);

        std::istringstream iss{std::move(content)};
        std::string line;
        while (not std::getline(iss, line).eof()) {
            s += '\n';
            line.empty() ? s += e : (s += p) += line;
        }

        s += '\n';
        s += this->get_prefix(prefix::tail);
        s += line;
        return s += this->get_eot();
    }

    std::string log_data::get_eot() const {
        return this->color + "\xE2\x96\xA0" + sgr_reset;
    }

    std::string log_data::get_head() const {
        return this->color + sgr_underline + this->get_label() + sgr_reset
          + ' ' + to_string(this->begin) + this->get_tags();
    }

    std::string log_data::get_prefix(prefix purpose) const {
        std::string p{this->color};
        switch (purpose) {
            case prefix::body: {
                p += " \xE2\x94\x9C ";
                break;
            }
            case prefix::tail: {
                p += " \xE2\x94\x94 ";
                break;
            }
            case prefix::none: {
                p += " \xE2\x94\x82 ";
                break;
            }
        }
        return p += sgr_reset;
    }

    std::string log_data::get_label() const {
        auto index = static_cast<unsigned>(this->label);
        return index < log_label_amount
          ? log_label_literals[index]
          : std::to_string(index);
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
        auto index = std::min(static_cast<unsigned>(label), log_label_amount);
        return "\033[" + log_label_colors[index] + 'm';
    }
}
