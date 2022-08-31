/* Apareo, Corte de Control, y altas, bajas y modificaciones en archivos binarios */

/* 8) Se dispone un archivo binario de inscripción de alumnos a exámenes finales MAESTROFINALES.DAT y otro con las
inscripciones del día de hoy DIAFINALES.DAT, ambos ordenados ascendente por número de legajo y código materia
y con el siguiente diseño:
a.1Nro de legajo  a.2 Código de materia   a.3 ApellidoNombre
Se pide desarrollar un programa que genere un nuevo archivo de inscripciones a finales FINALESACT.DAT
resultante del apareo de los dos archivos anteriores, con el mismo orden y diseño */

#include <iostream>

using namespace std;

// void generarArchivos();
void mostrarArchivo(FILE *archivo1, FILE *archivo2);
void mostrarArchFinalesActu(FILE *archActu);
void apareo(FILE *a1, FILE *a2);

struct Inscripcion
{
  int leg, codMat;
  // char nombreYApellido[36];
};

int main()
{
  // generarArchivos();

  FILE *archMaestroFinales = fopen("MAESTROFINALES.dat", "rb");
  FILE *archDiaFinales = fopen("DIAFINALES.dat", "rb");

  apareo(archMaestroFinales, archDiaFinales);

  fclose(archMaestroFinales);
  fclose(archDiaFinales);

  return 0;
}

void apareo(FILE *a1, FILE *a2)
{
  FILE *aFinalesAct;
  aFinalesAct = fopen("FINALESACT.dat", "wb");
  if (aFinalesAct == NULL)
    cout << "ERROR" << endl;
  else
  {
    Inscripcion mFinales, diaFinales;
    fread(&mFinales, sizeof(Inscripcion), 1, a1);
    fread(&diaFinales, sizeof(Inscripcion), 1, a2);
    while (!feof(a1) && !feof(a2))
    {
      if (mFinales.leg == diaFinales.leg)
      {
        if (mFinales.codMat < diaFinales.codMat)
        {
          fwrite(&mFinales, sizeof(Inscripcion), 1, aFinalesAct);
          fread(&mFinales, sizeof(Inscripcion), 1, a1);
        }
        else
        {
          fwrite(&diaFinales, sizeof(Inscripcion), 1, aFinalesAct);
          fread(&diaFinales, sizeof(Inscripcion), 1, a2);
        }
      }
      else
      {
        if (mFinales.leg < diaFinales.leg)
        {
          fwrite(&mFinales, sizeof(Inscripcion), 1, aFinalesAct);
          fread(&mFinales, sizeof(Inscripcion), 1, a1);
        }
        else
        {
          fwrite(&diaFinales, sizeof(Inscripcion), 1, aFinalesAct);
          fread(&diaFinales, sizeof(Inscripcion), 1, a2);
        }
      }
    }

    while (!feof(a1))
    {
      fwrite(&mFinales, sizeof(Inscripcion), 1, aFinalesAct);
      fread(&mFinales, sizeof(Inscripcion), 1, a1);
    }
    while (!feof(a2))
    {
      fwrite(&diaFinales, sizeof(Inscripcion), 1, aFinalesAct);
      fread(&diaFinales, sizeof(Inscripcion), 1, a2);
    }
  }
  fclose(aFinalesAct);
  mostrarArchFinalesActu(aFinalesAct);
}

void generarArchivos()
{
  FILE *archMFinales, *archDFinales;
  archMFinales = fopen("MAESTROFINALES.dat", "wb");
  archDFinales = fopen("DIAFINALES.dat", "wb");
  if (archMFinales == NULL || archDFinales == NULL)
    cout << "ERROR" << endl;
  else
  {
    Inscripcion inscpM, inscpD;

    cout << "CREANDO ARCHIVO MAESTROFINALES.DAT" << endl;

    cout << "Ingrese legajo (0 para finalizar) ";
    cin >> inscpM.leg;

    while (inscpM.leg != 0)
    {
      // cout << "Nombre y Apellido: ";
      // fflush(stdin);
      // cin.getline(inscpM.nombreYApellido, 36);
      cout << "Codigo de la materia: ";
      cin >> inscpM.codMat;
      fwrite(&inscpM, sizeof(Inscripcion), 1, archMFinales);
      cout << "Ingrese legajo (0 para finalizar) ";
      cin >> inscpM.leg;
    }
    fclose(archMFinales);

    cout << "CREANDO ARCHIVO DIAFINALES.DAT" << endl;

    cout << "Ingrese legajo (0 para finalizar) ";
    cin >> inscpD.leg;
    while (inscpD.leg != 0)
    {
      // cout << "Nombre y Apellido: ";
      // fflush(stdin);
      // cin.getline(inscpD.nombreYApellido, 36);
      cout << "Codigo de la materia: ";
      cin >> inscpD.codMat;
      fwrite(&inscpD, sizeof(Inscripcion), 1, archDFinales);
      cout << "Ingrese legajo (0 para finalizar) ";
      cin >> inscpD.leg;
    }
    fclose(archDFinales);

    // mostrarArchivo(archMFinales, archDFinales);
  }
}

void mostrarArchivo(FILE *archivo1, FILE *archivo2)
{
  archivo1 = fopen("MAESTROFINALES.dat", "rb");
  archivo2 = fopen("DIAFINALES.dat", "rb");
  if (archivo1 == NULL || archivo2 == NULL)
    cout << "ERROR" << endl;
  else
  {
    Inscripcion inscpM, inscpD;

    cout << "ARCHIVO MAESTROFINALES.DAT" << endl;

    fread(&inscpM, sizeof(Inscripcion), 1, archivo1);
    while (!feof(archivo1))
    {
      cout << endl;
      cout << "a.1 " << inscpM.leg << "    "
           << "a.2 " << inscpM.codMat << endl;
      // cout << "a.3 " << inscpM.nombreYApellido << endl;
      fread(&inscpM, sizeof(Inscripcion), 1, archivo1);
    }
    fclose(archivo1);

    cout << "ARCHIVO DIAFINALES.DAT" << endl;

    fread(&inscpD, sizeof(Inscripcion), 1, archivo2);
    while (!feof(archivo2))
    {
      cout << endl;
      cout << "a.1 " << inscpD.leg << "    "
           << "a.2 " << inscpD.codMat << endl;
      // cout << "a.3 " << inscpD.nombreYApellido << endl;
      fread(&inscpD, sizeof(Inscripcion), 1, archivo2);
    }
    fclose(archivo2);
  }
}

void mostrarArchFinalesActu(FILE *archActu)
{
  archActu = fopen("FINALESACT.dat", "rb");
  if (archActu == NULL)
    cout << "ERROR" << endl;
  else
  {
    Inscripcion inscp;

    cout << "ARCHIVO FINALESACT.DAT" << endl;

    fread(&inscp, sizeof(Inscripcion), 1, archActu);
    while (!feof(archActu))
    {
      cout << endl;
      cout << "a.1 " << inscp.leg << "    "
           << "a.2 " << inscp.codMat << endl;
      // cout << "a.3 " << inscp.nombreYApellido << endl;
      fread(&inscp, sizeof(Inscripcion), 1, archActu);
    }
    fclose(archActu);
  }
}
