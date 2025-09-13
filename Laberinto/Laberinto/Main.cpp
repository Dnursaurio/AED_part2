#include <iostream>

using namespace std;

char laberinto[10][10] = {
    {'A','*',' ',' ',' ',' ',' ',' ',' ','*'},
    {' ','*',' ',' ',' ',' ','*','*',' ','*'},
    {' ','*',' ','*','*',' ','*','*','*','*'},
    {' ','*',' ','*',' ',' ','*',' ',' ',' '},
    {' ',' ',' ','*',' ',' ',' ',' ','*','*'},
    {' ','*','*','*','*','*',' ',' ','*',' '},
    {' ',' ',' ',' ','*',' ',' ',' ',' ',' '},
    {' ','*','*',' ','*',' ',' ','*','*','*'},
    {'*','*',' ',' ','*',' ',' ','*',' ',' '},
    {' ',' ',' ','*','*',' ',' ',' ',' ','B'}
};

bool recorrer(char (*fila_actual)[10], char* columna_actual) {
    if (*columna_actual == 'B') return true;

    if (*columna_actual != 'A') {
        if (*columna_actual != ' ') return false;
        *columna_actual = '+';
    }

    int fila_detectada = fila_actual - laberinto;
    int columna_detectada = columna_actual - *fila_actual;

    int mov[4][2] = { {1,0}, {-1,0}, {0,1}, {0,-1} };

    for (int i = 0; i < 4; i++) {
        int siguiente_fila = fila_detectada + mov[i][0];
        int siguiente_columna = columna_detectada + mov[i][1];

        if (siguiente_fila < 0 || siguiente_fila >= 10 || siguiente_columna < 0 || siguiente_columna >= 10)
            continue;

        if (recorrer(laberinto + siguiente_fila, *(laberinto + siguiente_fila) + siguiente_columna)) {
            return true;
        }
    }

    if (*columna_actual == '+') *columna_actual = ' ';
    return false;
}

int main()
{
    cout << "---------------------------Laberinto A_B---------------------------" << endl;

    for (char(*filas)[10] = laberinto; filas < laberinto + 10; filas++) {
        for (char* columnas = *filas; columnas < *filas + 10; columnas++) {
            cout << *columnas << " ";
        }
        cout << "|" << endl;
    }

    cout << "---------------------" << endl;

    char(*fila_actual)[10] = laberinto;
    char* columna_actual = *fila_actual;
    for (char(*filas)[10] = laberinto; filas < laberinto + 10; filas++) {
        for (char* columnas = *filas; columnas < *filas + 10; columnas++) {
            if (*columnas == 'A') {
                fila_actual = filas;
                columna_actual = columnas;
            }
        }
    }

    recorrer(fila_actual, columna_actual);

    for (char(*filas)[10] = laberinto; filas < laberinto + 10; filas++) {
        for (char* columnas = *filas; columnas < *filas + 10; columnas++) {
            cout << *columnas << " ";
        }
        cout << "|" << endl;
    }
    cout << "---------------------" << endl;

    cout << "-------------------------------------------------------------------" << endl;
}
