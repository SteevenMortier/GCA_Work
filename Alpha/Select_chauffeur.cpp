#include "Alpha.h"

int select_chauffeur(SDL_Window *fenetre, SDL_Renderer *renderer)
{
	int finish = 0;
	int mouse_x;
	int mouse_y;
	Button setting_button(renderer, "P:/smortier/setting", 0, 0, 50, 50);
	Text title(renderer, "Fenetre chauffeur", 300, 50, 70, 60, 20); //Titre (Bienvenue sur alpha)
	std::string test = "";

	while (!(finish))
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				finish = 2;
			if (event.type == SDL_TEXTINPUT)
			{
				std::cout << event.text.text << std::endl;
				test = test + std::string(event.text.text, 1);
				std::cout << test << std::endl;
			}
		}
		SDL_PumpEvents(); // On demande à la SDL de mettre à jour les états sur les périphériques
		// Clavier
		{
			const Uint8* pKeyStates = SDL_GetKeyboardState(NULL);
			if (pKeyStates[SDL_SCANCODE_ESCAPE])
				finish = 1;
			// On peut vérifier d'autres touches, si on le souhaite

			SDL_Keymod mod = SDL_GetModState();
			if (mod != KMOD_NONE)
			{
				//fprintf(stdout, "Vous avez appuyé sur une touche spéciale : %d\n", mod);
			}
			Uint32 boutons = SDL_GetMouseState(&mouse_x, &mouse_y);

		}
		// Souris

		Uint32 boutons = SDL_GetMouseState(&mouse_x, &mouse_y);
		SDL_SetRenderDrawColor(renderer, 150, 150, 145, 100);
		SDL_RenderClear(renderer);
		title.TextUpdate();
		if (setting_button.Button_update(mouse_x, mouse_y, boutons))
			finish = true;
		SDL_RenderPresent(renderer);
		SDL_Delay(20); //Attente qui va soulager un peu la carte graphique -- 20ms
	}
	SDL_Delay(500);

	return (finish);
}