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

namespace ARS_defaults
{
	//Utilizado para controlar a idade de acasalamento de cada ser
	#define ARS_GLOBAL_BREEDING_AGE       16.0

	//Utilizado para controlar limites de idade de acasalamento
	#define ARS_BREEDING_AGE_THRESHOLD    2.0

	//Utilizado para controlar velhice de um objeto
	#define ARS_GLOBAL_OLD_AGE            70.0

	//Utilizado para controlar limites da velhice de um objeto
	#define ARS_GLOBAL_OLD_AGE_THRESHOLD  5.0

	//CONTROLA GERAÇÃO INICIAL DE INDIVÍDUOS RANDOMICOS	
	#define ARS_RANDOM_INITIAL_BEINGS true

	//CONFIGURAÇÃO DOS INDIVIDUOS
	#define ARS_TOTAL_GENERATIONS     10
	#define ARS_TOTAL_POPULATIONS     100000
	#define ARS_DNA_CODIFICATION_SIZE 10
	#define ARS_DNA_QUANTITY          1

	//CONFIGURAÇÃO DE COMPORTAMENTO DA POPULAÇÃO
	#define ARS_UPDATE_DEPTH          5

	//CONFIGURAÇÃO DE PROBABILIDADES
	#define ARS_MUTATION_PROBABILITY  0.01
	#define ARS_BREEDING_PROBABILITY  0.5

	//CONFIGURAÇÃO DE LIMIÁRES
	#define ARS_HIGH_LIMIAR          0.0
    #define ARS_LOW_LIMIAR           0.0

	//ID DAS FUNÇÕES CONFIGURADAS
	#define ARS_SELECTION_METHOD     0
	#define ARS_MUTATION_METHOD      0
	#define ARS_FITNESS_FUNCTION     0
	#define ARS_CROSSOVER_FUNCTION   0

	//DEFINIÇÕES DE SUPORTE
	#define ARS_MALE   0
	#define ARS_FEMALE 1

	//CONFIGURAÇÕES COMPORTAMENTAIS
	#define ARS_BREEDING_AGE     17
	#define ARS_BREEDING_AGE_INF 2
	#define ARS_BREEDING_AGE_SUP 10
	#define ARS_OLD_AGE          60
	#define ARS_OLD_AGE_INF      20
	#define ARS_OLD_AGE_SUP      20

	//ESTADOS PARA O SER
	#define ARS_CHILD 0
	#define ARS_TEEN  1
	#define ARS_ADULT 2
	#define ARS_OLD   3
	#define ARS_DEAD  4

	#define ARS_HIGH_LIMIAR_THRESHOLD 0.8
	#define ARS_LOW_LIMIAR_THRESHOLD  0.4

	#define ARS_MALE_REP_LIMIAR     1
	#define ARS_FEMALE_REP_LIMIAR   1
	#define ARS_MALE_REP_INF        1
	#define ARS_FEMALE_REP_INF      1
	#define ARS_MALE_REP_SUP        3
	#define ARS_FEMALE_REP_SUP      2

	#define ARS_MAX_GEN_BUFFER       500
	#define ARS_MAX_UPDATE_PER_FRAME 500

	//FUNCTIONS CODE
	#define ARS_SPHERE			 0
	#define ARS_ROSENBROCK		 1
	#define ARS_DEJONG_STEP		 2
	#define ARS_DEJONG_STEPB	 3
	#define ARS_SHEKELS_FOXHOLES 4
	#define ARS_SCHAFFER		 5
	#define ARS_SCHAFFERB		 6
	#define ARS_SPHERE_MODEL	 7
	#define ARS_SCHWEFEL		 8
	#define ARS_SCHWEFELB		 9
	#define ARS_ACKLEY			 10
	#define ARS_RASTRIGIN		 11
	#define ARS_GRIEWANGK		 12
	#define ARS_SCHWEFEL_PRO	 13
	#define ARS_BOHACHEVSKY		 14
	#define ARS_CINTARIA		 15
	#define ARS_SAPATEIRO	     16
	#define ARS_DIETA			 17
	#define ARS_TRANSPORTE		 18	
	#define ARS_REFINARIA		 19
	#define ARS_FABRICAMOVEIS	 20
	#define ARS_FABRICAP1P2		 21
	#define ARS_EXTREMEPROBLEM	 22

	//CROSSOVER FUNCTIONS
	#define ARS_SINGLE_POINT_CROSS  			0
	#define ARS_TWO_POINT_CROSS		    		1
	#define ARS_MULTI_POINT_CROSS				2
	#define ARS_UNIFORM_CROSS					3
	#define ARS_THREE_PARENT_CROSS		    	4
	#define ARS_SHUFFLE_CROSS					5
	#define ARS_PRECEDENCE_PRESERVATIVE_CROSS   6
	#define ARS_ORDERED_CROSS				    7

	//MUTATION FUNCTION
	#define ARS_FLIPPING_MUT	  0
	#define ARS_INTERCHANGING_MUT 1
	#define ARS_REVERSING_MUT	  2
}
