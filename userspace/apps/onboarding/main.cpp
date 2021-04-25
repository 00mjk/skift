#include <libio/Format.h>
#include <libwidget/Application.h>
#include <libwidget/Button.h>
#include <libwidget/Container.h>
#include <libwidget/Elements.h>
#include <libwidget/Label.h>
#include <libwidget/PaginationDots.h>
#include <libwidget/Screen.h>

struct Page
{
    String header;
    Vector<String> lines;
    String footer;
};

static const Vector<Page> PAGES = {
    {
        "Welcome to skiftOS!",
        {
            "skiftOS is a simple, handmade operating system for the x86 platform,",
            "aiming for clean and pretty APIs while keeping the spirit of UNIX.",
        },
        "You can skip at any time and start using skiftOS.",
    },
    {
        "Getting Started!",
        {
            "Click on the top left of the screen to bring up the application menu.",
            "Try out the terminal with familiar unix utilities.",
        },
        "Explore, experiment and enjoy.",
    },
    {
        "Join The Community.",
        {
            "The community is full of great people, join us on:",
            "Github, Discord, and Twitter #skiftOS.",
        },
        "https://skiftos.org/community",
    },
    {
        "Contribute to the project",
        {
            "Do you like skiftOS and want it to become even better?",
            "Then there are many way to contribute to the project:",
            "contributing code, reporting issues, donations, and sponsorship",
        },
        "https://skiftos.org/contributing",
    },
    {
        "All Done!",
        {
            "Thanks for choosing skiftOS!",
        },
        "<3",
    },
};

void pages(RefPtr<Widget::Element> host, const Page &page)
{
    host->add<Widget::Label>(page.header, Anchor::CENTER);

    auto content = host->add<Widget::Container>();
    content->insets({8, 0});
    content->layout(VFLOW(2));

    for (auto &lines : page.lines)
    {
        content->add<Widget::Label>(lines, Anchor::CENTER);
    }

    host->add<Widget::Label>(page.footer, Anchor::CENTER);
}

int main(int, char **)
{
    Widget::Window *window = new Widget::Window(WINDOW_BORDERLESS | WINDOW_ALWAYS_FOCUSED | WINDOW_ACRYLIC | WINDOW_NO_ROUNDED_CORNERS);

    window->type(WINDOW_TYPE_POPOVER);
    window->bound(Widget::Screen::bound());
    window->opacity(0);
    window->show();
    window->root()->layout(STACK());

    auto background = window->root()->add(Widget::panel());

    background->layout(STACK());
    background->color(Widget::THEME_MIDDLEGROUND, Graphic::Colors::BLACK.with_alpha(0.5));
    background->flags(Widget::Element::FILL);

    auto dialog = background->add(Widget::panel(6));

    dialog->pin_width(420);
    dialog->pin_height(420);

    dialog->layout(VFLOW(0));

    auto illustration = dialog->add(Widget::panel(6));
    illustration->min_height(160);
    illustration->color(Widget::THEME_MIDDLEGROUND, Graphic::Colors::WHITE);

    auto image = Widget::image(Graphic::Bitmap::placeholder(), Graphic::BitmapScaling::CENTER);
    illustration->add(image);
    image->flags(Widget::Element::FILL);

    auto content = dialog->add<Widget::Container>();
    content->flags(Widget::Element::FILL);
    content->insets(16);
    content->layout(VFLOW(4));

    auto dots_container = dialog->add<Widget::Container>();
    dots_container->insets(16);

    auto dots = dots_container->add<Widget::PaginationDots>(5);

    auto navigation = dialog->add<Widget::Container>();

    navigation->layout(HFLOW(4));
    navigation->insets(8);

    auto skipall_button = navigation->add<Widget::Button>(Widget::Button::TEXT, "Skip All");

    navigation->add(Widget::spacer());

    auto back_button = navigation->add<Widget::Button>(Widget::Button::OUTLINE, "Previous");

    auto next_button = navigation->add<Widget::Button>(Widget::Button::FILLED, "Next");

    int current_page = 0;

    auto set_current_page = [&](int index) {
        if (index == 5)
        {
            Widget::Application::the()->exit(PROCESS_SUCCESS);
        }

        if (index < 0 || index > 4)
        {
            return;
        }

        current_page = index;

        skipall_button->enable_if(current_page < 4);
        back_button->enable_if(current_page > 0);
        dots->index(index);

        auto image_path = IO::format("/Applications/onboarding/illustration{}.png", index);
        image->change_bitmap(Graphic::Bitmap::load_from(image_path).unwrap());

        content->clear();
        pages(content, PAGES[index]);
    };

    set_current_page(0);

    skipall_button->on(Widget::Event::ACTION, [](auto) {
        Widget::Application::the()->exit(PROCESS_SUCCESS);
    });

    back_button->on(Widget::Event::ACTION, [&](auto) {
        set_current_page(current_page - 1);
    });

    next_button->on(Widget::Event::ACTION, [&](auto) {
        set_current_page(current_page + 1);
    });

    window->on(Widget::Event::KEYBOARD_KEY_PRESS, [&](Widget::Event *event) {
        if (event->keyboard.key == KEYBOARD_KEY_ESC)
        {
            Widget::Application::the()->exit(PROCESS_SUCCESS);
        }
        else if (event->keyboard.key == KEYBOARD_KEY_RIGHT)
        {
            set_current_page(current_page + 1);
        }
        else if (event->keyboard.key == KEYBOARD_KEY_LEFT)
        {
            set_current_page(current_page - 1);
        }
    });

    return Widget::Application::the()->run();
}
