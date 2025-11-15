// rbt_with_graphics.cpp
// <-- Este archivo contiene TU RBT tal cual y añade las funciones gráficas adaptadas.
// Cambios mínimos: UNA LÍNEA pública getRoot() para permitir graficar sin tocar lógica.

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>
#include <stack>
#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Nodo
{
    Nodo(int v)
    {
        valor = v;
        color = true;      // rojo
        padre = nullptr;
        abuelo = nullptr;
        izq = nullptr;
        der = nullptr;
    }

    int valor;
    bool color;       // true = rojo, false = negro
    Nodo* padre;
    Nodo* abuelo;
    Nodo* izq;
    Nodo* der;
};

class RBtree
{
public:
    RBtree()
    {
        root = nullptr;
    }

    // -------------------------------------------------------
    // ADICIÓN MÍNIMA NECESARIA (UNA LÍNEA)
    // Permite a las funciones gráficas leer la raíz sin tocar la lógica.
    Nodo* getRoot() { return root; }
    // -------------------------------------------------------

    // ------------------------------------------
    // ROTACIÓN IZQUIERDA
    // ------------------------------------------
    void rotIzq(Nodo*& x)
    {
        Nodo* y = x->der;
        if (!y) return;

        x->der = y->izq;
        if (y->izq) y->izq->padre = x;

        y->padre = x->padre;

        if (!x->padre)
            root = y;
        else if (x->padre->izq == x)
            x->padre->izq = y;
        else
            x->padre->der = y;

        y->izq = x;
        x->padre = y;
    }

    // ------------------------------------------
    // ROTACIÓN DERECHA
    // ------------------------------------------
    void rotDer(Nodo*& x)
    {
        Nodo* y = x->izq;
        if (!y) return;

        x->izq = y->der;
        if (y->der) y->der->padre = x;

        y->padre = x->padre;

        if (!x->padre)
            root = y;
        else if (x->padre->izq == x)
            x->padre->izq = y;
        else
            x->padre->der = y;

        y->der = x;
        x->padre = y;
    }

    // ------------------------------------------
    // BÚSQUEDA
    // ------------------------------------------
    bool Find(Nodo**& ptr, int v)
    {
        while (!s.empty()) s.pop();

        ptr = &root;
        while (*ptr && (*ptr)->valor != v)
        {
            s.push(*ptr);
            if ((*ptr)->valor > v)
                ptr = &((*ptr)->izq);
            else
                ptr = &((*ptr)->der);
        }
        return *ptr != nullptr;
    }

    // ------------------------------------------
    // INSERT REAL DE ÁRBOL ROJO-NEGRO
    // ------------------------------------------
    bool Insert(int val)
    {
        Nodo** ptr;
        if (Find(ptr, val))
            return 0;

        // Crear nodo rojo
        *ptr = new Nodo(val);

        // padre y abuelo
        if (!s.empty()) {
            (*ptr)->padre = s.top();
            s.pop();
        }
        if (!s.empty()) {
            (*ptr)->abuelo = s.top();
        }

        Nodo* nodo = *ptr;

        // Caso 1: si es raíz → se vuelve negro
        if (!nodo->padre)
        {
            nodo->color = false;
            return 1;
        }

        // Mientras padre sea rojo → violación
        while (nodo->padre && nodo->padre->color == true)
        {
            Nodo* padre = nodo->padre;
            Nodo* abuelo = padre->padre;

            if (!abuelo) break;

            // TÍO
            Nodo* tio = (abuelo->izq == padre ? abuelo->der : abuelo->izq);

            // Caso 2: Tío rojo → recoloreo
            if (tio && tio->color == true)
            {
                padre->color = false;
                tio->color = false;
                abuelo->color = true;
                nodo = abuelo;
                continue;
            }

            // Caso 3: Rotaciones
            if (abuelo->izq == padre)
            {
                // LR
                if (padre->der == nodo)
                {
                    rotIzq(padre);
                    nodo = padre;
                    padre = nodo->padre;
                }
                // LL
                rotDer(abuelo);
            }
            else
            {
                // RL
                if (padre->izq == nodo)
                {
                    rotDer(padre);
                    nodo = padre;
                    padre = nodo->padre;
                }
                // RR
                rotIzq(abuelo);
            }

            padre->color = false;
            abuelo->color = true;
            break;
        }

        root->color = false; // raíz negra
        return 1;
    }

    // ------------------------------------------
    // ENCONTRAR REEMPLAZO
    // ------------------------------------------
    Nodo** Reemplazo(Nodo** q)
    {
        if (rand() % 2 == 0)
        {
            q = &(*q)->izq;
            while ((*q)->der)
                q = &((*q)->der);
        }
        else
        {
            q = &(*q)->der;
            while ((*q)->izq)
                q = &((*q)->izq);
        }
        return q;
    }

