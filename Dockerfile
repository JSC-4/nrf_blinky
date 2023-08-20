FROM ubuntu:20.04
ARG DEBIAN_FRONTEND=noninteractive

WORKDIR /app

# Download Linux support tools
RUN apt-get update && \
    apt-get clean && \
    apt-get install -y \
        curl unzip bzip2 cmake ninja-build python3-pip ruby wget

# Get ARM Toolchain
RUN wget https://developer.arm.com/-/media/Files/downloads/gnu-rm/10-2020q4/gcc-arm-none-eabi-10-2020-q4-major-x86_64-linux.tar.bz2 -O gcc-arm-none-eabi.tar.bz2 \
    && tar xvf gcc-arm-none-eabi.tar.bz2 \ 
    && rm gcc-arm-none-eabi.tar.bz2 \
    && mv gcc-arm-none-eabi-10-2020-q4-major /opt/ 
ENV PATH="/opt/gcc-arm-none-eabi-10-2020-q4-major/bin:$PATH"

# Add the project to the WORKDIR
ADD . ${WORKDIR}

# Build project
RUN cd ${WORKDIR} && \
  mkdir -p _build && \
  cmake . -B _build -GNinja && \
  cmake --build _build --target blinky -j

# RUN cd ${WORKDIR} 
# RUN ls 
# RUN pwd
# RUN mkdir -p _build
# RUN ls 
# RUN cmake . -B _build -GNinja
# RUN cmake --build _build --target blinky -j