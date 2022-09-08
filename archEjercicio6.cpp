
#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

struct Escuela
{
  int nroEscuela, cantAlumnos;
  char direccion[30];
};

void generarArchivoEscuelas(FILE *aEscuelas);
void mostrarArchivoEscuelas(FILE *aEscuelas);

int main()
{
  FILE *archivoDeEscuelas;

  // generarArchivoEscuelas(archivoDeEscuelas);
  mostrarArchivoEscuelas(archivoDeEscuelas);

  return 0;
}

void generarArchivoEscuelas(FILE *aEscuelas)
{
  aEscuelas = fopen("Escuelas.dat", "wb");
  if (aEscuelas == NULL)
    cout << "ERROR" << endl;
  else
  {
    Escuela esc;
    int i = 1;
    while (i <= 6)
    {
      esc.cantAlumnos = i + 20;
      esc.nroEscuela = i + 1;
      strcpy(esc.direccion, "Alvarez Jonte 4295");
      fwrite(&esc, sizeof(Escuela), 1, aEscuelas);
      i++;
    }
    fclose(aEscuelas);
  }
}

void mostrarArchivoEscuelas(FILE *aEscuelas)
{
  aEscuelas = fopen("Escuelas.dat", "rb");
  if (aEscuelas == NULL)
    cout << "ERROR" << endl;
  else
  {
    Escuela esc;
    fread(&esc, sizeof(Escuela), 1, aEscuelas);
    while (!feof(aEscuelas))
    {
      cout << endl;
      cout << "Escuelas" << endl;
      cout << "Cantidad de alumnos: " << esc.cantAlumnos << "    "
           << "Numero de escuela: " << esc.nroEscuela << endl;
      cout << "Direccion: " << esc.direccion << "    ";
      cout << endl;
      fread(&esc, sizeof(Escuela), 1, aEscuelas);
    }
    fclose(aEscuelas);
  }
}