/**
 * SEPRO ROBOTIQUE SAS © 2020 - 2021
 * Ce contenu est la propriété pleine, entière et exclusive de SEPRO GROUP.
 * 
 * INFORMATIONS CONFIDENTIELLES.
 * Ce contenu ne peut être communiqué ou divulgué à des tiers que sous réserve
 * de la signature préalable d’un accord de confidentialité avec SEPRO GROUP
 * et avec l’autorisation préalable et écrite de SEPRO GROUP.
 * 
 * This content is the full, sole and exclusive property of SEPRO GROUP.
 * 
 * CONFIDENTIAL INFORMATION.
 * This content may only be communicated or disclosed to third parties after
 * signing a confidentiality agreement with SEPRO GROUP and with the
 * written permission of SEPRO GROUP
 * 
 * @file DisplayChecker.cpp
 * @author nkhaldi (nkhaldi@sepro-group.com)
 * @version 0.1
 * @date 2021-05-07
 */

#include <iostream>
#include "DisplayChecker.hpp"

#define RED_COLOR		"\033[0;31m"
#define GREEN_COLOR		"\033[1;32m"
#define YELLOW_COLOR	"\033[1;33m"
#define BLUE_COLOR		"\033[1;34m"
#define PURPLE_COLOR	"\033[0;35m"
#define CYAN_COLOR		"\033[0;36m"
#define END_COLOR		"\033[1;0m"

#include <string.h>

/**
 * @brief display the return code
 * 
 * @param functionName 
 * @param retCode 
 */
