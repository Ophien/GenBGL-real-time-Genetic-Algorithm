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
#include <string>
#include <stdio.h>
#include <vector>
#include <map>

//------------------------------------------------------------------------------------------------
//ARS_COMMENTS::INTERNAL INCLUDE
//------------------------------------------------------------------------------------------------
#include "ARS_Behavior.h"
#include "ARS_PopulationConfig.h"

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

class ARS_BehaviorBank
{
public:
	//Singleton implementado
	static ARS_BehaviorBank& getInstance(){
		static ARS_BehaviorBank instance;
		return instance;
	}

	//Retorna comportamento de acordo com as configurações da população e sexo/tipo
	ARS_Behavior& SugestBehavior(int type, ARS_PopulationConfig& PopulationConfig);

	//Retorna comportamento randômico
	ARS_Behavior& GetRandomBehavior(int type);

	//Inserir comportamento no banco
	void InsertBehavior(int type, int code, ARS_Behavior* behavior){
		//Apenas insere comportamento no banco
		BehaviorBank[type][code] = behavior;
	}

private:
	ARS_BehaviorBank(void){}
	~ARS_BehaviorBank(void){}

	ARS_BehaviorBank(ARS_BehaviorBank const&);
	void operator=(ARS_BehaviorBank const&);

	//Sexo -> TIPO -> Comportamento
	map<int, map<int, ARS_Behavior*>> BehaviorBank;
};

