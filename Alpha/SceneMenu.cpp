#include <string>
#include "SceneMenu.h"
#include <SDL.h>
#include <SDL_image.h>
#include "Button.h"
#include "Text.h"
#include <SDL_ttf.h>
#include "Alpha.h"

SceneMenu::SceneMenu(std::string titreFenetre, int largeurFenetre, int hauteurFenetre) : m_win_title(titreFenetre), m_hauteur(hauteurFenetre), m_largeur(largeurFenetre), m_fenetre(0), m_renderer(0),
																						 m_logogca(0), m_texture(0)
{
	m_posx = 0;
	m_posy = 0;
}

SceneMenu::~SceneMenu()
{
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyTexture(m_texture);
	SDL_DestroyWindow(m_fenetre);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

bool SceneMenu::init_window()
{
	/* Initialisation simple */
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) != 0)
	{
		fprintf(stdout, "Échec de l'initialisation de la SDL (%s)\n", SDL_GetError());
		return false;
	}

	if (!(IMG_Init(IMG_INIT_JPG)))
	{
		fprintf(stdout, "Échec de l'initialisation de la SDL_image (%s)\n", SDL_GetError());
		return false;
	}

	if (TTF_Init() < 0)
	{
		fprintf(stdout, "Échec de l'initialisation de la SDL_ttf (%s)\n", SDL_GetError());
		return false;
	}

	/* Création de la fenêtre */
	m_fenetre = SDL_CreateWindow(m_win_title.c_str(), SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		m_largeur,
		m_hauteur,
		SDL_WINDOW_SHOWN);

	SDL_Surface *icon = IMG_Load("P:/smortier/icon.png"); //Icon de l'application
	SDL_SetWindowIcon(m_fenetre, icon);
	SDL_FreeSurface(icon);
	m_renderer = SDL_CreateRenderer(m_fenetre, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE); //Creation de l'unique renderer
	m_logogca = IMG_Load("P:/smortier/Logo.png"); //Logo GCA
	if (!m_logogca)
	{
		fprintf(stdout, "Impossible de charger l'image : (%s)(%s)\n", "P:/smortier/Logo.png", SDL_GetError());
		return false;
	}

	m_texture = SDL_CreateTextureFromSurface(m_renderer, m_logogca);
	SDL_FreeSurface(m_logogca);

	if (!(m_texture))
		return false;
	return true;
}

