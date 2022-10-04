#include "Adafruit_Sensor_Calibration.h"

#if defined(ADAFRUIT_SENSOR_CALIBRATION_USE_SDFAT)

#ifdef ADAFRUIT_SENSOR_CALIBRATION_USE_FLASH
#ifdef ADAFRUIT_SENSOR_CALIBRATION_USE_QSPIFLASH
static Adafruit_FlashTransport_QSPI flashTransport(PIN_QSPI_SCK, PIN_QSPI_CS,
                                                   PIN_QSPI_IO0, PIN_QSPI_IO1,
                                                   PIN_QSPI_IO2, PIN_QSPI_IO3);
#elif defined(ADAFRUIT_SENSOR_CALIBRATION_USE_SPIFLASH)
static Adafruit_FlashTransport_SPI flashTransport(EXTERNAL_FLASH_USE_CS,
                                                  &EXTERNAL_FLASH_USE_SPI);
#endif

static Adafruit_SPIFlash flash(&flashTransport);
static FatFileSystem fatfs;
#endif

#else
    return false;
#endif
  


