#include <iostream>

using namespace std;
#include <fstream>
#include <math.h>
#include <map>
#include <list>
#include <ctime>

class producto
{
public:
    void crear(string name,int uni_p,int uni_a,int cant,int long long cost);
    void sacar_producto(int num);
    void ver_producto();
    void anadir_cant(int can);
    string guardado();
    unsigned int disponible;//esta variable es publica para que desde fuera se pueda saber si el combo se puede ofrecer en base a los productos del inventario
private:
    string nombre;
    int unidades_p; //esta variable corresponde a las unidades que contiene cada producto (por ejemplo, si el producto es un paquete de 12 jugos, esta vaiable es 12)
    int unidades_a; //esta variable corresponde a las unidades que tiene el paquete abierto por dar un ejemplo
    int cantidad;
    int long long costo;
    string int2str(int long a);
};
