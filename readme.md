# NibblePoker's Clang Goodies
Small collection of utilities and libraries for C in order to simplify some development tasks.

## Features
* ![](docs/images/console.png) Launch arguments & verbs handling
* ![](docs/images/chain.png) Double linked lists with custom freeing callbacks
* ![](docs/images/text.png) Various string utilities
* ![](docs/images/bug.png) Toggleable debugging output functions
* ![](docs/images/module.png) Complete, toggleable & macro-able `WCHAR` support

## Remarks
This project is by no mean complete or exhaustive in the features it provides.<br>
It is mainly intended to provide me with a set of utilities and libraries I often use while making other applications.

While it is this way, its functions' names, signatures and behaviour should stay relatively similar as the project
advances.<br>
In the event I introduce breaking changes, you should be able to notice them since I'll be using
[Semantic Versioning](https://semver.org/).

## Documentation

### Viewing
*TODO: Put URL here once it has a proper link & branch.*

### Building
If you want to build the documentation, you need to do the following things:
* Install [Doxygen](https://www.doxygen.nl/) on your system.
* Clone the git submodules with `git submodule update --init --recursive`
* Run the [make-doc.bat](make-doc.bat) script.
* Go into `docs/html` and open the `index.html` file.

### Automation
*TODO: Automate with GitHub Actions.*

## Licenses
[MIT License](./LICENSE)

The [doxygen-awesome-css](https://github.com/jothepro/doxygen-awesome-css) repository uses the same
[license](https://github.com/jothepro/doxygen-awesome-css/blob/main/LICENSE).
