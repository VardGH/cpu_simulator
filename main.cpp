#include "cpu.hpp"
#include <iostream>

int main() 
{
    CPU my_cpu;
    try {
        my_cpu.load_from_file("code.txt");

        my_cpu.execute();

        my_cpu.print_registers();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    
    return 0;
}