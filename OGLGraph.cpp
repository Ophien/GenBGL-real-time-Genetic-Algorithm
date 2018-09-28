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
#include "OGLGraph.h"

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
void OGLGraph::setup( int width, int height, int offsetX, int offsetY, 
				 int scaleX, int scaleY, int channels, int cacheSize, float r, float g, float b )
{
	R= r;
	G = g;
	B = b;
	_offsetX = offsetX;
	_offsetY = offsetY;
	_width = width;
	_height = height;
	_scaleX = scaleX;
	_scaleY = scaleY;
	_channels = channels;
	_cacheSize = cacheSize;
}
//------------------------------------------------------------------------------------------------
void OGLGraph::update( float data )
{
	if ( _data.size() > (unsigned int)(_cacheSize) )
	{ 
		_data.pop_front();
		_movingAverage.pop_front();
		
		std::list<float>::const_iterator it;

		// Computes moving average
		float subTotal = 0.f;
		_data.push_back( data );
		for ( it=_data.begin(); it != _data.end(); it++ )
		{
			subTotal += *it;
		}
		float maTemp = (float) (subTotal/(_data.size()));
		_movingAverage.push_back( maTemp );

	}
	else
	{
        _data.push_back( data );

		// Computes moving average
		std::list<float>::const_iterator it;
		float subTotal = 0.f;
		for ( it=_data.begin(); it != _data.end(); it++ )
		{
			subTotal += *it;
		}
		float maTemp = (float) (subTotal/(_data.size()));
		_movingAverage.push_back( maTemp );
	}
}
//------------------------------------------------------------------------------------------------
void OGLGraph::draw()
{
	int cntX = 0;
	int cntY = 0;

	//CONFIG DA TRASNFORMAÇÃO PADRÃO DO GRÁFICO
	/*glMatrixMode(GL_PROJECTION); 
	glLoadIdentity(); 
	glOrtho(0, _width, 0, _height, 0, 1.0); 
	glMatrixMode(GL_MODELVIEW); 
	glLoadIdentity();*/

	//Deve desligar para não dar pau no plot
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glDisable (GL_LINE_STIPPLE);

	glBegin( GL_LINE_STRIP );
	glColor3ub ( (GLubyte)R, (GLubyte)G, (GLubyte)B );
	for ( _iterData=_data.begin(); _iterData != _data.end(); _iterData++ ){
        glVertex3f( (GLfloat)10.0+(cntX*_scaleX), ((GLfloat)10.0+(*_iterData))*_scaleY, (GLfloat)0.0 );
		cntX++;
	}
	glEnd();

	//Draw the moving average values
	glEnable (GL_LINE_STIPPLE);
	glLineStipple (3, 0xAAAA);
	glBegin( GL_LINE_STRIP );
	glColor3ub( (GLubyte)(R*0.5), (GLubyte)(G*0.5), (GLubyte)(B*0.5));

	//Desenha o gráfico se movendo com a line stipple
	for (_iterMA=_movingAverage.begin(); _iterMA != _movingAverage.end(); _iterMA++){
        glVertex3f( (GLfloat)10.0+(cntY*_scaleX), ((GLfloat)10.0+(*_iterMA))*_scaleY, (GLfloat)0.0);
		cntY++;
	}
	glEnd();

	//Deve desligar para não dar pau no resto da engine
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
}
