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
 * @file MessageProcessor.cpp
 * @author nkhaldi (nkhaldi@sepro-group.com)
 * @version 0.1
 * @date 2021-05-07
 */

#include "Message.hpp"
#include "DisplayChecker.hpp"
#include "MessageProcessor.hpp"
#include "BPApiRepSys.h"

// cpp lib
#include <thread>
#include <chrono>
#include <functional>
#include <csignal>

// #define TIME_INTERVAL 100 // ms ?
#define TIME_INTERVAL 3 // ms ?

// clib
#include <string.h>

// defines

#define MSG_LEN 60

// colors allows the user to best distinguish the messages + usefull for debuging
#define RED_COLOR		"\033[0;31m"
#define GREEN_COLOR		"\033[1;32m"
#define YELLOW_COLOR	"\033[1;33m"
#define BLUE_COLOR		"\033[1;34m"
#define PURPLE_COLOR	"\033[0;35m"
#define CYAN_COLOR		"\033[0;36m"
#define END_COLOR		"\033[1;0m"

#define COMP_NR			100 // safety


/**
 * @brief 
 * Construct a new MessageProcessor object
 * 
 * @param p_classId 
 * @param p_len 
 */
MessageProcessor::MessageProcessor(BPApiRepSysMsgClass p_classId, size_t p_len){
	m_classRange = p_classId;
	m_last_msgHdl = 0;
	init();
}

/**
 * @brief
 * not really used ...
 * 
 * @param p_classId 
 * @param p_len 
 * @return true 
 * @return false 
 */
bool	MessageProcessor::init()
{
	return ( ( m_msgQSetterThread.joinable() && m_msgQGetterThread.joinable() ) ? true : false);
}

/**
 * @brief 
 * Destroy the MessageProcessor object
 * 
 */
MessageProcessor::~MessageProcessor(){
	if (m_msgQSetterThread.joinable()){
		std::cout << "ending thread setter" << std::endl;
		m_msgQSetterThread.join();
	};

	if (m_msgQGetterThread.joinable()){
		std::cout << "ending thread getter" << std::endl;
		m_msgQGetterThread.join();
	};
}

/**
 * @brief 
 * [ WIP ] Operationnal POC for retrieving existing messages and new one
 * 
 * @param p_msgClassId 
 * @return true 
 * @return false 
 */
bool	MessageProcessor::NewMsgRetriever(BPApiRepSysMsgClass p_msgClassId){
	BPApiState retCode(void); // void permets d eviter les erreur de "unused parameter" [comment to be deleted]

	m_msgQSetterThread = std::thread([=]() mutable {
		std::cout << "enter NewMsgRetriever " << std::endl;

		while (true)
		{
			BPApiRepSysMsgHdl msgHdl;
			// std::this_thread::sleep_for(std::chrono::milliseconds(TIME_INTERVAL));
			std::this_thread::sleep_for(std::chrono::seconds(TIME_INTERVAL));

			if (BPApiRepSysGetLastMsg(p_msgClassId, &msgHdl) == BPApiStateOk && msgHdl != m_last_msgHdl)
			{
				Message *msg = new Message(msgHdl);
				if (msg->getCompNr() == 100)
				{
					messageModifier(msg, MSG_LEN);

					std::lock_guard<std::mutex> guard_1(m_msgQMutex);
					m_msgQ.push(msg);
					m_last_msgHdl = msgHdl;
				}
			}

		}
	});

	return true; // todo : define condition for returning true or false
}

/**
 * @brief 
 * print message from the message queue
 * 
 */
void	MessageProcessor::displayNewMsg(){

	std::cout << "\ndisplayMsgQ (get last msg)" << std::endl;

	m_msgQGetterThread = std::thread([=]() mutable {

		while (1)
		{
			std::unique_lock<std::mutex> lk(m_msgQMutex);
			lk.unlock();
			// std::this_thread::sleep_for(std::chrono::milliseconds(TIME_INTERVAL));
			std::this_thread::sleep_for(std::chrono::seconds(5));
			lk.lock();

			while (!m_msgQ.empty())
			{
				data_cond.wait(lk, [this] { return !m_msgQ.empty(); });
				Message *front = m_msgQ.top();
				std::cout << std::endl
						  << "XXXXXXXXXXXXXXXXXXX DISPLAY RETRIEVED MESSAGE [";
				std::cout << YELLOW_COLOR << Message::getMsgContent(*front, MSG_LEN) << END_COLOR << "]" << std::endl;
				m_msgQ.pop();
			}
			lk.unlock();
		}
	});
}

