/*------------------------------------------------------------------------------
*                             (c) 1999 by KEBA AG
*                                www.keba.com
*                                Linz/Austria
*                             All rights reserved
*-------------------------------------------------------------------------------
*/
/** @file
*   @brief Functions for a teachcontrol-client
*
*   Functions for a teachcontrol-client
*/
/*------------------------------------------------------------------------------
*/

#ifndef TcClient_H
#define TcClient_H

#include "TcClientDefinitions.h"

#ifdef __cplusplus
extern "C" {
#endif


/******************************************************************************/
/**
 * @brief Register a client for the teachcontrol-runtimesystem
 *
 * Register a client for the teachcontrol-runtimesystem.
 * The registration is necessary for all further calls of interface functions
 * by the client. Clients registered as 'observer' are only allowed to call
 * reading functions, 'controller' are allowed to call any function. At most 10
 * clients can be registered simultaneously. 
 */
TcBool TcOpenTeachControl (
   TcClientType type,   /**< [in]  Clienttype, observer or controller. */
   TcHdl *clientHnd,    /**< [out] Connection-handle */
   char **version       /**< [out] TC version string */
   );

/******************************************************************************/
/**
 * @brief Deregister a client from the teachcontrol-runtimesystem
 *
 * Deregister a client from the teachcontrol-runtimesystem.
 * After deregistration no further calls of interface functions are possible.
 * All resources associated with the client, such as editors or variable-groups,
 * are deleted.
 *
 * @see TcOpenTeachControl
 */
TcBool TcCloseTeachControl (
   TcHdl clientHnd   /**< [in] Connection-handle */
   );

/******************************************************************************/
/**
 * @brief Read the work-paths
 *
 * Read the parent-directory paths for the teachtalk-projects (work-paths).
 */
TcBool TcReadProjectPath (
   char **pathLocal, /**< [out] directory path */
   char **pathUNC    /**< [out] directory path (UNC) */
   );

/******************************************************************************/
/**
 * @brief Read a list with currently registered clients
 *
 * Read a list with currently registered clients.
 */
TcBool TcGetClientList (
   TcClientInfo clients[TcMaxClients], /**< [out] Array with client information (0 to nrClients-1) */
   int *nrClients                      /**< [out] Number of registered clients */
   );

/******************************************************************************/
/**
 * @brief Set the name with which the client is registered at the control
 *
 * Set the name with which the client is registered at the control. If the
 * client is deregistered because of inactivity then a warning using this name
 * is emitted.
 */
TcBool TcSetClientName (
   const char *name  /**< [in] Client-name */
   );

/******************************************************************************/
/**
 * @brief Set the access-type (observer/controller) for the client
 *
 * Set the access-type (observer/controller) for the client. If the client is
 * supposed to become a controller and another controller is already registered
 * at the system, then this is only possible with 'forceController' set to true:
 */
TcBool TcSetClientType (
   TcClientType type,      /**< [in] New access-type */
   TcBool forceController  /**< [in] Allow more than one controller */
   );

/******************************************************************************/
/**
 * @brief Make the client noticeable for the system
 *
 * Make the client noticeable for the system. Clients which do not use any
 * interface calls for a certain time are automatically deregistered by the
 * system (see the configuration parameter 'keepAliveTimeout'). This function
 * can be called cyclically to avoid this.
 *
 * @return Returns false only if the client is not registered
 */
TcBool TcKeepAlive ();

/******************************************************************************/
/**
 * @brief Request exclusive write access
 *
 * Request exclusive write access. The function informs other clients with
 * write access that they should change their status from controller to
 * observer. With 'request' set to false the demand can be withdrawn.
 */
TcBool TcRequestWriteAccess (
   TcBool request    /**< [in] Request set/reset */
   );

/******************************************************************************/
/**
 * @brief Check whether another client requests exclusive write access
 *
 * The function can be called cyclically to check whether another client
 * requests exclusive write access (with the function TcRequestWriteAccess).
 * If so the client can change its status from controller to observer.
 * 
 * @see TcRequestWriteAccess
 */
TcBool TcWriteAccessRequestPending (
   TcBool *requestPending  /**< [out] True when a write-access request is pending */
   );

/******************************************************************************/
/**
 * @brief Convert an exeUnitHnd to a scopeHnd
 *
 * Convert an execution node (exeUnitHnd) to a structure-tree node
 * (scopeHnd).
 */
TcBool TcConvertExeUnitHandle (
   TcHdl exeUnitHnd, /**< [in]  Execution node */
   TcHdl *scopeHnd   /**< [out] Structure-tree node */
   );

/******************************************************************************/
/**
 * @brief Convert a dirEntryHnd to a scopeHnd
 *
 * Convert a directory entry (dirEntryHnd) to a structure-tree node (scopeHnd).
 */
TcBool TcConvertDirEntryHandle (
   TcDirHandle dirEntryHnd,   /**< [in]  Directory entry */
   TcHdl *scopeHnd            /**< [out] Structure-tree node */
   );

/******************************************************************************/
/**
 * @brief Convert a scopeHnd to a dirEntryHnd
 *
 * Convert a structure-tree node (scopeHnd) to a directory entry (dirEntryHnd).
 */
TcBool TcConvertScopeHandle (
   TcHdl scopeHnd,            /**< [in]  Structure-tree node */
   TcDirHandle dirEntryHnd    /**< [out] Directory entry */
   );

/******************************************************************************/
/**
 * @brief Get the first dirEntryHnd in the directory
 *
 * Get the first directory entry of the given kind in the given directory. If no
 * directory is given (empty string) then the work-path is used.
 */
TcBool TcGetFirstDirEntry (
  TcDirHandle directory,   /**< [in]  Directory */
  TcDirEntryKind kind,     /**< [in]  Entry kind */
  TcHdl *iterHnd,          /**< [out] Handle for iteration */
  TcDirHandle dirEntryHnd  /**< [out] First entry */
  );

/******************************************************************************/
/**
 * @brief Get the next dirEntryHnd in the directory
 *
 * Get the next directory entry of the given kind in the given directory. If no
 * directory is given (empty string) then the work-path is used.
 */
TcBool TcGetNextDirEntry (
  TcDirHandle directory,   /**< [in]  Directory */
  TcDirEntryKind kind,     /**< [in]  Entry kind */
  TcHdl *iterHnd,          /**< [in]  Handle for iteration */
  TcDirHandle dirEntryHnd  /**< [out] Next entry */
  );

/******************************************************************************/
/**
 * @brief Get information for a dirEntryHnd
 *
 * Get information for the given directory entry.
 */
TcBool TcGetDirEntryInfo (
   TcDirHandle dirEntryHnd,      /**< [in]  Directory entry */
   TcDirEntryInfo *dirEntryInfo  /**< [out] Information for the entry */
   );

/******************************************************************************/
/**
 * @brief Get the first dirEntryHnd chunk in the directory
 *
 * Get the first chunk of directory entries of the given kind in the given
 * directory. If no directory is given (empty string) then the work-path is used.
 */
TcBool TcGetFirstDirEntryChunk (
   TcDirHandle directory,                 /**< [in]  Directory */
   TcDirEntryKind kind,                   /**< [in]  Entry kind */
   TcHdl *iterHnd,                        /**< [in]  Handle for iteration */
   TcDirHandle dirEntryHnds[TcChunkLen],  /**< [out] First entries */
   unsigned *nrDirEntries                 /**< [out] Number of entries */
   );

/******************************************************************************/
/**
 * @brief Get the next dirEntryHnd chunk in the directory
 *
 * Get the next chunk of directory entries of the given kind in the given
 * directory. If no directory is given (empty string) then the work-path is used.
 */
TcBool TcGetNextDirEntryChunk (
   TcDirHandle directory,                 /**< [in]  Directory */
   TcDirEntryKind kind,                   /**< [in]  Entry kind */
   TcHdl *iterHnd,                        /**< [in]  Handle for iteration */
   TcDirHandle dirEntryHnds[TcChunkLen],  /**< [out] Next entries */
   unsigned *nrDirEntries                 /**< [out] Number of entries */
   );

/******************************************************************************/
/**
 * @brief Get information for a dirEntryHnd list
 *
 * Get information for the given list of directory entries.
 */
TcBool TcGetDirEntryInfoList (
   TcDirHandle dirEntryPaths[TcChunkLen],    /**< [in]  List of directory entries */
   unsigned nrDirEntryPaths,                 /**< [in]  Number of directory entries */
   TcDirEntryInfo dirEntryInfos[TcChunkLen]  /**< [out] Information for the entries */
   );

/******************************************************************************/
/**
 * @brief Add a directory entry
 *
 * Add a directory entry to the given directory.
 */
TcBool TcAddDirEntry (
   TcDirHandle directory,     /**< [in]  Directory */
   const char *dirEntryName,  /**< [in]  Name of the new directory entry */
   TcDirEntryKind kind,       /**< [in]  Kind of the new directory entry */
   TcDirHandle dirEntryHnd    /**< [out] The new directory entry */
   );

/******************************************************************************/
/**
 * @brief Copy a directory entry
 *
 * Copy a directory entry to the given directory.
 */
TcBool TcCopyDirEntry (
   TcDirHandle srcDirEntryHnd,   /**< [in]  Source directory entry */
   TcDirHandle destDirectory  ,  /**< [in]  Destination directory */
   const char *destDirEntryName, /**< [in]  Name of the new directory entry */
   TcDirEntryKind kind,          /**< [in]  Kind of the new directory entry */
   TcDirHandle destDirEntryHnd   /**< [out] The new directory entry */
   );
                                                                                     
/******************************************************************************/
/**
 * @brief Rename a directory entry
 *
 * Rename a directory entry, a new name and a new kind can be specified.
 */
TcBool TcRenameDirEntry (
   TcDirHandle dirEntryHnd,      /**< [in]  Directory entry */
   const char *newDirEntryName,  /**< [in]  New name */
   TcDirEntryKind kind,          /**< [in]  New kind */
   TcDirHandle newDirEntryHnd    /**< [out] The new directory entry */
   );

/******************************************************************************/
/**
 * @brief Delete a directory entry
 *
 * Delete the given directory entry.
 */
TcBool TcDeleteDirEntry (
   TcDirHandle dirEntryHnd    /**< [in]  Directory entry */
   );

/******************************************************************************/
/**
 * @brief Delete a directory entry
 *
 * Delete the given directory entry. Deletion in spite of write protection can
 * be forced.
 */
TcBool TcDeleteDirEntryExt (
   TcDirHandle dirEntryHnd,   /**< [in] Directory entry */
   TcBool forced              /**< [in] 1: Write protection ignored */
   );

/******************************************************************************/
/**
 * @brief Create an archive
 *
 * Create an archive-file (file extension 'tta').
 */
TcBool TcArchiveCreate (
   TcDirHandle archiveDirEntryHnd,  /**< [in] Directory entry for the new archive  */
   TcDirHandle inputDirectory,      /**< [in] Directory with the files that shall be stored in the archive */
   const char *password,            /**< [in] Password for the archive, 0 or "" if no password shall be required */
   unsigned verMajor,               /**< [in] Major version number */
   unsigned verMinor,               /**< [in] Minor version number */
   const char *comment,             /**< [in] Comment that will be stored in the archive information-block */
   TcBool removeInput               /**< [in] 1: The input directory shall be deleted after creation of the archive */
   );

/******************************************************************************/
/**
 * @brief Extract the contents of an archive
 *
 * Extract the contents of an archive.
 */
TcBool TcArchiveExtract (
   TcDirHandle archiveDirEntryHnd,  /**< [in]  Directory entry of the archive  */
   TcDirHandle outputDirectory,     /**< [in]  Directory into which the files of the archive shall be extracted */
   const char *password,            /**< [in]  Password for the archive, 0 or "" if no password is necessary */
   TcBool removeArchive,            /**< [in]  1: The archive shall be deleted after extraction to the output directory */
   TcBool *pwdInvalid               /**< [out] 1: The given password was not correct */
   );

/******************************************************************************/
/**
 * @brief Open an editor
 *
 * Open a new editor for the file associated with the given structure-tree node.
 */
TcBool TcOpenSyntaxEditor (
   TcHdl scopeHnd,   /**< [in]  Structure-tree node */
   TcHdl *editHnd    /**< [out] The new editor */
   );

/******************************************************************************/
/**
 * @brief Open an editor
 *
 * Open a new editor for the file associated with the given structure-tree node.
 * If the file resides inside an encrypted archive the password has to be given.
 */
TcBool TcOpenSyntaxEditorExt (
   TcHdl scopeHnd,         /**< [in]  Structure-tree node */
   const char *password,   /**< [in]  Password for files residing in encrypted archives */
   TcHdl *editHnd          /**< [out] The new editor */
   );

/******************************************************************************/
/**
 * @brief Close an editor
 *
 * Close the given editor.
 */
TcBool TcCloseEditor (
   TcHdl editHnd  /**< [in] Editor handle */
   );

/******************************************************************************/
/**
 * @brief Save an editor
 *
 * Save the content of the given editor to the associated file.
 */
TcBool TcSaveEditor (
   TcHdl editHnd  /**< [in] Editor handle */
   );

/******************************************************************************/
/**
 * @brief Get the the first line for an iteration through the editor
 *
 * Get the first line for an iteration through the editor content. It can be
 * specified how many lines from the beginning shall be skipped.
 */
TcBool TcGetFirstLine (
   TcHdl editHnd,    /**< [in]  Editor handle */
   TcHdl *iterHnd,   /**< [out] Handle for iteration */
   int nrSkipLines,  /**< [in]  Number of lines that shall be skipped */
   char *line,       /**< [out] Buffer for the line */
   int maxLen        /**< [in]  Number of characters that can be stored in the buffer */
   );

/******************************************************************************/
/**
 * @brief Get the the next line during an iteration through the editor
 *
 * Get the the next line during an iteration through the editor.
 */
TcBool TcGetNextLine (
   TcHdl editHnd,    /**< [in]  Editor handle */
   TcHdl *iterHnd,   /**< [in/out] Handle for iteration */
   char *line,       /**< [out] Buffer for the line */
   int maxLen        /**< [in]  Number of characters that can be stored in the buffer */
   );

/******************************************************************************/
/**
 * @brief Get the the first chunk of lines for an iteration through the editor
 *
 * Get the first chunk of lines for an iteration through the editor content. It
 * can be specified how many lines from the beginning shall be skipped.
 */
TcBool TcGetFirstLineChunk (
   TcHdl editHnd,                /**< [in]  Editor handle */
   TcHdl *iterHnd,               /**< [out] Handle for iteration */
   int nrSkipLines,              /**< [in]  Number of lines that shall be skipped */
   char *linePtrs[TcChunkLen],   /**< [out] Array of pointers to the line beginnings */
   char *linesBuf,               /**< [in]  Buffer for the text of all lines */
   int bufLen,                   /**< [in]  Number of bytes that can be stored in the buffer */
   unsigned int *nrLines         /**< [out] Number of lines that were stored */
   );

/******************************************************************************/
/**
 * @brief Get the the next chunk of lines for an iteration through the editor
 *
 * Get the next chunk of lines for an iteration through the editor content. It
 * can be specified how many lines from the beginning shall be skipped.
 */
TcBool TcGetNextLineChunk (
   TcHdl editHnd,                /**< [in]  Editor handle */
   TcHdl *iterHnd,               /**< [in/out] Handle for iteration */
   char *linePtrs[TcChunkLen],   /**< [out] Array of pointers to the line beginnings */
   char *linesBuf,               /**< [in]  Buffer for the text of all lines */
   int bufLen,                   /**< [in]  Number of bytes that can be stored in the buffer */
   unsigned int *nrLines         /**< [out] Number of lines that were stored */
   );

/******************************************************************************/
/**
 * @brief Get information for an editor
 *
 * Get information for the given editor.
 */
TcBool TcGetEditorInfo (
   TcHdl editHnd,          /**< [in]  Editor handle */
   TcEditorInfo *editInfo  /**< [out] Information for the editor */
   );

/******************************************************************************/
/**
 * @brief Insert text into an editor
 *
 * Insert Text into an editor.
 */
TcBool TcInsertText (
   TcHdl editHnd,       /**< [in] Editor handle */
   TcPos *pos,          /**< [in] Position at which the text shall be inserted */
   int len,             /**< [in] Number of characters that shall be inserted, -1 for full string */
   const char *insText  /**< [in] Text that shall be inserted */
   );

/******************************************************************************/
/**
 * @brief Delete text from an editor
 *
 * Delete text from an editor.
 */
TcBool TcDeleteText (
   TcHdl editHnd, /**< [in] Editor handle */
   TcPos *beg,    /**< [in] Position at which the deletion should begin */
   TcPos *end     /**< [in] Position at which the deletion should end */
   );

/******************************************************************************/
/**
 * @brief Delete symbol from an editor
 *
 * Delete symbol from an editor.
 */
TcBool TcDeleteSymbol (
   TcHdl editHnd, /**< [in] Editor handle */
   TcHdl symHnd   /**< [in] Symbol handle */
   );

/******************************************************************************/
/**
 * @brief Get the first syntactic symbol
 *
 * Get the first syntactic symbol for an iteration through the editor.
 */
TcBool TcGetFirstSymbol (
   TcHdl editHnd,    /**< [in]  Editor handle */
   TcHdl nonTermHnd, /**< [in]  Nonterminal symbol, 0 for the axiom */
   TcHdl *iterHnd,   /**< [out] Handle for iteration */
   TcSymbol *symbol  /**< [out] First symbol */
   );

/******************************************************************************/
/**
 * @brief Get the next syntactic symbol
 *
 * Get the next syntactic symbol during an iteration through the editor.
 */
TcBool TcGetNextSymbol (
   TcHdl editHnd,    /**< [in]  Editor handle */
   TcHdl nonTermHnd, /**< [in]  Nonterminal symbol, 0 for the axiom */
   TcHdl *iterHnd,   /**< [in/out] Handle for iteration */
   TcSymbol *symbol  /**< [out] Next symbol */
   );

/******************************************************************************/
/**
 * @brief Get the first chunk of syntactic symbols
 *
 * Get the first chunk of syntactic symbols for an iteration through the editor.
 */
TcBool TcGetFirstSymbolChunk (
   TcHdl editHnd,                /**< [in]  Editor handle */
   TcHdl nonTermHnd,             /**< [in]  Nonterminal symbol, 0 for the axiom */
   TcHdl *iterHnd,               /**< [out] Handle for iteration */
   TcSymbol symbols[TcChunkLen], /**< [out] Array with symbols */
   int *nrSymbols                /**< [out] Number of stored symbols */
   );

/******************************************************************************/
/**
 * @brief Get the next chunk of syntactic symbols
 *
 * Get the next chunk of syntactic symbols during an iteration through the
 * editor.
 */
TcBool TcGetNextSymbolChunk (
   TcHdl editHnd,                /**< [in]  Editor handle */
   TcHdl nonTermHnd,             /**< [in]  Nonterminal symbol, 0 for the axiom */
   TcHdl *iterHnd,               /**< [in/out] Handle for iteration */
   TcSymbol symbols[TcChunkLen], /**< [out] Array with symbols */
   int *nrSymbols                /**< [out] Number of stored symbols */
   );

/******************************************************************************/
/**
 * @brief Get the begin- and end-position of a symbol
 *
 * Get the begin- and end-position of a symbol in the given editor.
 */
TcBool TcGetSymbolTextRange (
   TcHdl editHnd,    /**< [in]  Editor handle */
   TcHdl symHnd,     /**< [in]  Symbol handle */
   TcPos *beginPos,  /**< [out] Position where the symbol begins */
   TcPos *endPos     /**< [out] Position where the symbol ends */
   );

/******************************************************************************/
/**
 * @brief Get the begin- and end-position of a structure-tree node
 *
 * Get the begin- and end-position of a structure-tree node in the given editor.
 */
TcBool TcGetNodeTextRange (
   TcHdl editHnd,    /**< [in]  Editor handle */
   TcHdl nodeHnd,    /**< [in]  Structure-tree node */
   TcPos *beginPos,  /**< [out] Position where the node begins */
   TcPos *endPos     /**< [out] Position where the node ends */
   );

/******************************************************************************/
/**
 * @brief Get the text for a symbol
 *
 * Get the text for a symbol in the given editor.
 */
TcBool TcGetSymbolText (
   TcHdl editHnd,    /**< [in]  Editor handle */
   TcHdl symHnd,     /**< [in]  Symbol handle */
   char *text,       /**< [out] Buffer for the text */
   int maxLen        /**< [in]  Number of characters that can be stored in the buffer */
   );

/******************************************************************************/
/**
 * @brief Insert statement text into a routine
 *
 * Insert statement text into the statement-list of a routine.
 */
TcBool TcInsertStatement (
   TcHdl routineHnd,       /**< [in] Routine handle (structure-tree node) */
   TcPos *pos,             /**< [in] Position where the statement shall be inserted */
   const char *stmtText    /**< [in] Text for the new statement */
   );

/******************************************************************************/
/**
 * @brief Delete statement from a routine
 *
 * Delete one or more statements from a routine.
 */
TcBool TcDeleteStatement (
   TcHdl routineHnd, /**< [in] Routine handle (structure-tree node) */
   TcPos *beginPos,  /**< [in] Position at which the deletion should begin */
   TcPos *endPos     /**< [in] Position at which the deletion should end */
   );
   
/******************************************************************************/
/**
 * @brief Replace statement text in a routine
 *
 * Replace text in a routine with new statement text.
 */
TcBool TcReplaceStatement (
   TcHdl routineHnd,       /**< [in] Routine handle (structure-tree node) */
   TcPos *beginPos,        /**< [in] Position at which the replacement should begin */
   TcPos *endPos,          /**< [in] Position at which the replacement should end */
   const char *stmtText    /**< [in] Text for the new statement */
   );

/******************************************************************************/
/**
 * @brief Replace comment text in a routine
 *
 * Replace comment text in a routine. From the given positions only the 'line'
 * members are evaluated. It is checked whether original and new text consist
 * of comments or empty lines only.
 */
TcBool TcReplaceComment (
   TcHdl itemHnd,             /**< [in] Item handle (structure-tree node) */
   TcPos *beginPos,           /**< [in] Position at which the replacement should begin */
   TcPos *endPos,             /**< [in] Position at which the replacement should end */
   const char *commentText    /**< [in] Text for the new comment */
   );

/******************************************************************************/
/**
 * @brief Set the instruction pointer
 *
 * Set the instruction pointer of the given routine to the given line. All
 * routines called by the given routine are closed and an active waiting
 * condition is resolved.
 */
TcBool TcSetInstructionPointer (
   TcHdl exeUnitHnd, /**< [in] Routine handle (execution node) */
   int lineNr        /**< [in] New line number */
   );

/******************************************************************************/
/**
 * @brief Compile a project
 *
 * Compile the given project and insert it into the structure-tree. If the
 * project was already translated it is translated anew with the existing
 * structure-tree handle remaining valid.
 */
TcBool TcBuild (
   const TcDirHandle dirEntryHnd    /**< [in] Project directory */
   );

/******************************************************************************/
/**
 * @brief Start the compilation of a project
 *
 * In contrast to TcBuild this function returns immediately, it is not waited
 * for completion. Only after completion the project becomes visible in the 
 * structure-tree, which can be realized using e.g. TcOpenNode.
 */
TcBool TcBuildStart (
   const TcDirHandle dirEntryHnd    /**< [in] Project directory */
   );

/******************************************************************************/
/**
 * @brief Delete a project from the structure-tree
 *
 * Delete a project and all elements within from the structure-tree. A project
 * can not be destroyed as long as it is loaded.
 */
TcBool TcDestroy (
   TcHdl scopeHnd    /**< [in] Structure-tree node of the project */
   );

/******************************************************************************/
/**
 * @brief Write save-files for the given structure-tree node
 *
 * Write save-files for all projects and programs contained in the given node.
 */
TcBool TcWriteData (
   TcHdl scopeHnd    /**< [in] Structure-tree node of a project or program */
   );

/******************************************************************************/
/**
 * @brief Write save-files for the given structure-tree node
 *
 * Write save-files for all projects and programs contained in the given node.
 * The consideration of sub-projects can be suppressed.
 */
TcBool TcWriteDataExt (
   TcHdl scopeHnd,   /**< [in] Structure-tree node of a project or program */
   TcBool strict     /**< [in] 1: No consideration of sub-projects */
   );

/******************************************************************************/
/**
 * @brief Read an error message
 *
 * Read an error message of the last compile-operation (TcBuild). Can be
 * repeated until all messages have been received.
 */
TcBool TcReadError (
   TcErrorElem *error   /**< [out] Error message */
   );

/******************************************************************************/
/**
 * @brief Read error messages for the given project
 *
 * Read error messages of the last compile-operation (TcBuild) for the given
 * project. A new TcBuild for the project will delete all previous messages and
 * create new ones.
 */
TcBool TcGetErrors (
   TcHdl projScopeHandle,              /**< [in]  Project handle (structure-tree node) */
   TcErrorElem errors[TcErrorLimit],   /**< [out] Error messages */
   int *nrErrors                       /**< [out] Number of received errors */
   );

/******************************************************************************/
/**
 * @brief Check whether the project in the structure-tree is still current
 *
 * Check whether the project in the structure-tree is still matching the files 
 * in the corresponding directory.
 *
 * @return Returns true if the project is valid and current
 */
TcBool TcIsCurrent (
   TcHdl scopeHnd    /**< [in] Project handle (structure-tree node) */
   );

/******************************************************************************/
/**
 * @brief Read structure-tree changes
 *
 * With TcReadNodeChange at most the last 500 (gcTcChunkLen) changes can be
 * read. Every change record contains an increasing counter value (starting with
 * 0) and the handle of the affected structure-tree element. The element can
 * have been created, modified or deleted. For changes of composite elements
 * only the handle of the composite element is registered, not every
 * sub-element.
 */
TcBool TcReadNodeChange (
   int startChangeCnt,                 /**< [in]  Minimum counter value */
   TcNodeChange changes[TcChunkLen],   /**< [out] Received change records */
   int *nrChanges                      /**< [out] Number of received change records */
   );

/******************************************************************************/
/**
 * @brief Get the structure-tree node for the given path
 *
 * Get the structure-tree node for the given structure-tree path.
 */
TcBool TcOpenNode (
   const char *nodePath,   /**< [in]  Node path, e.g. "project.program.variable" */
   TcHdl *nodeHnd,         /**< [out] Structure-tree node */
   TcNodeKind *kind        /**< [out] Node kind  */
   );

/******************************************************************************/
/**
 * @brief Get the first structure-tree element in the given scope
 *
 * Get the first structure-tree element of the given kind in the given scope.
 *
 * @see TcGetNextNode
 */
TcBool TcGetFirstNode (
   TcHdl scopeHnd,   /**< [in]  Structure-tree scope */
   TcNodeKind kind,  /**< [in]  Kind of nodes to search */
   TcHdl *iterHnd,   /**< [out] Handle for iteration */
   TcHdl *nodeHnd    /**< [out] First structure-tree node */
   );

/******************************************************************************/
/**
 * @brief Get the next structure-tree element in the given scope
 *
 * Get the next structure-tree element of the given kind in the given scope.
 *
 * @see TcGetFirstNode
 */
TcBool TcGetNextNode (
   TcHdl scopeHnd,   /**< [in]  Structure-tree scope */
   TcNodeKind kind,  /**< [in]  Kind of nodes to search */
   TcHdl *iterHnd,   /**< [in/out] Handle for iteration */
   TcHdl *nodeHnd    /**< [out] Next structure-tree node */
   );

/******************************************************************************/
/**
 * @brief Get the first chunk of structure-tree elements in the given scope
 *
 * Get the first chunk of structure-tree elements of the given kind in the
 * given scope.
 *
 * @see TcGetNextNodeChunk
 */
TcBool TcGetFirstNodeChunk (
   TcHdl scopeHnd,               /**< [in]  Structure-tree scope */
   TcNodeKind kind,              /**< [in]  Kind of nodes to search */
   TcHdl *iterHnd,               /**< [out] Handle for iteration */
   TcHdl nodeHnds[TcChunkLen],   /**< [out] First structure-tree nodes */
   int *nrHnds                   /**< [out] Number of received nodes */
   );

/******************************************************************************/
/**
 * @brief Get the next chunk of structure-tree elements in the given scope
 *
 * Get the next chunk of structure-tree elements of the given kind in the
 * given scope.
 *
 * @see TcGetFirstNodeChunk
 */
TcBool TcGetNextNodeChunk (
   TcHdl scopeHnd,               /**< [in]  Structure-tree scope */
   TcNodeKind kind,              /**< [in]  Kind of nodes to search */
   TcHdl *iterHnd,               /**< [in/out] Handle for iteration */
   TcHdl nodeHnds[TcChunkLen],   /**< [out] Next structure-tree nodes */
   int *nrHnds                   /**< [out] Number of received nodes */
   );

/******************************************************************************/
/**
 * @brief Get a chunk of interfaces for the given type
 *
 * Get a chunk of interfaces implemented or extended by the given type.
 */
TcBool TcGetInterfaceChunk (
   TcHdl typeHnd,             /**< [in]  Type handle (structure-tree node) */
   TcHdl *iterHnd,            /**< [in/out] Handle for iteration, use 0 for a start */
   TcHdl itfHnds[TcChunkLen], /**< [out] Interface handles */
   int *nrHnds                /**< [out] Number of received interface handles, finished when *nrHnds<TcChunkLen */
   );

/******************************************************************************/
/**
 * @brief Read general information for a node
 *
 * Read general information for a structure-tree node.
 */
TcBool TcGetNodeInfo (
   TcHdl scopeHandle,      /**< [in]  Structure-tree node */
   TcNodeInfo *nodeInfo    /**< [out] General information */
   );

/******************************************************************************/
/**
 * @brief Read information for a routine node
 *
 * Read information for a routine node in the structure-tree.
 */
TcBool TcGetRoutineInfo (
   TcHdl routineScopeHandle,     /**< [in]  Routine handle (structure-tree node) */
   TcRoutineInfo *routineInfo    /**< [out] Routine information */
   );

/******************************************************************************/
/**
 * @brief Read information for a variable node
 *
 * Read information for a variable node in the structure-tree.
 */
TcBool TcGetVarInfo (
   TcHdl varScopeHandle,   /**< [in]  Variable handle (structure-tree node) */
   TcVarInfo *varInfo      /**< [out] Variable information */
   );

/******************************************************************************/
/**
 * @brief Read information for a type node
 *
 * Read information for a type node in the structure-tree.
 */
TcBool TcGetTypeInfo (
   TcHdl typeScopeHandle,  /**< [in]  Type handle (structure-tree node) */
   TcTypeInfo *typeInfo    /**< [out] Type information */
   );

/******************************************************************************/
/**
 * @brief Read information for a constant node
 *
 * Read information for a constant node in the structure-tree.
 */
TcBool TcGetConstInfo (
   TcHdl constScopeHandle, /**< [in]  Constant handle (structure-tree node) */
   TcConstInfo *constInfo  /**< [out] Constant information */
   );

/******************************************************************************/
/**
 * @brief Read general information for a list of nodes
 *
 * Read general information for a list of structure-tree nodes.
 */
TcBool TcGetNodeInfoList (
   TcHdl scopeHandles[TcChunkLen],     /**< [in]  Structure-tree nodes */
   int nrHdls,                         /**< [in]  Number of nodes */
   TcNodeInfo nodeInfos[TcChunkLen]    /**< [out] General information for the nodes */
   );

/******************************************************************************/
/**
 * @brief Read information for a list of routine nodes
 *
 * Read information for a list of routine nodes (structure-tree).
 */
TcBool TcGetRoutineInfoList (
   TcHdl routineScopeHandles[TcChunkLen],    /**< [in]  Routine handles (structure-tree nodes) */
   int nrHdls,                               /**< [in]  Number of nodes */
   TcRoutineInfo routineInfos[TcChunkLen]    /**< [out] Information for the routines */
   );

/******************************************************************************/
/**
 * @brief Read information for a list of variable nodes
 *
 * Read information for a list of variable nodes (structure-tree).
 */
TcBool TcGetVarInfoList (
   TcHdl varScopeHandles[TcChunkLen],  /**< [in]  Variable handles (structure-tree nodes) */
   int nrHdls,                         /**< [in]  Number of nodes */
   TcVarInfo varInfos[TcChunkLen]      /**< [out] Information for the variables */
   );

/******************************************************************************/
/**
 * @brief Read information for a list of type nodes
 *
 * Read information for a list of type nodes (structure-tree).
 */
TcBool TcGetTypeInfoList (
   TcHdl typeScopeHandles[TcChunkLen], /**< [in]  Type handles (structure-tree nodes) */
   int nrHdls,                         /**< [in]  Number of nodes */
   TcTypeInfo typeInfos[TcChunkLen]    /**< [out] Information for the types */
   );

/******************************************************************************/
/**
 * @brief Read information for a list of constant nodes
 *
 * Read information for a list of constant nodes (structure-tree).
 */
TcBool TcGetConstInfoList (
   TcHdl constScopeHandles[TcChunkLen],   /**< [in]  Constant handles (structure-tree nodes) */
   int nrHdls,                            /**< [in]  Number of nodes */
   TcConstInfo constInfos[TcChunkLen]     /**< [out] Information for the constants */
   );

/******************************************************************************/
/**
 * @brief Read attributes for a list of structure-tree nodes
 *
 * Read the attributes-text for a list of structure-tree nodes.
 */
TcBool TcGetAttributes (
   TcHdl scopeHandles[TcChunkLen],              /**< [in]  Structure-tree nodes */
   int nrHdls,                                  /**< [in]  Number of nodes */
   char attributes[TcChunkLen][TcMaxAttrLen+1]  /**< [out] Attributes-text for the nodes */
   );

/******************************************************************************/
/**
 * @brief Set the attributes for a structure-tree node
 *
 * Set the attributes-text for a structure-tree node.
 */
TcBool TcSetAttributes (
   TcHdl scopeHandle,               /**< [in] Structure-tree node */
   char attributes[TcMaxAttrLen+1]  /**< [in] New attributes-text */
   );

/******************************************************************************/
/**
 * @brief Create a new program
 *
 * Create a new program, the corresponding file is created as well if necessary.
 */
TcBool TcAddProgramNode (
   TcNodeInfo *nodeInfo    /**< [in] General information, relevant: upperHnd, attr, elemName */
   );

/******************************************************************************/
/**
 * @brief Create a new routine
 *
 * Create a new routine, the text in the corresponding file is created as well.
 */
TcBool TcAddRoutineNode (
   TcNodeInfo *nodeInfo,         /**< [in] General information */
   TcRoutineInfo *routineInfo    /**< [in] Routine information */
   );

/******************************************************************************/
/**
 * @brief Create a new variable
 *
 * Create a new variable
 */
TcBool TcAddVarNode (
   TcNodeInfo *nodeInfo,   /**< [in] General information */
   TcVarInfo *varInfo      /**< [in] Variable information */
   );

/******************************************************************************/
/**
 * @brief Create a new type
 *
 * Create a new type, the text in the corresponding file is created as well.
 */
TcBool TcAddTypeNode (
   TcNodeInfo *nodeInfo,   /**< [in] General information */
   TcTypeInfo *typeInfo    /**< [in] Type information */
   );

/******************************************************************************/
/**
 * @brief Create a new type
 *
 * Create a new type, the text in the corresponding file is created as well.
 */
TcBool TcAddConstNode (
   TcNodeInfo *nodeInfo,   /**< [in] General information */
   TcConstInfo *constInfo  /**< [in] Constant information */
   );

/******************************************************************************/
/**
 * @brief Rename a structure-tree node
 *
 * Rename a structure-tree node, only variables subordinate to projects or
 * programs can be renamed. All references to the variable in its project and 
 * in subordinate loaded projects are renamed as well.
 */
TcBool TcRenameNode (
   TcHdl scopeHnd,      /**< [in] Variable handle (structure-tree node) */
   const char *newName  /**< [in] The new name of the variable */
   );

/******************************************************************************/
/**
 * @brief Move a variable
 *
 * Move a variable into a new scope. It is checked whether all accesses in
 * compiled projects will still be possible and whether the variable can be
 * added to the new scope. Source- and target- location have to be static. There
 * has to be a hierarchical relation between the source and the target, a
 * variable can oly be moved to subordinate or superordinate locations.
 * An unreferenced variable can also be moved between loaded projects, otherwise
 * the dependent scope must not be loaded since it has to be recompiled.
 */
TcBool TcMoveVar (
   TcHdl varHnd,        /**< [in]  Existing variable handle */
   TcHdl newScopeHnd,   /**< [in]  New scope handle */
   TcHdl *newVarHnd     /**< [out] New variable handle */
   );

/******************************************************************************/
/**
 * @brief Remove a structure-tree node
 *
 * Remove a structure-tree node, the text in the corresponding file is removed
 * as well. Referenced nodes can not be removed.
 */
TcBool TcRemoveNode (
   TcHdl scopeHnd    /**< [in] Structure-tree node */
   );

/******************************************************************************/
/**
 * @brief Get an access handle for the given variable
 *
 * Get a variable access handle for the variable given by its access path.
 */
TcBool TcOpenVarAccess (
   const char *varAccessPath, /**< [in]  Variable access path, e.g. "prog.v[4].x" */
   TcVarAccess *varAccess,    /**< [out] Variable access handle */
   TcTypeKind *typeKind       /**< [out] Type of the variable */
   );

/******************************************************************************/
/**
 * @brief Get access handles for the given variables
 *
 * Get variable access handles for the variables given by their access paths.
 */
TcBool TcOpenVarAccessList (
   char *varAccessPaths[TcChunkLen],   /**< [in]  Variable access paths */
   int nrVars,                         /**< [in]  Number of variables */
   TcVarAccess varAccess[TcChunkLen],  /**< [out] Variable access handles */
   TcVarAccessInfo info[TcChunkLen]    /**< [out] Access information */
   );

/******************************************************************************/
/**
 * @brief Get the SAVE-value of a variable
 *
 * Get the SAVE-value of a variable or a variable component.
 */
TcBool TcGetSaveValue (
   TcVarAccess *varAccess, /**< [in]  Variable access handle */
   TcValue *varValue       /**< [out] Received SAVE-value */
   );

/******************************************************************************/
/**
 * @brief Get the SAVE-values of multiple variables
 *
 * Get the SAVE-values of multiple variables or variable components.
 */
TcBool TcGetSaveValueList (
   TcVarAccess varAccess[TcChunkLen],  /**< [in]  Variable access handles */
   int nrVars,                         /**< [in]  Number of variables */
   TcValue varValue[TcChunkLen]        /**< [out] Received SAVE-values */
   );

/******************************************************************************/
/**
 * @brief Set the SAVE-value for a variable
 *
 * Set the SAVE-value for a variable or a variable component.
 */
TcBool TcSetSaveValue (
   TcVarAccess *varAccess, /**< [in] Variable access handle */
   TcValue *varValue       /**< [in] The new SAVE-value */
   );

/******************************************************************************/
/**
 * @brief Copy SAVE-values between variables
 *
 * Copy actual values for the SAVE-members from one variable to another if
 * possible, otherwise the values from the SAVE-lists themselves. 
 */
TcBool TcCopySaveValue (
   TcVarAccess *destVarAccess,   /**< [in] Variable access handle for the destination variable */
   TcVarAccess *srcVarAccess     /**< [in] Variable access handle for the source variable */
   );

/******************************************************************************/
/**
 * @brief Get the actual value of a variable
 *
 * Get the actual value of a variable with basic type.
 */
TcBool TcGetActValue (
   TcHdl exeUnitHnd,       /**< [in]  Execution node, routine handle or 0 for static variables */
   TcVarAccess *varAccess, /**< [in]  Variable access handle */
   TcValue *varValue       /**< [out] The received actual value */
   );

/******************************************************************************/
/**
 * @brief Get a list of actual values of variables
 *
 * Get a list of actual values of variables with basic type.
 */
TcBool TcGetActValueList (
   TcHdl exeUnitHnds[TcChunkLen],      /**< [in]  Execution nodes, routine handle or 0 for static variables */
   TcVarAccess varAccess[TcChunkLen],  /**< [in]  Variable access handle */
   int nrVars,                         /**< [in]  Number of variables */
   TcValue varValues[TcChunkLen]       /**< [out] The received actual values */
   );

/******************************************************************************/
/**
 * @brief Set the value of a variable
 *
 * Set the value of a variable with basic type.
 */
TcBool TcSetActValue (
   TcHdl exeUnitHnd,       /**< [in] Execution node, routine handle or 0 for static variables */
   TcVarAccess *varAccess, /**< [in] Variable access handle */
   TcValue *varValue       /**< [in] The new value */
   );

/******************************************************************************/
/**
 * @brief Set the value of a variable without logging
 *
 * Set the value of a variable with basic type without logging.
 */
TcBool TcSetActValueSilent (
   TcHdl exeUnitHnd,       /**< [in] Execution node, routine handle or 0 for static variables */
   TcVarAccess *varAccess, /**< [in] Variable access handle */
   TcValue *varValue       /**< [in] The new value */
   );

/******************************************************************************/
/**
 * @brief Copy the actual values from one variable to another
 *
 * Copy the actual values from one variable to another variable.
 */
TcBool TcCopyActValue (
   TcHdl destExeUnitHnd,         /**< [in] Destination execution node, routine handle or 0 for static variables */
   TcVarAccess *destVarAccess,   /**< [in] Destination variable access handle */
   TcHdl srcExeUnitHnd,          /**< [in] Source execution node, routine handle or 0 for static variables */
   TcVarAccess *srcVarAccess     /**< [in] Source variable access handle */
   );

/******************************************************************************/
/**
 * @brief Create an access handle for a variable
 *
 * Create an access handle for the given variable.
 */
TcBool TcGetVarAccess (
   TcHdl varHnd,           /**< [in]  Variable handle (structure-tree node) */
   TcVarAccess *varAccess  /**< [out] The new variable access handle */
   );

/******************************************************************************/
/**
 * @brief Create an access handle for a structure element
 *
 * Create a variable access handle for a structure element.
 */
TcBool TcGetStructElemAccess (
   TcVarAccess *varAccess,    /**< [in]  Variable access handle for the structure */
   TcHdl elemHnd,             /**< [in]  Variable handle for the structure element (structure-tree node) */
   TcVarAccess *elemAccess    /**< [out] Variable access handle for the structure element */
   );

/******************************************************************************/
/**
 * @brief Create an access handle for an array element
 *
 * Create a variable access handle for an array element.
 */
TcBool TcGetArrayElemAccess (
   TcVarAccess *varAccess,    /**< [in]  Variable access handle for the array */
   int index,                 /**< [in]  Array-index */
   TcVarAccess *elemAccess    /**< [out] Variable access handle for the array element */
   );

/******************************************************************************/
/**
 * @brief Create a temporary instance
 *
 * Create the temporary instance for the given unit type. If the instance
 * existed already then the ececution node will be deleted and recreated, but
 * the structure-tree node of the temporary variable remains valid. 
 */
TcBool TcCreateInstance (
   TcHdl typeHnd,       /**< [in]  Type handle (structure-tree node) */
   TcHdl *tempVarHnd    /**< [out] Variable handle of the temporary variable (structure-tree node) */
   );

/******************************************************************************/
/**
 * @brief Get the current target of a MAPTO-variable
 *
 * Get the current target of the given MAPTO-variable.
 */
TcBool TcGetMapTarget (
   TcHdl exeUnitHnd,       /**< [in]  Execution node, routine handle or 0 for static variables */
   TcVarAccess *varAccess, /**< [in]  Variable access handle */
   TcMapTarget *target     /**< [out] The current target */
   );

/******************************************************************************/
/**
 * @brief Set the target of a MAPTO-variable
 *
 * Set the target of the given MAPTO-variable.
 */
TcBool TcSetMapTarget (
   TcHdl exeUnitHnd,       /**< [in] Execution node, routine handle or 0 for static variables */
   TcVarAccess *varAccess, /**< [in] Variable access handle */
   TcMapTarget *target     /**< [in] The new target */
   );

/******************************************************************************/
/**
 * @brief Write a new initialization
 *
 * Use the current variable values to write a new initialization for the given
 * variable. The function can only be used with static variables declared in
 * enduser-files (".tid"-files).
 */
TcBool TcWriteInitValue (
   TcHdl varHnd   /**< [in] Variable handle (structure-tree node) */
   );

/******************************************************************************/
/**
 * @brief Get a memory dump
 *
 * Get a copy of the specified memory area belonging to the given variable.
 */
TcBool TcGetMemDump (
   TcHdl exeUnitHnd,       /**< [in]  Execution node, routine handle or 0 for static variables */
   TcVarAccess *varAccess, /**< [in]  Variable access handle */
   int offset,             /**< [in]  Start offset within the variable in bytes */
   unsigned char *buffer,  /**< [out] Buffer into which the memory shall be copied */
   int bufferSize,         /**< [in]  Size of the buffer in bytes */
   int *nrBytes,           /**< [out] Number of received bytes */
   TcBool *bigEndian       /**< [out] 0: buffer in little endian format, 1: buffer in big endian format */
   );

/******************************************************************************/
/**
 * @brief Get array elements
 *
 * Get the values of multiple array elements of a basic type.
 */
TcBool TcGetActArrayValues (
   TcHdl exeUnitHnd,       /**< [in]  Execution node, routine handle or 0 for static variables */
   TcVarAccess *varAccess, /**< [in]  Variable access handle */
   int offset,             /**< [in]  Start offset within the array, this is the number of elements that shall be skipped */
   TcValue *buffer,        /**< [out] Buffer into which the elements shall be copied */
   int bufferSize,         /**< [in]  Size of the buffer in bytes */
   int *nrElems            /**< [out] Number of received elements */
   );

/******************************************************************************/
/**
 * @brief Create a duplicate of a variable
 *
 * Create a new variable, the text in the corresponding file is created as well.
 * Before NEW- and INIT-routines are executed the data from the source variable
 * is copied into the new variable.
 */
TcBool TcDuplicateVar (
   TcNodeInfo *destNodeInfo,  /**< [in] General information */
   TcVarInfo *destVarInfo,    /**< [in] Variable information */
   TcHdl srcExeUnitHnd,       /**< [in] Source execution node, routine handle or 0 for static variables */
   TcVarAccess *srcVarAccess  /**< [in] Source variable access handle */
   );

/******************************************************************************/
/**
 * @brief Create a new variable group
 *
 * Create a new variable group with the given name.
 */
TcBool TcNewVarGroup (
   const char *groupName,  /**< [in]  The name of the new variable group */
   TcHdl *groupHnd         /**< [out] The new variable group */
   );

/******************************************************************************/
/**
 * @brief Remove a variable group
 *
 * Delete the given variable group.
 */
TcBool TcRemoveVarGroup (
   TcHdl groupHnd    /**< [in] The variable group that shall be deleted */
   );

/******************************************************************************/
/**
 * @brief Add variables to a variable group
 *
 * Add variables to the given variable group. Each added variable receives a
 * group identity number (group ID).
 *
 * @return Returns true only if all variables were added successfully
 */
TcBool TcAddVarsToGroup (
   TcHdl groupHnd,                        /**< [in]  Variable group */
   TcHdl exeUnitHnds[TcChunkLen],         /**< [in]  Execution nodes, routine handle or 0 for static variables */
   TcVarAccess varAccessHnds[TcChunkLen], /**< [in]  Variable access handles */
   int varIds[TcChunkLen],                /**< [out] Group IDs of the  added variables */
   int *nrVars                            /**< [in/out] in: Number of variables to add, out: Number of variables added successfully */
   );

/******************************************************************************/
/**
 * @brief Remove variables from a variable group
 *
 * Remove certain variables from the given variable group.
 */
TcBool TcRemoveVarsFromGroup (
   TcHdl groupHnd,         /**< [in] Variable group */
   int varIds[TcChunkLen], /**< [in] Group IDs of the variables to remove */
   int nrVars              /**< [in] Number of variables to remove */
   );

/******************************************************************************/
/**
 * @brief Read values of variables in a variable group
 *
 * Read the values of variables in the given variable group.
 */
TcBool TcReadVarGroupValues (
   TcHdl groupHnd,                  /**< [in]  Variable group */
   int startIdx,                    /**< [in]  Number of group variables to skip */
   int varIds[TcChunkLen],          /**< [out] Group IDs of the variables that were read */
   TcValue varValues[TcChunkLen],   /**< [out] Values of the variables that were read */
   int *nrVars                      /**< [out] Number of variables that were read */
   );

/******************************************************************************/
/**
 * @brief Read changed values of variables in a variable group
 *
 * Read the values of variables in the given variable group. Only values that
 * were modified since the last read-command are considered.
 */
TcBool TcReadChangedVarGroupValues (
   TcHdl groupHnd,                  /**< [in]  Variable group */
   int startIdx,                    /**< [in]  Number of group variables to skip */
   int varIds[TcChunkLen],          /**< [out] Group IDs of the variables that were read */
   TcValue varValues[TcChunkLen],   /**< [out] Values of the variables that were read */
   int *nrVars                      /**< [out] Number of variables that were read */
   );

/******************************************************************************/
/**
 * @brief Load a project
 *
 * Load a project.
 *
 * @deprecated Use TcLoadProj instead.
 */
TcBool TcLoadGlobal (
   TcHdl globalScopeHnd,   /**< [in]  Project that shall be loaded (structure-tree node) */
   TcHdl *exeUnitHnd       /**< [out] Project that was created (execution node) */
   );

/******************************************************************************/
/**
 * @brief Unload a project
 *
 * Unload a project, 0 can be used for the top-project.
 */
TcBool TcUnloadGlobal (
   TcHdl exeUnitHnd  /**< [in] Project that shall be unloaded (execution node), 0 for the top project */
   );

/******************************************************************************/
/**
 * @brief Load a project
 *
 * Load a project. During loading the variables are initialized and NEW- and
 * INIT- routines are executed. If superordinate projects exist in the 
 * structure-tree but not in the execution-tree then they will be loaded as
 * well.
 */
TcBool TcLoadProj (
   TcHdl projHnd,       /**< [in]  Project that shall be loaded (structure-tree node) */
   TcHdl *exeUnitHnd    /**< [out] Project that was created (execution node) */
   );

/******************************************************************************/
/**
 * @brief Unload a project
 *
 * Unload a project. During unloading EXIT- and DELETE- routines are executed.
 * If subordinate projects exist they will be unloaded as well.
 */
TcBool TcUnloadProj (
   TcHdl exeUnitHnd  /**< [in] Project that shall be unloaded (execution node) */
   );

/******************************************************************************/
/**
 * @brief Start a program
 *
 * Start the unnamed routine of a program (ttp- or tip- file). The associated
 * project has to be loaded completely first. The started routine is called
 * 'sequence'.
 */
TcBool TcStartProg (
   TcHdl progScopeHnd,  /**< [in]  Program (structure-tree node) */
   TcHdl *exeUnitHnd    /**< [out] Sequence (execution node) */
   );

/******************************************************************************/
/**
 * @brief Start a program
 *
 * Start the unnamed routine of a program (ttp- or tip- file). The associated
 * project has to be loaded completely first. Extended start properties can be
 * specified. The started routine is called 'sequence'.
 *
 * @see TcStartFlags
 */
TcBool TcStartProgEx (
   TcHdl progScopeHnd,  /**< [in]  Program (structure-tree node) */
   int startFlags,      /**< [in]  Start properties */
   TcHdl *exeUnitHnd    /**< [out] Sequence (execution node) */
   );

/******************************************************************************/
/**
 * @brief Interrupt a program
 *
 * Interrupt a program sequence.
 */
TcBool TcInterruptProg (
   TcHdl exeUnitHnd  /**< [in] Sequence (execution node) */
   );

/******************************************************************************/
/**
 * @brief Continue a program
 *
 * Continue a program sequence.
 */
TcBool TcContinueProg (
   TcHdl exeUnitHnd  /**< [in] Sequence (execution node) */
   );

/******************************************************************************/
/**
 * @brief Stop a program
 *
 * Stop a program sequence.
 */
TcBool TcStopProg (
   TcHdl exeUnitHnd  /**< [in] Sequence (execution node) */
   );

/******************************************************************************/
/**
 * @brief Execute a method
 *
 * Execute the method with the given name in the given block-instance with the
 * given parameter. The method has to have exactly one parameter with the type
 * of the block itself and a boolean return value.
 *
 * @deprecated Use TcExecuteMethodExt instead.
 */
TcBool TcExecuteMethod (
   const char *methodName,          /**< [in]  Method name */
   TcHdl instanceExeUnitHnd,        /**< [in]  Instance execution node */
   TcVarAccess *instanceVarAccess,  /**< [in]  Instance variable access handle */
   TcHdl paramExeUnitHnd,           /**< [in]  Parameter execution node */
   TcVarAccess *paramVarAccess,     /**< [in]  Parameter variable access handle */
   TcBool *methodRetVal             /**< [out] Method return value */
   );

/******************************************************************************/
/**
 * @brief Execute a block- or program- routine
 *
 * Execute a routine in a block or program as a newly created sequence. Number
 * and types of the given parameters have to coincide with the given routine.
 * The return value of the routine (if any) has to be of a basic type.
 * If the routine has a return value this function waits for the routine to
 * finish.
 */
TcBool TcExecuteMethodExt (
   TcHdl routineHnd,                   /**< [in]  Routine (structure-tree node) */
   TcVarAccess *instance,              /**< [in]  Variable access handle for the block- or program-instance */
   TcMethodParam params[TcMaxParams],  /**< [in]  Parameters */
   int nrParams,                       /**< [in]  Number of parameters */
   TcValue *methodRetVal               /**< [out] Return value of the executed routine */
   );

/******************************************************************************/
/**
 * @brief Get the first execution unit
 *
 * Get the first execution unit of the given kind subordinate to the given
 * parent execution unit.
 */
TcBool TcGetFirstExeUnit (
   TcHdl parentHnd,     /**< [in]  Parent execution unit */
   TcExeUnitKind kind,  /**< [in]  Kind of units to search */
   TcHdl *iterHnd,      /**< [out] Handle for iteration */
   TcHdl *exeUnitHnd    /**< [out] First execution unit */
   );

/******************************************************************************/
/**
 * @brief Get the next execution unit
 *
 * Get the next execution unit of the given kind subordinate to the given
 * parent execution unit.
 */
TcBool TcGetNextExeUnit (
   TcHdl parentHnd,     /**< [in]  Parent execution unit */
   TcExeUnitKind kind,  /**< [in]  Kind of units to search */
   TcHdl *iterHnd,      /**< [in/out] Handle for iteration */
   TcHdl *exeUnitHnd    /**< [out] Next execution unit */
   );

/******************************************************************************/
/**
 * @brief Get the first chunk of execution units
 *
 * Get the first chunk of execution units of the given kind subordinate to the
 * given parent execution unit.
 */
TcBool TcGetFirstExeUnitChunk (
   TcHdl parentHnd,                 /**< [in]  Parent execution unit */
   TcExeUnitKind kind,              /**< [in]  Kind of units to search */
   TcHdl *iterHnd,                  /**< [out] Handle for iteration */
   TcHdl exeUnitHnds[TcChunkLen],   /**< [out] First execution units */
   int *nrExeUnitHnds               /**< [out] Number of received units */
   );

/******************************************************************************/
/**
 * @brief Get the next chunk of execution units
 *
 * Get the next chunk of execution units of the given kind subordinate to the
 * given parent execution unit.
 */
TcBool TcGetNextExeUnitChunk (
   TcHdl parentHnd,                 /**< [in]  Parent execution unit */
   TcExeUnitKind kind,              /**< [in]  Kind of units to search */
   TcHdl *iterHnd,                  /**< [in/out] Handle for iteration */
   TcHdl exeUnitHnds[TcChunkLen],   /**< [out] Next execution units */
   int *nrExeUnitHnds               /**< [out] Number of received units */
   );

/******************************************************************************/
/**
 * @brief Get a chunk of execution units from multiple parent units
 *
 * Get a chunk of execution units from multiple parent units.
 *
 * @deprecated Use TcGetFirstExeUnitChunk/TcGetNextExeUnitChunk instead.
 */
TcBool TcGetMultExeUnitChunk (
   TcHdl parentHnds[TcChunkLen],       /**< [in]  Parent execution units */
   int nrParentHnds,                   /**< [in]  Number of parent units */
   TcExeUnitKind kind,                 /**< [in]  Kind of units to search */
   TcHdl *iterHnd,                     /**< [in/out] Handle for iteration, start with 0! */
   TcHdl upperExeUnitHnds[TcChunkLen], /**< [out] Received parent units */
   TcHdl exeUnitHnds[TcChunkLen],      /**< [out] Received execution units */
   int *nrExeUnitHnds                  /**< [out] Number of received units */
   );

/******************************************************************************/
/**
 * @brief Get information for an execution unit
 *
 * Get information for the given execution unit.
 */
TcBool TcGetExeUnitInfo (
   TcHdl exeUnitHnd,             /**< [in]  Execution unit */
   TcExeUnitInfo *exeUnitInfo    /**< [out] Information for the unit */
   );

/******************************************************************************/
/**
 * @brief Get information for a list of execution units
 *
 * Get information for a list of execution units.
 */
TcBool TcGetExeUnitInfoList (
   TcHdl exeUnitHnds[TcChunkLen],         /**< [in]  Execution units */
   int nrExeUnits,                        /**< [in]  Number of units */
   TcExeUnitInfo exeUnitInfo[TcChunkLen]  /**< [out] Information for the units */
   );

/******************************************************************************/
/**
 * @brief Get the status of an execution unit
 *
 * Get the status of the given execution unit.
 */
TcBool TcGetExeUnitStatus (
   TcHdl exeUnitHnd,                /**< [in]  Execution unit */
   TcExeUnitStatus *exeUnitStatus   /**< [out] Status of the unit */
   );

/******************************************************************************/
/**
 * @brief Get the status for a list of execution units
 *
 * Get the status for a list of execution units.
 */
TcBool TcGetExeUnitStatusList (
   TcHdl exeUnitHnds[TcChunkLen],               /**< [in]  Execution units */
   int nrExeUnits,                              /**< [in]  Number of units */
   TcExeUnitStatus exeUnitStatus[TcChunkLen]    /**< [out] Status information for the units */
   );

/******************************************************************************/
/**
 * @brief Set the debug mode
 *
 * Set the debug mode.
 *
 * @deprecated Use TcSetExeFlag instead.
 */
TcBool TcSetDebugMode (
   TcHdl exeUnitHnd,    /**< [in] (not used) */
   TcExeFlags exeFlags  /**< [in] Routine- or flow- related */
   );

/******************************************************************************/
/**
 * @brief Set or reset an execution flag
 *
 * Set or reset the given execution flag.
 */
TcBool TcSetExeFlag (
   TcHdl exeUnitHnd,    /**< [in] Routine or flow */
   TcExeFlags exeFlags, /**< [in] Affected flag */
   TcBool value         /**< [in] New value */
   );

/******************************************************************************/
/**
 * @brief Start a step command
 *
 * Start a step command.
 */
TcBool TcStep (
   TcHdl exeUnitHnd,    /**< [in] Routine or flow */
   TcStepState stepCmd  /**< [in] Step command */
   );

/******************************************************************************/
/**
 * @brief Start a step command
 *
 * Start a step command for multiple execution units..
 */
TcBool TcStepList (
   TcHdl exeUnitHnds[TcChunkLen],   /**< [in] Execution units */
   int nrExeUnits,                  /**< [in] Number of units */
   TcStepState stepCmd              /**< [in] Step command */
   );

/******************************************************************************/
/**
 * @brief Set a code-point
 *
 * Set a break- or watch-point on the given line in the given routine. The
 * code-point can be restricted to a specific block-instance. 
 */
TcBool TcSetCodePoint (
   TcHdl routScopeHnd,           /**< [in] Routine (structure-tree node) */
   int lineNr,                   /**< [in] The line for the code-point */
   TcHdl exeUnitHnd,             /**< [in] (not used) */
   TcInstancePath *instancePath, /**< [in] Specific block-instance (or empty path if not used) */
   TcCodePointKind kind          /**< [in] Kind of the new code-point */
   );

/******************************************************************************/
/**
 * @brief Remove code-points
 *
 * Remove code-points.
 */
TcBool TcRemoveCodePoint (
   TcHdl routScopeHnd,  /**< [in] Routine (structure-tree node), 0 for all code-points in all routines */
   int lineNr           /**< [in] Line number, -1 for all code-points in the given routine */
   );

/******************************************************************************/
/**
 * @brief Get code-points
 *
 * Get all code-points for the given routine.
 */
TcBool TcGetCodePoints (
   TcHdl routScopeHnd,                       /**< [in]  Routine (structure-tree node) */
   int lineNrs[TcMaxCodePoints],             /**< [out] Line numbers of the code-points */
   TcCodePointKind kinds[TcMaxCodePoints],   /**< [out] Kinds of the code-points  */
   TcBool active[TcMaxCodePoints],           /**< [out] Activation state of the code-points */
   int *nrCodepoints                         /**< [out] Number of code-points */
   );

/******************************************************************************/
/**
 * @brief Get routines which have code-points
 *
 * Get routines which have code-points. The change counter is incremented
 * whenever a code-point in any routine is created or deleted.
 */
TcBool TcGetCodePointRoutines (
   int *chgCnt,                     /**< [out] Global change counter */
   TcHdl routScopeHnds[TcChunkLen], /**< [out] Routines with code-points (structure-tree nodes) */
   int *nrRoutines                  /**< [out] Number of routines */
   );

/******************************************************************************/
/**
 * @brief Activate or deactivate code-points
 *
 * Activate or deactivate code-points.
 */
TcBool TcActivateCodePoint (
   TcHdl routScopeHnd,  /**< [in] Routine (structure-tree node), 0 for all code-points in all routines */
   int lineNr,          /**< [in] Line number, -1 for all code-points in the given routine */
   TcBool active        /**< [in] 0: deactivate, 1: activate */
   );

/******************************************************************************/
/**
 * @brief Get a watch-point counter
 *
 * Read how often the given watch-point was passed through.
 */
TcBool TcGetWatchPointCounter (
   TcHdl routScopeHnd,  /**< [in]  Routine (structure-tree node) */
   int lineNr,          /**< [in]  Line number */
   int *counter         /**< [out] Number of passes */
   );

/******************************************************************************/
/**
 * @brief Reset watch-point counters
 *
 * Reset watch-point counters.
 */
TcBool TcResetWatchPointCounter (
   TcHdl routScopeHnd,  /**< [in] Routine (structure-tree node), 0 for all watch-points in all routines */
   int lineNr           /**< [in] Line number, -1 for all watch-points in the given routine */
   );

/******************************************************************************/
/**
 * @brief Add a variable to a watch-point
 *
 * Add a variable to a watch-point. The variable has to be static and of a
 * basic type. Only TcMaxWatchVars variables can be added to a watch-point.
 */
TcBool TcSetWatchPointVar (
   TcHdl routScopeHnd,           /**< [in]  Routine (structure-tree node) */
   int lineNr,                   /**< [in]  Line number */
   TcHdl exeUnitHnd,             /**< [in]  (not used) */
   TcInstancePath *instancePath, /**< [in]  Instance path of the variable */
   int *varNr                    /**< [out] Variable identification */
   );

/******************************************************************************/
/**
 * @brief Remove variables from a watch-point
 *
 * Remove variables from a watch-point.
 */
TcBool TcRemoveWatchPointVar (
   TcHdl routScopeHnd,  /**< [in] Routine (structure-tree node) */
   int lineNr,          /**< [in] Line number */
   int varNr            /**< [in] Variable identification, 0 for all variables of the watch-point */
   );

/******************************************************************************/
/**
 * @brief Get the value of a watch-point variable
 *
 * Get the value of the given watch-point variable.
 */
TcBool TcGetWatchPointValue (
   TcHdl routScopeHnd,  /**< [in]  Routine (structure-tree node) */
   int lineNr,          /**< [in]  Line number */
   int varNr,           /**< [in]  Variable identification */
   TcValue *varValue    /**< [out] Received value */
   );

/******************************************************************************/
/**
 * @brief Get all variables added to a watch-point
 *
 * Get all variables added to the given watch-point.
 */
TcBool TcGetWatchPointVars (
   TcHdl routScopeHnd,                             /**< [in]  Routine (structure-tree node) */
   int lineNr,                                     /**< [in]  Line number */
   TcHdl exeUnitHnds[TcMaxWatchVars],              /**< [out] (not used) */
   TcInstancePath instancePaths[TcMaxWatchVars],   /**< [out] Received Instance paths */
   int varNr[TcMaxWatchVars],                      /**< [out] Received variable identifications */
   int *nrWatchVars                                /**< [out] Number of received variables */
   );

/******************************************************************************/
/**
 * @brief Set watch-point triggers
 *
 * Set watch-point trigger values, this modifies how often variable values are
 * saved. With 'count=0' values are saved every time the watch-point is passed
 * (default). With 'count>0' values are saved once after 'count' passes.
 */
TcBool TcSetWatchPointTrigger (
   TcHdl routScopeHnd,  /**< [in] Routine (structure-tree node), 0 for all watch-points in all routines */
   int lineNr,          /**< [in] Line number, -1 for all watch-points in the given routine */
   int count            /**< [in] New trigger value */
   );

/******************************************************************************/
/**
 * @brief Request a state manager transition
 *
 * Submit the given command to request a state manager transition.
 */
TcBool TcStateMgrCommand (
   TcStateMgrCmd cmd    /**< [in] Command for the state manager */
   );


#ifdef __cplusplus
}
#endif

#endif
