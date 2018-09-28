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

//DEFINIÇÃO PARA EVITAR ERROS DE INCLUDE
class ARS_Being;

#define MALE   0
#define FEMALE 1

class ARS_BeingStatus
{
public:
	ARS_BeingStatus(void);
	~ARS_BeingStatus(void);

	void Init(
		int Sex           = 0,
		int ID            = 0,
		int FatherID      = 0,
		int MotherID      = 0,
		int Generation    = 0,
		float Fitness     = 0.0f,
		float MaturityAge = 0.0f,
		float OldAge      = 0.0f,
		float BreedingAge = 0.0f);

	//Configura parente comum.
	void setParent(ARS_Being& parent){
		being = &parent;
	}

	ARS_Being& Parent(){return *being;}

	void SetParent(ARS_Being* parent){being = parent;}

	int& State();
	int& Sex();
	int& ID();
	int& FatherID();
	int& MotherID();
	int& Generation();
	int& MaxBreeding(){return maxBreeding;}

	double& Fitness();
	double& OldAge();
	double& BreedingAge();
	double& LifeTime();

	void setOldAge(double value){oldAge = value;}
	void setBreedingAge(double value){breedingAge = value;}

private:
	//VARIÁVEIS DE IDENTIFICAÇÃO
	int sex;
	int iD;
	int fatherID;
	int motherID;
	int generation;

	//VARIÁVEIS DE CONTROLE
	double fitness;
	double lifeTime;
	double oldAge;
	double breedingAge;

	//VARIÁVEIS PARA CONTROLE DE ESTADO
	int state;
	int maxBreeding;

	//Ser configurado para este status
	ARS_Being* being;
};

