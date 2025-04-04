<h1 align="center">
    Sysrepo Plugin Hardware
</h1>

<p align="center">
  <a href="#development">Development</a> •
  <a href="#documentation">Documentation</a> •
  <a href="#support-and-feedback">Support</a> •
  <a href="#how-to-contribute">Contribute</a> •
  <a href="#contributors">Contributors</a> •
  <a href="#licensing">Licensing</a>
</p>

The goal of this project is to create a Debian implementation of the IETF-Hardware YANG module disregarding any SNMP approach.

## About this component

A sysrepo plugin for the IETF-Hardware YANG module [RFC8348](https://tools.ietf.org/html/rfc8348)

## Development

The full development progress can be found in the [documentation](./DOCUMENTATION.md).

### Dependencies
```
libyang
libyang-cpp
sysrepo
sysrepo-cpp
libsensors4-dev
lm-sensors
pthreads
lshw
```

The `main` or `master` branch should be compiled using the the master branches of `libyang` and `sysrepo`. The `libyang1` branch is outdated and only works with the old versions of libyang and sysrepo.

### Build

The plugin is built as a shared library using the [MESON build system](https://mesonbuild.com/) and is required for building the plugin.

```bash
apt install meson ninja-build cmake pkg-config
```

The plugin install location is the `{prefix}` folder, the `libietf-hardware-plugin.so` should be installed over to the `plugins` folder from the sysrepo installation (e.g. the sysrepo install location for the bash commands below is `/opt/sysrepo`)\
Build by making a build directory (i.e. build/), run meson in that dir, and then use ninja to build the desired target.

```bash
git clone git@github.com:telekom/sysrepo-plugin-hardware.git
cd sysrepo-plugin-hardware
mkdir -p /opt/sysrepo/lib/sysrepo/plugins
meson --prefix="/opt/sysrepo/lib/sysrepo/plugins" ./build
ninja -C ./build
```

### Installation

Meson installs the shared-library in the `{prefix}`.

```bash
ninja install -C ./build
```

## Code of Conduct

This project has adopted the [Contributor Covenant](https://www.contributor-covenant.org/) in version 2.0 as our code of conduct. Please see the details in our [CODE_OF_CONDUCT.md](CODE_OF_CONDUCT.md). All contributors must abide by the code of conduct.

## Working Language

We decided to apply _English_ as the primary project language.

Consequently, all content will be made available primarily in English. We also ask all interested people to use English as language to create issues, in their code (comments, documentation etc.) and when you send requests to us. The application itself and all end-user facing content will be made available in other languages as needed.

## Documentation

The full documentation for the plugin can be found [here](./DOCUMENTATION.md).

## Support and Feedback

The following channels are available for discussions, feedback, and support requests:

| Type                     | Channel                                                |
| ------------------------ | ------------------------------------------------------ |
| **Issues**   | <a href="/../../issues/new/choose" title="General Discussion"><img src="https://img.shields.io/github/issues/telekom/sysrepo-plugin-hardware?style=flat-square"></a> </a>   |
| **Other Requests**    | <a href="mailto:opensource@telekom.de" title="Email Open Source Team"><img src="https://img.shields.io/badge/email-Open%20Source%20Team-green?logo=mail.ru&style=flat-square&logoColor=white"></a>   |

## How to Contribute

Contribution and feedback is encouraged and always welcome. For more information about how to contribute, the project structure, as well as additional contribution information, see our [Contribution Guidelines](./CONTRIBUTING.md). By participating in this project, you agree to abide by its [Code of Conduct](./CODE_OF_CONDUCT.md) at all times.

## Contributors

Our commitment to open source means that we are enabling -in fact encouraging- all interested parties to contribute and become part of its developer community.

## Licensing

Copyright (C) 2021 Deutsche Telekom AG.

Licensed under the **BSD 3-Clause License** (the "License"); you may not use this file except in compliance with the License.

You may obtain a copy of the License by reviewing the file [LICENSE](./LICENSE) in the repository.

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the [LICENSE](./LICENSE) for the specific language governing permissions and limitations under the License.
