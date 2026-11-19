# DPF Monitor v. 0.1

Prototypowy firmware startowy dla ESP32-S3 DevKitC-1 N16R8.

## Funkcje
- start ESP32-S3 i komunikaty USB CDC/Serial 115200,
- komendy HELP, INFO, SCAN, STOP,
- skanowanie BLE przez NimBLE i wypisanie znalezionych urządzeń,
- bezpieczny tryb: brak poleceń do ECU, brak kasowania DTC i brak wymuszania regeneracji.

## Kompilacja
Projekt jest przeznaczony do PlatformIO:
`pio run -e esp32-s3-devkitc-1`

Plik wynikowy: `.pio/build/esp32-s3-devkitc-1/firmware.bin`

## Flashowanie
To jest standardowy obraz aplikacji PlatformIO `firmware.bin`, przeznaczony do wgrania jako aplikacja przy adresie `0x10000`, a nie kompletny obraz scalony z bootloaderem i tabelą partycji. W aplikacji flashującej należy użyć trybu wgrywania pojedynczego firmware pod adresem `0x10000`. Jeśli aplikacja wymaga pełnego obrazu lub wielu plików, należy najpierw przygotować wariant merged.

## Uwaga
Kompilacja i działanie na fizycznej płytce muszą zostać potwierdzone. N16R8 oznacza 16 MB flash i 8 MB PSRAM; ustawienia pamięci są skonfigurowane dla wariantu OPI PSRAM.
