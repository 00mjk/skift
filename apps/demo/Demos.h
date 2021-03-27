#pragma once

#include <libsystem/eventloop/Timer.h>
#include <libwidget/Application.h>
#include <libwidget/Component.h>

void colors_draw(Graphic::Painter &painter, Recti screen, float time);

void graphics_draw(Graphic::Painter &painter, Recti screen, float time);

void lines_draw(Graphic::Painter &painter, Recti screen, float time);

void path_draw(Graphic::Painter &Painter, Recti screen, float time);

typedef void (*DrawDemoCallback)(Graphic::Painter &painter, Recti screen, float time);

struct Demo
{
    const char *name;
    DrawDemoCallback callback;
};
