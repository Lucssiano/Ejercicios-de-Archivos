/* 13) Dado el archivo ‘ALUMNOS.dat’ con los datos personales de alumnos ordenado por legajo, con el siguiente diseño:

a.1 Legajo                        a.2 Apellido y nombre ( 30 caracteres)
a.3 Domicilio (20 caracteres)     a.4 Código postal
a.5 Teléfono (10 caracteres)      a.6 Año de ingreso

Y otro archivo con el mismo orden que el mencionado llamado “NOVEDADES.dat”, con las actualizaciones (altas,
bajas, y modificaciones) a ser aplicadas, donde cada registro contiene además de todos los campos de Alumnos.dat un
código de operación (‘A’: Alta, ‘B’: Baja, ‘M’: Modificación).

Se pide desarrollar todos los pasos necesarios para realizar un programa que genere un archivo actualizado
“ALUMACTU.dat” con el mismo diseño.  */

#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

void generarArchivoAlumnos(FILE *archNov);
void mostrarAlumnos(FILE *archAlum);
void generarArchivoNovedades(FILE *archNov);
void mostrarNovedades(FILE *archNov);
void generarArchivoActualizado(FILE *archAlum, FILE *archNov, FILE *archActu);
void mostrarActualizado(FILE *archActu);

struct DatosAlumnos
{
  char nombreYApellido[30], domicilio[20], telefono[10];
  int leg, codPostal, añoDeIngreso;
};

struct Novedades
{
  char nombreYApellido[30], domicilio[20], telefono[10], codOperacion[2];
  int leg, codPostal, añoDeIngreso;
};

int main()
{
  FILE *archAlumnos, *archAlumAct, *archNovedades;

  // generarArchivoAlumnos(archAlumnos);
  // generarArchivoNovedades(archNovedades);

  // generarArchivoActualizado(archAlumnos, archNovedades, archAlumAct);
  return 0;
}

// Se pide desarrollar todos los pasos necesarios para realizar un programa que genere un archivo actualizado
// “ALUMACTU.dat” con el mismo diseño.
void generarArchivoActualizado(FILE *archAlum, FILE *archNov, FILE *archActu)
{
  archActu = fopen("ALUMACTU.dat", "wb");
  archAlum = fopen("ALUMNOS.dat", "rb");
  archNov = fopen("NOVEDADES.dat", "rb");
  if (archActu == NULL || archAlum == NULL || archAlum == NULL)
    cout << "ERROR" << endl;
  else
  {
    DatosAlumnos alum;
    Novedades nov;
    fread(&alum, sizeof(DatosAlumnos), 1, archAlum);
    fread(&nov, sizeof(Novedades), 1, archNov);
    while (!feof(archAlum) && !feof(archNov))
    {
      if (alum.leg < nov.leg)
      {
        fwrite(&alum, sizeof(DatosAlumnos), 1, archActu);
        fread(&alum, sizeof(DatosAlumnos), 1, archAlum);
      }
      else
      {
        if (alum.leg == nov.leg)
        {
          if (nov.codOperacion == "B")
          {
            fread(&alum, sizeof(DatosAlumnos), 1, archAlum);
            fread(&nov, sizeof(Novedades), 1, archNov);
          }
          else
          {
            fwrite(&nov, sizeof(Novedades), 1, archActu); // Cómo le saco la M?
            fread(&alum, sizeof(DatosAlumnos), 1, archAlum);
            fread(&nov, sizeof(Novedades), 1, archNov);
          }
        }
        else
        {
          fwrite(&nov, sizeof(Novedades), 1, archActu); // Cómo le saco la A?
          fread(&nov, sizeof(Novedades), 1, archNov);
        }
      }
    }

    while (!feof(archAlum))
    {
      fwrite(&alum, sizeof(DatosAlumnos), 1, archActu);
    }

    while (!feof(archNov))
    {
      fwrite(&nov, sizeof(Novedades), 1, archActu);
    }

    fclose(archActu);
    mostrarActualizado(archActu);
  }
}

void mostrarActualizado(FILE *archActu)
{
  archActu = fopen("ALUMACTU.dat", "rb");
  if (archActu == NULL)
    cout << "ERROR" << endl;
  else
  {
    DatosAlumnos alum;
    fread(&alum, sizeof(DatosAlumnos), 1, archActu);
    while (!feof(archActu))
    {
      cout << endl;
      cout << "ARCH ACTU" << endl;
      cout << "a.1 " << alum.leg << "    "
           << "a.2 " << alum.nombreYApellido << endl;
      cout << "a.3 " << alum.domicilio << "    "
           << "a.4 " << alum.codPostal << endl;
      cout << "a.5 " << alum.telefono << "    "
           << "a.6 " << alum.añoDeIngreso << endl;
      fread(&alum, sizeof(DatosAlumnos), 1, archActu);
    }
    fclose(archActu);
  }
}

