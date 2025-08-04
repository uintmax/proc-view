#ifndef PROCLISTWINDOW_H
#define PROCLISTWINDOW_H
#include <QtWidgets>
#include "../Process.h"

namespace ui {
    /**
     * Window lists all running processes and exposes a Lua scripting interface
     */
    class ProcListWindow : public QMainWindow {
    public:
        ProcListWindow();
    };
}


#endif //PROCLISTWINDOW_H
