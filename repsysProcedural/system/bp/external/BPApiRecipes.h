 /*------------------------------------------------------------------------------
*                             (c) 2011 by KEBA AG
*                                www.keba.com
*                                Linz/Austria
*                             All rights reserved
*-------------------------------------------------------------------------------
*/
/** @file
* @brief Interface for variable recipes access
*
*   Interface for variable recipes access
*
*/
/*------------------------------------------------------------------------------
*/

#ifndef PACKAGE_API_RECIPE_H
#define PACKAGE_API_RECIPE_H


#include "BPApiTypes.h"


#ifdef __cplusplus
extern "C" {
#endif

typedef const char * BPApiRecipes_Name;                /**< name of recipe */
typedef const char * BPApiRecipes_FileName;            /**< file name including file extension (but without path) */
typedef const char * BPApiRecipes_FilePath;            /**< full file path (does not contain the file name!) */
typedef const char * BPApiRecipes_InstanceId;          /**< instance identification, e.g., "Hk[1]" */
typedef int32_t      BPApiRecipeAsyncHdl;              /**< handle used for asynchronous calls */

typedef const wchar_t * BPApiRecipes_NameW;            /**< name of recipe in Unicode */
typedef const wchar_t * BPApiRecipes_FileNameW;        /**< file name including file extension (but without path) in Unicode */
typedef const wchar_t * BPApiRecipes_FilePathW;        /**< full file path (does not contain the file name!) in Unicode*/
typedef const wchar_t * BPApiRecipes_InstanceIdW;      /**< instance identification in Unicode, e.g., "Hk[1]" */


/******************************************************************************/
/**
 * @brief Writes a recipe file (ASCII)
 *
 * Writes a recipe file in ASCII:
 *     Stores the current values of a set of variables defined by a
 *     variable group name (recipe name) a file with the defined name.
 *     Additionally a file path may be provided.
 *     Otherwise the recipe files is created in the default recipe directory.
 *
 * @return State information about the call.
 */
BPApiState BPApiRecipeWriteA (
   BPApiRecipes_Name       recipeName,                 /**< [in] name of recipe */
   BPApiRecipes_FileName   fileName,                   /**< [in] file name (mandatory) */
   BPApiRecipes_FilePath   filePath                    /**< [in] full file path without file name; if 0 or an empty string is specified then the standard path for recipes is used to locate the file */
   );

/******************************************************************************/
/**
 * @brief Writes a recipe file (Unicode)
 *
 * Writes a recipe file in Unicode:
 *     Stores the current values of a set of variables defined by a
 *     variable group name (recipe name) a file with the defined name.
 *     Additionally a file path may be provided.
 *     Otherwise the recipe files is created in the default recipe directory.
 *
 * @return State information about the call.
 */
BPApiState BPApiRecipeWriteW (
   BPApiRecipes_NameW      recipeName,                  /**< [in] name of recipe in Unicode */
   BPApiRecipes_FileNameW  fileName,                    /**< [in] file name in Unicode (mandatory) */
   BPApiRecipes_FilePathW  filePath                     /**< [in] full file path without file name in Unicode; if 0 or an empty string is specified then the standard path for recipes is used to locate the file */
   );


/******************************************************************************/
/**
 * @brief Start writing a recipe file asynchronous (ASCII)
 *
 * Start writing a recipe file in ASCII:
 *     Same functionality as BPApiRecipeWrite(), but operation will be
 *     performed asynchronously. Poll for result with function
 *     BPApiRecipeWriteAsyncGetResult().
 *     ATTENTION: If you do not poll for result, memory leaks will occure!
 *                You have to poll until state != BPApiStateRecipes_StartSucceeded.
 *
 * @return State information about the call.
 */
BPApiState BPApiRecipeWriteAsyncStartA (
   BPApiRecipes_Name       recipeName,                 /**< [in]  name of recipe */
   BPApiRecipes_FileName   fileName,                   /**< [in]  file name (mandatory) */
   BPApiRecipes_FilePath   filePath,                   /**< [in]  full file path without file name; if 0 or an empty string is specified then the standard path for recipes is used to locate the file */
   BPApiRecipeAsyncHdl    *hdl                         /**< [out] pass the content of this handle when calling BPApiRecipeWriteAsyncGetResult(); never change the content of this handle! */
   );

/******************************************************************************/
/**
 * @brief Start writing a recipe file asynchronous (Unicode)
 *
 * Start writing a recipe file in Unicode:
 *     Same functionality as BPApiRecipeWrite(), but operation will be
 *     performed asynchronously. Poll for result with function
 *     BPApiRecipeWriteAsyncGetResult().
 *     ATTENTION: If you do not poll for result, memory leaks will occure!
 *                You have to poll until state != BPApiStateRecipes_StartSucceeded.
 *
 * @return State information about the call.
 */
BPApiState BPApiRecipeWriteAsyncStartW (
   BPApiRecipes_NameW      recipeName,                 /**< [in]  name of recipe in Unicode */
   BPApiRecipes_FileNameW  fileName,                   /**< [in]  file name in Unicode (mandatory) */
   BPApiRecipes_FilePathW  filePath,                   /**< [in]  full file path without file name in Unicode; if 0 or an empty string is specified then the standard path for recipes is used to locate the file */
   BPApiRecipeAsyncHdl     *hdl                        /**< [out] pass the content of this handle when calling BPApiRecipeWriteAsyncGetResult(); never change the content of this handle! */
   );


/******************************************************************************/
/**
 * @brief Poll for result of asynchronous write operation
 *
 * Poll for result of asynchronous operation started by BPApiRecipeWriteAsyncStart()
 *
 * @return State information about the call.
 *         BPApiStateParamError, if passed 'hdl' is invalid.
 *         BPApiStateRecipes_StartSucceeded, if async operation is in progress.
 */
BPApiState BPApiRecipeWriteAsyncGetResult (
   BPApiRecipeAsyncHdl     hdl                         /**< [in]  use the handle returned by BPApiRecipeWriteAsyncStart() */
   );


/******************************************************************************/
/**
 * @brief Reads a recipe file (ASCII)
 *
 * Reads a recipe file in ASCII:
 *     Reads a recipe file and loads the variable values defined in the file.
 *
 * @return State information about the call.
 */
BPApiState BPApiRecipeReadA (
   BPApiRecipes_FileName   fileName,                   /**< [in] file name (mandatory) */
   BPApiRecipes_FilePath   filePath                    /**< [in] full file path without file name; if 0 or an empty string is specified then the standard path for recipes is used to locate the file */
   );


/******************************************************************************/
/**
 * @brief Reads a recipe file (Unicode)
 *
 * Reads a recipe file in Unicode:
 *     Reads a recipe file and loads the variable values defined in the file.
 *
 * @return State information about the call.
 */
BPApiState BPApiRecipeReadW (
   BPApiRecipes_FileNameW fileName,                    /**< [in] file name in Unicode (mandatory) */
   BPApiRecipes_FilePathW filePath                     /**< [in] full file path without file name in Unicode; if 0 or an empty string is specified then the standard path for recipes is used to locate the file */
   );


/******************************************************************************/
/**
 * @brief Start reading a recipe file asynchronous (ASCII)
 *
 * Reads a recipe file in ASCII:
 *     Same functionality as BPApiRecipeRead(), but operation will be
 *     performed asynchronously. Poll for result with function
 *     BPApiRecipeReadAsyncGetResult().
 *     ATTENTION: If you do not poll for result, memory leaks will occure!
 *                You have to poll until state != BPApiStateRecipes_StartSucceeded.
 *
 * @return State information about the call.
 */
BPApiState BPApiRecipeReadAsyncStartA (
   BPApiRecipes_FileName   fileName,                   /**< [in]  file name (mandatory) */
   BPApiRecipes_FilePath   filePath,                   /**< [in]  file path without file name; if 0 or an empty string is specified then the standard path for recipes is used to locate the file */
   BPApiRecipeAsyncHdl    *hdl                         /**< [out] pass the content of this handle when calling BPApiRecipeReadAsyncGetResult(); never change the content of this handle! */
   );

/******************************************************************************/
/**
 * @brief Start reading a recipe file asynchronous (Unicode)
 *
 * Reads a recipe file in Unicode:
 *     Same functionality as BPApiRecipeRead(), but operation will be
 *     performed asynchronously. Poll for result with function
 *     BPApiRecipeReadAsyncGetResult().
 *     ATTENTION: If you do not poll for result, memory leaks will occure!
 *                You have to poll until state != BPApiStateRecipes_StartSucceeded.
 *
 * @return State information about the call.
 */
BPApiState BPApiRecipeReadAsyncStartW (
   BPApiRecipes_FileNameW   fileName,                  /**< [in]  file name in Unicode (mandatory) */
   BPApiRecipes_FilePathW   filePath,                  /**< [in]  file path without file name in Unicode; if 0 or an empty string is specified then the standard path for recipes is used to locate the file */
   BPApiRecipeAsyncHdl     *hdl                        /**< [out] pass the content of this handle when calling BPApiRecipeReadAsyncGetResult(); never change the content of this handle! */
   );


/******************************************************************************/
/**
 * @brief Poll for result of asynchronous read operation
 *
 * Poll for result of asynchronous operation started by BPApiRecipeReadAsyncStart()
 *
 * @return State information about the call.
 *         BPApiStateParamError, if passed 'hdl' is invalid.
 *         BPApiStateRecipes_StartSucceeded, if async operation is in progress.
 */
BPApiState BPApiRecipeReadAsyncGetResult (
   BPApiRecipeAsyncHdl     hdl                         /**< [in]  use the handle returned by BPApiRecipeReadAsyncStart() */
   );


/******************************************************************************/
/**
 * @brief Start reading a recipe file with asynchronous. Load instance relative recipes (ASCII)
 *
 * Reads a recipe file in ASCII:
 *     Same functionality as BPApiRecipeRead(), but operation will be
 *     performed asynchronously. Poll for result with function
 *     BPApiRecipeReadAsyncGetResult().
 *     To load instance relative recipes, an instance number must be defined.
 *     ATTENTION: If you do not poll for result, memory leaks will occure!
 *                You have to poll until state != BPApiStateRecipes_StartSucceeded.
 *
 * @return State information about the call.
 */
BPApiState BPApiRecipeReadInstanceAsyncStartA (
   BPApiRecipes_FileName   fileName,                   /**< [in]  file name (mandatory) */
   BPApiRecipes_FilePath   filePath,                   /**< [in]  file path without file name; if 0 or an empty string is specified then the standard path for recipes is used to locate the file */
   uint32_t                instanceNo,                 /**< [in]  instance number for specified recipe */
   BPApiRecipeAsyncHdl    *hdl                         /**< [out] pass the content of this handle when calling BPApiRecipeReadAsyncGetResult(); never change the content of this handle! */
);

/******************************************************************************/
/**
 * @brief Start reading a recipe file with asynchronous. Load instance relative recipes (Unicode)
 *
 * Reads a recipe file in Unicode:
 *     Same functionality as BPApiRecipeRead(), but operation will be
 *     performed asynchronously. Poll for result with function
 *     BPApiRecipeReadAsyncGetResult().
 *     To load instance relative recipes, an instance number must be defined.
 *     ATTENTION: If you do not poll for result, memory leaks will occure!
 *                You have to poll until state != BPApiStateRecipes_StartSucceeded.
 *
 * @return State information about the call.
 */
BPApiState BPApiRecipeReadInstanceAsyncStartW (
   BPApiRecipes_FileNameW  fileName,                   /**< [in]  file name in Unicode (mandatory) */
   BPApiRecipes_FilePathW  filePath,                   /**< [in]  file path without file name in Unicode; if 0 or an empty string is specified then the standard path for recipes is used to locate the file */
   uint32_t                instanceNo,                 /**< [in]  instance number for specified recipe */
   BPApiRecipeAsyncHdl    *hdl                         /**< [out] pass the content of this handle when calling BPApiRecipeReadAsyncGetResult(); never change the content of this handle! */
   );


/******************************************************************************/
/**
 * @brief Start writing a recipe file with asynchronous. Create relative recipes (ASCII)
 *
 * Writes a recipe file in ASCII:
 *     Same functionality as BPApiRecipeWrite(), but operation will be
 *     performed asynchronously. Poll for result with function
 *     BPApiRecipeWriteAsyncGetResult().
 *     Additionally an instance identification may be provided to create
 *     relative recipes.
 *     ATTENTION: If you do not poll for result, memory leaks will occure!
 *                You have to poll until state != BPApiStateRecipes_StartSucceeded.
 *
 * @return State information about the call.
 */
BPApiState BPApiRecipeWriteInstanceAsyncStartA (
   BPApiRecipes_Name       recipeName,                 /**< [in]  name of recipe (may be 0 or an empty string --> all variables used); */
   BPApiRecipes_InstanceId instanceId,                 /**< [in]  instance specification for recipe */
   BPApiRecipes_FileName   fileName,                   /**< [in]  file name (mandatory) */
   BPApiRecipes_FilePath   filePath,                   /**< [in]  full file path without file name; if 0 or an empty string is specified then the standard path for recipes is used to locate the file */
   BPApiRecipeAsyncHdl    *hdl                         /**< [out] pass the content of this handle when calling BPApiRecipeWriteAsyncGetResult(); never change the content of this handle! */
);

/******************************************************************************/
/**
 * @brief Start writing a recipe file with asynchronous. Create relative recipes (Unicode)
 *
 * Writes a recipe file in Unicode:
 *     Same functionality as BPApiRecipeWrite(), but operation will be
 *     performed asynchronously. Poll for result with function
 *     BPApiRecipeWriteAsyncGetResult().
 *     Additionally an instance identification may be provided to create
 *     relative recipes.
 *     ATTENTION: If you do not poll for result, memory leaks will occure!
 *                You have to poll until state != BPApiStateRecipes_StartSucceeded.
 *
 * @return State information about the call.
 */
BPApiState BPApiRecipeWriteInstanceAsyncStartW (
   BPApiRecipes_NameW         recipeName,              /**< [in]  name of recipe in Unicode (may be 0 or an empty string --> all variables used); */
   BPApiRecipes_InstanceIdW   instanceId,              /**< [in]  instance specification for recipe in Unicode */
   BPApiRecipes_FileNameW     fileName,                /**< [in]  file name in Unicode (mandatory) */
   BPApiRecipes_FilePathW     filePath,                /**< [in]  full file path without file name in Unicode; if 0 or an empty string is specified then the standard path for recipes is used to locate the file */
   BPApiRecipeAsyncHdl       *hdl                      /**< [out] pass the content of this handle when calling BPApiRecipeWriteAsyncGetResult(); never change the content of this handle! */
   );

/******************************************************************************/
/**
 * @brief Update all variable values in a file
 *
 * Updates all variable values that have been defined in the specified file.
 *
 * @return State information about the call.
 */
BPApiState BPApiRecipeUpdateFile(
   BPApiRecipes_FileName fileName,                 /**< [in]  file name (mandatory) */
   BPApiRecipes_FilePath filePath                  /**< [in]  full file path without file name; if 0 or an empty string is specified then the standard path for recipes is used to locate the file */
   );


/******************************************************************************/
/**
 * @brief Checks if recipe file has been changed
 *
 * Checks if any variable value in a recipe file has been changed.
 *
 * @return State information about the call.
 */
BPApiState BPApiRecipeIsFileChanged(
   BPApiRecipes_FileName fileName,                 /**< [in]  file name (mandatory) */
   BPApiRecipes_FilePath filePath                  /**< [in]  full file path without file name; if 0 or an empty string is specified then the standard path for recipes is used to locate the file */
   );



/******************************************************************************/
/**
 * @brief Start an asynchronous operation to update all variable values in a file.
 *
 * Updates all variable values that have been defined in the specified file:
 *     Same functionality as BPApiRecipeUpdateFile(), but operation will be
 *     performed asynchronously. Poll for result with function
 *     BPApiRecipeUpdateFileAsyncGetResult().
 *     ATTENTION: If you do not poll for result, memory leaks will occur!
 *                You have to poll until state != BPApiStateRecipes_StartSucceeded.
 *
 * @return State information about the call.
 */
BPApiState BPApiRecipeUpdateFileAsyncStart (
   BPApiRecipes_FileName   fileName,               /**< [in]  file name (mandatory) */
   BPApiRecipes_FilePath   filePath,               /**< [in]  full file path without file name; if 0 or an empty string is specified then the standard path for recipes is used to locate the file */
   BPApiRecipeAsyncHdl    *hdl                     /**< [out] pass the content of this handle when calling BPApiRecipeUpdateFileAsyncGetResult(); never change the content of this handle! */
   );



/******************************************************************************/
/**
 * @brief Poll for result of asynchronous update file operation
 *
 * Poll for result of asynchronous operation started by BPApiRecipeUpdateFileAsyncStart()
 *
 * @return State information about the call.
 *         BPApiStateParamError, if passed 'hdl' is invalid.
 *         BPApiStateRecipes_StartSucceeded, if async operation is in progress.
 */
BPApiState BPApiRecipeUpdateFileAsyncGetResult (
   BPApiRecipeAsyncHdl hdl                            /**< [in]  use the handle returned by BPApiRecipeUpdateFileAsyncStart() */
   );



/** @cond */
#ifdef UNICODE
   #define BPApiRecipeWrite                     BPApiRecipeWriteW
   #define BPApiRecipeWriteAsyncStart           BPApiRecipeWriteAsyncStartW
   #define BPApiRecipeRead                      BPApiRecipeReadW
   #define BPApiRecipeReadAsyncStart            BPApiRecipeReadAsyncStartW
   #define BPApiRecipeReadInstanceAsyncStart    BPApiRecipeReadInstanceAsyncStartW
   #define BPApiRecipeWriteInstanceAsyncStart   BPApiRecipeWriteInstanceAsyncStartW
#else
   #define BPApiRecipeWrite                     BPApiRecipeWriteA
   #define BPApiRecipeWriteAsyncStart           BPApiRecipeWriteAsyncStartA
   #define BPApiRecipeRead                      BPApiRecipeReadA
   #define BPApiRecipeReadAsyncStart            BPApiRecipeReadAsyncStartA
   #define BPApiRecipeReadInstanceAsyncStart    BPApiRecipeReadInstanceAsyncStartA
   #define BPApiRecipeWriteInstanceAsyncStart   BPApiRecipeWriteInstanceAsyncStartA
#endif
/** @endcond */

#ifdef __cplusplus
}
#endif /* C++ */

#endif /* PACKAGE_API_RECIPE_H */
