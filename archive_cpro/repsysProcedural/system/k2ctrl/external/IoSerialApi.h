/*------------------------------------------------------------------------------
*                             (c) 2014 by KEBA AG
*                                www.keba.com
*                                Linz/Austria
*                             All rights reserved
*-------------------------------------------------------------------------------
*/
/** @file
*   @brief Interface for communication with the serial port.
*
*   This interface supports various methods for using the serial port.
*   It can be used to rad and write data from the serial port as well as set
*   the operation parameters.
*/
/*------------------------------------------------------------------------------
*/

#ifndef IOSERIALAPI_H_
#define IOSERIALAPI_H_

/*------------------------------------------------------------------------------
*  Includes
*/
#include "IoSerialApi.h"
#include "IoApiTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------------------------
*  Typedefs
*/

/******************************************************************************/
/**
 *  Modes for opening a serial interface device.
 */
typedef uint32_t IoSioOpenMode;
enum {
   eIoSioOpenReadOnly    = 0,      /**< for read only access */
   eIoSioOpenWriteOnly   = 1,      /**< for write only access */
   eIoSioOpenReadWrite   = 2       /**< for read and write access */
};

/******************************************************************************/
/**
 *  Operationmode types.
 */
typedef uint32_t IoSioOperationMode;
enum {
   eIoSioModeDefault     = 0, /**< Default mode, depends of device */
   eIoSioModeXonXoff     = 1, /**< XON/XOFF mode */
   eIoSioModeRs232RtsCts = 2, /**< RTS and CTS flowcontrol on RS232 interface */
   eIoSioModeRs485       = 3, /**< RS485 mode */
   eIoSioModeRs232       = 4, /**< RS232 mode */
   eIoSioModeRs422       = 5, /**< RS422 mode */
   eIoSioModeCurrLoop    = 6  /**< Current loop mode */
};

/******************************************************************************/
/**
 *  Parity bit settings.
 */
typedef uint32_t IoSioParity;
enum {
   eIoSioParityNone   = 0,      /**< no parity */
   eIoSioParityEven   = 1,      /**< even parity */
   eIoSioParityOdd    = 2       /**< odd parity */
};

/******************************************************************************/
/**
 *  Stop bit settings.
 */
typedef uint32_t IoSioStopBits;
enum {
   eIoSioStopbit_1      = 0,   /**< 1 stop bit */
   eIoSioStopbit_1_5    = 1,   /**< 1 1/2 stop bit */
   eIoSioStopbit_2      = 2    /**< 2 stop bits */
};

/******************************************************************************/
/**
 *  Data bits.
 */
typedef uint32_t IoSioDataBits;
enum {
   eIoSioDatabit_5   = 5,      /**< 5 data bits */
   eIoSioDatabit_6   = 6,      /**< 6 data bits */
   eIoSioDatabit_7   = 7,      /**< 7 data bits */
   eIoSioDatabit_8   = 8       /**< 8 data bits */
};

/******************************************************************************/
/**
 *  Baud rates.
 */
typedef uint32_t IoSioBaudrates;
enum {
   eIoSioBaudrate_300      = 300,      /**< 300 baud */
   eIoSioBaudrate_600      = 600,      /**< 600 baud */
   eIoSioBaudrate_1200     = 1200,     /**< 1200 baud */
   eIoSioBaudrate_1800     = 1800,     /**< 1800 baud */
   eIoSioBaudrate_2400     = 2400,     /**< 2400 baud */
   eIoSioBaudrate_3600     = 3600,     /**< 3600 baud */
   eIoSioBaudrate_4800     = 4800,     /**< 4800 baud */
   eIoSioBaudrate_7200     = 7200,     /**< 7200 baud */
   eIoSioBaudrate_9600     = 9600,     /**< 9600 baud */
   eIoSioBaudrate_19200    = 19200,    /**< 19200 baud */
   eIoSioBaudrate_38400    = 38400,    /**< 38400 baud */
   eIoSioBaudrate_57600    = 57600,    /**< 57600 baud */
   eIoSioBaudrate_115200   = 115200    /**< 115200 baud */
};

/******************************************************************************/
/**
 *  @brief Open a serial IO device.
 *
 *  This method opens a serial IO device.
 *
 * @return State information about the operation.
 *         IoApiStateOk, if serial device could be opened.
 *         IoApiStateNotOk, if serial device failed to open.
 */
