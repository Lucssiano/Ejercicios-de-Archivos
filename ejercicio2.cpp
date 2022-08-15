/* 2) Dado el archivo binario generado en el ejercicio 1, desarrolle un programa que solicitando por teclado un código de
materia permita seleccionar todos los registros de alumnos que se anotaron para rendirla y los grabe en otro archivo
(MATFINALES.DAT), con el mismo diseño. */

#include <iostream>

using namespace std;

void mostrarArchivo(FILE *archivo);

struct Inscripcion
{
  char nombreYApellido[36];
  int legajo, codMateria, dia, mes, año;
};

int main()
{
  FILE *archivoDias, *archivoMat;
  archivoDias = fopen("DIAFINALES.dat", "rb");
  archivoMat = fopen("MATFINALES.dat", "wb");
  if (archivoDias == NULL && archivoMat == NULL)
    cout << "ERROR" << endl;
  else
  {
    Inscripcion inscp;
    int codigoIngresado;

    cout << "Ingrese un codigo de materia: ";
    cin >> codigoIngresado;

    fread(&inscp, sizeof(Inscripcion), 1, archivoDias);
    while (!feof(archivoDias))
    {
      if (codigoIngresado == inscp.codMateria)
        fwrite(&inscp, sizeof(Inscripcion), 1, archivoMat);

      fread(&inscp, sizeof(Inscripcion), 1, archivoDias);
    }
    fclose(archivoDias);
    fclose(archivoMat);
    mostrarArchivo(archivoMat);
  }
  return 0;
}

void mostrarArchivo(FILE *archivo)
{
  archivo = fopen("MATFINALES.dat", "rb");
  if (archivo == NULL)
    cout << "ERROR" << endl;
  else
  {
    Inscripcion inscp;
    fread(&inscp, sizeof(Inscripcion), 1, archivo);
    while (!feof(archivo))
    {
      cout << endl;
      cout << "a.1 " << inscp.legajo << "    "
           << "a.2 " << inscp.codMateria << endl;
      cout << "a.3 " << inscp.dia << "    "
           << "a.4 " << inscp.mes << endl;
      cout << "a.5 " << inscp.año << "    "
           << "a.6 " << inscp.nombreYApellido << endl;
      fread(&inscp, sizeof(Inscripcion), 1, archivo);
    }
    fclose(archivo);
  }
}