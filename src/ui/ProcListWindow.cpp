#include "ProcListWindow.h"

namespace ui {
    ProcListWindow::ProcListWindow() {
        auto procs = Process::get_all_processes();

        setWindowTitle("ProcView - List");
        resize(600, 600);
        // TODO: Check if Qt is freeing all my allocated objects

        // Tabs
        auto tabs = new QTabWidget{this};
        setCentralWidget(tabs);

        auto tab_proc_list = new QWidget{tabs};
        auto tab_lua = new QWidget{tabs};

        tabs->addTab(tab_proc_list, "Processes");
        tabs->addTab(tab_lua, "Lua Scripting");

        // Proc list tab
        auto layout_proc_list = new QBoxLayout{QBoxLayout::Direction::Down, tab_proc_list};
        proc_table = new QTableWidget(procs.size(), 3, tab_proc_list);
        layout_proc_list->addWidget(proc_table);

        proc_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
        proc_table->verticalHeader()->setVisible(false);
        auto header_pid = new QTableWidgetItem{};
        header_pid->setText("PID");
        auto header_user = new QTableWidgetItem{};
        header_user->setText("User");
        auto header_name = new QTableWidgetItem{};
        header_name->setText("Name");
        proc_table->setHorizontalHeaderItem(0, header_pid);
        proc_table->setHorizontalHeaderItem(1, header_user);
        proc_table->setHorizontalHeaderItem(2, header_name);

        for (int i = 0; i < procs.size(); i++) {
            auto item_pid = new QTableWidgetItem(QString::number(procs.at(i).get_pid()));
            auto item_user = new QTableWidgetItem(QString::number(procs.at(i).get_uid()));
            auto item_name = new QTableWidgetItem(QString::fromStdString(procs.at(i).get_comm()));
            proc_table->setItem(i, 0, item_pid);
            proc_table->setItem(i, 1, item_user);
            proc_table->setItem(i, 2, item_name);
        }

        connect(proc_table, &QTableWidget::cellDoubleClicked, this, &ProcListWindow::handle_table_click);

        show();
    }

    void ProcListWindow::handle_table_click(int row, int column) {
        auto pid = proc_table->item(row, 0); // Get pid
        auto proc_details_window = new ProcDetailsWindow(pid->text().toLong(), this);
    }
}
