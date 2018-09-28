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

#ifndef ARS_BENCHMARK_H
#define ARS_BENCHMARK_H
//------------------------------------------------------------------------------------------------
//ARS_COMMENTS::SYSTEM INCLUDES
//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
//ARS_COMMENTS::INTERNAL INCLUDE
//------------------------------------------------------------------------------------------------
#include "ARS_Helper.h"

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

namespace ARS_BenchmarkFunctions{
	//ARS_COMMENTS::UTILIZADO NA FUN플O FOXHOLES
	extern const int FoxHolesConstants[2][25];

	extern FitnessFunc GetFitnessFunction(int ID);

#if defined(VARIABLE_LIST)

	//ARS_COMMENTS::Va_lis def
	/*-----------------------------------------------------------------------------------------------*/
	/*  - Sphere Function -																			 */ 
    /*Parameters          - int n (Va_list size), ... (variables)									 */
	/*Recommended         - use this functions with 3 dimensions									 */
	/*Recommended Limits  - use this functions with -100 <= xi <= 100 interval				     	 */
	/*																								 */
	/*  - Optimal value for recommended configurations -											 */
	/*  optimal = 0 for values = { 0, 0, 0 } and limit = -100 <= xi <= 100							 */
	/*-----------------------------------------------------------------------------------------------*/
	extern double Sphere(int n, ...);

	/*-----------------------------------------------------------------------------------------------*/
	/*  - Rosenbrock Function -																		 */ 
	/*Parameters          - int n (Va_list size), ... (variables)									 */
	/*Recommended         - use this functions with 2 dimensions									 */
	/*Recommended Limits  - use this functions with -2.048 <= xi <= 2.048 interval			     	 */
	/*																								 */
	/*  - Optimal value for recommended configurations -											 */
	/*  optimal = 0 for values = { 0, 0 } and limit = -2.048 <= xi <= 2.048							 */
	/*-----------------------------------------------------------------------------------------------*/
	extern double Rosenbrock(int n, ...);

	/*-----------------------------------------------------------------------------------------------*/
	/*  - De Jong step Function -																	 */ 
	/*Parameters          - int n (Va_list size), ... (variables)									 */
	/*Recommended         - use this functions with 5 dimensions									 */
	/*Recommended Limits  - use this functions with -5.12 <= xi <= 5.12 interval				     */
	/*																								 */
	/*  - Optimal values for recommended configurations -											 */
	/*  optimal = 0 for values = { 0, 0, 0, 0, 0 } and limit = -5.12 <= xi <= 5.12					 */
	/*-----------------------------------------------------------------------------------------------*/
	extern double DeJongStep(int n, ...);

	/*-----------------------------------------------------------------------------------------------*/
	/*  - De Jong step.4 Function -																	 */ 
	/*Parameters          - int n (Va_list size), ... (variables)									 */
	/*Recommended         - use this functions with 30 dimensions									 */
	/*Recommended Limits  - use this functions with -1.28 <= xi <= 1.28 interval				     */
	/*																								 */
	/*  - Optimal value for recommended configurations -											 */
	/*  optimal = 0 for values = { 0, ..., 0 } and limit = -1.28 <= xi <= 1.28					     */
	/*-----------------------------------------------------------------------------------------------*/
	extern double DeJonStepB(int n, ...);

	/*-----------------------------------------------------------------------------------------------*/
	/*  - Shekel's Foxholes Function -																 */ 
	/*Parameters          - int n (Va_list size), ... (variables)									 */
	/*Recommended         - use this functions with 2 dimensions									 */
	/*Recommended Limits  - use this functions with -65.536 <= xi <= 65.536 interval				 */
	/*																								 */
	/*  - Optimal value for recommended configurations -											 */
	/*  optimal   = 0.9980038 for values = {-31.9784576, -31.9786271}								 */
	/*	and limit = -65.536 <= xi <= 65.536															 */
	/*-----------------------------------------------------------------------------------------------*/
	extern double ShekelsFoxholes(int n, ...);