    // ------------------------------------------
    // DELETE REAL RB (con recoloreo + rotaciones)
    // ------------------------------------------
    bool Remove(int val)
    {
        Nodo** ptr;

        if (!Find(ptr, val))
            return 0;

        Nodo* z = *ptr;

        // Si tiene dos hijos → usar reemplazo
        if (z->izq && z->der)
        {
            Nodo** q = Reemplazo(ptr);
            z->valor = (*q)->valor;
            ptr = q;
            z = *ptr;
        }

        Nodo* hijo = (z->izq ? z->izq : z->der);

        // Caso: nodo rojo con hijo negro → simple
        if (z->color == true)
        {
            *ptr = hijo;
            if (hijo) hijo->padre = z->padre;
            delete z;
            return 1;
        }

        // Caso: nodo negro con hijo rojo → recolorear hijo
        if (hijo && hijo->color == true)
        {
            hijo->color = false;
            hijo->padre = z->padre;
            *ptr = hijo;
            delete z;
            return 1;
        }

        // Caso: nodo NEGRO sin hijos → doble negro
        fixDelete(ptr, z);

        delete z;
        return 1;
    }

    void InOrder(Nodo* n)
    {
        if (!n)
        {
            return;
        }
        else
        {
            InOrder(n->izq);
            cout << n->valor << " ";
            InOrder(n->der);
        }
    }

    void PrintInOrder()
    {
        InOrder(root);
        cout << endl;
    }

private:

    // --------------------------------------------------------
    // FIX DELETE (sin mover nada fuera, solo lo necesario)
    // --------------------------------------------------------
    void fixDelete(Nodo** ptr, Nodo* x)
    {
        Nodo* padre = x->padre;
        Nodo* hermano;

        while (ptr && *ptr != root && (!*ptr || (*ptr)->color == false))
        {
            if (padre->izq == *ptr)
            {
                hermano = padre->der;

                // Hermano rojo
                if (hermano->color == true)
                {
                    hermano->color = false;
                    padre->color = true;
                    rotIzq(padre);
                    hermano = padre->der;
                }

                // ambos hijos negros
                if ((!hermano->izq || hermano->izq->color == false) &&
                    (!hermano->der || hermano->der->color == false))
                {
                    hermano->color = true;
                    *ptr = padre;
                    padre = padre->padre;
                }
                else
                {
                    if (!hermano->der || hermano->der->color == false)
                    {
                        if (hermano->izq) hermano->izq->color = false;
                        hermano->color = true;
                        rotDer(hermano);
                        hermano = padre->der;
                    }
                    hermano->color = padre->color;
                    padre->color = false;
                    if (hermano->der) hermano->der->color = false;
                    rotIzq(padre);
                    *ptr = root;
                }
            }
            else
            {
                hermano = padre->izq;

                if (hermano->color == true)
                {
                    hermano->color = false;
                    padre->color = true;
                    rotDer(padre);
                    hermano = padre->izq;
                }

                if ((!hermano->izq || hermano->izq->color == false) &&
                    (!hermano->der || hermano->der->color == false))
                {
                    hermano->color = true;
                    *ptr = padre;
                    padre = padre->padre;
                }
                else
                {
                    if (!hermano->izq || hermano->izq->color == false)
                    {
                        if (hermano->der) hermano->der->color = false;
                        hermano->color = true;
                        rotIzq(hermano);
                        hermano = padre->izq;
                    }
                    hermano->color = padre->color;
                    padre->color = false;
                    if (hermano->izq) hermano->izq->color = false;
                    rotDer(padre);
                    *ptr = root;
                }
            }
        }

        if (*ptr) (*ptr)->color = false;
    }

    Nodo* root;
    stack<Nodo*> s;
};

// ------------------------
// FUNCIONES GRAFICAS ADAPTADAS (tomadas del AVL que pegaste)
// ------------------------

// Filled circle via scan — same approach que en tu AVL (función copiada/adaptada)
static void DrawCircle(SDL_Renderer* renderer, int x, int y, int r) {
    for (int w = 0; w < r * 2; w++)
        for (int h = 0; h < r * 2; h++) {
            int dx = r - w;
            int dy = r - h;
            if ((dx * dx + dy * dy) <= (r * r))
                SDL_RenderPoint(renderer, x + dx, y + dy);
        }
}

// Text rendering adapted a SDL3_ttf correctamente (wrap = 0)
static void DrawTextSDL(SDL_Renderer* renderer, TTF_Font* font, const string& text, int x, int y, SDL_Color color = { 0,0,0,255 }) {
    if (!font || !renderer) return;
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), 0, color);
    if (!surface) return;
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FRect dst = { (float)x - surface->w / 2.0f, (float)y - surface->h / 2.0f, (float)surface->w, (float)surface->h };
    SDL_RenderTexture(renderer, texture, nullptr, &dst);
    SDL_DestroyTexture(texture);
}

