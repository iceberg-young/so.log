#include "log_data.hpp"

namespace so {
    namespace {
        constexpr auto known_labels = static_cast<size_t>(log_label::count_known_labels);

        const char* const label_prints[]{
          "SPECIAL", "FAILURE", "WARNING", "CAUTION", "SUCCESS", "VERBOSE"
        };
        static_assert(
          sizeof(label_prints) / sizeof(label_prints[0]) == known_labels,
          "Elements should match enumerations in `log_label`."
        );

        const char label_colors[]{'4', '1', '5', '3', '2', '6', '7'};
        static_assert(
          sizeof(label_colors) == known_labels + 1, // +default
          "Elements should match enumerations in `log_label`."
        );

        const char sgr_reset[]{"\033[m"};
        const char sgr_underline[]{"\033[4m"};
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
        return this->color + "\xE2\x96\xA0\n" + sgr_reset;
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
        auto i = static_cast<size_t>(this->label);
        return i < known_labels ? label_prints[i] : std::to_string(i);
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
        auto i = std::min(static_cast<size_t>(label), known_labels);
        return std::string{"\033[3"} + label_colors[i] + 'm';
    }
}
