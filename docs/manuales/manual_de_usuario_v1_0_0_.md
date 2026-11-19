# GUÍA DE USUARIO Y OPERACIÓN DEL SISTEMA

* **Proyecto:** Juego de Naves en Consola en C++ — Programación Orientada a Objetos (`class Nave`)
* **Institución:** E.E.S.T. N.° 1 "Eduardo Ader" — Vicente López
* **Asignatura:** Laboratorio de Programación (LPR) — 5° Año 3° Grupos A-B
* **Docente:** Prof. Mansilla Muñoz York Elías
* **Autor / Grupo:** [Apellido y Nombre / Grupo 03]
* **Versión:** v1.0.0 | **Fecha:** 21 de octubre de 2026

---

## CONTROL DE VERSIONES

| Versión | Fecha | Descripción |
| :--- | :--- | :--- |
| **v1.0.0** | 21/10/2026 | Emisión de la guía inicial del usuario para el simulador de combate espacial en consola (`juegodenaves`). |

---

## 1. REQUISITOS MÍNIMOS DEL SISTEMA

* **Sistema Operativo:** Windows 10 o Windows 11 (64-bit), requerido por las librerías de consola `<windows.h>` y `<conio.h>`.
* **Consola de Comandos:** Windows PowerShell o Símbolo del sistema (CMD).
* **Memoria RAM:** 512 MB libres.
* **Almacenamiento:** 10 MB de espacio disponible en disco.

---

## 2. GUÍA PASO A PASO DE EJECUCIÓN

### Paso 1: Apertura de la Terminal
Abra la carpeta raíz del proyecto `juegodenaves` en el Explorador de Archivos de Windows, presione la tecla **Shift** y haga clic derecho en un área vacía. Seleccione *"Abrir la ventana de PowerShell aquí"*.

### Paso 2: Invocación del Ejecutable
En la línea de comandos de PowerShell, ingrese la ruta del binario compilado y presione **Enter**:

```powershell
.\src\juegodenaves.exe
```

### Paso 3: Registro de Piloto y Controles de Juego
Al iniciar, el sistema solicita el **Nombre y Apellido** del piloto (que se mostrará en el HUD superior para la evidencia de captura). Luego limpia la pantalla, oculta el cursor y habilita los siguientes controles en tiempo real:

* **Desplazamiento de la nave:** Teclas `W` (arriba), `S` (abajo), `A` (izquierda) y `D` (derecha).
* **Disparo de proyectiles:** Barra espaciadora (`ESPACIO`) para emitir disparos verticales (`|`) hacia los asteroides (`O`).

### Paso 4: Interpretación de los Resultados
Durante la partida, la parte superior de la consola muestra el nombre del piloto y la cantidad de vidas restantes de la nave. Al llegar las vidas a cero, se limpia la pantalla y se exhibe el mensaje de finalización (Microsoft Corporation, 2026).

#### Figura 1
*Salida en consola del simulador de combate espacial con HUD de piloto y vidas*

```text
PILOTO: [Nombre y Apellido]
VIDAS: 3

        O                  O
                 O
                          |
              ^
             (0)
            ^^^^
```

> *Nota.* La salida ilustra el estado activo del combate en consola con el indicador del piloto, las vidas disponibles, los proyectiles disparados y los asteroides en descenso.

---

## 3. RESOLUCIÓN DE PROBLEMAS FRECUENTES (FAQ)

1. **La ventana de la consola se abre y se cierra instantáneamente.**
   * **Causa:** El archivo ejecutable se abrió haciendo doble clic desde el Explorador de Windows en lugar de invocarse desde una sesión de PowerShell activa.
   * **Solución:** Abra una ventana de PowerShell en la carpeta `juegodenaves` y ejecute `.\src\juegodenaves.exe`.

2. **Windows Defender o SmartScreen bloquea la ejecución.**
   * **Causa:** El ejecutable compilado localmente con `g++` no cuenta con firma digital comercial.
   * **Solución:** En la ventana de SmartScreen, seleccione *"Más información"* y luego pulse *"Ejecutar de todas formas"*.

3. **Las teclas de movimiento no responden con mayúsculas activadas (Bloq Mayús).**
   * **Causa:** El teclado envía caracteres en mayúscula si el Bloqueo de Mayúsculas está activo.
   * **Solución:** El programa convierte automáticamente las teclas mediante `tolower(_getch())`; procure mantener desactivado Bloq Mayús para mayor comodidad en el juego.

---

## 4. REFERENCIAS

* Microsoft Corporation. (2026). *Documentación de Windows PowerShell*. https://learn.microsoft.com/powershell/