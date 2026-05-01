# Combine the related files for a specific platform and MCU.

# Target ECU board design
BOARDCPPSRC = $(BOARD_DIR)/board_configuration.cpp
DDEFS += -DEFI_MAIN_RELAY_CONTROL=TRUE

# Add them all together
DDEFS += -DLED_CRITICAL_ERROR_BRAIN_PIN=Gpio::G0
DDEFS += -DFIRMWARE_ID=\"vthpnp\"

DDEFS += -DEFI_SOFTWARE_KNOCK=TRUE -DSTM32_ADC_USE_ADC3=TRUE

DDEFS += -DEFI_CONSOLE_TX_BRAIN_PIN=Gpio::D6 -DEFI_CONSOLE_RX_BRAIN_PIN=Gpio::D5
# DDEFS += -DTS_PRIMARY_UxART_PORT=SD2 -DEFI_TS_PRIMARY_IS_SERIAL=TRUE -DSTM32_SERIAL_USE_USART2=TRUE -DSTM32_UART_USE_USART2=FALSE

# Atlas has WiFi
USE_WIFI = yes

# Enable the SD card bootloader
SD_BOOTLOADER = no

# WiFi bootloader OTA doesn't fit in the 32KB F4 bootloader region
WIFI_BOOTLOADER = no

DDEFS += -DSTATIC_BOARD_ID=STATIC_BOARD_ID_VTHPNP

SHORT_BOARD_NAME = vthpnp

IS_STM32F429 = yes

# WiFi consumes extra SRAM vs proteus-base, so reduce Lua heap to fit in 192KB
DDEFS += -DLUA_USER_HEAP=50000