// Nodo recursivo — adaptado de tu DrawNode del AVL, añade color según nodo->color (rojo/negro)
static void DrawNodeRecursive(SDL_Renderer* renderer, TTF_Font* font, Nodo* node, int x, int y, int offsetX) {
    if (!node) return;
    int childY = y + 80;

    if (node->izq) {
        SDL_SetRenderDrawColor(renderer, 180, 180, 180, 255);
        SDL_RenderLine(renderer, x, y, x - offsetX, childY);
    }
    if (node->der) {
        SDL_SetRenderDrawColor(renderer, 180, 180, 180, 255);
        SDL_RenderLine(renderer, x, y, x + offsetX, childY);
    }

    // Relleno según color del nodo del RBT
    if (node->color) {
        // rojo
        SDL_SetRenderDrawColor(renderer, 220, 60, 60, 255);
        DrawCircle(renderer, x, y, 25);
        // texto en blanco para contraste
        DrawTextSDL(renderer, font, to_string(node->valor), x, y, { 255,255,255,255 });
    }
    else {
        // negro
        SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
        DrawCircle(renderer, x, y, 25);
        // texto en blanco para contraste
        DrawTextSDL(renderer, font, to_string(node->valor), x, y, { 255,255,255,255 });
    }

    // borde
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    for (int a = 0; a < 360; a += 8) {
        double rad = a * 3.14159265358979323846 / 180.0;
        int sx = (int)(x + cos(rad) * 26.5);
        int sy = (int)(y + sin(rad) * 26.5);
        SDL_RenderPoint(renderer, sx, sy);
    }

    // Recursión
    if (node->izq) DrawNodeRecursive(renderer, font, node->izq, x - offsetX, childY, offsetX / 2);
    if (node->der) DrawNodeRecursive(renderer, font, node->der, x + offsetX, childY, offsetX / 2);
}

// Dibuja todo el árbol (interfaz simple). No modifica el tree.
static void DrawTreeSDL(SDL_Renderer* renderer, TTF_Font* font, RBtree& tree, int winW, int winH) {
    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
    SDL_RenderClear(renderer);

    Nodo* root = tree.getRoot(); // uso del getter mínimo que añadí
    if (root) {
        int startX = winW / 2;
        int startY = 70;
        int offsetX = winW / 4;
        DrawNodeRecursive(renderer, font, root, startX, startY, offsetX);
    }

    // HUD simple
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    DrawTextSDL(renderer, font, "I = insert random | D = delete random | Esc = exit", 400, winH - 30);
    SDL_RenderPresent(renderer);
}

// ----------------------
// MAIN: mantuve tus inserciones y print exactamente como estaban.
// He añadido una ventana SDL/loop para mostrar el árbol.
// Si NO quieres que la ventana se abra automáticamente, comenta el bloque SDL/TTF y el loop.
// ----------------------

int main()
{
    RBtree arbol;
    arbol.Insert(1);
    arbol.Insert(8);
    arbol.Insert(3);
    arbol.Insert(7);
    arbol.Insert(2);
    arbol.Insert(9);
    arbol.Insert(4);
    arbol.Insert(5);
    arbol.Insert(6);
    arbol.Insert(21);
    arbol.Insert(25);
    arbol.Insert(36);

    arbol.PrintInOrder();


    // ---------- Inicialización SDL3 + TTF ----------
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cerr << "SDL_Init error: " << SDL_GetError() << endl;
        return 1;
    }
    if (TTF_Init() < 0) {
        cerr << "TTF_Init error: " << SDL_GetError() << endl;
        SDL_Quit();
        return 1;
    }

    const int WINW = 1280;
    const int WINH = 720;
    SDL_Window* window = SDL_CreateWindow("Red-Black Tree - SDL3", WINW, WINH, 0);
    if (!window) {
        cerr << "CreateWindow error: " << SDL_GetError() << endl;
        TTF_Quit();
        SDL_Quit();
        return 1;
    }
    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);
    if (!renderer) {
        cerr << "CreateRenderer error: " << SDL_GetError() << endl;
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    const char* fontPath = "C:/Windows/Fonts/arial.ttf";
    TTF_Font* font = TTF_OpenFont(fontPath, 18);
    if (!font) {
        fontPath = "arial.ttf";
        font = TTF_OpenFont(fontPath, 18);
        if (!font) {
            cerr << "No se pudo abrir la fuente. Ajusta fontPath. Error: " << SDL_GetError() << endl;
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            TTF_Quit();
            SDL_Quit();
            return 1;
        }
    }

    // dibujado inicial
    DrawTreeSDL(renderer, font, arbol, WINW, WINH);

    // loop de eventos simple (teclas para insertar/eliminar y actualizar dibujo)
    bool running = true;
    SDL_Event e;
    srand((unsigned)time(nullptr));

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) running = false;
            else if (e.type == SDL_EVENT_KEY_DOWN) {
                switch (e.key.key) {
                case SDL_SCANCODE_ESCAPE:
                    running = false;
                    break;
                case SDL_SCANCODE_I: {
                    int val = rand() % 100;
                    arbol.Insert(val);
                    DrawTreeSDL(renderer, font, arbol, WINW, WINH);
                    break;
                }
                case SDL_SCANCODE_D: {
                    // intentar eliminar un valor aleatorio
                    int tries = 0;
                    bool removed = false;
                    while (tries++ < 200 && !removed) {
                        int v = rand() % 100;
                        removed = arbol.Remove(v);
                    }
                    DrawTreeSDL(renderer, font, arbol, WINW, WINH);
                    break;
                }
                default:
                    break;
                }
            }
        }
        SDL_Delay(16);
    }

    // cleanup
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
