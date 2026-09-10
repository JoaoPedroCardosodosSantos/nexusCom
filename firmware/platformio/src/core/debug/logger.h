#ifndef LOGGER_H
#define LOGGER_H

#include <Arduino.h>

class Logger
{
public:

    // =================================================
    // NÍVEIS
    // =================================================

    enum Level
    {
        ERROR = 0,
        WARN  = 1,
        INFO  = 2,
        DEBUG = 3
    };

    // =================================================
    // CONFIGURAÇÃO
    // =================================================

    static const uint16_t MAX_ENTRIES = 128;
    static const uint8_t MODULE_SIZE = 12;
    static const uint8_t MESSAGE_SIZE = 96;

    // =================================================
    // INICIALIZAÇÃO
    // =================================================

    void begin(
        uint32_t baudRate = 115200
    );

    // =================================================
    // LOG
    // =================================================

    void error(
        const char* module,
        const char* message
    );

    void warn(
        const char* module,
        const char* message
    );

    void info(
        const char* module,
        const char* message
    );

    void debug(
        const char* module,
        const char* message
    );

    // =================================================
    // CONFIGURAÇÃO
    // =================================================

    void setLevel(Level level);

    Level getLevel() const;

    // =================================================
    // CONSULTA
    // =================================================

    void printLogs();

    void printLogsByModule(
        const char* module
    );

    void printLogsByLevel(
        Level level
    );

    void clear();

    uint16_t count() const;

    // =================================================
    // UTILITÁRIOS
    // =================================================

    const char* levelName(
        Level level
    ) const;

private:

    struct Entry
    {
        uint32_t timestamp;

        Level level;

        char module[MODULE_SIZE];

        char message[MESSAGE_SIZE];
    };

    Entry entries[MAX_ENTRIES];

    uint16_t writeIndex;

    uint16_t entryCount;

    Level currentLevel;

    // =================================================
    // MÉTODOS INTERNOS
    // =================================================

    void add(
        Level level,
        const char* module,
        const char* message
    );

    void printEntry(
        const Entry& entry
    );

    void printTimestamp(
        uint32_t timestamp
    );

    void copyString(
        char* destination,
        const char* source,
        size_t size
    );
};

// =====================================================
// INSTÂNCIA GLOBAL
// =====================================================

extern Logger logger;

// =====================================================
// MACROS
// =====================================================

#define LOG_ERROR(module, message) \
    logger.error(module, message)

#define LOG_WARN(module, message) \
    logger.warn(module, message)

#define LOG_INFO(module, message) \
    logger.info(module, message)

#define LOG_DEBUG(module, message) \
    logger.debug(module, message)

#endif