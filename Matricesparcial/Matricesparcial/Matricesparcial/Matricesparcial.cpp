#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <Windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib") // Enlazar la biblioteca de sonido

#define TECLA_ARRIBA 72
#define TECLA_ABAJO 80
#define ENTER 13

using namespace std;

void gotoxy(int x, int y);
void menuPrincipal();
int SumaMatrices();
int RestaMatrices();
int MultiplicacionMatrices();
void Salir();
int menu(const char* titulo, const char* opciones[], int n);
void ingresarMatriz(int matriz[][10], int filas, int columnas, int numeroMatriz);
void sumarMatrices(int matrizA[][10], int matrizB[][10], int resultado[][10], int filas, int columnas);
void imprimirMatriz(int matriz[][10], int filas, int columnas, int x, int y);
void restarMatrices(int matrizA[][10], int matrizB[][10], int resultado[][10], int filas, int columnas);
void multiplicarMatrices(int matrizA[][10], int matrizB[][10], int resultado[][10], int filasA, int columnasA, int columnasB);
void datos();
void menuTamanioMatriz(const char* titulo, int& filas, int& columnas);
void playSound();

int filasA, columnasA, filasB, columnasB;

void gotoxy(int x, int y) {
    COORD coord{};
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void playSound() {
    Beep(523, 100); // Sonido al seleccionar una opción
}

int main() {
    datos();
    menuPrincipal();
    return EXIT_SUCCESS;
}

void menuPrincipal() {
    bool rep = true;
    int op;

    system("color 3D");
    const char* titulo = "MENU PRINCIPAL";
    const char* opciones[] = { "SUMA DE MATRICES", "RESTA DE MATRICES", "MULTIPLICACION DE MATRICES", "SALIDA" };
    int n = 4;

    do {
        op = menu(titulo, opciones, n);
        switch (op) {
        case 1:
            system("cls");
            SumaMatrices();
            break;
        case 2:
            system("cls");
            RestaMatrices();
            break;
        case 3:
            system("cls");
            MultiplicacionMatrices();
            break;
        case 4:
            system("cls");
            Salir();
            rep = false;
            break;
        }
        system("pause>nul");
    } while (rep);
}

void menuTamanioMatriz(const char* titulo, int& filas, int& columnas) {
    system("cls");
    gotoxy(35, 5); cout << titulo;
    gotoxy(35, 7); cout << "Ingrese el numero de filas: ";
    cin >> filas;
    gotoxy(35, 9); cout << "Ingrese el numero de columnas: ";
    cin >> columnas;
    playSound(); // Sonido al ingresar el tamaño
}

int SumaMatrices() {
    gotoxy(50, 2); cout << "SUMA DE MATRICES";

    menuTamanioMatriz("TAMANIO DE LA PRIMERA MATRIZ", filasA, columnasA);
    menuTamanioMatriz("TAMANIO DE LA SEGUNDA MATRIZ", filasB, columnasB);

    if (filasA > 0 && columnasA > 0 && filasB > 0 && columnasB > 0 && filasA == filasB && columnasA == columnasB) {
        int matriz1[10][10], matriz2[10][10], resultado[10][10];
        ingresarMatriz(matriz1, filasA, columnasA, 1);
        ingresarMatriz(matriz2, filasB, columnasB, 2);
        sumarMatrices(matriz1, matriz2, resultado, filasA, columnasA);

        system("cls");
        gotoxy(10, 2); cout << "Matriz A:";
        imprimirMatriz(matriz1, filasA, columnasA, 10, 4);

        gotoxy(40, 2); cout << "Matriz B:";
        imprimirMatriz(matriz2, filasB, columnasB, 40, 4);

        gotoxy(70, 2); cout << "Resultado (A + B):";
        imprimirMatriz(resultado, filasA, columnasA, 70, 4);

        PlaySound(L"..\\VictorySoundEffect.wav", NULL, SND_FILENAME | SND_ASYNC);
        _getch();
    }
    else {
        gotoxy(10, 25); cout << "No se pueden sumar las matrices debido a dimensiones incompatibles." << endl;
        PlaySound(L"..\\errorsoundeffect.wav", NULL, SND_FILENAME | SND_ASYNC);
        _getch();
    }
    return EXIT_SUCCESS;
}

int RestaMatrices() {
    gotoxy(50, 2); cout << "RESTA DE MATRICES";

    menuTamanioMatriz("TAMAÑO DE LA PRIMERA MATRIZ", filasA, columnasA);
    menuTamanioMatriz("TAMAÑO DE LA SEGUNDA MATRIZ", filasB, columnasB);

    if (filasA > 0 && columnasA > 0 && filasB > 0 && columnasB > 0 && filasA == filasB && columnasA == columnasB) {
        int matriz1[10][10], matriz2[10][10], resultado[10][10];
        ingresarMatriz(matriz1, filasA, columnasA, 1);
        ingresarMatriz(matriz2, filasB, columnasB, 2);
        restarMatrices(matriz1, matriz2, resultado, filasA, columnasA);

        system("cls");
        gotoxy(10, 2); cout << "Matriz A:";
        imprimirMatriz(matriz1, filasA, columnasA, 10, 4);

        gotoxy(40, 2); cout << "Matriz B:";
        imprimirMatriz(matriz2, filasB, columnasB, 40, 4);

        gotoxy(70, 2); cout << "Resultado (A - B):";
        imprimirMatriz(resultado, filasA, columnasA, 70, 4);

        PlaySound(L"..\\exito2.wav", NULL, SND_FILENAME | SND_ASYNC);
        _getch();
    }
    else {
        cout << "No se pueden restar las matrices debido a dimensiones incompatibles." << endl;
        PlaySound(L"..\\errorsoundeffect.wav", NULL, SND_FILENAME | SND_ASYNC);
        _getch();
    }
    return EXIT_SUCCESS;
}

int MultiplicacionMatrices() {
    gotoxy(50, 2); cout << "MULTIPLICACION DE MATRICES";

    menuTamanioMatriz("TAMAÑO DE LA PRIMERA MATRIZ", filasA, columnasA);
    menuTamanioMatriz("TAMAÑO DE LA SEGUNDA MATRIZ", filasB, columnasB);

    if (filasA > 0 && columnasA > 0 && filasB > 0 && columnasB > 0 && columnasA == filasB) {
        int matriz1[10][10], matriz2[10][10], resultado[10][10];
        ingresarMatriz(matriz1, filasA, columnasA, 1);
        ingresarMatriz(matriz2, filasB, columnasB, 2);
        multiplicarMatrices(matriz1, matriz2, resultado, filasA, columnasA, columnasB);

        system("cls");
        gotoxy(10, 2); cout << "Matriz A:";
        imprimirMatriz(matriz1, filasA, columnasA, 10, 4);

        gotoxy(40, 2); cout << "Matriz B:";
        imprimirMatriz(matriz2, filasB, columnasB, 40, 4);

        gotoxy(70, 2); cout << "Resultado (A * B):";
        imprimirMatriz(resultado, filasA, columnasB, 70, 4);

        _getch();
    }
    else {
        cout << "No se pueden multiplicar las matrices debido a dimensiones incompatibles." << endl;
        PlaySound(L"..\\errorsoundeffect.wav", NULL, SND_FILENAME | SND_ASYNC);
        _getch();
    }
    return EXIT_SUCCESS;
}

void Salir() {
    gotoxy(5, 15); cout << "SALIENDO......................................................................................Presione ENTER";
    playSound(); // Sonido al salir
    system("pause>nul");
}

int menu(const char* titulo, const char* opciones[], int n) {
    int opcionSeleccionada = 1;
    int tecla;
    bool repite = true;

    do {
        system("cls");
        gotoxy(45, 7 + opcionSeleccionada); cout << "-->";
        gotoxy(55, 5); cout << titulo;
        for (int i = 0; i < n; i++) {
            gotoxy(50, 8 + i); cout << i + 1 << ". " << opciones[i];
        }
        gotoxy(5, 20); cout << "Escoja la opcion con las teclas de direccion de su teclado y para escojer cualquier opcion presione enter";

        do {
            tecla = _getch();
        } while (tecla != TECLA_ARRIBA && tecla != TECLA_ABAJO && tecla != ENTER);

        switch (tecla) {
        case TECLA_ARRIBA:
            opcionSeleccionada--;
            if (opcionSeleccionada < 1) {
                opcionSeleccionada = n;
            }
            playSound(); // Sonido al moverse
            break;
        case TECLA_ABAJO:
            opcionSeleccionada++;
            if (opcionSeleccionada > n) {
                opcionSeleccionada = 1;
            }
            playSound(); // Sonido al moverse
            break;
        case ENTER:
            repite = false;
            playSound(); // Sonido al seleccionar
            break;
        }
    } while (repite);

    return opcionSeleccionada;
}

void ingresarMatriz(int matriz[][10], int filas, int columnas, int numeroMatriz) {
    system("cls");
    gotoxy(40, 3); cout << "Ingrese los elementos de la matriz " << numeroMatriz << ":" << endl;

    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            gotoxy(10, 5 + i); cout << "Elemento [" << i << "][" << j << "]: ";
            gotoxy(30 + j * 7, 5 + i); cin >> matriz[i][j];
        }
    }
    playSound(); // Sonido al ingresar datos
}

