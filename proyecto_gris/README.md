# Proyecto de Conversión a Escala de Grises con OpenMP

Este proyecto utiliza OpenMP para realizar la conversión de imágenes a escala de grises de forma eficiente. Se basa en OpenCV para el procesamiento de imágenes y OpenMP para la paralelización.

## Requisitos

- **Compilador:** Se requiere un compilador que admita C++11 y OpenMP. Se recomienda g++.
- **OpenCV:** Asegúrate de tener instalada la librería OpenCV (versión 4.x).
- **OpenMP:** Debería estar disponible en la mayoría de los compiladores.

## Compilación

Para compilar el programa, utiliza el siguiente comando:

```bash
make -f Makefile_openmp
esto generará el ejecutable 'grayscale_openmp'
El programa acepta el siguiente formato:
./grayscale_openmp <imagen_entrada> <imagen_salida>
ejemplo:
./grayscale_openmp chems.png imagen_gris_openmp.jpg

