/*------------------------------------------------------------------------------
*                             (c) 2019 by KEBA AG
*                                www.keba.com
*                                Linz/Austria
*                             All rights reserved
*-------------------------------------------------------------------------------
*/
/** @file
*   @brief General definitions for a teachcontrol-client
*
*   General definitions for a teachcontrol-client
*/
/*------------------------------------------------------------------------------
*/

#ifndef _TcClientDefinitions_H
#define _TcClientDefinitions_H

#include <stdint.h>

#ifdef  __cplusplus
extern "C" {
#endif


#define TcMaxNameLen             32    /**< Maximal name length */
#define TcNrErrorParams           8    /**< Maximal number of (error-)message parameters */
#define TcErrorStringBufferSize  76    /**< (Error-)Message string-buffer size */
#define TcMaxPathLen            255    /**< Maximal path length (characters) */
#define TcMaxStrLen             255    /**< Maximal string length (characters) */
#define TcChunkLen               50    /**< Array-length for packed read functions */
#define TcMaxClients             10    /**< Maximal number of simultaneous clients */
#define TcErrorLimit             20    /**< Maximal number of compiler error messages */
#define TcMaxAttrLen            512    /**< Maximal length of attribute-strings (characters) */
#define TcMaxParams              16    /**< Maximal number of method parameters */

typedef int TcHdl;                           /**< Handle */
typedef char TcBool;                         /**< Boolean value (1 byte, 0:false, 1:true) */
typedef char TcDirHandle [TcMaxPathLen + 1]; /**< Directory handle */

/** Client type */
typedef int TcClientType;
enum {
   TcClientTypeController, /**< Controller, full access */
   TcClientTypeObserver    /**< Observer, only read access */
};

/** Kinds of directory entries */
typedef int TcDirEntryKind;
enum {
   TcDirEntryKindProject       = 0,    /**< '.tt' */
   TcDirEntryKindUnit          = 1,    /**< '.tts' */
   TcDirEntryKindProg          = 2,    /**< '.ttp' */
   TcDirEntryKindData          = 3,    /**< '.ttd' */
   TcDirEntryKindFilterAllTc   = 4,    /**< Filter for '.tt', '.tts', '.ttp', '.ttd', '.tip', '.tid', '.tir' */
   TcDirEntryKindNoTc          = 5,    /**< No TC-file/folder */
   TcDirEntryKindUserProg      = 6,    /**< '.tip' */
   TcDirEntryKindUserData      = 7,    /**< '.tid' */
   TcDirEntryKindFilterAllUser = 8,    /**< Filter for '.tip', '.tid', '.tir' */
   TcDirEntryKindFilterAllProg = 9,    /**< Filter for '.ttp', '.tip' */
   TcDirEntryKindFilterAll     = 10,   /**< All files/folders */
   TcDirEntryKindArchive       = 11,   /**< Archive-file '.tta' */
   TcDirEntryKindStarepVar     = 12,   /**< Variable file for the state report '.ts' */
   TcDirEntryKindUserFunc      = 13,   /**< '.tir' */
   TcDirEntryKindUserVar       = 14    /**< '.tiv' */
};

/** Information for a directory entry */
typedef struct TcDirEntryInfo {
   char name[TcMaxNameLen+1]; /**< Name of the entry */
   TcDirEntryKind kind;       /**< The kind of the entry */
   long size;                 /**< Size of the entry (bytes) */
   unsigned long attr;        /**< Attributes */
   unsigned long createTime;  /**< Creation time */
   unsigned long modifyTime;  /**< Modification time */
   unsigned long accessTime;  /**< Last access time */
   TcBool isGlobal;           /**< @deprecated True for name='_global' */
} TcDirEntryInfo;

/** (Error-)Message kind */
typedef int TcErrorKind;
enum {
   TcErrorKindInfo      = 1,  /**< Info */
   TcErrorKindWarning   = 2,  /**< Warning */
   TcErrorKindError     = 3,  /**< Error */
   TcErrorKindErrorInfo = 4   /**< Error-Info */
};

/** (Error-)Message parameter type */
typedef int TcErrorParamType;
enum {
   TcErrorParamTypeInt    = 0,   /**< Integer */
   TcErrorParamTypeFloat  = 1,   /**< Floating point */
   TcErrorParamTypeString = 2    /**< String */
};

/** (Error-)Message parameter */
typedef struct TcErrorParam {
   TcErrorParamType type;                       /**< (Error-)Message) parameter type */
   int intValue;                                /**< Value (for integer type ) */
   float floatValue;                            /**< Value (for float type ) */
   char stringValue[TcErrorStringBufferSize];   /**< Value (for string type ) */
} TcErrorParam;

/** (Error-)Message element */
typedef struct TcErrorElem {
   TcErrorKind msgKind;                   /**< Message kind */
   int msgNr;                             /**< Message number */
   int nrParams;                          /**< Number of parameters */
   TcErrorParam params[TcNrErrorParams];  /**< Parameters */
} TcErrorElem;

/** Information about a client */
typedef struct TcClientInfo {
   int hnd;                   /**< Connection handle */
   TcClientType type;         /**< Client type */
   char name[TcMaxNameLen];   /**< Client name @see TcSetClientName */
} TcClientInfo;

/** Priority of a teachtalk routine */
typedef int TcPriority;
enum {
   TcPriorityNone     = -1,
   TcPriorityTop      = 0, /**< Highest priority, PRIO 0 */
   TcPriorityHigh     = 1, /**< Routines started using PRIO, PRIO 1 */
   TcPriorityStandard = 2, /**< Routines started normally, PRIO 2 */
   TcPrioritySystem   = 3, /**< Routines started by the system, PRIO 3 */
   TcPriorityLow      = 4  /**< Lowest priority, PRIO 4 */
};

/** Command for the state manager */
typedef int TcStateMgrCmd;
enum {
   TcStateMgrCmdLoad       = 1, /**< (INIT -> STOP) Build */
   TcStateMgrCmdUnload     = 2, /**< (STOP -> INIT) Destroy */
   TcStateMgrCmdActivate   = 3, /**< (STOP -> RUN ) Load */
   TcStateMgrCmdStop       = 4, /**< (RUN  -> STOP) Unload */
   TcStateMgrCmdContinue   = 5, /**< (HALT -> RUN ) Continue */
   TcStateMgrCmdInterrupt  = 6  /**< (RUN  -> HALT) Interrupt */
};


#define TcNrOffsets            29   /**< Maximal number of offsets in a variable access handle */
#define TcMaxInstancePathElems 30   /**< Maximal number of elements in an instance-path */

/**
 * Variable access handle (structure). A component within the variable is
 * specified with its offset. If the component is a MAPTO-variable then 'index'
 * is incremented and the next offset in the array refers to the dereferenced
 * component.
 */
typedef struct TcVarAccess {
   TcHdl varHdl;              /**< Variable which is accessed initially */
   TcHdl typeHdl;             /**< Type of the component accessed finally */
   int index;                 /**< Index finally accessed in the offsets-array */
   int offsets[TcNrOffsets];  /**< Array with offsets */
} TcVarAccess;

/** Variable-value */
typedef struct TcValue {
   TcBool isValid;               /**< Shows whether the value is valid */
   char sValue[TcMaxStrLen + 1]; /**< Value of a STRING variable */
   int64_t i64Value;             /**< Value of a LINT/ULINT/LWORD/LREAL variable */
   float fValue;                 /**< Value of a REAL variable */
   int32_t i32Value;             /**< Value of a DINT/UDINT/DWORD variable */
   int16_t i16Value;             /**< Value of a INT/UINT/WORD variable */
   int8_t i8Value;               /**< Value of a SINT/USINT/BYTE variable */
   TcBool bValue;                /**< Value of a BOOL variable */
} TcValue;

/** Instance-path element */
typedef struct TcInstancePathElem {
   TcHdl selection; /**< Selection of a component of a structure or block */
   int index;       /**< Index in an array (if selection = 0) */
} TcInstancePathElem;

/** Decription of the instance-path of a variable (eg. "prog.x[5].y") */
typedef struct TcInstancePath {
   int nrOfElems;                                    /**< Number of elements in the instance-path */
   TcInstancePathElem elems[TcMaxInstancePathElems]; /**< Elements of the instance-path */
} TcInstancePath;

/** Information about changes in the structure-tree */
typedef struct TcNodeChange {
   int changeCnt; /**< Increasing counter value (starting with 0) */
   TcHdl hdl;     /**< Handle of the affected structure-tree element */
} TcNodeChange;

/** Kinds of structure-tree elements.*/
typedef int TcNodeKind;
enum {
   TcNodeKindRoot               = 0,   /**< Root-node, containing e.g. basic types */
   TcNodeKindGlobal             = 1,   /**< Global-project (_global.tt) */
   TcNodeKindProject            = 2,   /**< Project */
   TcNodeKindProgram            = 3,   /**< Program */
   TcNodeKindType               = 4,   /**< Type */
   TcNodeKindRoutine            = 5,   /**< Routine */
   TcNodeKindVariable           = 6,   /**< Variable */
   TcNodeKindConstant           = 7,   /**< Constant */
   TcNodeKindFilterAll          = 8,   /**< Iteration filter for all structure-tree elements */
   TcNodeKindFilterProgramUser  = 9,   /**< Iteration filter for all programs with USER-Attribute */
   TcNodeKindFilterTypeUser     = 10,  /**< Iteration filter for all types with USER-Attribute */
   TcNodeKindFilterRoutineUser  = 11,  /**< Iteration filter for all routines with USER-Attribute */
   TcNodeKindFilterVariableUser = 12,  /**< Iteration filter for all variables with USER-Attribute */
   TcNodeKindFilterConstantUser = 13,  /**< Iteration filter for all constants with USER-Attribute */
   TcNodeKindFilterAllUser      = 14,  /**< Iteration filter for all structure-tree elements with USER-Attribute */
   TcNodeKindSystem             = 15,  /**< System-project (_system) */
   TcNodeKindBase               = 16   /**< Base-project (_base) */
};

/** Attributes for structure-tree elements @see TcNodeInfo::attr */
typedef int TcNodeAttr;
enum {
   TcNodeAttrUser          = 1,   /**< USER attribute is set */
   TcNodeAttrHasAttributes = 2,   /**< Element has attributes */
   TcNodeAttrReferenced    = 4,   /**< Element is referenced */
   TcNodeAttrAbstract      = 8,   /**< Element is abstract (block or routine) */
   TcNodeAttrDeprecated    = 16,  /**< DEPRECATED attribute (routine) */
   TcNodeAttrExportVar     = 32,  /**< EXPORT variable */
   TcNodeAttrNormalProg    = 64,  /**< ttp-program */
   TcNodeAttrInterface     = 128, /**< INTERFACE-block */
   TcNodeAttrUserFunc      = 256  /**< User-function (tir) */
};

/** General information about structure-tree elements */
typedef struct TcNodeInfo {
   TcNodeKind kind;                 /**< The kind of the element */
   char elemName[TcMaxNameLen+1];   /**< Name of the element */
   int incCnt;                      /**< Incarnation counter */
   int refCnt;                      /**< Reference counter */
   uint32_t attr;                   /**< Bit field for node attributes @see TcNodeAttr */
   TcHdl upperHnd;                  /**< Handle of the (structural) superordinate element */
   TcHdl declHnd;                   /**< Handle of the program or block in which the element was declared (for projects or programs the element itself) */
} TcNodeInfo;

/** Kinds of routines */
typedef int TcRoutineKind;
enum {
   TcRoutineKindUnNamed = 0, /**< Unnamed routine */
   TcRoutineKindNamed   = 1, /**< Named routine */
   TcRoutineKindEvent   = 2  /**< Event-routine (AT-routine) */
};

/** Information about routines */
typedef struct TcRoutineInfo {
   int incCnt;          /**< Incarnation counter */
   int dataSize;        /**< Data size */
   int codeSize;        /**< @deprecated Always 0 */
   int nrOfStmts;       /**< Number of statements */
   TcHdl retTypHnd;     /**< Handle of the type of the return value */
   int nrFormalPar;     /**< Number of formal parameters */
   TcRoutineKind kind;  /**< The kind of the routine */
   TcHdl varHnd;        /**< Handle of the event-variable */
   TcBool isPrivate;    /**< 0: public, 1: private */
} TcRoutineInfo;

/** Kinds of variables */
typedef int TcVarKind;
enum {
   TcVarKindParam      = 0, /**< Routine-parameter */
   TcVarKindVar        = 1, /**< Normal variable */
   TcVarKindConstParam = 2, /**< Routine-parameter with attribute "CONST" */
   TcVarKindValueParam = 3, /**< Routine-parameter with attribute "VAR_IN" */
   TcVarKindVarConst   = 4  /**< Variable with attribute "CONST" */
};

/** Variable-attributes @see TcVarInfo::attr */
typedef int TcVarAttr;
enum {
   TcVarAttrOptional   = 1,  /**< Optional parameter */
   TcVarAttrReferenced = 2,  /**< Variable referenced */
   TcVarAttrReadonly   = 4,  /**< Attribute "READONLY" */
   TcVarAttrNoInit     = 8,  /**< Attribute "NOINIT" */
   TcVarAttrDynamic    = 16  /**< Dynamic variable without declaration text */
};

/** Information about variables */
typedef struct TcVarInfo {
   int incCnt;              /**< If >=0: incarnation counter. If <0: ones' complement of the offset (only for type-elements) */
   int dataSize;            /**< Data size */
   TcHdl typHnd;            /**< Handle of the type of the variable */
   TcVarKind kind;          /**< The kind of the variable */
   int attr;                /**< Bit field for variable attributes @see TcVarAttr */
   TcBool isPrivate;        /**< 0: public, 1: private */
   TcBool isSave;           /**< 1: is persistent (SAVE) */
   TcBool isProjectSave;    /**< 1: is persistent (SAVE PROJECT) */
   TcHdl variantConstHnd;   /**< Handle of the selection-constant for variants */
} TcVarInfo;

/** Information about constants */
typedef struct TcConstInfo {
   TcHdl typHnd;  /**< Handle of the type of the constant */
   TcValue value; /**< Value of the constant */
} TcConstInfo;

/** Kinds of types */
typedef int TcTypeKind;
enum {
   TcTypeKindNone     =  0,   /**< No type */
   TcTypeKindBool     =  1,   /**< BOOL */

   TcTypeKindInt8     =  2,   /**< SINT */
   TcTypeKindInt16    =  3,   /**< INT */
   TcTypeKindInt32    =  4,   /**< DINT */
   TcTypeKindInt64    =  5,   /**< LINT */

   TcTypeKindReal     =  6,   /**< REAL */
   TcTypeKindString   =  7,   /**< STRING of any length */
   TcTypeKindSubrange =  8,   /**< Subrange */
   TcTypeKindEnum     =  9,   /**< Enumeration */
   TcTypeKindArray    = 10,   /**< Array (ARRAY) */
   TcTypeKindStruct   = 11,   /**< Structure (STRUCT) */
   TcTypeKindUnit     = 12,   /**< Block ('.tts') */
   TcTypeKindRef      = 13,   /**< Reference (MAPTO) */
   TcTypeKindRoutine  = 14,   /**< ROUTINE */
   TcTypeKindAny      = 15,   /**< ANY */

   TcTypeKindProg     = 16,   /**< Program ('.ttp', 'tip') */
   TcTypeKindProj     = 17,   /**< User project ('.tt') */
   TcTypeKindGlobal   = 18,   /**< _global.tt */
   TcTypeKindSystem   = 19,   /**< _system.tt */

   TcTypeKindByte     = 20,   /**< BYTE */
   TcTypeKindWord     = 21,   /**< WORD */
   TcTypeKindDWord    = 22,   /**< DWORD */
   TcTypeKindLWord    = 23,   /**< LWORD */

   TcTypeKindLReal    = 24,   /**< LREAL */

   TcTypeKindBase     = 25,   /**< _base.tt */

   TcTypeKindUInt8    = 26,   /**< USINT */
   TcTypeKindUInt16   = 27,   /**< UINT */
   TcTypeKindUInt32   = 28,   /**< UDINT */
   TcTypeKindUInt64   = 29,   /**< ULINT */

   TcTypeKindAnyInt   = 30,   /**< ANY_INT */
   TcTypeKindAnyReal  = 31,   /**< ANY_REAL */
   TcTypeKindAnyNum   = 32,   /**< ANY_NUM */
   TcTypeKindAnyBit   = 33,   /**< ANY_BIT */
   TcTypeKindAnyBasic = 34    /**< ANY_BASIC */
};

/** Information about types */
typedef struct TcTypeInfo {
   int typeSize;              /**< Size of a variable with this type */
   TcHdl baseTypHnd;          /**< Handle of the base-type for alias-types or referenced type for MAPTO-types */
   TcTypeKind kind;           /**< The kind of the type */
   int lowerBound;            /**< Lower bound (for array- and subrange- types, 1 for creating STRING[N]) */
   int upperBound;            /**< Upper bound (for array- and subrange- types, N for creating STRING[N]) */
   TcHdl lowerBoundConstHnd;  /**< Handle of the constant for the lower bound for array- and subrange- types */
   TcHdl upperBoundConstHnd;  /**< Handle of the constant for the upper bound for array- and subrange- types, handle of the constant N for creating STRING[N] */
   TcHdl arraySizeConstHnd;   /**< Handle of the constant for the size for array-types */
   TcHdl baseUnitHnd;         /**< Handle of the base-type for inheritance */
   TcHdl variantVarHnd;       /**< Handle of the selection variable for variants */
   TcHdl returnTypeHnd;       /**< Handle of the return-type for routine-types */
   TcHdl arrayElemHnd;        /**< Handle of the element-type for array-types */
} TcTypeInfo;

/** Attributes for variable access handles @see TcVarAccessInfo::attr */
typedef int TcVarAccessAttr;
enum {
   TcVarAccessAttrUser         = 1,  /**< USER-attribute */
   TcVarAccessAttrPrivate      = 2,  /**< PRIVATE-attribute */
   TcVarAccessAttrReadonly     = 4,  /**< READONLY-attribute */
   TcVarAccessAttrConst        = 8,  /**< CONST-attribute */
   TcVarAccessAttrMapto        = 16  /**< MAPTO-variables involved */
};

/** Information about variable access handles */
typedef struct TcVarAccessInfo {
   TcTypeKind typeKind;    /**< The kind of the type of the variable access handle */
   int attr;               /**< Bit field for variable access handle attributes @see TcVarAccessAttr */
} TcVarAccessInfo;


#define TcMaxCallPathLen      80    /**< Maximal length of a call path (bytes)*/
#define TcMaxExternalPathLen 256    /**< Maximal length of an external call path (bytes) */
#define TcMaxCodePoints       20    /**< Maximal number of code-points in a routine */
#define TcMaxWatchVars        48    /**< Maximal number of variables in a watch-point */

/**  Flags that can be combined when starting a program @see TcStartProgEx */
typedef int TcStartFlags;
enum {
   TcStartFlagsEmpty     = 0, /**< No flag */
   TcStartFlagsInterrupt = 1, /**< The sequence shall be interrupted immediately */
   TcStartFlagsRestart   = 2, /**< After completion the sequence shall be reset to the first line and it shall be interrupted */
   TcStartFlagsMultiFlow = 4  /**< A new sequence shall be started even if a sequence already exists */
};

/** Kinds of execution units */
typedef int TcExeUnitKind;
enum {
   TcExeUnitKindInvalid           = -1,   /**< Invalid unit */
   TcExeUnitKindGlobal            = 0,    /**< Global project */
   TcExeUnitKindProject           = 1,    /**< Project */
   TcExeUnitKindProgram           = 2,    /**< Program */
   TcExeUnitKindRoutine           = 3,    /**< Routine */
   TcExeUnitKindFilterAll         = 4,    /**< Filter for all units */
   TcExeUnitKindFilterUserProgram = 5,    /**< Filter for end-user-programs */
   TcExeUnitKindFilterUserRoutine = 6,    /**< Filter for end-user-routines */
   TcExeUnitKindFilterAllUser     = 7,    /**< Filter for all end-user-units */
   TcExeUnitKindSystem            = 8,    /**< System project (_system) */
   TcExeUnitKindBase              = 9     /**< Base project (_base) */
};

/** States of execution units */
typedef int TcExecUnitState;
enum {
   TcExecUnitStateInvalid     = -1, /**< Invalid state */
   TcExecUnitStateWaiting     = 0,  /**< Routine is waiting */
   TcExecUnitStateRunning     = 1,  /**< Routine is running */
   TcExecUnitStateStepping    = 2,  /**< Routine is stepping */
   TcExecUnitStateDefunct     = 3,  /**< Routine has returned */
   TcExecUnitStateInterrupted = 4   /**< Routine is interrupted */
};

/** Step-command or -state, can relate to flows or routines @see TcSetExeFlag, TcStep, TcExeUnitStatus */
typedef int TcStepState;
enum {
   TcStepStateOff,       /**< @deprecated Do not use */
   TcStepStateStepBreak, /**< Interrupt execution of statements */
   TcStepStateStepInto,  /**< Execute until next statement */
   TcStepStateStepOver , /**< Execute until next statement in the current routine-incarnation */
   TcStepStateStepOut ,  /**< Execute until the current routine-incarnation returns */
   TcStepStateWait,      /**< @deprecated Do not use */
   TcStepStateStepGo     /**< Execute statements */
};

/** Information about execution units (static) */
typedef struct TcExeUnitInfo {
   TcExeUnitKind  kind;             /**< The kind of the execution unit */
   TcBool isMainFlow;               /**< @deprecated Do not use */
   TcInstancePath instancePath;     /**< Instance-path */
   char callPath[TcMaxCallPathLen]; /**< Call path (only for routines) */
   TcHdl structureHdl;              /**< Corresponding structure-tree node */
   TcPriority priority;             /**< Priority (only for routines) */
} TcExeUnitInfo;

/** Possible states of a project */
typedef int TcProjState;
enum {
   TcProjStateUnloaded   = -1,   /**< Project is not loaded */
   TcProjStateLoading    =  0,   /**< Project is loading */
   TcProjStateUnloading  =  1,   /**< Project is unloading */
   TcProjStateLoaded     =  2    /**< Project is loaded */
};

/** Execution flags @see TcSetExeFlag, TcExeUnitStatus::exeFlags */
typedef int TcExeFlags;
enum {
   TcExeFlagsDebugFlow        = 0x1,      /**< Flow-debug-mode (global) */
   TcExeFlagsDebugRoutine     = 0x2,      /**< Routine-debug-mode (global) */
   TcExeFlagsMainFlowStepping = 0x10000   /**< Main-flow-step-mode (flow-related) */
};

/** Current status of an execution unit (dynamic) */
typedef struct TcExeUnitStatus {
   TcExecUnitState state;  /**< State */
   TcStepState     step;   /**< Step state */
   int exeFlags;           /**< Bit field for execution flags @see TcExeFlags */
   int changeCnt;          /**< Change counter */
   int nrChilds;           /**< Number of child nodes. In programs: structure-tree handle of the program with the main-flow. */
   int line;               /**< Current line. In projects: TcProjState. In programs: execution handle of the routine with the main-flow. */
   int mainFlowLine;       /**< Main-flow-line, -1 if not containing the main-flow */
} TcExeUnitStatus;

/** Kinds of code-points */
typedef int TcCodePointKind;
enum {
   TcCodePointKindBreakPoint,       /**< Break-point */
   TcCodePointKindWatchPoint,       /**< Watch-point */
   TcCodePointKindBreakPointMain    /**< Main-flow-break-point */
};

/** Kinds of mappings */
typedef int TcMapKind;
enum {
   TcMapKindVoid,          /**< Not mapped */
   TcMapKindInternal,      /**< Internal variable or routine */
   TcMapKindExternal,      /**< External variable or routine */
   TcMapKindIecVariable,   /**< System-variable (IEC) */
   TcMapKindIecAlarm,      /**< System-alarm (IEC) */
   TcMapKindIecEvent       /**< System-event (IEC) */
};

/** Description of a map target */
typedef struct TcMapTarget {
   TcMapKind kind;                        /**< The kind of the mapping */
   TcHdl exeUnit;                         /**< @deprecated Always 0 */
   TcInstancePath instancePath;           /**< Instance-path of the variable or program or block */
   TcHdl routine;                         /**< Internally mapped routine (structure-tree node) */
   char external[TcMaxExternalPathLen];   /**< String for external MAPX-mapping or hints if appropriate */
} TcMapTarget;

/** Description of a method parameter @see TcExecuteMethodExt */
typedef struct TcMethodParam {
   TcVarAccess varAccess;  /**< Variable access handle */
   TcValue value;          /**< Value */
   TcBool isValue;         /**< 0: 'varAccess' is valid, 1: 'value' is valid,  */
} TcMethodParam;


/** Kinds of editor symbols */
typedef int TcSymbolKind;
enum {
   /* Terminal symbols */
   TcSymbolKindTComment = -2,
   TcSymbolKindTError = -1,
   TcSymbolKindTEof = 0,
   TcSymbolKindTInherit = 1,
   TcSymbolKindTSemicolon = 2,
   TcSymbolKindTPrivate = 3,
   TcSymbolKindTGlobal = 4,
   TcSymbolKindTConst = 5,
   TcSymbolKindTValueParam = 6,
   TcSymbolKindTSave = 7,
   TcSymbolKindTEndSave = 8,
   TcSymbolKindTColonEqual = 9,
   TcSymbolKindTConstant = 10,
   TcSymbolKindTEndConstant = 11,
   TcSymbolKindTColon = 12,
   TcSymbolKindTVar = 13,
   TcSymbolKindTEndVar = 14,
   TcSymbolKindTType = 15,
   TcSymbolKindTEndType = 16,
   TcSymbolKindTMapTo = 17,
   TcSymbolKindTRoutine = 18,
   TcSymbolKindTParenthesesLeft = 19,
   TcSymbolKindTParenthesesRight = 20,
   TcSymbolKindTBracketLeft = 21,
   TcSymbolKindTBracketRight = 22,
   TcSymbolKindTDoublePoint = 23,
   TcSymbolKindTComma = 24,
   TcSymbolKindTArray = 25,
   TcSymbolKindTOf = 26,
   TcSymbolKindTStruct = 27,
   TcSymbolKindTEndStruct = 28,
   TcSymbolKindTCase = 29,
   TcSymbolKindTEndRoutine = 30,
   TcSymbolKindTAt = 31,
   TcSymbolKindTStart = 32,
   TcSymbolKindTPrio = 33,
   TcSymbolKindTDo = 34,
   TcSymbolKindTStop = 35,
   TcSymbolKindTIf = 36,
   TcSymbolKindTThen = 37,
   TcSymbolKindTEndIf = 38,
   TcSymbolKindTElseIf = 39,
   TcSymbolKindTElse = 40,
   TcSymbolKindTGoto = 41,
   TcSymbolKindTEndCase = 42,
   TcSymbolKindTFor = 43,
   TcSymbolKindTTo = 44,
   TcSymbolKindTEndFor = 45,
   TcSymbolKindTWhile = 46,
   TcSymbolKindTEndWhile = 47,
   TcSymbolKindTRepeat = 48,
   TcSymbolKindTUntil = 49,
   TcSymbolKindTEndRepeat = 50,
   TcSymbolKindTLabel = 51,
   TcSymbolKindTSelect = 52,
   TcSymbolKindTDeselect = 53,
   TcSymbolKindTReturn = 54,
   TcSymbolKindTWait = 55,
   TcSymbolKindTPoint = 56,
   TcSymbolKindTLess = 57,
   TcSymbolKindTGreater = 58,
   TcSymbolKindTLessEqual = 59,
   TcSymbolKindTGreaterEqual = 60,
   TcSymbolKindTEqual = 61,
   TcSymbolKindTNotEqual = 62,
   TcSymbolKindTMinus = 63,
   TcSymbolKindTPlus = 64,
   TcSymbolKindTOr = 65,
   TcSymbolKindTXor = 66,
   TcSymbolKindTMul = 67,
   TcSymbolKindTDiv = 68,
   TcSymbolKindTMod = 69,
   TcSymbolKindTAnd = 70,
   TcSymbolKindTNot = 71,
   TcSymbolKindTIdent = 72,
   TcSymbolKindTInteger = 73,
   TcSymbolKindTReal = 74,
   TcSymbolKindTString = 75,
   TcSymbolKindTLock = 76,
   TcSymbolKindTUnlock = 77,
   TcSymbolKindTNewLine = 78,
   TcSymbolKindTUser = 79,
   TcSymbolKindTLoop = 80,
   TcSymbolKindTEndLoop = 81,
   TcSymbolKindTCall = 82,
   TcSymbolKindTOptional = 83,
   TcSymbolKindTProject = 84,
   TcSymbolKindTCurlyBracketLeft = 85,
   TcSymbolKindTCurlyBracketRight = 86,
   TcSymbolKindTAttrSeperator = 87,
   TcSymbolKindTName = 88,
   TcSymbolKindTReadonly = 89,
   TcSymbolKindTRun = 90,
   TcSymbolKindTKill = 91,
   TcSymbolKindTAbstract = 92,
   TcSymbolKindTDeactivate = 93,
   TcSymbolKindTBegin = 94,
   TcSymbolKindTEnd = 95,
   TcSymbolKindTIdent2 = 96,   
   TcSymbolKindTExport = 97,
   TcSymbolKindTBy = 98,
   TcSymbolKindTNoInit = 99,


   TcSymbolKindNTFirstNonTerm = 100, /* Begin of nonterminal symbols */

   /* Nonterminal symbols */
   TcSymbolKindNTConstPart = 101,
   TcSymbolKindNTVarPart = 102,
   TcSymbolKindNTTypePart = 103,
   TcSymbolKindNTVarDeclaration = 104,
   TcSymbolKindNTTypeDefinition = 105,
   TcSymbolKindNTConstDeclaration = 106,
   TcSymbolKindNTStatementPart = 107,
   TcSymbolKindNTParameter = 108,
   TcSymbolKindNTEnumeration = 109,
   TcSymbolKindNTEnumerationType = 110,
   TcSymbolKindNTStructType = 111,
   TcSymbolKindNTArrayType = 112,
   TcSymbolKindNTUserPart = 113,
   TcSymbolKindNTUserVarDeclaration = 114,
   TcSymbolKindNTFunctionBlock = 120,
   TcSymbolKindNTAtBlock = 121,
   TcSymbolKindNTRoutineHead = 122,
   TcSymbolKindNTAtRoutineHead = 123,
   TcSymbolKindNTAttribBlock = 124,
   TcSymbolKindNTResultType = 125,
   TcSymbolKindNTEmptyStatement = 130,
   TcSymbolKindNTAssignStatement = 131,
   TcSymbolKindNTCallStatement = 132,
   TcSymbolKindNTWaitStatement = 133,
   TcSymbolKindNTIfStatement = 134,
   TcSymbolKindNTIfGotoStatement = 135,
   TcSymbolKindNTCaseStatement = 136,
   TcSymbolKindNTForStatement = 137,
   TcSymbolKindNTWhileStatement = 138,
   TcSymbolKindNTRepeatStatement = 139,
   TcSymbolKindNTReturnStatement = 140,
   TcSymbolKindNTLabelStatement = 141,
   TcSymbolKindNTGotoStatement = 142,
   TcSymbolKindNTSelectStatement = 144,
   TcSymbolKindNTDeselectStatement = 145,
   TcSymbolKindNTStopStatement = 146,
   TcSymbolKindNTLockStatement = 147,
   TcSymbolKindNTUnlockStatement = 148,
   TcSymbolKindNTLoopStatement = 149,
   TcSymbolKindNTRunStatement = 150,
   TcSymbolKindNTKillStatement = 151,
   TcSymbolKindNTCaseSel = 158,
   TcSymbolKindNTRoutine = 159,
   TcSymbolKindNTExpression = 160,
   TcSymbolKindNTActParamList = 161,
   TcSymbolKindNTName = 162,
   TcSymbolKindNTFileName = 163,
   TcSymbolKindNTRefType = 164,

   TcSymbolKindNTLastNonTerm = 299, /* End of nonterminal symbols */


   /* Terminal symbols (continued) */
   TcSymbolKindTResult = 300,
   TcSymbolKindTParam = 301,
   TcSymbolKindTInterface = 302,
   TcSymbolKindTInternal = 303,
   TcSymbolKindT_Export = 304,   
   TcSymbolKindTNext = 305,
   TcSymbolKindTBreak = 306,
   TcSymbolKindTImplement = 307,
   TcSymbolKindTExtend = 308,
   TcSymbolKindTDeprecated = 309,
   TcSymbolKindTNoSave = 310
};


/** Information about an editor */
typedef struct TcEditorInfo {
   int nrOfLines;          /**< Number of lines */
   int nrOfChars;          /**< Number of characters */
   int cursorLine;         /**< Cursor-line */
   int cursorCol;          /**< Cursor-column */
   int nrOfSyntaxErrors;   /**< Number of syntax errors */
} TcEditorInfo;


typedef void * TcSymbolHandle; /**< Symbol handle */

/** Editor symbol */
typedef struct TcSymbol {
  TcSymbolHandle handle;      /**< Handle of the symbol */
  TcSymbolHandle upperHandle; /**< Handle of the superordinate symbol */
  TcSymbolKind token;         /**< The kind of the symbol */
  char *text;                 /**< Symbol-text */
  int len;                    /**< Length of the symbol-text (characters) */
} TcSymbol;

/** Editor position, lines and columns start with 0 */
typedef struct TcPos {
  int line; /**< Line */
  int col;  /**< Column */
} TcPos;


#ifdef  __cplusplus
}
#endif

#endif

