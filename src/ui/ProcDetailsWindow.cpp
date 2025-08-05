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

        auto tab_memory_regions = new QWidget{tabs};
        auto tab_memory_scanner = new MemoryScannerWidget{proc, this};
        auto tab_lua = new QWidget{tabs};

        tabs->addTab(tab_memory_regions, "Memory Regions");
        tabs->addTab(tab_memory_scanner, "Memory Scanner");
        tabs->addTab(tab_lua, "Lua Scripting");

        // Memory regions tab
        auto layout_memory_regions = new QBoxLayout{QBoxLayout::Direction::Down, tab_memory_regions};
        regions_table = new QTableWidget(memory_regions.size(), 4, tab_memory_regions);
        layout_memory_regions->addWidget(regions_table);

        regions_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
        regions_table->verticalHeader()->setVisible(false);
        auto header_start_addr = new QTableWidgetItem{"Start"};
        auto header_end_addr = new QTableWidgetItem{"End"};
        auto header_permissions = new QTableWidgetItem{"Permissions"};
        auto header_pathname = new QTableWidgetItem{"Pathname"};
        regions_table->setHorizontalHeaderItem(0, header_start_addr);
        regions_table->setHorizontalHeaderItem(1, header_end_addr);
        regions_table->setHorizontalHeaderItem(2, header_permissions);
        regions_table->setHorizontalHeaderItem(3, header_pathname);

        for (int i = 0; i < memory_regions.size(); i++) {
            const auto &region = memory_regions.at(i);
            auto item_start_addr = new QTableWidgetItem(QString::number(region.get_start_addr(), 16));
            auto item_end_addr = new QTableWidgetItem(QString::number(region.get_end_addr(), 16));
            auto item_permissions = new QTableWidgetItem(QString::fromStdString(region.get_permissions()));
            auto item_pathname = new QTableWidgetItem(QString::fromStdString(region.get_pathname()));

            regions_table->setItem(i, 0, item_start_addr);
            regions_table->setItem(i, 1, item_end_addr);
            regions_table->setItem(i, 2, item_permissions);
            regions_table->setItem(i, 3, item_pathname);
        }


        show();
    }

    void ProcDetailsWindow::handle_btn_new_scan() {
        qDebug() << "Scan value: " << line_value->text();
    }

    void ProcDetailsWindow::handle_btn_next_scan() {
    }
}
