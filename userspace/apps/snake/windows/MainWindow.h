#pragma once

#include <libwidget/TitleBar.h>
#include <libwidget/Window.h>

#include "libgraphic/Icon.h"
#include "snake/widgets/BoardWidget.h"

namespace Snake
{

class MainWindow : public Widget::Window
{
private:
public:
    MainWindow()
        : Window{WINDOW_NONE}
    {
        root()->layout(VFLOW(0));

        new Widget::TitleBar(
            root(),
            Graphic::Icon::get("snake"),
            "Snake");

        auto board = new BoardWidget(root());
        board->outsets({32});
        board->focus();

        resize_to_content();
    }

    ~MainWindow()
    {
    }
};

} // namespace Snake
