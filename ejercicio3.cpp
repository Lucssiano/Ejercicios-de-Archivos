/* 3) Dado el archivo binario generado en el ejercicio 1, que contiene todas las inscripciones del día, y otro con el mismo
diseño que contiene las inscripciones anteriores (FINALES.DAT), desarrolle un programa que agregue al archivo de
inscripciones anteriores el contenido del archivo del día. */

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
  FILE *archivoDias, *archivoFinales;
  archivoDias = fopen("DIAFINALES.dat", "rb");
  archivoFinales = fopen("FINALES.dat", "ab");
  if (archivoDias == NULL && archivoFinales == NULL)
    cout << "ERROR" << endl;
  else
  {
    Inscripcion inscp;
    fread(&inscp, sizeof(Inscripcion), 1, archivoDias);
    while (!feof(archivoDias))
    {
      fwrite(&inscp, sizeof(Inscripcion), 1, archivoFinales);
      fread(&inscp, sizeof(Inscripcion), 1, archivoDias);
    }
    fclose(archivoDias);
    fclose(archivoFinales);
    mostrarArchivo(archivoFinales);
  }
  return 0;
}

void mostrarArchivo(FILE *archivo)
{
  archivo = fopen("Finales.dat", "rb");
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