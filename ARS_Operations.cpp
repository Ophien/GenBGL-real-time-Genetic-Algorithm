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
#include <list>
#include <algorithm>

//------------------------------------------------------------------------------------------------
//ARS_COMMENTS::INTERNAL INCLUDE
//------------------------------------------------------------------------------------------------
#include "ARS_Operations.h"

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

namespace ARS_Operations{
	bool decrease = false;
	//para rotação de mutação
	void increaseMutationRotation(int& value, int max){
		if(decrease)
			value--;
		else
			value++;

		if(value>=max){
			decrease = true;
			value--;
		}

		if(value<0){
			decrease = false;
			value++;
		}
	}

	//APLICA MUTAÇÃO EM UM BINÁRIO BÁSICO DE ACORDO COM AS CONFIGURAÇÕES DE UMA POPULAÇÃO
	void Applymutation(ARS_PopulationConfig& Config, ARS_Bin& value, int primaryCutPoint, int size){
		double MutProb = Config.MutationProbability;
		MutProb       *= 100;

		int MutWillOccur = rand() % 100;

		//Colocar mutação da população
		if(MutWillOccur < MutProb){
			int RandInterchanger = 0;
			switch(Config.MutationMethod){
			case ARS_FLIPPING_MUT:
				ARS_Flipping(value, primaryCutPoint);
				break;
			case ARS_INTERCHANGING_MUT:
				RandInterchanger = rand() % size;
				ARS_Interchanging(value, primaryCutPoint, RandInterchanger);
				break;
			case ARS_REVERSING_MUT:
				ARS_Reversing(value, primaryCutPoint);
				break;
			}
		}
	}
	//------------------------------------------------------------------------------------------------
	//PODE SER UTILIZADO COMO HOTSPOT
	void ApplyCrossOver(ARS_PopulationConfig& config, ARS_Being& A, ARS_Being& B){
		double breedingProbability = config.BreedingProbability * 100;
		int sucess = rand() % 100;
		if(sucess < breedingProbability){	
			//Tamanhos diferentes retornar vazio
			if(A.GetDNA().size() != B.GetDNA().size())
				return;

			ARS_Population& population = A.Population();

			//Cria indivíduos com quantidade de DNAs_prédefinido
			ARS_Being* sonA = new ARS_Being(population, A.GetDNA().size());
			ARS_Being* sonB = new ARS_Being(population, A.GetDNA().size());

			vector<ARS_Bin*>& DNA_A = A.GetDNA();
			vector<ARS_Bin*>& DNA_B = B.GetDNA();

			ARS_PopulationConfig& configuration = population.GetConfiguration();

			//Filhos para adiconar no lugar correto
			ARS_Bin** children;

			//if(population.Statistics().beingsCount >= 120)
			//{
			//	printf("PAREI");
			//}

			//Para cada DNA
			for(unsigned int i = 0; i < DNA_A.size(); i++){
				ARS_Bin* currentA = DNA_A[i];
				ARS_Bin* currentB = DNA_B[i];

				int DNA_BIT_COUNT = currentA->Size();

				//para buferizar o decimal em tempo de geração do binário
				//AINDA NÃO IMPLEMENTADO
				int decA;
				int decB;
				int decC;

				//para pontos de corte nos cruzamentos
				int randCutPointA = rand() % (configuration.DNACodificationSize-1) + 1;
				int randCutPointB = rand() % (configuration.DNACodificationSize-1) + 1;
				int randCutPointC = rand() % (configuration.DNACodificationSize-1) + 1;
				int randCutPointD = rand() % (configuration.DNACodificationSize-1) + 1;
				int randCutPointE = rand() % (configuration.DNACodificationSize-1) + 1;
				
				//para controle interno de alguns cruzamentos
				int* Mask;
				int randHelperA;
				int randHelperB;
				ARS_PopulationHolder* holder;
				ARS_Bin* randomThirdEye = NULL;

				switch(config.CrossoverFunction){
				case ARS_SINGLE_POINT_CROSS:
					children = ARS_SinglePointCrossover(configuration, *currentA, *currentB, decA, decB, randCutPointA); 
					break;
				case ARS_TWO_POINT_CROSS:
					children = ARS_TwoPointCrossover(configuration, *currentA, *currentB, decA, decB, randCutPointA, randCutPointB);
					break;
				case ARS_MULTI_POINT_CROSS:
					children = ARS_MultiPointCrossover(configuration, *currentA, *currentB, decA, decB, 5, randCutPointA, randCutPointB, randCutPointC, randCutPointD, randCutPointE);
					break;
				case ARS_UNIFORM_CROSS:
					Mask = new int[DNA_BIT_COUNT];
					
					for(int j = 0; j < DNA_BIT_COUNT; j++)
						Mask[j] = rand() % 2;

					children = ARS_UniformCrossover(configuration, *currentA, *currentB, decA, decB, Mask);
					break;
				case ARS_THREE_PARENT_CROSS:
					randHelperB = rand() % 2; // define qual sexo pegar
					holder = &population.GetPopulationHolder(A.GetStatus().Generation(), randHelperB);

					randHelperA = rand() % holder->all.size();// define qual indivíduo pegar
					//TODO::PEGAR TERCEIRO INDIVÍDUO RANDÔMICAMENTE AQUI
					randomThirdEye = holder->all[randHelperA]->GetDNA()[i];
					
					children = new ARS_Bin*[2];
					children[0] = ARS_ThreeParentCrossover(configuration, *currentA, *currentB, *randomThirdEye, decA, decB, decC);

					randHelperB = rand() % 2; // define qual sexo pegar
					holder = &population.GetPopulationHolder(A.GetStatus().Generation(), randHelperB);

					randHelperA = rand() % holder->all.size();// define qual indivíduo pegar
					//TODO::PEGAR TERCEIRO INDIVÍDUO RANDÔMICAMENTE AQUI
					randomThirdEye = holder->all[randHelperA]->GetDNA()[i];
					
					children[1] = ARS_ThreeParentCrossover(configuration, *currentA, *currentB, *randomThirdEye, decA, decB, decC);
					break;
				case ARS_SHUFFLE_CROSS:
					//Mask = new int[DNA_BIT_COUNT];
					
					//for(int j = 0; j < DNA_BIT_COUNT; j++)
					//	Mask[j] = rand() % 2;

					children = ARS_ShuffleCrossover(configuration, *currentA, *currentB, decA, decB, NULL);
					break;
				case ARS_PRECEDENCE_PRESERVATIVE_CROSS:
					Mask = new int[DNA_BIT_COUNT];
					
					for(int j = 0; j < DNA_BIT_COUNT; j++)
						Mask[j] = rand() % 2;
					
					children = new ARS_Bin*[2];

					children[0] = ARS_PrecedencePreservativeCrossover(configuration, *currentA, *currentB, decA, decB, Mask);
					
					for(int j = 0; j < DNA_BIT_COUNT; j++)
						Mask[j] = rand() % 2;
					
					children[1] = ARS_PrecedencePreservativeCrossover(configuration, *currentA, *currentB, decA, decB, Mask);
					break;
				case ARS_ORDERED_CROSS:
					children = ARS_OrderedCrossover(configuration, *currentA, *currentB, decA, decB, randCutPointA, randCutPointB);
					break;
				default:
					children = ARS_SinglePointCrossover(configuration, *currentA, *currentB, decA, decB, randCutPointA); 
					break;
				}// Fim Switch

				//Adicionar novos binários ao DNA final
				//BUFERIZANDO VALORES-----------------------------------------------------------------------------
				//Configurando vetor de decimais
				decA = children[0]->Decimal();
				decB = children[1]->Decimal();

				sonA->DecimalArray().push_back(decA);
				sonB->DecimalArray().push_back(decB);
	
				//Configura valores interpolados
				pair<double, double> currentLimit = configuration.Limits[0][i];
				double interpolA = Interpolation(children[0]->Decimal(), currentLimit.first, currentLimit.second, DNA_BIT_COUNT);
				double interpolB = Interpolation(children[1]->Decimal(), currentLimit.first, currentLimit.second, DNA_BIT_COUNT);

				sonA->IDecimalArray().push_back(interpolA);
				sonB->IDecimalArray().push_back(interpolB);

				//Adiciona novo DNA nos respectivos filhos

				if(children[0] == 0x0 || children[1] == 0x0){
					children = new ARS_Bin*[2];
					children[0] = new ARS_Bin(configuration.DNACodificationSize);
					children[1] = new ARS_Bin(configuration.DNACodificationSize);
				}

				sonA->GetDNA().push_back(children[0]);
				sonB->GetDNA().push_back(children[1]);
				//BUFERIZANDO VALORES-----------------------------------------------------------------------------
			}//Acabou de percorrer todos os DNA's

			//----------------------------------------------------------------------------------------------------
			//Verificar quem será adicionado a nova população aqui
			//Calcula função fitness
			
			double fitnessA = 0.0;
			double fitnessB = 0.0;

			if(config.Minimization){
				fitnessA = 1/(sonA->fitnessFunction(DNA_A.size(), sonA->IDecimalArray()) + config.EPSILON);
				fitnessB = 1/(sonB->fitnessFunction(DNA_A.size(), sonB->IDecimalArray()) + config.EPSILON);
			}else{
				fitnessA = sonA->fitnessFunction(DNA_A.size(), sonA->IDecimalArray());
				fitnessB = sonB->fitnessFunction(DNA_B.size(), sonB->IDecimalArray());
			}

			sonA->GetStatus().Fitness() = fitnessA;
			sonB->GetStatus().Fitness() = fitnessB;

			//Configurando nova geração
			sonA->GetStatus().Generation() = A.GetStatus().Generation() + 1;
			sonB->GetStatus().Generation() = A.GetStatus().Generation() + 1;

			//Configurando sexo
			ARS_SetSex(sonA);
			ARS_SetSex(sonB);
			//BUFERIZANDO VALORES-----------------------------------------------------------------------------

			//Inserindo filhos na população

			//Fim da execução garantir que o pretendente tenha somado 1 a seu contador
			//de acasalamento
			B.GetStatus().MaxBreeding()++;

			//TODO::COLOCAR ELETISMO AQUI

			//Garante inserir apenas 1 por vez
			if(sonA->GetStatus().Fitness() > sonB->GetStatus().Fitness()){
				population.InsertBeing(sonA);
				delete sonB;
			}
			else{
				population.InsertBeing(sonB);
				delete sonA;
			}
		}//Acabou de verificar se poderá ser efetuado o cruzamento
	}//Fim método
	//------------------------------------------------------------------------------------------------
	void ARS_SetSex(ARS_Being* being){
		//ARS_Population& beingPop = being->Population();
		//being->GetStatus().Sex() = (being->GetDNA()[0]->Higher()[0] + being->GetDNA()[0]->Higher()[beingPop.GetConfiguration().DNACodificationSize-1])%2;
		being->GetStatus().Sex() = rand() % 2;
	}
	//------------------------------------------------------------------------------------------------
	double Interpolation(double val, double inf, double sup, int BinSize){
		double interpolated = 0.0;

		interpolated = (val * (sup - inf))/(pow(2.0, BinSize) - 1) + inf;

		return interpolated;
	}
	//------------------------------------------------------------------------------------------------
	//Calcula parte inteira e decimal de um binário
	ARS_Bin& ARS_RandomBin(int size){
		ARS_Bin* newBin = new ARS_Bin(size);

		string value;
		int _intPart = 0;
		int _exp     = size - 1;
		
		int* High = newBin->Higher();

		//#pragma omp parallel for reduction (+:_intPart)
		for(int i = 0; i < size; i++){
			int Random  = rand() % 2;
			High[i]     = Random;

			_intPart += (int)pow(2.0, (int)_exp) * Random;
			_exp--;
		}

		//Essa função chama 1 for a mais no programa
		//newBin->CalcDec();

		newBin->Decimal() = _intPart;

		//ARS_COMMENTS::RETORNA REFERÊNCIA
		return *newBin;
	}
	//------------------------------------------------------------------------------------------------
	//Binário randômico com interpolação e fitness
	ARS_Bin& ARS_RandomBin_IFitness(int size){
		ARS_Bin* newBin = new ARS_Bin(size);

		string value;
		
		int* High = newBin->Higher();

		for(int i = 0; i < size; i++){
			int Random = rand() % 2;
			High[i]    = Random;
		}

		newBin->CalcDec();

		//ARS_COMMENTS::RETORNA REFERÊNCIA
		return *newBin;
	}
	//------------------------------------------------------------------------------------------------
	/*ARS_COMMENTS::POPULATION CREATOR METHODS*/
	//------------------------------------------------------------------------------------------------
	void ARS_SimplePopulationRandom(
		ARS_Population& _population, 
		int quantity,
		int DNAsCount, 
		int DNACodificationSize){

		//ARS_COMMENTS::INSERE ELEMENTO NA POPULAÇÃO	
		for(int i = 0; i < quantity; i++){
			ARS_Being* newBeing = new ARS_Being(_population);
			_population.InsertBeing(newBeing);
		}
	}
	//------------------------------------------------------------------------------------------------
	/*ARS_COMMENTS::POPULATION CREATOR METHODS*/
	//------------------------------------------------------------------------------------------------
	/*ARS_COMMENTS::SELECTION METHODS*/
	//------------------------------------------------------------------------------------------------
	//TODO::VER NECESSIDADE DE IMPLEMENTAR
	//------------------------------------------------------------------------------------------------

