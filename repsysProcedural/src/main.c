/*
 * =====================================================================================
 *
 *       Filename:  main.c (POC !!!)
 *
 *    Description:  setup
 *
 *        Version:  1.0
 *        Created:  04/29/2021 01:50:55 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  nkhaldi, 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h> // strdup
#include "BPApiRepSys.h"

#define MSG_LEN 80

#define GREEN_COLOR		"\033[1;32m"
#define YELLOW_COLOR	"\033[1;33m"
#define BLUE_COLOR		"\033[1;34m"
#define END_COLOR		"\033[1;0m"

void printState(BPApiState retCode)
{
	switch (retCode)
	{
	case BPApiStateOk:
		printf("BPApiStateOk\n");
		break;
	case BPApiStateStringChopped:
		printf("BPApiStateStringChopped\n");
		break;
	case BPApiStateInternalError:
		printf("BPApiStateInternalError\n");
		break;
	case BPApiStateNotOk:
		printf("BPApiStateNotOk\n");
		break;
	case BPApiStateParamError:
		printf("BPApiStateParamError\n");
		break;
	case BPApiStateComNotRunning:
		printf("BPApiStateComNotRunning\n");
		break;
	case BPApiStateFuncNotFound:
		printf("BPApiStateFuncNotFound\n");
		break;
	case BPApiStateNotImplementedYet:
		printf("BPApiStateNotImplementedYet\n");
		break;
	case BPApiStateDiskSpaceFull:
		printf("BPApiStateDiskSpaceFull\n");
		break;
	case BPApiStateInitError:
		printf("BPApiStateInitError\n");
		break;
	case BPApiStateInvalidHandle:
		printf("BPApiStateInvalidHandle\n");
		break;
	case BPApiStateOutOfMemory:
		printf("BPApiStateOutOfMemory\n");
		break;
	case BPApiStateRequestTimeout:
		printf("BPApiStateRequestTimeout\n");
		break;
	case BPApiStateInvalidMultiByteChar:
		printf("BPApiStateInvalidMultiByteChar\n");
		break;
	case BPApiStateStaRepAlreadyStarted:
		printf("BPApiStateStaRepAlreadyStarted\n");
		break;
	case BPApiStateStaRepInvalidDestPath:
		printf("BPApiStateStaRepInvalidDestPath\n");
		break;
	case BPApiStateStaRepNotInit:
		printf("BPApiStateStaRepNotInit\n");
		break;
	case BPApiStateStaRepMissing:
		printf("BPApiStateStaRepMissing\n");
		break;
	case BPApiStateRepSysFunctionFaild:
		printf("BPApiStateRepSysFunctionFaild\n");
		break;
	case BPApiStateRepSysInvalidWideChar:
		printf("BPApiStateRepSysInvalidWideChar\n");
		break;
	case BPApiStateRepSysInvalidMultiByteChar:
		printf("BPApiStateRepSysInvalidMultiByteChar\n");
		break;
	case BPApiStateRepSysInvalidHandle:
		printf("BPApiStateRepSysInvalidHandle\n");
		break;
	case BPApiStateRepSysUnknownParamKind:
		printf("BPApiStateRepSysUnknownParamKind\n");
		break;
	case BPApiStateRepSysBufferTooSmall:
		printf("BPApiStateRepSysBufferTooSmall\n");
		break;
	case BPApiStateRepSysNotImplemented:
		printf("BPApiStateRepSysNotImplemented\n");
		break;
	case BPApiStateRepSysIllegalArguments:
		printf("BPApiStateRepSysIllegalArguments\n");
		break;
	case BPApiStateRepSysVarNotFound:
		printf("BPApiStateRepSysVarNotFound\n");
		break;
	case BPApiStateRepSysInvalidVarType:
		printf("BPApiStateRepSysInvalidVarType\n");
		break;
	case BPApiStateRepSysProtVarAlreadySet:
		printf("BPApiStateRepSysProtVarAlreadySet\n");
		break;
	case BPApiStateRepSysProvNotSupported:
		printf("BPApiStateRepSysProvNotSupported\n");
		break;
	case BPApiStateRepSysInvalidParamType:
		printf("BPApiStateRepSysInvalidParamType\n");
		break;
	case BPApiStateDeviceCommandTemporarilyUnavailable:
		printf("BPApiStateDeviceCommandTemporarilyUnavailable\n");
		break;
	case BPApiStateDeviceCommandPermanentlyUnavailable:
		printf("BPApiStateDeviceCommandPermanentlyUnavailable\n");
		break;
	case BPApiStateVarNotFound:
		printf("BPApiStateVarNotFound\n");
		break;
	case BPApiStateVarNoChildren:
		printf("BPApiStateVarNoChildren\n");
		break;
	case BPApiStateNoMoreNodes:
		printf("BPApiStateNoMoreNodes\n");
		break;
	case BPApiStateNoAccess:
		printf("BPApiStateNoAccess\n");
		break;
	case BPApiStatePropNotFound:
		printf("BPApiStatePropNotFound\n");
		break;
	case BPApiStateRecipes_PartsFailed:
		printf("BPApiStateRecipes_PartsFailed\n");
		break;
	case BPApiStateRecipes_NothingToDo:
		printf("BPApiStateRecipes_NothingToDo\n");
		break;
	case BPApiStateRecipes_Changed:
		printf("BPApiStateRecipes_Changed\n");
		break;
	case BPApiStateRecipes_Unchanged:
		printf("BPApiStateRecipes_Unchanged\n");
		break;
	case BPApiStateRecipes_StartSucceeded:
		printf("BPApiStateRecipes_StartSucceeded\n");
		break;
	case BPApiStateRecipes_RecipeNotFound:
		printf("BPApiStateRecipes_RecipeNotFound\n");
		break;
	case BPApiStateRecipes_InvalidPath:
		printf("BPApiStateRecipes_InvalidPath\n");
		break;
	case BPApiStateRecipes_InvalidName:
		printf("BPApiStateRecipes_InvalidName\n");
		break;
	case BPApiStateRecipes_RecipeNoAccess:
		printf("BPApiStateRecipes_RecipeNoAccess\n");
		break;
	case BPApiStateRecipes_CRC_Error:
		printf("BPApiStateRecipes_CRC_Error\n");
		break;
	case BPApiStateRecipes_DataBase_Error:
		printf("BPApiStateRecipes_DataBase_Error\n");
		break;
	case BPApiProviderFileNotFound:
		printf("BPApiProviderFileNotFound\n");
		break;
	case BPApiProviderInvalidFile:
		printf("BPApiProviderInvalidFile\n");
		break;
	case BPApiProviderLoadError:
		printf("BPApiProviderLoadError\n");
		break;
	case BPApiProviderCRCMismatch:
		printf("BPApiProviderCRCMismatch\n");
		break;

	default:
		break;
	}
}

void setMsgA_hardWritten(BPApiRepSysMsgClass msgClassId, uint32_t compNr, uint32_t instNr, uint32_t msgNr)
{
	/*
	rappeler la methode ci dessous consiste a aller au message suivant !
	la methode BPApiRepSysSetMsgA va formatter le message comme un printf attention cependant :
	le formattage ignore tout caractere autre qu un specifieur : "%d" "%s"
	vous pouvez mettre jusqu'a 8 element a afficher
	retCode = BPApiRepSysSetMsgA(msgClassId, compNr, instNr, msgNr, "%s %d %s %d %d %d %d %s", "TEST_00_hardWritten", 32, "toto", 34, 35, 36, 37 , "titi");
	si le message n affiche qu une seule variable (1 seul specifieur) alors le message affiche sera suivi par "...," et cela autant de fois que de places disponibles (jusqu a 7 max)
	*/

	BPApiState retCode;

	printf("=====> SetMsgA retCode : ");

	retCode = BPApiRepSysSetMsgA(msgClassId, compNr, instNr, msgNr, "%s %s", "TEST_00", "hardWritten");
	printState(retCode);
}

