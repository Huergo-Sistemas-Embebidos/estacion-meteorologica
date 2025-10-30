#include "sd-manager.h"

SDManager::SDManager(int CSPin) : CSPin(CSPin) {}

bool SDManager::begin() {
    // TODO
}

void SDManager::appendFile(const char *path, const char *message, const char *defaultHeaders) {
    // TODO
}

String SDManager::readFile(const char *path) {
    // TODO
}

String **SDManager::readEnvironmentVariables(const char *path) {
    File file = SD.open(path, FILE_READ);
    if (!file) {
        Serial.println("[SD] Error al abrir el archivo de variables de entorno.");
        return nullptr;
    }

    // Temporary storage for pairs
    std::vector<String *> pairs;
    while (file.available()) {
        String line = file.readStringUntil('\n');
        line.trim();
        if (line.length() == 0) continue;
        int eqIdx = line.indexOf('=');
        if (eqIdx == -1) continue;
        String key = line.substring(0, eqIdx);
        String value = line.substring(eqIdx + 1);
        key.trim();
        value.trim();
        // Remove quotes from value
        if (value.startsWith("\"") && value.endsWith("\"")) {
            value = value.substring(1, value.length() - 1);
        }
        String *pair = new String[2];
        pair[0] = key;
        pair[1] = value;
        pairs.push_back(pair);
    }
    file.close();

    // Allocate result array
    String **result = new String *[pairs.size() + 1];
    for (size_t i = 0; i < pairs.size(); ++i) {
        result[i] = pairs[i];
    }
    result[pairs.size()] = nullptr;
    return result;
}
