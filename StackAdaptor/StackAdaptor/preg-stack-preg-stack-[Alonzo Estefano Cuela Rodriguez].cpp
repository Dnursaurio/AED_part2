#include <iostream>
using namespace std;

// Primero, implementa una lista enlazada simple
struct Node
{
    Node(int v)
    {
        valor = v;
        next = NULL;
    }
    int valor;
    Node* next;
};

class SinglyLinkedList
{
public:

    // Metodos de la lista enlazada: constructor, destructor, etc
    SinglyLinkedList()
    {
        head = nullptr;
    }

    ~SinglyLinkedList()
    {
        while (head)
        {
            Node* temp = head->next;
            head->next = 0;
            delete head;
            head = temp;
        }
    }

    bool Find(int x, Node**& ptr)
    {
        for (ptr = &head; *ptr && (*ptr)->valor < x; ptr = &((*ptr)->next));
        return  *ptr && (*ptr)->valor < x;
    }

    bool push(int x)
    {
        Node** ptr;
        if (Find(x, ptr))
        {
            return 0;
        }
        else
        {
            Node* temp = new Node(x);
            *ptr = temp;
            return 1;
        }
    }

    //segun indicaciones esto es como un pop front
    bool pop()
    {
        if (!head)
        {
            return 0;
        }
        else
        {
            Node* temp = head;
            head = head->next;
            temp->next = 0;
            delete temp;
            return 1;
        }
    }

    int& top()
    {
        return head->valor;
    }

    bool vacio()
    {
        return head == 0;
    }

    void print()
    {
        Node** printer = &head;
        for (printer; *printer; printer = &(*printer)->next)
        {
            cout << (*printer)->valor << " ";
        }
        return;
    }
    
private:
    Node* head;
};

// Ahora, crea un adaptador de Stack usando tu lista enlazada
class Stack
{
public:
    // Debes implementar estas funciones
    void push(int x)
    {
        // Inserta el elemento x en la parte superior de la pila
        sll.push(x);
    }
    
    bool pop()
    {
        // Elimina el elemento superior de la pila
        if (sll.pop()) return 1;
        return 0;
    }
    
    int& top()
    {
        // Devuelve una referencia al elemento superior de la pila
        return sll.top();
    }
    
    bool empty()
    {
        // Devuelve true si la pila está vacía, false en caso contrario
        return sll.vacio();
    }
    
    // Función auxiliar para depuración
    void print()
    {
        // Aqui llamar al print de la lista enlazada
        sll.print();
    }
    
private:
    // Debes usar tu lista enlazada como almacenamiento interno
    SinglyLinkedList sll;
};

int main()
{
    // Pruebas del stack
    Stack stack;
    
    // Prueba 1: Inserción de elementos
    std::cout << "Prueba 1: Insertando elementos" << std::endl;
    stack.push(10);
    stack.push(20);
    stack.push(30);
    std::cout << "Stack: ";
    stack.print();
    
    // Prueba 2: Acceso al elemento superior
    std::cout << "\nPrueba 2: Elemento superior" << std::endl;
    std::cout << "Top: " << stack.top() << std::endl;
    
    // Prueba 3: Eliminación de elementos
    std::cout << "\nPrueba 3: Eliminando elementos" << std::endl;
    stack.pop();
    std::cout << "Después de pop: ";
    stack.print();
    std::cout << "Nuevo top: " << stack.top() << std::endl;
    
    // Prueba 4: Verificación de pila vacía
    std::cout << "\nPrueba 4: Verificación de pila vacía" << std::endl;
    std::cout << "¿Está vacía? " << (stack.empty() ? "Sí" : "No") << std::endl;
    
    // Prueba 5: Vaciado completo de la pila
    std::cout << "\nPrueba 5: Vaciado completo" << std::endl;
    stack.pop(); // Queda un elemento
    stack.pop(); // Queda vacía
    std::cout << "Después de vaciar: ";
    stack.print();
    std::cout << "¿Está vacía? " << (stack.empty() ? "Sí" : "No") << std::endl;
    
    // Prueba 6: Operaciones adicionales
    std::cout << "\nPrueba 6: Operaciones adicionales" << std::endl;
    for (int i = 1; i <= 5; i++)
    {
        stack.push(i * 10);
    }
    std::cout << "Después de insertar 5 elementos: ";
    stack.print();
    
    return 0;
}
