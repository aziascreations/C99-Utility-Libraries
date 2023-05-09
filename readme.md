# NibblePoker's Clang Goodies
Small collection of utilities and libraries for C in order to simplify some development tasks.

## Features
* ![](docs/images/console.png) Robust launch arguments parsing & handling with verb support
* ![](docs/images/chain.png) Double linked lists with custom freeing callbacks
* ![](docs/images/text.png) Various string utilities
* ![](docs/images/bug.png) Toggleable debugging output functions
* ![](docs/images/module.png) Complete, toggleable & macro-able `WCHAR` support
* ![](docs/images/view_more.png) Other features such as UUID4, and more to come

## Remarks
This project is by no mean complete or exhaustive in the features it provides.<br>
It is mainly intended to provide me with a set of utilities and libraries I often use while making other applications.

While it is this way, its functions' names, signatures and behaviour should stay relatively similar as the project
advances.<br>
In the event I introduce breaking changes, you should be able to notice them since I'll be using
[Semantic Versioning](https://semver.org/).

## Usage
In order to use this library in your projects you need to do the following things:

Firstly, add this repository as a submodule in your project and checkout to a specific tag or commit:
```bash
git submodule add https://github.com/aziascreations/C99-Utility-Libraries.git libs/nibblepoker-c-goodies
git -C libs/nibblepoker-c-goodies checkout <hash|tag>
```

Afterward, add the following lines in your *CMakeLists.txt*:
```cmake
file(
    GLOB_RECURSE src_nibblepoker_c_goodies
    CONFIGURE_DEPENDS "libs/nibblepoker-c-goodies/src/*.h" "libs/nibblepoker-c-goodies/src/*.c"
)
```

Finally, modify you targets to add `${src_nibblepoker_c_goodies}` like so:
```cmake
add_executable(my_app src/main.c ${src_nibblepoker_c_goodies} ...)
```

## Examples
**TODO:** *Add intro text.*

Alternatively, you can also check the [aziascreations/C99-Win32-Wifi-Utility](https://github.com/aziascreations/C99-Win32-Wifi-Utility)
repository for a complete example in a "fully-fledged" Windows application.

### Launch arguments
**TODO**

### Double Linked Lists
* [Basic operations](examples/dllist_basic.c)
    * Creating a list, adding, accessing & iteration over values and basic freeing call.
* [Custom freeing operation](examples/dllist_custom_free.c)
    * Same as above while using structured data that needs to be freed in a specific way.

### UUID
* [UUID4 generation](examples/uuid_all.c)
  * Rudimentary RNG setup & UUID4 generation.

## Documentation

### Viewing
You can consult the documentation at the following URL:<br>
&nbsp;&nbsp;&nbsp;&nbsp;https://aziascreations.github.io/C99-Utility-Libraries/

It is automatically updated when a commit is pushed onto the `master` branch.

### Building
If you want to build the documentation, you need to do the following things:
* Install [Doxygen](https://www.doxygen.nl/) on your system.
* Clone the git submodules with `git submodule update --init --recursive`
* Run the [make-doc.bat](https://github.com/aziascreations/C99-Utility-Libraries/blob/master/make-doc.bat) script.
* Go into `docs/html` and open the `index.html` file.

## Licenses
[MIT License](https://github.com/aziascreations/C99-Utility-Libraries/blob/master/LICENSE)

The [doxygen-awesome-css](https://github.com/jothepro/doxygen-awesome-css) repository uses the same
[license](https://github.com/jothepro/doxygen-awesome-css/blob/main/LICENSE).
