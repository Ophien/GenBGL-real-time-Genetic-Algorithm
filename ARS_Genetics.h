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

#ifndef ARS_GENETICS_H
#define ARS_GENETICS_H
//------------------------------------------------------------------------------------------------
//ARS_COMMENTS::SYSTEM INCLUDES
//------------------------------------------------------------------------------------------------
#include <vector>
#include <math.h>
#include <stdio.h>
#include <iostream>

//------------------------------------------------------------------------------------------------
//ARS_COMMENTS::INTERNAL INCLUDE
//------------------------------------------------------------------------------------------------
#include "ARS_MathHelper.h"
#include "ARS_Helper.h"
#include "ARS_Population.h"
#include "ARS_BenchmarkFunctions.h"

//------------------------------------------------------------------------------------------------
//ARS_COMMENTS::USED NAMESPACES
//------------------------------------------------------------------------------------------------
using namespace std;
using namespace ARS_Helper;
using namespace ARS_MathHelper;
using namespace ARS_BenchmarkFunctions;

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

//------------------------------------------------------------------------------------------------
namespace ARS_Genetics{
		/*-----------------------------------------------------------------------------*/
		/* - ARS_GeneticsController class -											   */
		/* Classe responsável por controlar um conjunto de populações.				   */
		/*																			   */
		/*-----------------------------------------------------------------------------*/
		class ARS_GeneticsController{
		public:
			ARS_GeneticsController(void);
			~ARS_GeneticsController(void);

			ARS_Population& GetPopulation(int PopulationIndex){
				return *populations[PopulationIndex];
			}

		private:
			vector<ARS_Population*> populations;
		};

		/*-----------------------------------------------------------------------------*/
		/* - ARS_Configurations class -												   */
		/* Classe responsável por armazenar configurações atuais do espaço.			   */
		/*																			   */
		/*-----------------------------------------------------------------------------*/
		class ARS_Configurations;

}//ARS_COMMENTS::END NAMESPACE ARS_GENETICS
#endif
