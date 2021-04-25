#include <libwidget/Container.h>
#include <libwidget/Label.h>
#include <libwidget/Spacer.h>
#include <libwidget/dialog/MessageBox.h>

namespace Widget
{

DialogResult MessageBox::create_and_show(String title, String message)
{
    return create_and_show(title, message, Graphic::Icon::get("info"), DialogButton::OK);
}

DialogResult MessageBox::create_and_show(String title, String message, RefPtr<Graphic::Icon> icon)
{
    return create_and_show(title, message, icon, DialogButton::OK);
}

DialogResult MessageBox::create_and_show(String title, String message, RefPtr<Graphic::Icon> icon, int buttons)
{
    MessageBox dialog;

    dialog.icon(icon);
    dialog.title(title);
    dialog.message(message);
    dialog.buttons(buttons);

    return dialog.show();
}

void MessageBox::render(Window *window)
{
    window->size(Math::Vec2i(300, 200));

    window->root()->layout(VFLOW(0));
    window->root()->insets(Insetsi(8));

    auto message_label = window->root()->add<Label>(_message, Anchor::CENTER);
    message_label->flags(Component::FILL);

    auto container = window->root()->add<Container>();
    container->layout(HFLOW(4));

    container->add<Spacer>();

    create_buttons(container);
}

} // namespace Widget
