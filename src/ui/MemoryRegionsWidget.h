#ifndef MEMORYREGIONSWIDGET_H
#define MEMORYREGIONSWIDGET_H
#include <QtWidgets>
#include "../Process.h"

namespace ui {
    class MemoryRegionsWidget : public QWidget {
    public:
        MemoryRegionsWidget(const Process &proc, QWidget *parent);

    private:
        Process proc;
        QTableWidget *regions_table = nullptr;
    };
}


#endif //MEMORYREGIONSWIDGET_H
