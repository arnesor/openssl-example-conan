# openssl-example-conan
This projects demonstrates how to use pacakges created with the Conan C and
C++ package manager. It is a small example using the OpenSSL package.

Instructions (Linux):

```bash
$ git clone https://github.com/arnesor/openssl-example-conan.git
$ mkdir build && cd build
$ conan install ../openssl-example-conan
$ cmake ../openssl-example-conan
$ cmake --build .
$ cd bin
$ ./openssl-example
```

Instructions (Windows):

```bash
$ git clone https://github.com/arnesor/openssl-example-conan.git
$ mkdir build && cd build
$ conan install ..\openssl-example-conan
$ cmake ../openssl-example-conan -G "Visual Studio 14 2015 Win64"
$ cmake --build . --config Release
$ cd bin
$ openssl-example
```

