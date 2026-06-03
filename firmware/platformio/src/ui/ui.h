#ifndef UI_H
#define UI_H

void drawHomeScreen();
void inicializarSistema();

void addRX(const char* msg);
void addTX(const char* msg);

void drawStatusBar();
void drawEditor(
    const char* texto,
    bool modoNumerico
);

#endif