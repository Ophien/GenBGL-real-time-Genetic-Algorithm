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
#include <vector>

//------------------------------------------------------------------------------------------------
//ARS_COMMENTS::INTERNAL INCLUDE
//------------------------------------------------------------------------------------------------
#include "Defaults.h"
#include "ARS_Helper.h"

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

//using namespace ARS_Operations;
using namespace std;

class ARS_PopulationConfig
{
public:
	//CRIA CONFIGURAÇÃO COM VALORES PADRÕES
	ARS_PopulationConfig(
	bool RandomInitialBeings   = true,
	int TotalGenerations       = ARS_TOTAL_GENERATIONS,
	int InicialPopulationSize  = ARS_TOTAL_POPULATIONS,
	int DNACodificationSize    = ARS_DNA_CODIFICATION_SIZE,
	int DNAQuantity            = ARS_DNA_QUANTITY,
	int UpdateDepth            = ARS_UPDATE_DEPTH,
	double MutationProbability = ARS_MUTATION_PROBABILITY,
	double BreedingProbability = ARS_BREEDING_PROBABILITY,
	double highLimiar          = ARS_HIGH_LIMIAR,
	double lowLimiar           = ARS_LOW_LIMIAR,
	double highLimiarThreshold = ARS_HIGH_LIMIAR_THRESHOLD,
	double lowLimiarThreshold  = ARS_LOW_LIMIAR_THRESHOLD,
	int SelectionMethod        = ARS_SELECTION_METHOD,
	int MutationMethod         = ARS_MUTATION_METHOD,
	int FitnessFunction        = ARS_FITNESS_FUNCTION,
	int CrossoverFunction      = ARS_CROSSOVER_FUNCTION,
	int BreedingAge			   = ARS_BREEDING_AGE,
	int BreedingAgeInf         = ARS_BREEDING_AGE_INF,
	int BreedingAgeSup		   = ARS_BREEDING_AGE_SUP,
	int OldAge				   = ARS_OLD_AGE,
	int OldAgeInf              = ARS_OLD_AGE_INF,
	int OldAgeSup			   = ARS_OLD_AGE_SUP,
	int maleReproductionLimiar     = ARS_MALE_REP_LIMIAR,
	int maleRepLimiarInf		   = ARS_MALE_REP_INF,
	int maleRepLimiarSup		   = ARS_MALE_REP_SUP,
	int femaleReproductionLimiar   = ARS_FEMALE_REP_LIMIAR,
	int femaleRepLimiarInf		   = ARS_FEMALE_REP_INF,
	int femaleRepLimiarSup		   = ARS_FEMALE_REP_SUP,
	vector<pair<double, double>>* Limits = NULL);

	~ARS_PopulationConfig(void);

	vector<pair<double, double>>* Limits;

	//CONTROLA GERAÇÃO INICIAL DE INDIVÍDUOS RANDOMICOS	
	bool RandomInitialBeings;
	bool Eletism;
	bool DynamicMutation;
	bool High;
	bool Med;
	bool Low;
	bool Minimization;
	bool MutationDisabler;
	double InverseMutDisableCycle;
	double MutationDisablerCycle;
	double DynamicMutationCycle;
	double DualProposal;
	double EPSILON;

	//CONFIGURAÇÃO DOS INDIVIDUOS
	int TotalGenerations;
	int InicialPopulationSize;
	int DNACodificationSize;
	int DNAQuantity;

	//CONFIGURAÇÃO DE COMPORTAMENTO DA POPULAÇÃO
	int UpdateDepth;

	//CONFIGURAÇÃO DE PROBABILIDADES
	double MutationProbability;
	double BreedingProbability;

	//CONFIGURAÇÃO DE LIMIAR PARA SEPARAR INDIVÍDUOS EM GRUPOS
	double highLimiar;
	double lowLimiar;
	double highLimiarThreshold;
	double lowLimiarThreshold;

	//ID DAS FUNÇÕES CONFIGURADAS
	int SelectionMethod;
	int MutationMethod;
	int FitnessFunction;
	int CrossoverFunction;

	//SIMULATION CONFIG
	int maxGenBuffer;
	int maxUpdatesPerFrame;

	//LIFE LIMIAR
	int BreedingAge;
	int OldAge;
	int BreedingAgeInf;
	int BreedingAgeSup;
	int OldAgeInf;
	int OldAgeSup;
	
	//Utilizado para invalidar o indivíduo após cruzar
	int maleReproductionLimiar;
	int femaleReproductionLimiar;

	//Utilizado para controlar tudo
	int maleRepLimiarInf;
	int femaleRepLimiarInf;
	int maleRepLimiarSup;
	int femaleRepLimiarSup;
};

