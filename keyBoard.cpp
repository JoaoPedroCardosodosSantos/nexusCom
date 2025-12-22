#include "keyBoard.h"

// Construtor
Keyboard::Keyboard() :

keyBoard{
    // LINHA 0 
    {
      { '1', '0', T_NORMAL }, { '2', '!', T_NORMAL }, { '3', '"', T_NORMAL },
      { '4', '\'', T_NORMAL }, { '5', '?', T_NORMAL }, { '6', '~', T_NORMAL },
      { '7', '^', T_NORMAL }, { '8', ',', T_NORMAL }, { '9', '.', T_NORMAL }
    },

    // LINHA 1 
    {
      { 'q', 'Q', T_NORMAL }, { 'y', 'w', T_NORMAL }, { 'e', 'E', T_NORMAL },
      { 'r', 'R', T_NORMAL }, { 't', 'T', T_NORMAL }, { 'u', 'U', T_NORMAL },
      { 'i', 'I', T_NORMAL }, { 'o', 'O', T_NORMAL }, { 'p', 'P', T_NORMAL }
    },

    // LINHA 2 
    {
      { 'a', 'A', T_NORMAL }, { 's', 'S', T_NORMAL }, { 'd', 'D', T_NORMAL },
      { 'f', 'F', T_NORMAL }, { 'g', 'G', T_NORMAL }, { 'h', 'H', T_NORMAL },
      { 'j', 'J', T_NORMAL }, { 'l', 'k', T_NORMAL }, { 0, 0, T_DELETE }
    },

    // LINHA 3
    {
      { 'x', 'z', T_NORMAL }, { 'c', 'ç', T_NORMAL }, { 'v', 'V', T_NORMAL },
      { 'b', 'B', T_NORMAL }, { 'n', 'N', T_NORMAL }, { 'm', 'M', T_NORMAL },
      { 0, 0, T_SHIFT }, { 0, 0, T_UP }, { 0, 0, T_ENTER }
    },

    // LINHA 4
    {
      { 0, 0, T_FIXA }, { 0, 0, T_HOME }, { 0, 0, T_SPACE },
      { 0, 0, T_UNUSED }, { 0, 0, T_UNUSED }, { 0, 0, T_UNUSED },
      { 0, 0, T_RIGHT }, { 0, 0, T_DOWN }, { 0, 0, T_LEFT }
    }
},

specialKeys{
    { T_SHIFT, false }, { T_FIXA, false }, { T_HOME, false },
    { T_LEFT, false }, { T_DOWN, false }, { T_RIGHT, false },
    { T_UP, false }, { T_ENTER, false }, { T_DELETE, false },
    { T_SPACE, false }, { T_UNUSED, false }
},

note(""){}

// Retorna tecla da matriz 
const Key& Keyboard::getKey(uint8_t row, uint8_t col) const {
    return keyBoard[row][col];
}

String Keyboard::getNote() const {
    return note;
}

const SpecialKey* Keyboard::getSpecialKeys() const {
    return specialKeys;
}

void Keyboard::clearNote() {
    note = "";
}

void Keyboard::interpret(const Key& k) {

    // Teclas especiais
    for (int i = 0; i < NUM_SPECIAL_KEYS; i++) {
        if (k.type == specialKeys[i].type) {
            if(specialKeys[i].ativo) {
                specialKeys[i].ativo = false;
            } else {
                specialKeys[i].ativo = true;
            }
            return;
        }
    }

    // SHIFT + FIXA
    if (specialKeys[0].ativo && specialKeys[1].ativo) {
        if (k.normal == 'y') { note += 'W'; return; }
        if (k.normal == 'l') { note += 'K'; return; }
        if (k.normal == 'x') { note += 'Z'; return; }
    }

    // SHIFT
    if (specialKeys[0].ativo) {

        for (int i = 0; i < COLUMNS; i++) {
            if (k.normal == keyBoard[0][i].normal) {
                note += keyBoard[0][i].shift;
                return;
            }
        }

        if (k.normal == 'y') { note += 'w'; return; }
        if (k.normal == 'l') { note += 'k'; return; }
        if (k.normal == 'x') { note += 'z'; return; }
        if (k.normal == 'c') { note += 'ç'; return; }
    }

    // FIXA
    if (specialKeys[1].ativo) {

        if (k.normal == 'y') { note += 'Y'; return; }
        if (k.normal == 'l') { note += 'L'; return; }
        if (k.normal == 'x') { note += 'X'; return; }
        if (k.normal == 'c') { note += 'C'; return; }

        for (int i = 0; i < COLUMNS; i++) {
            if (k.normal == keyBoard[0][i].normal) {
                note += keyBoard[0][i].normal;
                return;
            }
        }

        note += k.shift;
        return;
    }

    note += k.normal;
}

// Função de conversão para String 
const char* keyTypeToString(KeyType type) {
    switch (type) {
        case T_NORMAL: return "T_NORMAL";
        case T_SHIFT:  return "T_SHIFT";
        case T_FIXA:   return "T_FIXA";
        case T_ENTER:  return "T_ENTER";
        case T_DELETE: return "T_DELETE";
        case T_HOME:   return "T_HOME";
        case T_SPACE:  return "T_SPACE";
        case T_UP:     return "T_UP";
        case T_DOWN:   return "T_DOWN";
        case T_RIGHT:  return "T_RIGHT";
        case T_LEFT:   return "T_LEFT";
        case T_UNUSED: return "T_UNUSED";
        default:       return "UNKNOWN";
    }
}