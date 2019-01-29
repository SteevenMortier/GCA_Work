#pragma once
#ifndef INPUTFIELD_H
#define INPUTFIELD_H

#include "Alpha.h"

class InputField
{
public:
	InputField(SDL_Renderer *renderer, int posx, int posy, std::string message);
	bool InputFieldUpdate(int mousex, int mousey, int clic);
	~InputField();
	bool m_ison;
	Text *m_text;

private:
	int m_posx, m_posy, m_mousex, m_mousey, m_clic, m_hauteur, m_largeur;
	SDL_Renderer *m_renderer;
	SDL_Surface *m_fieldsurf;
	SDL_Texture *m_fieldtext;
	std::string m_inputmsg;
};

#endif