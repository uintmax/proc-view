#include "ProcDetailsWindow.h"

#include <qboxlayout.h>

namespace ui {
    ProcDetailsWindow::ProcDetailsWindow(pid_t pid, QWidget *parent): QMainWindow(parent), proc(pid) {
        std::vector<MemoryRegion> memory_regions;
        try {
            memory_regions = proc.get_memory_regions();
        } catch (const std::runtime_error &e) {
            auto e_msg = new QMessageBox{parent};
            e_msg->setText("Could not access memory regions. Try again with higher privileges.");
            e_msg->show();
            close();
            return;
        }
        QString title_str = "ProcView - " + QString::number(pid) + " - " + QString::fromStdString(proc.get_comm());
        setWindowTitle(title_str);
        resize(600, 600);

        // Tabs
        auto tabs = new QTabWidget{this};
        setCentralWidget(tabs);

        auto tab_memory_regions = new MemoryRegionsWidget{proc, this};
        auto tab_memory_scanner = new MemoryScannerWidget{proc, this};
        auto tab_lua = new QWidget{tabs};

        tabs->addTab(tab_memory_regions, "Memory Regions");
        tabs->addTab(tab_memory_scanner, "Memory Scanner");
        tabs->addTab(tab_lua, "Lua Scripting");

        show();
    }

    void ProcDetailsWindow::handle_btn_new_scan() {
        qDebug() << "Scan value: " << line_value->text();
    }

    void ProcDetailsWindow::handle_btn_next_scan() {
    }
}
