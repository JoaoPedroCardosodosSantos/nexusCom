#include "logger.h"

Logger logger;

// =====================================================
// INICIALIZAÇÃO
// =====================================================

void Logger::begin(uint32_t baudRate)
{
    Serial.begin(baudRate);

    delay(100);

    writeIndex = 0;
    entryCount = 0;

    currentLevel = INFO;

    Serial.println();
    Serial.println("========================================");
    Serial.println("          NexusCom Logger");
    Serial.println("========================================");
    Serial.print("Buffer de logs: ");
    Serial.print(MAX_ENTRIES);
    Serial.println(" entradas");

    Serial.print("Nivel: ");
    Serial.println(levelName(currentLevel));

    Serial.println();
}

// =====================================================
// LOG ERROR
// =====================================================

void Logger::error(
    const char* module,
    const char* message
)
{
    add(ERROR, module, message);
}

// =====================================================
// LOG WARN
// =====================================================

void Logger::warn(
    const char* module,
    const char* message
)
{
    add(WARN, module, message);
}

// =====================================================
// LOG INFO
// =====================================================

void Logger::info(
    const char* module,
    const char* message
)
{
    add(INFO, module, message);
}

// =====================================================
// LOG DEBUG
// =====================================================

void Logger::debug(
    const char* module,
    const char* message
)
{
    add(DEBUG, module, message);
}

// =====================================================
// ADICIONA LOG
// =====================================================

void Logger::add(
    Level level,
    const char* module,
    const char* message
)
{
    // Não registra níveis abaixo do configurado
    if (level > currentLevel)
    {
        return;
    }

    Entry& entry = entries[writeIndex];

    entry.timestamp = millis();
    entry.level = level;

    copyString(
        entry.module,
        module,
        MODULE_SIZE
    );

    copyString(
        entry.message,
        message,
        MESSAGE_SIZE
    );

    printEntry(entry);

    writeIndex++;

    if (writeIndex >= MAX_ENTRIES)
    {
        writeIndex = 0;
    }

    if (entryCount < MAX_ENTRIES)
    {
        entryCount++;
    }
}

// =====================================================
// IMPRIME ENTRADA
// =====================================================

void Logger::printEntry(
    const Entry& entry
)
{
    Serial.print("[");

    printTimestamp(entry.timestamp);

    Serial.print("] ");

    Serial.print("[");
    Serial.print(levelName(entry.level));
    Serial.print("] ");

    Serial.print(entry.module);

    Serial.print(" ");

    Serial.println(entry.message);
}

// =====================================================
// TIMESTAMP
// =====================================================

void Logger::printTimestamp(
    uint32_t timestamp
)
{
    uint32_t seconds = timestamp / 1000;

    uint16_t milliseconds =
        timestamp % 1000;

    uint8_t hours =
        (seconds / 3600) % 24;

    uint8_t minutes =
        (seconds / 60) % 60;

    uint8_t secs =
        seconds % 60;

    if (hours < 10)
        Serial.print("0");

    Serial.print(hours);
    Serial.print(":");

    if (minutes < 10)
        Serial.print("0");

    Serial.print(minutes);
    Serial.print(":");

    if (secs < 10)
        Serial.print("0");

    Serial.print(secs);
    Serial.print(".");

    if (milliseconds < 100)
        Serial.print("0");

    if (milliseconds < 10)
        Serial.print("0");

    Serial.print(milliseconds);
}

// =====================================================
// NOME DO NÍVEL
// =====================================================

const char* Logger::levelName(
    Level level
) const
{
    switch (level)
    {
        case ERROR:
            return "ERROR";

        case WARN:
            return "WARN ";

        case INFO:
            return "INFO ";

        case DEBUG:
            return "DEBUG";

        default:
            return "?????";
    }
}

// =====================================================
// ALTERA NÍVEL
// =====================================================

void Logger::setLevel(
    Level level
)
{
    currentLevel = level;
}

// =====================================================
// OBTÉM NÍVEL
// =====================================================

Logger::Level Logger::getLevel() const
{
    return currentLevel;
}

// =====================================================
// IMPRIME TODOS OS LOGS
// =====================================================

void Logger::printLogs()
{
    if (entryCount == 0)
    {
        Serial.println("Nenhum log armazenado.");
        return;
    }

    Serial.println();
    Serial.println("========== LOGS ==========");

    uint16_t start;

    if (entryCount < MAX_ENTRIES)
    {
        start = 0;
    }
    else
    {
        start = writeIndex;
    }

    for (uint16_t i = 0; i < entryCount; i++)
    {
        uint16_t index =
            (start + i) % MAX_ENTRIES;

        printEntry(entries[index]);
    }

    Serial.println("==========================");
    Serial.println();
}

// =====================================================
// LOGS POR MÓDULO
// =====================================================

void Logger::printLogsByModule(
    const char* module
)
{
    bool found = false;

    Serial.println();
    Serial.print("========== LOGS: ");
    Serial.print(module);
    Serial.println(" ==========");

    uint16_t start;

    if (entryCount < MAX_ENTRIES)
    {
        start = 0;
    }
    else
    {
        start = writeIndex;
    }

    for (uint16_t i = 0; i < entryCount; i++)
    {
        uint16_t index =
            (start + i) % MAX_ENTRIES;

        if (strcmp(
                entries[index].module,
                module
            ) == 0)
        {
            printEntry(entries[index]);
            found = true;
        }
    }

    if (!found)
    {
        Serial.println("Nenhum log encontrado.");
    }

    Serial.println("================================");
    Serial.println();
}

// =====================================================
// LOGS POR NÍVEL
// =====================================================

void Logger::printLogsByLevel(
    Level level
)
{
    bool found = false;

    Serial.println();
    Serial.print("========== LOGS: ");
    Serial.print(levelName(level));
    Serial.println(" ==========");

    uint16_t start;

    if (entryCount < MAX_ENTRIES)
    {
        start = 0;
    }
    else
    {
        start = writeIndex;
    }

    for (uint16_t i = 0; i < entryCount; i++)
    {
        uint16_t index =
            (start + i) % MAX_ENTRIES;

        if (entries[index].level == level)
        {
            printEntry(entries[index]);
            found = true;
        }
    }

    if (!found)
    {
        Serial.println("Nenhum log encontrado.");
    }

    Serial.println("================================");
    Serial.println();
}

// =====================================================
// LIMPA BUFFER
// =====================================================

void Logger::clear()
{
    writeIndex = 0;
    entryCount = 0;

    Serial.println(
        "Buffer de logs limpo."
    );
}

// =====================================================
// QUANTIDADE
// =====================================================

uint16_t Logger::count() const
{
    return entryCount;
}

// =====================================================
// COPIA STRING COM SEGURANÇA
// =====================================================

void Logger::copyString(
    char* destination,
    const char* source,
    size_t size
)
{
    if (size == 0)
    {
        return;
    }

    strncpy(
        destination,
        source,
        size - 1
    );

    destination[size - 1] = '\0';
}