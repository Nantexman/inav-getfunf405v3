#!/usr/bin/env python3
"""Patch INAV's F4 clock init for boards without an HSE crystal.

Stock INAV SetSysClock() waits for HSE and hangs in while(1) if it never
starts. GETFUNF405V3 has no crystal populated (the stock Betaflight build
reports "PLLP-HSI"), so we clock the PLL from HSI/16 instead:
16 MHz / 16 * 336 / 2 = 168 MHz SYSCLK, / 7 = 48 MHz USB.

The patch is guarded by #if defined(GETFUNF405V3) so other targets are
unaffected. Run from the INAV repo root.
"""

import pathlib
import sys

FILE = pathlib.Path("src/main/target/system_stm32f4xx.c")

ANCHOR = "  __IO uint32_t StartUpCounter = 0, HSEStatus = 0;\n\n  /* Enable HSE */"

REPLACEMENT = """  __IO uint32_t StartUpCounter = 0, HSEStatus = 0;

#if defined(GETFUNF405V3) && defined(STM32F40_41xxx)
  /* GETFUNF405V3 has no HSE crystal (stock firmware runs PLLP-HSI).
     Clock PLL from HSI/16: 16/16*336/2 = 168 MHz, /7 = 48 MHz USB. */
  (void)StartUpCounter;
  (void)HSEStatus;
  RCC->APB1ENR |= RCC_APB1ENR_PWREN;
  PWR->CR |= PWR_CR_VOS;
  RCC->CFGR |= RCC_CFGR_HPRE_DIV1;
  RCC->CFGR |= RCC_CFGR_PPRE2_DIV2;
  RCC->CFGR |= RCC_CFGR_PPRE1_DIV4;
  RCC->PLLCFGR = 16 | (PLL_N << 6) | (((PLL_P >> 1) - 1) << 16) | (PLL_Q << 24);
  RCC->CR |= RCC_CR_PLLON;
  while ((RCC->CR & RCC_CR_PLLRDY) == 0) {
  }
  FLASH->ACR = FLASH_ACR_PRFTEN | FLASH_ACR_ICEN | FLASH_ACR_DCEN | FLASH_ACR_LATENCY_5WS;
  RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
  RCC->CFGR |= RCC_CFGR_SW_PLL;
  while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL) {
  }
  SystemCoreClockUpdate();
  return;
#endif

  /* Enable HSE */"""

src = FILE.read_text()
if "GETFUNF405V3" in src:
    print("patch already applied")
    sys.exit(0)
if ANCHOR not in src:
    sys.exit("ERROR: anchor not found in " + str(FILE))
FILE.write_text(src.replace(ANCHOR, REPLACEMENT, 1))
print("HSI clock patch applied to", FILE)
