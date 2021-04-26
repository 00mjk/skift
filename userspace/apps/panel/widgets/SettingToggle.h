#pragma once

#include <libsettings/Setting.h>
#include <libwidget/Elements.h>

namespace panel
{

class SettingToggle : public Widget::ButtonElement
{
private:
    String _name;
    RefPtr<Graphic::Icon> _icon;
    OwnPtr<Settings::Setting> _setting;
    bool _enabled;

public:
    SettingToggle(String name, RefPtr<Graphic::Icon> icon, const char *setting)
        : ButtonElement(ButtonElement::TEXT),
          _name(name),
          _icon(icon)
    {
        _setting = own<Settings::Setting>(setting, [this](auto &value) {
            _enabled = value.as_bool();
            render();
        });

        render();
    }

    ~SettingToggle()
    {
    }

    void render()
    {
        clear();

        insets({12, 12, 12, 12});

        auto icon = add(Widget::icon(_icon));
        icon->insets(Insetsi(0, 0, 0, 4));

        auto label = add(Widget::label(_name));
        label->flags(Element::FILL);

        auto sw = add(Widget::toggle(_enabled));
    }

    void event(Widget::Event *event) override
    {
        if (event->type == Widget::Event::ACTION)
        {
            _setting->write(!_enabled);
            event->accepted = true;
        }

        ButtonElement::event(event);
    }
};

} // namespace panel
