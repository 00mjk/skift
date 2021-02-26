#pragma once

#include "kernel/devices/UNIXDevice.h"

class UnixNull : public UNIXDevice
{
private:
public:
    UnixNull(DeviceAddress address) : UNIXDevice(address, DeviceClass::NULL_)
    {
    }

    ~UnixNull() {}

    ResultOr<size_t> read(size64_t offset, void *buffer, size_t size) override
    {
        __unused(offset);
        __unused(buffer);
        __unused(size);

        return 0;
    }

    ResultOr<size_t> write(size64_t offset, const void *buffer, size_t size) override
    {
        __unused(offset);
        __unused(buffer);
        __unused(size);

        return size;
    }
};