IoApiState IoApiSioOpen(
   IoApiHdl        devHdl,      /**< [in]  Device handle */
   IoSioOpenMode   mode         /**< [in]  Open mode */
   );


/******************************************************************************/
/**
 *  @brief Close a serial IO device.
 *
 *  This method closes a serial IO device.
 *
 * @return State information about the operation.
 *         IoApiStateOk, if serial device could be closed.
 *         IoApiStateNotOk, if serial device failed to close.
 */
IoApiState IoApiSioClose(
   IoApiHdl devHdl      /**< [in]  Device handle */
   );



/******************************************************************************/
/**
 *  @brief Read data from a serial IO device.
 *
 *  This method reads data from a serial IO device.
 *
 * @return State information about the operation.
 *         IoApiStateOk, if serial transfer succeeded.
 *         IoApiStateInvalidAddr, if pBuffer or pResult are invalid pointers.
 *         IoApiStateTimeout, if a timeout occurred.
 *         IoApiStateNotOk, if serial transfer failed.
 */
IoApiState IoApiSioRead(
   IoApiHdl  devHdl,    /**< [in]  Device handle */
   char     *pBuffer,   /**< [out] Buffer for data to read */
   uint32_t  cntBytes,  /**< [in]  Number of bytes that should be read, buffer
                                   has to be big enough for cntBytes */
   uint32_t  timeoutUs, /**< [in]  Timeout in microseconds for receiving data */
   uint32_t *pResult    /**< [out] Number of bytes read */
   );



/******************************************************************************/
/**
 *  @brief Write data to a serial IO device.
 *
 *  This method writes data to a serial IO device.
 *
 * @return State information about the operation.
 *         IoApiStateOk, if serial transfer succeeded.
 *         IoApiStateInvalidAddr, if pBuffer or pResult are invalid pointers.
 *         IoApiStateNotOk, if serial transfer failed.
 */
IoApiState IoApiSioWrite(
   IoApiHdl      devHdl,       /**< [in]  Device handle */
   char         *pBuffer,      /**< [in]  Buffer with data to write */
   uint32_t      cntBytes,     /**< [in]  Number of bytes to write */
   uint32_t     *pResult       /**< [out] Number of bytes written */
   );


/******************************************************************************/
/**
 *  @brief Get number of characters available to read. (FIONREAD)
 *
 *  This Function retrieves the number of characters which are available to read.
 *
 * @return State information about the operation.
 *         IoApiStateOk, if serial transfer succeeded.
 *         IoApiStateInvalidHandle, if devHdl points to an invalid device.
 *         IoApiStateInvalidAddr, if numChars is an invalid pointer.
 *         IoApiStateNotOk, if serial transfer failed.
 */
IoApiState IoApiSioNRead(
   IoApiHdl     devHdl,       /**< [in]  Device handle */
   int         *numChars      /**< [out] Number of characters to be read */
   );


/******************************************************************************/
/**
 *  @brief Get number of characters still to be written. (FIONWRITE)
 *
 *  This Function retrieves the number of characters which are still to be written.
 *
 * @return State information about the operation.
 *         IoApiStateOk, if serial transfer succeeded.
 *         IoApiStateInvalidHandle, if devHdl points to an invalid device.
 *         IoApiStateInvalidAddr, if numChars is an invalid pointer.
 *         IoApiStateNotOk, if serial transfer failed.
 */
IoApiState IoApiSioNWrite(
   IoApiHdl     devHdl,   /**< [in]  Device handle */
   int         *numChars  /**< [out] Number of characters still to be written */
   );


/******************************************************************************/
/**
 *  @brief Get remaining size of the write buffer.
 *
 *  This function retrieves the number of characters which can be written to the write buffer.
 *
 * @return State information about the operation.
 *         IoApiStateOk, if serial transfer succeeded.
 *         IoApiStateInvalidHandle, if devHdl points to an invalid device.
 *         IoApiStateInvalidAddr, if numChars is an invalid pointer.
 *         IoApiStateNotOk, if serial transfer failed.
 */
IoApiState IoApiSioGetNumCharsAvailableForFreeWrite(
   IoApiHdl  devHdl,  /**< [in]  Device handle */
   int      *numChars /**< [out] Remaining size for characters in the write buffer */
   );


