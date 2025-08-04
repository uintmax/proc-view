#include "ProcDetailsWindow.h"

namespace ui {
    ProcDetailsWindow::ProcDetailsWindow(pid_t pid, QWidget *parent): QMainWindow(parent) {
        proc = std::make_unique<Process>(pid);
        QString title_str = "ProcView - " + QString::number(pid) + " - " + QString::fromStdString(proc->get_comm());
        setWindowTitle(title_str);
        resize(600, 600);
        show();
    }
}
