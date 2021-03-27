#pragma once

#include <libgraphic/Icon.h>
#include <libwidget/Widget.h>

class IconPanel : public Widget
{
private:
    RefPtr<Graphic::Icon> _icon;
    Graphic::IconSize _icon_size = Graphic::ICON_18PX;

public:
    void icon_size(Graphic::IconSize size) { _icon_size = size; }

    IconPanel(Widget *parent, RefPtr<Graphic::Icon> icon);

    void paint(Graphic::Painter &, const Recti &) override;

    Vec2i size() override;
};
