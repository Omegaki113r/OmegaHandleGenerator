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
 * Last Modified: Monday, 22nd July 2024 1:26:53 am
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
        OMEGA_LOGE("Unable to create valid handle");
        generated_handle = 0;
        goto response;
    }
    Vector_value *inserted_handle = Vector_push_back(&handles, generated_handle);
    if (inserted_handle == NULL)
    {
        OMEGA_LOGE("Inserting handle to vector failed");
        generated_handle = 0;
    }
response:
    return generated_handle;
}

bool OmegaHandleGenerator_delete_handle(uint64_t in_handle)
{
    c_foreach(handle_iterator, Vector, handles)
    {
        if (*handle_iterator.ref == in_handle)
        {
            Vector_erase_at(&handles, handle_iterator);
            return true;
        }
    }
    return false;
}