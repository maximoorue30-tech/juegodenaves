# MANUAL TÉCNICO DEL PROGRAMADOR Y ARQUITECTURA DE CÓDIGO

* **Proyecto:** Juego de Naves en Consola en C++ — Programación Orientada a Objetos (Actividad 8)
* **Institución:** E.E.S.T. N.° 1 "Eduardo Ader" — Vicente López
* **Asignatura:** Laboratorio de Programación (LPR) — 5° Año 3° Grupos A-B
* **Docente:** Prof. Mansilla Muñoz York Elías
* **Autor / Grupo:** [Apellido y Nombre / Grupo 03]
* **Fecha:** 21 de octubre de 2026 | **Versión:** v1.0.0

---

## CONTROL DE VERSIONES Y CHANGELOG

| Versión | Fecha | Autor | Descripción de Cambios |
| :--- | :--- | :--- | :--- |
| **v1.0.0** | 21/10/2026 | [Autor / Grupo 03] | Versión inicial del motor de combate espacial en C++ con clases `Nave`, `Asteroide` y `Bala`, encapsulamiento y sincronización Dual-Remote. |

---

## 1. ARQUITECTURA DEL SISTEMA Y ENTORNO DE DESARROLLO

### Requisitos del Entorno
* **Compilador:** `g++` (MinGW-w64 GCC v8.1.0 o superior) con estándar `-std=c++11` habilitado.
* **Librerías Utilizadas:** `<iostream>`, `<windows.h>`, `<conio.h>`, `<vector>`, `<ctime>` y `<cctype>`.
* **IDE recomendado:** Visual Studio Code con extensión *C/C++ Extension Pack*.
* **Shell y Control de Versiones:** Windows PowerShell 5.1+ y Git configurado en modo Dual-Remote (GitHub + GitLab).

### Estructura de Directorios del Repositorio

```text
/juegodenaves/
├── .gitattributes          <-- Normalización de finales de línea
├── .gitignore              <-- Exclusiones (.exe, *.out, .vscode/)
├── LICENSE                 <-- Licencia MIT escolar
├── README.md               <-- Portada del proyecto
├── CHANGELOG.md            <-- Historial de versiones del software
├── docs/                   <-- Carpeta de Documentación Formal
│   ├── InformeEEST1_LPR2026_ACT08_G03_v1.0.0.pdf
│   └── manuales/
│       ├── manual_programador_v1.0.0.pdf
│       ├── manual_programador_v1.0.0.md
│       ├── manual_usuario_v1.0.0.pdf
│       └── manual_usuario_v1.0.0.md
├── src/                    <-- Código fuente C++
│   └── main.cpp
└── capturas/               <-- Evidencias de ejecución (.png)
    └── combate_consola.png <-- Captura de tu consola con tu nombre y apellido
```

---

## 2. DOCUMENTACIÓN DE CLASES Y MÓDULOS (`src/main.cpp`)

### Funciones Auxiliares de Consola: `gotoxy()` y `ocultarCursor()`
* **Propósito:** Posicionar el cursor en coordenadas `(x, y)` de la consola de Windows mediante `SetConsoleCursorPosition` y ocultar el cursor parpadeante mediante `SetConsoleCursorInfo`.

### Clase Principal: `Nave`
* **Atributos Privados (`private:`):** `int x, y` (coordenadas de la nave en consola) e `int vidas` (cantidad de vidas restantes), encapsulados para evitar modificaciones externas directas (Stroustrup, 2013).
* **Constructor y Métodos Públicos (`public:`):** `Nave(int _x, int _y, int _vidas)` inicializa el estado; `getX()`, `getY()` y `getVidas()` consultan los atributos; `reducirVida()` decrementa `vidas`; `pintar()` y `borrar()` dibujan o limpian el sprite ASCII de tres filas; `mover(char tecla)` valida los límites de pantalla antes de actualizar `x` o `y`.

### Clases Secundarias: `Asteroide` y `Bala`
* **`Asteroide`:** Encapsula coordenadas `x, y` con métodos `pintar()`, `borrar()` y `mover()`, reiniciando su posición superior aleatoria al superar el límite inferior (`y > 23`).
* **`Bala`:** Encapsula coordenadas `x, y` con `mover()` (desplazamiento ascendente `y--`) y `fueraDeRango()` para detectar cuándo sale del área de juego (Kernighan & Ritchie, 1988).

### Bucle Principal y Detección de Colisiones (`main()`)
* **Mecánica:** Solicita `nombrePiloto` para el HUD, instancia `Nave jugador(35, 20, 3)` y colecciones dinámicas `vector<Asteroide*>` y `vector<Bala*>`. En cada iteración de `while (!gameOver)` lee entradas con `_kbhit()` y `tolower(_getch())`, actualiza proyectiles y asteroides, evalúa colisiones asteroide-jugador y bala-asteroide, libera memoria dinámica con `delete` y pausa con `Sleep(30)`.

---

## 3. INSTRUCCIONES DE COMPILACIÓN, DEPURACIÓN Y SINCRONIZACIÓN GIT

### Compilación y Ejecución desde PowerShell

```powershell
# 1. Compilación limpia habilitando estándar C++11
g++ -std=c++11 src/main.cpp -o src/juegodenaves.exe

# 2. Ejecución directa del binario resultante
.\src\juegodenaves.exe
```

### Sincronización Dual-Remote (GitHub + GitLab)

```bash
git add .
git commit -m "feat(act08): implementa motor de juego de naves con class Nave v1.0.0"
git push origin main
git push gitlab main
```

### Diagnóstico de Errores Frecuentes

1. **Error: `windows.h` o `conio.h` no encontrados en compiladores no Windows.**
   * **Causa:** Estas cabeceras pertenecen a la API de consola de Windows / MinGW.
   * **Solución:** Compilar en Windows 10/11 utilizando MinGW-w64 (`g++`) con estándar `-std=c++11`.

2. **Fugas de memoria o referencias inválidas al destruir balas o asteroides.**
   * **Causa:** Eliminación de punteros en vectores dinámicos sin liberar la memoria asignada con `new`.
   * **Solución:** Invocar `delete` sobre el puntero antes de llamar a `erase()` sobre el `vector` correspondiente.

---

## 4. REFERENCIAS

* Kernighan, B. W., & Ritchie, D. M. (1988). *El lenguaje de programación C* (2.ª ed.). Prentice Hall.
* Stroustrup, B. (2013). *The C++ programming language* (4th ed.). Addison-Wesley.