#ifndef INCLUDE_SO_LOG_ONCE_FLAG
#define INCLUDE_SO_LOG_ONCE_FLAG

#include <memory>
#include <sstream>
#include "log_filter.hpp"

namespace so {
    class log :
      public std::ostringstream
    {
        friend std::ostream& operator<<(std::ostream& out, const class log& message);

    public:
        log(log_filter::label label);

    public:
        void append_tag(const std::string& tag);

        void remove_tag(const std::string& tag);

        void clear_tags();

    public:
        std::string str() const;

    private:
        std::shared_ptr<class log_data> data;
    };
}

#endif//INCLUDE_SO_LOG_ONCE_FLAG
