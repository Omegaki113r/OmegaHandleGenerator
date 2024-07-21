/**
 * @file OmegaHandleGenerator.c
 * @author Omegaki113r
 * @date Sunday, 21st July 2024 6:28:31 pm
 * @copyright Copyright 2024 - 2024 0m3g4ki113r, Xtronic
 * */
/*
 * Project: OmegaHandleGenerator
 * File Name: OmegaHandleGenerator.c
 * File Created: Sunday, 21st July 2024 6:28:31 pm
 * Author: Omegaki113r (omegaki113r@gmail.com)
 * -----
 * Last Modified: Monday, 22nd July 2024 2:13:17 am
 * Modified By: Omegaki113r (omegaki113r@gmail.com)
 * -----
 * Copyright 2024 - 2024 0m3g4ki113r, Xtronic
 * -----
 * HISTORY:
 * Date      	By	Comments
 * ----------	---	---------------------------------------------------------
 *
 * 22-07-2024	0m3g4	OmegaHandleGenerator_create_handle and OmegaHandleGenerator_delete_handle added
 */

#include "OmegaHandleGenerator.h"
#include "OmegaBaseLoggingController.h"
#include "OmegaUtilityDriver.h"

#if __has_include(<sdkconfig.h>)
#include <sdkconfig.h>

#if CONFIG_OMEGA_HANDLE_GENERATOR_VERBOSE
#define OMEGA_HANDLE_GENERATOR_LOGV(format, ...) OMEGA_LOGV(format, ##__VA_ARGS__)
#define OMEGA_HANDLE_GENERATOR_HEX_LOGV(format, ...) OMEGA_HEX_LOGV(format, ##__VA_ARGS__)
#else
#define OMEGA_HANDLE_GENERATOR_LOGV(format, ...)
#define OMEGA_HANDLE_GENERATOR_HEX_LOGV(format, ...)
#endif

#if CONFIG_OMEGA_HANDLE_GENERATOR_DEBUG
#define OMEGA_HANDLE_GENERATOR_LOGD(format, ...) OMEGA_LOGD(format, ##__VA_ARGS__)
#define OMEGA_HANDLE_GENERATOR_HEX_LOGD(format, ...) OMEGA_HEX_LOGD(format, ##__VA_ARGS__)
#else
#define OMEGA_HANDLE_GENERATOR_LOGD(format, ...)
#define OMEGA_HANDLE_GENERATOR_HEX_LOGD(format, ...)
#endif

#if CONFIG_OMEGA_HANDLE_GENERATOR_INFO
#define OMEGA_HANDLE_GENERATOR_LOGI(format, ...) OMEGA_LOGI(format, ##__VA_ARGS__)
#define OMEGA_HANDLE_GENERATOR_HEX_LOGI(format, ...) OMEGA_HEX_LOGI(format, ##__VA_ARGS__)
#else
#define OMEGA_HANDLE_GENERATOR_LOGI(format, ...)
#define OMEGA_HANDLE_GENERATOR_HEX_LOGI(format, ...)
#endif

#if CONFIG_OMEGA_HANDLE_GENERATOR_WARN
#define OMEGA_HANDLE_GENERATOR_LOGW(format, ...) OMEGA_LOGW(format, ##__VA_ARGS__)
#define OMEGA_HANDLE_GENERATOR_HEX_LOGW(format, ...) OMEGA_HEX_LOGW(format, ##__VA_ARGS__)
#else
#define OMEGA_HANDLE_GENERATOR_LOGW(format, ...)
#define OMEGA_HANDLE_GENERATOR_HEX_LOGW(format, ...)
#endif

#if CONFIG_OMEGA_HANDLE_GENERATOR_ERROR
#define OMEGA_HANDLE_GENERATOR_LOGE(format, ...) OMEGA_LOGE(format, ##__VA_ARGS__)
#define OMEGA_HANDLE_GENERATOR_HEX_LOGE(format, ...) OMEGA_HEX_LOGE(format, ##__VA_ARGS__)
#else
#define OMEGA_HANDLE_GENERATOR_LOGE(format, ...)
#define OMEGA_HANDLE_GENERATOR_HEX_LOGE(format, ...)
#endif

#if CONFIG_OMEGA_FILE_SUSTEM_CONTROLLER_PROFILE
#define OMEGA_HANDLE_GENERATOR_PROFILE_START(name) PROFILE_START(name)
#define OMEGA_HANDLE_GENERATOR_PROFILE_END() PROFILE_END()
#else
#define OMEGA_HANDLE_GENERATOR_PROFILE_START(name)
#define OMEGA_HANDLE_GENERATOR_PROFILE_END()
#endif

#endif

#define MAX_ITERATION_AMOUNT 100

#define RAND() (rand() & 0x7fff)

#define i_TYPE Vector, u64
#include <vec.h>

static Vector handles;

uint64_t OmegaHandleGenerator_create_handle()
{
    u64 iteration_count = 0;
    u64 generated_handle = 0;
    do
    {
    regenerate_handle:
        generated_handle = ((u64)RAND() << 48) ^ ((u64)RAND() << 35) ^ ((u64)RAND() << 22) ^
                           ((u64)RAND() << 9) ^ ((u64)RAND() >> 4);
        c_foreach(handle_iterator, Vector, handles)
        {
            if (generated_handle == *handle_iterator.ref)
                goto regenerate_handle;
        }
    } while (generated_handle <= 0 && iteration_count++ < MAX_ITERATION_AMOUNT);
    if (iteration_count >= MAX_ITERATION_AMOUNT)
    {
        OMEGA_HANDLE_GENERATOR_LOGE("Unable to create valid handle");
        generated_handle = 0;
        goto response;
    }
    Vector_value *inserted_handle = Vector_push_back(&handles, generated_handle);
    if (inserted_handle == NULL)
    {
        OMEGA_HANDLE_GENERATOR_LOGE("Inserting handle to vector failed");
        generated_handle = 0;
    }
response:
    OMEGA_HANDLE_GENERATOR_LOGV("Generated Handle: %llu, Vector Size: %d", generated_handle, Vector_size(&handles));
    return generated_handle;
}

bool OmegaHandleGenerator_delete_handle(uint64_t in_handle)
{
    bool ret = false;
    c_foreach(handle_iterator, Vector, handles)
    {
        if (*handle_iterator.ref == in_handle)
        {
            Vector_erase_at(&handles, handle_iterator);
            ret = true;
            goto response;
        }
    }
response:
    OMEGA_HANDLE_GENERATOR_LOGV("Deleting Handle: %llu, Vector Size: %d", in_handle, Vector_size(&handles));
    return ret;
}