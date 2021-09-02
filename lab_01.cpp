// lab_01.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <stdio.h>
#define WINVER 0x0A00
#include <windows.h>

#define BUFSIZE MAX_PATH
#define FILESYSNAMEBUFSIZE MAX_PATH
#define MAX_KEY_LENGTH 255

using namespace std;

#define INFO_BUFFER_SIZE 32767

//2. Измерение производительности ЦП
//Замер рабочей частоты f 
double PCFreq = 0.0;
__int64 CounterStart = 0;

void StartCounter()
{
    LARGE_INTEGER li;
    if (!QueryPerformanceFrequency(&li))
        cout << "Function QueryPerformanceFrequency() failed!\n";

    PCFreq = double(li.QuadPart);

    printf("\n2.1.  CPU frequency: %u  Hz\n", li);
    QueryPerformanceCounter(&li);
    CounterStart = li.QuadPart;
}

//Подсчет кол-ва тактов ЦП, которе занимает исполнение предыдущего пункта
double GetCounter()
{
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return double((li.QuadPart - CounterStart) * 1000000) / PCFreq;
}

int main()
{
    //пункт 1.1 
    DWORD dwVersion = 0;
    DWORD dwMajorVersion = 0;
    DWORD dwMinorVersion = 0;
    DWORD dwBuild = 0;

    dwVersion = GetVersion();

    // Get the Windows version.

    dwMajorVersion = (DWORD)(LOBYTE(LOWORD(dwVersion)));
    dwMinorVersion = (DWORD)(HIBYTE(LOWORD(dwVersion)));

    // Get the build number.

    if (dwVersion < 0x80000000)
        dwBuild = (DWORD)(HIWORD(dwVersion));

    printf("Version is %d.%d (%d)\n",
        dwMajorVersion,
        dwMinorVersion,
        dwBuild);

    //пункт 1.2 
    TCHAR szPath[_MAX_PATH] = { 0 };
    UINT iRet = GetSystemDirectory(szPath, _MAX_PATH);
    printf("Result function GetSystemDirectory %d\n", iRet);
    
    //пункт 1.3 
    char buffer[256];
    DWORD size = 256;
    GetComputerNameA(buffer, &size);
    printf("%s\n", buffer);

    GetUserNameA(buffer, &size);
    printf("%s\n", buffer);

    //пункт 1.4
    char buffer2[MAX_PATH + 1];
    DWORD size2 = MAX_PATH;
    char buffer3[MAX_PATH + 1];
    DWORD  CBufLen = MAX_PATH;
    __int64 total, available, free;

    HANDLE firstVolume =  FindFirstVolumeA(buffer2, size2);
    printf("\n      %s", buffer2);

    do {
        printf("\n%s", buffer2);
        CBufLen = MAX_PATH;
        GetVolumePathNamesForVolumeNameA(buffer2, buffer3, CBufLen, &CBufLen);
        char* path = buffer3;
        printf("\npath: %s", path);
        GetDiskFreeSpaceExA(buffer2, (PULARGE_INTEGER)&available, (PULARGE_INTEGER)&total, (PULARGE_INTEGER)&free);
        printf("\nsize: %I64d  bytes ", total);
        printf("\nFree space: %I64d  bytes\n", available);



    } while (FindNextVolumeA(firstVolume, buffer2, BUFSIZE));
    FindVolumeClose(firstVolume);

    
    /*
    //пункт 1.5
    DWORD dwSize;
    TCHAR szName[MAX_KEY_LENGTH];
    HKEY hKey;
    DWORD dwIndex = 0;
    DWORD retCode;
    DWORD BufferSize = 8192;
    PPERF_DATA_BLOCK PerfData = (PPERF_DATA_BLOCK)malloc(BufferSize);
    DWORD cbData = BufferSize;

    if (RegOpenKeyExA(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run",
        0, KEY_ALL_ACCESS, &hKey) == !ERROR_SUCCESS)
    {
        printf("Function RegOpenKeyEx() failed!\n");
    }
    else printf("\nStartup commands:\n");

    while (1) {
        dwSize = sizeof(szName);
        retCode = RegEnumValue(hKey, dwIndex, szName, &dwSize, NULL, NULL, NULL, NULL);

        if (retCode == ERROR_SUCCESS)
        {
            RegQueryValueEx(hKey, szName, NULL, NULL, (LPBYTE)PerfData, &cbData);
            printf("      %d: %s:  %s\n", dwIndex + 1, szName, PerfData);
            dwIndex++;
        }
        else break;
    }
    */

    //RegCloseKey(hKey);

    StartCounter();
    cout << "2.2.  CPU clock count: " << GetCounter() << "  us \n";
    return 0;


}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
