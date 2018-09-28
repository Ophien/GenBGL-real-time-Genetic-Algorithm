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

namespace ARS_Helper{
	//------------------------------------------------------------------------------------------------
	bool isDelim(const char& query, const string& delimList){
		for(unsigned int i = 0; i < delimList.length(); i++)
			if(query == delimList[i])
				return true;
		return false;
	}
	//------------------------------------------------------------------------------------------------
	vector<string> split(const string& line, const string& delimList){
		int len = line.length();
		string temp;
		vector<string> output;
		char _current = 0;
		for(int i = 0; i < len; i++){
			if(isDelim(line[i], delimList)){
				if(temp.length() > 0)
					output.push_back(temp);
				temp.clear();
			}
			else
				if(line[i] != ' ' && 
					(line[i] == '1' || line[i] == '0'))
					temp += line[i];
		}
		if(temp.length() > 0)
			output.push_back(temp);
		return output;
	}
	//------------------------------------------------------------------------------------------------
}//ARS_COOMENTS::END NAMESPACE ARS_HELPER
