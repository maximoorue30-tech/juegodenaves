/*
====================================================================
Materia: Laboratorio de Programación (LPR) - 5° Año
Institución: E.E.S.T. N° 1 "Eduardo Ader" - Vicente López
Archivo: src/main.cpp
Actividad 8: Introducción a POO - Motor de Juego de Naves (class Nave + Boss)
Docente: Mansilla Muñoz York Elías
Estudiante: Maximo Benjamin Orue
====================================================================
*/

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <ctime>
#include <cctype> // Para tolower()

using namespace std;

void gotoxy(int x, int y) {
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hCon, dwPos);
}

void ocultarCursor() {
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = 2;
    cci.bVisible = FALSE;
    SetConsoleCursorInfo(hCon, &cci);
}

// ====================================================================
// CLASE NAVE (El Jugador)
// ====================================================================
class Nave {
private:
    int x, y;
    int vidas;

public:
    Nave(int _x, int _y, int _vidas) {
        x = _x;
        y = _y;
        vidas = _vidas;
    }

    int getX() { return x; }
    int getY() { return y; }
    int getVidas() { return vidas; }
    void reducirVida() { vidas--; }

    void pintar() {
        gotoxy(x, y);     cout << "  ^  ";
        gotoxy(x, y + 1); cout << " (0) ";
        gotoxy(x, y + 2); cout << "^^^^ ";
    }

    void borrar() {
        gotoxy(x, y);     cout << "     ";
        gotoxy(x, y + 1); cout << "     ";
        gotoxy(x, y + 2); cout << "     ";
    }

    void mover(char tecla) {
        borrar();
        if (tecla == 'a' && x > 2)  x--;
        if (tecla == 'd' && x < 70) x++;
        if (tecla == 'w' && y > 5)  y--;
        if (tecla == 's' && y < 20) y++;
        pintar();
    }
};

// ====================================================================
// CLASE ASTEROIDE Y BALA
// ====================================================================
class Asteroide {
private:
    int x, y;

public:
    Asteroide(int _x, int _y) {
        x = _x;
        y = _y;
    }

    int getX() { return x; }
    int getY() { return y; }

    void pintar() { gotoxy(x, y); cout << "O"; }
    void borrar() { gotoxy(x, y); cout << " "; }

    void mover() {
        borrar();
        y++;
        if (y > 23) {
            y = 4;
            x = (rand() % 70) + 2;
        }
        pintar();
    }
};

class Bala {
private:
    int x, y;

public:
    Bala(int _x, int _y) {
        x = _x;
        y = _y;
    }

    int getX() { return x; }
    int getY() { return y; }

    void mover() {
        gotoxy(x, y); cout << " ";
        y--;
        gotoxy(x, y); cout << "|";
    }

    bool fueraDeRango() { return y < 4; }
};

// ====================================================================
// DESAFÍO OBLIGATORIO - FUNCIONALIDAD 13: CLASE BOSS FINAL
// Aparece cuando score > 1000 y barre la pantalla de lado a lado.
// ====================================================================
class Boss {
private:
    int x, y, hp, direccion;

public:
    Boss() {
        x = 30;
        y = 3;
        hp = 50;
        direccion = 1;
    }

    int getX() { return x; }
    int getY() { return y; }
    int getHp() { return hp; }
    void recibirDanio() { hp--; }

    void borrar() {
        gotoxy(x, y);
        cout << "             ";
    }

    void mover() {
        borrar();
        x += direccion;
        if (x >= 60 || x <= 5) direccion *= -1; // Rebote en bordes
        gotoxy(x, y);
        cout << "[\\]=======/[/]"; // Pintar nave jefe (13 caracteres)
    }
};

