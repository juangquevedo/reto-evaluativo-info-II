#include <iostream>

using namespace std;

class producto
{
public:
    producto();
    void sacar_producto(int num);
    void ver_producto();
    unsigned int disponible=((unidades_p-1)*cantidad)+unidades_a;//esta variable es publica para que desde fuera se pueda saber si el combo se puede ofrecer en base a los productos del inventario
private:
    string nombre;
    int unidades_p;
    int unidades_a;
    int cantidad;
    int long long costo;
};
