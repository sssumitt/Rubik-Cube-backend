FROM ubuntu:22.04

# Install build tools + git + python3
RUN apt update \
 && apt install -y g++ make cmake curl libboost-all-dev git python3

WORKDIR /app

# Copy your code in
COPY . .

# Clone Crow and use its merge script to produce crow.h
RUN git clone --depth 1 https://github.com/CrowCpp/Crow.git /tmp/crow \
 && python3 /tmp/crow/scripts/merge_all.py /tmp/crow/include include/crow.h

# Now build
RUN make

EXPOSE 18080
CMD ["./cube_backend"]
