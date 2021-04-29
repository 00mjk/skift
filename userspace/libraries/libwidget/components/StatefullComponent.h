#pragma once

#include <libwidget/components/Component.h>

namespace Widget
{

template <typename TState>
class StatefullComponent : public Component
{
private:
    TState _state = {};

public:
    void state(TState state)
    {
        _state = state;
        should_rebuild();
    }

    const TState &state()
    {
        return _state;
    }
};

} // namespace Widget
