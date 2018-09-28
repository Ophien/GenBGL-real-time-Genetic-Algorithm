/*MIT License
*
*Copyright (c) 2018 Alysson Ribeiro da Silva
*
*Permission is hereby granted, free of charge, to any person obtaining a copy 
*of this software and associated documentation files (the "Software"), to deal 
*in the Software without restriction, including *without limitation the rights 
*to use, copy, modify, merge, publish, distribute, sublicense, and/or sell 
*copies of the Software, and to permit persons to whom the Software is furnished 
*to do so, subject *to the following conditions:
*
*The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
*
*THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
*EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
*FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. *IN NO EVENT SHALL THE AUTHORS 
*OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN 
*AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH 
*THE *SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#pragma once
//------------------------------------------------------------------------------------------------
//ARS_COMMENTS::SYSTEM INCLUDES
//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
//ARS_COMMENTS::INTERNAL INCLUDE
//------------------------------------------------------------------------------------------------
#include "ARS_BeingStatus.h"

//------------------------------------------------------------------------------------------------
//ARS_COMMENTS::USED NAMESPACES
//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
//ARS_COMMENTS::DEFINITIONS
//------------------------------------------------------------------------------------------------
//ESTADOS DO SER
#define NEWBORN     -1
#define IDLE         0
#define BREEDIND_AGE 1
#define BREEDING     2
#define OLD_AGE      3
#define DEAD         4

//------------------------------------------------------------------------------------------------
//ARS_COMMENTS::MACROS
//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
//ARS_COMMENTS::CONSTANTS
//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
//ARS_COMMENTS::GLOBAL FUNCTIONS BODYS
//------------------------------------------------------------------------------------------------

namespace behavior_helper{
	//ARS_COMMENTS::OPERAÇÕES BÁSICAS PARA CONTROLAR COMPORTAMENTO DO INDIVÍDUO

	//UTILIZADA PARA ATUALIZAR O TEMPO DE VIDA E CONFIGURAR ALGUMA FLAG DE ATIVAÇÃO
	extern void UpdateLifeTimeA     (const double& time, ARS_BeingStatus& beingStatus);

	//UTILIZADA PARA ATUALIZAR A FLAG RESPONSÁVEL PELO ACASALAMENTO
	extern void UpdateBreedingTimeA (const double& time, ARS_BeingStatus& beingStatus);

	//UTILIZADA PARA ATUALIZAR ESTADO DE INVALIDADE DA INDIVÍDUO
	extern void UpdateOldTimeA      (const double& time, ARS_BeingStatus& beingStatus);

	//UTLIZADO PARA SOLICITAR CRUZAMENTO COM OUTRO INDIVÍDUO
	extern void UpdateSelectionA    (const double& time, ARS_BeingStatus& beingStatus);

	//UTILIZADO PARA SIMULAR CRUZAMENTO COM OUTRO INDIVÍDUO
	extern void UpdateBreedingA     (const double& time, ARS_BeingStatus& beingStatus);

	//UTILIZADO PARA APLICAR MUTAÇÃO NO RESPECTIVO INDIVÍDUO
	extern void UpdateMutationA     (const double& time, ARS_BeingStatus& beingStatus);
};
