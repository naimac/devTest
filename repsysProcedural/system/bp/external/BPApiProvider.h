/*------------------------------------------------------------------------------
*                             (c) 2014 by KEBA AG
*                                www.keba.com
*                                Linz/Austria
*                             All rights reserved
*-------------------------------------------------------------------------------
*/
/** @file
*   @brief Interface for creating variable providers
*
*   These interfaces may be used to register variable providers for native libraries.
*   This makes selected global and static variables, including variables from user
*   defined data types such as structures and arrays, available to the variable server
*   and to BpApiVar access functions. A binary library file (*.so), and the corresponding
*   compiled library load information file (*.clf) need to be specified.
*   The *.clf file may be generated using the variable symbol information generator
*   (VarSymInfoGen) from the linker symbol information, the *.so file and a variable
*   selection file. The *.clf file must match the checksum of the *.so file, so it is
*   recommended to generate the *.clf file along with the *.so file (e.g., by a
*   post-build step or a make target).
*
*/
/*------------------------------------------------------------------------------
*/

#ifndef PACKAGE_API_PROVIDER_H
#define PACKAGE_API_PROVIDER_H

#include "BPApiTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/** The requested lock action for the ::BPApiProviderLockFunc callback. */
typedef uint32_t BPApiProviderLockAction;
enum {
   BPApiProviderLockActionUnlock = 0,                /**< The lock action 'to unlock'. */
   BPApiProviderLockActionLock   = 1                 /**< The lock action 'to lock'. */
};

/** Handle type for a provider. */
typedef uint32_t BPApiProviderHdl;

/** The callback reason type for the ::BPApiProviderLockFunc callback. */
typedef uint32_t BPApiProviderCall;
enum {
   BPApiProviderCallInit   = 0,                      /**< The callback reason 'Init'. */
   BPApiProviderCallExit   = 1,                      /**< The callback reason 'Exit'. */
   BPApiProviderCallRead   = 2,                      /**< The callback reason 'Read'. */
   BPApiProviderCallWrite  = 3,                      /**< The callback reason 'Write'. */
   BPApiProviderCallBrowse = 4                       /**< The callback reason 'Browse'. */
};

/** The callback function type for the provider access control. */
typedef void (*BPApiProviderLockFunc)(
   BPApiProviderLockAction lock,                     /**< The requested lock action. */
   BPApiProviderHdl providerHdl,                     /**< The handle of the provider. */
   BPApiProviderCall providerCall                    /**< The callback reason. */
   );

/******************************************************************************/
/**
 * @brief Create a variable provider registration (ASCII)
 *
 * Create a variable provider registration of the specified binary object and
 * clf file.
 *
 * @return  ::BPApiStateOk on success,<BR>
 *          ::BPApiStateParamError if 'providerHdl', 'binaryFilename' or 'clfFilename' is NULL,<BR>
 *          ::BPApiProviderFileNotFound if 'binaryFilename' or 'clfFilename' cannot be found,<BR>
 *          ::BPApiProviderInvalidFile if 'clfFilename' is invalid,<BR>
 *          ::BPApiProviderLoadError if 'binaryFilename' (library) cannot be loaded,<BR>
 *          ::BPApiProviderCRCMismatch if 'clfFilename' is invalid or doesn't match to 'binaryFilename',<BR>
 *          other errorCodes for internal errors
 */
BPApiState BPApiProviderCreateA (
   const char *libraryFilename,                      /**< [in]  The file path to the library or NULL for the current executable. */
   const char *clfFilename,                          /**< [in]  The file path to the clf file. */
   BPApiProviderLockFunc lockFunc,                   /**< [in]  The lock callback (optional - can be NULL). */
   BPApiProviderHdl *providerHdl                     /**< [out] Returns the provider handle. */
   );

/******************************************************************************/
/**
 * @brief Create a variable provider registration (Unicode)
 *
 * Create a variable provider registration of the specified binary object and
 * clf file.
 *
 * @return  ::BPApiStateOk on success,<BR>
 *          ::BPApiStateParamError if 'providerHdl', 'binaryFilename' or 'clfFilename' is NULL,<BR>
 *          ::BPApiProviderFileNotFound if 'binaryFilename' or 'clfFilename' cannot be found,<BR>
 *          ::BPApiProviderInvalidFile if 'clfFilename' is invalid,<BR>
 *          ::BPApiProviderLoadError if 'binaryFilename' (library) cannot be loaded,<BR>
 *          ::BPApiProviderCRCMismatch if 'clfFilename' is invalid or doesn't match to 'binaryFilename',<BR>
 *          other errorCodes for internal errors
 */
BPApiState BPApiProviderCreateW (
   const wchar_t *libraryFilename,                   /**< [in]  The file path to the library or NULL for the current executable. */
   const wchar_t *clfFilename,                       /**< [in]  The file path to the clf file. */
   BPApiProviderLockFunc lockFunc,                   /**< [in]  The lock callback (optional - can be NULL). */
   BPApiProviderHdl *providerHdl                     /**< [out] Returns the provider handle. */
   );

/******************************************************************************/
/**
 * @brief Delete a variable provider registration
 *
 * Delete a variable provider registration, which has been created by ::BPApiProviderCreateA
 * or ::BPApiProviderCreateW.
 *
 * @return  ::BPApiStateOk on success,<BR>
 *          ::BPApiStateParamError if 'providerHdl' is invalid,<BR>
 *          other errorCodes for internal errors
 */
BPApiState BPApiProviderDelete (
   BPApiProviderHdl providerHdl                      /**< [in]  The handle of the provider. */
   );

/** @cond */
#ifdef UNICODE
   #define BPApiProviderCreate BPApiProviderCreateW
#else
   #define BPApiProviderCreate BPApiProviderCreateA
#endif
/** @endcond */

#ifdef __cplusplus
}
#endif /* C++ */

#endif /* PACKAGE_API_PROVIDER_H_INCLUDED */