	/*-----------------------------------------------------------------------------------------------*/
	/*  - Sphere model Function -																	 */ 
	/*Parameters          - int n (Va_list size), ... (variables)									 */
	/*Recommended         - use this functions with 30 dimensions									 */
	/*Recommended Limits  - use this functions with -30 <= xi <= 30 interval					     */
	/*																								 */
	/*  - Optimal value for recommended configurations -											 */
	/*  optimal = 0 for values = { ... } and limit = -30 <= xi <= 30							     */
	/*-----------------------------------------------------------------------------------------------*/
	extern double SphereModel(int n, ...);

	/*-----------------------------------------------------------------------------------------------*/
	/*  - Schwefel Function -																		 */ 
	/*Parameters          - int n (Va_list size), ... (variables)									 */
	/*Recommended         - use this functions with 30 dimensions									 */
	/*Recommended Limits  - use this functions with -30 <= xi <= 30 interval					     */
	/*																								 */
	/*  - Optimal value for recommended configurations -											 */
	/*  optimal = 0 for values = { ... } and limit = -30 <= xi <= 30							     */
	/*-----------------------------------------------------------------------------------------------*/
	extern double Schwefel(int n, ...);

	/*-----------------------------------------------------------------------------------------------*/
	/*  - SchwefelB Function -																		 */ 
	/*Parameters          - int n (Va_list size), ... (variables)									 */
	/*Recommended         - use this functions with 10 dimensions									 */
	/*Recommended Limits  - use this functions with -500 <= xi <= 500 interval					     */
	/*																								 */
	/*  - Optimal value for recommended configurations -											 */
	/*  optimal   = -418.98288n for values = { 420.9687, ..., 420.9867 }							 */
	/*  and limit = -500 <= xi <= 500																 */
	/*-----------------------------------------------------------------------------------------------*/
	extern double SchwefelB(int n, ...);

	/*-----------------------------------------------------------------------------------------------*/
	/*  - Ackley Function -																			 */ 
	/*Parameters          - int n (Va_list size), ... (variables)									 */
	/*Recommended         - use this functions with 30 dimensions									 */
	/*Recommended Limits  - use this functions with -30 <= xi <= 30 interval					     */
	/*																								 */
	/*  - Optimal value for recommended configurations -											 */
	/*  optimal = 0 for values = { 0, ..., 0 } and limit = -30 <= xi <= 30						     */
	/*-----------------------------------------------------------------------------------------------*/
	extern double Ackley(int n, ...);

	/*-----------------------------------------------------------------------------------------------*/
	/*  - Rastrigin Function -																		 */ 
	/*Parameters          - int n (Va_list size), ... (variables)									 */
	/*Recommended         - use this functions with 20 dimensions									 */
	/*Recommended Limits  - use this functions with -5.12 <= xi <= 5.12 interval				     */
	/*																								 */
	/*  - Optimal value for recommended configurations -											 */
	/*  optimal = 0 for values = { 0, ..., 0 } and limit = -5.12 <= xi <= 5.12					     */
	/*-----------------------------------------------------------------------------------------------*/
	extern double Rastrigin(int n, ...);

	/*-----------------------------------------------------------------------------------------------*/
	/*  - Griewangk Function -																		 */ 
	/*Parameters          - int n (Va_list size), ... (variables)									 */
	/*Recommended         - use this functions with 10 dimensions									 */
	/*Recommended Limits  - use this functions with -600 <= xi <= 600 interval					     */
	/*																								 */
	/*  - Optimal value for recommended configurations -											 */
	/*  optimal = 0 for values = { 0, ..., 0 } and limit = -600 <= xi <= 600						 */
	/*-----------------------------------------------------------------------------------------------*/
	extern double Griewangk(int n, ...);

