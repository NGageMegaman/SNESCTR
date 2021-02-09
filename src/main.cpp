#include "cpu.h"
using namespace std;

int main() {
    CPU *cpu = CPU::getInstance();
    while (1) {
        cpu->executeInstruction();
    }
}