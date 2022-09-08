/* 6) Se tiene el archivo “Escuelas.dat” con un registro con las escuelas de gestión estatal de un municipio de la provincia.
Cada registro tiene número de escuela, dirección y cantidad total de alumnos. El archivo está ordenado por número de
escuela. Hacer un programa que informe los datos de las escuelas que están entre dos números de escuela ingresados
por teclado. Informar también la cantidad de total de alumnos de las escuelas informadas. */

#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

struct Escuela
{
  int nroEscuela, cantAlumnos;
  char direccion[30];
};

void procesarDatosEscuela(FILE *aEscuelas);

int main()
{
  FILE *archivoDeEscuelas;

  archivoDeEscuelas = fopen("Escuelas.dat", "rb");

  procesarDatosEscuela(archivoDeEscuelas);

  return 0;
}

void procesarDatosEscuela(FILE *aEscuelas)
{
  // Hacer un programa que informe los datos de las escuelas que están entre dos números de escuela ingresados
  // por teclado. Informar también la cantidad de total de alumnos de las escuelas informadas.
  if (aEscuelas == NULL)
  {
    cout << "ERROR" << endl;
  }
  else
  {
    Escuela esc;
    int nro1, nro2;

    cout << "Ingrese dos numeros de escuela: ";
    cin >> nro1 >> nro2; // 5 8

    do
    {
      fread(&esc, sizeof(Escuela), 1, aEscuelas);
    } while (esc.nroEscuela != nro1);

    do
    {
      cout << endl;
      cout << "Numero de escuela: " << esc.nroEscuela << endl;
      cout << "Cantidad de Alumnos: " << esc.cantAlumnos << endl;
      cout << "Direccion: " << esc.direccion << endl;
      cout << endl;
      fread(&esc, sizeof(Escuela), 1, aEscuelas);
    } while (esc.nroEscuela <= nro2);

    fclose(aEscuelas);
  }
}