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
 * @file main.cpp
 * @author nkhaldi (nkhaldi@sepro-group.com)
 * @version 0.1
 * @date 2021-05-07
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h> // strdup
#include "BPApiRepSys.h"

#include "DisplayChecker.hpp"
#include "Message.hpp"
#include "MessageProcessor.hpp"

#include <csignal>

// defines
#define MSG_LEN 90
#define TIME_INTERVAL 100

// coloring for better visualization of messages and debugging messages
#define RED_COLOR		"\033[0;31m"
#define GREEN_COLOR		"\033[1;32m"
#define YELLOW_COLOR	"\033[1;33m"
#define BLUE_COLOR		"\033[1;34m"
#define PURPLE_COLOR	"\033[0;35m"
#define CYAN_COLOR		"\033[0;36m"
#define END_COLOR		"\033[1;0m"

namespace{
  volatile std::sig_atomic_t stop = 0;
}

#define CLASS_ID_RANGE				\
	(									\
		BPApiRepSysMsgClassErrorFatal |	\
  		BPApiRepSysMsgClassError |		\
		BPApiRepSysMsgClassErrorMinor |	\
		BPApiRepSysMsgClassWarning |	\
		BPApiRepSysMsgClassInfo |		\
		BPApiRepSysMsgClassErrorApp |	\
		BPApiRepSysMsgClass7 |			\
		BPApiRepSysMsgClass8 |			\
		BPApiRepSysMsgClass9 |			\
		BPApiRepSysMsgClass10 |			\
		BPApiRepSysMsgClass11 |			\
		BPApiRepSysMsgClass12			\
	)

/**
 * @brief FOR TESTING
 * generate and send fake messages to repsys
 * allows testing the retrieving of this messages by the reporter message
 * 
 * @param p_msgClassId 
 * @param p_compNr 
 * @param p_instNr 
 * @param p_msgNr 
 */
void	logNewMsg(BPApiRepSysMsgClass p_msgClassId, uint32_t p_compNr, uint32_t p_instNr, uint32_t p_msgNr){

	// on affiche dans les logs un message ayant les memes caracterisques que les 5 premiers arguments
	// faire une methode comme le logMsgNew qui log un custom message comme ci dessous
	int id = 0;
	while(1)
	{
		// recupere et affiche le msg correspondant aux datas compNr, instNr, msgNr et classIdassId
		id++;
		BPApiRepSysSetMsgA(p_msgClassId, id, id, id, "%s%d", "TEST", id);
		
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}

/**
 * @brief 
 * retrieve ALL SAFETY MSG (compNR = 100) and forward them according rules
 * Change classID according rules set in MessageProcessor::messageModifier
 * Get the Next Handle object and print it
 * functional test (it works well) for loop on all the messages for a given class
 * this method correspond to the following repsys rest api command : 
 * http://{controllerIPAddress}/api/v3/report-system/messages?history=false&formatMsg=true&paramValues=false&tsFormat=ra
 * 
 */
void	displayAllMsgForGivenClass()
{
	std::cout << GREEN_COLOR << "Retrieving existing msgs from class (decimal) 1 to 12 (hexa : 1 to 800)" << END_COLOR << std::endl;

	BPApiRepSysMsgHdl msgHdl;
	std::string msgContent;
	BPApiRepSysMsgClass classId = CLASS_ID_RANGE;

	if (BPApiRepSysGetFirstMsg(classId, &msgHdl) == BPApiStateOk)
	{
		Message firstMsg(msgHdl);

		if (firstMsg.getCompNr() == 100)
		{
			msgContent = Message::getMsgContent(msgHdl, MSG_LEN);
			std::cout << YELLOW_COLOR << "get content from msgHdl : " << msgContent.c_str() << END_COLOR << std::endl;

			// std::cout << "\nbefore changing classID" << std::endl;
			// std::cout << RED_COLOR << firstMsg << END_COLOR << std::endl;

			// MessageProcessor::messageModifier(&firstMsg, MSG_LEN);

			// std::cout << "\nafter changing classID" << std::endl;
			// std::cout << GREEN_COLOR << firstMsg << END_COLOR << std::endl;

		}

		while (BPApiRepSysGetNextMsg(classId, &msgHdl) == BPApiStateOk)
		{
			Message nextMsg(msgHdl);

			if (nextMsg.getCompNr() == 100)
			{
				std::cout << "\n**********************************************" << std::endl;

				std::cout << std::endl;
				msgContent = Message::getMsgContent(msgHdl, MSG_LEN);
				std::cout << YELLOW_COLOR << msgContent.c_str() << END_COLOR << std::endl;

				// std::cout << "\nbefore changing class" << std::endl;
				// std::cout << RED_COLOR << nextMsg << END_COLOR << std::endl;

				// MessageProcessor::messageModifier(&nextMsg, MSG_LEN);

				// std::cout << "\nafter changing classID" << std::endl;
				// std::cout << GREEN_COLOR << nextMsg << END_COLOR << std::endl << std::endl;
			}
		}
	}
}

int main(){

	BPApiState retCode(void);

	// message key = compNr/msgNr
	// if 2 messages gets the same msg key, then they are differenciated by their instNr
	// if 2 messages gets the same msg key and the same instNr, then, only one occurrence is concidered 

	// displayAllMsgForGivenClass(); //OK

	// new thread with method logNewMsg attached to it (this method is set at line 66)
    // std::thread th1(logNewMsg, msgClassId, compNr, instNr, msgNr);

	MessageProcessor msgProc(CLASS_ID_RANGE, MSG_LEN);

	// if (th1.joinable())
	// {
	// 	th1.join();
	// }
	
	msgProc.displayAllMsg();
	msgProc.NewMsgRetriever(CLASS_ID_RANGE);
	msgProc.displayNewMsg();

	return 0;
}