	//------------------------------------------------------------------------------------------------
	/*ARS_COMMENTS::CROSS METHODS*/
	ARS_Bin** ARS_SinglePointCrossover(ARS_PopulationConfig& config, ARS_Bin& A, ARS_Bin& B, int& decA, int& decB, int cutPoint){
		int sizeA = A.Size();
		int sizeB = B.Size();

		if(sizeA != sizeB)
			return NULL;

		if(cutPoint < 1 || cutPoint >= sizeA)
			return NULL;

		//ARS_COMMENTS::CRIA FILHO PARA RETORNAR DENTRO DO PAI
		ARS_Bin** children = new ARS_Bin*[2];

		children[0] = new ARS_Bin(sizeA);//setSize(sizeA);
		children[1] = new ARS_Bin(sizeA);//setSize(sizeB);

		int* childrenA = children[0]->Higher();
		int* childrenB = children[1]->Higher();

		int* fatherA = A.Higher();
		int* fatherB = B.Higher();

		for(int i = 0; i < A.Size(); i++){
			if(i < cutPoint){
				childrenA[i] = fatherA[i];
				childrenB[i] = fatherB[i];
			}else{
				childrenA[i] = fatherB[i];
				childrenB[i] = fatherA[i];
			}

			//Deve ser aplicado aqui para garantir mutação bit a bit
			int primaryCutPoint = rand() % A.Size();
			Applymutation(config, *children[0], primaryCutPoint, A.Size());

			primaryCutPoint = rand() % A.Size();
			Applymutation(config, *children[1], primaryCutPoint, A.Size());
		}

		children[0]->CalcDec();
		children[1]->CalcDec();

		return children;
	}
	//------------------------------------------------------------------------------------------------
	ARS_Bin** ARS_TwoPointCrossover(ARS_PopulationConfig& config, ARS_Bin& A, ARS_Bin& B, int& decA, int& decB, int FirstCutPoint, int SecondCutPoint){
		int sizeA = A.Size();
		int sizeB = B.Size();

		if(sizeA != sizeB)
			return NULL;

		if(FirstCutPoint == SecondCutPoint)
			return ARS_SinglePointCrossover(config, A,B,decA, decB,FirstCutPoint);

		int MinCutPoint = 0;
		int MaxCutPoint = 0;

		if(FirstCutPoint > SecondCutPoint){
			MinCutPoint = SecondCutPoint;
			MaxCutPoint = FirstCutPoint;

		}else{
			MinCutPoint = FirstCutPoint;
			MaxCutPoint = SecondCutPoint;
		}

		if(MaxCutPoint >= sizeA || MinCutPoint < 1)
			return NULL;

		//ARS_COMMENTS::CRIA FILHO PARA RETORNAR DENTRO DO PAI
		ARS_Bin** children = new ARS_Bin*[2];

		children[0] = new ARS_Bin(sizeA);//setSize(sizeA);
		children[1] = new ARS_Bin(sizeA);//setSize(sizeB);

		int* childrenA = children[0]->Higher();
		int* childrenB = children[1]->Higher();

		int* fatherA = A.Higher();
		int* fatherB = B.Higher();

		for(int i = 0; i < A.Size(); i++){
			if(i < MinCutPoint || i > MaxCutPoint - 1){
				childrenA[i] = fatherA[i];
				childrenB[i] = fatherB[i];
			}else{
				childrenA[i] = fatherB[i];
				childrenB[i] = fatherA[i];
			}

			//Deve ser aplicado aqui para garantir mutação bit a bit
			int primaryCutPoint = rand() % A.Size();
			Applymutation(config, *children[0], primaryCutPoint, A.Size());

			primaryCutPoint = rand() % A.Size();
			Applymutation(config, *children[1], primaryCutPoint, A.Size());
		}
		
		children[0]->CalcDec();
		children[1]->CalcDec();

		return children;
	}
	//------------------------------------------------------------------------------------------------
	ARS_Bin** ARS_MultiPointCrossover(ARS_PopulationConfig& config, ARS_Bin& A, ARS_Bin& B, int& decA, int& decB, int quantity ,...){
		int sizeA = A.Size();
		int sizeB = B.Size();

		if(sizeA != sizeB)
			return NULL;

		std::list<int> _cutPoints;

		VA_START(quantity);
		for(int i = 0; i < quantity; i++){
			int _cutPoint = va_arg(arguments, int);

			_cutPoints.push_back(_cutPoint);
		}
		VA_END();

		//_cutPoints.sort();

		//ARS_COMMENTS::PARA REMOVER DUPLICADOS
		//Unifier uni;

		//_cutPoints.remove_if(uni);

		if(_cutPoints.front() < 1 || _cutPoints.back() >= sizeA)
			return NULL;

		if(_cutPoints.size() == 0)
			return NULL;

		if(_cutPoints.size() == 2)
			return ARS_TwoPointCrossover(config, A,B, decA, decB, _cutPoints.back(), _cutPoints.front());

		if(_cutPoints.size() == 1)
			return ARS_SinglePointCrossover(config, A,B, decA, decB, _cutPoints.front());

		//ARS_COMMENTS::CRIA FILHO PARA RETORNAR DENTRO DO PAI
		ARS_Bin** children = new ARS_Bin*[2];

		children[0] = new ARS_Bin(sizeA);//setSize(sizeA);
		children[1] = new ARS_Bin(sizeA);//setSize(sizeB);

		int* childrenA = children[0]->Higher();
		int* childrenB = children[1]->Higher();

		int* fatherA = A.Higher();
		int* fatherB = B.Higher();

		list<int>::iterator it = _cutPoints.begin();
		int ListCurElement = *it;

		bool swap = false;
		for(int i = 0; i < sizeA; i++){
			if(i == ListCurElement){
				swap = !swap;

				it++;

				if(it!=_cutPoints.end())
					ListCurElement = *it;
			}

			if(swap){
				childrenA[i] = fatherB[i];
				childrenB[i] = fatherA[i];
			}else{
				childrenA[i] = fatherA[i];
				childrenB[i] = fatherB[i];
			}

			//Deve ser aplicado aqui para garantir mutação bit a bit
			//Deve ser aplicado aqui para garantir mutação bit a bit
			int primaryCutPoint = rand() % A.Size();
			Applymutation(config, *children[0], primaryCutPoint, A.Size());

			primaryCutPoint = rand() % A.Size();
			Applymutation(config, *children[1], primaryCutPoint, A.Size());
		}

		children[0]->CalcDec();
		children[1]->CalcDec();

		return children;
	}

