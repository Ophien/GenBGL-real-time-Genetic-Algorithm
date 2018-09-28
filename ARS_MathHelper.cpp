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
#include "ARS_MathHelper.h"

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

namespace ARS_MathHelper{
	//------------------------------------------------------------------------------------------------
	long double PI = 4.0*atan(1.0);
	double E  = 2.71828;
	//------------------------------------------------------------------------------------------------
	double ARS_fRand(double fMin, double fMax)
	{
		double f = (double)rand() / RAND_MAX;
		return fMin + f * (fMax - fMin);
	}
	//------------------------------------------------------------------------------------------------
	double ARS_fRand()
	{
		double f = (double)rand();
		double f2 = (double)rand() / RAND_MAX;
		return f + f2;
	}
	//------------------------------------------------------------------------------------------------
	double ARS_Gauss(double value, double average, double variance, double deviation){
		double _SquareVariance = pow( variance, 2.0);
		double _XiMinusAverage = pow( (value - average), 2.0);
		double _EPow           = -1 * ( _XiMinusAverage / (2 * _SquareVariance));
		double _E              = pow( E, _EPow);
		double _fraction       = sqrtl(2*PI*_SquareVariance);
		double _gauss          = ( 1 / _fraction ) * _E;

		return _gauss;
	}
	//------------------------------------------------------------------------------------------------
	double ARS_Gauss(double mean, double variance){
		/*for(;;) {
			double u1 = ARS_fRand();
			double u2 = ARS_fRand();
			double v1 = 2 * u1 - 1;
			double v2 = 2 * u2 - 1;
			double w  = (v1 * v1) + (v2 * v2);

			if (w <= 1) {
				double y  = sqrt( (-2 * log(w)) / w);
				double x1 = v1 * y;
				return(x1 * sqrt(variance) + mean);
			}
		}*/
		return (double)sqrt(10.0) + mean;
	}
	//------------------------------------------------------------------------------------------------
}
