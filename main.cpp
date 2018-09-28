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

﻿//------------------------------------------------------------------------------------------------
//ARS_COMMENTS::SYSTEM INCLUDES
//------------------------------------------------------------------------------------------------
#include <iostream>
#include "ARS_Bin.h"
#include <bitset>
#include <stdio.h>
#include <dos.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

//------------------------------------------------------------------------------------------------
//ARS_COMMENTS::INTERNAL INCLUDE
//------------------------------------------------------------------------------------------------
#include "LimitH.h"
#include "ARS_Genetics.h"
#include "ARS_BehaviorBank.h"
#include "ARS_MaleBehavior.h"
#include "ARS_FemaleBehavior.h"
#include "Defaults.h"
#include "ARS_EventManager.h"
#include "ARS_Engine.h"
#include "OGLGraph.h"
#include "ARS_BenchmarkFunctions.h"
#include "ARS_MathHelper.h"
#include "ARS_Operations.h"

//------------------------------------------------------------------------------------------------
//ARS_COMMENTS::USED NAMESPACES
//------------------------------------------------------------------------------------------------
using namespace std;
using namespace ARS_Genetics;
using namespace ARS_BenchmarkFunctions;
using namespace ARS_MathHelper;
using namespace ARS_Operations;
using namespace LIMITS;
//------------------------------------------------------------------------------------------------
//ARS_COMMENTS::DEFINITIONS
//------------------------------------------------------------------------------------------------
#define margin       10
#define bMargin      25
#define space        5

#define MAX_MARGIN   10 // para plotar corretamente até o topo do máximo
#define MIN_MARGIN   10  // para plotar corretamente o minimo
#define RIGHT_MARGIN 20  // para plotar corretamente a largura

#define ASPECT_ZOOM 0.4

double ASPECT_ZOOM_H = 0.0;
int width            = 1280;
int height           = 720;
int minDeslocHelp    = 100;

//------------------------------------------------------------------------------------------------
//ARS_COMMENTS::MACROS
//------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------
//ARS_COMMENTS::CONSTANTS
//------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------
//ARS_COMMENTS::GLOBAL FUNCTIONS BODYS
//------------------------------------------------------------------------------------------------

//------------------GRAPH DEF---------------------------------------------------------------------
OGLGraph*       fMed;
OGLGraph*       gfMed;
OGLGraph*	    lfMax;
OGLGraph*       fMax;

//------------------GENETIC DEF-------------------------------------------------------------------
//ARS_Population*                   Pop;			//População para controle
//ARS_PopulationStatus              liveStatus;   //Status da ultima geração para facilitar visualização dos dados

//------------------CONTROL-----------------------------------------------------------------------
bool reset = false;

//------------------TWEAK BAR DEF-----------------------------------------------------------------
TwBar* Config;
TwBar* CurrentGenerationStatus;
TwBar* CurrentLimit;
TwBar* Generations;
TwBar* Statistics;
TwBar* LocalStatistics;
TwBar* Operations;
TwBar* Functions;

//------------------GLOBAL EVENTS MANAGERS--------------------------------------------------------
ARS_EventManager<void> LimitAddEvents;


//------------------OPERATION HELPERS-------------------------------------------------------------
int perturbationSize = 100;
int minDesloc        = 0;
vec2 GraphsTranslation;

//Para inserção de novos limites
double infLimit      = 0.0;
double supLimit		 = 0.0;
int    selectGen     = 0;

//------------------CONFIG DEF--------------------------------------------------------------------
int barsAlpha        = 150;

//------------------METHODS DEF HUD CONFIG--------------------------------------------------------
void setupWindowsSizes();
void DynamicConfigureGraphs();

//------------------METHODS DEF TWEAK BAR CONFIG--------------------------------------------------
void StatisticsBarSetup();
void LocalStatisticsBarSetup();
void ConfigBarSetup();
void OperationsBarSetup();
void SetupFunctionsBar();
void setupBarsBehavior();
void SetupAllGenerations();
void SetupCurrentLimits();
void generalBarsSetup();    //Configura todas as barras
void configureGeneralGenerations(int gen);

//------------------EVENTS CONFIGURATION----------------------------------------------------------
void configureAllEvents();

//------------------TWEAK CALLBACKS---------------------------------------------------------------
void TW_CALL ARS_InsertPerturbation(void *clientData);
void TW_CALL ARS_InsertLimit(void *clientData);
void TW_CALL ARS_RemoveLimit(void *clientData);
void TW_CALL SelectGen(void* clientData);
void TW_CALL SetFitnessFunc(void* clientData);
void TW_CALL SetCrossOverFunc(void* clientData);
void TW_CALL SetMutationFunc(void* clientData);
void TW_CALL RestartSimulation(void* clientData);
void TW_CALL SelectCustomGen(void* clientData);
void TW_CALL SetGraphsDimention(void* clientData);
void TW_CALL Minimization(void* clientData);
void TW_CALL Maximization(void* clientData);

//------------------METHODS DEF INTEGRITY CHECK---------------------------------------------------
void checkLimits();

//------------------GENERAL OPERATIONS METHODS----------------------------------------------------
void DynamicConfigureGraphs();
void init();							   //Inicializa todo o sistema
void Draw(double time);
void Update(double time);
int main(int argc, char* argv[]);          //main

