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

#include "LimitH.h"

namespace LIMITS{
	//------------------------------------------------------------------------------------------------
	vector<std::pair<double,double>>* limits;
	ARS_Population*                   Pop;			//População para controle
	ARS_PopulationStatus              liveStatus;   //Status da ultima geração para facilitar visualização dos dados
	//------------------------------------------------------------------------------------------------
	void insertLimit(double inf, double sup){
		limits->push_back(std::make_pair<double, double>(inf, sup));
	}
	//------------------------------------------------------------------------------------------------
	void removeLimit(int index){
		limits->pop_back();
	}
	//------------------------------------------------------------------------------------------------
	void MinimizationE(){
		Pop->GetConfiguration().Minimization = true;
				if(Pop->GetCurrentPopStatus().beingsCount == 0)
			return;
		Pop->clearGlobalData();
		ARS_InsertPerturbationE();
	}
	//------------------------------------------------------------------------------------------------
	void MaximizationE(){

		Pop->GetConfiguration().Minimization = false;
				if(Pop->GetCurrentPopStatus().beingsCount == 0)
			return;
		Pop->clearGlobalData();
		ARS_InsertPerturbationE();
	}
	//------------------------------------------------------------------------------------------------
	void ARS_InsertPerturbationE(){
		if(Pop->GetCurrentPopStatus().beingsCount == 0)
			return;

		//Mata todos antes de inserir a perturbação
		Pop->KillAllBeings(Pop->CurrentGeneration());   //Mata todos dessa geração
		Pop->KillAllBeings(Pop->CurrentGeneration()+1); //Mata todos que já foram gerados da próxima geração para evitar erros

		//Cria novo ser aleatória para inserir
		//O tratamento de limites e etc é feito automáticamente
		for(int i = 0; i < 100; i++){
			ARS_Being* new_born = new ARS_Being(*Pop);
			int gen = Pop->CurrentGeneration();
			new_born->GetStatus().Generation() = gen; 

			//Insere ser recem criado... o tamanho da população pode exceder por isso é uma perturbação
			Pop->InsertBeing(new_born, gen);
		}
	}
}
