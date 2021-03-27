#pragma once

#include <libwidget/Widget.h>

class Image : public Widget
{
private:
    RefPtr<Graphic::Bitmap> _bitmap;
    Graphic::BitmapScaling _scaling = Graphic::BitmapScaling::FIT;

public:
    Image(Widget *parent, RefPtr<Graphic::Bitmap> bitmap);

    Image(Widget *parent, RefPtr<Graphic::Bitmap> bitmap, Graphic::BitmapScaling scaling);

    void change_bitmap(RefPtr<Graphic::Bitmap> bitmap);

    void scaling(Graphic::BitmapScaling scaling);

    void paint(Graphic::Painter &, const Recti &) override;

    virtual Vec2i size() override;
};
