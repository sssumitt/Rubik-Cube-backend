FROM ubuntu:22.04

# Install build tools + git for grabbing Crow
RUN apt update && \
    apt install -y g++ make cmake curl libboost-all-dev git

# Pull Crow single-header and install it under include/
WORKDIR /app
COPY . . 

# Fetch Crow’s amalgamated header and rename to crow.h
RUN git clone --depth 1 https://github.com/CrowCpp/Crow.git /tmp/crow && \
    cp /tmp/crow/include/crow_all.h include/crow.h

# Build the app
RUN make

# Expose Crow’s port
EXPOSE 18080

CMD ["./cube_backend"]
