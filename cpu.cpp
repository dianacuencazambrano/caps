#include <iostream>
#include <Windows.h>

int main() {
    // Obtiene el uso de la CPU para el proceso actual.
    double cpuUsage = 0.0;
    HANDLE hProcess = GetCurrentProcess();
    FILETIME ftCreation, ftExit, ftKernel, ftUser;

    if (GetProcessTimes(hProcess, &ftCreation, &ftExit, &ftKernel, &ftUser)) {
        ULARGE_INTEGER kernelTime, userTime;
        kernelTime.LowPart = ftKernel.dwLowDateTime;
        kernelTime.HighPart = ftKernel.dwHighDateTime;
        userTime.LowPart = ftUser.dwLowDateTime;
        userTime.HighPart = ftUser.dwHighDateTime;

        // Calcula el tiempo total de CPU utilizado.
        ULONGLONG totalTime = kernelTime.QuadPart + userTime.QuadPart;

        // Obtiene el tiempo de CPU del sistema.
        FILETIME ftIdle, ftKernelSystem, ftUserSystem;
        if (GetSystemTimes(&ftIdle, &ftKernelSystem, &ftUserSystem)) {
            ULARGE_INTEGER kernelSystemTime, userSystemTime;
            kernelSystemTime.LowPart = ftKernelSystem.dwLowDateTime;
            kernelSystemTime.HighPart = ftKernelSystem.dwHighDateTime;
            userSystemTime.LowPart = ftUserSystem.dwLowDateTime;
            userSystemTime.HighPart = ftUserSystem.dwHighDateTime;

            // Calcula el tiempo total de CPU del sistema.
            ULONGLONG totalSystemTime = kernelSystemTime.QuadPart + userSystemTime.QuadPart;

            // Calcula el uso de la CPU como porcentaje.
            if (totalSystemTime > 0) {
                cpuUsage = 100.0 * (totalTime / static_cast<double>(totalSystemTime));
            }
        }
    }

    std::cout << "Uso de CPU: " << cpuUsage << "%" << std::endl;

    return 0;
}
