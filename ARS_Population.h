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

#ifndef ARS_POPULATION_H
#define ARS_POPULATION_H
//------------------------------------------------------------------------------------------------
//ARS_COMMENTS::SYSTEM INCLUDES
//------------------------------------------------------------------------------------------------
#include <vector>


//------------------------------------------------------------------------------------------------
//ARS_COMMENTS::INTERNAL INCLUDE
//------------------------------------------------------------------------------------------------
#include "ARS_Being.h"
#include "ARS_PopulationConfig.h"
#include "ARS_BehaviorBank.h"
#include "Defaults.h"
#include "CTimer.h"
#include "ARS_EventManager.h"

#include <limits>
//------------------------------------------------------------------------------------------------
//ARS_COMMENTS::USED NAMESPACES
//------------------------------------------------------------------------------------------------
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

//CLASSE UTILIZADA PARA SEPARAR OS INDIVÍDUOS DE UMA POPULAÇÃO
class ARS_PopulationHolder{
public:
	ARS_PopulationHolder(void){}
	~ARS_PopulationHolder(void){}

	vector<ARS_Being*> high;
	vector<ARS_Being*> medium;
	vector<ARS_Being*> low;
	vector<ARS_Being*> all;
};

//CLASSE UTILIZADA PARA GUARDAR ESTATÍSTICAS DA POPULAÇÃO
class ARS_PopulationStatus{
public:
	ARS_PopulationStatus(void){
		maleCount   = 0;
		femaleCount = 0;
		beingsCount = 0;

		fitnessSum       = 0.0;
		meanFitness      = 0.0;
		maxFitness       = 0.0;

		double maxDouble = pow(2.0, (double)sizeof(double)*8) - 1;

		minFitness       = maxDouble;
		minFitnessMale   = maxDouble;
		minFitnessFemale = maxDouble;

		maxFitnessMale   = 0.0;
		meanFitnessMale  = 0.0;
		fitnessSumMale   = 0.0;

		maxFitnessFemale  = 0.0;
		meanFitnessFemale = 0.0;
		fitnessSumFemale  = 0.0;

		deadMales   = 0;
		deadFemales = 0;
		dead        = 0;

		_MaxFitnessBeing  = NULL;
		_MaxFitnessFemale = NULL;
		_MaxFitnessMale   = NULL;
		_MinFitness       = NULL;
		_MinFitnessMale   = NULL;
		_MinFitnessFemale = NULL;
	}

	~ARS_PopulationStatus(void){}

	//Machos
	double             maxFitnessMale;
	double			   meanFitnessMale;
	double             fitnessSumMale;

	//Femea
	double             maxFitnessFemale;
	double			   meanFitnessFemale;
	double             fitnessSumFemale;

	//Geral
	double             fitnessSum;
	double             meanFitness;
	double			   maxFitness; 
	double			   minFitness;
	double			   minFitnessMale;
	double			   minFitnessFemale;

	//Contagem
	int				   maleCount;
	int				   femaleCount;
	int                beingsCount;

	int	deadMales;
	int	deadFemales;
	int dead;

	ARS_Being*		   _MaxFitnessBeing ;
	ARS_Being*         _MaxFitnessFemale;
	ARS_Being*		   _MaxFitnessMale  ;
	ARS_Being*         _MinFitness      ;
	ARS_Being*		   _MinFitnessMale  ;
	ARS_Being*         _MinFitnessFemale;
};

class ARS_Population
{
public:
	//CONSTRUTOR PADRAO DE UMA POPULAÇÃO
	//CTimer _popTimer;

	//Fazer a cópia neste caso não importa
	ARS_Population(ARS_PopulationConfig& Config);

	~ARS_Population(void);

	int              GetSize();
	int				 GenBeing(){
		int ret = curID;
		curID++;
		return ret;};

		double&           FitnessSum();
		double&           MeanFitness();
		double&           MaxFitness();
		double&           YearTimer();
		double&           HourTimer();
		double&           SecondsTimer();
		int&              MaxGeneration(){return maxGeneration;}
		int&              LowerGeneration();
		int			      CurrentGeneration(){return currentGeneration;}

		ARS_PopulationStatus& Statistics(){return GlobalStatistics;}

		virtual void     initialize();

		//Configura comportamento de acordo com o status atual da população
		void			 ConfigureBehavior(ARS_Being& being);

		void			ConfigureAgeLimiar(ARS_Being& being);

		//Deve ser calculado na hora de inserir o indivíduo para evitar problemas futuros
		void DynamicLimiarUpdate();

		void ConfigureGlobalStatistics(ARS_Being* being, int generation);

		void ConfigureLocalStatistics(ARS_Being* being, int generation);

		void ConfigureAndInsert(ARS_Being* being, int generation, bool front = false);

		//FUNÇÃO MAIS IMPORTANTE DO PROGRAMA
		//----------------------------------
		//É RESPONSÁVEL POR INSERIR OS INDIVÍDUOS NA POPULAÇÃO
		//CALCULA IDADE E CONFIGURA TODOS OS PARAMETROS
		void             InsertBeing(ARS_Being* being, int generation = -1, bool front = false);

		void             KillBeing(ARS_Being* being);
		void             KillAllBeings(int generation);

