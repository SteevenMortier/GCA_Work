#pragma once
#ifndef BUTTON_H
#define Button_H

#include <SDL.h>
#include <string>

class Button
{
public:
	Button(SDL_Renderer *renderer, std::string path, int posx, int posy, int hight, int weight);
	~Button();
	bool Button_update(int mousex, int mousey, Uint32 clic);
private:
	std::string m_path;
	int m_x;
	int m_y;
	int m_hight;
	int m_weight;
	SDL_Renderer *m_renderer;
	SDL_Texture *m_buttontexture;
	SDL_Surface *m_buttonimage;
	SDL_Surface *m_buttonTarget;
	SDL_Surface *m_buttonTrigger;
};

#endif