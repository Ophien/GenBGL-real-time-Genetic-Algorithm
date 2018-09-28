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
#include "ARS_Population.h"
#include "ARS_Operations.h"

//------------------------------------------------------------------------------------------------
//ARS_COMMENTS::USED NAMESPACES
//------------------------------------------------------------------------------------------------
using namespace std;
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

//------------------------------------------------------------------------------------------------
ARS_Population::ARS_Population(ARS_PopulationConfig& Config)
{
	//PARA CONTROLE DE EXECUÇÃO
	maxGeneration   = 0;
	lowerGeneration = 0;

	Configuration = &Config;

	//Inicializando timers
	yearTimer    = 0.0;
	hourTimer    = 0.0;
	secondsTimer = 0.0;

	//Define qual geração irá atualizar
	currentGeneration = 0;

	//Inicializando ID generator
	curID = 0;

//	updateSleep = 0.1;
//	sleep = 0.0;
	beingsUpdateCountMale = 0;
	beingsUpdateCountFemale = 0;
	currentUpdateCount = 0;

	InverseMutationDisablerTimer = 0.0;

	MutationDisabled = false;
}
//------------------------------------------------------------------------------------------------
ARS_Population::~ARS_Population(void)
{
}
//------------------------------------------------------------------------------------------------
void ARS_Population::initialize(){
	//PRINTF PARA DEBUG
	printf("Gerando pop inicial...\n");

	//ARS_COMMENTS::CRIA POPULAÇÃO INICIAL
	for(int i = 0; i < Configuration->InicialPopulationSize; i++){
		//Fitness é calculado aqui dentro
		ARS_Being* new_born = new ARS_Being(*this);
		InsertBeing(new_born);
	}	

	//ARS_COMMENTS::TODO::O TIMER DEVE SER CONTROLADO EXTERNAMENTE
	_popTimer.Init();

	//Insere a gen original
	AllGenerationsStatus.push_back(&GetCurrentPopStatus());

	GenerationIncreaseEvents.CallEvents(NULL);

	DynamicMutationTimer = 0.0;

	printf("Pop inicial gerada com sucesso...\n");

}
//------------------------------------------------------------------------------------------------
void ARS_Population::Evolution(){
	//ARS_COMMENTS::EXECUTA ATÉ GERAÇÃO MÁXIMA SER ENCONTRADA
	int& MAX          = Configuration->TotalGenerations;
	int& UPDATE_DEPTH = Configuration->UpdateDepth;

	//para testes
	//unsigned long long int ITERATIONS_COUNT = 0;

	//printf("Executando...\n");

	//Percorre range de atualização de gerações
	if(maxGeneration < MAX){
		if(GlobalStatistics.beingsCount >= 300000)
			maxGeneration = MAX + 10;

		//Atualiza temporizador
		_popTimer.Update();
		double timer = _popTimer.GetElapsedSeconds();

		//Configura mutação dinâmica aqui
		if(Configuration->DynamicMutation){
			if(DynamicMutationTimer >= Configuration->DynamicMutationCycle){
				increaseMutationRotation(Configuration->MutationMethod, 3);
				DynamicMutationTimer = 0.0;
			}
			DynamicMutationTimer += timer;
		}

		
		if(Configuration->MutationDisabler){
			if(!MutationDisabled){
				//Mutation disabler event
				double CurrentPopMaxFitness = GetCurrentPopStatus().maxFitness;
				if(std::abs(previousMaxFitness-CurrentPopMaxFitness)<2.0*std::numeric_limits<double>::epsilon()){
					MutationDisablerTimer += timer;
				}else{
					MutationDisablerTimer = 0.0;
				}

				if(MutationDisablerTimer >= Configuration->MutationDisablerCycle){
					OriginalMutationRate			   = Configuration->MutationProbability;
					Configuration->MutationProbability = 0.0;
					InverseMutationDisablerTimer       = 0.0;
					MutationDisabled = true;
				}
			}
		}

		if(MutationDisabled){
			if(InverseMutationDisablerTimer >= Configuration->InverseMutDisableCycle){
				MutationDisabled				   = false;
				MutationDisablerTimer			   = 0.0;
				Configuration->MutationProbability = OriginalMutationRate;
			}

			InverseMutationDisablerTimer += timer;
		}
		
		previousMaxFitness = GetCurrentPopStatus().maxFitness;
		//Calculando quantidade de iterações que devem ser feitas para atualizar a população.
		//int delta = maxGeneration - UPDATE_DEPTH;

		//Garantir que não tente acessar elementos inválidos
		//if(delta <= 0)
		//	delta = maxGeneration;

		//Vai para proxima geração apenas quando preencher a mesma completamente
		if(population[currentGeneration+1].first.beingsCount >= Configuration->InicialPopulationSize){
			//ELETISMO AQUI EVENTO PRINCIPAL
			if(Configuration->Eletism){
				ARS_Being* maxBeing = GlobalStatistics._MaxFitnessBeing;
				maxBeing->ResetStatus();
				InsertBeing(maxBeing, -1, true);

				//maxBeing = GlobalStatistics._MaxFitnessFemale;
				//maxBeing->ResetStatus();
				//InsertBeing(maxBeing, -1, true);
			}

			currentGeneration++;

			//Insere nova gen
			AllGenerationsStatus.push_back(&GetCurrentPopStatus());

			GenerationIncreaseEvents.CallEvents(NULL);
			//Configuration->InicialPopulationSize+=50;
		}

		//Atualiza os indivíduos de todas as gerações dentro da janela de atualização
		//for(int i = maxGeneration; i >= delta; i--){
		//Percorre todos os indivíduos machos e atualiza
		//O(n)
		ARS_PopulationHolder& malePopulation = population[currentGeneration].second[MALE];
		int maleSize = malePopulation.all.size();
		//double updateTimer = 0.0;

		//#pragma omp parallel for
		for(beingsUpdateCountMale; beingsUpdateCountMale < maleSize; beingsUpdateCountMale++, currentUpdateCount++)
		{
			malePopulation.all[beingsUpdateCountMale]->Behave(timer);
		
			//updateTimer += _popTimer.GetElapsedSeconds();

			if(currentUpdateCount >= Configuration->maxUpdatesPerFrame)
				break;

			//if(updateTimer >= 0.3)
			//	break;
		}

		//Percorre todos os indivíduos femeas e atualiza
		//O(n)
		ARS_PopulationHolder& femalePopulation = population[currentGeneration].second[FEMALE];
		int femaleSize = femalePopulation.all.size();

		//updateTimer = 0.0;

		//#pragma omp parallel for
		for(beingsUpdateCountFemale; beingsUpdateCountFemale < femaleSize; beingsUpdateCountFemale++, currentUpdateCount++)
		{
			femalePopulation.all[beingsUpdateCountFemale]->Behave(timer);
		
			//updateTimer += _popTimer.GetElapsedSeconds();
			
			if(currentUpdateCount >= Configuration->maxUpdatesPerFrame)
				break;

			//if(updateTimer >= 0.3)
			//	break;
		}

		if(beingsUpdateCountFemale >= femaleSize && beingsUpdateCountMale >= maleSize){
			beingsUpdateCountFemale = 0;
			beingsUpdateCountMale   = 0;
		}

		if(currentUpdateCount>=Configuration->maxUpdatesPerFrame)
			currentUpdateCount=0;

		//Verificar lista de mortos e colher o que for necessário
		//}//fim for gerações

		//TESTE
		//ITERATIONS_COUNT++;
		/*printf("------------------ COUNT --------\nB. Count: %i D. females: %i D. males: %i\n------------------ Fmed, fMax ---\nG. FMax: %f G. FMed: %f\n", 
		GlobalStatistics.beingsCount, 
		GlobalStatistics.deadFemales, 
		GlobalStatistics.deadMales,
		GlobalStatistics.maxFitness,
		GlobalStatistics.meanFitness);*/
	}//fim while max
	//printf("Terminado com sucesso...\n");
}
//------------------------------------------------------------------------------------------------
//Configura comportamento de acordo com o status atual da população
void			 ARS_Population::ConfigureBehavior(ARS_Being& being){
	int& sex = being.GetStatus().Sex();
	ARS_BehaviorBank& bBank = ARS_BehaviorBank::getInstance();

	if(sex == MALE){
		being.SetBehavior(bBank.GetRandomBehavior(sex));
	}else{
		being.SetBehavior(bBank.GetRandomBehavior(sex));
	}
}
//------------------------------------------------------------------------------------------------
void			ARS_Population::ConfigureAgeLimiar(ARS_Being& being){
	ARS_BeingStatus& status = being.GetStatus();
	status.setBreedingAge(Configuration->BreedingAge);
	status.setOldAge(Configuration->OldAge);
}
//------------------------------------------------------------------------------------------------
//Deve ser calculado na hora de inserir o indivíduo para evitar problemas futuros
void ARS_Population::DynamicLimiarUpdate(){
	Configuration->highLimiar = GlobalStatistics.meanFitness * Configuration->highLimiarThreshold;
	Configuration->lowLimiar  = GlobalStatistics.meanFitness * Configuration->lowLimiarThreshold;
}
//------------------------------------------------------------------------------------------------
void ARS_Population::ConfigureGlobalStatistics(ARS_Being* being, int generation){
	int& sex        = being->GetStatus().Sex();
	double& fitness = being->GetStatus().Fitness();

	//----------------------------------CALCULANDO ESTATÍSTICAS GLOBAIS---------------
	GlobalStatistics.fitnessSum           += fitness;

	if(fitness > GlobalStatistics.maxFitness){
		GlobalStatistics.maxFitness       = fitness;
		GlobalStatistics._MaxFitnessBeing = being;

		//Chama eventos de crescimento de max aqui
		MaxFitnessIncrease.CallEvents(NULL);
	}

	if(fitness <= GlobalStatistics.minFitness){
		GlobalStatistics.minFitness = fitness;
		GlobalStatistics._MaxFitnessBeing = being;
	}

	GlobalStatistics.beingsCount++;

	double UniversalMean = GlobalStatistics.fitnessSum / GlobalStatistics.beingsCount;
	GlobalStatistics.meanFitness = UniversalMean;

	if(sex == MALE){
		//Contagem
		GlobalStatistics.maleCount++;

		//Configurando estatisticas para femeas
		GlobalStatistics.fitnessSumMale   += fitness;

		//Configurando máximo
		if(fitness > GlobalStatistics.maxFitnessMale){
			GlobalStatistics.maxFitnessMale  = fitness;
			GlobalStatistics._MaxFitnessMale = being;
		}

		if(fitness <= GlobalStatistics.minFitnessMale){
			GlobalStatistics.minFitnessMale = fitness;
			GlobalStatistics._MinFitnessMale = being;
		}

		//Calculando média para fémeas
		GlobalStatistics.meanFitnessMale = GlobalStatistics.fitnessSumMale / GlobalStatistics.maleCount;
	}else{
		//Contagem
		GlobalStatistics.femaleCount++;

		//Configurando estatisticas para os machos
		GlobalStatistics.fitnessSumFemale += fitness;

		//Configurando máximo
		if(fitness > GlobalStatistics.maxFitnessFemale){
			GlobalStatistics.maxFitnessFemale  = fitness;
			GlobalStatistics._MaxFitnessFemale = being;
		}

		if(fitness <= GlobalStatistics.minFitnessFemale){
			GlobalStatistics.minFitnessFemale = fitness;
			GlobalStatistics._MinFitnessFemale = being;
		}

		//Calculando média para fémeas
		GlobalStatistics.meanFitnessFemale = GlobalStatistics.fitnessSumFemale / GlobalStatistics.femaleCount;
	}
	//----------------------------------CALCULANDO ESTATÍSTICAS GLOBAIS---------------
}
//------------------------------------------------------------------------------------------------
void ARS_Population::ConfigureLocalStatistics(ARS_Being* being, int generation){
	if(generation < 0 )
		generation = being->GetStatus().Generation();

	int& sex        = being->GetStatus().Sex();
	double& fitness = being->GetStatus().Fitness();

	//----------------------------------CALCULANDO ESTATÍSTICAS LOCAIS---------------
	//Calcula novos valores para atual geração
	ARS_PopulationStatus& _CurGenSts = population[generation].first;
	_CurGenSts.fitnessSum           += fitness;

	if(fitness > _CurGenSts.maxFitness){
		//for(int i = 0; i < being->GetDNA().size(); i++){
		//	printf("X%i: %f  ",i, being->IDecimalArray()[i]);
		//}
		//printf("\n");

		_CurGenSts.maxFitness       = fitness;
		_CurGenSts._MaxFitnessBeing = being;
	}

	if(fitness <= _CurGenSts.minFitness){
		_CurGenSts.minFitness = fitness;
		_CurGenSts._MaxFitnessBeing = being;
	}

	//Calculando nova média dinamicamente, popSize = machos + femeas
	ARS_PopulationHolder& popHolderMale = population[generation].second[ARS_MALE];
	int maleSize = popHolderMale.all.size();

	ARS_PopulationHolder& popHolderFemale = population[generation].second[ARS_FEMALE];
	int femaleSize = popHolderMale.all.size();

	int popSize = _CurGenSts.beingsCount;
	_CurGenSts.meanFitness = _CurGenSts.fitnessSum / popSize;

	if(sex == 1){
		//Configurando estatisticas para femeas
		_CurGenSts.fitnessSumMale   += fitness;

		//Configurando máximo
		if(fitness > _CurGenSts.maxFitnessMale){
			_CurGenSts.maxFitnessMale  = fitness;
			_CurGenSts._MaxFitnessMale = being;
		}

		if(fitness <= _CurGenSts.minFitnessMale){
			_CurGenSts.minFitnessMale = fitness;
			_CurGenSts._MinFitnessMale = being;
		}

		//Calculando média para fémeas
		ARS_PopulationHolder& popHolder = population[generation].second[sex];
		int size = popHolder.all.size();
		_CurGenSts.meanFitnessMale = _CurGenSts.fitnessSumMale / size;
	}else{
		//Configurando estatisticas para os machos
		_CurGenSts.fitnessSumFemale += fitness;

		//Configurando máximo
		if(fitness > _CurGenSts.maxFitnessFemale){
			_CurGenSts.maxFitnessFemale  = fitness;
			_CurGenSts._MaxFitnessFemale = being;
		}

		if(fitness <= _CurGenSts.minFitnessFemale){
			_CurGenSts.minFitnessFemale = fitness;
			_CurGenSts._MinFitnessFemale = being;
		}

		//Calculando média para fémeas
		ARS_PopulationHolder& popHolder = population[generation].second[sex];
		int size = popHolder.all.size();
		_CurGenSts.meanFitnessFemale = _CurGenSts.fitnessSumFemale / size;
	}
	//----------------------------------CALCULANDO ESTATÍSTICAS LOCAIS---------------
}
//------------------------------------------------------------------------------------------------
void ARS_Population::ConfigureAndInsert(ARS_Being* being, int generation, bool front){
	//----------------------------------CONFIGURANDO SER-----------------------------
	//Insere indivíduo na respectiva geração e sexo
	if(generation < 0 )
		generation = being->GetStatus().Generation();

	int& sex        = being->GetStatus().Sex();
	double& fitness = being->GetStatus().Fitness();

	//Configura população atual
	being->SetPopulation(this);

	//Configura idade
	ConfigureAgeLimiar(*being);

	//Configurar comportamento aqui
	ConfigureBehavior(*being);

	if(generation > maxGeneration)
		maxGeneration = generation;

	vector<ARS_Being*> newVector;
	newVector.push_back(being);

	//Configura em qual parte da população o 'ser' deve pertencer
	if(fitness > Configuration->highLimiar){
		if(front)
			population[generation].second[sex].high.insert(population[generation].second[sex].high.begin(), newVector.begin(), newVector.end());
		else
			population[generation].second[sex].high.push_back(being);
	}else if(fitness > Configuration->lowLimiar){
		if(front)
			population[generation].second[sex].medium.insert(population[generation].second[sex].medium.begin(), newVector.begin(), newVector.end());
		else
			population[generation].second[sex].medium.push_back(being);
	}else{
		if(front)
			population[generation].second[sex].low.insert(population[generation].second[sex].low.begin(), newVector.begin(), newVector.end());
		else
			population[generation].second[sex].low.push_back(being);
	}

	//Insere no geral para facilitar operações futuras
	if(front)
		population[generation].second[sex].all.insert(population[generation].second[sex].all.begin(), newVector.begin(), newVector.end());
	else
		population[generation].second[sex].all.push_back(being);

	if(sex == MALE)
		population[generation].first.maleCount++;
	else
		population[generation].first.femaleCount++;

	//Contagem
	population[generation].first.beingsCount++;
	//----------------------------------CONFIGURANDO SER-----------------------------
}
//------------------------------------------------------------------------------------------------
//FUNÇÃO MAIS IMPORTANTE DO PROGRAMA
//----------------------------------
//É RESPONSÁVEL POR INSERIR OS INDIVÍDUOS NA POPULAÇÃO
//CALCULA IDADE E CONFIGURA TODOS OS PARAMETROS
void ARS_Population::InsertBeing(ARS_Being* being, int generation, bool front){
	//	if(population[maxGeneration].first.beingsCount >= Configuration->InicialPopulationSize)
	//		return;

	//Configure e insere o ser
	ConfigureAndInsert(being, generation, front);

	//Estatísticas locais
	ConfigureLocalStatistics(being, generation);

	//Estatísticas globais
	ConfigureGlobalStatistics(being, generation);

	//Configura novo limiar
	DynamicLimiarUpdate();
}
//------------------------------------------------------------------------------------------------
void ARS_Population::KillAllBeings(int generation){
		clearCurrentPopData();

		ARS_PopulationHolder& malePopulation = population[generation].second[MALE];
		int maleSize = malePopulation.all.size();
		ARS_PopulationHolder& femalePopulation = population[generation].second[FEMALE];
		int femaleSize = femalePopulation.all.size();

		while(malePopulation.all.size() > 0)
			malePopulation.all.pop_back();

		while(femalePopulation.all.size() > 0)
			femalePopulation.all.pop_back();

		//O(2n)

		malePopulation.high.clear();
		malePopulation.medium.clear();
		malePopulation.low.clear();

		femalePopulation.high.clear();
		femalePopulation.medium.clear();
		femalePopulation.low.clear();

		//UPDATE STATISTICS
		population[generation].first.dead        += maleSize + femaleSize;
		population[generation].first.deadMales   += maleSize;
		population[generation].first.deadFemales += femaleSize;

		GlobalStatistics.dead        += maleSize + femaleSize;
		GlobalStatistics.deadFemales += femaleSize;
		GlobalStatistics.deadMales   += maleSize;
}
