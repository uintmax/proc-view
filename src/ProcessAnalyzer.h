#ifndef PROCESSANALYZER_H
#define PROCESSANALYZER_H
#include "Process.h"


class ProcessAnalyzer {
public:
    enum class BinaryFormat {
        ELF,
        PE, // Running in WINE
        UNKNOWN
    };

    ProcessAnalyzer(const Process &proc): proc(proc) {
    }

    BinaryFormat get_binary_format();

private:
    Process proc;
};


#endif //PROCESSANALYZER_H
