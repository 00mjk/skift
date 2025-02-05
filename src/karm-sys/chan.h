#pragma once

#include <embed/sys.h>
#include <karm-fmt/fmt.h>
#include <karm-io/traits.h>

#include "fd.h"

namespace Karm::Sys {

struct In : public Io::Reader {
    Strong<Fd> _fd;

    In(Strong<Fd> fd) : _fd(fd) {}

    Result<size_t> read(void *data, size_t size) override {
        return _fd->read(data, size);
    }
};

struct Out : public Io::Writer {
    Strong<Fd> _fd;

    Out(Strong<Fd> fd) : _fd(fd) {}

    Result<size_t> write(void const *data, size_t size) override {
        return _fd->write(data, size);
    }
};

struct Err : public Io::Writer {
    Strong<Fd> _fd;

    Err(Strong<Fd> fd) : _fd(fd) {}

    Result<size_t> write(void const *data, size_t size) override {
        return _fd->write(data, size);
    }
};

In &in();

Out &out();

Err &err();

static inline void println(Str str, auto &&...args) {
    (void)Fmt::format(out(), str, std::forward<decltype(args)>(args)...);
    (void)Io::putc(out(), '\n');
}

static inline void errln(Str str, auto &&...args) {
    (void)Fmt::format(err(), str, std::forward<decltype(args)>(args)...);
    (void)Io::putc(err(), '\n');
}

} // namespace Karm::Sys
