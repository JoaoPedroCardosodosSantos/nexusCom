#include "commandManager.h"

#include "../debug/logger.h"

// =====================================================
// VERSÃO DO FIRMWARE
// =====================================================

#define NEXUSCOM_VERSION "0.1.0"

// =====================================================
// INSTÂNCIA GLOBAL
// =====================================================

CommandManager commandManager;

// =====================================================
// INICIALIZAÇÃO
// =====================================================

void CommandManager::begin()
{
    bufferIndex = 0;

    memset(
        buffer,
        0,
        sizeof(buffer)
    );

    Serial.println();
    Serial.println("Digite 'help' para listar os comandos.");
    Serial.println();

    printPrompt();
}

// =====================================================
// PROCESSAMENTO
// =====================================================

void CommandManager::process()
{
    while (Serial.available())
    {
        char c = Serial.read();

        // ENTER
        if (c == '\n' || c == '\r')
        {
            if (bufferIndex > 0)
            {
                buffer[bufferIndex] = '\0';

                execute(buffer);

                bufferIndex = 0;

                memset(
                    buffer,
                    0,
                    sizeof(buffer)
                );
            }

            printPrompt();

            continue;
        }

        // BACKSPACE
        if (c == '\b' || c == 127)
        {
            if (bufferIndex > 0)
            {
                bufferIndex--;

                Serial.print("\b \b");
            }

            continue;
        }

        // Caracteres normais
        if (c >= 32 && c <= 126)
        {
            if (bufferIndex < BUFFER_SIZE - 1)
            {
                buffer[bufferIndex++] = c;

                Serial.print(c);
            }
        }
    }
}

// =====================================================
// EXECUTA COMANDO
// =====================================================

void CommandManager::execute(
    char* command
)
{
    Serial.println();

    // Remove espaços iniciais
    while (*command == ' ')
    {
        command++;
    }

    // -------------------------------------------------
    // HELP
    // -------------------------------------------------

    if (
        strcmp(command, "help") == 0 ||
        strcmp(command, "?") == 0
    )
    {
        commandHelp();
        return;
    }

    // -------------------------------------------------
    // STATUS
    // -------------------------------------------------

    if (strcmp(command, "status") == 0)
    {
        commandStatus();
        return;
    }

    // -------------------------------------------------
    // VERSION
    // -------------------------------------------------

    if (strcmp(command, "version") == 0)
    {
        commandVersion();
        return;
    }

    // -------------------------------------------------
    // REBOOT
    // -------------------------------------------------

    if (strcmp(command, "reboot") == 0)
    {
        commandReboot();
        return;
    }

    // -------------------------------------------------
    // LOGS
    // -------------------------------------------------

    if (
        strcmp(command, "logs") == 0
    )
    {
        logger.printLogs();
        return;
    }

    // logs lora
    if (
        strncmp(
            command,
            "logs ",
            5
        ) == 0
    )
    {
        char* argument = command + 5;

        if (strcmp(argument, "error") == 0)
        {
            logger.printLogsByLevel(
                Logger::ERROR
            );

            return;
        }

        if (strcmp(argument, "warn") == 0)
        {
            logger.printLogsByLevel(
                Logger::WARN
            );

            return;
        }

        if (strcmp(argument, "info") == 0)
        {
            logger.printLogsByLevel(
                Logger::INFO
            );

            return;
        }

        if (strcmp(argument, "debug") == 0)
        {
            logger.printLogsByLevel(
                Logger::DEBUG
            );

            return;
        }

        logger.printLogsByModule(
            argument
        );

        return;
    }

    // -------------------------------------------------
    // LOG LEVEL
    // -------------------------------------------------

    if (
        strncmp(
            command,
            "log level ",
            10
        ) == 0
    )
    {
        commandLog(command + 10);
        return;
    }

    // -------------------------------------------------
    // LOG CLEAR
    // -------------------------------------------------

    if (
        strcmp(
            command,
            "log clear"
        ) == 0
    )
    {
        logger.clear();
        return;
    }

    // -------------------------------------------------
    // COMANDO DESCONHECIDO
    // -------------------------------------------------

    printUnknownCommand(command);
}

// =====================================================
// HELP
// =====================================================

void CommandManager::commandHelp()
{
    Serial.println();
    Serial.println("========== NexusCom CLI ==========");

    Serial.println();
    Serial.println("Sistema:");
    Serial.println("  help");
    Serial.println("  status");
    Serial.println("  version");
    Serial.println("  reboot");

    Serial.println();
    Serial.println("Logs:");
    Serial.println("  logs");
    Serial.println("  logs <modulo>");
    Serial.println("  logs error");
    Serial.println("  logs warn");
    Serial.println("  logs info");
    Serial.println("  logs debug");
    Serial.println("  log level error");
    Serial.println("  log level warn");
    Serial.println("  log level info");
    Serial.println("  log level debug");
    Serial.println("  log clear");

    Serial.println();
    Serial.println("==================================");
    Serial.println();
}

// =====================================================
// STATUS
// =====================================================

void CommandManager::commandStatus()
{
    Serial.println();
    Serial.println("========== STATUS ==========");

    Serial.print("Firmware: ");
    Serial.println(NEXUSCOM_VERSION);

    Serial.print("Uptime: ");
    Serial.print(millis() / 1000);
    Serial.println(" s");

    Serial.print("Logs armazenados: ");
    Serial.println(logger.count());

    Serial.print("Nivel de log: ");
    Serial.println(
        logger.levelName(
            logger.getLevel()
        )
    );

    Serial.print("Free heap: ");
    Serial.print(
        ESP.getFreeHeap()
    );
    Serial.println(" bytes");

    Serial.println("============================");
    Serial.println();
}

// =====================================================
// VERSION
// =====================================================

void CommandManager::commandVersion()
{
    Serial.print(
        "NexusCom firmware "
    );

    Serial.println(
        NEXUSCOM_VERSION
    );
}

// =====================================================
// LOG LEVEL
// =====================================================

void CommandManager::commandLog(
    char* argument
)
{
    if (strcmp(argument, "error") == 0)
    {
        logger.setLevel(
            Logger::ERROR
        );

        Serial.println(
            "Nivel de log: ERROR"
        );

        return;
    }

    if (strcmp(argument, "warn") == 0)
    {
        logger.setLevel(
            Logger::WARN
        );

        Serial.println(
            "Nivel de log: WARN"
        );

        return;
    }

    if (strcmp(argument, "info") == 0)
    {
        logger.setLevel(
            Logger::INFO
        );

        Serial.println(
            "Nivel de log: INFO"
        );

        return;
    }

    if (strcmp(argument, "debug") == 0)
    {
        logger.setLevel(
            Logger::DEBUG
        );

        Serial.println(
            "Nivel de log: DEBUG"
        );

        return;
    }

    Serial.println(
        "Nivel invalido."
    );

    Serial.println(
        "Use: error, warn, info ou debug"
    );
}

// =====================================================
// REBOOT
// =====================================================

void CommandManager::commandReboot()
{
    Serial.println(
        "Reiniciando ESP32..."
    );

    delay(500);

    ESP.restart();
}

// =====================================================
// PROMPT
// =====================================================

void CommandManager::printPrompt()
{
    Serial.print("> ");
}

// =====================================================
// COMANDO DESCONHECIDO
// =====================================================

void CommandManager::printUnknownCommand(
    const char* command
)
{
    Serial.print(
        "Comando desconhecido: "
    );

    Serial.println(command);

    Serial.println(
        "Digite 'help' para ajuda."
    );
}