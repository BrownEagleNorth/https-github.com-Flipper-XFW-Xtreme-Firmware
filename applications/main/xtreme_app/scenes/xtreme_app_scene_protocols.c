#include "../xtreme_app.h"

enum VarItemListIndex {
    VarItemListIndexBadkbMode,
    VarItemListIndexBadbtRemember,
    VarItemListIndexSubghzFreqs,
    VarItemListIndexSubghzExtend,
};

void xtreme_app_scene_protocols_var_item_list_callback(void* context, uint32_t index) {
    XtremeApp* app = context;
    view_dispatcher_send_custom_event(app->view_dispatcher, index);
}

static void xtreme_app_scene_protocols_bad_bt_changed(VariableItem* item) {
    XtremeApp* app = variable_item_get_context(item);
    bool value = variable_item_get_current_value_index(item);
    variable_item_set_current_value_text(item, value ? "BT" : "USB");
    XTREME_SETTINGS()->bad_bt = value;
    app->save_settings = true;
}

static void xtreme_app_scene_protocols_bad_bt_remember_changed(VariableItem* item) {
    XtremeApp* app = variable_item_get_context(item);
    bool value = variable_item_get_current_value_index(item);
    variable_item_set_current_value_text(item, value ? "ON" : "OFF");
    XTREME_SETTINGS()->bad_bt_remember = value;
    app->save_settings = true;
}

static void xtreme_app_scene_protocols_subghz_extend_changed(VariableItem* item) {
    XtremeApp* app = variable_item_get_context(item);
    app->subghz_extend = variable_item_get_current_value_index(item);
    variable_item_set_current_value_text(item, app->subghz_extend ? "ON" : "OFF");
    app->save_subghz = true;
}

static void xtreme_app_scene_protocols_cc1101_handle_changed(VariableItem* item) {
    XtremeApp* app = variable_item_get_context(item);
    XTREME_SETTINGS()->spi_cc1101_handle =
        variable_item_get_current_value_index(item) == 0 ? SpiDefault : SpiExtra;
    variable_item_set_current_value_text(
        item, XTREME_SETTINGS()->spi_cc1101_handle == SpiDefault ? "Default" : "Extra");
    app->save_settings = true;
}

static void xtreme_app_scene_protocols_nrf24_handle_changed(VariableItem* item) {
    XtremeApp* app = variable_item_get_context(item);
    XTREME_SETTINGS()->spi_nrf24_handle =
        variable_item_get_current_value_index(item) == 0 ? SpiDefault : SpiExtra;
    variable_item_set_current_value_text(
        item, XTREME_SETTINGS()->spi_nrf24_handle == SpiDefault ? "Default" : "Extra");
    app->save_settings = true;
}

static void xtreme_app_scene_protocols_esp32_channel_changed(VariableItem* item) {
    XtremeApp* app = variable_item_get_context(item);
    XTREME_SETTINGS()->uart_esp_channel =
        variable_item_get_current_value_index(item) == 0 ? UARTDefault : UARTExtra;
    variable_item_set_current_value_text(
        item, XTREME_SETTINGS()->uart_esp_channel == UARTDefault ? "13,14" : "15,16");
    app->save_settings = true;
}

static void xtreme_app_scene_protocols_nmea_channel_changed(VariableItem* item) {
    XtremeApp* app = variable_item_get_context(item);
    XTREME_SETTINGS()->uart_nmea_channel =
        variable_item_get_current_value_index(item) == 0 ? UARTDefault : UARTExtra;
    variable_item_set_current_value_text(
        item, XTREME_SETTINGS()->uart_nmea_channel == UARTDefault ? "13,14" : "15,16");
    app->save_settings = true;
}

static void xtreme_app_scene_protocols_general_channel_changed(VariableItem* item) {
    XtremeApp* app = variable_item_get_context(item);
    XTREME_SETTINGS()->uart_general_channel =
        variable_item_get_current_value_index(item) == 0 ? UARTDefault : UARTExtra;
    variable_item_set_current_value_text(
        item, XTREME_SETTINGS()->uart_general_channel == UARTDefault ? "13,14" : "15,16");
    app->save_settings = true;
}

