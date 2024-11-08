#ifndef CONFIG_H
#define CONFIG_H

// Escolha as teclas:
// https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
#define TOGGLE_KEY 0x74  // Exemplo: F5
#define LEFT_CLICK_KEY VK_XBUTTON2
#define RIGHT_CLICK_KEY VK_XBUTTON1

/*
Intervalos de clique em ms
55 = ~15.7 cps
*/
#define LEFT_INTERVAL_MS 55
#define RIGHT_INTERVAL_MS 35

// Variacao maxima
#define LEFT_MAX_VAR 15
//#define RIGHT_MAX_VAR 50

#endif  // CONFIG_H
