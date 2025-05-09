$certDir = Join-Path $PSScriptRoot "..\..\certs"
$dataCertDir = Join-Path $PSScriptRoot "..\..\data\certs"
New-Item -ItemType Directory -Force -Path $certDir | Out-Null
New-Item -ItemType Directory -Force -Path $dataCertDir | Out-Null

$certPath = Join-Path $certDir "server.crt"
$keyPath = Join-Path $certDir "server.key"

# Generate self-signed certificate
openssl req -x509 -nodes -days 365 -newkey rsa:2048 `
  -keyout $keyPath `
  -out $certPath `
  -subj "/C=IT/ST=Italy/L=City/O=ESP32Dev/CN=esp32.local"

# Copy to data/certs for SPIFFS
Copy-Item $keyPath (Join-Path $dataCertDir "server.key") -Force
Copy-Item $certPath (Join-Path $dataCertDir "server.crt") -Force

Write-Host "Certificate and key generated in $certDir and copied to $dataCertDir."
