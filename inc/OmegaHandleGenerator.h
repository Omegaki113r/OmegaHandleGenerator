/**
 * @file OmegaHandleGenerator.h
 * @author Omegaki113r
 * @date Sunday, 21st July 2024 6:24:30 pm
 * @copyright Copyright 2024 - 2024 0m3g4ki113r, Xtronic
 * */
/*
 * Project: OmegaHandleGenerator
 * File Name: OmegaHandleGenerator.h
 * File Created: Sunday, 21st July 2024 6:24:30 pm
 * Author: Omegaki113r (omegaki113r@gmail.com)
 * -----
 * Last Modified: Monday, 22nd July 2024 1:18:24 am
 * Modified By: Omegaki113r (omegaki113r@gmail.com)
 * -----
 * Copyright 2024 - 2024 0m3g4ki113r, Xtronic
 * -----
 * HISTORY:
 * Date      	By	Comments
 * ----------	---	---------------------------------------------------------
 */

#ifndef __OMEGA_HANDLE_GENERATOR_H__
#define __OMEGA_HANDLE_GENERATOR_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

    uint64_t OmegaHandleGenerator_create_handle();
    bool OmegaHandleGenerator_delete_handle(uint64_t);

#ifdef __cplusplus
}
#endif

#endif