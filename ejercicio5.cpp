/* 5) Se tiene el archivo “Medicamentos.dat” con un registro por cada medicamento existente en una farmacia. Cada
registro tiene código, nombre, stock y precio unitario. Hacer un programa que informe los medicamentos con stock
menor a 5 y el stock valorizado. */

#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

void generarArchivoMedicamentos();
void mostrarMedicamentos(FILE *aMeds);
void punto5();

struct Medicamentos
{
  int cod, stock, precUnitario;
  char nombre[36];
};

int main()
{
  generarArchivoMedicamentos();
  punto5();
  return 0;
}

void punto5()
{
  FILE *archMeds = fopen("MEDICAMENTOS.dat", "rb");
  if (archMeds == NULL)
    cout << "ERROR" << endl;
  else
  {
    Medicamentos med;
    fread(&med, sizeof(Medicamentos), 1, archMeds);
    while (!feof(archMeds))
    {
      if (med.stock < 5)
        cout << "Nombre: " << med.nombre << " Stock: " << med.stock << " Precio Unitario: " << med.precUnitario << endl;
      fread(&med, sizeof(Medicamentos), 1, archMeds);
    }
    fclose(archMeds);
  }
}

void generarArchivoMedicamentos()
{
  FILE *archMeds = fopen("MEDICAMENTOS.dat", "wb");
  if (archMeds == NULL)
    cout << "ERROR" << endl;
  else
  {
    Medicamentos med;
    int i = 1;
    while (i < 20)
    {
      strcpy(med.nombre, "ibuprofeno");
      med.cod = i + 1;
      med.stock = i + 1;
      med.precUnitario = i + 100;
      fwrite(&med, sizeof(Medicamentos), 1, archMeds);
      i++;
    }
    fclose(archMeds);
    // mostrarMedicamentos(archMeds);
  }
}

void mostrarMedicamentos(FILE *aMeds)
{
  aMeds = fopen("MEDICAMENTOS.dat", "rb");
  if (aMeds == NULL)
    cout << "ERROR" << endl;
  else
  {
    Medicamentos med;
    fread(&med, sizeof(Medicamentos), 1, aMeds);
    while (!feof(aMeds))
    {
      cout << endl;
      cout << "MEDICAMENTOS" << endl;
      cout << "Nombre: " << med.nombre << "    "
           << "Codigo: " << med.cod << endl;
      cout << "Precio Unitario: " << med.precUnitario << "    "
           << "Stock: " << med.stock << endl;
      fread(&med, sizeof(Medicamentos), 1, aMeds);
    }
    fclose(aMeds);
  }
}