/******************************************************************************/
/**
 *  @brief Flush characters in buffers. (FIOFLUSH)
 *
 *  Discard all characters in the read and write buffers.
 *
 * @return State information about the operation.
 *         IoApiStateOk, if flushing buffer succeeded.
 *         IoApiStateInvalidHandle, if devHdl points to an invalid device.
 *         IoApiStateNotOk, if flushing buffer failed.
 */
IoApiState IoApiSioFlush(
   IoApiHdl       devHdl      /**< [in]  Device handle */
   );


/******************************************************************************/
/**
 *  @brief Flush characters in read buffers. (FIORFLUSH)
 *
 *  Discard all characters in the read buffer.
 *
 * @return State information about the operation.
 *         IoApiStateOk, if flushing buffer succeeded.
 *         IoApiStateInvalidHandle, if devHdl points to an invalid device.
 *         IoApiStateNotOk, if flushing buffer failed.
 */
IoApiState IoApiSioFlushReadBuffer(
   IoApiHdl       devHdl      /**< [in]  Device handle */
   );


/******************************************************************************/
/**
 *  @brief Flush characters in write buffers. (FIOWFLUSH)
 *
 *  Discard all characters in the write buffer.
 *
 * @return State information about the operation.
 *         IoApiStateOk, if flushing buffer succeeded.
 *         IoApiStateInvalidHandle, if devHdl points to an invalid device.
 *         IoApiStateNotOk, if flushing buffer failed.
 */
IoApiState IoApiSioFlushWriteBuffer(
   IoApiHdl       devHdl      /**< [in]  Device handle */
   );


/******************************************************************************/
/**
 *  @brief Set serial baud rate. (FIOBAUDRATE)
 *
 *  This Function sets the serial baud rate.
 *
 * @return State information about the operation.
 *         IoApiStateOk, if baudrate is set successfully.
 *         IoApiStateInvalidHandle, if devHdl points to an invalid device.
 *         IoApiStateNotOk, if setting baudrate failed.
 */
IoApiState IoApiSioSetBaudrate(
   IoApiHdl            devHdl,       /**< [in]  Device handle */
   IoSioBaudrates      baudrate      /**< [in]  Serial baudrate */
   );


/******************************************************************************/
/**
 *  @brief Get serial settings.
 *
 *  This Function gets serial configuration settings.
 *
 * @return State information about the operation.
 *         IoApiStateOk, if settings could be read successfully.
 *         IoApiStateInvalidHandle, if devHdl points to an invalid device.
 *         IoApiStateInvalidAddr, if on of the output pointers is invalid.
 *         IoApiStateNotOk, if settings could not be read.
 */
IoApiState IoApiSioGetSettings(
   IoApiHdl              devHdl,        /**< [in]  Device handle */
   IoSioBaudrates       *baudRate,      /**< [out] Baud rate, unit Baud */
   IoSioStopBits        *stopBits,      /**< [out] Stop bits */
   IoSioParity          *parity,        /**< [out] Parity */
   IoSioDataBits        *dataBits,      /**< [out] Number of data bits */
   IoSioOperationMode   *mode           /**< [out] Operation type */
   );


/******************************************************************************/
/**
 *  @brief Set serial settings.
 *
 *  This Function sets serial configuration settings.
 *
 * @return State information about the operation.
 *         IoApiStateOk, if settings could be written successfully.
 *         IoApiStateInvalidHandle, if devHdl points to an invalid device.
 *         IoApiStateNotOk, if settings could not be written.
 */
IoApiState IoApiSioSetSettings(
   IoApiHdl             devHdl,        /**< [in]  Device handle */
   IoSioBaudrates       baudRate,      /**< [in]  Baud rate, unit Baud */
   IoSioStopBits        stopBits,      /**< [in]  Stop bits */
   IoSioParity          parity,        /**< [in]  Parity */
   IoSioDataBits        dataBits,      /**< [in]  Number of data bits */
   IoSioOperationMode   mode           /**< [in]  Operation type */
   );


/******************************************************************************/
/**
 *  @brief Set read buffer size.
 *
 *  This Function sets read buffer size.
 *
 * @return State information about the operation.
 *         IoApiStateOk, if buffer size is written successfully.
 *         IoApiStateInvalidHandle, if devHdl points to an invalid device.
 *         IoApiStateNotOk, if buffer size could not be set.
 */
