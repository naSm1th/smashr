# smashr
Remote Shell using Simple-Socket Library

## Building
To build the remote shell server and client, run `make` from the root project directory.

## Running
### Server
To run the server with default options (port 2631, included shell), execute `./server.sh`.

Otherwise, run `bin/smashd [port_number] [shell to run]` (with the proper port number and shell).

The server will continue to run until you kill it with ctrl-c.

### Client
To run the client, run `bin/smashr [server] [port_number]` (with the proper domain name/IP address and port number).

The client will run until you exit the shell (usually with `exit`).
