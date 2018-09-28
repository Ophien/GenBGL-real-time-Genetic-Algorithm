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
#include "ARS_BenchmarkFunctions.h"
#include "ARS_MathHelper.h"
#include "ARS_Helper.h"
#include "Defaults.h"
#include "LimitH.h"

//------------------------------------------------------------------------------------------------
//ARS_COMMENTS::USED NAMESPACES
//------------------------------------------------------------------------------------------------
using namespace ARS_Helper;
using namespace ARS_MathHelper;
using namespace LIMITS;

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


namespace ARS_BenchmarkFunctions{
	double max = pow(2.0,(int)sizeof(double))-1;
	//------------------------------------------------------------------------------------------------
	const int FoxHolesConstants[2][25] = {
		{-32, -16, 0, 16, 32, -32, -16, 0, 16, 32, -32, -16, 0, 16, 32, -32,-16, 0, 16, 32, -32, -16, 0, 16, 32 },
		{-32, -32, -32, -32, -32, -16, -16, -16, -16, -16, 0, 0, 0, 0, 0, 16, 16, 16, 16, 16, 32, 32, 32, 32, 32  }};
		//------------------------------------------------------------------------------------------------
		FitnessFunc GetFitnessFunction(int ID){
			switch(ID){
			case ARS_SPHERE:
				return Sphere;
				break;
			case ARS_ROSENBROCK:
				return Rosenbrock;
				break;
			case ARS_DEJONG_STEP:
				return DeJongStep;
				break;
			case ARS_DEJONG_STEPB:
				return DeJonStepB;
				break;
			case ARS_SHEKELS_FOXHOLES:
				return ShekelsFoxholes;
				break;
			case ARS_SCHAFFER:
				return Schaffer;
				break;
			case ARS_SCHAFFERB:
				return SchafferB;
				break;
			case ARS_SPHERE_MODEL:
				return SphereModel;
				break;
			case ARS_SCHWEFEL:
				return Schwefel;
				break;
			case ARS_SCHWEFELB:
				return SchwefelB;
				break;
			case ARS_ACKLEY:
				return Ackley;
				break;
			case ARS_RASTRIGIN:
				return Rastrigin;
				break;
			case ARS_GRIEWANGK:
				return Griewangk;
				break;
			case ARS_SCHWEFEL_PRO:
				return SchwefelPro;
				break;
			case ARS_BOHACHEVSKY:
				return Bohachevsky;
				break;
			case ARS_CINTARIA:
				return Cintaria;
				break;
			case ARS_SAPATEIRO:
				return Sapateiro;
				break;
			case ARS_DIETA:
				return Dieta;
				break;
			case ARS_TRANSPORTE:
				return Transporte;
				break;
			case ARS_REFINARIA:
				return Refinaria;
				break;
			case ARS_FABRICAMOVEIS:
				return FabricaMoveis;
				break;
			case ARS_FABRICAP1P2:
				return FabricaP1P2;
				break;
			case ARS_EXTREMEPROBLEM:
				return EXTREME_PROBLEM;
				break;
			default:
				return Sphere;
				break;
			}
		}
		//------------------------------------------------------------------------------------------------
#if defined(VARIABLE_LIST)
		double Sphere(int n, ...){
			double _result = 0.0;

			VA_START(n);
			for(int i = 1; i <= n; i++){
				double Xi = VA_NEXT(double);
				_result += pow(Xi, 2.0);
			}
			VA_END();

			return _result;
		}
		//------------------------------------------------------------------------------------------------
		double Rosenbrock(int n, ...){
			double _result = 0.0;

			VA_START(n);
			for(int i = 1; i <= n; i++){
				double Xi = VA_NEXT(double);
				double quadraticXi;
				double first;
				double second;

				quadraticXi = pow(Xi, 2.0);

				first       = quadraticXi - Xi + 1;
				first       = 100 * pow( 2.0, first);

				second      = 1 - Xi;
				second      = pow( second, 2.0);

				_result    += first + second;        
			}
			VA_END();

			return _result;
		}
		//------------------------------------------------------------------------------------------------
		double DeJongStep(int n, ...){
			double _result = 0.0;

			VA_START(n);
			for(int i = 1; i <= n; i++){
				double Xi = VA_NEXT(double);
				_result += (int)Xi;
			}
			VA_END();

			return _result;
		}
		//------------------------------------------------------------------------------------------------
		double DeJonStepB(int n, ...){
			double _result = 0.0;

			VA_START(n);
			for(int i = 1; i <= n; i++){
				double Xi = VA_NEXT(double);
				double _pow;

				_pow        = pow(Xi, 4.0);
				_result    += (i * _pow) + ARS_Gauss(0,1);
			}
			VA_END();

			return _result;
		}
		//------------------------------------------------------------------------------------------------
		double ShekelsFoxholes(int n, ...){
			double _result = 0.0;

			//ARS_COMMENTS::PARA NÃO DAR PROBLEMA COM A MATRIZ DE CONSTANTES
			if(n > 25)
				return _result;

			double _const  = 0.002;

			VA_START(n);
			for(int i = 1; i <= n; i++){
				double Xi = VA_NEXT(double);
				double _external = 1;
				double _internal = 0.0;

				for(int j = 1; j <= 2; j ++){
					_internal += pow(6.0, Xi - FoxHolesConstants[j][i]);
				}

				_external = _external / (i + _internal);
				_result  += _external;
			}
			VA_END();

			return _result;
		}
		//------------------------------------------------------------------------------------------------
		double SphereModel(int n, ...){
			double _result         = 0.0;

			VA_START(n);
			for(int i = 1; i <= n; i++){
				double Xi = VA_NEXT(double);
				_result  += pow(Xi, 2.0);
			}
			VA_END();

			return _result;
		}
		//------------------------------------------------------------------------------------------------
		double Schwefel(int n, ...){
			double _result         = 0.0;

			VA_START(n);
			for(int i = 1; i <= n; i++){
				double Xi = VA_NEXT(double);
				_result  += pow(Xi + 0.5,2.0);
			}
			VA_END();

			return _result;
		}
		//------------------------------------------------------------------------------------------------
		double SchwefelB(int n, ...){
			double _result = 0.0;

			VA_START(n);
			for(int i = 1; i <= n; i++){
				double Xi = VA_NEXT(double);

				_result += -1 * Xi * sin(sqrt(abs(Xi)));
			}
			VA_END();

			return _result;
		}
		//------------------------------------------------------------------------------------------------
		double Ackley(int n, ...){
			double _result         = 0.0;

			double _firstSum       = 0.0;
			double _secondSum      = 0.0;

			VA_START(n);
			for(int i = 1; i <= n; i++){
				double Xi = VA_NEXT(double);
				_firstSum  += pow(Xi, 2.0);
				_secondSum += cos(2*PI*Xi);
			}
			VA_END();

			double _firstSumPow;
			double _FirstExp;
			double _SecondExp;

			_firstSumPow = pow(0.5, 1/n*_firstSum);
			_firstSum    = -0.2 * _firstSumPow;
			_secondSum   =  1/n * _secondSum;

			_FirstExp  = exp(_firstSum);
			_SecondExp = exp(_secondSum);

			_result = -20 * _FirstExp - _SecondExp + 20 + E;

			return _result;
		}
		//------------------------------------------------------------------------------------------------
		double Rastrigin(int n, ...){
			double _result = 0.0;

			VA_START(n);
			for(int i = 1; i <= n; i++){
				double Xi = VA_NEXT(double);
				double _internal = 0.0;

				_internal = pow(Xi, 2.0) - 10.0 * cos(2*PI*Xi);

				_result  += _internal;
			}
			VA_END();

			_result = 10*n+_result;

			return _result;
		}
		//------------------------------------------------------------------------------------------------
		double Griewangk(int n, ...){
			double _result = 0.0;
			double _sum    = 0.0;
			double _prod   = 0.0;

			VA_START(n);
			for(int i = 1; i <= n; i++){
				double Xi = VA_NEXT(double);

				_sum  += pow(Xi, 2.0) / 4000;
				_prod *= Xi / sqrt((double)i);
			}
			VA_END();

			_result = 1 + _sum - _prod;

			return _result;
		}
		//------------------------------------------------------------------------------------------------
		double SchwefelPro(int n, ...){
			double _result = 0.0;

			double* values = new double[n];
			memset(values, 0, sizeof(double)*n);

			VA_START(n);
			for(int i = 0; i < n; i++){
				double Xi = VA_NEXT(double);
				values[i] = Xi;
			}
			VA_END();

			for(int i = 1; i <= n; i++){
				double _internalSum = 0.0;

				for(int j = 1; j <= i; j++){
					double Xj    =  values[j-1];
					_internalSum += Xj;
				}

				_result += pow(_internalSum, 2.0);
			}

			delete []values;

			return _result;
		}
		//------------------------------------------------------------------------------------------------
		double Bohachevsky(int n, ...){
			double _result = 0.0;

			VA_START(n);
			for(int i = 1; i <= n-1; i++){
				double Xi     = VA_NEXT(double);
				double XiPlus = VA_NEXT(double);

				double _powXi     = pow(Xi, 2.0);
				double _powXiPlus = pow(XiPlus,2.0);

				_result += _powXi + _powXiPlus - 0.3 * cos(3*PI*Xi) - 0.4 * cos(4*PI*XiPlus) + 0.7;
			}
			VA_END();

			return _result;
		}
#endif
		//------------------------------------------------------------------------------------------------
		double Sphere(int size, vector<double>& values){
			int     n      = size;
			double _result = 0.0;

#pragma omp parallel for reduction(+:_result)
			for(int i = 1; i <= n; i++){
				_result += pow(values[i-1], 2.0);
			}

			return _result;
		}
		//------------------------------------------------------------------------------------------------
		double Rosenbrock(int size, vector<double>& values){
			int     n      = size;
			double _result = 0.0;

			for(int i = 1; i <= n; i++){
				double quadraticXi;
				double first;
				double second;

				quadraticXi = pow(values[i-1], 2.0);

				first       = quadraticXi - values[i-1] + 1;
				first       = 100 * pow(first, 2.0);

				second      = 1 - values[i-1];
				second      = pow( second, 2.0);

				_result    += first + second;        
			}

			return _result;
		}
		//------------------------------------------------------------------------------------------------
		double DeJongStep(int size, vector<double>& values){
			int     n      = size;
			double _result = 0.0;

			for(int i = 1; i <= n; i++){
				_result += (int)values[i-1];
			}

			return _result;
		}
		//------------------------------------------------------------------------------------------------
		double DeJonStepB(int size, vector<double>& values){
			int     n      = size;
			double _result = 0.0;

			if(size <= 1)
				return _result;

			for(int i = 1; i <= n; i++){
				double _pow;

				_pow        = pow(4.0, values[i-1]);
				_result    += (i * _pow) + ARS_Gauss(0,1);
			}

			return _result;
		}
		//------------------------------------------------------------------------------------------------
		double ShekelsFoxholes(int size, vector<double>& values){
			int     n      = size;
			double _result = 0.0;

			//ARS_COMMENTS::PARA NÃO DAR PROBLEMA COM O VETOR DE CONSTANTES
			if(n > 25)
				return _result;

			double _const  = 0.002;

			for(int i = 1; i <= n; i++){
				double _external = 1;
				double _internal = 0.0;

				for(int j = 1; j <= 2; j ++){
					_internal += pow(6.0, values[i-1] - FoxHolesConstants[j][i]);
				}

				_external = _external / (i + _internal);
				_result  += _external;
			}

			return _result;
		}
		//------------------------------------------------------------------------------------------------
		double Schaffer(int size, vector<double>& values){
			if(size!=2)
				return 0.0;

			double _result         = 0.0;
			double _powX1          = pow( values[0], 2.0);
			double _powX2          = pow( values[1], 2.0);
			double _powX1X2        = pow( _powX1 + _powX2, 0.25);

			double _powX1X2SinPart = pow( _powX1 + _powX2, 0.1); 
			double _sinPart        = sin(sin(50*_powX1X2SinPart)) + 1.0;

			_result = _powX1X2 * _sinPart;

			return _result;
		}
		//------------------------------------------------------------------------------------------------
		double SchafferB(int size, vector<double>& values){
			if(size!=2)
				return 0.0;

			double _result         = 0.0;
			double _powX1          = pow( values[0], 2.0);
			double _powX2          = pow( values[1], 2.0);

			double _firstPart      = (_powX1 + _powX2)/2;
			double _secondPart     = cos(20*PI*values[0])*cos(20*PI*values[1]);

			_result = _firstPart - _secondPart + 2;

			return _result;
		}
		//------------------------------------------------------------------------------------------------
		double SphereModel(int size, vector<double>& values){
			int     n              = size;
			double _result         = 0.0;

			for(int i = 1; i <= n; i++){
				_result += pow( values[i-1], 2.0);
			}

			return _result;
		}
		//------------------------------------------------------------------------------------------------
		double Schwefel(int size, vector<double>& values){
			int     n              = size;
			double _result         = 0.0;

			for(int i = 1; i <= n; i++){
				_result += pow( values[i-1] + 0.5, 2.0);
			}

			return _result;
		}
		//------------------------------------------------------------------------------------------------
		double SchwefelB(int size, vector<double>& values){
			int n = size;
			double _result = 0.0;

			for(int i = 1; i <= n; i++){
				double Xi = values[i-1];

				_result += -1 * Xi * sin(sqrt(abs(Xi)));
			}

			return _result;
		}
		//------------------------------------------------------------------------------------------------
		double Ackley(int size, vector<double>& values){
			int     n              = size;
			double _result         = 0.0;

			double _firstSum       = 0.0;
			double _secondSum      = 0.0;

			for(int i = 1; i <= n; i++){
				double Xi   = values[i-1];
				_firstSum  += pow(Xi, 2.0);
				_secondSum += cos(2*PI*Xi);
			}

			double _firstSumPow;
			double _FirstExp;
			double _SecondExp;

			_firstSumPow = pow(0.5, 1/n*_firstSum);
			_firstSum    = -0.2 * _firstSumPow;
			_secondSum   =  1/n * _secondSum;

			_FirstExp  = exp(_firstSum);
			_SecondExp = exp(_secondSum);

			_result = -20 * _FirstExp - _SecondExp + 20 + E;

			return _result;
		}
		//------------------------------------------------------------------------------------------------
		double Rastrigin(int size, vector<double>& values){
			int n = size;
			double _result = 0.0;

			for(int i = 1; i <= n; i++){
				double Xi        = values[i-1];
				double _internal = 0.0;

				_internal = pow(Xi, 2.0) - 10 * cos(2*PI*Xi);

				_result  += _internal;
			}

			_result = 10*n+_result;

			return _result;
		}
		//------------------------------------------------------------------------------------------------
		double Griewangk(int size, vector<double>& values){
			int n = size;
			double _result = 0.0;
			double _sum    = 0.0;
			double _prod   = 0.0;

			for(int i = 1; i <= n; i++){
				double Xi = values[i-1];

				_sum  += pow(Xi, 2.0) / 4000;
				_prod *= Xi / sqrt((double)i);
			}

			_result = 1 + _sum - _prod;

			return _result;
		}
		//------------------------------------------------------------------------------------------------
		double SchwefelPro(int size, vector<double>& values){
			int n = size;
			double _result = 0.0;

			for(int i = 1; i <= n; i++){
				double _internalSum = 0.0;

				for(int j = 1; j <= i; j++){
					double Xj    =  values[j-1];
					_internalSum += Xj;
				}

				_result += pow(_internalSum, 2.0);
			}

			return _result;
		}
		//------------------------------------------------------------------------------------------------
		double Bohachevsky(int size, vector<double>& values){
			int n = size;
			double _result = 0.0;

			for(int i = 1; i <= n-1; i++){
				double Xi     = values[i-1];
				double XiPlus = values[i];

				double _powXi     = pow(Xi, 2.0);
				double _powXiPlus = pow( XiPlus , 2.0);

				_result += _powXi + _powXiPlus - 0.3 * cos(3*PI*Xi) - 0.4 * cos(4*PI*XiPlus) + 0.7;
			}

			return _result;
		}
		//------------------------------------------------------------------------------------------------
		double DynamicControl(int size, double* values, double* means){
			int n = size;
			int    meansS  = size;

			if(n != meansS)
				return 0.0;

			double _result = 0.0;

			for(int i = 1; i <= n-1; i++){
				double _XiPow = pow(values[i-1],2.0);
				double _MiPow = pow(means[i-1],2.0);

				_result += _XiPow + _MiPow;
			}

			_result += values[n-1];

			return _result;
		}
		//------------------------------------------------------------------------------------------------
		double Cintaria(int size, vector<double>& values){
			if(size < 2)
				return 0.0;

			double x1, x2, g1, g2, g3, g4, result;

			x1 = values[0];
			x2 = values[1];

			bool Restriction = false;

			if(x1 < 0 || x2 < 0)
				Restriction = true;

			g1 = x1*2 + x2;
			g2 = x1 + x2;
			g3 = x1;
			g4 = x2;

			if(g1 > 1000 || g2 > 800 || g3 > 400 || g4 > 700)
				Restriction = true;

			result = 4*x1 + 3*x2;

			if(Restriction)
				result*=0;

			return result;
		}
		//------------------------------------------------------------------------------------------------
		double Sapateiro(int size, vector<double>& values){
			if(size < 2)
				return 0.0;

			double x1, x2, g1, g2, result;
			bool Restriction = false;

			x1 = values[0];
			x2 = values[1];

			if(x1 < 0 || x2 < 0)
				Restriction = true;

			g1 = 1 / (6 * x1) + 1 / (5 * x2);
			g2 = 2 * x1 + x2;

			if(g1 > 1 || g2 > 6)
				Restriction = true;

			result = 5*x1 + 2*x2;

			if(Restriction)
				result*=0;

			return result;
		}
		//------------------------------------------------------------------------------------------------
		double Dieta(int size, vector<double>& values){
			double result, x1, x2, x3, x4, g1, g2, g3;
			bool res = false;

			if(size < 4)
				return 0.0;

			x1 = values[0];
			x2 = values[1];
			x3 = values[2];
			x4 = values[3];

			g1 = 2*x1 + 2*x2 + 10*x3 + 20*x4;
			g2 = 30*x1 + 20*x2 + 10*x3 + 30*x4;
			g3 = 80*x1 + 70*x2 + 10*x3 + 80*x4;

			if(g1 < 11 || g2 < 70 || g3 < 250)
				res = true;

			result = 2*x1 + 4*x2 + 1.5*x3 + x4;

			if(res)
				result *= 0;
			
			return result;
		}
		//------------------------------------------------------------------------------------------------
		double Transporte(int size, vector<double>& values){
			double result, x1,x2,x3,x4,x5,x6, h1, h2,h3,h4,h5;
			bool res = false;

			if(size < 6)
				return max;

			x1 = values[0];
			x2 = values[1];
			x3 = values[2];
			x4 = values[3];
			x5 = values[4];
			x6 = values[5];

			h1 = x1 + x2 + x3;
			h2 = x4 + x5 + x6;
			h3 = x1 + x4;
			h4 = x2 + x5;
			h5 = x3 + x6;

			if(h1 != 100 || h2 != 50 || h3 != 80 || h4 != 30 || h4 != 40)
				return max;

			result = 7*x1 + 4*x2 + 3*x3 + 3*x4 + x5 + 2*x6;

			return result;
		}
		//------------------------------------------------------------------------------------------------
		double Refinaria(int size, vector<double>& values){
			double result, x1,x2,x3,x4,x5,x6,g1,g2,g3,g4,g5;
			bool res = false;

			if(size < 3)
				return 0.0;

			x1 = values[0];
			x2 = values[1];
			x3 = values[2];

			result = x1 * 0.30 + x2*0.25 + x3*0.20;

			g1 = x1*0.22 + x2*0.52 + x3 * 0.74;
			g2 = x1*0.50 + x2*0.34 + x3 * 0.20;
			g3 = x1*0.28 + x2*0.14 + x3 + 0.06;

			if(g1 > 9600000 || g2 >4800000 || g3 > 2200000 || x2 > 600000 || x3 < 16)
				res = true;

			if(res)
				result *= 0.0;

			return result;
		}
		//------------------------------------------------------------------------------------------------
		double FabricaMoveis(int size, vector<double>& values){
			double result, x1,x2,x3,x4,x5,x6,g1,g2,g3,g4,g5;
			bool res = false;

			if(size < 2)
				return 0.0;

			x1 = values[0];
			x2 = values[1];
				
			g1 = 0.05*x1 + 0.04*x2;
			g2 = 0.033*x1 + 0.025*x2;
			g3 = 0.05*x1 + 0.05*x2;
			g4 = 6*x1 + 4*x2;
	
			result = 200*x1 + 100*x2 - 10*x1 - 8*x2 - 60*x1 - 40*x2;

			if(g1 > 1 || g2 > 1 || g3 > 1 || g4 > 120)
				res = true;

			if(res)
				result *= 0x0;

			return result;
		}
		//------------------------------------------------------------------------------------------------
		double FabricaP1P2(int size, vector<double>& values){
			double result, x1,x2,x3,x4,x5,x6,g1,g2,g3,g4,g5;
			bool res = false;

			if(size < 2)
				return 0.0;

			x1 = values[0];
			x2 = values[1];
				
			g1 = 20*x1 + 40*x2;
	
			result = 1000*x1 + 2000*x2;

			if(g1 > 1200 || x1 > 40 || x2 > 50)
				res = true;

			if(res)
				result *= 0x0;

			return result;
		}
		//------------------------------------------------------------------------------------------------
		double EXTREME_PROBLEM(int size, vector<double>& values){
			return 0.0;
		}
}//ARS_COMMENTS::END NAMESPACE ARS_BENCHMARKFUNCTIONS
