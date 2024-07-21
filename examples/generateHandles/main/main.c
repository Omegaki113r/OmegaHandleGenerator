#include <stdio.h>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "OmegaBaseLoggingController.h"
#include "OmegaHandleGenerator.h"

void app_main(void)
{
    for (;;)
    {
        uint64_t handle = OmegaHandleGenerator_create_handle();
        OMEGA_LOGD("Generated handle: %llu", handle);
        if (OmegaHandleGenerator_delete_handle(handle))
        {
            OMEGA_LOGI("Handle delete success");
        }
        else
        {
            OMEGA_LOGE("Handle delete failed");
        }
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