void DisplayChecker::DisplayBPApiState(const char *functionName, const BPApiState &retCode)
{
	switch (retCode)
	{
	case BPApiStateOk:
		std::cout << std::string(functionName) << " retCode : " <<  "BPApiStateOk" << std::endl;
		break;
	case BPApiStateStringChopped:
		std::cout << std::string(functionName) << " retCode : " <<  "BPApiStateStringChopped" << std::endl;
		break;
	case BPApiStateInternalError:
		std::cout << std::string(functionName) << " retCode : " <<  "BPApiStateInternalError" << std::endl;
		break;
	case BPApiStateNotOk:
		std::cout << std::string(functionName) << " retCode : " <<  "BPApiStateNotOk" << std::endl;
		break;
	case BPApiStateParamError:
		std::cout << std::string(functionName) << " retCode : " <<  "BPApiStateParamError" << std::endl;
		break;
	case BPApiStateComNotRunning:
		std::cout << std::string(functionName) << " retCode : " <<  "BPApiStateComNotRunning" << std::endl;
		break;
	case BPApiStateFuncNotFound:
		std::cout << std::string(functionName) << " retCode : " <<  "BPApiStateFuncNotFound" << std::endl;
		break;
	case BPApiStateNotImplementedYet:
		std::cout << std::string(functionName) << " retCode : " <<  "BPApiStateNotImplementedYet" << std::endl;
		break;
	case BPApiStateDiskSpaceFull:
		std::cout << std::string(functionName) << " retCode : " <<  "BPApiStateDiskSpaceFull" << std::endl;
		break;
	case BPApiStateInitError:
		std::cout << std::string(functionName) << " retCode : " <<  "BPApiStateInitError" << std::endl;
		break;
	case BPApiStateInvalidHandle:
		std::cout << std::string(functionName) << " retCode : " <<  "BPApiStateInvalidHandle" << std::endl;
		break;
	case BPApiStateOutOfMemory:
		std::cout << std::string(functionName) << " retCode : " <<  "BPApiStateOutOfMemory" << std::endl;
		break;
	case BPApiStateRequestTimeout:
		std::cout << std::string(functionName) << " retCode : " <<  "BPApiStateRequestTimeout" << std::endl;
		break;
	case BPApiStateInvalidMultiByteChar:
		std::cout << std::string(functionName) << " retCode : " <<  "BPApiStateInvalidMultiByteChar" << std::endl;
		break;
	case BPApiStateStaRepAlreadyStarted:
		std::cout << std::string(functionName) << " retCode : " <<  "BPApiStateStaRepAlreadyStarted" << std::endl;
		break;
	case BPApiStateStaRepInvalidDestPath:
		std::cout << std::string(functionName) << " retCode : " <<  "BPApiStateStaRepInvalidDestPath" << std::endl;
		break;
	case BPApiStateStaRepNotInit:
		std::cout << std::string(functionName) << " retCode : " <<  "BPApiStateStaRepNotInit" << std::endl;
		break;
	case BPApiStateStaRepMissing:
		std::cout << std::string(functionName) << " retCode : " <<  "BPApiStateStaRepMissing" << std::endl;
		break;
	case BPApiStateRepSysFunctionFaild:
		std::cout << std::string(functionName) << " retCode : " <<  "BPApiStateRepSysFunctionFaild" << std::endl;
		break;
	case BPApiStateRepSysInvalidWideChar:
		std::cout << std::string(functionName) << " retCode : " <<  "BPApiStateRepSysInvalidWideChar" << std::endl;
		break;
	case BPApiStateRepSysInvalidMultiByteChar:
		std::cout << std::string(functionName) << " retCode : " <<  "BPApiStateRepSysInvalidMultiByteChar" << std::endl;
		break;
	case BPApiStateRepSysInvalidHandle:
		std::cout << std::string(functionName) << " retCode : " <<  "BPApiStateRepSysInvalidHandle" << std::endl;
		break;
	case BPApiStateRepSysUnknownParamKind:
		std::cout << std::string(functionName) << " retCode : " <<  "BPApiStateRepSysUnknownParamKind" << std::endl;
		break;
	case BPApiStateRepSysBufferTooSmall:
		std::cout << std::string(functionName) << " retCode : " <<  "BPApiStateRepSysBufferTooSmall" << std::endl;
		break;
	case BPApiStateRepSysNotImplemented:
		std::cout << std::string(functionName) << " retCode : " <<  "BPApiStateRepSysNotImplemented" << std::endl;
		break;
	case BPApiStateRepSysIllegalArguments:
		std::cout << std::string(functionName) << " retCode : " <<  "BPApiStateRepSysIllegalArguments" << std::endl;
		break;
	case BPApiStateRepSysVarNotFound:
		std::cout << std::string(functionName) << " retCode : " <<  "BPApiStateRepSysVarNotFound" << std::endl;
		break;
	case BPApiStateRepSysInvalidVarType:
		std::cout << std::string(functionName) << " retCode : " <<  "BPApiStateRepSysInvalidVarType" << std::endl;
		break;
	case BPApiStateRepSysProtVarAlreadySet:
		std::cout << std::string(functionName) << " retCode : " <<  "BPApiStateRepSysProtVarAlreadySet" << std::endl;
		break;
	case BPApiStateRepSysProvNotSupported:
		std::cout << std::string(functionName) << " retCode : " <<  "BPApiStateRepSysProvNotSupported" << std::endl;
		break;
	case BPApiStateRepSysInvalidParamType:
		std::cout << std::string(functionName) << " retCode : " <<  "BPApiStateRepSysInvalidParamType" << std::endl;
		break;
	case BPApiStateDeviceCommandTemporarilyUnavailable:
		std::cout << std::string(functionName) << " retCode : " <<  "BPApiStateDeviceCommandTemporarilyUnavailable" << std::endl;
		break;
	case BPApiStateDeviceCommandPermanentlyUnavailable:
		std::cout << std::string(functionName) << " retCode : " <<  "BPApiStateDeviceCommandPermanentlyUnavailable" << std::endl;
		break;
	case BPApiStateVarNotFound:
		std::cout << std::string(functionName) << " retCode : " <<  "BPApiStateVarNotFound" << std::endl;
		break;
	case BPApiStateVarNoChildren:
		std::cout << std::string(functionName) << " retCode : " <<  "BPApiStateVarNoChildren" << std::endl;
		break;
	case BPApiStateNoMoreNodes:
		std::cout << std::string(functionName) << " retCode : " <<  "BPApiStateNoMoreNodes" << std::endl;
		break;
	case BPApiStateNoAccess:
		std::cout << std::string(functionName) << " retCode : " <<  "BPApiStateNoAccess" << std::endl;
		break;
	case BPApiStatePropNotFound:
		std::cout << std::string(functionName) << " retCode : " <<  "BPApiStatePropNotFound" << std::endl;
		break;
	case BPApiStateRecipes_PartsFailed:
		std::cout << std::string(functionName) << " retCode : " <<  "BPApiStateRecipes_PartsFailed" << std::endl;
		break;
	case BPApiStateRecipes_NothingToDo:
		std::cout << std::string(functionName) << " retCode : " <<  "BPApiStateRecipes_NothingToDo" << std::endl;
		break;
	case BPApiStateRecipes_Changed:
		std::cout << std::string(functionName) << " retCode : " <<  "BPApiStateRecipes_Changed" << std::endl;
		break;
	case BPApiStateRecipes_Unchanged:
		std::cout << std::string(functionName) << " retCode : " <<  "BPApiStateRecipes_Unchanged" << std::endl;
		break;
	case BPApiStateRecipes_StartSucceeded:
		std::cout << std::string(functionName) << " retCode : " <<  "BPApiStateRecipes_StartSucceeded" << std::endl;
		break;
	case BPApiStateRecipes_RecipeNotFound:
		std::cout << std::string(functionName) << " retCode : " <<  "BPApiStateRecipes_RecipeNotFound" << std::endl;
		break;
	case BPApiStateRecipes_InvalidPath:
		std::cout << std::string(functionName) << " retCode : " <<  "BPApiStateRecipes_InvalidPath" << std::endl;
		break;
	case BPApiStateRecipes_InvalidName:
		std::cout << std::string(functionName) << " retCode : " <<  "BPApiStateRecipes_InvalidName" << std::endl;
		break;
	case BPApiStateRecipes_RecipeNoAccess:
		std::cout << std::string(functionName) << " retCode : " <<  "BPApiStateRecipes_RecipeNoAccess" << std::endl;
		break;
	case BPApiStateRecipes_CRC_Error:
		std::cout << std::string(functionName) << " retCode : " <<  "BPApiStateRecipes_CRC_Error" << std::endl;
		break;
	case BPApiStateRecipes_DataBase_Error:
		std::cout << std::string(functionName) << " retCode : " <<  "BPApiStateRecipes_DataBase_Error" << std::endl;
		break;
	case BPApiProviderFileNotFound:
		std::cout << std::string(functionName) << " retCode : " <<  "BPApiProviderFileNotFound" << std::endl;
		break;
	case BPApiProviderInvalidFile:
		std::cout << std::string(functionName) << " retCode : " <<  "BPApiProviderInvalidFile" << std::endl;
		break;
	case BPApiProviderLoadError:
		std::cout << std::string(functionName) << " retCode : " <<  "BPApiProviderLoadError" << std::endl;
		break;
	case BPApiProviderCRCMismatch:
		std::cout << std::string(functionName) << " retCode : " <<  "BPApiProviderCRCMismatch" << std::endl;
		break;

	default:
		break;
	}
}