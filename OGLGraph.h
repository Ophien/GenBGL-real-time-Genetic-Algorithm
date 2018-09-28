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
#include <time.h>
#include <List>

//------------------------------------------------------------------------------------------------
//ARS_COMMENTS::INTERNAL INCLUDE
//------------------------------------------------------------------------------------------------
#include "GL\glfw.h"
#include "vec2.h"

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

class OGLGraph
{
public:
	OGLGraph() {}
	~OGLGraph() {}
	void setup( int width, int height, int offsetX, int offsetY, 
				 int scaleX, int scaleY, int channels, int cacheSize, float r, float g, float b );
	
	void update( float );
	void draw();
	int& Width(){return _width;}
	int& Height(){return _height;}

private:
	float R,G,B;

	int _cacheSize;
	int _pWidth, _pHeight;
	int _width, _height;
	int _channels;
	int _scaleX, _scaleY;
	int _offsetX, _offsetY;

	std::list<float> _data;
	std::list<float> _movingAverage;
	std::list<float>::const_iterator _iterData;
	std::list<float>::const_iterator _iterMA;
};
