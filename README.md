# Setup

- **Windows**

  ```sh
  powershell "iwr -Uri https://raw.githubusercontent.com/SenZmaKi/Network-Programming/master/Assignment-1/install.ps1 -UseBasicParsing | iex"
  ```

- **Linux/Mac**
  - Install [Clang](https://clang.llvm.org/) 17.0.6+
  - Install [Make](https://www.gnu.org/software/make/manual/make.html) 4.4.1+
  - Install your equivalent of [MSVC C++ Build tools](https://visualstudio.microsoft.com/visual-cpp-build-tools/) (On Linux It's probably pre-installed)

# Make

```sh
cd Network-Programming/Assignment-1
```

Server runs at port `8080` and client connects at url `127.0.0.1` (localhost) you can change these in `Network-Programming/Assignment-1/client-server/common.hpp`

## Run/Build

- Build All

  ```sh
  make
  ```

- Server

  ```sh
  make run_server

  make server
  ```

- Client

  ```sh
  make run_client

  make client
  ```

- Standalone

  ```sh
  make run_standalone

  make standalone
  ```

## Clean previous builds

```sh
  make clean
```
