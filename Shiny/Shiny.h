///////////////////////////////////////////////////////////////////////////////
//	File:    Shiny.h
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////


#ifndef __SHINY__
#define __SHINY__


class ViewPane;
class World;

class Shiny
{
private:
	ViewPane *viewPane;
	World	 *world;
	double	 renderTime;

public:
	Shiny(int width,int height);
	Shiny::~Shiny();
	void* getFrameBuffer();
	double getRenderTime();
	
public:
	void render();
	
};

#endif