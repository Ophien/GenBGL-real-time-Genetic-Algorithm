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
#include "Behavior_helper.h"
#include "ARS_Operations.h"
#include "ARS_PopulationConfig.h"
#include "ARS_Population.h"
#include "ARS_Being.h"

//------------------------------------------------------------------------------------------------
//ARS_COMMENTS::USED NAMESPACES
//------------------------------------------------------------------------------------------------
using namespace ARS_Operations;

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

namespace behavior_helper{
	//------------------------------------------------------------------------------------------------
	void UpdateLifeTimeA     (const double& time, ARS_BeingStatus& beingStatus){
		beingStatus.LifeTime() += time;
	}
	//------------------------------------------------------------------------------------------------
	void UpdateSelectionA    (const double& time, ARS_BeingStatus& beingStatus){
		//Configurar solicitação para cruzamento aqui
		int& MyGeneration = beingStatus.Generation();
		int& MySex        = beingStatus.Sex();
		double& MyFitness = beingStatus.Fitness();

		//Para manipulação de lógica
		ARS_Population&       CurrentPop    = beingStatus.Parent().Population();
		ARS_PopulationStatus& Status	    = CurrentPop.GetCurrentPopStatus();
		ARS_PopulationConfig& CurrentConfig = CurrentPop.GetConfiguration();

		//Normalmente configurada em uma fêmea
		ARS_Being* destination;

		bool OK = false;
		int popSize = 0;

		vector<ARS_Being*>* beings;
		ARS_PopulationHolder& currentHolder = CurrentPop.GetPopulation()[MyGeneration].second[!MySex];

		
		//ARS_COMMENTS::SUBDIVISION SELECTION
		if(MyFitness > CurrentConfig.highLimiar){
			popSize = currentHolder.high.size();
			beings  = &currentHolder.high;
		}
		else
			if(MyFitness < CurrentConfig.highLimiar && MyFitness >= CurrentConfig.lowLimiar){
				int breedRand = rand() % 2;
				if(breedRand == 1){
					popSize = currentHolder.high.size();
					beings  = &currentHolder.high;
				}else{
					popSize = currentHolder.low.size();
					beings  = &currentHolder.low;
				}
			}
			else
				if(MyFitness < CurrentConfig.lowLimiar){
					popSize = currentHolder.medium.size();
					beings  = &currentHolder.medium;
				}
		//ARS_COMMENTS::SUBDIVISION SELECTION

		if(popSize > 0){
			int breedingSelection = rand() % popSize;

			//Seleção por categoria/compartimento
			destination = beings[0][breedingSelection];
			OK = true;
		}else{
			int size = currentHolder.all.size();
			if(size > 0){
				int breedingSelection = rand() % size;

				//Seleção por categoria/compartimento
				destination = currentHolder.all[breedingSelection];
				OK = true;
			}
		}

		if(OK){
			//TODO::LIMPAR MEMÓRIA CORRETAMENTE DEPOIS
			ARS_BreedingProposal* prop = new ARS_BreedingProposal();
			prop->proposer = &beingStatus.Parent();
			destination->BreedingProposal().push_back(prop);
		}
	}
	//------------------------------------------------------------------------------------------------
	void UpdateBreedingA     (const double& time, ARS_BeingStatus& beingStatus){
		//Configurar cruzamento aqui
		ARS_Population& CurrentPop          = beingStatus.Parent().Population();
		ARS_PopulationConfig& CurrentConfig = CurrentPop.GetConfiguration();

		//Verifica se há alguma proposta de cruzamento e usa a probabilidade de cruzamento bem sucedido aqui
		ARS_Being& Me = beingStatus.Parent();

		//Caso haja alguma proposta de cruzamento
		if(Me.BreedingProposal().size() >0){
			ARS_Being& proposer = *Me.BreedingProposal().back()->proposer;
			
			//Atualiza e cruza os indivíduos aqui
			ApplyCrossOver(CurrentConfig, Me, proposer);
		}

		Me.BreedingProposal().clear();
	}
	//------------------------------------------------------------------------------------------------
	//TODO::INVALIDAR ESTA OPERAÇÃO POIS A MUTAÇÃO É FEITA BIT A BIT EM TEMPO DE CRIAÇÃO
	void UpdateMutationA     (const double& time, ARS_BeingStatus& beingStatus){
		//Configurar mutação local aqui
	}
	//------------------------------------------------------------------------------------------------
};
