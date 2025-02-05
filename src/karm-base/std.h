#pragma once

#include <new>
#include <utility>

#include "_prelude.h"
#include <initializer_list>

#ifdef __meta_freestanding__

#    include <karm-meta/signess.h>

using ssize_t = Karm::Meta::MakeSigned<size_t>;

#endif
