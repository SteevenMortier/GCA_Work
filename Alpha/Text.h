#pragma once
#ifndef TEXT_H
#define TEXT_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class Text
{
public:
	Text(SDL_Renderer *renderer, std::string content, int posx, int posy, int size, int hauteur, int largeur);
	Text();
	bool TextUpdate();
	bool TextChangeColor(SDL_Color color);
	bool TextFontStyle(int bold, int italics, int underline);
	bool TextEdit(std::string content);
	std::string TextGetContent();
	~Text();
private:
	std::string m_content;
	int m_posx;
	int m_posy;
	int m_size;
	int m_hauteur;
	int m_largeur;
	SDL_Color m_color;
	TTF_Font *m_font;
	SDL_Renderer *m_renderer;
	SDL_Texture *m_texttexture;
	SDL_Surface *m_textsurf;
};

#endif