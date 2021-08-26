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
 * @file Message.cpp
 * @author nkhaldi (nkhaldi@sepro-group.com)
 * @version 0.1
 * @date 2021-05-07
 */

#include "BPApiRepSys.h"
#include "Message.hpp"
#include "DisplayChecker.hpp"

// coloring for better visualization of messages and debugging messages
#define RED_COLOR		"\033[0;31m"
#define GREEN_COLOR		"\033[1;32m"
#define YELLOW_COLOR	"\033[1;33m"
#define BLUE_COLOR		"\033[1;34m"
#define PURPLE			"\033[0;35m"
#define CYAN_COLOR		"\033[0;36m"
#define END_COLOR		"\033[1;0m"

#include <strings.h> // explicit_bzero
#include <stdlib.h> // malloc

/* 
why a specific class for messages ? because you may want (I needed) to do some operations on a message like : 
    - set/get specifically its attributes ? --> setters / getters
    - print all the attributes of a message ? --> operator << overload
    - print only the content of a message ? --> getMsgContent
    - compare two messages ? --> operator == and != overload

why wrapping the BPApiRespSys functions ?
    - for better maintenability, if the api changes for another one than the RepSys one

WIDIWIN : what is done is what is needed
*/

/**
 * @brief 
 * Construct a new Message object
 * 
 */
Message::Message(){
}

/**
 * @brief 
 * Construct a new Message object by setting each of its attributes
 * functional test ok
 * 
 * @param p_msgClassId 
 * @param p_compNr 
 * @param p_instNr 
 * @param p_msgNr 
 * @param p_ts 
 * @param p_paramCount 
 * @param p_msgState 
 * @param p_protocol_var 
 * @param p_hdl 
 */
Message::Message(
    BPApiRepSysMsgClass p_msgClassId,
	uint32_t            p_compNr,
	uint32_t            p_instNr,
	uint32_t            p_msgNr,
    BPApiTime           p_ts,
	uint32_t            p_paramCount,
	BPApiState          p_msgState,
	uint32_t            p_protocol_var,
    BPApiRepSysMsgHdl   p_hdl
    ) :
        m_msgClassId(p_msgClassId),
        m_compNr(p_compNr),
        m_instNr(p_instNr),
        m_msgNr(p_msgNr),
        m_ts(p_ts),
        m_paramCount(p_paramCount),
        m_msgState(p_msgState),
        m_protocol_var(p_protocol_var),
        m_msgHdl(p_hdl){
	// message key = compNr/msgNr
}

/**
 * @brief Destroy the Message object
 * 
 */
Message::~Message(){
}

/**
 * @brief 
 * Wrapper for BPApiRepSysGetMsgDataValues2
 * Construct a new Message object based on a msgHdl
 * functional test ok
 * 
 * @param msgHdl 
 */
Message::Message(const BPApiRepSysMsgHdl &msgHdl) {
    // BPApiState retCode;

    m_msgHdl = msgHdl;

	BPApiRepSysGetMsgDataValues2(  // on recupere les infos : classId, compNr, instNr, msgNr ... correspondant au handler
			msgHdl, // [in]
			&m_msgClassId, // ex. 256 <=> 0x100ul donc class9
			&m_compNr, // ex. 50
			&m_instNr, // ex. 10223622 
			&m_msgNr, // ex. 9999 
			&m_ts, 
			&m_paramCount, // ex. 1 
			&m_msgState, // ex. BPApiRepSysMsgStateToQuit
			&m_protocol_var);

    // si tu mets __FUNCTION__ tu vas afficher le nom de la classe mais pas le nom de la methode
	// DisplayChecker::DisplayBPApiState(__PRETTY_FUNCTION__, retCode);
}

/**
 * @brief 
 * Copy constructor : Construct a new Message:: Message object
 * functional test ok
 * 
 * @param src 
 */
Message::Message(Message const &src){

    this->m_msgClassId = src.m_msgClassId;
    this->m_compNr = src.m_compNr;
    this->m_instNr = src.m_instNr;
    this->m_msgNr = src.m_msgNr;
    this->m_ts = src.m_ts;
    this->m_paramCount = src.m_paramCount;
    this->m_msgState = src.m_msgState;
    this->m_protocol_var = src.m_protocol_var;
    this->m_msgHdl = src.m_msgHdl;
}

/**
 * @brief
 * set the class id for the current message instance
 * cpy Message to current Message instance
 * functional test ok : retry to be sure
 * 
 * @param newMsgClassId 
 */
void        Message::setClassId(BPApiRepSysMsgClass newMsgClassId) {
    this->m_msgClassId = newMsgClassId;
    return;
}

/**
 * @brief
 * set new msg state (for functional test !)
 * 
 * @param newMsgState 
 */
void        Message::setMsgState(BPApiRepSysMsgState newMsgState) {
    this->m_msgState = newMsgState;
    return;
}

/**
 * @brief 
 * test the equality between 2 Message objects
 * functional test ok
 * 
 * @param src 
 * @return true 
 * @return false 
 */