	/*-----------------------------------------------------------------------------------------------*/
	/*  - Schwefel's pro. 1.2 Function -															 */ 
	/*Parameters          - int n (Va_list size), ... (variables)									 */
	/*Recommended         - use this functions with 20 dimensions									 */
	/*Recommended Limits  - use this functions with -30 <= xi <= 30 interval						 */
	/*																								 */
	/*  - Optimal value for recommended configurations -											 */
	/*  optimal = 0 for values = { 0, ..., 0 } and limit = -30 <= xi <= 30							 */
	/*-----------------------------------------------------------------------------------------------*/
	extern double SchwefelPro(int n, ...);

	/*-----------------------------------------------------------------------------------------------*/
	/*  - Bohachevsky Function -																	 */ 
	/*Parameters          - int n (Va_list size), ... (variables)									 */
	/*Recommended         - use this functions with 10 dimensions									 */
	/*Recommended Limits  - use this functions with -5.12 <= xi <= 5.12 interval				     */
	/*																								 */
	/*  - Optimal value for recommended configurations -											 */
	/*  optimal = 0 for values = { 0, ..., 0 } and limit = -5.12 <= xi <= 5.12					     */
	/*-----------------------------------------------------------------------------------------------*/
	extern double Bohachevsky(int n, ...);
#endif

	/*-----------------------------------------------------------------------------------------------*/
	/*  - Sphere Function -																			 */ 
	/*Parameters          - vector<double>& values													 */
	/*Recommended         - use this functions with 3 dimensions									 */
	/*Recommended Limits  - use this functions with -100 <= xi <= 100 interval				     	 */
	/*																								 */
	/*  - Optimal value for recommended configurations -											 */
	/*  optimal = 0 for values = { 0, 0, 0 } and limit = -100 <= xi <= 100							 */
	/*-----------------------------------------------------------------------------------------------*/
	extern double Sphere(int size, vector<double>& values);

	/*-----------------------------------------------------------------------------------------------*/
	/*  - Rosenbrock Function -																		 */ 
	/*Parameters          - vector<double>& values													 */
	/*Recommended         - use this functions with 2 dimensions									 */
	/*Recommended Limits  - use this functions with -2.048 <= xi <= 2.048 interval			     	 */
	/*																								 */
	/*  - Optimal value for recommended configurations -											 */
	/*  optimal = 0 for values = { 0, 0 } and limit = -2.048 <= xi <= 2.048							 */
	/*-----------------------------------------------------------------------------------------------*/
	extern double Rosenbrock(int size, vector<double>& values);

	/*-----------------------------------------------------------------------------------------------*/
	/*  - De Jong step Function -																	 */ 
	/*Parameters          - vector<double>& values													 */
	/*Recommended         - use this functions with 5 dimensions									 */
	/*Recommended Limits  - use this functions with -5.12 <= xi <= 5.12 interval				     */
	/*																								 */
	/*  - Optimal values for recommended configurations -											 */
	/*  optimal = 0 for values = { 0, 0, 0, 0, 0 } and limit = -5.12 <= xi <= 5.12					 */
	/*-----------------------------------------------------------------------------------------------*/
	extern double DeJongStep(int size, vector<double>& values);

	/*-----------------------------------------------------------------------------------------------*/
	/*  - De Jong step.4 Function -																	 */ 
	/*Parameters          - vector<double>& values													 */
	/*Recommended         - use this functions with 30 dimensions									 */
	/*Recommended Limits  - use this functions with -1.28 <= xi <= 1.28 interval				     */
	/*																								 */
	/*  - Optimal value for recommended configurations -											 */
	/*  optimal = 0 for values = { 0, ..., 0 } and limit = -1.28 <= xi <= 1.28					     */
	/*-----------------------------------------------------------------------------------------------*/
	extern double DeJonStepB(int size, vector<double>& values);

