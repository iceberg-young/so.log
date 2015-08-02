/**
 * @copyright 2015 Iceberg YOUNG
 * @license GNU Lesser General Public License version 3
 */
#pragma once

#include <memory>
#include <sstream>
#include "log_filter.hpp"

namespace so {
    class log :
      public std::ostringstream {
        friend std::ostream& operator<<(std::ostream& out, const class log& message);

     public:
        log(log_label label = log_label::verbose);

     public:
        void assign(const std::string& tag);

        void revoke(const std::string& tag);

        void clear_tags();

     private:
        std::shared_ptr<class log_data> data;
    };
}
