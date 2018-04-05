# openssl-example-conan
This projects demonstrates how to use pacakges created with the Conan C and
C++ package manager. It is a small example using the OpenSSL package.

Instructions (Linux):

```bash
$ git clone https://github.com/arnesor/openssl-example-conan.git
$ mkdir build && cd build
$ conan install ../openssl-example-conan -s build_type=Debug --build=missing
$ cmake ../openssl-example-conan
$ cmake --build .
$ cd bin
$ ./openssl-example
$ ./openssl-test
```

Instructions (Windows):

```bash
$ git clone https://github.com/arnesor/openssl-example-conan.git
$ mkdir build && cd build
$ conan install ..\openssl-example-conan -s build_type=Debug --build=missing
$ conan install ..\openssl-example-conan -s build_type=Release --build=missing
$ cmake ../openssl-example-conan -G "Visual Studio 14 2015 Win64"
$ cmake --build . --config Debug
$ cd bin
$ openssl-example
$ openssl-test
```