	/*-----------------------------------------------------------------------------------------------*/
	/*  - Shekel's Foxholes Function -																 */ 
	/*Parameters          - vector<double>& values													 */
	/*Recommended         - use this functions with 2 dimensions									 */
	/*Recommended Limits  - use this functions with -65.536 <= xi <= 65.536 interval				 */
	/*																								 */
	/*  - Optimal value for recommended configurations -											 */
	/*  optimal   = 0.9980038 for values = {-31.9784576, -31.9786271}								 */
	/*	and limit = -65.536 <= xi <= 65.536															 */
	/*-----------------------------------------------------------------------------------------------*/
	extern double ShekelsFoxholes(int size, vector<double>& values);

	/*-----------------------------------------------------------------------------------------------*/
	/*  - Schaffer Function -																		 */ 
	/*Parameters          - vector<double>& values													 */
	/*Recommended         - use this functions with 2 dimensions									 */
	/*Recommended Limits  - use this functions with -100 <= xi <= 100 interval					     */
	/*																								 */
	/*  - Optimal value for recommended configurations -											 */
	/*  optimal = 0 for values = { 0, 0 } and limit = -100 <= xi <= 100							     */
	/*-----------------------------------------------------------------------------------------------*/
	extern double Schaffer(int size, vector<double>& values);

	/*-----------------------------------------------------------------------------------------------*/
	/*  - SchafferB Function -																		 */ 
	/*Parameters          - vector<double>& values													 */
	/*Recommended         - use this functions with 2 dimensions									 */
	/*Recommended Limits  - use this functions with -10 <= xi <= 10 interval					     */
	/*																								 */
	/*  - Optimal value for recommended configurations -											 */
	/*  optimal = 1 for values = { 0, 0 } and limit = -10 <= xi <= 10							     */
	/*-----------------------------------------------------------------------------------------------*/
	extern double SchafferB(int size, vector<double>& values);

	/*-----------------------------------------------------------------------------------------------*/
	/*  - Sphere model Function -																	 */ 
	/*Parameters          - vector<double>& values													 */
	/*Recommended         - use this functions with 30 dimensions									 */
	/*Recommended Limits  - use this functions with -30 <= xi <= 30 interval					     */
	/*																								 */
	/*  - Optimal value for recommended configurations -											 */
	/*  optimal = 0 for values = { ... } and limit = -30 <= xi <= 30							     */
	/*-----------------------------------------------------------------------------------------------*/
	extern double SphereModel(int size, vector<double>& values);

	/*-----------------------------------------------------------------------------------------------*/
	/*  - Schwefel Function -																		 */ 
	/*Parameters          - vector<double>& values													 */
	/*Recommended         - use this functions with 30 dimensions									 */
	/*Recommended Limits  - use this functions with -30 <= xi <= 30 interval					     */
	/*																								 */
	/*  - Optimal value for recommended configurations -											 */
	/*  optimal = 0 for values = { ... } and limit = -30 <= xi <= 30							     */
	/*-----------------------------------------------------------------------------------------------*/
	extern double Schwefel(int size, vector<double>& values);

	/*-----------------------------------------------------------------------------------------------*/
	/*  - SchwefelB Function -																		 */ 
	/*Parameters          - vector<double>& values													 */
	/*Recommended         - use this functions with 10 dimensions									 */
	/*Recommended Limits  - use this functions with -500 <= xi <= 500 interval					     */
	/*																								 */
	/*  - Optimal value for recommended configurations -											 */
	/*  optimal   = -418.98288n for values = { 420.9687, ..., 420.9867 }							 */
	/*  and limit = -500 <= xi <= 500																 */
	/*-----------------------------------------------------------------------------------------------*/
	extern double SchwefelB(int size, vector<double>& values);

	/*-----------------------------------------------------------------------------------------------*/
	/*  - Ackley Function -																			 */ 
	/*Parameters          - vector<double>& values													 */
	/*Recommended         - use this functions with 30 dimensions									 */
	/*Recommended Limits  - use this functions with -30 <= xi <= 30 interval					     */
	/*																								 */
	/*  - Optimal value for recommended configurations -											 */
	/*  optimal = 0 for values = { 0, ..., 0 } and limit = -30 <= xi <= 30						     */
	/*-----------------------------------------------------------------------------------------------*/
	extern double Ackley(int size, vector<double>& values);