		//Compara dois valores de geração de indivíduos para atualizar geração atual da população
		void             UpdateGeneration(int& compA, int& compB);
		void             Evolution();

		ARS_PopulationConfig& GetConfiguration(){return *Configuration;}

		ARS_PopulationStatus& GetCurrentPopStatus(){return population[currentGeneration].first;}

		ARS_PopulationStatus& GetPopulationStatus(int gen){return population[gen].first;}

		vector<ARS_PopulationStatus*>& GetStatusVector(){return AllGenerationsStatus;}

		ARS_PopulationHolder& GetPopulationHolder(int gen, int sex){return population[gen].second[sex];}

		//PARA OPERAÇÕES DE SELEÇÃO
		//chave para pesquisa
		//geração - sexo - indivíduos
		map<int,pair<ARS_PopulationStatus, map<int,ARS_PopulationHolder>>>& GetPopulation(){return population;}

		ARS_EventManager<void>& getGenIncreaseEM(){return GenerationIncreaseEvents;}

		ARS_EventManager<void>& getFitMaxIncreaseEM(){return MaxFitnessIncrease;}

		void setFitnessFunction(int ID);

		void clearCurrentPopData(){
			ARS_PopulationStatus& status = population[currentGeneration].first;
			status.beingsCount       = 0;
			status.femaleCount       = 0;
			status.fitnessSum        = 0.0;
			status.fitnessSumFemale  = 0.0;
			status.fitnessSumMale    = 0.0;
			status.maleCount         = 0;
			status.maxFitness        = 0.0;
			status.maxFitnessFemale  = 0.0;
			status.maxFitnessMale    = 0.0;
			status.meanFitness       = 0.0;
			status.meanFitnessFemale = 0.0;
			status.meanFitnessMale   = 0.0;
			status.minFitness        = 0.0;
			status.minFitnessFemale  = 0.0;
			status.minFitnessMale    = 0.0;
			status._MaxFitnessBeing  = NULL;
			status._MaxFitnessFemale = NULL;
			status._MaxFitnessMale   = NULL;
			status._MinFitness       = NULL;
			status._MinFitnessFemale = NULL;
			status._MinFitnessMale   = NULL;
		}

		void clearGlobalData(){
			GlobalStatistics.beingsCount       = 0;
			GlobalStatistics.femaleCount       = 0;
			GlobalStatistics.fitnessSum        = 0.0;
			GlobalStatistics.fitnessSumFemale  = 0.0;
			GlobalStatistics.fitnessSumMale    = 0.0;
			GlobalStatistics.maleCount         = 0;
			GlobalStatistics.maxFitness        = 0.0;
			GlobalStatistics.maxFitnessFemale  = 0.0;
			GlobalStatistics.maxFitnessMale    = 0.0;
			GlobalStatistics.meanFitness       = 0.0;
			GlobalStatistics.meanFitnessFemale = 0.0;
			GlobalStatistics.meanFitnessMale   = 0.0;
			GlobalStatistics.minFitness        = 0.0;
			GlobalStatistics.minFitnessFemale  = 0.0;
			GlobalStatistics.minFitnessMale    = 0.0;
			GlobalStatistics._MaxFitnessBeing  = NULL;
			GlobalStatistics._MaxFitnessFemale = NULL;
			GlobalStatistics._MaxFitnessMale   = NULL;
			GlobalStatistics._MinFitness       = NULL;
			GlobalStatistics._MinFitnessFemale = NULL;
			GlobalStatistics._MinFitnessMale   = NULL;
		}

private:
	//PARA TEMPORIZAR
	CTimer _popTimer;

	//CONFIGURAÇÇÕES GERAIS DA POPULAÇÃO
	ARS_PopulationConfig* Configuration;

	vector<ARS_PopulationStatus*> AllGenerationsStatus;

	//VARIAVEIS DE CONTROLE
	map<int,pair<ARS_PopulationStatus, map<int,ARS_PopulationHolder>>> population;

	//ESTATÍSTICAS GLOBAIS
	ARS_PopulationStatus GlobalStatistics;

	//CONTADOR DE TEMPO UTILIZADO PARA CONTAR AS ERAS JÁ PASSADAS DURANTE A EVOLUÇÃO
	//PODE SER UTILIZADO COMO TIMELINE
	double			   yearTimer;

	//PROTOTIPO - PODEM SER UTILIZADOS PARA UMA MEDIDA MAIS PRECISA DE TEMPO CASO SEJA NECESSÁRIO
	double hourTimer;
	double secondsTimer;
	double DynamicMutationTimer;// = 0.0;
	double MutationDisablerTimer;
	double InverseMutationDisablerTimer;
	double OriginalMutationRate;
	bool MutationDisabled;
	double previousMaxFitness; // para mutation disabler event

	//PARA CONTROLE DE EXECUÇÃO
	int maxGeneration; 
	ARS_Being* _MaxGeneration;

	int lowerGeneration; 
	ARS_Being* _LowerGeneration;

	//ID generator
	int				   curID;

	int currentGeneration;
	int beingsUpdateCountMale;
	int beingsUpdateCountFemale;
	int currentUpdateCount;

	//double updateSleep;
	//double sleep;

	ARS_EventManager<void> GenerationIncreaseEvents;
	ARS_EventManager<void> MaxFitnessIncrease;
};
#endif

