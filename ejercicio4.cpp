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

#include <iostream>

using namespace std;

int main()
{
  return 0;
}