bool        Message::operator==(Message const &src){

	if ( this != &src ){
	    if (this->m_msgClassId != src.m_msgClassId){
            return false;
        }

	    if (this->m_compNr != src.m_compNr){
            return false;
        }

	    if (this->m_instNr != src.m_instNr){
            return false;
        }

	    if (this->m_msgNr != src.m_msgNr){
            return false;
        }

    // pas de comparaison sur le timestamp mais on pourrait en faire un si on est fou
    // pas pertinent ceci dit dans l immediat
        // if (this->m_ts != src.m_ts)
        // {
        //     return false;
        // }

	    if (this->m_paramCount != src.m_paramCount){
            return false;
        }

	    if (this->m_msgState != src.m_msgState){
            return false;
        }

	    if (this->m_protocol_var != src.m_protocol_var){
            return false;
        }

        if (this->m_msgHdl != src.m_msgHdl){
            return false;
        }
    }
    return true;
}

/**
 * @brief 
 * test the non-equality between 2 Message objects
 * functional test ok
 * 
 * @param src 
 * @return true 
 * @return false 
 */
bool        Message::operator!=(Message const &src) {
    return ( (*this == src) ? false : true);
}

/**
 * @brief
 * functional test ok
 * 
 * @param os 
 * @param src 
 * @return std::ostream& 
 */
std::ostream & operator<<(std::ostream &os, const Message & src) {

    os <<  "\n\tmsgClassId [" << std::hex << src.m_msgClassId << "]";
    os <<  "\n\tcompNr [" << src.m_compNr << "]";
    os <<  "\n\tinstNr [" << src.m_instNr << "]";
    os <<  "\n\tmsgNr [" << src.m_msgNr << "]";
    // os <<  "\nts [" << src.m_ts << "]";
    os <<  "\n\tparamCount [" << src.m_paramCount << "]";
    os <<  "\n\tmsgState [" << src.m_msgState << "]";
    os <<  "\n\tprotocol_var [" << src.m_protocol_var << "]";
    // os <<  "\n\thdl [" << src.m_hdl << "]"; // pas pertinent

	return os;
}

/**
 * @brief 
 * getter for compNr attribute
 * functional test ok
 * 
 * @return uint32_t 
 */
uint32_t Message::getCompNr(void){
    return m_compNr;
}

/**
 * @brief 
 * getter for instNr attribute
 * functional test ok
 * 
 * @return uint32_t 
 */
uint32_t Message::getInstNr(void){
    return m_instNr;
}

/**
 * @brief 
 * getter for msgNr attribute
 * functional test ok
 * 
 * @return uint32_t 
 */
uint32_t Message::getMsgNr(void){
    return m_msgNr;
}

/**
 * @brief 
 * getter for handle (msgHdl) attribute
 * functional test ok
 * 
 * @return uint32_t 
 */
uint32_t Message::getHdl(void){
    return m_msgHdl;
}

/**
 * @brief 
 * getter for message classsId attribute
 * functional test ok
 * 
 * @return BPApiRepSysMsgClass 
 */
BPApiRepSysMsgClass Message::getClassId(void){
    return m_msgClassId;
}

/**
 * @brief 
 * 
 * @return BPApiRepSysMsgState 
 */
BPApiRepSysMsgState Message::getState(void){
    return m_msgState;
}

/**
 * @brief Get the Time object
 * 
 * @return BPApiTime 
 */
BPApiTime       Message::getTime(void)
{
    return this->m_ts;
}

/**
 * @brief 
 * get the content of the message object
 * get it from parameters msgHdl and the expected length of the message
 * functional test ok
 * 
 * @param msgHdl 
 * @param len 
 * @return std::string 
 */
std::string     Message::getMsgContent(const BPApiRepSysMsgHdl &msgHdl, size_t len){
	// BPApiState retCode;

	char *buffer = (char *)malloc(len * sizeof(char));
	bzero(buffer, len); // rtfm

	BPApiRepSysFormatMsgA(msgHdl, buffer, len);// msgHdl [in] ; buffer [out]

    std::string content(buffer);

    free(buffer);

	// DisplayChecker::DisplayBPApiState(__PRETTY_FUNCTION__, retCode);

    return content;
}

/**
 * @brief 
 * get the content of the message object
 * get it from another Message object and the expected length of the message
 * functional test ok
 * 
 * @param msg 
 * @param len 
 * @return std::string 
 */
std::string     Message::getMsgContent(Message msg, size_t len){
	
    // BPApiState retCode;

	char *buffer = (char *)malloc(len * sizeof(char));
	bzero(buffer, len); // rtfm

	BPApiRepSysFormatMsgA(msg.getHdl(), buffer, len);// msgHdl [in] ; buffer [out]

    std::string content(buffer);

    free(buffer);

	// DisplayChecker::DisplayBPApiState(__PRETTY_FUNCTION__, retCode);

    return content;
}