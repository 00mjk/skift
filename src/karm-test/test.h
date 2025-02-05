#pragma once

#include <karm-base/loc.h>
#include <karm-base/result.h>
#include <karm-base/string.h>
#include <karm-meta/utils.h>

#include "_prelude.h"

#include "driver.h"

namespace Karm::Test {

struct Test : Meta::NoCopy, Meta::NoMove {
    using Func = Error (*)(Driver &);

    Str _name;
    Func _func;
    Loc _loc;

    Test(Str name, Func func, Loc loc = Loc::current()) : _name(name), _func(func), _loc(loc) {
        driver().add(this);
    }

    Error run(Driver &driver) {
        return _func(driver);
    }
};

}; // namespace Karm::Test
