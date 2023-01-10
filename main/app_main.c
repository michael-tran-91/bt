#include "ble/ble_context.h"
#include "esp_gap_ble_api.h"

static ble_context *ctx;

static void gap_event_handler(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t *param)
{

}

void app_main()
{
    ctx = ble_context_create();
    ctx->setup(ctx);

    esp_ble_gap_register_callback(gap_event_handler);
}