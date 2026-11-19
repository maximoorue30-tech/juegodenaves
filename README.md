# Juego de Naves en Consola (`class Nave`) — Actividad 8

* **Materia:** Laboratorio de Programación (LPR) — 5° Año 3° Grupos A-B
* **Institución:** E.E.S.T. N.° 1 "Eduardo Ader" — Vicente López
* **Docente:** Prof. Mansilla Muñoz York Elías
* **Integrante / Grupo:** [Nombre y Apellido] — Grupo 03
* **Versión:** `v1.0.0`

## Descripción del Proyecto
Simulador de combate espacial en consola desarrollado en C++ aplicando Programación Orientada a Objetos (POO), encapsulamiento de atributos (`private:`) y métodos (`public:`), manejo de colecciones dinámicas (`std::vector`) y detección de colisiones entre la nave, asteroides y proyectiles.

## Estructura del Repositorio
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

## Compilación y Ejecución
```powershell
g++ -std=c++11 src/main.cpp -o src/juegodenaves.exe
.\src\juegodenaves.exe
```
