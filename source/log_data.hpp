#ifndef INCLUDE_SO_LOG_DATA_ONCE_FLAG
#define INCLUDE_SO_LOG_DATA_ONCE_FLAG

#include "log.hpp"
#include "datetime.hpp"

namespace so {
    class log_data
    {
    public:
        log_data(log::label label) :
          label(label),
          begin(datetime::now()),
          clock(std::chrono::steady_clock::now()) {
        }

    public:
        std::string get_head_prefix();

        std::string get_body_prefix();

        std::string get_tail_prefix();

        std::string get_time_summary();

        std::string get_tags();

    public:
        std::string tags;

    private:
        log::label label;

        datetime begin;

        std::chrono::steady_clock::time_point clock;
    };
}

#endif//INCLUDE_SO_LOG_DATA_ONCE_FLAG
