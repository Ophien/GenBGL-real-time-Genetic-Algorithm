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
#include "ARS_Bin.h"
#include "ARS_Helper.h"
#include "ARS_Population.h"

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


namespace ARS_Operations{
	extern bool decrease;

	extern void increaseMutationRotation(int& value, int max);

	//ARS_COMMENTS::SELEÇÃO DE CRUZAMENTO - size só é utilizado no interchanging
	extern void Applymutation(ARS_PopulationConfig& config, ARS_Bin& value, int PrimarycutPoint, int size = 0);
	
	//ARS_COMMENTS::APLICA CROSSOVER NO SIMULADOR DE ACORDO COM A CONFIG NA POPULAÇÃO
	extern void ApplyCrossOver(ARS_PopulationConfig& config, ARS_Being& A, ARS_Being& B);

	//ARS_COMMENTS::INTERPOTALÇÃO
	extern double Interpolation(double val, double inf, double sup, int BinSize);

	//ARS_COMMENTS::RANDOM BEING GENERATOR MODULE
	extern ARS_Bin& ARS_RandomBin(int size);

	//ARS_COMMENTS::TODO::CRIAR NOVOS MÉTODOS PARA GERAÇÃO RANDÔMICA DE ELEMENTOS

	//ARS_COMMENTS::SELECTION OPERATIONS
	extern ARS_Being& ARS_StochasticUniversalSamplingSelection(ARS_Population& _population);
	extern ARS_Being& ARS_BoltzmannSelection				  (ARS_Population& _population);
	extern ARS_Being& ARS_RouletteWheelSelection			  (ARS_Population& _population, int rolls, double total_pop);
	extern ARS_Being& ARS_RandomSelection					  (ARS_Population& _population);
	extern ARS_Being& ARS_RankSelection						  (ARS_Population& _population, double r);
	extern vector<ARS_Being*> ARS_TournamentSelection		  (ARS_Population& _population);

	//ARS_COMMENTS::BREEDING OPERATIONS
	//Mormais
	extern ARS_Bin** ARS_SinglePointCrossover           (ARS_PopulationConfig& config, ARS_Bin& A, ARS_Bin& B, int& decA, int& decB, int cutPoint);
	extern ARS_Bin** ARS_MultiPointCrossover            (ARS_PopulationConfig& config, ARS_Bin& A, ARS_Bin& B, int& decA, int& decB, int quantity, ...);
	extern ARS_Bin** ARS_TwoPointCrossover              (ARS_PopulationConfig& config, ARS_Bin& A, ARS_Bin& B, int& decA, int& decB, int FirstCutPoint, int SecondCutPoint);
	extern ARS_Bin** ARS_OrderedCrossover               (ARS_PopulationConfig& config, ARS_Bin& A, ARS_Bin& B, int& decA, int& decB, int FirstCutPoint, int SecondCutPoint);

	//Cruzamentos teste
	extern ARS_Bin** ARS_UniformCrossover               (ARS_PopulationConfig& config, ARS_Bin& A, ARS_Bin& B, int& decA, int& decB, int* Mask = NULL);
	extern ARS_Bin** ARS_ShuffleCrossover               (ARS_PopulationConfig& config, ARS_Bin& A, ARS_Bin& B, int& decA, int& decB, int* Mask = NULL);
	extern ARS_Bin*  ARS_PrecedencePreservativeCrossover(ARS_PopulationConfig& config, ARS_Bin& A, ARS_Bin& B, int& decA, int& decB, int* Operations = NULL);
	extern ARS_Bin*  ARS_ThreeParentCrossover           (ARS_PopulationConfig& config, ARS_Bin& A, ARS_Bin& B, ARS_Bin& C, int& decA, int& decB, int& decC);

	//ARS_COMMENTS::BREEDING ESPECIAIS
	//extern void ARS_SinglePointCrossover           (ARS_Population& population, ARS_Being& A, ARS_Being& B, unsigned int cutPoint);
	//extern void ARS_TwoPointCrossover              (ARS_Population& population, ARS_Being& A, ARS_Being& B, unsigned int FirstCutPoint, unsigned int SecondCutPoint);
	//extern void ARS_MultiPointCrossover            (ARS_Population& population, ARS_Being& A, ARS_Being& B, unsigned int quantity, ...);
	//extern void ARS_UniformCrossover               (ARS_Population& population, ARS_Being& A, ARS_Being& B, unsigned int* Mask = NULL);
	//extern void ARS_ThreeParentCrossover           (ARS_Population& population, ARS_Being& A, ARS_Being& B, ARS_Bin& C);
	//extern void ARS_ShuffleCrossover               (ARS_Population& population, ARS_Being& A, ARS_Being& B, unsigned int* Mask = NULL);
	//extern void ARS_PrecedencePreservativeCrossover(ARS_Population& population, ARS_Being& A, ARS_Being& B, unsigned int* Operations = NULL);
	//extern void ARS_OrderedCrossover               (ARS_Population& population, ARS_Being& A, ARS_Being& B, unsigned int FirstCutPoint, unsigned int SecondCutPoint);

	//ARS_COMMENTS::MUTATION OPERATIONS
	extern ARS_Bin& ARS_Flipping(ARS_Bin& value, int gene = -1);
	extern ARS_Bin& ARS_Interchanging(ARS_Bin& value, int geneA = -1, int geneB = -1);
	extern ARS_Bin ARS_Reversing(ARS_Bin& value, int gene = -1);

	extern void ARS_SetSex(ARS_Being* being);
};//ARS_COMMENTS::END NAMESPACE ARS_OPERATIONS 
