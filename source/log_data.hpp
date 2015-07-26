#ifndef INCLUDE_SO_LOG_DATA_ONCE_FLAG
#define INCLUDE_SO_LOG_DATA_ONCE_FLAG

#include <set>
#include "log.hpp"
#include "datetime.hpp"

namespace so {
    class log_data {
     public:
        enum class prefix {
            body, tail, none
        };

     public:
        const datetime begin;
        const std::string color;
        const log_label label;
        std::set<std::string> tags;

     public:
        log_data(log_label label) :
          begin(datetime::now()),
          color(log_data::get_color(label)),
          label(label) {}

     public:
        std::string format(const std::string& content) const;

     protected:
        std::string get_eot() const;

        std::string get_head() const;

        std::string get_prefix(prefix purpose) const;

        std::string get_label() const;

        std::string get_tags() const;

        static std::string get_color(log_label label);
    };
}

#endif//INCLUDE_SO_LOG_DATA_ONCE_FLAG
