so.log
======

Add [CSI-SGR] colorized prefixes to each line of log.
For easy to distinguish and read in console.


API
---

### Writing log

See [log.hpp](include/log.hpp).

- Step 1: Streaming log text to a `so::log` object. E.g.

  ```cpp
  so::log log{log_label::special};
  log << "Hello, ";
  // ...
  log << "world!";
  ```

  > **Under The Hood!**
  > `so::log` is publicly derived from `std::ostringstream`.

- Step 2: Optionally, adding tags for better classification.

  ```cpp
  so::log::append_tag(std::string tag)
  so::log::remove_tag(std::string tag)
  so::log::clear_tags()
  ```

  E.g.
  ```cpp
  log.append_tag("demo");
  ```

- Step 3: Streaming the `so::log` object to the target stream.

  > ```cpp
  > std::ostream& operator<<(std::ostream& out, so::log message)
  > ```

  E.g.
  ```cpp
  std::cerr << log;
  ```
  > ![Snapshot](snapshot.png)

> **Tip!**
> By using 2 stream objects, you avoid interlaced text (*in multi-threading*)
> from constructing complex log, which may not be an atom operation.

### Filtering log

See [log_filter.hpp](include/log_filter.hpp).


License
-------
![LGPLv3]

Copyright (C) 2015  Iceberg YOUNG

This program is free software: you can redistribute it and/or modify it
under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.


---

[CSI-SGR]: https://en.wikipedia.org/wiki/ANSI_escape_code#CSI_codes
"SGR (Select Graphic Rendition) Parameters"

[LGPLv3]: http://www.gnu.org/graphics/lgplv3-88x31.png
"GNU Lesser General Public License version 3"