bool SceneMenu::main_loop()
{
	Button connection_button(m_renderer, "P:/smortier/Button_connection", m_largeur / 2 - 75, m_hauteur - 120 , 150, 70); //Bouton de Connection
	InputField name(m_renderer, m_largeur / 2, m_hauteur - 300, "Nom de Session"); //InputField du nom
	InputField nameecar(m_renderer, m_largeur / 2, m_hauteur - 250, "Login Ecar"); //InputField du nom
	InputField mdpecar(m_renderer, m_largeur / 2, m_hauteur - 200, "Mdp Ecar"); //InputField du nom
	SDL_Surface *backgroundsurface = IMG_Load("P:/smortier/background_menu.jpg"); //Surface de l'image de fond du menu
	SDL_Texture *backgroundtexture = SDL_CreateTextureFromSurface(m_renderer, backgroundsurface); //Texture de l'image de fond
	SDL_FreeSurface(backgroundsurface);
	SDL_Color colortitle = {255, 255, 250}; // Couleur du titre
	Text title(m_renderer, "Bienvenue sur Alpha", m_largeur / 2, 50, 70, 60, 20); //Titre (Bienvenue sur alpha)
	SDL_Rect Logo = { m_largeur / 2 - 100 / 2, m_hauteur / 4, 100, 100 }; //Rect d'affichage du logo GCA
	title.TextChangeColor(colortitle); // CHangement de couleur du titre
	//title.TextEdit("Hello"); // On change le contenu du titre (Bienvenue sur Alpha -> Hello)
	title.TextFontStyle(1, 1, 0); //On passe le titre en gras, italic, pas souligné


	if (m_fenetre)
	{
		char cont = 1; /* Détermine si on continue la boucle principale */

		while (cont != 0)
		{
			SDL_PumpEvents(); // On demande à la SDL de mettre à jour les états sur les périphériques
			SDL_Event event;
			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT)
					return 0;
				if (event.type == SDL_TEXTINPUT)
				{
					if (name.m_ison)
					{
						//std::cout << event.text.text << std::endl;
						name.m_text->TextEdit(name.m_text->TextGetContent() + std::string(event.text.text, 1));
						//std::cout << name.m_text->TextGetContent() << std::endl;
					}
					if (nameecar.m_ison)
						nameecar.m_text->TextEdit(nameecar.m_text->TextGetContent() + std::string(event.text.text, 1));
					if (mdpecar.m_ison)
						mdpecar.m_text->TextEdit(mdpecar.m_text->TextGetContent() + std::string(event.text.text, 1));
				}

				if (event.type == SDL_KEYDOWN)
				{
					if (event.key.keysym.scancode == SDL_SCANCODE_BACKSPACE)
					{
						std::cout << "test" << std::endl;
						if (name.m_ison && name.m_text->TextGetContent().length() > 0)
							name.m_text->TextEdit(name.m_text->TextGetContent().erase(name.m_text->TextGetContent().length() - 1));
						if (nameecar.m_ison && nameecar.m_text->TextGetContent().length() > 0)
							nameecar.m_text->TextEdit(nameecar.m_text->TextGetContent().erase(nameecar.m_text->TextGetContent().length() - 1));
						if (mdpecar.m_ison && mdpecar.m_text->TextGetContent().length() > 0)
							mdpecar.m_text->TextEdit(mdpecar.m_text->TextGetContent().erase(mdpecar.m_text->TextGetContent().length() - 1));
						std::cout << "Delete pressed" << std::endl;
					}
				}
			}
			// Clavier
			{
				const Uint8* pKeyStates = SDL_GetKeyboardState(NULL);
				if (pKeyStates[SDL_SCANCODE_ESCAPE])
					cont = 0;
				// On peut vérifier d'autres touches, si on le souhaite

				SDL_Keymod mod = SDL_GetModState();
				if (mod != KMOD_NONE)
				{
					//fprintf(stdout, "Vous avez appuyé sur une touche spéciale : %d\n", mod);
				}
			}
			// Souris
			
			Uint32 boutons = SDL_GetMouseState(&m_posx, &m_posy);
			//fprintf(stdout, "Position de la souris : %d;%d\n", m_posx, m_posy);
			//fprintf(stdout, "Bouton de la souris : %d\n", boutons);
			
			SDL_SetRenderDrawColor(m_renderer, 150, 150, 145, 100); //Couleur du fond ...
			SDL_RenderClear(m_renderer); //Clear du renderer avec la couleur de fond.
			SDL_RenderCopy(m_renderer, backgroundtexture, NULL, NULL); //On met le background sur le renderer
			SDL_RenderCopy(m_renderer, m_texture, NULL, &Logo); // Puis le logo GCA
			name.InputFieldUpdate(m_posx, m_posy, boutons); //Update du field name
			nameecar.InputFieldUpdate(m_posx, m_posy, boutons); //Update du field name
			mdpecar.InputFieldUpdate(m_posx, m_posy, boutons); //Update du field name
			if (connection_button.Button_update(m_posx, m_posy, boutons) == true) //Si on clic sur le boutton de connection
			{
				// Interaction avec le boutton.
				fprintf(stdout, "Connection....\n");
				SDL_RenderClear(m_renderer);
				if (select_chauffeur(m_fenetre, m_renderer) == 2) //On lance l'affichage de la select_chauffeur
					cont = 0;
				//cont = 0;
				//return true;
			}
			title.TextUpdate(); //update du text titre
			SDL_RenderPresent(m_renderer); //On affiche enfin le renderer qu'on a remplis
			SDL_Delay(20); //Attente qui va soulager un peu la carte graphique -- 20ms
		}
	}
	else
	{
		fprintf(stderr, "Erreur de création de la fenêtre: %s\n", SDL_GetError());
		return false;
	}
	SDL_DestroyTexture(backgroundtexture); //Destuction de la texture de l'image de fond

	return false;
}

int SceneMenu::get_mousex() { return m_posx; }

int SceneMenu::get_mousey() { return m_posy; }