// ====================================================================
// PROGRAMA PRINCIPAL
// ====================================================================
int main() {
    srand(time(NULL));

    // SISTEMA ANTI-COPIA: Petición de datos
    string nombrePiloto;
    cout << "Ingresa tu Nombre y Apellido (Se mostrara en la captura de pantalla): ";
    getline(cin, nombrePiloto);

    system("cls");
    ocultarCursor();

    bool gameOver = false;
    int score = 0;
    bool bossDerrotado = false;

    Nave jugador(35, 20, 3);
    Boss* jefeFinal = nullptr;

    vector<Asteroide*> asteroides;
    vector<Bala*> balas;

    for (int i = 0; i < 5; i++) {
        asteroides.push_back(new Asteroide((rand() % 70) + 2, (rand() % 5) + 4));
    }

    jugador.pintar();

    while (!gameOver) {
        // HUD CON NOMBRE DEL ESTUDIANTE, VIDAS Y SCORE
        gotoxy(2, 1);
        cout << "PILOTO: " << nombrePiloto << "   ";
        gotoxy(2, 2);
        cout << "VIDAS: " << jugador.getVidas() << " | SCORE: " << score << "   ";

        // Aparición del Boss Final si score > 1000
        if (score > 1000 && jefeFinal == nullptr && !bossDerrotado) {
            jefeFinal = new Boss();
        }

        // Movimiento y HUD del Boss activo
        if (jefeFinal != nullptr) {
            jefeFinal->mover();
            gotoxy(42, 2);
            cout << "BOSS HP: " << jefeFinal->getHp() << "/50   ";
        }

        // Controles de teclado
        if (_kbhit()) {
            char tecla = tolower(_getch()); // tolower evita el problema del Bloq Mayús
            if (tecla == ' ') {
                balas.push_back(new Bala(jugador.getX() + 2, jugador.getY() - 1));
            } else {
                jugador.mover(tecla);
            }
        }

        // Movimiento y colisión de balas
        for (int i = 0; i < (int)balas.size(); i++) {
            balas[i]->mover();
            bool balaEliminada = false;

            // Colisión Bala -> Boss Final (ancho de 13 caracteres: x a x + 12)
            if (jefeFinal != nullptr) {
                if (balas[i]->getY() <= jefeFinal->getY() &&
                    balas[i]->getX() >= jefeFinal->getX() &&
                    balas[i]->getX() <= jefeFinal->getX() + 12) {

                    jefeFinal->recibirDanio();
                    score += 25;

                    gotoxy(balas[i]->getX(), balas[i]->getY()); cout << " ";
                    delete balas[i];
                    balas.erase(balas.begin() + i);
                    i--;
                    balaEliminada = true;

                    if (jefeFinal->getHp() <= 0) {
                        jefeFinal->borrar();
                        delete jefeFinal;
                        jefeFinal = nullptr;
                        bossDerrotado = true;
                        score += 1000;
                        gotoxy(42, 2);
                        cout << "BOSS DERROTADO! +1000 ";
                    }
                }
            }

            if (!balaEliminada && balas[i]->fueraDeRango()) {
                gotoxy(balas[i]->getX(), balas[i]->getY()); cout << " ";
                delete balas[i];
                balas.erase(balas.begin() + i);
                i--;
            }
        }

        // Movimiento y colisión de asteroides
        for (int i = 0; i < (int)asteroides.size(); i++) {
            asteroides[i]->mover();

            // Colisión Asteroide -> Jugador
            if ((asteroides[i]->getX() >= jugador.getX() && asteroides[i]->getX() <= jugador.getX() + 4) &&
                (asteroides[i]->getY() >= jugador.getY() && asteroides[i]->getY() <= jugador.getY() + 2)) {
                jugador.borrar();
                jugador.reducirVida();
                asteroides[i]->borrar();
                delete asteroides[i];
                asteroides[i] = new Asteroide((rand() % 70) + 2, 4);
                jugador.pintar();
                if (jugador.getVidas() <= 0) gameOver = true;
            }

            // Colisión Bala -> Asteroide
            for (int j = 0; j < (int)balas.size(); j++) {
                if (asteroides[i]->getX() == balas[j]->getX() &&
                    (asteroides[i]->getY() == balas[j]->getY() || asteroides[i]->getY() + 1 == balas[j]->getY())) {

                    gotoxy(balas[j]->getX(), balas[j]->getY()); cout << " ";
                    delete balas[j];
                    balas.erase(balas.begin() + j);

                    asteroides[i]->borrar();
                    delete asteroides[i];
                    asteroides[i] = new Asteroide((rand() % 70) + 2, 4);

                    score += 100; // Suma puntos para invocar al Boss (> 1000)
                    break;
                }
            }
        }

        Sleep(30);
    }

    // Liberación de memoria dinámica
    if (jefeFinal != nullptr) delete jefeFinal;
    for (Asteroide* a : asteroides) delete a;
    for (Bala* b : balas) delete b;

    system("cls");
    gotoxy(30, 10);
    cout << "GAME OVER... O sea... Perdiste!!";
    gotoxy(30, 11);
    cout << "PUNTAJE FINAL: " << score;
    gotoxy(30, 13);
    system("pause");
    return 0;
}
