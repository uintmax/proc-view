#include "ProcDetailsWindow.h"

#include <qboxlayout.h>

namespace ui {
    ProcDetailsWindow::ProcDetailsWindow(pid_t pid, QWidget *parent): QMainWindow(parent) {
        proc = std::make_unique<Process>(pid);
        std::vector<MemoryRegion> memory_regions;
        try {
            memory_regions = proc->get_memory_regions();
        } catch (const std::runtime_error &e) {

            auto e_msg = new QMessageBox{parent};
            e_msg->setText("Could not access memory regions. Try again with higher privileges.");
            e_msg->show();
            close();
            return;
        }
        QString title_str = "ProcView - " + QString::number(pid) + " - " + QString::fromStdString(proc->get_comm());
        setWindowTitle(title_str);
        resize(600, 600);

        // Tabs
        auto tabs = new QTabWidget{this};
        setCentralWidget(tabs);

        // TODO: Maybe extra classes for tabs
        auto tab_memory_regions = new QWidget{tabs};
        auto tab_memory_scanner = new QWidget{tabs};
        auto tab_lua = new QWidget{tabs};

        tabs->addTab(tab_memory_regions, "Memory Regions");
        tabs->addTab(tab_memory_scanner, "Memory Scanner");
        tabs->addTab(tab_lua, "Lua");

        // Memory regions tab
        auto layout_memory_regions = new QBoxLayout{QBoxLayout::Direction::Down, tab_memory_regions};
        regions_table = new QTableWidget(memory_regions.size(), 4, tab_memory_regions);
        layout_memory_regions->addWidget(regions_table);

        regions_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
        regions_table->verticalHeader()->setVisible(false);
        auto header_start_addr = new QTableWidgetItem{};
        header_start_addr->setText("Start");
        auto header_end_addr = new QTableWidgetItem{};
        header_end_addr->setText("End");
        auto header_permissions = new QTableWidgetItem{};
        header_permissions->setText("Permissions");
        auto header_pathname = new QTableWidgetItem{};
        header_pathname->setText("Pathname");
        regions_table->setHorizontalHeaderItem(0, header_start_addr);
        regions_table->setHorizontalHeaderItem(1, header_end_addr);
        regions_table->setHorizontalHeaderItem(2, header_permissions);
        regions_table->setHorizontalHeaderItem(3, header_pathname);


        show();
    }
}
