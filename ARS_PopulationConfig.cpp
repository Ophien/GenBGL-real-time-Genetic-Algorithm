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

//------------------------------------------------------------------------------------------------
//ARS_COMMENTS::INTERNAL INCLUDE
//------------------------------------------------------------------------------------------------
#include "ARS_PopulationConfig.h"

//------------------------------------------------------------------------------------------------
//ARS_COMMENTS::USED NAMESPACES
//------------------------------------------------------------------------------------------------

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

ARS_PopulationConfig::ARS_PopulationConfig(
	bool RandomInitialBeings,
	int TotalGenerations,
	int InicialPopulationSize,
	int DNACodificationSize,
	int DNAQuantity,
	int UpdateDepth,
	double MutationProbability,
	double BreedingProbability,
	double highLimiar,
	double lowLimiar,
	double highLimiarThreshold,
	double lowLimiarThreshold,
	int SelectionMethod,
	int MutationMethod,
	int FitnessFunction,
	int CrossoverFunction,
	int BreedingAge,
	int BreedingAgeInf,
	int BreedingAgeSup,
	int OldAge,
	int OldAgeInf,
	int OldAgeSup,
	int maleReproductionLimiar,
	int maleRepLimiarInf,
	int maleRepLimiarSup,
	int femaleReproductionLimiar,
	int femaleRepLimiarInf,
	int femaleRepLimiarSup,
	vector<pair<double,double>>* Limits)
{
	//CONTROLA GERAÇÃO INICIAL DE INDIVÍDUOS RANDOMICOS	
	this->RandomInitialBeings = RandomInitialBeings;

	//CONFIGURAÇÃO DOS INDIVIDUOS
	this->TotalGenerations          = TotalGenerations;
	this->InicialPopulationSize     = InicialPopulationSize;
	this->DNACodificationSize       = DNACodificationSize;

	//Configura quantidade de variáveis
	this->DNAQuantity         = DNAQuantity;

	if(Limits == NULL){
		this->Limits = new vector<pair<double, double>>();
		for(int i = 0; i < 1; i++)
			this->Limits->push_back(make_pair(0.0,0.0)); //Insere limites para zero para passar na interpolação
	}else{
		this->Limits = Limits;
	}

	//CONFIGURAÇÃO DE PROBABILIDADES
	this->MutationProbability = MutationProbability;
	this->BreedingProbability = BreedingProbability;
	this->highLimiar          = highLimiar;
	this->lowLimiar           = lowLimiar;

	//COMPORTAMENTO
	this->UpdateDepth         = UpdateDepth;

	//ID DAS FUNÇÕES CONFIGURADAS
	this->SelectionMethod   = SelectionMethod;
	this->MutationMethod    = MutationMethod;
	this->FitnessFunction   = FitnessFunction;
	this->CrossoverFunction = CrossoverFunction;

	//CONFIGURAÇÕES COMPORTAMENTAIS
	this->BreedingAge    = BreedingAge;
	this->BreedingAgeInf = BreedingAgeInf;
	this->BreedingAgeSup = BreedingAgeSup;
	this->OldAge         = OldAge;
	this->OldAgeInf		 = OldAgeInf;
	this->OldAgeSup		 = OldAgeSup;

	//Limiar para separar população
	this->highLimiarThreshold = highLimiarThreshold;
	this->lowLimiarThreshold  = lowLimiarThreshold;

	//Utilizado para invalidar o indivíduo após cruzar
	this->maleReproductionLimiar   = maleReproductionLimiar;
	this->femaleReproductionLimiar = femaleReproductionLimiar;

	//Utilizado para controlar tudo
	this->maleRepLimiarInf     = maleRepLimiarInf;
	this->femaleRepLimiarInf   = femaleRepLimiarInf;
	this->maleRepLimiarSup     = maleRepLimiarSup;
	this->femaleRepLimiarSup   = femaleRepLimiarSup;

	maxGenBuffer       = ARS_MAX_GEN_BUFFER;
	maxUpdatesPerFrame = ARS_MAX_UPDATE_PER_FRAME;
	
	DynamicMutationCycle   = 10.0;
	EPSILON                = 0.0001;
	InverseMutDisableCycle = 3.0;
	MutationDisablerCycle  = 5.0;
	
	RandomInitialBeings = true;
	DynamicMutation     = true;
	Eletism             = true;
	High				= true;
	Med					= true;
	Low					= true;
	Minimization        = true;
	MutationDisabler    = true;
}
//------------------------------------------------------------------------------------------------
ARS_PopulationConfig::~ARS_PopulationConfig(void)
{
}
