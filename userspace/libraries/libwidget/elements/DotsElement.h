#pragma once

#include <libwidget/Element.h>

namespace Widget
{

class DotsElement : public Element
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

    DotsElement(int count);

    void paint(Graphic::Painter &, const Math::Recti &) override;

    Math::Vec2i size() override;
};

static inline RefPtr<DotsElement> dots(int count)
{
    return make<DotsElement>(count);
}

} // namespace  Widget
