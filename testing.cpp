#include <iostream>
#include <bitset>

void iterateBits(unsigned short int code) {
    // Iterar de 15 a 0 para examinar todos los bits del unsigned short int (16 bits)
    for (int i = 15; i > 0; --i) {
        // Usar un desplazamiento y una máscara para comprobar el valor del bit en la posición i
        unsigned short int mask = 1 << i;
        bool bitValue = (code & mask) != 0; // bitValue será true si el bit en la posición i es 1

        // Imprimir el valor del bit
        std::cout << "Bit " << i << ": " << bitValue << "\n";
    }
}

int main() {
    unsigned short int code = 0b0011000000001000; // Ejemplo de código
    std::cout << "Iterando a través de los bits del código: " << std::bitset<16>(code) << "\n";
    iterateBits(code);

    return 0;
}