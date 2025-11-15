#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <string>

struct Nodo {
    int v;
    Nodo* izq;
    Nodo* der;
    Nodo(int val) : v(val), izq(NULL), der(NULL) {}
};

// ---- Funciones del árbol ----
void InOrder(Nodo* n) {
    if (!n) return;
    InOrder(n->izq);
    std::cout << n->v << " ";
    InOrder(n->der);
}

Nodo* CrearArbol(int* ini, int* fin) {
    std::vector<Nodo*> v;
    for (; ini < fin; ini++) {
        v.push_back(new Nodo(*ini));
    }

    while (v.size() > 1) {
        int suma = v[0]->v + v[1]->v;
        Nodo* n2 = new Nodo(suma);
        n2->izq = v[0];
        n2->der = v[1];
        v.erase(v.begin());
        v.erase(v.begin());
        v.push_back(n2);
    }

    Nodo* raiz = v.front();
    return raiz;
}

// ---- Funciones de dibujo ----

// Dibuja una línea entre dos puntos
void DrawLine(SDL_Renderer* renderer, int x1, int y1, int x2, int y2) {
    SDL_RenderLine(renderer, x1, y1, x2, y2);
}

// Dibuja un círculo simple
void DrawCircle(SDL_Renderer* renderer, int cx, int cy, int r) {
    for (int w = -r; w < r; w++) {
        for (int h = -r; h < r; h++) {
            if (w * w + h * h <= r * r) {
                SDL_RenderPoint(renderer, cx + w, cy + h);
            }
        }
    }
}

// Dibuja texto centrado
void DrawText(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, int x, int y, SDL_Color color) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), 0,color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FRect dstRect = { (float)(x - surface->w / 2), (float)(y - surface->h / 2), (float)surface->w, (float)surface->h };
    SDL_RenderTexture(renderer, texture, NULL, &dstRect);
    SDL_DestroySurface(surface);
    SDL_DestroyTexture(texture);
}

// Dibuja el árbol recursivamente
void DibujarArbol(SDL_Renderer* renderer, TTF_Font* font, Nodo* n, int x, int y, int offsetX, int nivel) {
    if (!n) return;
    SDL_Color color = { 255, 0, 0, 255 };

    // Conexiones
    if (n->izq) DrawLine(renderer, x, y, x - offsetX, y + 100);
    if (n->der) DrawLine(renderer, x, y, x + offsetX, y + 100);

    // Dibuja hijos
    DibujarArbol(renderer, font, n->izq, x - offsetX, y + 100, offsetX / 2, nivel + 1);
    DibujarArbol(renderer, font, n->der, x + offsetX, y + 100, offsetX / 2, nivel + 1);

    // Nodo
    DrawCircle(renderer, x, y, 20);
    DrawText(renderer, font, std::to_string(n->v), x, y, color);
}

// ---- Programa principal ----
int main(int argc, char* argv[]) {
    int arr[16] = { 2, 4, 7, 9, 10, 15, 3, 25, 38, 74, 1, 5, 10, 13, 11, 35 };
    Nodo* raiz = CrearArbol(arr, arr + 16);

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Error SDL_Init: " << SDL_GetError() << std::endl;
        return 1;
    }

    if (TTF_Init() < 0) {
        std::cerr << "Error TTF_Init: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Árbol Binario", 800, 600, SDL_WINDOW_RESIZABLE);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);

    TTF_Font* font = TTF_OpenFont("C:/Windows/Fonts/arial.ttf", 18);
    if (!font) {
        std::cerr << "Error cargando fuente: " << SDL_GetError() << std::endl;
        return 1;
    }

    bool running = true;
    SDL_Event e;

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) running = false;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        DibujarArbol(renderer, font, raiz, 400, 50, 200, 0);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
