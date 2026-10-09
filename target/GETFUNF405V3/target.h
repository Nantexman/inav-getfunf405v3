/*
 * Custom INAV target for GETFUNF405V3 (no-name AliExpress F405 stack)
 * Pin map extracted from the live board via Betaflight CLI `resource` dump.
 *
 * Hardware: STM32F405, ICM42688P (SPI1, CS PA4), DPS310 baro (I2C1),
 * MAX7456 OSD (SPI2, CS PB12), W25Q128 16MB flash (SPI3, CS PC13).
 * NOTE: board has no HSE crystal (Betaflight reports PLLP-HSI) -
 * the HSI clock patch (patches/apply_hsi.py) is required to boot.
 */

#pragma once

#define TARGET_BOARD_IDENTIFIER "GF4V"
#define USBD_PRODUCT_STRING     "GETFUNF405V3"

#define USE_TARGET_CONFIG

// *************** LEDs & Beeper ***************
#define LED0                    PC15
#define LED1                    PC14

#define BEEPER                  PB0
#define BEEPER_INVERTED

// *************** SPI ***************
#define USE_SPI

#define USE_SPI_DEVICE_1        // Gyro
#define SPI1_SCK_PIN            PA5
#define SPI1_MISO_PIN           PA6
#define SPI1_MOSI_PIN           PA7

#define USE_SPI_DEVICE_2        // OSD
#define SPI2_SCK_PIN            PB13
#define SPI2_MISO_PIN           PB14
#define SPI2_MOSI_PIN           PB15

#define USE_SPI_DEVICE_3        // Blackbox flash
#define SPI3_SCK_PIN            PB3
#define SPI3_MISO_PIN           PB4
#define SPI3_MOSI_PIN           PB5

// *************** I2C (baro + external mag) ***************
#define USE_I2C
#define USE_I2C_DEVICE_1
#define I2C1_SCL                PB8
#define I2C1_SDA                PB9

// *************** IMU ***************
// ICM42688P is auto-detected by the ICM42605 driver (shared WHO_AM_I table)
// CW90 comes from the board's factory Betaflight config (gyro_1_sensor_align)
#define USE_IMU_ICM42605
#define IMU_ICM42605_ALIGN      CW90_DEG
#define ICM42605_SPI_BUS        BUS_SPI1
#define ICM42605_CS_PIN         PA4

// *************** OSD ***************
#define USE_MAX7456
#define MAX7456_SPI_BUS         BUS_SPI2
#define MAX7456_CS_PIN          PB12

// *************** Flash (W25Q128, JEDEC 0xEF4018) ***************
#define USE_FLASHFS
#define USE_FLASH_M25P16
#define M25P16_SPI_BUS          BUS_SPI3
#define M25P16_CS_PIN           PC13
#define ENABLE_BLACKBOX_LOGGING_ON_SPIFLASH_BY_DEFAULT

// *************** Baro (DPS310 on I2C1) ***************
#define USE_BARO
#define BARO_I2C_BUS            BUS_I2C1
#define USE_BARO_DPS310
#define USE_BARO_BMP280
#define USE_BARO_SPL06

// *************** Mag (external compass on I2C1) ***************
#define USE_MAG
#define MAG_I2C_BUS             BUS_I2C1
#define USE_MAG_ALL

// *************** UARTs ***************
#define USE_VCP
#define USB_DETECT_PIN          PC3

#define USE_UART1
#define UART1_RX_PIN            PB7
#define UART1_TX_PIN            PB6

#define USE_UART2
#define UART2_RX_PIN            PA3
#define UART2_TX_PIN            PA2

#define USE_UART3
#define UART3_RX_PIN            PC11
#define UART3_TX_PIN            PC10

#define USE_UART4
#define UART4_RX_PIN            PA1
#define UART4_TX_PIN            PA0

#define USE_UART5
#define UART5_RX_PIN            PD2
#define UART5_TX_PIN            PC12

#define USE_UART6
#define UART6_RX_PIN            PC7
#define UART6_TX_PIN            PC6

#define SERIAL_PORT_COUNT       7

// *************** ADC (VBAT/CURR/RSSI) ***************
#define USE_ADC
#define ADC_CHANNEL_1_PIN       PC0     // VBAT
#define ADC_CHANNEL_2_PIN       PC1     // Current
#define ADC_CHANNEL_3_PIN       PC2     // RSSI
#define VBAT_ADC_CHANNEL            ADC_CHN_1
#define CURRENT_METER_ADC_CHANNEL   ADC_CHN_2
#define RSSI_ADC_CHANNEL            ADC_CHN_3

#define CURRENT_METER_SCALE     250     // typical for 50-60A stacks, calibrate later

// *************** PINIO (VTX power / user switches) ***************
#define USE_PINIO
#define USE_PINIOBOX
#define PINIO1_PIN              PC4
#define PINIO2_PIN              PC5

// *************** VTX ***************
#define USE_VTX_COMMON
#define USE_VTX_TRAMP
#define USE_VTX_SMARTAUDIO

// *************** LED strip ***************
#define USE_LED_STRIP
#define WS2811_PIN              PB1

// *************** Defaults ***************
#define DEFAULT_RX_TYPE         RX_TYPE_SERIAL
#define SERIALRX_PROVIDER       SERIALRX_SBUS

#define DEFAULT_FEATURES        (FEATURE_TX_PROF_SEL | FEATURE_OSD | FEATURE_CURRENT_METER | FEATURE_VBAT | FEATURE_TELEMETRY)

// *************** Motor outputs ***************
#define USE_SERIAL_4WAY_BLHELI_INTERFACE
#define MAX_PWM_OUTPUT_PORTS    8
#define USE_DSHOT
#define USE_ESC_SENSOR

// *************** Optical Flow and Lidar ***************
#define USE_RANGEFINDER
#define USE_RANGEFINDER_MSP
#define USE_OPFLOW
#define USE_OPFLOW_MSP

#define TARGET_IO_PORTA         0xffff
#define TARGET_IO_PORTB         0xffff
#define TARGET_IO_PORTC         0xffff
#define TARGET_IO_PORTD         (BIT(2))
