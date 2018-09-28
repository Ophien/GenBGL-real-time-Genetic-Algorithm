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

//------------------------------------------------------------------------------------------------
//ARS_COMMENTS::SYSTEM INCLUDES
//------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <math.h>

//------------------------------------------------------------------------------------------------
//ARS_COMMENTS::INTERNAL INCLUDE
//------------------------------------------------------------------------------------------------
#include "ARS_FemaleBehavior.h"
#include "Behavior_helper.h"
#include "ARS_Being.h"
#include "ARS_Population.h"
#include "Defaults.h"

//------------------------------------------------------------------------------------------------
//ARS_COMMENTS::USED NAMESPACES
//------------------------------------------------------------------------------------------------
using namespace behavior_helper;
using namespace std;

//------------------------------------------------------------------------------------------------
//ARS_COMMENTS::DEFINITIONS
//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
//ARS_COMMENTS::MACROS
//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
//ARS_COMMENTS::CONSTANTS
//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
//ARS_COMMENTS::GLOBAL FUNCTIONS BODYS
//------------------------------------------------------------------------------------------------
ARS_FemaleBehavior::ARS_FemaleBehavior(void) : ARS_Behavior(){
}
//------------------------------------------------------------------------------------------------
ARS_FemaleBehavior::~ARS_FemaleBehavior(void){
}
//------------------------------------------------------------------------------------------------
//ARS_COMMENTS::EXECUTA PRE COMPORTAMENTO
void ARS_FemaleBehavior::PreBehavior(ARS_BeingStatus& beingStatus, const double& time){
	//TODO::TRATAR EVENTOS AQUI
}
//------------------------------------------------------------------------------------------------
//ARS_COMMENTS::EXECUTA POS COMPORTAMENTO
void ARS_FemaleBehavior::PosBehavior(ARS_BeingStatus& beingStatus, const double& time){
	//TODO::TRATAR EVENTOS AQUI
}
//------------------------------------------------------------------------------------------------
//ARS_COMMENTS::UTILIZADO PARA EXECUTAR COMPORTAMENTO
void ARS_FemaleBehavior::Behavior(ARS_BeingStatus& beingStatus, const double& time){
	//TODO::ARRUMAR ESSE POG
	if(beingStatus.State() == ARS_DEAD)
		return;

	if(beingStatus.Parent().Population().GetPopulation()[beingStatus.Generation()+1].first.beingsCount
		>= beingStatus.Parent().Population().GetConfiguration().InicialPopulationSize)
		return;

	//TODO COLOCAR TODO COMPORTAMENTO DO MACHO AQUI
	//----------------------------OPERAÇÕES OBRIGATÓRIAS------------------------------
	UpdateLifeTimeA(time, beingStatus);
	UpdateMutationA(time, beingStatus);
	//----------------------------OPERAÇÕES OBRIGATÓRIAS------------------------------
	int death_random = rand() % 2;
	ARS_PopulationConfig& config = beingStatus.Parent().Population().GetConfiguration();

	if(beingStatus.MaxBreeding() >= config.femaleReproductionLimiar)
		beingStatus.State() = ARS_DEAD;

	//Máquina de estados do indivíduo
	switch(beingStatus.State()){
	case ARS_CHILD:
		//Atualização dos temporizadores
		if(beingStatus.LifeTime() >= beingStatus.BreedingAge())
			beingStatus.State() = ARS_ADULT;
		break;
	case ARS_ADULT:
		//Atualizar estado de acasalamento aqui
		if(config.DualProposal)
			UpdateSelectionA(time, beingStatus);
		
		UpdateBreedingA(time, beingStatus);

		if(beingStatus.LifeTime() >= beingStatus.OldAge())
			beingStatus.State() = ARS_OLD;
		break;
	case ARS_OLD:
		//Atualizar estado de velhice aqui
		if(death_random)
			beingStatus.State() = ARS_DEAD;
		break;
	case ARS_DEAD:
		//Atualizar morte aqui
		beingStatus.Parent().Population().Statistics().deadFemales++;
		beingStatus.Parent().Population().Statistics().dead++;
		beingStatus.Parent().Population().GetPopulation()[beingStatus.Generation()].first.deadFemales++;
		//ARS_COMMENTS::TODO::COLOCAR NA LISTA PARA REMOÇÃO POSTERIOR DA POPULAÇÃO
		break;
	}
}


