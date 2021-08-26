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
 * @file MessageProcessor.hpp
 * @author nkhaldi (nkhaldi@sepro-group.com)
 * @version 0.1
 * @date 2021-05-07
 */

#ifndef _MESSAGE_PROCESSOR_HPP_
#define _MESSAGE_PROCESSOR_HPP_

#include <iostream>
#include "BPApiRepSys.h"
#include "Message.hpp"
#include <vector>
#include <thread>
#include <mutex>
#include <functional> //std::functions
#include <stack>
#include <condition_variable>

/**
 * @brief 
 * contient tous les traitements pouvant etre fait sur un message ou un groupe de message
 * - recuperation / modification / renvoi d un message ou groupe de messages
 * 
 * la liste de methodes n est pas exhaustive et pourrait etre revue a la baisse en fonction de la demande
 */
class MessageProcessor
{
    public:

        // done
        MessageProcessor(BPApiRepSysMsgClass p_classId, size_t p_len);

        // done
        ~MessageProcessor();

        // done
        static void     messageModifier(Message *msg, size_t len);

        // done
        void            displayNewMsg(void);

        // done
        void            displayAllMsg(void);

        // in progress
        bool            NewMsgRetriever(BPApiRepSysMsgClass msgClassId);

    private:

        BPApiRepSysMsgClass     m_classRange;

        std::stack<Message *>   m_msgQ;

        std::condition_variable data_cond;

        BPApiRepSysMsgHdl       m_last_msgHdl;
        BPApiTime               m_last_ts; // unused but maybe usefull
    
        std::thread             m_msgQSetterThread;
        std::thread             m_msgQGetterThread;
        std::mutex              m_msgQMutex;

        // in progress
        bool                    init(void);

};

#endif