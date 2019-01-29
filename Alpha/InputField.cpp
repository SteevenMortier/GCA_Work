#include "Alpha.h"
#include "InputField.h"

InputField::InputField(SDL_Renderer *renderer,  int posx, int posy, std::string message) :  m_renderer(renderer), m_posx(posx), m_posy(posy), m_mousex(0), m_mousey(0),
																							m_clic(0), m_ison(0), m_hauteur(30), m_largeur(170), m_inputmsg(message)
{
	m_text = new Text(m_renderer, m_inputmsg, m_posx, m_posy - m_hauteur / 2 + 3, 20, m_hauteur, m_largeur);
	SDL_Color textcolor = {255, 0, 0};
	m_text->TextChangeColor(textcolor);
	m_fieldsurf = SDL_CreateRGBSurface(0, m_largeur, m_hauteur, 32, 0, 0, 0, 0);
	SDL_FillRect(m_fieldsurf, NULL, SDL_MapRGB(m_fieldsurf->format, 255, 255, 255));
	m_fieldtext = SDL_CreateTextureFromSurface(m_renderer, m_fieldsurf);
	SDL_FreeSurface(m_fieldsurf);
}

InputField::~InputField()
{
	delete m_text;
}

bool InputField::InputFieldUpdate(int mousex, int mousey, int clic)
{
	if ((mousex >= (m_posx - m_largeur / 2) && (mousex <= (m_posx - m_largeur / 2) + m_largeur) && (mousey >= (m_posy - m_hauteur / 2) && mousey <= (m_posy - m_hauteur / 2) + m_hauteur)) || m_ison)
	{
		SDL_Color targettedcolor = { 120, 0, 0 };
		m_text->TextChangeColor(targettedcolor);
	}
	else
	{
		SDL_Color untargettedcolor = { 255, 0, 0 };
		m_text->TextChangeColor(untargettedcolor);
	}

	if (clic && (mousex >= (m_posx - m_largeur / 2) && (mousex <= (m_posx - m_largeur / 2) + m_largeur) && (mousey >= (m_posy - m_hauteur / 2) && mousey <= (m_posy - m_hauteur / 2) + m_hauteur)))
	{
		m_ison = true;
		m_text->TextEdit("");
	}
	else if (clic && !(mousex >= (m_posx - m_largeur / 2) && (mousex <= (m_posx - m_largeur / 2) + m_largeur) && (mousey >= (m_posy - m_hauteur / 2) && mousey <= (m_posy - m_hauteur / 2) + m_hauteur)))
		m_ison = false;
	/*if (m_ison)
		fprintf(stdout, "Input Box is triggered - - -\n");
	else
		fprintf(stdout, "InputBox untriggered\n"); // DEBUG BOX TRIGGER*/
	SDL_Rect rect = {m_posx - m_largeur / 2, m_posy - m_hauteur / 2, m_largeur, m_hauteur};
	SDL_RenderCopy(m_renderer, m_fieldtext, NULL, &rect);
	m_text->TextUpdate();
	return true;
}
