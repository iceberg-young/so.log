#include <iostream>
#include <unistd.h>
#include "log.hpp"

using namespace std;
using namespace so;

void generate(log_label label) {
    log x{label};
    x.assign("LGPL");
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
    x.assign("v3");
    usleep(rand() % 7000);
    cerr << x << endl;
}

int main() {
    generate(log_label::special);
    generate(log_label::failure);
    generate(log_label::warning);
    generate(log_label::caution);
    generate(log_label::success);
    generate(log_label::verbose);
    generate(static_cast<log_label>(13));
    return 0;
}