	/*-----------------------------------------------------------------------------------------------*/
	/*  - Rastrigin Function -																		 */ 
	/*Parameters          - vector<double>& values													 */
	/*Recommended         - use this functions with 20 dimensions									 */
	/*Recommended Limits  - use this functions with -5.12 <= xi <= 5.12 interval				     */
	/*																								 */
	/*  - Optimal value for recommended configurations -											 */
	/*  optimal = 0 for values = { 0, ..., 0 } and limit = -5.12 <= xi <= 5.12					     */
	/*-----------------------------------------------------------------------------------------------*/
	extern double Rastrigin(int size, vector<double>& values);

	/*-----------------------------------------------------------------------------------------------*/
	/*  - Griewangk Function -																		 */ 
	/*Parameters          - vector<double>& values													 */
	/*Recommended         - use this functions with 10 dimensions									 */
	/*Recommended Limits  - use this functions with -600 <= xi <= 600 interval					     */
	/*																								 */
	/*  - Optimal value for recommended configurations -											 */
	/*  optimal = 0 for values = { 0, ..., 0 } and limit = -600 <= xi <= 600						 */
	/*-----------------------------------------------------------------------------------------------*/
	extern double Griewangk(int size, vector<double>& values);

	/*-----------------------------------------------------------------------------------------------*/
	/*  - Schwefel's pro. 1.2 Function -															 */ 
	/*Parameters          - vector<double>& values													 */
	/*Recommended         - use this functions with 20 dimensions									 */
	/*Recommended Limits  - use this functions with -30 <= xi <= 30 interval						 */
	/*																								 */
	/*  - Optimal value for recommended configurations -											 */
	/*  optimal = 0 for values = { 0, ..., 0 } and limit = -30 <= xi <= 30							 */
	/*-----------------------------------------------------------------------------------------------*/
	extern double SchwefelPro(int size, vector<double>& values);

	/*-----------------------------------------------------------------------------------------------*/
	/*  - Bohachevsky Function -																	 */ 
	/*Parameters          - vector<double>& values													 */
	/*Recommended         - use this functions with 10 dimensions									 */
	/*Recommended Limits  - use this functions with -5.12 <= xi <= 5.12 interval				     */
	/*																								 */
	/*  - Optimal value for recommended configurations -											 */
	/*  optimal = 0 for values = { 0, ..., 0 } and limit = -5.12 <= xi <= 5.12					     */
	/*-----------------------------------------------------------------------------------------------*/
	extern double Bohachevsky(int size, vector<double>& values);

	/*-----------------------------------------------------------------------------------------------*/
	/*  - dynamic control Function -																 */ 
	/*Parameters          - vector<double>& values													 */
	/*Recommended         - use this functions with 45 dimensions									 */
	/*Recommended Limits  - use this functions with -200 <= xi <= 200 interval					     */
	/*																								 */
	/*  - Optimal value for recommended configurations -											 */
	/*  optimal = 16180.340452 for values = { ... } and limit = -200 <= xi <= 200				     */
	/*-----------------------------------------------------------------------------------------------*/
	extern double DynamicControl(double* values, double* means);

	//FUN합ES FOLHA 1
	extern double Sapateiro(int size, vector<double>& values);
	extern double Cintaria(int size, vector<double>& values);
	extern double Dieta(int size, vector<double>& values);
	extern double Transporte(int size, vector<double>& values);

	//FUN합ES FOLHA 2
	extern double Refinaria(int size, vector<double>& values);
	extern double FabricaMoveis(int size, vector<double>& values);
	extern double FabricaP1P2(int size, vector<double>& values);

	//FUN합ES FOLHA 3
	extern double EXTREME_PROBLEM(int size, vector<double>& values);
}//ARS_COMMENTS::END NAMESPACE ARS_BENCHMARKFUNCTIONS
#endif

