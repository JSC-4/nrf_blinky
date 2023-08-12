This is a basic project for building the blinky nRF52840 exmaple using CMake.

Following commands used to run the example
docker build -f .\Dockerfile -t nrf-basic .   
docker run -it -v ${PWD}:/app nrf-basic  

cmake . -B _build -GNinja
cmake --build _build --target blinky -j