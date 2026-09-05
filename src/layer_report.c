/*
 * layer_report.c
 *
 * Tiny ZMK event listener that prints the currently active (highest)
 * layer number over the USB logging console whenever it changes, e.g.:
 *
 *     ZMKLAYER:0
 *     ZMKLAYER:1
 *     ZMKLAYER:3
 *
 * A host-side program can watch the console/serial port for these
 * lines to know which layer is active and draw an overlay accordingly.
 *
 * zmk_keymap_highest_layer_active() already accounts for conditional
 * layers (e.g. your layer_3 that activates when layers 1 and 2 are
 * both held), so this reports the *effective* layer, not just a raw
 * bitmask.
 */

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

#include <zmk/event_manager.h>
#include <zmk/events/layer_state_changed.h>
#include <zmk/keymap.h>

LOG_MODULE_REGISTER(layer_overlay_report, LOG_LEVEL_INF);

static int layer_overlay_report_listener(const zmk_event_t *eh) {
    uint8_t layer = zmk_keymap_highest_layer_active();
    LOG_INF("ZMKLAYER:%d", layer);
    return ZMK_EV_EVENT_BUBBLE;
}

ZMK_LISTENER(layer_overlay_report, layer_overlay_report_listener);
ZMK_SUBSCRIPTION(layer_overlay_report, zmk_layer_state_changed);
