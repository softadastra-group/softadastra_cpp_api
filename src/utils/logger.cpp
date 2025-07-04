#include "utils/logger.hpp"

namespace Softadastra {

    namespace {
        bool useColor = true;
        bool writeToFile = true;
        bool rotateLogsDaily = false;

        std::string currentLogDate = "";
        std::ofstream logFile;

        std::string getDateOnly() {
            std::time_t now = std::time(nullptr);
            std::tm* localTime = std::localtime(&now);
            char buffer[20];
            std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", localTime);
            return buffer;
        }

        void openLogFileForToday() {
            std::string today = getDateOnly();
            if (currentLogDate != today) {
                if (logFile.is_open()) logFile.close();
                std::string filename = "log_" + today + ".log";
                logFile.open(filename, std::ios::app);
                currentLogDate = today;
            }
        }
    }

    void enableColor(bool value) {
        useColor = value;
    }

    void enableFileLogging(bool value) {
        writeToFile = value;
        if (value && rotateLogsDaily) {
            openLogFileForToday();
        } else if (value && !rotateLogsDaily && !logFile.is_open()) {
            logFile.open("softadastra.log", std::ios::app);
        }
    }

    void enableDailyLogRotation(bool value) {
        rotateLogsDaily = value;
        if (value && writeToFile) {
            openLogFileForToday();
        }
    }

    std::string getCurrentTime() {
        std::time_t now = std::time(nullptr);
        std::tm* localTime = std::localtime(&now);
        char buffer[80];
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localTime);
        return buffer;
    }

    void log(LogLevel level, const std::string& message) {
        std::string prefix;
        std::string colorCode;

        switch (level) {
            case LogLevel::INFO:
                prefix = "ℹ️  [INFO]";
                colorCode = "\033[36m";
                break;
            case LogLevel::WARNING:
                prefix = "⚠️  [WARNING]";
                colorCode = "\033[33m";
                break;
            case LogLevel::ERROR:
                prefix = "❌ [ERROR]";
                colorCode = "\033[31m";
                break;
        }

        std::string timeStr = getCurrentTime();
        std::string finalMessage = "[" + timeStr + "] " + prefix + " " + message;

        // Console
        if (useColor) {
            std::cout << colorCode << finalMessage << "\033[0m" << std::endl;
        } else {
            std::cout << finalMessage << std::endl;
        }

        // Fichier
        if (writeToFile) {
            if (rotateLogsDaily) openLogFileForToday();
            if (logFile.is_open()) {
                logFile << finalMessage << std::endl;
            }
        }
    }

}
