# sysrepo-plugins-common

Set of utilities/functionalities which can be used for easier build of sysrepo
plugins.

# Build

Use the following set of commands to build the project:

```sh
git clone https://github.com/telekom/sysrepo-plugins-common.git
cd sysrepo-plugins-common
git submodule init
git submodule update
mkdir build; cd build
cmake .. # setup CMAKE_INSTALL_PREFIX if needed
make -j
```

# Documentation

As for the documentation, the files are documented using doxygen comments:

```sh
mkdir docs
doxygen Doxyfile
```

Use doxygen or browse `.h` files for an API description.

## Code of Conduct

This project has adopted the
[Contributor Covenant](https://www.contributor-covenant.org/) in version 2.0 as
our code of conduct. Please see the details in our
[CODE_OF_CONDUCT.md](CODE_OF_CONDUCT.md). All contributors must abide by the
code of conduct.

## How to Contribute

Contribution and feedback is encouraged and always welcome. For more information
about how to contribute, the project structure, as well as additional
contribution information, see our [Contribution Guidelines](./CONTRIBUTING.md).
By participating in this project, you agree to abide by its
[Code of Conduct](./CODE_OF_CONDUCT.md) at all times.

## Contributors

Our commitment to open source means that we are enabling -in fact encouraging-
all interested parties to contribute and become part of its developer community.

## Licensing

Copyright (C) 2022 Deutsche Telekom AG.

Licensed under the **BSD 3-Clause License** (the "License"); you may not use
this file except in compliance with the License.

You may obtain a copy of the License by reviewing the file [LICENSE](./LICENSE)
in the repository.

Unless required by applicable law or agreed to in writing, software distributed
under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the [LICENSE](./LICENSE)
for the specific language governing permissions and limitations under the
License.
