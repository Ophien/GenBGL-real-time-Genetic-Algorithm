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
#include "ARS_Being.h"
#include "ARS_Operations.h"
#include "ARS_BenchmarkFunctions.h"
#include "ARS_BehaviorBank.h"

//------------------------------------------------------------------------------------------------
//ARS_COMMENTS::USED NAMESPACES
//------------------------------------------------------------------------------------------------
using namespace ARS_Operations;
using namespace ARS_BenchmarkFunctions;

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

ARS_Being::ARS_Being(ARS_Population& population, int DNAQuant){
	//Configurando ID
	Status.ID()    = population.GenBeing();
	Status.State() = ARS_CHILD; //Estado ap�s acabar de nascer
	Pop = &population;

	//Configura��o da popula��o a qual o ser pertence
	ARS_PopulationConfig& configuration = population.GetConfiguration();

	//Inicializando buffers de vari�veis
	//Buferiza��o utilizada para evitar cria��o de mais loops na hora de se calcular a adaptabilidade
	//decimal      = new double[DNAQuant];
	//interpolated = new double[DNAQuant];

	//Configurando fun��o de avalia��o
	fitnessFunction = GetFitnessFunction(configuration.FitnessFunction);

	Behavior = NULL;

	//Referencia para grafo de cena =)
	Status.SetParent(this);
}
//------------------------------------------------------------------------------------------------
ARS_Being::ARS_Being(ARS_Population& population){
	//Configurando ID
	Status.ID()    = population.GenBeing();
	Status.State() = ARS_CHILD; //Estado ap�s acabar de nascer
	Pop = &population;

	//Configura��o da popula��o a qual o ser pertence
	ARS_PopulationConfig& configuration = population.GetConfiguration();

	//Inicializando buffers de vari�veis
	//Buferiza��o utilizada para evitar cria��o de mais loops na hora de se calcular a adaptabilidade
	//decimal      = new double[configuration.Limits->size()];
	//interpolated = new double[configuration.Limits->size()];

	//Configurando fun��o de avalia��o
	fitnessFunction = GetFitnessFunction(configuration.FitnessFunction);

	//Gera apenas se for randomico
	if(configuration.RandomInitialBeings){

		//Cria bin�rios aleat�rios
		for(unsigned int i = 0; i < configuration.Limits->size(); i++){
			//Pega referencia, ponteiro criado dentro da fun��o
			//TODO::VERIFICAR COMPLEXIDADE:: 1 FOR PARA BIN E DEC
			//TODO::VERIFICAR NECESSIDADE DE TER 1 FOR AQUI DENTRO PARA CALCULAR BIN SEPARADO
			ARS_Bin& newDNA = ARS_RandomBin(configuration.DNACodificationSize);

			//Adiciona DNA na lista
			DNA.push_back(&newDNA);

			//Adiciona decimal da lista de decimais
			decimal.push_back(newDNA.Decimal());

			//Adiciona valores interpolados no buffer do indiv�duo
			std::pair<double, double> currentLimit = configuration.Limits[0][i];
			double interpol = Interpolation(
										decimal[i], 
										currentLimit.first, 
										currentLimit.second, 
										configuration.DNACodificationSize);
			interpolated.push_back(interpol);
		}

		//Calcula fitness de acordo com os valores buferizados j� interpolados da codifica��o
		//J� tem que estar calculado para evitar opera��es desnecess�rias na hora de inserir na popula��o
		if(configuration.Minimization)
			Status.Fitness() = 1/(fitnessFunction(configuration.Limits->size(), interpolated) + Pop->GetConfiguration().EPSILON);
		else
			Status.Fitness() = fitnessFunction(configuration.Limits->size(), interpolated);
		
		//Configura sexo de acordo com bit mais significativo
		ARS_SetSex(this);//Status.Sex() = (DNA[0]->Higher()[0] + DNA[0]->Higher()[population.GetConfiguration().DNACodificationSize - 1]) % 2;
	}

	Behavior = NULL;//&ARS_BehaviorBank::getInstance().GetRandomBehavior(MALE);
	
	//Referencia para grafo de cena =)
	Status.SetParent(this);
}
//------------------------------------------------------------------------------------------------
ARS_Being::~ARS_Being(void){
}
//------------------------------------------------------------------------------------------------
void ARS_Being::SetDNA(int Index, ARS_Bin* Dna){
	if((unsigned)Index > DNA.size())
		return;

	if(DNA[Index] != 0x0){
		delete DNA[Index];
		DNA[Index] = 0x0;
	}

	DNA[Index] = Dna;
}

void ARS_Being::ResetStatus(){
		ARS_PopulationConfig& conf = Pop->GetConfiguration();
		Status.BreedingAge() = conf.BreedingAge;
		Status.Generation() = Pop->CurrentGeneration() + 1;
		Status.LifeTime() = 0.0;
		
		Status.MaxBreeding() = 0;

		Status.OldAge() = conf.OldAge;

		Status.State() = ARS_CHILD;
		
		CurrentProposal.clear();
	}
