#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <Arduino.h>

// Tipos de tecla
enum KeyType {
    T_NORMAL,
    T_SHIFT,
    T_FIXA,
    T_ENTER,
    T_DELETE,
    T_HOME,
    T_SPACE,
    T_UP,
    T_DOWN,
    T_RIGHT,
    T_LEFT,
    T_UNUSED
};

// Função de conversão
const char* keyTypeToString(KeyType type);

// Estrutura da tecla
struct Key {
    char normal;
    char shift;
    KeyType type;
};

// Estrutura de tecla especial 
struct SpecialKey {
    KeyType type;
    bool ativo;
};

// Dimensões
#define ROWS 5
#define COLUMNS 9
#define NUM_SPECIAL_KEYS 11

class Keyboard {
  private:
    const Key keyBoard[ROWS][COLUMNS];
    SpecialKey specialKeys[NUM_SPECIAL_KEYS];
    String note;

  public:
    Keyboard();

    void interpret(const Key& k);

    String getNote() const;
    const SpecialKey* getSpecialKeys() const;
    void clearNote();
    const Key& getKey(uint8_t row, uint8_t col) const;
};

#endif