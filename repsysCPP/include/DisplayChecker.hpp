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
 * @file DisplayChecker.hpp
 * @author nkhaldi (nkhaldi@sepro-group.com)
 * @version 0.1
 * @date 2021-05-07
 */

#ifndef _DISPLAY_CHECKER_HPP_
#define _DISPLAY_CHECKER_HPP_

#include "Message.hpp"
#include "BPApiRepSys.h"

/**
 * @brief 
 * Affichage de debug
 * - verification du contenu d un message
 * - verification du code de retour repSys
 */
class DisplayChecker
{
    public:
        static void DisplayBPApiState(const char *functionNameMsgPrefix, const BPApiState &BPApiRetCode);

    private:
};

#endif