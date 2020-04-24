#include "dados.h"
#include "interface.h"

int main() {
    ESTADO *e = inicializar_estado();
    while(interpretador(e));
    return 0;
}