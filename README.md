# INAV 9.1.0 для GETFUNF405V3

Кастомный таргет INAV 9.1.0 для полётного контроллера GETFUNF405V3
(STM32F405, ICM42688P, баро DPS310, OSD MAX7456, флеш 16 МБ W25Q128).

Карта пинов восстановлена с живой платы через Betaflight CLI
(`resource`, `timer show`, `dma show`).

Важно: на плате нет кварца HSE (штатная прошивка работает на PLLP-HSI),
поэтому при сборке применяется патч `patches/apply_hsi.py`, тактующий PLL от HSI.

## Сборка

Прошивка собирается автоматически через GitHub Actions при каждом пуше:
готовый `.hex` появляется в разделе Releases.

Локально:

```sh
git clone --depth 1 --branch 9.1.0 https://github.com/iNavFlight/inav.git
cp -r target/GETFUNF405V3 inav/src/main/target/
cd inav && python3 ../patches/apply_hsi.py
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --target GETFUNF405V3 -j
# -> build/inav_9.1.0_GETFUNF405V3.hex
```
