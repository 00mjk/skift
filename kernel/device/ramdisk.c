/* Copyright © 2018-2020 N. Van Bossuyt.                                      */
/* This code is licensed under the MIT License.                               */
/* See: LICENSE.md                                                            */

#include <libfile/tar.h>
#include <libmath/math.h>
#include <libsystem/cstring.h>
#include <libsystem/error.h>
#include <libsystem/logger.h>

#include "filesystem/Filesystem.h"
#include "multiboot.h"

void ramdisk_load(multiboot_module_t *module)
{
    // Extract the ramdisk tar archive.

    logger_info("Loading ramdisk at 0x%x...", module->mod_start);

    void *ramdisk = (void *)module->mod_start;

    tar_block_t block;
    for (size_t i = 0; tar_read(ramdisk, &block, i); i++)
    {
        Path *file_path = path_create(block.name);

        if (block.name[strlen(block.name) - 1] == '/')
        {
            int result = filesystem_mkdir(file_path);

            if (result < 0)
            {
                logger_warn("Failed to create directory %s: %s", block.name, error_to_string(-result));
            }
        }
        else
        {
            FsHandle *handle = NULL;
            error_t result = filesystem_open(file_path, OPEN_WRITE | OPEN_CREATE, &handle);

            if (result != ERR_SUCCESS)
            {
                logger_warn("Failed to open file %s! %s", block.name, error_to_string(result));
                continue;
            }

            size_t writen = 0;
            result = fshandle_write(handle, block.data, block.size, &writen);

            if (result != ERR_SUCCESS)
            {
                logger_error("Failled to write file: %s", error_to_string(result));
            }

            fshandle_destroy(handle);
        }

        path_destroy(file_path);
    }

    logger_info("Loading ramdisk succeeded.");
}
