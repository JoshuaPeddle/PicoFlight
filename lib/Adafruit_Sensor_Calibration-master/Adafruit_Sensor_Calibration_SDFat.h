#ifndef __ADAFRUIT_SENSOR_CALIBRATION_SDFAT__
#define __ADAFRUIT_SENSOR_CALIBRATION_SDFAT__



#if defined(ADAFRUIT_SENSOR_CALIBRATION_USE_SDFAT)

// Use filesystem! Must be SdFat derived

// We'll need Arduino JSON to store in a file


#if defined(EXTERNAL_FLASH_DEVICES) || defined(PIN_QSPI_SCK)
#include <Adafruit_SPIFlash.h>
#define ADAFRUIT_SENSOR_CALIBRATION_USE_FLASH

#if defined(EXTERNAL_FLASH_USE_QSPI) || defined(PIN_QSPI_SCK)
#define ADAFRUIT_SENSOR_CALIBRATION_USE_QSPIFLASH
#elif defined(EXTERNAL_FLASH_USE_SPI)
#define ADAFRUIT_SENSOR_CALIBRATION_USE_SPIFLASH
#else
#error("Chip has external flash chip but no interface defined in variant!")
#endif

#endif


#endif

#endif // include once