void imprimirMatriz(int matriz[][10], int filas, int columnas, int x, int y) {
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            gotoxy(x + j * 7, y + i);
            cout << "[" << matriz[i][j] << "]";
        }
    }
}

void sumarMatrices(int matrizA[][10], int matrizB[][10], int resultado[][10], int filas, int columnas) {
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            resultado[i][j] = matrizA[i][j] + matrizB[i][j];
        }
    }
}

void restarMatrices(int matrizA[][10], int matrizB[][10], int resultado[][10], int filas, int columnas) {
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            resultado[i][j] = matrizA[i][j] - matrizB[i][j];
        }
    }
}

void multiplicarMatrices(int matrizA[][10], int matrizB[][10], int resultado[][10], int filasA, int columnasA, int columnasB) {
    for (int i = 0; i < filasA; ++i) {
        for (int j = 0; j < columnasB; ++j) {
            resultado[i][j] = 0;
            for (int k = 0; k < columnasA; ++k) {
                resultado[i][j] += matrizA[i][k] * matrizB[k][j];
            }
        }
    }
}

void datos() {
    system("color AF");
    gotoxy(35, 5); cout << "*************************************************";
    gotoxy(35, 6); cout << "*           OPERACIONES  MATRICIALES            *";
    gotoxy(35, 7); cout << "*************************************************";
    gotoxy(35, 8); cout << "*                                               *";
    gotoxy(35, 9); cout << "*************************************************";
    gotoxy(35, 8); cout << "*                PROGRAMACION I                 *";
    gotoxy(35, 9); cout << "*************************************************";
    gotoxy(35, 10); cout << "*  Estudiantes:                  Carnet:        *";
    gotoxy(35, 11); cout << "************************************************";
    gotoxy(35, 12); cout << "*  Carla Marina Chumil Sequen    2290-23-14690  *";
    gotoxy(35, 13); cout << "*************************************************";
    gotoxy(35, 14); cout << "*  William Eduardo Yoc Chalcu    2290-23-11497  *";
    gotoxy(35, 15); cout << "*************************************************";
    gotoxy(35, 16); cout << "*  Maria      2290-23-14631  *";
    gotoxy(35, 17); cout << "*************************************************";
    gotoxy(35, 20); cout << "Presione ENTER para continuar...";
    system("pause>nul");
}