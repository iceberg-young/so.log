#include "log_data.hpp"

namespace so {
    namespace {
        const std::string LOG_LABEL_LITERALS[] = {
          "SPECIAL", "FAILURE", "WARNING", "CAUTION", "MESSAGE", "SUCCESS",
        };

        const std::string LOG_LABEL_COLORS[] = {
          "34", "35", "31", "33", "36", "32", "39",
        };

        constexpr unsigned LOG_LABEL_AMOUNT = sizeof(LOG_LABEL_LITERALS) / sizeof(LOG_LABEL_LITERALS[0]);

        std::string get_escape(const std::string& code) {
            return "\033[" + code + 'm';
        }

        const std::string SGR_BOLD = "\033[1m";

        const std::string SGR_RESET = "\033[m";

        std::string get_colored_label(const std::string& color, const std::string& label) {
            return SGR_BOLD + color + label + get_escape("22") + "\xE2\x94\xAC" + SGR_RESET;
        }

        std::string get_colored_joint(const std::string& color, const std::string& token) {
            return "\n       " + color + token + SGR_RESET;
        }

        std::string get_colored_time(const std::string& color, const std::string& w3dt, long ms) {
            auto s = color + '[' + w3dt;
            if (ms > 0) {
                s += " +" + std::to_string(ms) + "ms";
            }
            return s + ']' + SGR_RESET;
        }

        std::string get_label(log_filter::label label) {
            auto index = static_cast<unsigned>(label);
            if (index >= LOG_LABEL_AMOUNT) {
                char buffer[sizeof("0000000")];
                snprintf(buffer, sizeof(buffer), "%07X", index);
                return std::string{buffer, 7};
            }
            return LOG_LABEL_LITERALS[index];
        }
    }

    std::string log_data::get_head_prefix() {
        return get_colored_label(this->get_color(), get_label(this->label));
    }

    std::string log_data::get_body_lacuna() {
        return get_colored_joint(this->get_color(), "\xE2\x94\x82");
    }

    std::string log_data::get_body_prefix() {
        return get_colored_joint(this->get_color(), "\xE2\x94\x9C");
    }

    std::string log_data::get_tail_prefix() {
        return get_colored_joint(this->get_color(), "\xE2\x94\x94");
    }

    std::string log_data::get_time_summary() {
        auto w3dt = to_string(this->begin);
        auto delta = std::chrono::steady_clock::now() - this->clock;
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(delta).count();
        return get_colored_time(this->get_color(), w3dt, ms);
    }

    std::string log_data::get_tags() {
        std::string s;
        if (not this->tags.empty()) {
            s += SGR_BOLD;
            for (auto& t : this->tags) {
                (s += " #") += t;
            }
        }
        return s + SGR_RESET;
    }

    std::string log_data::get_color() {
        auto index = std::min(static_cast<unsigned>(this->label), LOG_LABEL_AMOUNT);
        return get_escape(LOG_LABEL_COLORS[index]);
    }
}
