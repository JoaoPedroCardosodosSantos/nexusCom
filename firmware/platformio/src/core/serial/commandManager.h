#ifndef COMMAND_MANAGER_H
#define COMMAND_MANAGER_H

#include <Arduino.h>

class CommandManager
{
public:

    static const uint8_t BUFFER_SIZE = 96;

    void begin();

    void process();

private:

    char buffer[BUFFER_SIZE];

    uint8_t bufferIndex;

    // =================================================
    // PROCESSAMENTO
    // =================================================

    void execute(
        char* command
    );

    // =================================================
    // COMANDOS
    // =================================================

    void commandHelp();

    void commandStatus();

    void commandVersion();

    void commandLogs(
        char* argument
    );

    void commandLog(
        char* argument
    );

    void commandReboot();

    // =================================================
    // UTILITÁRIOS
    // =================================================

    void printPrompt();

    void printUnknownCommand(
        const char* command
    );
};

extern CommandManager commandManager;

#endif