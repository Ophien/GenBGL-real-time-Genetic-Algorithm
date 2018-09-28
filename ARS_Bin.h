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

#ifndef ARS_BIN_H
#define ARS_BIN_H
//------------------------------------------------------------------------------------------------
//ARS_COMMENTS::SYSTEM INCLUDES
//------------------------------------------------------------------------------------------------
#include <iostream>
#include <stdio.h>
#include <ostream>
#include <istream>
#include <sstream>
#include "ARS_Helper.h"

//------------------------------------------------------------------------------------------------
//ARS_COMMENTS::INTERNAL INCLUDE
//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
//ARS_COMMENTS::USED NAMESPACES
//------------------------------------------------------------------------------------------------
using namespace std;
using namespace ARS_Helper;

//------------------------------------------------------------------------------------------------
//ARS_COMMENTS::DEFINITIONS
//------------------------------------------------------------------------------------------------
#define DEFAULT_SIZE      4
#define DEFAULT_PRECISION 4

//------------------------------------------------------------------------------------------------
//ARS_COMMENTS::MACROS
//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
//ARS_COMMENTS::CONSTANTS
//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
//ARS_COMMENTS::GLOBAL FUNCTIONS BODYS
//------------------------------------------------------------------------------------------------

class ARS_Bin{
public:
	int ID;
	ARS_Bin(int size = DEFAULT_SIZE, int precision = DEFAULT_PRECISION);
	~ARS_Bin(void);
	void setValue(double value);
	void setValue(const char* binValue);
	void printDecimal();
	void printBinary(bool both = false);
	string getHighBinString();
	string getLowBinString();
	int Size();
	int Precision();
	int* Higher();
	int* Lower();
	double& Decimal();
	void setSize(int size);
	void CalcDec();

	//ARS_COMMENTS::BINARY
	const ARS_Bin operator+(const ARS_Bin& _value){ARS_Bin a; return a;}
	ARS_Bin operator-(const ARS_Bin& _value){ARS_Bin a; return a;}
	ARS_Bin operator/(const ARS_Bin& _value){ARS_Bin a; return a;}
	ARS_Bin operator*(const ARS_Bin& _value){ARS_Bin a; return a;}
	
	//ARS_COMMENTS::UNARY
	const ARS_Bin& operator+=(const ARS_Bin& _value){return _value;}
	const ARS_Bin& operator-=(const ARS_Bin& _value){return _value;}
	const ARS_Bin& operator/=(const ARS_Bin& _value){return _value;}
	const ARS_Bin& operator*=(const ARS_Bin& _value){return _value;}
	const ARS_Bin& operator<<(const ARS_Bin& _value){return _value;}
	const ARS_Bin& operator>>(const ARS_Bin& _value){return _value;}

private:
	double decimal;

	int*   higher;
	int*   lower;
	int    size;
	int    precision;
};
#endif
