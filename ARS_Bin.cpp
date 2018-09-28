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
#include "ARS_Bin.h"

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

ARS_Bin::ARS_Bin(int size, int precision){
	ID = 0;

	// Parte inteira
	higher = new int [size];
	memset(higher, 0, sizeof(int)*size);

	// Parte fracionária
	lower  = new int [precision];
	memset(lower, 0, sizeof(int)*precision);

	// Configurando variáveis
	this->size      = size;
	this->precision = precision;

	decimal = 0.0;
	setValue(0.0);
}
//------------------------------------------------------------------------------------------------
void ARS_Bin::CalcDec(){
	int _intPart = 0;
	int exp = size - 1;

	for(int i = 0; i < size; i++){
		int current = higher[i];

		_intPart += (int)pow(2.0, exp) * current;
		exp--;
	}

	decimal = _intPart;
}
//------------------------------------------------------------------------------------------------
ARS_Bin::~ARS_Bin(void){
	// Deletando ponteiros
	//delete []higher;
	//delete []lower;

	//TODO::ARRUMAR ESSE DELETE

	// Garantindo memória limpa
	higher = 0x0;
	lower  = 0x0;
}
//------------------------------------------------------------------------------------------------
void ARS_Bin::setSize(int size){
	delete []higher;
	higher = 0x0;

	// Parte inteira
	higher = new int [size];
	memset(higher, 0, sizeof(int)*size);

	// Configurando variáveis
	this->size      = size;

	decimal = 0.0;
	setValue(0.0);
}
//------------------------------------------------------------------------------------------------
void ARS_Bin::setValue(double value){
	// Parte inteira
	int high = (int)value;

	// Verifica se o número cabe no meu binário
	if(high > pow(2.0, size) - 1)
		return;

	// Atribui valor decimal
	decimal = value;

	// Parte fracionária
	double fraction = value - high;

	int _mod     = high % 2;
	high        /= 2;
	int _counter = 0;

	higher[_counter] = _mod;

	// Parte inteira
	while(high > 0){
		_mod  = high % 2;
		high /= 2;

		higher[_counter] = _mod;

		_counter++;
	}

	// Parte fracionária

	for(int i = 0; i < precision; i++){
		fraction = fraction * 2;

		// Pega parte inteira
		int binRes = (int)fraction;

		// Pega parte fracionária para novo cálculo
		fraction = fraction - binRes;

		// Atribui meu binário
		lower[i] = binRes;
	}
}
//------------------------------------------------------------------------------------------------
void ARS_Bin::setValue(const char* binValue){
	int _lenght = strlen(binValue);

	// TODO::Colocar erro aqui
	if(_lenght <= 0)
		return;

	double decimalRes = 0.0;

	vector<string> splited = split(binValue, ",");

	// Configura parte inteira
	if(splited.size() <= 0)
		return;

	string _int = splited[0];

	int _intPart = 0;

	for(int i = _int.length() - 1; i >= 0; i--){
		char _current = _int[i];
		int bit = atoi(&_current);

		_intPart += (int)pow(2.0, (int)i) * bit;

		higher[i] = bit;
	}

	decimal = _intPart;

	// Configura parte fracionária
	if(splited.size() < 2)
		return;

	string _frac = splited[1];

	double _fracPart = 0.0;

	for(unsigned int i = 0; i < _frac.length(); i++){
		char _current = _frac[i];
		int bit = atoi(&_current);

		_fracPart += (1.0 / pow(2.0, (int)i)) * bit;

		lower[i] = bit;
	}

	// Atribuindo decimal
	decimal += _fracPart;
}
//------------------------------------------------------------------------------------------------
void ARS_Bin::printDecimal(){
	printf("Decimal value: %4.4f\n", decimal);
}
//------------------------------------------------------------------------------------------------
void ARS_Bin::printBinary(bool both){
	printf("Binary value: ");
	for(int i = 0; i < size; i++)
		printf("%i", higher[i]);

	if(both){
		printf(".");
		for(int i = 0; i < precision; i++)
			printf("%i", lower[i]);
	}

	printf("\n");
}
//------------------------------------------------------------------------------------------------
string ARS_Bin::getHighBinString(){
	ostringstream  ss;

	for(int i = 0; i < size; i++)
		ss << higher[i];

	return ss.str();
}
//------------------------------------------------------------------------------------------------
string ARS_Bin::getLowBinString(){
	ostringstream  ss;

	for(int i = 0; i < precision; i++)
		ss << lower[i];

	return ss.str();
}
//------------------------------------------------------------------------------------------------
int ARS_Bin::Size(){return size;}
//------------------------------------------------------------------------------------------------
int ARS_Bin::Precision(){return precision;}
//------------------------------------------------------------------------------------------------
int* ARS_Bin::Higher(){return higher;}
//------------------------------------------------------------------------------------------------
int* ARS_Bin::Lower(){return lower;}
//------------------------------------------------------------------------------------------------
double& ARS_Bin::Decimal(){return decimal;} 
//------------------------------------------------------------------------------------------------
