#ifndef PROCDETAILSWINDOW_H
#define PROCDETAILSWINDOW_H

#include <QtWidgets>
#include <memory>
#include "../Process.h"

namespace ui {
    /**
     * Lists information of a specified process and offers process analysis options
     */
    class ProcDetailsWindow : public QMainWindow {
    public:
        ProcDetailsWindow(pid_t pid, QWidget *parent);

    private:
        std::unique_ptr<Process> proc;
    };
}

#endif //PROCDETAILSWINDOW_H
