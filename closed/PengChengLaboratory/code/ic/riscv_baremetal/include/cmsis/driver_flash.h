#ifndef DRIVER_FLASH_H_
#define DRIVER_FLASH_H_

#include "driver_common.h"

#define FLASH_API_VERSION DRIVER_VERSION_MAJOR_MINOR(1,0)  /* API version */

#define FLASH_SECTOR_INFO(addr,size) { (addr), (addr)+(size)-1 }

/**
\brief Flash Sector information
*/
typedef struct _FLASH_SECTOR {
  uint32_t start;                       // Sector Start address
  uint32_t end;                         // Sector End address (start+size-1)
} const FLASH_SECTOR;

/**
\brief Flash information
*/
typedef struct _FLASH_INFO {
  FLASH_SECTOR     *sector_info;        // Sector layout information (NULL=Uniform sectors)
  uint32_t          sector_count;       // Number of sectors
  uint32_t          sector_size;        // Uniform sector size in bytes (0=sector_info used) 
  uint32_t          page_size;          // Optimal programming page size in bytes
  uint32_t          program_unit;       // Smallest programmable unit in bytes
  uint8_t           erased_value;       // Contents of erased memory (usually 0xFF)
  uint8_t           reserved[3];        // Reserved (must be zero)
} const FLASH_INFO;


/**
\brief Flash Status
*/
typedef volatile struct _FLASH_STATUS {
  uint32_t busy     : 1;                // Flash busy flag
  uint32_t error    : 1;                // Read/Program/Erase error flag (cleared on start of next operation)
  uint32_t reserved : 30;
} FLASH_STATUS;


/****** Flash Event *****/
#define FLASH_EVENT_READY           (1UL << 0)  // Flash Ready
#define FLASH_EVENT_ERROR           (1UL << 1)  // Read/Program/Erase Error

typedef void (*Flash_SignalEvent_t) (uint32_t event);    // Pointer to Flash_SignalEvent : Signal Flash Event.


/**
\brief Flash Driver Capabilities.
*/
typedef struct _FLASH_CAPABILITIES {
  uint32_t event_ready  : 1;            // Signal Flash Ready event
  uint32_t data_width   : 2;            // Data width: 0=8-bit, 1=16-bit, 2=32-bit
  uint32_t erase_chip   : 1;            // Supports EraseChip operation
  uint32_t reserved     : 28;           // Reserved (must be zero)
} FLASH_CAPABILITIES;


/**
\brief Access structure of the Flash Driver
*/
typedef struct _DRIVER_FLASH {
  DRIVER_VERSION     (*GetVersion)     (void);
  FLASH_CAPABILITIES (*GetCapabilities)(void);
  int32_t            (*Initialize)     (Flash_SignalEvent_t cb_event);
  int32_t            (*Uninitialize)   (void);
  int32_t            (*PowerControl)   (POWER_STATE state);
  int32_t            (*ReadData)       (uint32_t addr,       void *data, uint32_t cnt);
  int32_t            (*ProgramData)    (uint32_t addr, const void *data, uint32_t cnt);
  int32_t            (*EraseSector)    (uint32_t addr);
  int32_t            (*EraseChip)      (void);
  FLASH_STATUS       (*GetStatus)      (void);
  FLASH_INFO *       (*GetInfo)        (void);
} const DRIVER_FLASH;

extern DRIVER_FLASH Driver_Flash;

#endif /* __DRIVER_FLASH_H__ */
