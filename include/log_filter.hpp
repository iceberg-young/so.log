#ifndef INCLUDE_SO_LOG_FILTER_ONCE_FLAG
#define INCLUDE_SO_LOG_FILTER_ONCE_FLAG

#include <string>

namespace so {
    class log_filter
    {
    public:
        enum class label
        {
            special,
            failure,
            warning,
            caution,
            message,
            success,
        };

    public:
        // <label>[(+/-)(tag,)+]
        static void configure(const std::string& settings);

    public:
        // Block all unspecified.
        static void on();

        // Pass all unspecified.
        static void off();

        // Block the specified tag.
        static void block(const std::string& tag);

        // Pass the specified tag.
        static void pass(const std::string& tag);

        // Block any log that higher than `max`.
        static void level(label max);
    };
}

#endif//INCLUDE_SO_LOG_FILTER_ONCE_FLAG
