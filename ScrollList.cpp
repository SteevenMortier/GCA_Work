#include "Alpha.h"

ScrollList::ScrollList(SDL_Renderer *renderer, int posx, int posy, std::string init_message) : m_posx(posx), m_posy(posy), m_renderer(renderer), m_show(true), m_weight(600), m_hight(50),
																							   m_scrollstart(0), m_initmsg(init_message)
{
	m_find = new InputField(renderer, m_posx, m_posy, m_initmsg); //Input box qui va servir a faire la recherche
	m_find->InputFieldResize(m_weight, m_hight); // On la resize en plus grand
	m_find->InputFieldFontStyle(1, 0, 0); // Bold
}

ScrollList::~ScrollList()
{
	delete m_find;
}

bool CompareWithCaps(std::string string1, std::string string2, int lenght) // ON return true si les "lenght" premiers char sont egaux sachant que 'a' == 'A'
{
	const char *str1;
	const char *str2;
	int index = 0;
	str1 = string1.c_str();
	str2 = string2.c_str(); 

	while (index < lenght)
	{
		if (str1[index] != str2[index] && str1[index] != str2[index] - 32 && str1[index] - 32 != str2[index])
			return false;
		index++;
	}

	return true;
}

bool ScrollList::ScrollListUpdate(std::vector<SDL_Event> events) // Probleme : quand on fait un recherche qui est hors scroll -> faut scroll pour afficher et c relou
{
	int mousex, mousey; //Position de la souris
	size_t numberprinted = 0;
	size_t decalage;	//Size_t qui set à faire la recherche : on se decale si ca ne correspond pas
	Uint32 boutons = SDL_GetMouseState(&mousex, &mousey); //On inject les positions de la souris dans les int dédiés

	m_find->InputFieldUpdate(mousex, mousey, boutons, events); //Update du inputfield
	for (std::vector<int>::size_type i = 0; i != events.size(); i++) //Pour tous les events
	{
		if (events[i].type == SDL_MOUSEWHEEL) //Gestion de la molette souris pour le scroll
		{
			if (events[i].wheel.y > 0) // scroll up
			{
				//std::cout << "Scroll Up" << std::endl;
				if (m_scrollstart > 0)
					m_scrollstart -= 1;
			}
			if (events[i].wheel.y < 0) //scroll down
			{
				//std::cout << "Scroll Down" << std::endl;
				if (m_contentlist.size() >= 6 && static_cast<std::vector<int>::size_type>(m_scrollstart) < m_contentlist.size() - 6) // 6 étant le max à afficher + Cast pour le Warning (int -> std::vector<int>::size_type)
					m_scrollstart += 1;
			}
		}
	}
	m_show = m_find->m_ison;
	//std::cout << "m_scrollstart = " << m_scrollstart << std::endl;
	if (m_show || mouseinbox(mousex, mousey, m_posx - m_weight / 2, m_posy, m_weight, m_hight + (m_hight * 6 / 2))) // Une case = hight / 2 et on prend (m_posx - m_weight / 2) pour x a cause de la mise au milieu de l'inputbox
	{ //En gros : si on doit show ou que la souris est sur l'inputfield
		decalage = 0; //Lié a la position des elements
		for (std::vector<std::string>::size_type i = 0; i != m_contentlist.size() && m_scrollstart + i < m_contentlist.size() && numberprinted <= (6 - 1); i++) // Pour tous les (contenu de la scrollList)
		{
			if (CompareWithCaps(m_find->InputFieldGetString(), m_contentlist[i + m_scrollstart], m_find->InputFieldGetString().size()) == true) // filtre de recherche
			{
				if (boutons && mouseinbox(mousex, mousey, m_posx - m_weight / 2, m_posy + m_hight / 2 + (i - decalage) * m_hight / 2, m_weight, m_hight / 2)) // Si on clique sur un choix ca le prend
				{
					m_find->InputFieldSetString(m_contentlist[i + m_scrollstart]);
					std::cout << "Clicked : " << m_contentlist[i + m_scrollstart] << std::endl;
				}
				if (m_show) //Si on dois montrer la liste
				{
					if (mouseinbox(mousex, mousey, m_posx - m_weight / 2, m_posy + m_hight / 2 + (i - decalage) * m_hight / 2, m_weight, m_hight / 2)) //Couleurs des choix
						SDL_SetRenderDrawColor(m_renderer, 120, 120, 115, 50); //couleur targetted
					else
						SDL_SetRenderDrawColor(m_renderer, 162, 40, 40, 50); //couleur de base
					SDL_Rect rect = { m_posx - m_weight / 2, m_posy + m_hight / 2 + static_cast<int>(i - decalage) * m_hight / 2 , m_weight, m_hight / 2 }; //On cast pour le Warning du compilo + flemme de changer les variables en size_t
					SDL_RenderFillRect(m_renderer, &rect); //On render le rectangle de choix
					Text tmp(m_renderer, m_contentlist[i + m_scrollstart], m_posx, m_posy + m_hight / 2 + (i - decalage) * m_hight / 2, 20, 10, 25); // on affiche le text from liste
					tmp.TextUpdate(); //Et on l'affiche
					numberprinted++;
				}
			}
			else
				decalage += 1;
			//std::cout << "numberprinted : " << numberprinted << ", i : " << i << ", scrollstart : " << m_scrollstart << ", sizemax : " << m_contentlist.size() << std::endl;
		}
	}
	if (m_find->InputFieldGetString().size() == 0 && !m_find->m_ison) // si on a rien choisi et qu'on est out of the box
	{
		m_find->InputFieldSetString(m_initmsg); //Remettre le init message dans la box
		m_scrollstart = 0;
	}
	//std::cout << "InputField Content : [" << m_find->InputFieldGetString() << "]" << std::endl;
	return true;
}