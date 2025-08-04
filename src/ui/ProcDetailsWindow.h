#ifndef PROCDETAILSWINDOW_H
#define PROCDETAILSWINDOW_H

#include <QtWidgets>
#include <memory>
#include "../Process.h"
#include <QDebug>

namespace ui {
    /**
     * Lists information of a specified process and offers process analysis options
     */
    class ProcDetailsWindow : public QMainWindow {
    public:
        ProcDetailsWindow(pid_t pid, QWidget *parent);

    private:
        void handle_btn_new_scan();
        void handle_btn_next_scan();

        std::unique_ptr<Process> proc;
        // Managed by Qt
        QTableWidget *regions_table = nullptr;
        QTableWidget *scanner_table = nullptr;
        QLineEdit *line_value = nullptr;
    };
}

#endif //PROCDETAILSWINDOW_H
