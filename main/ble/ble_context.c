#include "ble_context.h"
#include "ble_gap.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_bt.h"

#include "esp_gatts_api.h"
#include "esp_bt_defs.h"
#include "esp_bt_main.h"
#include "esp_gatt_common_api.h"

#include "sdkconfig.h"

#define GATTS_TAG "GATTS_DEMO"

typedef struct ble_context_t
{
    ble_context base;
    ble_gap *gap;
} ble_context_t;

static void ble_context_t_init(ble_context_t *p);
static void ble_context_t_deinit(ble_context_t *p);
static void ble_context_t_dealloc(ble_context_t *p);
static void ble_context_setup(ble_context *obj);

static void ble_context_t_init(ble_context_t *p)
{
    object_init(&p->base.base);
    p->base.base.dealloc = (object_dealloc) ble_context_t_dealloc;
    p->base.setup = ble_context_setup;
    p->gap = NULL;
}

static void ble_context_t_deinit(ble_context_t *p)
{
    if (p->gap) {
        RELEASE(&p->gap->base);
        p->gap = NULL;
    }
}

static void ble_context_t_dealloc(ble_context_t *p)
{
    ble_context_t_deinit(p);
    free(p);
}

ble_context *ble_context_create()
{
    ble_context_t *p = (ble_context_t *)malloc(sizeof(ble_context_t));
    ble_context_t_init(p);
    return &p->base;
}

static esp_err_t __setup_controller()
{
    esp_err_t ret;

    ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK( ret );

    ESP_ERROR_CHECK(esp_bt_controller_mem_release(ESP_BT_MODE_CLASSIC_BT));

    esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
    ret = esp_bt_controller_init(&bt_cfg);
    if (ret) {
        ESP_LOGE(GATTS_TAG, "%s initialize controller failed: %s\n", __func__, esp_err_to_name(ret));
        return ret;
    }

    ret = esp_bt_controller_enable(ESP_BT_MODE_BLE);
    if (ret) {
        ESP_LOGE(GATTS_TAG, "%s enable controller failed: %s\n", __func__, esp_err_to_name(ret));
        return ret;
    }
    ret = esp_bluedroid_init();
    if (ret) {
        ESP_LOGE(GATTS_TAG, "%s init bluetooth failed: %s\n", __func__, esp_err_to_name(ret));
        return ret;
    }
    ret = esp_bluedroid_enable();
    if (ret) {
        ESP_LOGE(GATTS_TAG, "%s enable bluetooth failed: %s\n", __func__, esp_err_to_name(ret));
        return ret;
    }

    return ret;
}

static void ble_context_setup(ble_context *obj)
{
    ble_context_t *p = (ble_context_t *)obj;

    esp_err_t ret;
    ret = __setup_controller();
    if (ret) return;

    p->gap = ble_gap_create();
}