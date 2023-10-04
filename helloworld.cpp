#include <iostream>
#include <Windows.h>

int main() {
    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);

    std::cout << "Número de núcleos de CPU: " << sysInfo.dwProcessorType << std::endl;

    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(memInfo);
    
    if (GlobalMemoryStatusEx(&memInfo)) {
        std::cout << "Memoria RAM total: " << (memInfo.ullTotalPhys / (1024 * 1024)) << " MB" << std::endl;
        std::cout << "Memoria RAM disponible: " << (memInfo.ullAvailPhys / (1024 * 1024)) << " MB" << std::endl;
    } else {
        std::cerr << "Error al obtener información de memoria." << std::endl;
    }

    return 0;
}
