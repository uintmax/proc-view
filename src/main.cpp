#define SOL_ALL_SAFETIES_ON 1
#include <iostream>
#include "Process.h"
#include "System.h"
#include <sol/sol.hpp>
#include <QtWidgets>

#include "analysis/MemoryScanner.h"
#include "analysis/StringsFinder.h"
#include "analysis/LuaInterface.h"
#include "ui/ProcListWindow.h"

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    ui::ProcListWindow proc_list_window;

    return app.exec();
}
