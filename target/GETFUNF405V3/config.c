/*
 * Runtime defaults for GETFUNF405V3.
 */

#include <stdint.h>
#include <stdbool.h>
#include <platform.h>

#include "fc/fc_msp_box.h"
#include "io/piniobox.h"
#include "io/serial.h"
#include "drivers/serial.h"

void targetConfiguration(void)
{
    // PINIO1 (PC4) -> USER1, PINIO2 (PC5) -> USER2 mode switches
    pinioBoxConfigMutable()->permanentId[0] = BOX_PERMANENT_ID_USER1;
    pinioBoxConfigMutable()->permanentId[1] = BOX_PERMANENT_ID_USER2;

    // GPS (u-blox M10) is wired to UART6 and configured for 57600 baud
    serialConfigMutable()->portConfigs[findSerialPortIndexByIdentifier(SERIAL_PORT_USART6)].functionMask = FUNCTION_GPS;
    serialConfigMutable()->portConfigs[findSerialPortIndexByIdentifier(SERIAL_PORT_USART6)].gps_baudrateIndex = BAUD_57600;
}