void xtreme_app_scene_protocols_on_enter(void* context) {
    XtremeApp* app = context;
    XtremeSettings* xtreme_settings = XTREME_SETTINGS();
    VariableItemList* var_item_list = app->var_item_list;
    VariableItem* item;

    item = variable_item_list_add(
        var_item_list, "BadKB Mode", 2, xtreme_app_scene_protocols_bad_bt_changed, app);
    variable_item_set_current_value_index(item, xtreme_settings->bad_bt);
    variable_item_set_current_value_text(item, xtreme_settings->bad_bt ? "BT" : "USB");

    item = variable_item_list_add(
        var_item_list,
        "BadBT Remember",
        2,
        xtreme_app_scene_protocols_bad_bt_remember_changed,
        app);
    variable_item_set_current_value_index(item, xtreme_settings->bad_bt_remember);
    variable_item_set_current_value_text(item, xtreme_settings->bad_bt_remember ? "ON" : "OFF");

    item = variable_item_list_add(var_item_list, "SubGHz Freqs", 0, NULL, app);
    variable_item_set_current_value_text(item, ">");

    item = variable_item_list_add(
        var_item_list, "SubGHz Extend", 2, xtreme_app_scene_protocols_subghz_extend_changed, app);
    variable_item_set_current_value_index(item, app->subghz_extend);
    variable_item_set_current_value_text(item, app->subghz_extend ? "ON" : "OFF");

    item = variable_item_list_add(
        var_item_list,
        "SPI CC1101 Handle",
        2,
        xtreme_app_scene_protocols_cc1101_handle_changed,
        app);
    variable_item_set_current_value_index(item, xtreme_settings->spi_cc1101_handle);
    variable_item_set_current_value_text(
        item, xtreme_settings->spi_cc1101_handle == SpiDefault ? "Default" : "Extra");

    item = variable_item_list_add(
        var_item_list, "SPI NRF24 Handle", 2, xtreme_app_scene_protocols_nrf24_handle_changed, app);
    variable_item_set_current_value_index(item, xtreme_settings->spi_nrf24_handle);
    variable_item_set_current_value_text(
        item, xtreme_settings->spi_nrf24_handle == SpiDefault ? "Default" : "Extra");

    item = variable_item_list_add(
        var_item_list,
        "UART ESP32/ESP8266 Channel",
        2,
        xtreme_app_scene_protocols_esp32_channel_changed,
        app);
    variable_item_set_current_value_index(item, xtreme_settings->uart_esp_channel);
    variable_item_set_current_value_text(
        item, xtreme_settings->uart_esp_channel == UARTDefault ? "13,14" : "15,16");

    item = variable_item_list_add(
        var_item_list,
        "UART NMEA Channel",
        2,
        xtreme_app_scene_protocols_nmea_channel_changed,
        app);
    variable_item_set_current_value_index(item, xtreme_settings->uart_nmea_channel);
    variable_item_set_current_value_text(
        item, xtreme_settings->uart_nmea_channel == UARTDefault ? "13,14" : "15,16");

    item = variable_item_list_add(
        var_item_list,
        "UART General Channel",
        2,
        xtreme_app_scene_protocols_general_channel_changed,
        app);
    variable_item_set_current_value_index(item, xtreme_settings->uart_general_channel);
    variable_item_set_current_value_text(
        item, xtreme_settings->uart_general_channel == UARTDefault ? "13,14" : "15,16");

    variable_item_list_set_enter_callback(
        var_item_list, xtreme_app_scene_protocols_var_item_list_callback, app);

    variable_item_list_set_selected_item(
        var_item_list, scene_manager_get_scene_state(app->scene_manager, XtremeAppSceneProtocols));

    view_dispatcher_switch_to_view(app->view_dispatcher, XtremeAppViewVarItemList);
}

bool xtreme_app_scene_protocols_on_event(void* context, SceneManagerEvent event) {
    XtremeApp* app = context;
    bool consumed = false;

    if(event.type == SceneManagerEventTypeCustom) {
        scene_manager_set_scene_state(app->scene_manager, XtremeAppSceneProtocols, event.event);
        consumed = true;
        switch(event.event) {
        case VarItemListIndexSubghzFreqs:
            scene_manager_next_scene(app->scene_manager, XtremeAppSceneProtocolsFreqs);
            break;
        default:
            break;
        }
    }

    return consumed;
}

void xtreme_app_scene_protocols_on_exit(void* context) {
    XtremeApp* app = context;
    variable_item_list_reset(app->var_item_list);
}
