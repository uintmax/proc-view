#include "LuaWidget.h"

namespace ui {
    LuaWidget::LuaWidget(QWidget *parent): QWidget(parent) {
        auto layout = new QBoxLayout{QBoxLayout::Direction::Down, this};
        text_edit = new QTextEdit{this};
        auto btn_execute = new QPushButton{"Execute", this};
        connect(btn_execute, &QPushButton::released, this, &LuaWidget::handle_btn_execute);
        layout->addWidget(text_edit);
        layout->addWidget(btn_execute);
    }

    void LuaWidget::handle_btn_execute() {
        auto script = text_edit->toPlainText();
        try {
            lua_interface.execute_script(script.toStdString());
        } catch (const std::exception &e) {
            auto e_msg = new QMessageBox{this};
            e_msg->setText("Lua script execution failed");
            e_msg->show();
        }
    }
}
