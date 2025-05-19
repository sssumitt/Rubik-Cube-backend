FROM ubuntu:22.04

# Install dependencies
RUN apt update && apt install -y g++ make cmake curl libboost-all-dev

# Set working directory
WORKDIR /app

# Copy everything
COPY . .

# Build the app
RUN make

# Expose the port Crow uses (default 18080)
EXPOSE 18080

# Run the app (change name if needed)
CMD ["./cube_backend"]