IoApiState IoApiSioSetReadBufSize(
   IoApiHdl    devHdl,      /**< [in]  Device handle */
   int         size         /**< [in]  Buffer size */
   );


/******************************************************************************/
/**
 *  @brief Set write buffer size.
 *
 *  This Function sets write buffer size.
 *
 * @return State information about the operation.
 *         IoApiStateOk, if buffer size is written successfully.
 *         IoApiStateInvalidHandle, if devHdl points to an invalid device.
 *         IoApiStateNotOk, if buffer size could not be set.
 */
IoApiState IoApiSioSetWriteBufSize(
   IoApiHdl    devHdl,      /**< [in]  Device handle */
   int         size         /**< [in]  Buffer size */
   );


/******************************************************************************/
/**
 *  @brief Get read buffer size.
 *
 *  This Function gets read buffer size.
 *
 * @return State information about the operation.
 *         IoApiStateOk, if reading buffer size succeeded.
 *         IoApiStateInvalidHandle, if devHdl points to an invalid device.
 *         IoApiStateInvalidAddr, if size is an invalid pointer.
 *         IoApiStateNotOk, if buffer size could not be read.
 */
IoApiState IoApiSioGetReadBufSize(
   IoApiHdl     devHdl,      /**< [in]  Device handle */
   int         *size         /**< [out] Buffer size */
   );


/******************************************************************************/
/**
 *  @brief Get write buffer size.
 *
 *  This Function gets write buffer size.
 *
 * @return State information about the operation.
 *         IoApiStateOk, if reading buffer size succeeded.
 *         IoApiStateInvalidHandle, if devHdl points to an invalid device.
 *         IoApiStateInvalidAddr, if size is an invalid pointer.
 *         IoApiStateNotOk, if buffer size could not be read.
 */
IoApiState IoApiSioGetWriteBufSize(
   IoApiHdl     devHdl,      /**< [in]  Device handle */
   int         *size         /**< [out] Buffer size */
   );

/******************************************************************************/
/**
 *  @brief Set operation mode.
 *
 *  This Function sets the operation mode for a serial device.
 *
 * @return State information about the operation.
 *         IoApiStateOk, if setting new mode succeeded.
 *         IoApiStateInvalidHandle, if devHdl points to an invalid device.
 *         IoApiStateNotOk, if new mode could not be set.
 */
IoApiState IoApiSioSetOperationMode(
   IoApiHdl             devHdl,      /**< [in]  Device handle */
   IoSioOperationMode   mode         /**< [in]  Operation mode */
   );

/******************************************************************************/
/**
 *  @brief Sets or resets RTS.
 *
 *  Sets or resets RTS.
 *
 * @return State information about the operation.
 *         IoApiStateOk, if setting/resetting RTS succeeded.
 *         IoApiStateInvalidHandle, if devHdl points to an invalid device.
 *         IoApiStateNotOk, if RTS could not be set.
 */
IoApiState IoApiSioReSetRts(
   IoApiHdl    devHdl,      /**< [in]  Device handle */
   int         reset         /**< [in]  Set/reset RTS */
   );

/******************************************************************************/
/**
 *  @brief Gets CTS.
 *
 *  Gets CTS line - only useable in RS232 mode
 *
 * @return State information about the operation.
 *         IoApiStateOk, if getting CTS succeeded.
 *         IoApiStateInvalidHandle, if devHdl points to an invalid device.
 *         IoApiStateNotOk, if CTS could not be get.
 */
IoApiState IoApiSioGetCts(
   IoApiHdl    devHdl,      /**< [in]  Device handle */
   int        *cts          /**< [out]  CTS line */
   );


/******************************************************************************/
/**
 *  @brief Sets or resets DTR.
 *
 *  Sets or resets DTR.
 *
 * @return State information about the operation.
 *         IoApiStateOk, if setting/resetting DTR succeeded.
 *         IoApiStateInvalidHandle, if devHdl points to an invalid device.
 *         IoApiStateNotOk, if DTR could not be set.
 */
IoApiState IoApiSioReSetDtr(
   IoApiHdl    devHdl,      /**< [in]  Device handle */
   int         reset        /**< [in]  Set/reset DTR  */
   );


#ifdef __cplusplus
}
#endif

#endif /* IOSERIALAPI_H_ */
