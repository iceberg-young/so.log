#include "log_data.hpp"

namespace so {
    namespace {
        const char* LOG_LABEL_LITERALS[] = {
          "UNKNOWN", "FAILURE", "WARNING", "CAUTION", "MESSAGE", "SUCCESS",
        };

        const char* LOG_LABEL_COLORS[] = {
          "34", "35", "31", "33", "36", "32", "30",
        };

        constexpr unsigned LOG_LABEL_AMOUNT = sizeof(LOG_LABEL_LITERALS) / sizeof(LOG_LABEL_LITERALS[0]);

        std::string get_colored_label(unsigned index, const std::string& label) {
            return std::string{"\033[1;"} + LOG_LABEL_COLORS[index] + 'm' + label + "\033[22m\xE2\x94\xAC\033[0m";
        }

        std::string get_colored_joint(unsigned index, const std::string& token) {
            return std::string{"\n       \033["} + LOG_LABEL_COLORS[index] + 'm' + token + "\033[0m";
        }

        std::string get_colored_time(unsigned index, const std::string& w3dt, long ms) {
            auto s = std::string{"\033["} + LOG_LABEL_COLORS[index] + "m[" + w3dt;
            if (ms > 0) {
                s += " +" + std::to_string(ms) + "ms";
            }
            return s += "]\033[0m ";
        }
    }

    std::string log_data::get_head_prefix() {
        auto index = static_cast<unsigned>(this->label);
        if (index >= LOG_LABEL_AMOUNT) {
            char buffer[sizeof("0000000")];
            snprintf(buffer, sizeof(buffer), "%07X", index);
            return get_colored_label(LOG_LABEL_AMOUNT, buffer);
        }
        return get_colored_label(index, LOG_LABEL_LITERALS[index]);
    }

    std::string log_data::get_body_prefix() {
        auto index = static_cast<unsigned>(this->label);
        return get_colored_joint(std::min(index, LOG_LABEL_AMOUNT), "\xE2\x94\x9C");
    }

    std::string log_data::get_tail_prefix() {
        auto index = static_cast<unsigned>(this->label);
        return get_colored_joint(std::min(index, LOG_LABEL_AMOUNT), "\xE2\x94\x94");
    }

    std::string log_data::get_time_summary() {
        auto index = static_cast<unsigned>(this->label);
        auto w3dt = to_string(this->begin);
        auto delta = std::chrono::steady_clock::now() - this->clock;
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(delta).count();
        return get_colored_time(std::min(index, LOG_LABEL_AMOUNT), w3dt, ms);
    }

    std::string log_data::get_tags() {
        return "\033[1m" + this->tags + "\033[0m";
    }
}
