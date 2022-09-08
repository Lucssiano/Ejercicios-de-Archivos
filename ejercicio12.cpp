/* 12) El dueño de un local de venta de juegos para distintas consolas necesita desarrollar un algoritmo que grabe un archivo,
JuegosPorConsola.dat, ordenado por consola, con un solo registro por consola según el siguiente diseño:
a) Consola (10 caracteres) b) Cantidad de juegos
Para obtener la información solicitada se cuenta con el archivo Juegos.dat, ordenado por consola, con un registro por
cada juego que se encuentra en el local, con el siguiente diseño:

1) Código del juego       2) Titulo del Juego (30 caracteres)
3) Stock en el local      4) Consola (10 caracteres)

*/

#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

struct Juegos
{
  int cod, stock;
  char titulo[30], consola[10];
};

struct JuegosxConsola
{
  int cantJuegos;
  char consola[10];
};

void generarArchivoDeJuegos(FILE *a);
void mostrarArchivoActualizado(FILE *a);

int main()
{
  FILE *archJxConsola, *archJuegos;

  // generarArchivoDeJuegos(archJuegos);

  Juegos juego;
  JuegosxConsola cons;

  archJuegos = fopen("Juegos.dat", "rb");
  archJxConsola = fopen("JuegosPorConsola.dat", "wb");

  if (archJuegos == NULL || archJxConsola == NULL)
    cout << "ERROR" << endl;
  else
  {
    int contador;
    fread(&juego, sizeof(Juegos), 1, archJuegos);
    char nomConsola[10];
    strcpy(nomConsola, juego.consola);
    strcpy(cons.consola, nomConsola);
    while (!feof(archJuegos))
    {
      contador = 0;
      do
      {
        contador++;
        fread(&juego, sizeof(Juegos), 1, archJuegos);
        if (nomConsola == juego.consola)
          cout << "son iguales" << endl;
      } while (!feof(archJuegos) && nomConsola == juego.consola);
      cout << juego.consola << " juego.consola" << endl;
      cout << nomConsola << " nomConsola" << endl;
      cout << endl;
      // cout << contador << " contador" << endl;
      cons.cantJuegos = contador;
      fwrite(&cons, sizeof(JuegosxConsola), 1, archJxConsola);
      strcpy(nomConsola, juego.consola);
      strcpy(cons.consola, nomConsola);
    }
    fclose(archJuegos);
    fclose(archJxConsola);
    mostrarArchivoActualizado(archJxConsola);
  }
  return 0;
}

void generarArchivoDeJuegos(FILE *a)
{
  a = fopen("Juegos.dat", "wb");
  if (a == NULL)
    cout << "ERROR" << endl;
  else
  {
    Juegos juego;

    cout << "CREANDO ARCHIVO Juegos.DAT" << endl;

    cout << "Codigo de juego (0 para finalizar) ";
    cin >> juego.cod;

    while (juego.cod != 0)
    {
      cout << "Titulo: ";
      fflush(stdin);
      cin.getline(juego.titulo, 30);

      cout << "Consola: ";
      fflush(stdin);
      cin.getline(juego.consola, 10);

      cout << "Stock: ";
      cin >> juego.stock;

      fwrite(&juego, sizeof(Juegos), 1, a);

      cout << "Codigo de juego (0 para finalizar) ";
      cin >> juego.cod;
    }
    fclose(a);
  }
}

void mostrarArchivoActualizado(FILE *a)
{
  a = fopen("JuegosPorConsola.dat", "rb");
  if (a == NULL)
    cout << "ERROR" << endl;
  else
  {
    JuegosxConsola cons;

    cout << "Leyendo archivo de JuegosPorConsola.DAT" << endl;

    fread(&cons, sizeof(JuegosxConsola), 1, a);
    while (!feof(a))
    {
      cout << endl;
      cout << "Consola: " << cons.consola << "    "
           << "Cantidad de Juegos: " << cons.cantJuegos << endl;
      fread(&cons, sizeof(JuegosxConsola), 1, a);
    }
  }
  fclose(a);
}