// blocage sur utilisation va_list (bonus)
// ne pas utiliser pour l instant !!!
/*
void setListMsgA(BPApiRepSysMsgClass msgClassId, uint32_t compNr, uint32_t instNr, uint32_t msgNr, char *msg, ...)
{
	BPApiState retCode = BPApiStateOk;

	va_list lst;
	va_start(lst, msg);

	printf("=====> Set[List]MsgA retCode : ");
	retCode = BPApiRepSysSetMsgListA(msgClassId, compNr, instNr, msgNr, "%s", lst);
	va_end(lst);
	printState(retCode);
	printf("\n msg value after BPApiRepSysSetMsg[List]A [%s]\n", msg);
}
*/

// j ai exporte ici des methodes deja utilisees et fonctionnelles dans le main ... donc je ne re-teste pas cette methode
void logPrinter(BPApiRepSysMsgClass msgClassId, uint32_t compNr, uint32_t instNr, uint32_t msgNr)
{
	BPApiState retCode;

	// [ rule 1 ]
	// you can print at most 8 values (the additional ones will be ignored)
	// for specifying the values you put a specifier "%s, %d etc" added characters along the specifiers will be ignored
	retCode = BPApiRepSysSetMsgA(msgClassId, compNr, instNr, msgNr, "%s %s %d %c %s %d %d %x", "toto", "titi", 007, 'Z', "tata", 006, 005, 255);
	printState(retCode);

	// [ rule 2 ]
	/*
	if compNr, instNr, msgNr, msgClassId ... datas, relates to an existing log message,
	then it is enough to put the specifier %s and not to give him the corresponding string,
	otherwise BE AWARE that the only thing to be printed is the existing message corresponding to the datas (compNr, instNr ...) given
	it is the api which will obtain the corresponding message.
	*/
	
	// below example of an existing log message  "------------------------- System ready ---------------------------"
	msgClassId = BPApiRepSysMsgClass13;
	compNr = 50; 	// already exist
	instNr = 0; 	// already exist
	msgNr = 3450; 	// alreadt exist

	// bad way
	retCode = BPApiRepSysSetMsgA(msgClassId, compNr, instNr, msgNr, "%s %s", "hello", "sepro"); // "hello" and "sepro" will not be printed
	printState(retCode);

	// write way
	retCode = BPApiRepSysSetMsgA(msgClassId, compNr, instNr, msgNr, "%s"); // the arguments corresponds to an existing message, so there is no need to give the corresponding string
	printState(retCode);

	// [ rule 3 ]
	// as long as the message is hardwritten, you can put it as well through a char[] or a char*
	char XYZ_string[] = "XYZ";
	char *ABC_string = strdup("ABC");

	retCode = BPApiRepSysSetMsgA(msgClassId, compNr, instNr, msgNr, "%s %s", XYZ_string, ABC_string);
	printState(retCode);
	free(ABC_string);

	// [ rule 4 ]
	// but ! ... if you attempt to retrieve an existing log message, you will not be able (I didn't find how ...) to print it like below
	// TODO
}

