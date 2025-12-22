#include "keyBoard.h"

Keyboard keyboard;

void setup() {
    Serial.begin(9600);

    // Testes de interpretador de teclado 
    
    // row + col
    keyboard.interpret(keyboard.getKey(3,2));  

    if(keyboard.getNote().length() != 0) {
        Serial.println("String: "+keyboard.getNote());
    } 
    
    const SpecialKey* sk = keyboard.getSpecialKeys();
    for(int i = 0; i < 11; i++) {
        if (sk[i].ativo) { Serial.println(keyTypeToString(sk[i].type)); return;}
    }

}

void loop() {

}