/**
 * @brief 
 * 
 */
void	MessageProcessor::displayAllMsg()
{
	std::cout << GREEN_COLOR << "Retrieving existing msgs from class (decimal) 1 to 12 (hexa : 1 to 800)" << END_COLOR << std::endl;

	BPApiRepSysMsgHdl msgHdl;
	std::string msgContent;

	if (BPApiRepSysGetFirstMsg(m_classRange, &msgHdl) == BPApiStateOk)
	{
		Message firstMsg(msgHdl);

		if (firstMsg.getCompNr() == COMP_NR)
		{
			msgContent = Message::getMsgContent(msgHdl, MSG_LEN);
			std::cout << YELLOW_COLOR << "get content from msgHdl : " << msgContent.c_str() << END_COLOR << std::endl;

			std::cout << "\nbefore changing classID" << std::endl;
			std::cout << RED_COLOR << firstMsg << END_COLOR << std::endl;

			MessageProcessor::messageModifier(&firstMsg, MSG_LEN);

			std::cout << "\nafter changing classID" << std::endl;
			std::cout << GREEN_COLOR << firstMsg << END_COLOR << std::endl;

			m_last_msgHdl = msgHdl;
		}

		while (BPApiRepSysGetNextMsg(m_classRange, &msgHdl) == BPApiStateOk)
		{
			Message nextMsg(msgHdl);

			if (nextMsg.getCompNr() == COMP_NR)
			{
				std::cout << "\n**********************************************" << std::endl;

				std::cout << std::endl;
				msgContent = Message::getMsgContent(msgHdl, MSG_LEN);
				std::cout << YELLOW_COLOR << msgContent.c_str() << END_COLOR << std::endl;

				std::cout << "\nbefore changing class" << std::endl;
				std::cout << RED_COLOR << nextMsg << END_COLOR << std::endl;

				MessageProcessor::messageModifier(&nextMsg, MSG_LEN);

				std::cout << "\nafter changing classID" << std::endl;
				std::cout << GREEN_COLOR << nextMsg << END_COLOR << std::endl << std::endl;
			}
		}

		m_last_msgHdl = msgHdl;
	}
}

/**
 * @brief 
 * for a given message represented by its msg handle (msgHdl)
 * 1. retrieving of its content
 * 2. forward it to repsys with new classId if need be
 * 
 * @param msgClassId 
 * @param compNr 
 * @param instNr 
 * @param msgNr 
 * @param msgHdl 
 * @param len 
 */
void	MessageProcessor::messageModifier(Message *msg, size_t len){

    if (msg->getClassId() == BPApiRepSysMsgClassWarning || msg->getClassId() == BPApiRepSysMsgClass8 || msg->getClassId() == BPApiRepSysMsgClass11)
    {
		msg->setClassId(BPApiRepSysMsgClass15);
        std::cout << BLUE_COLOR << "\n --> (warning) to be forwarded to new class 15 (0x4000)" << END_COLOR << std::endl;
    }
	// StateToReset = 4 ; StateToResetAndQuit = 6
	else if (msg->getState() == BPApiRepSysMsgStateToReset || msg->getState() == BPApiRepSysMsgStateToResetAndQuit)
    {
		msg->setClassId(BPApiRepSysMsgClass14);
        std::cout << BLUE_COLOR << "\n --> (not-ack) to be forwarded to new class 14 (0x2000)" << END_COLOR << std::endl;
    }
	// StateToQuit = 5 ; StateToResetOrQuit = 7
    else if (msg->getState() == BPApiRepSysMsgStateToQuit || msg->getState() == BPApiRepSysMsgStateToResetOrQuit)
    {
		msg->setClassId(BPApiRepSysMsgClass13);
        std::cout << BLUE_COLOR << "\n --> (ack) to be forwarded to new class 13 (0x1000)" << END_COLOR << std::endl;
    }
	else
	{
		std::cout << BLUE_COLOR << "\n no class change needed" << END_COLOR << std::endl << std::endl;
	}

	std::string msgContent = msg->getMsgContent(*msg, MSG_LEN);

	BPApiRepSysSetMsgA(msg->getClassId(), msg->getCompNr(), msg->getInstNr(), msg->getMsgNr(), "%s", msgContent.c_str()); // recupere et affiche le msg correspondant aux datas compNr, instNr, msgNr et classIdassId
	// DisplayChecker::DisplayBPApiState(__PRETTY_FUNCTION__, retCode);
}
