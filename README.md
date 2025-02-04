# AdaWS

AdaWS is a simple *HTTP Web Server* built on C. This project consists of two main parts: **server** and **client**, which can be run within a single executable, allowing the development and testing of basic HTTP services. The server supports several static endpoints like `/`, `/about`, and `/purpose`, serving HTML files to the client.



## Getting Started
### Prerequisites

- GCC (compiler)
- Unix/Linux-based operating system (since it uses sockets and file system)

### Installation

1. **Clone the repository** to your local machine

```git
git clone https://github.com/azisuverse/AdaWS.git
```

2. **Compile the program** using *Makefile* or *Bash Script*

- Makefile

```make
make
```

- Bash

```sh
./build.sh
```

3. **Run the program** client or server

- Server

```sh
# run server
./adaws server
```

- Client (on another terminal)

```sh
# run client
./adaws client
```


## Features

- Provides a simple HTTP server that handles multiple endpoints:
- `/` - Serves the home page
- `/about` - Serves the about page
- `/purpose` - Serves the purpose page
- Supports client connections using TCP and sends HTTP requests to the server
- Code is split into two main parts: server and client, and run from a single executable without additional arguments.
- Uses the `SO_REUSEADDR` socket option to allow binding to the same port even after the server has been stopped.

## Endpoints

- GET / - Serve the `index.html` file
- GET /about - Serve the `about.html` file
- GET /purpose - Serve the `purpose.html` file

If an invalid endpoint requested, the server will return *404 Not Found* response.

## Contribs

1. Fork the repository.
2. Create new branch (git checkout -b future-feature-name).
3. Make the changes you want.
4. Commit the changes (git commit -am "feat: foo feature").
5. Push to the branch (git push origin future-feature-name).
6. Create a pull request

## License

This project is licensed under the MIT License see the [LICENSE](
https://github.com/aazis7/AdaWS/blob/main/LICENSE
) file for the details

## Final Touch
Thanks for visiting and reading this repository, I hope you will make your contribution and make this project more useful, [@aazis7](https://github.com/aazis7)
