#include "MemoryScannerWidget.h"

namespace ui {
    MemoryScannerWidget::MemoryScannerWidget(const Process &proc, QWidget *parent): QWidget(parent),
        proc(proc), memory_scanner(proc) {
        auto layout_memory_scanner = new QBoxLayout{QBoxLayout::Direction::Down, this};

        line_value = new QLineEdit{this};
        line_value->setValidator(new QIntValidator{line_value});
        auto btn_scan_new = new QPushButton{"New scan", this};
        connect(btn_scan_new, &QPushButton::released, this, &MemoryScannerWidget::handle_btn_new_scan);
        auto btn_scan_next = new QPushButton{"Next scan", this};
        connect(btn_scan_next, &QPushButton::released, this, &MemoryScannerWidget::handle_btn_next_scan);
        layout_memory_scanner->addWidget(line_value);
        layout_memory_scanner->addWidget(btn_scan_new);
        layout_memory_scanner->addWidget(btn_scan_next);


        scanner_table = new QTableWidget(0, 2, this);

        scanner_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
        scanner_table->verticalHeader()->setVisible(false);
        auto header_address = new QTableWidgetItem{"Address"};
        auto header_value = new QTableWidgetItem{"Value"};

        scanner_table->setHorizontalHeaderItem(0, header_address);
        scanner_table->setHorizontalHeaderItem(1, header_value);
        layout_memory_scanner->addWidget(scanner_table);

        connect(scanner_table, &QTableWidget::cellDoubleClicked, this, &MemoryScannerWidget::handle_table_click);
    }

    void MemoryScannerWidget::handle_btn_new_scan() {
        // qDebug() << "Scan value: " << line_value->text();
        memory_scanner.scan_new(line_value->text().toInt());
        auto results = memory_scanner.get_addr_results();
        scanner_table->clearContents();
        scanner_table->setRowCount(results.size());
        for (int i = 0; i < results.size(); i++) {
            auto result_addr = new QTableWidgetItem{QString::number(results.at(i), 16)};
            auto result_value = new QTableWidgetItem{line_value->text()}; // TODO: Add live update for values in table
            scanner_table->setItem(i, 0, result_addr);
            scanner_table->setItem(i, 1, result_value);
        }
    }

    void MemoryScannerWidget::handle_btn_next_scan() {
        memory_scanner.scan_next(line_value->text().toInt());
        auto results = memory_scanner.get_addr_results();
        scanner_table->clearContents();
        scanner_table->setRowCount(results.size());
        for (int i = 0; i < results.size(); i++) {
            auto result_addr = new QTableWidgetItem{QString::number(results.at(i), 16)};
            auto result_value = new QTableWidgetItem{line_value->text()};
            scanner_table->setItem(i, 0, result_addr);
            scanner_table->setItem(i, 1, result_value);
        }
    }

    void MemoryScannerWidget::handle_table_click(int row, int column) {
        bool ok = false;
        auto addr = scanner_table->item(row, 0)->text().toULongLong(&ok, 16);
        if (!ok) {
            auto e_msg = new QMessageBox{this};
            e_msg->setText("Could not parse address in scanner_table");
            e_msg->show();
            return;
        }
        // For now only int support
        auto value = QInputDialog::getInt(this, "Change value", "New value:");
        try {
            proc.write(addr, value);
        } catch (const std::exception &e) {
            auto e_msg = new QMessageBox{this};
            e_msg->setText("Could not write to address.");
            e_msg->show();
        }
    }
}
