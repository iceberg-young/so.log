/**
 * @copyright 2015 Iceberg YOUNG
 * @license GNU Lesser General Public License version 3
 */
#pragma once

#include <string>

namespace so {
    enum class log_label :
      unsigned {
        special,
        failure,
        warning,
        caution,
        success,
        verbose,
        count_known_labels,
    };

    class log_filter {
     public:
        // (* EBNF *) [ latch ] [ ( "+" | "-" ) tag { "," tag } ]
        static void configure(const std::string& settings);

     public:
        // Block any log, unless it has a specified tag.
        static void on();

        // Only block a log which has any specified tag.
        static void off();

        // Specify a tag.
        static void append(const std::string& tag);

        // Remove a specified tag.
        static void remove(const std::string& tag);

        // Block any log that has a higher label than `max`.
        static void latch(log_label max);
    };
}
