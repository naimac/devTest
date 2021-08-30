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
 * @author nkhaldi (nkhaldi@sepro-group.com)
 * @version 0.1
 * @date 2021-05-07
 */

#ifndef _MESSAGE_HPP_
#define _MESSAGE_HPP_

#include <iostream>
#include "BPApiRepSys.h"

class Message
{
    public:

        // constructors
        Message();
        Message( // todo : delete it
            BPApiRepSysMsgClass p_msgClassId,
            uint32_t p_compNr,
            uint32_t p_instNr,
            uint32_t p_msgNr,
            BPApiTime p_ts,
            uint32_t p_paramCount,
            BPApiState p_msgState,
            uint32_t p_protocol_var,
            BPApiRepSysMsgHdl p_hdl
            );
        Message(Message const & src);
        Message(const BPApiRepSysMsgHdl &msgHdl); // BPApiRepSysGetMsgDataValues

        // destructor
        ~Message();

        // operator overload
        Message & operator=(Message const &src) = delete;  // forbidding copy
        bool operator==(Message const &src); // operator "==" overload
        bool operator!=(Message const &src); // operator "==" overload
        friend std::ostream & operator<<(std::ostream &os, Message const &src); // operator "<<" overload

        // get and format message content
        static std::string getMsgContent(const BPApiRepSysMsgHdl &msgHdl, size_t len);
        static std::string getMsgContent(Message msg, size_t len);

        // setters
        void setClassId(BPApiRepSysMsgClass newMsgClassId); // cpy Message to current Message instance
        void setMsgState(BPApiRepSysMsgState newMsgState);

        // getters
        uint32_t getCompNr(void);
        uint32_t getInstNr(void);
        uint32_t getMsgNr(void);
        uint32_t getHdl(void);
        u_int32_t getState(void);
        BPApiTime getTime(void);
        BPApiRepSysMsgClass getClassId(void);

        // voir comment compiler et construire cette methode
        // Message & GetSpecificMessage(const BPApiRepSysMsgClass &msgClass, const uint32_t &compNr, const uint32_t &instNr, const uint32_t &msgNr);

    private:

	    BPApiRepSysMsgClass m_msgClassId; 
	    uint32_t            m_compNr;
	    uint32_t            m_instNr;
	    uint32_t            m_msgNr;
        BPApiTime           m_ts;
	    uint32_t            m_paramCount;
	    BPApiState          m_msgState;
	    uint32_t            m_protocol_var;
        BPApiRepSysMsgHdl   m_msgHdl; // mandatory
};

#endif