	//------------------------------------------------------------------------------------------------
	ARS_Bin** ARS_UniformCrossover(ARS_PopulationConfig& config, ARS_Bin& A, ARS_Bin& B, int& decA, int& decB, int* Mask){
		int sizeA = A.Size();
		int sizeB = B.Size();

		if(sizeA != sizeB)
			return NULL;

		//ARS_COMMENTS::CRIA FILHO PARA RETORNAR DENTRO DO PAI
		ARS_Bin** children = new ARS_Bin*[2];

		children[0] = new ARS_Bin(sizeA);//setSize(sizeA);
		children[1] = new ARS_Bin(sizeA);//setSize(sizeB);

		int* childrenA = children[0]->Higher();
		int* childrenB = children[1]->Higher();

		int* fatherA = A.Higher();
		int* fatherB = B.Higher();

		bool useMask = false;

		if(Mask != NULL)
			useMask = true;

		//if(useMask){
		//	int _maskSize = sizeof(Mask)/sizeof(int);
//
		//	if(_maskSize != sizeA)
		//		return NULL;
		//}

		for(int i = 0; i < sizeA; i++){
			int _maskLayer;
			if(useMask){
				_maskLayer = Mask[i];
			}else{
				_maskLayer = rand() % 2;
			}

			if(_maskLayer == 0){
				childrenA[i] = fatherB[i];
				childrenB[i] = fatherA[i];
			}else{
				childrenA[i] = fatherA[i];
				childrenB[i] = fatherB[i];
			}

			//Deve ser aplicado aqui para garantir mutação bit a bit
			int primaryCutPoint = rand() % A.Size();
			Applymutation(config, *children[0], primaryCutPoint, A.Size());

			primaryCutPoint = rand() % A.Size();
			Applymutation(config, *children[1], primaryCutPoint, A.Size());
		}

		children[0]->CalcDec();
		children[1]->CalcDec();

		return children;
	}
	//------------------------------------------------------------------------------------------------
	ARS_Bin* ARS_ThreeParentCrossover(ARS_PopulationConfig& config, ARS_Bin& A, ARS_Bin& B, ARS_Bin& C, int& decA, int& decB, int& decC){
		int sizeA = A.Size();
		int sizeB = B.Size();
		int sizeC = C.Size();

		if(sizeA != sizeB || sizeA != sizeC || sizeC != sizeB)
			return NULL;

		//ARS_COMMENTS::CRIA FILHO PARA RETORNAR DENTRO DO PAI
		ARS_Bin* children;
		children = new ARS_Bin(sizeA);

		int* fatherA = A.Higher();
		int* fatherB = B.Higher();
		int* fatherC = C.Higher();

		int* childrenA = children->Higher();

		for(int i = 0; i < sizeA; i++){
			if(fatherA[i] == fatherB[i])
				childrenA[i] = fatherA[i];
			else
				childrenA[i] = fatherC[i];
		
			//Deve ser aplicado aqui para garantir mutação bit a bit
			int primaryCutPoint = rand() % A.Size();
			Applymutation(config, *children, primaryCutPoint, A.Size());

		}

		children->CalcDec();
		
		return children;
	}
	/*ARS_COMMENTS::MUTATION METHODS*/
	//------------------------------------------------------------------------------------------------
	ARS_Bin** ARS_ShuffleCrossover(ARS_PopulationConfig& config, ARS_Bin& A, ARS_Bin& B, int& decA, int& decB, int* Mask){
		int sizeA = A.Size();
		int sizeB = B.Size();

		if(sizeA != sizeB)
			return NULL;

		//ARS_COMMENTS::CRIA FILHO PARA RETORNAR DENTRO DO PAI
		ARS_Bin** children = new ARS_Bin*[2];

		children[0] = new ARS_Bin(sizeA);//setSize(sizeA);
		children[1] = new ARS_Bin(sizeA);//setSize(sizeB);

		int* childrenA = children[0]->Higher();
		int* childrenB = children[1]->Higher();

		vector<int> fatherAVec;
		vector<int> fatherBVec;

		int* fatherA = A.Higher();
		int* fatherB = B.Higher();
		
		bool useMask = false;

		if(Mask == NULL){
			//ARS_COMMENTS::PREPARANDO E EMBARALHANDO NOVOS GENES PARA CRUZAR
			for(int i = 0; i < sizeA; i++){
				fatherAVec.push_back(fatherA[i]);
				fatherBVec.push_back(fatherB[i]);
			}

			std::random_shuffle(fatherAVec.begin(), fatherAVec.end());
			std::random_shuffle(fatherBVec.begin(), fatherBVec.end());
		}else
			useMask = true;

		if(useMask){
			int _maskSize = sizeof(Mask)/sizeof(int);

			if(_maskSize != sizeA)
				return NULL;
		}

		for(int i = 0; i < sizeA; i++){
			int _maskLayer;
			if(useMask){
				_maskLayer = Mask[i];
			}else{
				_maskLayer = rand() % 2;
			}

			if(_maskLayer == 0){
				childrenA[i] = fatherBVec[i];
				childrenB[i] = fatherAVec[i];
			}else{
				childrenA[i] = fatherAVec[i];
				childrenB[i] = fatherBVec[i];
			}

			//Deve ser aplicado aqui para garantir mutação bit a bit
			int primaryCutPoint = rand() % A.Size();
			Applymutation(config, *children[0], primaryCutPoint, A.Size());

			primaryCutPoint = rand() % A.Size();
			Applymutation(config, *children[0], primaryCutPoint, A.Size());
		}

		children[0]->CalcDec();
		children[1]->CalcDec();

		return children;
	}
	//------------------------------------------------------------------------------------------------
	ARS_Bin* ARS_PrecedencePreservativeCrossover(ARS_PopulationConfig& config, ARS_Bin& A, ARS_Bin& B, int& decA, int& decB, int* Operations){
		bool useOperations = false;
		int sizeA = A.Size();
		int sizeB = B.Size();
		int OpSize = 0;

		//if(Operations != NULL){
		//	useOperations = true;
		//	OpSize = sizeof(Operations)/sizeof(int);

		//	if(OpSize != sizeA)
		//		return NULL;
		//}		

		if(sizeA != sizeB)
			return NULL;

		//ARS_COMMENTS::CRIA FILHO PARA RETORNAR DENTRO DO PAI
		ARS_Bin* children;

		children = new ARS_Bin(sizeA);//.setSize(sizeA);

		int* childrenA = children->Higher();

		int* fatherA = A.Higher();
		int* fatherB = B.Higher();

		//ARS_COMMENTS::OPERATIONS SIMULATOR S
		vector<int> fatherAVec;
		vector<int> fatherBVec;

		if(!useOperations){
			//ARS_COMMENTS::PREPARANDO E EMBARALHANDO NOVOS GENES PARA CRUZAR
			for(int i = 0; i < sizeA; i++){
				fatherAVec.push_back(fatherA[i]);
				fatherBVec.push_back(fatherB[i]);
			}
		
			//GERA PERMUTAÇÃO
			std::random_shuffle(fatherAVec.begin(), fatherAVec.end());
			std::random_shuffle(fatherBVec.begin(), fatherBVec.end());
		}

		//UTILIZADO PARA SABER DE QUEM PEGAR O BIT
		bool op = false;

		//ARS_COMMENTS::CADA HORA É A VEZ DE UMA OPERAÇÃO EXECUTAR
		//ARS_COMMENTS::SE CASO A OPERAÇÃO FOR 0 ENTÃO TROCA OS GENES
		//ARS_COMMETNS::CASO CONTRÁRIO DEIXA COMO ESTÁ
		for(int i = 0; i < sizeA; i++){
			op = true;

			if(useOperations){
				if(Operations[i] == 0)
					op = false;
			}else{
				int _operation = rand()%2; // Pega operação randomica para calcular o cruzamento
				if(_operation == 0)
					op = false;
			}

			//ARS_COMMENTS::DE ACORDO COM A OPERAÇÃO NO VETOR PEGAR O RESPECTIVO BIT DO PAI
			if(op)
				childrenA[i] = fatherAVec[i];
			else
				childrenA[i] = fatherBVec[i];

			//Deve ser aplicado aqui para garantir mutação bit a bit
			int primaryCutPoint = rand() % A.Size();
			Applymutation(config, *children, primaryCutPoint, A.Size());
		}

		children->CalcDec();
		
		return children;
	}
	//------------------------------------------------------------------------------------------------
	void OrderedCrossoverHelper(int vecSize, int* A, int* B, int* Son, int MinCutPoint, int MaxCutPoint){
		int size = vecSize;
		int oneCount   = 0;
		int zeroCount = 0;

		//Contar zeros e uns do vetor que se esta verificando
		for(int i = MinCutPoint; i < MaxCutPoint; i++){
			if(A[i] == 0)
				zeroCount++;
			else
				oneCount++;
		}

		int _curJ = 0;
		//verificar a ordem dos elementos em B para inserir em A
		for(int i = MinCutPoint; i < MaxCutPoint; i++){
			for(int j = _curJ; j <size; j++){
				if(B[j] == 0 && zeroCount > 0){
					Son[i] = 0;
					zeroCount --;
					_curJ++;
					break;
				}else if(B[j] == 1 && oneCount >0){
					Son[i] = 1;
					oneCount --;
					_curJ++;
					break;
				}else if(j+1 == size)
					Son[i] = A[i];
			}
		}
	}
	//------------------------------------------------------------------------------------------------
	ARS_Bin** ARS_OrderedCrossover(ARS_PopulationConfig& config, ARS_Bin& A, ARS_Bin& B, int& decA, int& decB, int FirstCutPoint, int SecondCutPoint){
		int sizeA = A.Size();
		int sizeB = B.Size();

		if(sizeA != sizeB)
			return NULL;

		if(FirstCutPoint == SecondCutPoint)
			return ARS_SinglePointCrossover(config, A,B, decA, decB, FirstCutPoint);

		int MinCutPoint = 0;
		int MaxCutPoint = 0;

		if(FirstCutPoint > SecondCutPoint){
			MinCutPoint = SecondCutPoint;
			MaxCutPoint = FirstCutPoint;

		}else{
			MinCutPoint = FirstCutPoint;
			MaxCutPoint = SecondCutPoint;
		}

		if(MaxCutPoint >= sizeA || MinCutPoint < 1)
			return NULL;

		//ARS_COMMENTS::CRIA FILHO PARA RETORNAR DENTRO DO PAI
		ARS_Bin** children = new ARS_Bin*[2];

		children[0] = new ARS_Bin(sizeA);//setSize(sizeA);
		children[1] = new ARS_Bin(sizeA);//setSize(sizeB);

		int* childrenA = children[0]->Higher();
		int* childrenB = children[1]->Higher();

		int* fatherA = A.Higher();
		int* fatherB = B.Higher();
		
		for(int i = 0; i < sizeA; i++){
			if(i < MinCutPoint || i > MaxCutPoint - 1){
				childrenA[i] = fatherA[i];
				childrenB[i] = fatherB[i];
			}else{
				//ARS_COMMENTS::TRATA ORDEM FILHO 1
				OrderedCrossoverHelper(sizeA, fatherA, fatherB, childrenA, MinCutPoint, MaxCutPoint);

				//ARS_COMMENTS::TRATA ORDEM FILHO 2
				OrderedCrossoverHelper(sizeA, fatherB, fatherA, childrenB, MinCutPoint, MaxCutPoint);
			}

			//Deve ser aplicado aqui para garantir mutação bit a bit
			int primaryCutPoint = rand() % A.Size();
			Applymutation(config, *children[0], primaryCutPoint, A.Size());

			primaryCutPoint = rand() % A.Size();
			Applymutation(config, *children[0], primaryCutPoint, A.Size());
		}

		children[0]->CalcDec();
		children[1]->CalcDec();

		return children;
	}
	//------------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------------
	ARS_Bin& ARS_Flipping(ARS_Bin& value, int gene){
		int geneX;
		int* High = value.Higher();
		int size = value.Size();

		if(gene < 0 || gene >= size)
			geneX = rand()%size;
		else
			geneX = gene;

		High[geneX] = !High[geneX];

		return value;
	}
	//------------------------------------------------------------------------------------------------
	ARS_Bin& ARS_Interchanging(ARS_Bin& value, int geneA, int geneB){
		int geneXA;
		int geneXB;
		int* High = value.Higher();
		int size = value.Size();

		if(geneA < 0  || geneA >= size)
			geneXA = rand()%size;
		else
			geneXA = geneA;

		if(geneB < 0 || geneB >= size)
			geneXB = rand()%size;
		else
			geneXB = geneB;

		int interchangeA = High[geneXA];

		High[geneXA] = High[geneXB];
		High[geneXB] = interchangeA;

		return value;
	}
	//------------------------------------------------------------------------------------------------
	ARS_Bin ARS_Reversing(ARS_Bin& value, int gene){
		int geneX;
		int* High = value.Higher();
		int size = value.Size();

		if(gene < 0 || gene >= size)
			geneX = rand()%size;
		else
			geneX = gene;

		ARS_Bin child;

		child.setSize(value.Size());

		if(geneX+1 != size)
			High[geneX+1] = !High[geneX+1];
		
		if(geneX-1 >= 0)
			High[geneX-1] = !High[geneX-1];

		//ARS_COMMENTS::FAZENDO CÓPIA DO FILHO
		int* childHigh = child.Higher();

		for(int i = 0; i < value.Size(); i++)
			childHigh[i] = High[i];

		return child;
	}
	//------------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------------

	//------------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------------
}//ARS_COMMENTS::END NAMESPACE ARS_OPERATIONS 
