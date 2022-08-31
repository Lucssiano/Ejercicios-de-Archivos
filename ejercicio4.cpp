/* 4) Dado un archivo binario de productos que contiene 100 registros, y cada registro corresponde a un producto que está
codificado del 1 a 100, ordenado por código de producto con el siguiente diseño:
código de producto (1..100) stock

y otro archivo binario de pedidos, con el siguiente diseño:
número de pedido número de cliente
código de producto (1..100) cantidad pedida

Se pide desarrollar un algoritmo que:

a) Realice un listado con los pedidos que fueron satisfechos en su totalidad según el siguiente listado:

Pedidos Satisfechos
Número de pedido  Número de Cliente Código de Producto Cantidad pedida
9999                    999999            999              9999
9999                    999999            999              9999

b) actualizar el campo stock del archivo de producto, cada vez que acepte un pedido.

c) grabar un archivo binario con el mismo diseño que el archivo de pedidos, con aquellos pedidos que no
pueden ser satisfechos en su totalidad. */

/* FALTA AGREGAR LOS ARCHIVOS PARA COMPROBAR DE QUE FUNCIONA BIEN */

#include <iostream>
#include <stdio.h>

using namespace std;

struct Producto
{
  unsigned codProd;
  unsigned stock;
};

struct Pedido
{
  unsigned nroPed;
  unsigned nroCli;
  unsigned codProd;
  unsigned cantPedida;
};

void procesarPedidos(FILE *aPed, FILE *aProd, FILE *aPedNs);
void procesarUnPedido(Pedido ped, FILE *apr, FILE *ans);
void mostrarTitulos();
void mostrar(Pedido p);

int main()
{
  FILE *archProd, *archPed, *archPedNS;

  archProd = fopen("Productos.dat", "rb+");
  archPed = fopen("Pedidos.dat", "rb");
  archPedNS = fopen("PedidosNoSatisfechos.dat", "wb");

  procesarPedidos(archPed, archProd, archPedNS);

  fclose(archProd);
  fclose(archPed);
  fclose(archPedNS);
}

void procesarPedidos(FILE *aPed, FILE *aProd, FILE *aPedNs)
{
  Pedido pedido;
  mostrarTitulos();
  fread(&pedido, sizeof(Pedido), 1, aPed);
  while (!feof(aPed))
  {
    procesarUnPedido(pedido, aProd, aPedNs);
    fread(&pedido, sizeof(Pedido), 1, aPed);
  }
}

void procesarUnPedido(Pedido ped, FILE *aProd, FILE *aPedNs)
{
  Producto prod;
  fseek(aProd, (ped.codProd - 1) * sizeof(Producto), SEEK_SET);
  fread(&prod, sizeof(Producto), 1, aProd);
  if (ped.cantPedida <= prod.stock)
  {
    mostrar(ped);
    prod.stock -= ped.cantPedida;
    fseek(aProd, (ped.codProd - 1) * sizeof(Producto), SEEK_SET);
    fwrite(&prod, sizeof(Producto), 1, aProd);
  }
  else
    fwrite(&ped, sizeof(Pedido), 1, aPedNs);
}

void mostrarTitulos()
{
  cout << "Numero de pedido       "
       << "Número de Cliente        "
       << "Código de Producto        "
       << "Cantidad pedida       " << endl;
}

void mostrar(Pedido p)
{
  cout << p.nroPed << "        "
       << p.nroCli << "        "
       << p.codProd << "        "
       << p.cantPedida << endl;
}