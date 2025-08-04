#ifndef PROCLISTWINDOW_H
#define PROCLISTWINDOW_H
#include <QtWidgets>
#include "../Process.h"
#include <iostream>
#include "ProcDetailsWindow.h"

namespace ui {
    /**
     * Window lists all running processes and exposes a Lua scripting interface
     */
    class ProcListWindow : public QMainWindow {
    public:
        ProcListWindow();
    private:
        QTableWidget *proc_table = nullptr;
        void handle_table_click(int row, int column);
    };
}


#endif //PROCLISTWINDOW_H
