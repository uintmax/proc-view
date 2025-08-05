#include "MemoryRegionsWidget.h"

namespace ui {
    MemoryRegionsWidget::MemoryRegionsWidget(const Process &proc, QWidget *parent): QWidget(parent), proc(proc) {
        auto memory_regions = proc.get_memory_regions();
        auto layout_memory_regions = new QBoxLayout{QBoxLayout::Direction::Down, this};
        regions_table = new QTableWidget(memory_regions.size(), 4, this);
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
    }
}
