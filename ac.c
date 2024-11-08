#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#include "config.h"

// Variavel global para alternar o estado entre thread e main
volatile int is_toggle = 1;

// Thread para alternar o estado do autoclicker
DWORD WINAPI ToggleThread() {
    while (1) {
        if (GetAsyncKeyState(TOGGLE_KEY) & 0x8000) {
            is_toggle = !is_toggle;  // Alterna o estado
            puts(is_toggle ? "on" : "off");

            // Aguarda a tecla ser solta
            while (GetAsyncKeyState(TOGGLE_KEY) & 0x8000)
                ;
            Sleep(100);  // Debounce
        }
        Sleep(10);  // Mudar depois?
    }
    return 0;
}

void print_config_keys() {
    printf("TOGGLE_KEY: 0x%x\n", TOGGLE_KEY);
    printf("LEFT_CLICK_KEY: 0x%x\n", LEFT_CLICK_KEY);
    printf("RIGHT_CLICK_KEY: 0x%x\n", RIGHT_CLICK_KEY);
}

int main() {
    srand(time(NULL));

    // Cria a thread para alternar o estado do autoclicker
    HANDLE hThread = CreateThread(NULL, 0, ToggleThread, NULL, 0, NULL);
    if (hThread == NULL) {
        puts("Erro ao criar a thread.");
        return 1;
    }

    // Cria o evento para alternar o estado do autoclicker
    HANDLE hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
    if (hEvent == NULL) {
        puts("Erro ao criar o evento.");
        return 1;
    }

    puts("ok");
    print_config_keys();

    while (1) {
        if (is_toggle) {
            if (GetAsyncKeyState(LEFT_CLICK_KEY) & 0x8000) {
                mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
                mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
                int randomizer = LEFT_INTERVAL_MS +
                                 (rand() % (2 * LEFT_MAX_VAR + 1)) -
                                 LEFT_MAX_VAR;
                Sleep(randomizer);
            } else if (GetAsyncKeyState(RIGHT_CLICK_KEY) & 0x8000) {
                mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
                mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
                Sleep(50);
            } else {
                WaitForSingleObject(hEvent, 10);  // Espera por 10 ms ou até que o evento seja sinalizado
            }
        } else {
            WaitForSingleObject(hEvent, 100);  // Espera por 100 ms ou até que o evento seja sinalizado
        }
    }

    CloseHandle(hThread);
    CloseHandle(hEvent);
    return 0;
}
