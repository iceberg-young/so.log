#ifndef INCLUDE_SO_LOG_FILTER_ONCE_FLAG
#define INCLUDE_SO_LOG_FILTER_ONCE_FLAG

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
        // latch[(+|-)tag(,tag)*]
        static void configure(const std::string& settings);

     public:
        // Block any log that has none of specified tags.
        static void on();

        // Block any log that has any of specified tags.
        static void off();

        // Specify a tag.
        static void notice(const std::string& tag);

        // Revoke a specified tag.
        static void ignore(const std::string& tag);

        // Block any log that has a higher label than `max`.
        static void latch(log_label max);
    };
}

#endif//INCLUDE_SO_LOG_FILTER_ONCE_FLAG
