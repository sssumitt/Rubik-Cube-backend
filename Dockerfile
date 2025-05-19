FROM ubuntu:22.04

RUN apt update \
 && apt install -y g++ make cmake curl libboost-all-dev

WORKDIR /app
COPY . .

# Download crow_all.h (rename to crow.h)
RUN curl -fsSL "https://sourceforge.net/projects/crow-framework.mirror/files/v1.0%2B4/crow_all.h/download" \
     -o include/crow.h

RUN make

EXPOSE 18080
CMD ["./cube_backend"]
