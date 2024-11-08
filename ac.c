#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define MOUSE5 0x06 // Superior
#define MOUSE4 0x05 // Inferior
#define TOGGLE_KEY VK_F6

// Estado do toggle
volatile int is_toggle = 1;

// Thread para alternar o estado do auto clicker
DWORD WINAPI ToggleThread() {
    while (1) {
        if (GetAsyncKeyState(TOGGLE_KEY) & 0x8000) {
            // Alterna o estado.
            is_toggle = !is_toggle;

            puts(is_toggle ? "on" : "off");

            // Aguarda a tecla ser solta
            while (GetAsyncKeyState(TOGGLE_KEY) & 0x8000)
                ;
            Sleep(100); // Delay para evitar toggle duplo
        }

        // Mudar depois?
        Sleep(10);
    }
    return 0;
}

int main() {
    srand(time(NULL));
    int randomizer = 0;
    // Intervalo entre cliques
    int left_interval_ms = 50;
    int right_interval_ms = 35;
    // Variacao maxima
    int left_max_var = 5;
    int right_max_var = 15;

    // Cria a thread que ira assistir a tecla toggle
    HANDLE hThread = CreateThread(NULL, 0, ToggleThread, NULL, 0, NULL);
    if (hThread == NULL) {
        puts("Erro ao criar a thread.");
        return 1;
    }

    puts("Mouse4 = Left Click\nMouse5 = Right Click\nF6 = Toggle");

    while (1) {
        if (is_toggle) {
            if (GetAsyncKeyState(MOUSE5) & 0x8000) {
                mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
                mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);

                randomizer = left_interval_ms +
                             (rand() % (2 * left_max_var + 1)) - left_max_var;
                Sleep(randomizer);
            }

            else if (GetAsyncKeyState(MOUSE4) & 0x8000) {
                mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
                mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);

                randomizer = right_interval_ms +
                             (rand() % (2 * right_max_var + 1)) - right_max_var;
                Sleep(randomizer);
            }

            // Mudar depois?
            Sleep(10);
        }
    }

    // Nao deve chegar aqui
    WaitForSingleObject(hThread, INFINITE);
    CloseHandle(hThread);
}
