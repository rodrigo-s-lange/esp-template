#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef ESP_COMPONENT_INIT_FLAGS_DEFINED
#define ESP_COMPONENT_INIT_FLAGS_DEFINED
typedef enum {
    ESP_INIT_NONE = 0,
    ESP_INIT_AT = (1U << 0),
    ESP_INIT_LOG = (1U << 1),
} esp_component_init_flags_t;
#endif

/**
 * @brief Runtime configuration for the component.
 *
 * Replace this structure with fields that describe capability-oriented
 * configuration. Do not leak backend implementation details into the
 * public API unless there is a strong architectural reason.
 */
typedef struct {
    int placeholder_field;
} esp_your_component_config_t;

/**
 * @brief Initialize the component with the provided init flags.
 *
 * Public init contract:
 * - reject double init with ESP_ERR_INVALID_STATE
 * - do not allocate hidden long-lived resources you cannot release in deinit()
 * - AT is optional; if unsupported, runtime should reject it before calling init
 *
 * @param flags Bitwise OR of @ref esp_component_init_flags_t values.
 * @return
 *      - ESP_OK on success
 *      - ESP_ERR_INVALID_STATE if already initialized or if AT was requested
 *        before the AT subsystem was initialized
 *      - Another error code if initialization fails
 */
esp_err_t esp_your_component_init_flags(uint32_t flags);

#define ESP_YOUR_COMPONENT_INIT_SELECT(_1, _2, NAME, ...) NAME
#define ESP_YOUR_COMPONENT_INIT_ONE(flags) esp_your_component_init_flags((uint32_t)(flags))
#define ESP_YOUR_COMPONENT_INIT_TWO(flag_a, flag_b) esp_your_component_init_flags((uint32_t)(flag_a) | (uint32_t)(flag_b))
#define esp_your_component_init(...) \
    ESP_YOUR_COMPONENT_INIT_SELECT(__VA_ARGS__, ESP_YOUR_COMPONENT_INIT_TWO, ESP_YOUR_COMPONENT_INIT_ONE)(__VA_ARGS__)

/**
 * @brief Deinitialize the component and release all owned resources.
 *
 * @return
 *      - ESP_OK on success
 *      - ESP_ERR_INVALID_STATE if the component is not initialized
 */
esp_err_t esp_your_component_deinit(void);

/**
 * @brief Check whether the component is initialized.
 *
 * @return true when initialized, otherwise false.
 */
bool esp_your_component_is_initialized(void);

/**
 * @brief Apply runtime configuration to the component.
 *
 * Keep the public API capability-oriented.
 * Do not leak backend names like LEDC, RMT, SPI2_HOST, GPTimer, or similar
 * backend details into the public contract.
 *
 * @param config Pointer to a validated configuration structure.
 * @return
 *      - ESP_OK on success
 *      - ESP_ERR_INVALID_ARG if @p config is invalid
 *      - ESP_ERR_INVALID_STATE if the component is not initialized
 */
esp_err_t esp_your_component_configure(const esp_your_component_config_t *config);

#ifdef __cplusplus
}
#endif
