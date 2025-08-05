#ifndef MEMORYSCANNERWIDGET_H
#define MEMORYSCANNERWIDGET_H

#include <QtWidgets>
#include "../Process.h"
#include "../analysis/MemoryScanner.h"

namespace ui {
    class MemoryScannerWidget : public QWidget {
    public:
        MemoryScannerWidget(const Process &proc, QWidget *parent);

    private:
        void handle_btn_new_scan();
        void handle_btn_next_scan();

        QLineEdit *line_value = nullptr;
        QTableWidget *scanner_table = nullptr;
        analysis::MemoryScanner memory_scanner;

    };
}


#endif //MEMORYSCANNERWIDGET_H
