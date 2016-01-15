# Project Express

Node server, socket.io/serial adapter, and arduino sketches for Project Express
   
## Getting Started
* Install `node` and `npm`
* Run `npm install` in the project directory
* Start the server: `node bin/www`
* * The server is now running at localhost:3000
* * / serves the dot drawing page for the projector
* * /client.html is a mouse/tablet input method that sends input to the server over socket.io
* Start the serial adapter: `node bin/arduino-adapter`
* * It will establish a socket connection to the server and a serial connection to Arduino
* Make sure the Arduino has `arduino/motor_controller/motor_controller.ino` uploaded

## Hardware Pinouts

TODO