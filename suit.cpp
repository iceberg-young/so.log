#include <iostream>
#include <unistd.h>
#include "include/log.hpp"

using namespace std;
using namespace so;

void generate(log_filter::label label) {
    log x{label};
    x.append_tag("LGPL");
    x << "This program is free software: you can redistribute it and/or modify it\n"
      "under the terms of the GNU Lesser General Public License as published by\n"
      "the Free Software Foundation, either version 3 of the License, or\n"
      "(at your option) any later version.\n\n";
    x << "This program is distributed in the hope that it will be useful,\n"
      "but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
      "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
      "GNU Lesser General Public License for more details.\n\n";
    x << "You should have received a copy of the GNU Lesser General Public License\n"
      "along with this program.  If not, see <http://www.gnu.org/licenses/>.";
    x.append_tag("v3");
    usleep(rand() % 7000);
    cerr << x.str() << endl;
}

int main() {
    generate(log_filter::label::special);
    generate(log_filter::label::failure);
    generate(log_filter::label::warning);
    generate(log_filter::label::caution);
    generate(log_filter::label::message);
    generate(log_filter::label::success);
    generate(static_cast<log_filter::label>(13));
    return 0;
}
