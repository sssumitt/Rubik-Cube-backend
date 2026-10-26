# ---------- Build stage: compiler + headers, thrown away after build ----------
FROM ubuntu:22.04 AS build

RUN apt-get update && apt-get install -y --no-install-recommends \
        g++ make curl ca-certificates libboost-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY . .

# Crow single-header (v1.0+4)
RUN mkdir -p include && \
    curl -fsSL "https://github.com/CrowCpp/Crow/releases/download/v1.0%2B4/crow_all.h" \
        -o include/crow.h && \
    make

# ---------- Runtime stage: just the binary + solver tables ----------
FROM ubuntu:22.04

RUN useradd --create-home --uid 10001 appuser
WORKDIR /app

COPY --from=build /app/cube_backend .
COPY --from=build /app/Table ./Table

USER appuser
ENV PORT=5050
EXPOSE 5050

CMD ["./cube_backend"]
