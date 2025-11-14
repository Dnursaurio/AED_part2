#include <iostream>
#include <stack>
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

int main()
{
    RBtree arbol;

    int op, x;

    while (true)
    {
        cout << "\n--- MENU ---\n";
        cout << "1. Insertar\n";
        cout << "2. Eliminar\n";
        cout << "3. Mostrar in-order\n";
        cout << "4. Salir\n";
        cout << "Opcion: ";
        cin >> op;

        if (op == 1)
        {
            cout << "Valor a insertar: ";
            cin >> x;
            arbol.Insert(x);
            cout << "Insertado.\n";
        }
        else if (op == 2)
        {
            cout << "Valor a eliminar: ";
            cin >> x;
            if (arbol.Remove(x))
                cout << "Eliminado.\n";
            else
                cout << "No existe.\n";
        }
        else if (op == 3)
        {
            cout << "In-order: ";
            arbol.PrintInOrder();
            cout << "\n";
        }
        else if (op == 4)
        {
            break;
        }
        else
        {
            cout << "Opcion invalida.\n";
        }
    }

    return 0;
}

