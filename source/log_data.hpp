/**
 * @copyright 2015 Iceberg YOUNG
 * @license GNU Lesser General Public License version 3
 */
#pragma once

#include <set>
#include "log.hpp"
#include "datetime.hpp"

namespace so {
    class log_data {
     public:
        static const std::string label_lookup;

     public:
        const std::chrono::steady_clock::time_point begin;
        const std::string color;
        const log_label label;
        std::set<std::string> tags;

     public:
        log_data(log_label label) :
          begin(std::chrono::steady_clock::now()),
          color(log_data::get_color(label)),
          label(label) {}

     public:
        std::string format(const std::string& content) const;

     protected:
        std::string get_head() const;

        std::string get_interval() const;

        std::string get_label() const;

        std::string get_tags() const;

        static std::string get_color(log_label label);
    };

    constexpr auto log_known_labels = static_cast<size_t>(log_label::_count_);
    constexpr auto log_label_length = 8U;
}
