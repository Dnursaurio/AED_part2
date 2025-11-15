#include <iostream>
#include <stack>
#include <stdlib.h>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include <cmath>

using namespace std;

struct Nodo {
    Nodo(int v) {
        valor = v;
        izq = nullptr;
        der = nullptr;
    }
    int valor;
    Nodo* izq;
    Nodo* der;
};

class AVL {
public:
    AVL() { raiz = nullptr; }

    bool Insert(int v) {
        Nodo** ptr;
        if (Find(ptr, v))
            return 0;
        else {
            *ptr = new Nodo(v);
            while (!s.empty()) {
                Nodo* par = s.top();
                s.pop();
                Nodo* padre_par = nullptr;
                if (!s.empty()) padre_par = s.top();
                int dif = diferencia_de_alturas(par);
                if (dif < -1) {
                    if (diferencia_de_alturas(par->der) <= 0)
                        RR(par, padre_par);
                    else
                        RL(par, padre_par);
                }
                if (dif > 1) {
                    if (diferencia_de_alturas(par->izq) >= 0)
                        LL(par, padre_par);
                    else
                        LR(par, padre_par);
                }
            }
            return 1;
        }
    }

    bool Remove(int v) {
        Nodo** ptr;
        if (!Find(ptr, v)) return 0;
        else {
            if ((*ptr)->izq && (*ptr)->der) {
                Nodo** q = reemplazo(ptr);
                (*ptr)->valor = (*q)->valor;
                ptr = q;
            }
            Nodo* temp = *ptr;
            if (temp->der)
                *ptr = temp->der;
            else
                *ptr = temp->izq;
            delete temp;

            // rebalanceo
            while (!s.empty()) {
                Nodo* par = s.top();
                s.pop();
                Nodo* padre_par = nullptr;
                if (!s.empty()) padre_par = s.top();
                int dif = diferencia_de_alturas(par);
                if (dif < -1) {
                    if (diferencia_de_alturas(par->der) <= 0)
                        RR(par, padre_par);
                    else
                        RL(par, padre_par);
                }
                if (dif > 1) {
                    if (diferencia_de_alturas(par->izq) >= 0)
                        LL(par, padre_par);
                    else
                        LR(par, padre_par);
                }
            }
            return 1;
        }
    }

    void PrintInOrder() {
        InOrder(raiz);
        cout << endl;
    }

    Nodo* getRoot() { return raiz; }

private:
    Nodo* raiz;
    stack<Nodo*> s;
    bool Find(Nodo**& ptr, int v) {
        while (!s.empty()) s.pop();
        ptr = &raiz;
        while (*ptr && (*ptr)->valor != v) {
            s.push(*ptr);
            if ((*ptr)->valor > v)
                ptr = &((*ptr)->izq);
            else
                ptr = &((*ptr)->der);
        }
        return *ptr != NULL;
    }

    int Alturas(Nodo* n) {
        if (!n) return 0;
        int izq = Alturas(n->izq);
        int der = Alturas(n->der);
        return max(izq, der) + 1;
    }

    int diferencia_de_alturas(Nodo* n) {
        if (!n) return 0;
        return Alturas(n->izq) - Alturas(n->der);
    }

    void RR(Nodo* par, Nodo* padre_par) {
        Nodo* A = par;
        Nodo* B = par->der;
        Nodo* temp = B->izq;
        A->der = temp;
        B->izq = A;
        Nodo* tmp = B;
        if (padre_par) {
            if (padre_par->izq == par)
                padre_par->izq = tmp;
            else
                padre_par->der = tmp;
        }
        else
            raiz = tmp;
    }

    void RL(Nodo* par, Nodo* padre_par) {
        Nodo* A = par;
        Nodo* C = A->der;
        Nodo* B = C->izq;
        Nodo* temp1 = B->izq;
        Nodo* temp2 = B->der;
        A->der = temp1;
        C->izq = temp2;
        B->izq = A;
        B->der = C;
        Nodo* tmp = B;
        if (padre_par) {
            if (padre_par->izq == par)
                padre_par->izq = tmp;
            else
                padre_par->der = tmp;
        }
        else
            raiz = tmp;
    }

