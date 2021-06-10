#ifndef __DRIVER_COMMON_H___
#define __DRIVER_COMMON_H___

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#define DRIVER_VERSION_MAJOR_MINOR(major,minor) (((major) << 8) | (minor))

typedef struct _DRIVER_VERSION {
  uint16_t api;                         ///< API version
  uint16_t drv;                         ///< Driver version
} DRIVER_VERSION;

/* General return codes */
#define DRIVER_OK                 0 ///< Operation succeeded 
#define DRIVER_ERROR             -1 ///< Unspecified error
#define DRIVER_ERROR_BUSY        -2 ///< Driver is busy
#define DRIVER_ERROR_TIMEOUT     -3 ///< Timeout occurred
#define DRIVER_ERROR_UNSUPPORTED -4 ///< Operation not supported
#define DRIVER_ERROR_PARAMETER   -5 ///< Parameter error
#define DRIVER_ERROR_SPECIFIC    -6 ///< Start of driver specific errors 

typedef enum _POWER_STATE {
  POWER_OFF,                        ///< Power off: no operation possible
  POWER_LOW,                        ///< Low Power mode: retain state, detect and signal wake-up events
  POWER_FULL                        ///< Power on: full operation at maximum performance
} POWER_STATE;

#endif /* __DRIVER_COMMON_H__*/