//------------------------------------------------------------------------------------------------
void TW_CALL Minimization(void* clientData){
	Pop->GetConfiguration().Minimization = true;
	Pop->clearGlobalData();
	ARS_InsertPerturbation(clientData);
}
//------------------------------------------------------------------------------------------------
void TW_CALL Maximization(void* clientData){
	Pop->GetConfiguration().Minimization = false;
	Pop->clearGlobalData();
	ARS_InsertPerturbation(clientData);
}
//------------------------------------------------------------------------------------------------
void TW_CALL ARS_InsertPerturbation(void *clientData){
	//Mata todos antes de inserir a perturbação
	Pop->KillAllBeings(Pop->CurrentGeneration());   //Mata todos dessa geração
	Pop->KillAllBeings(Pop->CurrentGeneration()+1); //Mata todos que já foram gerados da próxima geração para evitar erros

	//Cria novo ser aleatória para inserir
	//O tratamento de limites e etc é feito automáticamente
	for(int i = 0; i < perturbationSize; i++){
		ARS_Being* new_born = new ARS_Being(*Pop);
		int gen = Pop->CurrentGeneration();
		new_born->GetStatus().Generation() = gen; 

		//Insere ser recem criado... o tamanho da população pode exceder por isso é uma perturbação
		Pop->InsertBeing(new_born, gen);
	}
}
//------------------------------------------------------------------------------------------------
void TW_CALL ARS_InsertLimit(void *clientData){
	limits->push_back(std::make_pair<double,double>(infLimit, supLimit));
	//deve adicionar uma perturbação para evitar engargalamento
	ARS_InsertPerturbation(clientData);
	LimitAddEvents.CallEvents(clientData);
}	
//------------------------------------------------------------------------------------------------
void TW_CALL ARS_RemoveLimit(void *clientData){
	limits->pop_back();
	ARS_InsertPerturbation(clientData);
	LimitAddEvents.CallEvents(clientData);
}
//------------------------------------------------------------------------------------------------
void TW_CALL SelectGen(void* clientData){
	int currentGen = reinterpret_cast<int>(clientData);
	configureGeneralGenerations(currentGen);
}
//------------------------------------------------------------------------------------------------
void FUNCTION_CHANGE_EVENT(int funcID){
	double max = pow(2.0,(int)sizeof(double))-1;
	switch(funcID){
	case ARS_CINTARIA:
				limits->clear();
				insertLimit(0,400);
				insertLimit(0,700);
				MaximizationE();
				break;
			case ARS_SAPATEIRO:
				limits->clear();
				insertLimit(0,3);
				insertLimit(0,5);
				MaximizationE();
				break;
			case ARS_DIETA:
				limits->clear();
				insertLimit(0,max);
				insertLimit(0,max);
				insertLimit(0,max);
				insertLimit(0,max);
				MinimizationE();
				break;
			case ARS_TRANSPORTE:
				limits->clear();
				insertLimit(0,max);
				insertLimit(0,max);
				insertLimit(0,max);
				insertLimit(0,max);
				insertLimit(0,max);
				insertLimit(0,max);
				MinimizationE();
				break;
			case ARS_REFINARIA:
				limits->clear();
				insertLimit(0,7857142.85);
				insertLimit(0,600000);
				insertLimit(0,125714285.6);
				MaximizationE();
				break;
			case ARS_FABRICAMOVEIS:
				limits->clear();
				insertLimit(0,20);
				insertLimit(0,20);
				MaximizationE();
				break;
			case ARS_FABRICAP1P2:
				limits->clear();
				insertLimit(0,40);
				insertLimit(0,30);
				MaximizationE();
				break;
	}
}
//------------------------------------------------------------------------------------------------
void TW_CALL SetFitnessFunc(void* clientData){
	int Function = reinterpret_cast<int>(clientData);
	Pop->GetConfiguration().FitnessFunction = Function;
	//ATUALIZA EVENTO DE TROCA DE FUNÇÃO
	FUNCTION_CHANGE_EVENT(Function);
	//Perturba a curva para melhor impácto na simulação
	ARS_InsertPerturbation(NULL);
}
//------------------------------------------------------------------------------------------------
void TW_CALL SelectCustomGen(void* clientData){
	int gen = reinterpret_cast<int>(clientData);
	if(gen == -1)
		configureGeneralGenerations(Pop->CurrentGeneration());
	else
		configureGeneralGenerations(selectGen);

	printf("----------------------------------------------------------\n");
	printf("Generation: %i\n", Pop->CurrentGeneration());
	for(int i = 0; i < limits->size(); i++){
		double currentRes = Pop->Statistics()._MaxFitnessBeing->IDecimalArray()[i];
		printf("X%i: %.5f\n", i, currentRes);
	}
	printf("----------------------------------------------------------\n");
}
//------------------------------------------------------------------------------------------------
void TW_CALL SetGraphsWidth(const void* value, void* clientData){
	width          = *(const int*)value;
	int bufferSize = width - RIGHT_MARGIN;
	int max        = (int)height  + MAX_MARGIN;
	//minDesloc      = (int)Pop->GetCurrentPopStatus().meanFitness + MIN_MARGIN; // para plotagem dinâmica

	fMed->Width()  = bufferSize;
	fMax->Width()  = bufferSize;
	lfMax->Width() = bufferSize;
	gfMed->Width() = bufferSize;
}
//------------------------------------------------------------------------------------------------
void TW_CALL GetGraphsWidth(void* value, void* clientData){
	*(int*)value = width;
}
//------------------------------------------------------------------------------------------------
void TW_CALL SetGraphsHeight(const void* value, void* clientData){
	height         = *(const int*)value;
	int max        = (int)height  + MAX_MARGIN;
	//minDesloc      = (int)Pop->GetCurrentPopStatus().meanFitness + MIN_MARGIN; // para plotagem dinâmica

	fMed->Height()  = height;
	fMax->Height()  = height;
	lfMax->Height() = height;
	gfMed->Height() = height;
}
//------------------------------------------------------------------------------------------------
void TW_CALL GetGraphsHeight(void* value, void* clientData){
	*(int*)value = height;
}
//------------------------------------------------------------------------------------------------
void TW_CALL SetGraphsZoom(const void* value, void* clientData){
	ASPECT_ZOOM_H   = *(const double*)value;
	//minDesloc      = (int)Pop->GetCurrentPopStatus().meanFitness + MIN_MARGIN; // para plotagem dinâmica

	fMed->Height()  *= ASPECT_ZOOM_H;
	fMax->Height()  *= ASPECT_ZOOM_H;
	lfMax->Height() *= ASPECT_ZOOM_H;
	gfMed->Height() *= ASPECT_ZOOM_H;
}
//------------------------------------------------------------------------------------------------
void TW_CALL GetGraphsZoom(void* value, void* clientData){
	*(double*)value = ASPECT_ZOOM_H;
}
//------------------------------------------------------------------------------------------------
void TW_CALL SetX(const void* value, void* clientData){
	GraphsTranslation.x   = *(const int*)value;
	//minDesloc      = (int)Pop->GetCurrentPopStatus().meanFitness + MIN_MARGIN; // para plotagem dinâmica
}
//------------------------------------------------------------------------------------------------
void TW_CALL GetX(void* value, void* clientData){
	*(int*)value = GraphsTranslation.x;
}
//------------------------------------------------------------------------------------------------
void TW_CALL SetY(const void* value, void* clientData){
	GraphsTranslation.y   = *(const int*)value;
}
//------------------------------------------------------------------------------------------------
void TW_CALL GetY(void* value, void* clientData){
	*(int*)value = GraphsTranslation.y;
}
//------------------------------------------------------------------------------------------------
void TW_CALL SetGraphsDimention(void* clientData){
	int bufferSize = width - RIGHT_MARGIN;

	fMed->Width()  = bufferSize;
	fMax->Width()  = bufferSize;
	lfMax->Width() = bufferSize;
	gfMed->Width() = bufferSize;

	fMed->Height()  = height;
	fMax->Height()  = height;
	lfMax->Height() = height;
	gfMed->Height() = height;

	fMed->Height()  *= ASPECT_ZOOM_H;
	fMax->Height()  *= ASPECT_ZOOM_H;
	lfMax->Height() *= ASPECT_ZOOM_H;
	gfMed->Height() *= ASPECT_ZOOM_H;
}
//------------------------------------------------------------------------------------------------
void TW_CALL SetCrossOverFunc(void* clientData){
	int crxCod = reinterpret_cast<int>(clientData);
	Pop->GetConfiguration().CrossoverFunction = crxCod;
}
//------------------------------------------------------------------------------------------------
void TW_CALL SetMutationFunc(void* clientData){
	int mutCod = reinterpret_cast<int>(clientData);
	Pop->GetConfiguration().MutationMethod = mutCod;
}
//------------------------------------------------------------------------------------------------
void ReDrawGraphs(){
	if(fMed!=0x0){
		delete fMed;
		fMed = 0x0;
	}

	if(fMax!=0x0){
		delete fMax;
		fMax = 0x0;
	}

	if(lfMax!=0x0){
		delete lfMax;
		lfMax = 0x0;
	}

	if(gfMed!=0x0){
		delete gfMed;
		gfMed = 0x0;
	}

//	GraphsTranslation.x = 0.0f;
//	GraphsTranslation.y = 0.0f;

	//ESSA PERTURBAÇÃO DEVE SER APLICADA PARA O TAMANHO DA POPULAÇÃO TOTAL
	ARS_InsertPerturbation(NULL);

	//Deve haver um deslocamento em Y de acordo com um vetor do mínmo para o máximo local
//	GraphsTranslation.x = 5;
//	GraphsTranslation.y = Pop->GetCurrentPopStatus().maxFitness - Pop->GetCurrentPopStatus().meanFitness;

	DynamicConfigureGraphs();
}
//------------------------------------------------------------------------------------------------
void TW_CALL RestartSimulation(void* clientData){
	reset = true;
}
//------------------------------------------------------------------------------------------------
void checkLimits(){
	if(Pop->GetConfiguration().InicialPopulationSize < 0)
		Pop->GetConfiguration().InicialPopulationSize = 0;
}
//------------------------------------------------------------------------------------------------
void setupWindowsSizes(){
	TwDefine("Config size      ='250 500'");
	TwDefine("Generations size ='250 400'");
	TwDefine("Statistics size  ='250 400'");
	TwDefine("LocalStatistics size  ='250 400'");
	TwDefine("Config size  ='250 400'");
	TwDefine("CustomGeneration size  ='250 400'");
}
//------------------------------------------------------------------------------------------------
void StatisticsBarSetup(){
	TwAddSeparator(Statistics, NULL, "group='Statistics'");
	TwAddSeparator(Statistics, NULL, "group='Count'");
	TwAddVarRO(Statistics, "mfm", TW_TYPE_DOUBLE, &Pop->Statistics().maxFitnessMale,     "label='Max Fitness Male' group='Statistics' ");
	TwAddVarRO(Statistics, "mff", TW_TYPE_DOUBLE, &Pop->Statistics().maxFitnessFemale,   "label='Max Fitness Female' group='Statistics' ");
	TwAddVarRO(Statistics, "mgf", TW_TYPE_DOUBLE, &Pop->Statistics().maxFitness,         "label='Max Global Fitness' group='Statistics' ");
	TwAddVarRO(Statistics, "mefm", TW_TYPE_DOUBLE, &Pop->Statistics().meanFitnessMale,   "label='Mean Fitness Male' group='Statistics' ");
	TwAddVarRO(Statistics, "meff", TW_TYPE_DOUBLE, &Pop->Statistics().meanFitnessFemale, "label='Mean Fitness Female' group='Statistics' ");
	TwAddVarRO(Statistics, "megf", TW_TYPE_DOUBLE, &Pop->Statistics().meanFitness,       "label='Mean Global Fitness' group='Statistics' ");
	TwAddVarRO(Statistics, "mifm", TW_TYPE_DOUBLE, &Pop->Statistics().minFitnessMale,    "label='Min Fitness Male' group='Statistics' ");
	TwAddVarRO(Statistics, "miff", TW_TYPE_DOUBLE, &Pop->Statistics().minFitnessFemale,  "label='Min Fitness Female' group='Statistics' ");
	TwAddVarRO(Statistics, "migf", TW_TYPE_DOUBLE, &Pop->Statistics().minFitness,        "label='Min Global Fitness Female' group='Statistics' ");
	TwAddVarRO(Statistics, "fsm", TW_TYPE_DOUBLE, &Pop->Statistics().fitnessSumMale,     "label='Fitness Sum Male' group='Statistics' ");
	TwAddVarRO(Statistics, "fsf", TW_TYPE_DOUBLE, &Pop->Statistics().fitnessSumFemale,   "label='Fitness Sum Female' group='Statistics' ");
	TwAddVarRO(Statistics, "fsg", TW_TYPE_DOUBLE, &Pop->Statistics().fitnessSum,         "label='Fitness Global Sum' group='Statistics' ");

	TwAddVarRO(Statistics, "Male Count"  , TW_TYPE_INT32, &Pop->Statistics().maleCount  , "group='Count' label='Male count'"); 
	TwAddVarRO(Statistics, "Female Count", TW_TYPE_INT32, &Pop->Statistics().femaleCount, "group='Count' label='Female count'"); 
	TwAddVarRO(Statistics, "Total Count" , TW_TYPE_INT32, &Pop->Statistics().beingsCount, "group='Count' label='Total count'"); 
	TwAddVarRO(Statistics, "Dead Males"  , TW_TYPE_INT32, &Pop->Statistics().deadMales  , "group='Count' label='Dead males'"); 
	TwAddVarRO(Statistics, "Dead Females", TW_TYPE_INT32, &Pop->Statistics().deadFemales, "group='Count' label='Dead females'"); 
	TwAddVarRO(Statistics, "Total deads" , TW_TYPE_INT32, &Pop->Statistics().dead       , "group='Count' label='Dead'"); 
}
//------------------------------------------------------------------------------------------------
void LocalStatisticsBarSetup(){
	TwAddSeparator(LocalStatistics, NULL, "group='Statistics'");
	TwAddSeparator(LocalStatistics, NULL, "group='Count'");
	TwAddVarRO(LocalStatistics, "mfm" , TW_TYPE_DOUBLE,  &liveStatus.maxFitnessMale   , "label='Max Fitness Male'    group='Statistics' ");
	TwAddVarRO(LocalStatistics, "mff" , TW_TYPE_DOUBLE,  &liveStatus.maxFitnessFemale , "label='Max Fitness Female'  group='Statistics' ");
	TwAddVarRO(LocalStatistics, "mgf" , TW_TYPE_DOUBLE,  &liveStatus.maxFitness       , "label='Max Global Fitness'  group='Statistics' ");
	TwAddVarRO(LocalStatistics, "mefm", TW_TYPE_DOUBLE,  &liveStatus.meanFitnessMale  , "label='Mean Fitness Male'   group='Statistics' ");
	TwAddVarRO(LocalStatistics, "meff", TW_TYPE_DOUBLE,  &liveStatus.meanFitnessFemale, "label='Mean Fitness Female' group='Statistics' ");
	TwAddVarRO(LocalStatistics, "megf", TW_TYPE_DOUBLE,  &liveStatus.meanFitness      , "label='Mean Global Fitness' group='Statistics' ");
	TwAddVarRO(LocalStatistics, "mifm", TW_TYPE_DOUBLE,  &liveStatus.minFitnessMale   , "label='Min Fitness Male'    group='Statistics' ");
	TwAddVarRO(LocalStatistics, "miff", TW_TYPE_DOUBLE,  &liveStatus.minFitnessFemale , "label='Min Fitness Female'  group='Statistics' ");
	TwAddVarRO(LocalStatistics, "migf", TW_TYPE_DOUBLE,  &liveStatus.minFitness       , "label='Min Global Fitness Female' group='Statistics' ");
	TwAddVarRO(LocalStatistics, "fsm" , TW_TYPE_DOUBLE,  &liveStatus.fitnessSumMale   , "label='Fitness Sum Male'    group='Statistics' ");
	TwAddVarRO(LocalStatistics, "fsf" , TW_TYPE_DOUBLE,  &liveStatus.fitnessSumFemale , "label='Fitness Sum Female'  group='Statistics' ");
	TwAddVarRO(LocalStatistics, "fsg" , TW_TYPE_DOUBLE,  &liveStatus.fitnessSum       , "label='Fitness Global Sum'  group='Statistics' ");

	TwAddVarRO(LocalStatistics, "Male Count", TW_TYPE_INT32,  &liveStatus.maleCount, "group='Count' label='Male count'"); 
	TwAddVarRO(LocalStatistics, "Female Count", TW_TYPE_INT32,  &liveStatus.femaleCount, "group='Count' label='Female count'"); 
	TwAddVarRO(LocalStatistics, "Total Count", TW_TYPE_INT32,  &liveStatus.beingsCount, "group='Count' label='Total count'"); 
	TwAddVarRO(LocalStatistics, "Dead Males", TW_TYPE_INT32,  &liveStatus.deadMales, "group='Count' label='Dead males'"); 
	TwAddVarRO(LocalStatistics, "Dead Females", TW_TYPE_INT32,  &liveStatus.deadFemales, "group='Count' label='Dead females'"); 
	TwAddVarRO(LocalStatistics, "Total deads", TW_TYPE_INT32,  &liveStatus.dead, "group='Count' label='Dead'"); 
}
//------------------------------------------------------------------------------------------------
void ConfigBarSetup(){
	TwAddSeparator(Config, NULL, "group='General'");
	TwAddVarRW(Config, "MaxPopulation" , TW_TYPE_INT32,  &Pop->GetConfiguration().InicialPopulationSize, "group='General' label='Population size'"); 
	TwAddVarRW(Config, "DnaSize"       , TW_TYPE_INT32,  &Pop->GetConfiguration().DNACodificationSize  , "group='General' label='DNA size'"); 
	TwAddVarRW(Config, "MutProb"       , TW_TYPE_DOUBLE, &Pop->GetConfiguration().MutationProbability  , "group='General' label='Mut. Prob.'");
	TwAddVarRW(Config, "BreedProb"     , TW_TYPE_DOUBLE, &Pop->GetConfiguration().BreedingProbability  , "group='General' label='Breed. Prob.'");
	TwAddVarRW(Config, "HighLimiar"    , TW_TYPE_DOUBLE, &Pop->GetConfiguration().highLimiar           , "group='General' label='High Limiar'");
	TwAddVarRW(Config, "LowLimiar"     , TW_TYPE_DOUBLE, &Pop->GetConfiguration().lowLimiar            , "group='General' label='Low Limiar'");
	TwAddVarRW(Config, "DualProposer"  , TW_TYPE_BOOL32, &Pop->GetConfiguration().DualProposal         , "group='General' label='Dual proposal'");
	TwAddVarRW(Config, "Eletism"       , TW_TYPE_BOOL32, &Pop->GetConfiguration().Eletism              , "group='General' label='Eletism'");
	TwAddVarRW(Config, "DMutationD"    , TW_TYPE_BOOL32, &Pop->GetConfiguration().MutationDisabler     , "group='General' label='Mutation disabler'");
	TwAddVarRW(Config, "DMutationDTimer", TW_TYPE_DOUBLE, &Pop->GetConfiguration().MutationDisablerCycle  , "group='General' label='D. mutation d. interval'");
	TwAddVarRW(Config, "DMutationDITimer",TW_TYPE_DOUBLE, &Pop->GetConfiguration().InverseMutDisableCycle , "group='General' label='D. mutation i. d. interval'");
	TwAddVarRW(Config, "DMutation"     , TW_TYPE_BOOL32, &Pop->GetConfiguration().DynamicMutation      , "group='General' label='Dynamic mutation'");
	TwAddVarRW(Config, "DMutationTimer", TW_TYPE_DOUBLE, &Pop->GetConfiguration().DynamicMutationCycle , "group='General' label='D. mutation interval'");
	TwAddButton(Config, "Minimization", Minimization, NULL, "group='General' label='Minimization'");
	TwAddButton(Config, "Maximization", Maximization, NULL, "group='General' label='Maximization'");
	TwAddSeparator(Config, NULL, "group='Breeding'");
	TwAddSeparator(Config, NULL, "group='Age'");
	TwAddVarRW(Config, "BreedAge"   , TW_TYPE_INT32, &Pop->GetConfiguration().BreedingAge     , "group='Age' label='Breeding age'"); 
	TwAddVarRW(Config, "BreedAgeSup", TW_TYPE_INT32, &Pop->GetConfiguration().BreedingAgeSup  , "group='Age' label='Breeding age sup.'"); 
	TwAddVarRW(Config, "BreedAgeInf", TW_TYPE_INT32, &Pop->GetConfiguration().BreedingAgeInf  , "group='Age' label='Breeding age inf.'"); 
	TwAddVarRW(Config, "OldAge"     , TW_TYPE_INT32, &Pop->GetConfiguration().OldAge          , "group='Age' label='Old age'"); 
	TwAddVarRW(Config, "OldAgeSup"  , TW_TYPE_INT32, &Pop->GetConfiguration().OldAgeSup       , "group='Age' label='Old age sup.'"); 
	TwAddVarRW(Config, "OldAgeInf"  , TW_TYPE_INT32, &Pop->GetConfiguration().OldAgeInf       , "group='Age' label='Old age inf.'");
	TwAddVarRW(Config, "MaxReproductionMale"     , TW_TYPE_INT32, &Pop->GetConfiguration().maleReproductionLimiar    , "group='Breeding' label='Max breeding male'"); 
	TwAddVarRW(Config, "MaxReproductionMaleSup"  , TW_TYPE_INT32, &Pop->GetConfiguration().maleRepLimiarSup          , "group='Breeding' label='Max breeding male sup.'"); 
	TwAddVarRW(Config, "MaxReproductionMaleInf"  , TW_TYPE_INT32, &Pop->GetConfiguration().maleRepLimiarInf          , "group='Breeding' label='Max breeding male inf.'"); 
	TwAddVarRW(Config, "MaxReproductionFemale"   , TW_TYPE_INT32, &Pop->GetConfiguration().femaleReproductionLimiar  , "group='Breeding' label='Max breeding female'"); 
	TwAddVarRW(Config, "MaxReproductionFemaleSup", TW_TYPE_INT32, &Pop->GetConfiguration().femaleRepLimiarSup        , "group='Breeding' label='Max breeding female sup.'"); 
	TwAddVarRW(Config, "MaxReproductionFemaleInf", TW_TYPE_INT32, &Pop->GetConfiguration().femaleRepLimiarInf        , "group='Breeding' label='Max breeding female inf.'"); 
	TwAddSeparator(Config, NULL, "group='Simulation Config'");
	TwAddVarRW(Config, "Max Updates per frame", TW_TYPE_INT32, &Pop->GetConfiguration().maxUpdatesPerFrame, "group='Simulation Config' label='Max Updates Per Frame'");
	TwAddVarRW(Config, "Gen. buffer size"     , TW_TYPE_INT32, &Pop->GetConfiguration().maxGenBuffer      , "group='Simulation Config' label='Gen. Buffer Size'");
	TwAddSeparator(Config, NULL, "group='Limits'");
	//TwAddSeparator(Config, NULL, "group='Current limits'"); //Não há necessidade
	TwAddVarRW(Config, "Inf."   , TW_TYPE_DOUBLE, &infLimit, "group='Limits' label='Inf. limit'");
	TwAddVarRW(Config, "Sup."   , TW_TYPE_DOUBLE, &supLimit, "group='Limits' label='Sup. limit'");
	TwAddButton(Config, "ADD"   , ARS_InsertLimit, NULL    , "group='Limits' label='Insert new Limit'");
	TwAddButton(Config, "REMOVE", ARS_RemoveLimit, NULL    , "group='Limits' label='Remove limit'");
	TwAddSeparator(Config, NULL, "group='Custom'");
	TwAddVarRW(Config , "Generation", TW_TYPE_INT32  , &selectGen  , "group='Custom' label='Custom ID'");
	TwAddButton(Config, "AddButton" , SelectCustomGen, NULL        , "group='Custom' label='Search'");
	TwAddButton(Config, "GetLast"   , SelectCustomGen, (void*)-1   , "group='Custom' label='Get last'");

	TwAddSeparator(Config, NULL, "group='Graphconfig'");
	TwAddVarCB(Config, "Width" , TW_TYPE_INT32, SetGraphsWidth, GetGraphsWidth, (void*)&width   , "group='Graphconfig' label='Width'");
	TwAddVarCB(Config, "Height", TW_TYPE_INT32, SetGraphsHeight, GetGraphsHeight, (void*)&height, "group='Graphconfig' label='Height'");
	//TwAddVarRW(Config, "Min", TW_TYPE_INT32, &minDeslocHelp, "group='Graph config' label='Min Desloc.'");
	TwAddVarCB(Config, "Zoom", TW_TYPE_DOUBLE,SetGraphsZoom, GetGraphsZoom, (void*)&ASPECT_ZOOM_H, "group='Graphconfig' label='Zoom.'");
	//TwAddButton(Config, "Apply", SetGraphsDimention, NULL, "group='Graph config' label='Apply'");
	TwAddVarCB(Config, "X", TW_TYPE_INT32, SetX, GetX, (void*)&GraphsTranslation.x, "group='Graphconfig' label='X'");
	TwAddVarCB(Config, "Y", TW_TYPE_INT32, SetY, GetY, (void*)&GraphsTranslation.y, "group='Graphconfig' label='Y'");
}
//------------------------------------------------------------------------------------------------
void SetupFunctionsBar(){
	TwAddSeparator(Functions, NULL, "group='Functions'");
	TwAddButton(Functions, "Sphere"          , SetFitnessFunc, (void*)ARS_SPHERE          , "group='Functions' label='Sphere'");
	TwAddButton(Functions, "Rosenbrock"      , SetFitnessFunc, (void*)ARS_ROSENBROCK      , "group='Functions' label='Rosenbrock'");
	TwAddButton(Functions, "DeJong Step"     , SetFitnessFunc, (void*)ARS_DEJONG_STEP     , "group='Functions' label='DeJong Step'");
	TwAddButton(Functions, "DeJong Step B"   , SetFitnessFunc, (void*)ARS_DEJONG_STEPB    , "group='Functions' label='DeJong Step B'");
	TwAddButton(Functions, "Shekels FoxHoles", SetFitnessFunc, (void*)ARS_SHEKELS_FOXHOLES, "group='Functions' label='Shekels FoxHoles'");
	TwAddButton(Functions, "Schaffer"        , SetFitnessFunc, (void*)ARS_SCHAFFER        , "group='Functions' label='Schaffer'");
	TwAddButton(Functions, "SchafferB"       , SetFitnessFunc, (void*)ARS_SCHAFFERB       , "group='Functions' label='SchafferB'");
	TwAddButton(Functions, "Sphere Model"    , SetFitnessFunc, (void*)ARS_SPHERE_MODEL    , "group='Functions' label='Sphere Model'");
	TwAddButton(Functions, "Schwefel"        , SetFitnessFunc, (void*)ARS_SCHWEFEL        , "group='Functions' label='Schwefel'");
	TwAddButton(Functions, "SchewefelB"      , SetFitnessFunc, (void*)ARS_SCHWEFELB       , "group='Functions' label='SchewefelB'");
	TwAddButton(Functions, "Ackley"          , SetFitnessFunc, (void*)ARS_ACKLEY          , "group='Functions' label='Ackley'");
	TwAddButton(Functions, "Rastrigin"       , SetFitnessFunc, (void*)ARS_RASTRIGIN       , "group='Functions' label='Rastrigin'");
	TwAddButton(Functions, "Griewangk"       , SetFitnessFunc, (void*)ARS_GRIEWANGK       , "group='Functions' label='Griewangk'");
	TwAddButton(Functions, "Schwefel Pro"    , SetFitnessFunc, (void*)ARS_SCHWEFEL_PRO    , "group='Functions' label='Schwefel Pro'");
	TwAddButton(Functions, "Bohachevsky"     , SetFitnessFunc, (void*)ARS_BOHACHEVSKY     , "group='Functions' label='Bohachevsky'");
	TwAddButton(Functions, "Cintaria"		 , SetFitnessFunc, (void*)ARS_CINTARIA        , "group='Functions' label='Cintaria'");
	TwAddButton(Functions, "Sapateiro"       , SetFitnessFunc, (void*)ARS_SAPATEIRO       , "group='Functions' label='Sapateiro'");
	TwAddButton(Functions, "Dieta"			 , SetFitnessFunc, (void*)ARS_DIETA           , "group='Functions' label='Dieta'");
	TwAddButton(Functions, "Transporte"      , SetFitnessFunc, (void*)ARS_TRANSPORTE      , "group='Functions' label='Transporte'");
	TwAddButton(Functions, "Refinaria"       , SetFitnessFunc, (void*)ARS_REFINARIA       , "group='Functions' label='Refinaria'");
	TwAddButton(Functions, "FabricaMoveis"   , SetFitnessFunc, (void*)ARS_FABRICAMOVEIS   , "group='Functions' label='Fabricamoveis'");
	TwAddButton(Functions, "FabricaP1P2"     , SetFitnessFunc, (void*)ARS_FABRICAP1P2     , "group='Functions' label='Fabricap1p2'");
	TwAddSeparator(Functions, NULL, "group='Breedingfunctions'");
	TwAddButton(Functions, "SinglePoint", SetCrossOverFunc, (void*)ARS_SINGLE_POINT_CROSS, "group='Breedingfunctions' label='Single point'");
	TwAddButton(Functions, "TwoPoint"   , SetCrossOverFunc, (void*)ARS_TWO_POINT_CROSS   , "group='Breedingfunctions' label='Two point'");
	TwAddButton(Functions, "MultiPoint" , SetCrossOverFunc, (void*)ARS_MULTI_POINT_CROSS , "group='Breedingfunctions' label='Multipoint'");
	TwAddButton(Functions, "Uniform"    , SetCrossOverFunc, (void*)ARS_UNIFORM_CROSS     , "group='Breedingfunctions' label='Uniform'");
	TwAddButton(Functions, "ThreeParent", SetCrossOverFunc, (void*)ARS_THREE_PARENT_CROSS, "group='Breedingfunctions' label='Threeparent point'");
	TwAddButton(Functions, "Shuffle"    , SetCrossOverFunc, (void*)ARS_SHUFFLE_CROSS     , "group='Breedingfunctions' label='Shuffle point'");
	TwAddButton(Functions, "PrecedencePreservative", SetCrossOverFunc, (void*)ARS_PRECEDENCE_PRESERVATIVE_CROSS, "group='Breedingfunctions' label='PPX point'");
	TwAddButton(Functions, "Ordered"    , SetCrossOverFunc, (void*)ARS_ORDERED_CROSS, "group='Breedingfunctions' label='Ordered point'");
	TwAddSeparator(Functions, NULL, "group='Mutation'");
	TwAddButton(Functions, "Fliping"      , SetMutationFunc, (void*)ARS_FLIPPING_MUT     , "group='Mutation' label='Flipping'");
	TwAddButton(Functions, "Interchanging", SetMutationFunc, (void*)ARS_INTERCHANGING_MUT, "group='Mutation' label='Interchanging'");
	TwAddButton(Functions, "Reversing"    , SetMutationFunc, (void*)ARS_REVERSING_MUT    , "group='Mutation' label='Reversing'");
}
//------------------------------------------------------------------------------------------------
void OperationsBarSetup(){
	TwAddSeparator(Operations, NULL, "group='Perturbation'");
	TwAddVarRW(Operations    , "Perturbation magnetidi", TW_TYPE_INT32         , &perturbationSize, "group='Perturbation' label='Magnetide'");
	TwAddButton(Operations   , "Add perturbation"      , ARS_InsertPerturbation, NULL             , "group='Perturbation' label='Add Perturbation'");
	TwAddSeparator(Operations, NULL, "group='Simulation'");
	TwAddButton(Operations, "Reset", RestartSimulation, NULL, "group='Simulation' label='ReDraw'");
}
//------------------------------------------------------------------------------------------------
void setupBarsBehavior(){
	TwDefine("Config                  color='0 0 0' alpha='150' valueswidth='100' resizable='true' iconified = 'true' movable = 'true' visible = 'true' refresh='0'");
	TwDefine("Generations             color='0 0 0' alpha='150' valueswidth='100' resizable='true' iconified = 'true' movable = 'true' visible = 'true' refresh='0'");
	TwDefine("Statistics              color='0 0 0' alpha='150' valueswidth='100' resizable='true' iconified = 'true' movable = 'true' visible = 'true' refresh='0'" );
	TwDefine("CustomGeneration        color='0 0 0' alpha='150' valueswidth='100' resizable='true' iconified = 'true' movable = 'true' visible = 'true' refresh='0'");
	TwDefine("Limits                  color='0 0 0' alpha='150' valueswidth='100' resizable='true' iconified = 'true' movable = 'true' visible = 'true' refresh='0'");
	TwDefine("LocalStatistics         color='0 0 0' alpha='150' valueswidth='100' resizable='true' iconified = 'true' movable = 'true' visible = 'true' refresh='0'");
	TwDefine("Operations              color='0 0 0' alpha='150' valueswidth='100' resizable='true' iconified = 'true' movable = 'true' visible = 'true' refresh='0'" );
	TwDefine("Functions               color='0 0 0' alpha='150' valueswidth='100' resizable='true' iconified = 'true' movable = 'true' visible = 'true' refresh='0'" );
	TwDefine("TW_HELP                 color='0 0 0' alpha='150' resizable='true' iconified ='true'");	
}
//------------------------------------------------------------------------------------------------
void configureGeneralGenerations(int gen){
	TwRemoveAllVars(CurrentGenerationStatus);

	TwAddSeparator(CurrentGenerationStatus, NULL, "group='Statistics'");
	TwAddSeparator(CurrentGenerationStatus, NULL, "group='Count'");
	TwAddVarRO(CurrentGenerationStatus, "mfm" , TW_TYPE_DOUBLE, &Pop->GetPopulationStatus(gen).maxFitnessMale,    "label='Max Fitness Male' group='Statistics' ");
	TwAddVarRO(CurrentGenerationStatus, "mff" , TW_TYPE_DOUBLE, &Pop->GetPopulationStatus(gen).maxFitnessFemale,  "label='Max Fitness Female' group='Statistics' ");
	TwAddVarRO(CurrentGenerationStatus, "mgf" , TW_TYPE_DOUBLE, &Pop->GetPopulationStatus(gen).maxFitness,        "label='Max Global Fitness' group='Statistics' ");
	TwAddVarRO(CurrentGenerationStatus, "mefm", TW_TYPE_DOUBLE, &Pop->GetPopulationStatus(gen).meanFitnessMale,   "label='Mean Fitness Male' group='Statistics' ");
	TwAddVarRO(CurrentGenerationStatus, "meff", TW_TYPE_DOUBLE, &Pop->GetPopulationStatus(gen).meanFitnessFemale, "label='Mean Fitness Female' group='Statistics' ");
	TwAddVarRO(CurrentGenerationStatus, "megf", TW_TYPE_DOUBLE, &Pop->GetPopulationStatus(gen).meanFitness,       "label='Mean Global Fitness' group='Statistics' ");
	TwAddVarRO(CurrentGenerationStatus, "mifm", TW_TYPE_DOUBLE, &Pop->GetPopulationStatus(gen).minFitnessMale,    "label='Min Fitness Male' group='Statistics' ");
	TwAddVarRO(CurrentGenerationStatus, "miff", TW_TYPE_DOUBLE, &Pop->GetPopulationStatus(gen).minFitnessFemale,  "label='Min Fitness Female' group='Statistics' ");
	TwAddVarRO(CurrentGenerationStatus, "migf", TW_TYPE_DOUBLE, &Pop->GetPopulationStatus(gen).minFitness,        "label='Min Global Fitness Female' group='Statistics' ");
	TwAddVarRO(CurrentGenerationStatus, "fsm" , TW_TYPE_DOUBLE, &Pop->GetPopulationStatus(gen).fitnessSumMale,    "label='Fitness Sum Male' group='Statistics' ");
	TwAddVarRO(CurrentGenerationStatus, "fsf" , TW_TYPE_DOUBLE, &Pop->GetPopulationStatus(gen).fitnessSumFemale,  "label='Fitness Sum Female' group='Statistics' ");
	TwAddVarRO(CurrentGenerationStatus, "fsg" , TW_TYPE_DOUBLE, &Pop->GetPopulationStatus(gen).fitnessSum,        "label='Fitness Global Sum' group='Statistics' ");

	TwAddVarRO(CurrentGenerationStatus, "Male Count"  , TW_TYPE_INT32, &Pop->GetPopulationStatus(gen).maleCount,   "group='Count' label='Male count'"); 
	TwAddVarRO(CurrentGenerationStatus, "Female Count", TW_TYPE_INT32, &Pop->GetPopulationStatus(gen).femaleCount, "group='Count' label='Female count'"); 
	TwAddVarRO(CurrentGenerationStatus, "Total Count" , TW_TYPE_INT32, &Pop->GetPopulationStatus(gen).beingsCount, "group='Count' label='Total count'"); 
	TwAddVarRO(CurrentGenerationStatus, "Dead Males"  , TW_TYPE_INT32, &Pop->GetPopulationStatus(gen).deadMales,   "group='Count' label='Dead males'"); 
	TwAddVarRO(CurrentGenerationStatus, "Dead Females", TW_TYPE_INT32, &Pop->GetPopulationStatus(gen).deadFemales, "group='Count' label='Dead females'"); 
	TwAddVarRO(CurrentGenerationStatus, "Total deads" , TW_TYPE_INT32, &Pop->GetPopulationStatus(gen).dead,        "group='Count' label='Dead'"); 

	TwAddSeparator(LocalStatistics, NULL, "group='Variables'");
	for(int i = 0; i < limits->size(); i++){
		char buf[1000];
		sprintf_s(buf, "group='Variables' label='X%i'", i);
		TwAddVarRO(CurrentGenerationStatus, buf, TW_TYPE_DOUBLE, &Pop->Statistics()._MaxFitnessBeing->IDecimalArray()[i], buf);	
	}
}
//------------------------------------------------------------------------------------------------
void SetupAllGenerations(){
	TwRemoveAllVars(Generations);

	TwAddSeparator(Generations, NULL, "group='Generations'");

	int min = Pop->GetStatusVector().size() - Pop->GetConfiguration().maxGenBuffer;
	
	if(min<=0)
		min = 0;

	int max = Pop->GetStatusVector().size();

	for(int i = min; i < max; i++){
		char buff[1000];
		sprintf_s(buff, "Generation %i", i );
		if(!TwAddButton(Generations, buff, SelectGen, (void*)i, "group='Generations'"))
			printf("ERRO");
	}
}
//------------------------------------------------------------------------------------------------
void SetupCurrentLimits(){
	//Remove tudo para depois configurar
	TwRemoveAllVars(CurrentLimit);

	//Insere todos os limites
	for(unsigned int i = 0; i < limits->size(); i++){
		char bufA[1000];
		char bufB[1000];

		//Configura separator
		sprintf_s(bufA, "group='Limit%i'", i+1, i+1);
		TwAddSeparator(CurrentLimit, NULL, bufA);

		//Configura inferior
		sprintf_s(bufA, "group='Limit%i' label='Inf.'", i+1);
		sprintf_s(bufB, "Inf. %i", i+1);
		TwAddVarRW(CurrentLimit, bufB, TW_TYPE_DOUBLE, &limits[0][i].first , bufA);

		//Configure superior
		sprintf_s(bufA, "group='Limit%i' label='Sup.'", i+1);
		sprintf_s(bufB, "Sup. %i", i+1);
		TwAddVarRW(CurrentLimit, bufB, TW_TYPE_DOUBLE, &limits[0][i].second, bufA);
	}
}
//------------------------------------------------------------------------------------------------
void generalBarsSetup(){
	TwDefine(" GLOBAL help='ARSOMF - Alysson Ribeiro da Silva OpenGL MINI FRAMEWORK Version: 0.1'");
	Config					= TwNewBar("Config");
	Generations				= TwNewBar("Generations");
	Statistics				= TwNewBar("Statistics");
	CurrentLimit			= TwNewBar("Limits");
	LocalStatistics			= TwNewBar("LocalStatistics");
	Operations				= TwNewBar("Operations");
	Functions				= TwNewBar("Functions");
	CurrentGenerationStatus = TwNewBar("CustomGeneration");
	TwDefine("GLOBAL buttonalign='center'");
	TwDefine(" GLOBAL iconalign=horizontal ");

	//setupBarsComponents();
	//setupHelpTexts();
	//setupBarsGeneral();
	configureGeneralGenerations(0);
	SetupFunctionsBar();
	SetupCurrentLimits();
	SetupAllGenerations();
	OperationsBarSetup();
	LocalStatisticsBarSetup();
	setupBarsBehavior();
	StatisticsBarSetup();
	ConfigBarSetup();
	setupWindowsSizes();
}
//------------------------------------------------------------------------------------------------
void DynamicConfigureGraphs(){
	int bufferSize = window.width - RIGHT_MARGIN;
	int max        = (int)Pop->GetCurrentPopStatus().maxFitness  + MAX_MARGIN;
	minDesloc      = (int)Pop->GetCurrentPopStatus().meanFitness + MIN_MARGIN; // para plotagem dinâmica

	if(fMed == 0x0)
		fMed = new OGLGraph();

	if(fMax == 0x0)
		fMax = new OGLGraph();

	if(lfMax == 0x0)
		lfMax = new OGLGraph();

	if(gfMed == 0x0)
		gfMed = new OGLGraph();

	fMed->setup( window.width , max - max * ASPECT_ZOOM, 0, 0, 1, 1, 2, bufferSize, 255,255,0 );
	fMax->setup( window.width , max - max * ASPECT_ZOOM, 0, 0, 1, 1, 2, bufferSize, 255,255,255);
	lfMax->setup( window.width, max - max * ASPECT_ZOOM, 0, 0, 1, 1, 2, bufferSize, 0  ,0  ,255);
	gfMed->setup( window.width, max - max * ASPECT_ZOOM, 0, 0, 1, 1, 2, bufferSize, 0  ,255,0);
}
//------------------------------------------------------------------------------------------------
void configureAllEvents(){
	//POP EVENTS-----------------
	Pop->getGenIncreaseEM().InsertEvent(SetupAllGenerations);
	//Pop->getFitMaxIncreaseEM().InsertEvent(DynamicConfigureGraphs);

	//GLOBAL EVENTS--------------
	LimitAddEvents.InsertEvent(SetupCurrentLimits);

	//Mouse move
	//_mouseMoveEventHandler->registerEvent(new MouseMove());
}
//------------------------------------------------------------------------------------------------
void init(){
	//TESTES BEHAVIOR BANK --------------------------------------------------------------------
	ARS_BehaviorBank& bBank = ARS_BehaviorBank::getInstance();
	bBank.InsertBehavior(MALE  , 0, new ARS_MaleBehavior()); 
	bBank.InsertBehavior(FEMALE, 0, new ARS_FemaleBehavior());
	//TESTES BEHAVIOR BANK --------------------------------------------------------------------

	//TESTES POPULAÇÃO ------------------------------------------------------------------------

	limits = new vector<std::pair<double,double>>();
	//for(int i = 0; i < 2; i++)
	//	limits->push_back(make_pair(0,400)); // PADRÃO

	//Cintaria
	insertLimit(0,3);
	insertLimit(0,5);

	//limits->push_back(make_pair(-5.12,5.12)); // PADRÃO
	//limits->push_back(make_pair(-5.12,5.12)); // PADRÃO
	//limits->push_back(make_pair(-5.12,5.12)); // PADRÃO
	//limits->push_back(make_pair(-5.12,5.12)); // PADRÃO
	//limits->push_back(make_pair(-5.12,5.12)); // PADRÃO
	//limits->push_back(make_pair(-5.12,5.12)); // PADRÃO
	//limits->push_back(make_pair(-5.12,5.12)); // PADRÃO
	//limits->push_back(make_pair(-5.12,5.12)); // PADRÃO
	//limits->push_back(make_pair(-5.12,5.12)); // PADRÃO
	//limits->push_back(make_pair(-5.12,5.12)); // PADRÃO

	ARS_PopulationConfig* mantis;

	//Mantis configuration
	mantis = new ARS_PopulationConfig(
		true,   //Random beings
		100000, //Max generations
		100,    //Tamanho da população inicial
		10,     //Tamanho do DNA
		1,      //Quantidade de DNA's //não utilizado mais
		5,      //Profundidade de atualização de gerações
		0.01,   //Probabilidade de mutação
		0.5,    //Probabilidade de cruzamento
		0.0,    //High Limiar
		0.0,    //Low Limiar
		0.8,    //High limiar threshold
		0.4,    //Low limiar threshold
		0,      //Metodo de seleção - não necessário
		ARS_REVERSING_MUT,   //Metodo de mutação
		ARS_RASTRIGIN,       //Metodo fitness
		ARS_TWO_POINT_CROSS, //Metodo de cruzamento
		0,		//Breeding age
		2,		//Breed inf
		2,		//Breed sup
		1000,   //Old age
		2,		//Old inf
		2,		//Old sup
		40,     //Max reproduction male
		2,		//rep male inf
		2,		//rep male sup
		50,     //Max reproduction female
		2,		//rep female inf
		2,		//rep female sup
		limits  //Limites das variáveis
		);

	mantis->Minimization = false;

	Pop = new ARS_Population(*mantis);
	Pop->initialize(); //Inicializa com pop randomica inicial

	//TESTES POPULAÇÃO ------------------------------------------------------------------------

	//INICIALIZAÇÕES GERAIS -------------------------------------------------------------------

	fMed  = 0x0;
	fMax  = 0x0;
	lfMax = 0x0;
	gfMed = 0x0;

	//Deve ser configurado aqui para evitar erros
	liveStatus = Pop->GetCurrentPopStatus();
	DynamicConfigureGraphs();	
	generalBarsSetup();
	configureAllEvents(); //Configura eventos
	
	//INICIALIZAÇÕES GERAIS -------------------------------------------------------------------
}
//------------------------------------------------------------------------------------------------
void Draw(double time){
	//CONFIG DA TRASNFORMAÇÃO PADRÃO DO GRÁFICO
	glPushMatrix();
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity(); 
	glOrtho(0, fMed->Width(), 0, fMed->Height(), 0, 1.0); 
	glMatrixMode(GL_MODELVIEW); 
	glLoadIdentity();
	
	//Translação da câmera
	//glTranslatef(0,-minDesloc,0);
	glTranslatef(GraphsTranslation.x, GraphsTranslation.y, 0);

	fMed->draw();
	fMax->draw();
	lfMax->draw();
	gfMed->draw();

	glPopMatrix();
}
//------------------------------------------------------------------------------------------------
void Update(double time){
	if(reset){
		ReDrawGraphs();
		reset = false;
	}

	//DEBUG::PRINT

	//DEBUG::PRINT

	//---------------------------------------------------------------------------
	//---------------------------------------------------------------------------

	checkLimits();
	Pop->Evolution();
	
	//SetGraphsDimention(NULL);

	double value = Pop->GetCurrentPopStatus().meanFitness;
	fMed->update((float)value-minDesloc);//-minDesloc);
	fMax->update((float)Pop->Statistics().maxFitness-minDesloc);//-minDesloc);
	lfMax->update((float)Pop->GetCurrentPopStatus().maxFitness-minDesloc);//-minDesloc);
	gfMed->update((float)Pop->Statistics().meanFitness-minDesloc);//-minDesloc);

	liveStatus = Pop->GetCurrentPopStatus();
}
//------------------------------------------------------------------------------------------------
int main(int argc, char* argv[]){
	//Semente para inicialização de randômicos
	srand((unsigned int)time(NULL));

	//vector<double> values;
	//for(int i = 0; i < 10; i++)
	//	values[i] = 1;
	//values.push_back(-4.5229);
	//values.push_back(0);
	//printf("RAS: %f\n" ,1/(Rastrigin(1, values)+0.0001));
	//getchar();

	WINDOW_NAME = "ARS GENETICS"; 
	
	ARS_Initialize();
	ARS_SetDrawFunc(&Draw);
	ARS_SetUpdateFunc(&Update);

	//Todos os meus inits devem vir aqui
	init();
	//Todos os meus inits devem vir aqui
	
	ARS_Run();

	return 0;
}
//----------------------------------------------------------------------------------------------------
