#include <abi/Syscalls.h>

#include <libwidget/Application.h>
#include <libwidget/Button.h>
#include <libwidget/Container.h>
#include <libwidget/IconPanel.h>
#include <libwidget/Label.h>
#include <libwidget/Panel.h>
#include <libwidget/Screen.h>
#include <libwidget/Spacer.h>

int main(int argc, char **argv)
{
    Widget::Application::initialize(argc, argv);

    Widget::Window *window = new Widget::Window(WINDOW_BORDERLESS | WINDOW_ALWAYS_FOCUSED | WINDOW_ACRYLIC | WINDOW_NO_ROUNDED_CORNERS);

    window->type(WINDOW_TYPE_POPOVER);
    window->bound(Widget::Screen::bound());
    window->opacity(0);
    window->root()->layout(STACK());

    auto background = window->root()->add<Widget::Panel>();

    background->layout(STACK());
    background->color(Widget::THEME_MIDDLEGROUND, Graphic::Colors::BLACK.with_alpha(0.5));
    background->flags(Widget::Element::FILL);

    auto dialog = background->add<Widget::Container>();

    dialog->min_width(256);
    dialog->min_height(256);
    dialog->layout(VFLOW(8));

    auto icon_and_title_container = dialog->add<Widget::Panel>();
    icon_and_title_container->layout(HFLOW(4));
    icon_and_title_container->border_radius(6);
    icon_and_title_container->insets(Insetsi{8});

    auto title_icon = icon_and_title_container->add<Widget::IconPanel>(Graphic::Icon::get("power-standby"));
    title_icon->icon_size(Graphic::ICON_36PX);

    auto warning_container = icon_and_title_container->add<Widget::Container>();
    warning_container->flags(Widget::Element::FILL);
    warning_container->layout(VGRID(2));

    warning_container->add<Widget::Label>("Shutdown or restart your computer.", Anchor::BOTTOM_LEFT);
    warning_container->add<Widget::Label>("Any unsaved work will be lost!", Anchor::TOP_LEFT);

    dialog->add<Widget::Spacer>();

    auto shutdown_button = dialog->add<Widget::Button>(Widget::Button::TEXT, Graphic::Icon::get("power-standby"), "Shutdown");

    shutdown_button->on(Widget::EventType::ACTION, [&](auto) {
        hj_system_shutdown();
    });

    auto reboot_button = dialog->add<Widget::Button>(Widget::Button::TEXT, Graphic::Icon::get("restart"), "Reboot");

    reboot_button->on(Widget::EventType::ACTION, [&](auto) {
        hj_system_reboot();
    });

    dialog->add<Widget::Button>(Widget::Button::TEXT, Graphic::Icon::get("logout"), "Logoff");

    dialog->add<Widget::Spacer>();

    auto cancel_button = dialog->add<Widget::Button>(Widget::Button::FILLED, "Cancel");

    cancel_button->on(Widget::EventType::ACTION, [&](auto) {
        window->hide();
    });

    window->on(Widget::Event::KEYBOARD_KEY_PRESS, [&](Widget::Event *event) {
        if (event->keyboard.key == KEYBOARD_KEY_ESC)
        {
            Widget::Application::exit(PROCESS_SUCCESS);
        }
    });

    window->show();

    return Widget::Application::run();
}
