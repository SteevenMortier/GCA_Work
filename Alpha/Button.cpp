#include <SDL.h>
#include <SDL_image.h>
#include "Button.h"

using namespace std;

Button::Button(SDL_Renderer *renderer, std::string path, int x, int y, int hight, int weight) : m_renderer(renderer), m_path(path), m_x(x), m_y(y), m_hight(hight), m_weight(weight)
{
	string tmp = m_path + ".png";
	m_buttonimage = IMG_Load(tmp.c_str());
	tmp = m_path + "_target.png";
	m_buttonTarget = IMG_Load(tmp.c_str());
	tmp = m_path + "_triggered.png";
	m_buttonTrigger = IMG_Load(tmp.c_str());

	if (!(m_buttonimage) || !(m_buttonTarget) || !(m_buttonTrigger))
	{
		fprintf(stdout, "Impossible de charger l'image Bouton  -> (%s)\n", SDL_GetError());
	}
	m_buttontexture = SDL_CreateTextureFromSurface(m_renderer, m_buttonimage);
	/*SDL_Rect options = {m_x, m_y, 130, 50}; // Taille et position du bouton
	SDL_RenderCopy(m_renderer, m_buttontexture, NULL, &options);
	SDL_RenderPresent(m_renderer);*/
}

Button::~Button()
{
	SDL_FreeSurface(m_buttonimage);
	SDL_FreeSurface(m_buttonTarget);
	SDL_FreeSurface(m_buttonTrigger);
	SDL_DestroyTexture(m_buttontexture);
}

bool Button::Button_update(int mousex, int mousey, Uint32 clic)
{
	if ((mousex >= m_x && mousex <= m_hight + m_x) && (mousey >= m_y && mousey <= m_weight + m_y))
	{
		if (clic > 0)
		{
			SDL_DestroyTexture(m_buttontexture);
			m_buttontexture = SDL_CreateTextureFromSurface(m_renderer, m_buttonTrigger);
			SDL_Rect options = { m_x, m_y, m_hight, m_weight }; // Taille et position du bouton
			SDL_RenderCopy(m_renderer, m_buttontexture, NULL, &options);
			return true;
		}
		else
		{
			SDL_DestroyTexture(m_buttontexture);
			m_buttontexture = SDL_CreateTextureFromSurface(m_renderer, m_buttonTarget);
			SDL_Rect options = { m_x, m_y, m_hight, m_weight }; // Taille et position du bouton
			SDL_RenderCopy(m_renderer, m_buttontexture, NULL, &options);
		}
	}
	else
	{
		SDL_DestroyTexture(m_buttontexture);
		m_buttontexture = SDL_CreateTextureFromSurface(m_renderer, m_buttonimage);
		SDL_Rect options = { m_x, m_y, m_hight, m_weight }; // Taille et position du bouton
		SDL_RenderCopy(m_renderer, m_buttontexture, NULL, &options);
	}
	return false;
}