#!/usr/bin/env bash
set -e
CERT_DIR="$(dirname "$0")/../../certs"
DATA_CERT_DIR="$(dirname "$0")/../../data/certs"
mkdir -p "$CERT_DIR"
mkdir -p "$DATA_CERT_DIR"

# Generate self-signed certificate
openssl req -x509 -nodes -days 365 -newkey rsa:2048 \
  -keyout "$CERT_DIR/server.key" \
  -out "$CERT_DIR/server.crt" \
  -subj "/C=IT/ST=Italy/L=City/O=ESP32Dev/CN=esp32.local"

# Copy to data/certs for SPIFFS
cp "$CERT_DIR/server.key" "$DATA_CERT_DIR/server.key"
cp "$CERT_DIR/server.crt" "$DATA_CERT_DIR/server.crt"

echo "Certificate and key generated in $CERT_DIR and copied to $DATA_CERT_DIR."
