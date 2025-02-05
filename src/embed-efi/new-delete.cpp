#include <efi/base.h>
#include <efi/spec.h>

void *__attribute__((weak)) operator new(size_t size) {
    void *res = nullptr;
    Efi::st()->boot->allocatePool(Efi::MemoryType::BOOT_SERVICES_DATA, size, &res).unwrap();
    return res;
}

void *__attribute__((weak)) operator new[](size_t size) {
    void *res = nullptr;
    Efi::st()->boot->allocatePool(Efi::MemoryType::BOOT_SERVICES_DATA, size, &res).unwrap();
    return res;
}

void __attribute__((weak)) operator delete(void *ptr) {
    Efi::st()->boot->freePool(ptr).unwrap();
}

void __attribute__((weak)) operator delete[](void *ptr) {
    Efi::st()->boot->freePool(ptr).unwrap();
}

void __attribute__((weak)) operator delete(void *ptr, size_t) {
    Efi::st()->boot->freePool(ptr).unwrap();
}

void __attribute__((weak)) operator delete[](void *ptr, size_t) {
    Efi::st()->boot->freePool(ptr).unwrap();
}