    void LL(Nodo* par, Nodo* padre_par) {
        Nodo* C = par;
        Nodo* B = C->izq;
        Nodo* temp = B->der;
        C->izq = temp;
        B->der = C;
        Nodo* tmp = B;
        if (padre_par) {
            if (padre_par->izq == par)
                padre_par->izq = tmp;
            else
                padre_par->der = tmp;
        }
        else
            raiz = tmp;
    }

    void LR(Nodo* par, Nodo* padre_par) {
        Nodo* C = par;
        Nodo* A = C->izq;
        Nodo* B = A->der;
        Nodo* temp1 = B->izq;
        Nodo* temp2 = B->der;
        A->der = temp1;
        C->izq = temp2;
        B->izq = A;
        B->der = C;
        Nodo* tmp = B;
        if (padre_par) {
            if (padre_par->izq == par)
                padre_par->izq = tmp;
            else
                padre_par->der = tmp;
        }
        else
            raiz = tmp;
    }

    Nodo** reemplazo(Nodo** ptr) {
        if (rand() % 2 == 1)
            for (ptr = &((*ptr)->der); *ptr && (*ptr)->izq; ptr = &((*ptr)->izq));
        else
            for (ptr = &((*ptr)->izq); *ptr && (*ptr)->der; ptr = &((*ptr)->der));
        return ptr;
    }

    void InOrder(Nodo* n) {
        if (!n) return;
        InOrder(n->izq);
        cout << n->valor << " ";
        InOrder(n->der);
    }
};

// -------------------- GRAFICADOR SDL3 ------------------------

void DrawCircle(SDL_Renderer* renderer, int x, int y, int r) {
    for (int w = 0; w < r * 2; w++)
        for (int h = 0; h < r * 2; h++) {
            int dx = r - w;
            int dy = r - h;
            if ((dx * dx + dy * dy) <= (r * r))
                SDL_RenderPoint(renderer, x + dx, y + dy);
        }
}

void DrawText(SDL_Renderer* renderer, TTF_Font* font, const string& text, int x, int y) {
    SDL_Color color = { 0, 0, 0, 255 };
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), 0, color);
    if (!surface) return;
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FRect dst = { (float)x - surface->w / 2, (float)y - surface->h / 2, (float)surface->w, (float)surface->h };
    SDL_RenderTexture(renderer, texture, NULL, &dst);
    SDL_DestroyTexture(texture);
    SDL_DestroySurface(surface);
}

void DrawNode(SDL_Renderer* renderer, TTF_Font* font, Nodo* node, int x, int y, int offsetX) {
    if (!node) return;

    int childY = y + 80;
    if (node->izq)
        SDL_RenderLine(renderer, x, y, x - offsetX, childY);
    if (node->der)
        SDL_RenderLine(renderer, x, y, x + offsetX, childY);

    DrawCircle(renderer, x, y, 25);
    DrawText(renderer, font, to_string(node->valor), x, y);

    if (node->izq)
        DrawNode(renderer, font, node->izq, x - offsetX, childY, offsetX / 2);
    if (node->der)
        DrawNode(renderer, font, node->der, x + offsetX, childY, offsetX / 2);
}

void RenderAVL(AVL& avl) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) return;
    if (TTF_Init() < 0) return;

    SDL_Window* window = SDL_CreateWindow("AVL Tree", 1080, 1020, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
    TTF_Font* font = TTF_OpenFont("C:/Windows/Fonts/arial.ttf", 18);
    if (!font) {
        cout << "No se encontró Arial.ttf\n";
        return;
    }

    bool running = true;
    SDL_Event e;
    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT)
                running = false;
        }

        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        DrawNode(renderer, font, avl.getRoot(), 500, 80, 200);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}

// -------------------- MAIN ------------------------

int main() {
    AVL avl;
    int arr[12] = { 1,8,3,7,2,9,4,5,6,21,25,36 };
    for (int i = 0; i < 12; i++)
    {
        avl.Insert(arr[i]);
    }
    avl.PrintInOrder();

    RenderAVL(avl);
    return 0;
}
