#ifndef INCLUDE_SO_LOG_ONCE_FLAG
#define INCLUDE_SO_LOG_ONCE_FLAG

#include <memory>
#include <sstream>

namespace so {
    class log :
      public std::ostringstream
    {
    public:
        enum class label
        {
            unknown,
            failure,
            warning,
            caution,
            message,
            success,
        };

    public:
        log(label head);

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