int main()
{
	BPApiState retCode;

	BPApiRepSysMsgClass oldClassId = BPApiRepSysMsgClassInfo;
	BPApiRepSysMsgClass newClassId = BPApiRepSysMsgClass13;
	BPApiRepSysMsgHdl oldMsgHdl;
	BPApiRepSysMsgHdl newMsgHdl;
	uint32_t count = 0;

	// compNr, instNr, msgNr ...
	uint32_t compNr;
	uint32_t instNr;
	uint32_t msgNr;
	BPApiTime ts;
	uint32_t paramCount;
	BPApiRepSysMsgState msgState;
	uint32_t protocol_var;

	// [ GET MSG COUNT FROM CLASS_ID ]
	retCode = BPApiRepSysGetHistoryMsgCount(newClassId, &count);
	printf("%s \n [START] new class msg total [%u] %s\n", BLUE_COLOR, count, END_COLOR);

	// [ GET MSG HDL FROM CLASS_ID ]
	// STEP_1 : on recupere le handler correspondant au 1er msg de classe
	retCode = BPApiRepSysGetFirstHistoryMsg(oldClassId, &oldMsgHdl); 
	printState(retCode);

	char *buffer = (char *)malloc(MSG_LEN * sizeof(char));
	bzero(buffer, MSG_LEN);

	// [ GET MSG DATAS FROM HDL ]
	// on recupere toutes les donnees d un msg en fonction de son handler (oldMsgHdl)
	retCode = BPApiRepSysGetMsgDataValues2(  // on recupere les in      fos : classId, compNr, instNr, msgNr ... correspondant au handler
			oldMsgHdl, // [in]
			&oldClassId, // ex. 256 <=> 0x100ul donc class9
			&compNr, // ex. 50
			&instNr, // ex. 10223622 
			&msgNr, // ex. 9999 
			&ts, 
			&paramCount, // ex. 1 
			&msgState, // ex. BPApiRepSysMsgStateToQuit
			&protocol_var);

	printState(retCode);

	// affichage pour verifier les infos
	printf("\n OldClassId [%x]\n\
	compNr [%u]\n\
	instNr [%u]\n\
	msgNr [%u]\n\
	paramCount [%u]\n\
	msgState [%u]\n\
	protocol_var[%x]\n\n",
	oldClassId, 
	compNr,
	instNr,
	msgNr,
	paramCount,
	msgState,
	protocol_var);
	
	// STEP_2 : on s'assure de recuperer le msg correspondant au handler
	// [ GET & FORMAT ASCII MSG FROM MSG HDL ]

	// paramValueMemory attempt
	// uint32_t bufLen = 0;
	// retCode = BPApiRepSysGetMsgParamValueMemory(newMsgHdl, paramCount, buffer, &bufLen);
	// printState(retCode);
	
	retCode = BPApiRepSysFormatMsgA(oldMsgHdl, buffer, MSG_LEN); // oldMsgHdl [in] ; buffer [out]
	printState(retCode);
	printf("\n%sFIRST HIST MSG for given handler [%s] %s\n\n", YELLOW_COLOR, buffer, END_COLOR);

	retCode = BPApiRepSysQuitMsg(newClassId, compNr, instNr, msgNr);
	// printf("resetMsg retCode : ");
	// printState(retCode);

	// STEP_3 : on change la classe du message et on recupere un nouveau handler
	// [ BUILD NEW MSG HANDLER FROM DATAS : newClassId, compNr, instNr, msgNr ]
	retCode = BPApiRepSysGetMsg(newClassId, compNr, instNr, msgNr, &newMsgHdl);
	printf("=====> BPApiRepSysGetMsg retCode : ");
	printState(retCode);

	// [ GET MSG DATAS FROM HANDLER ]
	retCode = BPApiRepSysGetMsgDataValues2(
			newMsgHdl, // [in]
			&newClassId, // ex. 256 <=> 0x100ul donc class9
			&compNr, // ex. 50
			&instNr, // ex. 10223622 
			&msgNr, // ex. 9999 
			&ts, 
			&paramCount, // ex. 1 
			&msgState, // ex. BPApiRepSysMsgStateToQuit
			&protocol_var);
	printf("=====> GetMsgDataValues retCode : ");
	printState(retCode);

	// [ PRINT MSG DATAS ]
	printf("\n newClassId [%x]\n\
	compNr [%u]\n\
	instNr [%u]\n\
	msgNr [%u]\n\
	paramCount [%u]\n\
	msgState [%u]\n\
	protocol_var[%x]\n",
	newClassId, 
	compNr,
	instNr,
	msgNr,
	paramCount,
	msgState,
	protocol_var);

	// [ SET MSG CONTENT FROM HANDLER ]
	bzero(buffer, MSG_LEN);
	retCode = BPApiRepSysFormatMsgA(oldMsgHdl, buffer, MSG_LEN); // oldMsgHdl [in] ; buffer [out]
	printState(retCode);
	printf("%sBUFFER msg from handler [%s]%s\n\n", GREEN_COLOR, buffer, END_COLOR);

	// [ PRINT (LOG) MSG CONTENT HANDLER FROM DATAS : newClassId, compNr, instNr, msgNr ]
	retCode = BPApiRepSysSetMsgA(newClassId, compNr, instNr, msgNr, "%s", buffer); // recupere et affiche le msg correspondant aux datas compNr, instNr, msgNr et classIdassId
	printf("=====> BPApiRepSysSetMsgA retCode : ");
	printState(retCode);

	// [ GET MSG COUNT FROM CLASS_ID ]
	retCode = BPApiRepSysGetHistoryMsgCount(newClassId, &count);
	printState(retCode);

	// [ PRINT MSG COUNT ]
	printf("%s \n [END] new class msg total [%u] %s\n", BLUE_COLOR, count, END_COLOR);

	// [ GET HANDLER FROM CLASS_ID ]
	BPApiRepSysMsgHdl lastMsgHdl;
	retCode = BPApiRepSysGetLastMsg(newClassId, &lastMsgHdl);
	printState(retCode);

	// [ SET MSG CONTENT FROM HANDLER ]
	bzero(buffer, MSG_LEN);
	retCode = BPApiRepSysFormatMsgA(lastMsgHdl, buffer, MSG_LEN); // oldMsgHdl [in] ; buffer [out]
	printState(retCode);

	// [ PRINT MSG CONTENT ]
	printf("\n%sLAST HIST MSG for given handler [%s] %s\n\n", YELLOW_COLOR, buffer, END_COLOR);

	return 0;
}