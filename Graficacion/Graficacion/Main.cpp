#include <vector>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>

struct Nodo
{
    Nodo(int val)
    {
        v = val;
        izq = NULL;
        der = NULL;
    }
    int v;
    Nodo* izq;
    Nodo* der;
};

void InOrder(Nodo* n)
{
    if (!n)
    {
        return;
    }
    InOrder(n->izq);
    std::cout << n->v << " ";
    InOrder(n->der);
}

Nodo* CrearArbol(int* ini, int* fin)
{
    std::vector<Nodo*>v;
    for (; ini < fin; ini++)
    {
        Nodo* n = new Nodo(*ini);
        v.push_back(n);
    }
    while (v.size() > 1)
    {
        int suma = v[0]->v + v[1]->v;
        Nodo* n2 = new Nodo(suma);
        n2->izq = v[0];
        n2->der = v[1];
        v.erase(v.begin());
        v.erase(v.begin());
        v.push_back(n2);
    }

    Nodo* raiz = v.front();
    InOrder(raiz);
    return raiz;
}

int main()
{   
    int arr[16] = { 2,4,7,9,10,15,3,25,38,74,1,5,10,13,11,35 };
    int* ini = arr;
    int* fin = arr + 16;
    CrearArbol(ini, fin);

    return 0;
}