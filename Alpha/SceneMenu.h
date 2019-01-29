#pragma once
#ifndef  SCENEMENU_H
#define SCENEMENU_H

#include <SDL.h>


class SceneMenu
{
	public:
		SceneMenu();
		SceneMenu(std::string titreFenetre, int largeurFenetre, int hauteurFenetre);
		~SceneMenu();
		bool init_window();
		bool main_loop();
		int get_mousex();
		int get_mousey();

	private:
		std::string m_win_title;
		int m_hauteur;
		int m_largeur;
		int m_posx;
		int m_posy;
		SDL_Window *m_fenetre;
		SDL_Renderer *m_renderer;
		SDL_Texture *m_texture;
		//SDL_Texture *m_buttontexture;
		SDL_Surface *m_logogca;
		//SDL_Surface *m_button;
};

#endif //  SCENEMENU_H
