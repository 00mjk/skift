#include "libio/Format.h"
#include "libio/Path.h"
#include <libsystem/Logger.h>
#include <libwidget/Application.h>
#include <libwidget/Button.h>
#include <libwidget/Panel.h>
#include <libwidget/TextEditor.h>
#include <libwidget/TitleBar.h>

int main(int argc, char **argv)
{
    Widget::Application::initialize(argc, argv);

    Widget::Window *window = new Widget::Window(WINDOW_RESIZABLE);
    window->size(Math::Vec2i(700, 500));
    window->root()->layout(VFLOW(0));

    if (argc == 2)
    {
        new Widget::TitleBar(
            window->root(),
            Graphic::Icon::get("text-box"),
            IO::format("Text Editor · {}", IO::Path::parse(argv[1]).basename()));
    }
    else
    {
        new Widget::TitleBar(
            window->root(),
            Graphic::Icon::get("text-box"),
            "Text Editor");
    }

    auto *toolbar = new Widget::Panel(window->root());

    toolbar->layout(HFLOW(4));
    toolbar->insets(Insetsi(4, 4));

    new Widget::Button(toolbar, Widget::Button::TEXT, Graphic::Icon::get("folder-open"));
    new Widget::Button(toolbar, Widget::Button::TEXT, Graphic::Icon::get("content-save"));
    new Widget::Button(toolbar, Widget::Button::TEXT, Graphic::Icon::get("file-plus"));

    auto model = Widget::TextModel::empty();

    if (argc == 2)
    {
        logger_info("Opening text document from '%s'", argv[1]);
        model = Widget::TextModel::from_file(argv[1]);
    }

    auto *field = new Widget::TextEditor(window->root(), model);
    field->flags(Widget::Component::FILL);
    field->overscroll(true);
    field->insets({4});
    field->focus();

    window->show();

    return Widget::Application::run();
}
