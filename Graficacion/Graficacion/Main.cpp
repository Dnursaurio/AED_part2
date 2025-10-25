#include <SDL3/SDL.h>

struct Nodo
{
	Nodo(int val)
	{
		//eso aun es en consola
		v = val;
		izq = NULL;
		der = NULL;
	}
	int v;
	Nodo* izq;
	Nodo* der;
};

class arbolBin
{
public:
	arbolBin()
	{
		raiz = nullptr;
	}
	bool Insert(Nodo**& ptr,int valor)
	{
		for (ptr = &raiz; *ptr && (*ptr)->v != valor;);
	}
private:
	Nodo* raiz;
};

int main()
{
	SDL_Window* ventana = SDL_CreateWindow("Graficacion de arbol", 800, 600, 0);
	SDL_Renderer* render = SDL_CreateRenderer(ventana, NULL);
	SDL_Event evento;

	SDL_SetRenderDrawColor(render, 50, 50, 50, 255);
	SDL_RenderClear(render);
	SDL_RenderPresent(render);
	bool ventana_abierta = 1;
	while (ventana_abierta)
	{
		SDL_PollEvent(&evento);
		if (evento.type == SDL_EVENT_QUIT)
		{
			ventana_abierta = 0;
		}
	}
	
	SDL_DestroyRenderer(render);
	SDL_DestroyWindow(ventana);

	return 0;
}