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

#ifndef ARS_BEING_H
#define ARS_BEING_H
//------------------------------------------------------------------------------------------------
//ARS_COMMENTS::SYSTEM INCLUDES
//------------------------------------------------------------------------------------------------
#include <string>
#include <map>
#include <vector>

//------------------------------------------------------------------------------------------------
//ARS_COMMENTS::INTERNAL INCLUDE
//------------------------------------------------------------------------------------------------
#include "ARS_Bin.h"
#include "ARS_Helper.h"
#include "ARS_Behavior.h"
#include "ARS_BeingStatus.h"

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
class ARS_Population;
class ARS_PopulationConfig;
class ARS_Being;

//Classe responsável por controlar as propostas de acasalamento
class ARS_BreedingProposal{
public:
	ARS_BreedingProposal(void){
		Enable = false;
	}
	~ARS_BreedingProposal(void){}

	bool Enable;

	ARS_Being* proposer;
};

class ARS_Being{
public:
	//Construtor padrão deve existir para evitar erros
	//Utilizado pelas funções de crossover
	ARS_Being(ARS_Population& population, int DNAQuant);

	/*ARS_Being(ARS_Population& population)
	 *
	 *Este construtor já gera o ser completamente configurado
	 *de acordo com os padrões e configurações de uma determinada população
	 *
	 */
	ARS_Being(ARS_Population& population);
	~ARS_Being(void);

	void SetDNA(int index, ARS_Bin* value);
	void SetPopulation(ARS_Population* Pop){this->Pop = Pop;};

	vector<ARS_Bin*>& GetDNA(){return DNA;}

	//Arrays utilizados para diminuir a complexidade do algoritmo
	vector <double>&  DecimalArray(){return decimal;}
	vector <double>&  IDecimalArray(){return interpolated;}

	ARS_BeingStatus& GetStatus(){return Status;}

	ARS_BeingStatus GetStatusClone(){return Status;}

	//Função de avaliação colocada aqui para garantir maior abstração
	FitnessFunc fitnessFunction;

	void SetBehavior(ARS_Behavior& behavior){this->Behavior = &behavior;}

	ARS_Population& Population(){return *Pop;}

	vector<ARS_BreedingProposal*>& BreedingProposal(){return CurrentProposal;}

	void Behave(const double& time){if(Behavior!=NULL)Behavior->Execute(Status, time);}

	void ResetStatus();

private:
	/*Atributos para teste*/
	ARS_BeingStatus Status;

	/*Being chromossome*/
	vector<ARS_Bin*> DNA;

	//Arrays utilizados para diminuir a complexidade do algoritmo
	vector<double>   decimal;
	vector<double>   interpolated;

	//CONTROLADOR DE COMPORTAMENTO
	ARS_Behavior* Behavior;

	//PROPOSAL
	//Trocar para uma lista, pois um ser pode possuir mais de uma proposta de cruzamento
	vector<ARS_BreedingProposal*> CurrentProposal;

	//POPULAÇÃO A QUAL PERTENCE
	ARS_Population* Pop;
};
#endif

