#include <stdio.h>
#include <string.h>

#include <libgraphic/Painter.h>
#include <libio/Format.h>
#include <libwidget/Placeholder.h>
#include <libwidget/Window.h>

Placeholder::Placeholder(Widget *parent, String text)
    : Widget(parent),
      _alert_icon(Graphic::Icon::get("alert"))
{
    _text = IO::format("Cannot create an instance of \"{}\".", text);
}

void Placeholder::paint(Graphic::Painter &painter, const Recti &)
{
    painter.draw_rectangle(bound(), Graphic::Colors::RED);

    painter.blit(
        *_alert_icon,
        Graphic::ICON_18PX,
        _alert_icon->bound(Graphic::ICON_18PX).moved(Vec2i(8, 8)),
        Graphic::Colors::RED);

    painter.draw_string(*font(), _text.cstring(), {32, 20}, color(THEME_FOREGROUND));
}
