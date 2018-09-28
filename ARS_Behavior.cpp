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
#include "ARS_Behavior.h"

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

//------------------------------------------------------------------------------------------------
ARS_Behavior::ARS_Behavior()
{
}
//------------------------------------------------------------------------------------------------
ARS_Behavior::~ARS_Behavior(void)
{
}
//------------------------------------------------------------------------------------------------
void ARS_Behavior::Execute(ARS_BeingStatus& beingStatus, const double& time){
	//CHAMA TODOS OS COMPORTAMENTOS DO INDIV�DUO
	PreBehavior(beingStatus, time);
	Behavior(beingStatus, time);
	PosBehavior(beingStatus, time);
}
//------------------------------------------------------------------------------------------------
void ARS_Behavior::PreBehavior(ARS_BeingStatus& beingStatus, const double& time){
}
//------------------------------------------------------------------------------------------------
void ARS_Behavior::PosBehavior(ARS_BeingStatus& beingStatus, const double& time){
}
//------------------------------------------------------------------------------------------------
void ARS_Behavior::Behavior(ARS_BeingStatus& beingStatus, const double& time){
}
//------------------------------------------------------------------------------------------------
