#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include "Text.h"

using namespace std;

Text::Text() {}

Text::Text(SDL_Renderer *renderer, std::string content, int posx, int posy, int size, int hauteur, int largeur) : m_renderer(renderer), m_content(content), m_posx(posx), m_posy(posy), 
																								m_size(size), m_font(0), m_texttexture(0), m_textsurf(0), m_hauteur(hauteur), m_largeur(largeur)
{
	m_color = { 255, 255, 255 };
	m_font = TTF_OpenFont("P:/smortier/arial.ttf", m_size);
	if (m_font <= 0)
	{
		fprintf(stdout, "Impossible de charger le font! (%s)\n", SDL_GetError());
	}
	SDL_Color color = { 255, 255, 255 };
	m_textsurf = TTF_RenderText_Solid(m_font, m_content.c_str(), m_color);
	m_texttexture = SDL_CreateTextureFromSurface(m_renderer, m_textsurf);
	SDL_QueryTexture(m_texttexture, 0, 0, &m_largeur, &m_hauteur);
	SDL_FreeSurface(m_textsurf);
}

Text::~Text()
{
	fprintf(stdout, "Destruction Text \n");
	TTF_CloseFont(m_font);
	SDL_DestroyTexture(m_texttexture);
}

bool Text::TextEdit(string content) //Erreur qui cause une exeption
{
	m_content = content;
	SDL_DestroyTexture(m_texttexture);
	m_textsurf = TTF_RenderText_Solid(m_font, m_content.c_str(), m_color);
	m_texttexture = SDL_CreateTextureFromSurface(m_renderer, m_textsurf);
	SDL_QueryTexture(m_texttexture, 0, 0, &m_largeur, &m_hauteur);
	SDL_FreeSurface(m_textsurf);
	return true;
}

bool Text::TextUpdate()
{
	SDL_Rect rect = {m_posx - (m_largeur / 2), m_posy, m_largeur, m_hauteur};
	SDL_RenderCopy(m_renderer, m_texttexture, NULL, &rect);
	return true;
}

bool Text::TextChangeColor(SDL_Color color)
{
	SDL_DestroyTexture(m_texttexture);
	m_color = color;
	m_textsurf = TTF_RenderText_Solid(m_font, m_content.c_str(), m_color);
	m_texttexture = SDL_CreateTextureFromSurface(m_renderer, m_textsurf);
	SDL_QueryTexture(m_texttexture, 0, 0, &m_largeur, &m_hauteur);
	SDL_FreeSurface(m_textsurf);
	return true;
}

bool Text::TextFontStyle(int bold, int italics, int underline)
{
	SDL_DestroyTexture(m_texttexture);
	if (bold && italics && underline)
		TTF_SetFontStyle(m_font, TTF_STYLE_BOLD | TTF_STYLE_ITALIC | TTF_STYLE_UNDERLINE);
	else if (bold && italics)
		TTF_SetFontStyle(m_font, TTF_STYLE_BOLD | TTF_STYLE_ITALIC);
	else if (bold && underline)
		TTF_SetFontStyle(m_font, TTF_STYLE_BOLD | TTF_STYLE_UNDERLINE);
	else if (italics && underline)
		TTF_SetFontStyle(m_font, TTF_STYLE_UNDERLINE | TTF_STYLE_ITALIC);
	else if (italics)
		TTF_SetFontStyle(m_font, TTF_STYLE_ITALIC);
	else if (bold)
		TTF_SetFontStyle(m_font, TTF_STYLE_BOLD);
	else if (underline)
		TTF_SetFontStyle(m_font, TTF_STYLE_UNDERLINE);
	else
		TTF_SetFontStyle(m_font, TTF_STYLE_NORMAL);
	m_textsurf = TTF_RenderText_Solid(m_font, m_content.c_str(), m_color);
	m_texttexture = SDL_CreateTextureFromSurface(m_renderer, m_textsurf);
	SDL_QueryTexture(m_texttexture, 0, 0, &m_largeur, &m_hauteur);
	SDL_FreeSurface(m_textsurf);
	return true;
}

std::string Text::TextGetContent() { return m_content; }