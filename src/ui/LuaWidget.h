#ifndef LUAWIDGET_H
#define LUAWIDGET_H
#include <QtWidgets>
#include "../Process.h"
#include "../analysis/LuaInterface.h"

namespace ui {
    class LuaWidget : public QWidget {
    public:
        // TODO: Add Process to parameters -> Work on Lua interface. Different interfaces for process list and single process
        LuaWidget(QWidget *parent);

    private:
        void handle_btn_execute();

        analysis::LuaInterface lua_interface;
        QTextEdit *text_edit = nullptr;
    };
}


#endif //LUAWIDGET_H
