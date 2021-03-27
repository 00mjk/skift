#pragma once

#include <libwidget/Component.h>

namespace Widget
{

class PaginationDots : public Component
{
private:
    int _count = 3;
    int _index = 0;

public:
    static constexpr int DOTSIZE = 4;
    static constexpr int DOTSPACING = 8;

    int count() const { return _count; }

    void count(int count)
    {
        _count = count;
        max_width(size().x());
        should_relayout();
        should_repaint();
    }

    int index() const { return _index; }

    void index(int index)
    {
        should_repaint();
        _index = index;
    }

    PaginationDots(Component *parent, int count);

    ~PaginationDots() override;

    void paint(Graphic::Painter &, const Recti &) override;

    Vec2i size() override;
};

} // namespace  Widget