void generarArchivoAlumnos(FILE *archAlum)
{
  archAlum = fopen("ALUMNOS.dat", "wb");
  if (archAlum == NULL)
    cout << "ERROR" << endl;
  else
  {
    DatosAlumnos alumno;
    int i = 1;
    while (i <= 20)
    {
      alumno.leg = i;
      alumno.añoDeIngreso = 1999 + i;
      strcpy(alumno.domicilio, "Jarana 222");
      alumno.codPostal = 99 + i;
      strcpy(alumno.nombreYApellido, "Lucho Riente");
      strcpy(alumno.telefono, "234643234");
      fwrite(&alumno, sizeof(DatosAlumnos), 1, archAlum);
      i++;
    }
    fclose(archAlum);
    // mostrarAlumnos(archAlum);
  }
}

void generarArchivoNovedades(FILE *archNov)
{
  archNov = fopen("NOVEDADES.dat", "wb");
  if (archNov == NULL)
    cout << "ERROR" << endl;
  else
  {
    Novedades nov;
    int i = 1;
    while (i <= 10)
    {
      nov.leg = i;
      nov.añoDeIngreso = 1999 + i;
      strcpy(nov.domicilio, "Jarana 222");
      nov.codPostal = 99 + i;
      strcpy(nov.nombreYApellido, "Lucho Riente");
      strcpy(nov.telefono, "234643234");
      char cod[2];
      switch (i)
      {
      case 1:
        strcpy(cod, "A");
        break;
      case 2:
        strcpy(cod, "B");
        break;
      case 3:
        strcpy(cod, "M");
        break;
      case 4:
        strcpy(cod, "M");
        break;
      case 5:
        strcpy(cod, "M");
        break;
      case 6:
        strcpy(cod, "B");
        break;
      case 7:
        strcpy(cod, "A");
        break;
      case 8:
        strcpy(cod, "B");
        break;
      case 9:
        strcpy(cod, "B");
        break;
      case 10:
        strcpy(cod, "B");
        break;
      }
      strcpy(nov.codOperacion, cod);
      fwrite(&nov, sizeof(Novedades), 1, archNov);
      i++;
    }
    fclose(archNov);
    // mostrarNovedades(archNov);
  }
}

void mostrarAlumnos(FILE *archAlum)
{
  archAlum = fopen("ALUMNOS.dat", "rb");
  if (archAlum == NULL)
    cout << "ERROR" << endl;
  else
  {
    DatosAlumnos alum;
    fread(&alum, sizeof(DatosAlumnos), 1, archAlum);
    while (!feof(archAlum))
    {
      cout << endl;
      cout << "ALUMNOS" << endl;
      cout << "a.1 " << alum.leg << "    "
           << "a.2 " << alum.nombreYApellido << endl;
      cout << "a.3 " << alum.domicilio << "    "
           << "a.4 " << alum.codPostal << endl;
      cout << "a.5 " << alum.telefono << "    "
           << "a.6 " << alum.añoDeIngreso << endl;
      fread(&alum, sizeof(DatosAlumnos), 1, archAlum);
    }
    fclose(archAlum);
  }
}

void mostrarNovedades(FILE *archNov)
{
  archNov = fopen("NOVEDADES.dat", "rb");
  if (archNov == NULL)
    cout << "ERROR" << endl;
  else
  {
    Novedades nov;
    fread(&nov, sizeof(Novedades), 1, archNov);
    while (!feof(archNov))
    {
      cout << endl;
      cout << "NOVEDADES" << endl;
      cout << "a.1 " << nov.leg << "    "
           << "a.2 " << nov.nombreYApellido << endl;
      cout << "a.3 " << nov.domicilio << "    "
           << "a.4 " << nov.codPostal << endl;
      cout << "a.5 " << nov.telefono << "    "
           << "a.6 " << nov.añoDeIngreso << endl;
      cout << "a.7 " << nov.codOperacion << endl;
      fread(&nov, sizeof(Novedades), 1, archNov);
    }
    fclose(archNov);
  }
}