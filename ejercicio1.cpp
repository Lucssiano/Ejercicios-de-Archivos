/* 1) Se dispone de un conjunto de inscripciones de alumnos a examen en el mes de mayo.
Cada inscripción tiene los siguientes datos: nombre y apellido, número de legajo, código de materia, día, mes y año del
examen. Los datos finalizan con un número de legajo igual a cero.
Desarrollar un programa que a partir del ingreso de las inscripciones por teclado, genere un archivo binario de
inscripción de alumnos a exámenes finales DIAFINALES.DAT, según el siguiente diseño:
a.1 Nro. de legajo    a.2 Código de materia
a.3 Día del examen    a.4 Mes del examen
a.5 Año del examen    a.6 Nombre-Apellido  */

#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

void mostrarArchivo(FILE *archivo);

struct Inscripcion
{
  char nombreYApellido[36];
  int legajo, codMateria, dia, mes, año;
};

int main()
{
  FILE *archFinales;
  archFinales = fopen("DIAFINALES.dat", "wb");
  if (archFinales == NULL)
    cout << "ERROR" << endl;
  else
  {
    Inscripcion inscp;
    string nombre, apellido, nombreConcatenado;
    cout << "Ingrese legajo (0 para finalizar) ";
    cin >> inscp.legajo;
    while (inscp.legajo != 0)
    {
      cout << "Nombre y Apellido: ";
      cin >> nombre >> apellido;
      nombreConcatenado = nombre + " " + apellido;
      strcpy(inscp.nombreYApellido, nombreConcatenado.c_str());
      cout << "Codigo de la materia: ";
      cin >> inscp.codMateria;
      cout << "Mes del examen: ";
      cin >> inscp.mes;
      cout << "Dia del examen: ";
      cin >> inscp.dia;
      cout << "Ano del examen: ";
      cin >> inscp.año;
      fwrite(&inscp, sizeof(Inscripcion), 1, archFinales);
      cout << "Ingrese legajo (0 para finalizar) ";
      cin >> inscp.legajo;
    }
    fclose(archFinales);
    mostrarArchivo(archFinales);
  }
  return 0;
}

void mostrarArchivo(FILE *archivo)
{
  archivo = fopen("DIAFINALES.dat", "rb");
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