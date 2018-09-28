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
#include "ARS_BeingStatus.h"
#include "Behavior_helper.h"

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
ARS_BeingStatus::ARS_BeingStatus(void){
	//VARIÁVEIS DE IDENTIFICAÇÃO
	sex        = 0;
	iD         = 1;
	fatherID   = 0;
	motherID   = 0;
	generation = 0;

	//VARIÁVEIS DE CONTROLE
	fitness     = 0.0;
	oldAge      = 0.0;
	breedingAge = 0.0;
	lifeTime    = 0.0;

	//ESTADO INICIAL
	state = NEWBORN;

	maxBreeding = 0;

	//PARA NÃO DAR ACESSO ILEGAL
	being = 0x0;
}
//------------------------------------------------------------------------------------------------
void ARS_BeingStatus::Init(
		int Sex,
		int ID,
		int FatherID,
		int MotherID,
		int Generation,
		float Fitness,
		float MaturityAge,
		float OldAge,
		float BreedingAge){
	this->sex = Sex;
	this->iD  = ID;
	this->fatherID = FatherID;
	this->motherID = MotherID;
	this->generation = Generation;
	this->fitness = Fitness;
	this->oldAge = OldAge;
	this->breedingAge = BreedingAge;
}
//------------------------------------------------------------------------------------------------
ARS_BeingStatus::~ARS_BeingStatus(void){}
//------------------------------------------------------------------------------------------------
int& ARS_BeingStatus::State(){return state;}
int& ARS_BeingStatus::Sex(){return sex;}
int& ARS_BeingStatus::ID(){return iD;}
int& ARS_BeingStatus::FatherID(){return fatherID;}
int& ARS_BeingStatus::MotherID(){return motherID;}
int& ARS_BeingStatus::Generation(){return generation;}
//------------------------------------------------------------------------------------------------
double& ARS_BeingStatus::Fitness(){return fitness;}
double& ARS_BeingStatus::OldAge(){return oldAge;}
double& ARS_BeingStatus::BreedingAge(){return breedingAge;}
double& ARS_BeingStatus::LifeTime(){return lifeTime;}
//------------------------------------------------------------------------------------------------
