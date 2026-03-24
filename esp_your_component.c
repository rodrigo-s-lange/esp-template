#include <ctype.h>
#include <string.h>

#include "esp_at.h"
#include "esp_log.h"

#include "esp_your_component.h"

static const char *TAG = "esp_your_component";

static bool s_initialized = false;
static bool s_log_enabled = false;
static bool s_at_enabled = false;

#define YOUR_LOGI(...) do { if (s_log_enabled) ESP_LOGI(TAG, __VA_ARGS__); } while (0)
#define YOUR_LOGW(...) do { if (s_log_enabled) ESP_LOGW(TAG, __VA_ARGS__); } while (0)
#define YOUR_LOGE(...) do { if (s_log_enabled) ESP_LOGE(TAG, __VA_ARGS__); } while (0)

static esp_err_t register_at_commands(void);
static void unregister_at_commands(void);
static void handle_at_your_query(const char *param);
static void handle_at_your(const char *param);

/**
 * @brief Trim leading and trailing whitespace in-place.
 *
 * @param s Mutable string buffer.
 * @return Pointer to the trimmed string or NULL if @p s is NULL.
 */
static char *trim_ws(char *s)
{
    if (s == NULL) return NULL;
    while (*s != '\0' && isspace((unsigned char)*s)) s++;
    size_t n = strlen(s);
    while (n > 0 && isspace((unsigned char)s[n - 1])) {
        s[n - 1] = '\0';
        n--;
    }
    return s;
}

/**
 * @brief Compare two strings case-insensitively.
 *
 * @param a First string.
 * @param b Second string.
 * @return true if both strings are equal ignoring ASCII case.
 */
static bool ci_equals(const char *a, const char *b)
{
    if (a == NULL || b == NULL) return false;
    while (*a != '\0' && *b != '\0') {
        if (toupper((unsigned char)*a) != toupper((unsigned char)*b)) return false;
        a++;
        b++;
    }
    return *a == '\0' && *b == '\0';
}

esp_err_t esp_your_component_init_flags(uint32_t flags)
{
    bool log_enabled = (flags & ESP_INIT_LOG) != 0U;
    bool at_enabled = (flags & ESP_INIT_AT) != 0U;

    if (s_initialized) return ESP_ERR_INVALID_STATE;
    if (at_enabled && !esp_at_is_initialized()) return ESP_ERR_INVALID_STATE;

    s_log_enabled = log_enabled;
    s_at_enabled = at_enabled;
    s_initialized = true;

    if (s_at_enabled) {
        esp_err_t err = register_at_commands();
        if (err != ESP_OK) {
            s_initialized = false;
            s_log_enabled = false;
            s_at_enabled = false;
            return err;
        }
    }

    YOUR_LOGI("initialized (AT=%s)", s_at_enabled ? "on" : "off");
    return ESP_OK;
}

esp_err_t esp_your_component_deinit(void)
{
    if (!s_initialized) return ESP_ERR_INVALID_STATE;

    /*
     * Release every resource owned by this component here.
     * Examples:
     * - AT commands
     * - tasks
     * - timers
     * - queues
     * - mutexes
     * - GPIO ownership via esp_pins
     * - bus/device handles
     */
    unregister_at_commands();

    s_initialized = false;
    s_log_enabled = false;
    s_at_enabled = false;
    return ESP_OK;
}

bool esp_your_component_is_initialized(void)
{
    return s_initialized;
}

esp_err_t esp_your_component_configure(const esp_your_component_config_t *config)
{
    if (!s_initialized || config == NULL) return ESP_ERR_INVALID_ARG;

    /*
     * Validate every public argument.
     * Roll back partial state on failure.
     * Do not abort the firmware with ESP_ERROR_CHECK() here.
     */
    return ESP_OK;
}

static esp_err_t register_at_commands(void)
{
    esp_err_t err = esp_at_register_cmd_example("AT+YOUR?", handle_at_your_query, "AT+YOUR?");
    if (err != ESP_OK) return err;

    err = esp_at_register_cmd_example("AT+YOUR", handle_at_your, "AT+YOUR=CFG");
    if (err != ESP_OK) {
        (void)esp_at_unregister_cmd("AT+YOUR?");
        return err;
    }

    err = esp_at_set_help_visible("AT+YOUR", false);
    if (err != ESP_OK) {
        (void)esp_at_unregister_cmd("AT+YOUR");
        (void)esp_at_unregister_cmd("AT+YOUR?");
        return err;
    }

    return ESP_OK;
}

static void unregister_at_commands(void)
{
    (void)esp_at_unregister_cmd("AT+YOUR?");
    (void)esp_at_unregister_cmd("AT+YOUR");
}

static void handle_at_your_query(const char *param)
{
    (void)param;
    AT(C "Your component:");
    AT(C "  state : %s", s_initialized ? "initialized" : "not initialized");
    AT(C "  at    : %s", s_at_enabled ? "enabled" : "disabled");
    AT(C "  log   : %s", s_log_enabled ? "enabled" : "disabled");
    AT(C "Usage:");
    AT(C "  AT+YOUR=CFG");
    AT(C "  AT+YOUR=DO,<arg1>,<arg2>");
}

static void handle_at_your(const char *param)
{
    if (param == NULL || *param == '\0') {
        AT(R "ERROR: use AT+YOUR? for syntax");
        return;
    }

    char work[96];
    if (strlen(param) >= sizeof(work)) {
        AT(R "ERROR: command too long");
        return;
    }
    strncpy(work, param, sizeof(work) - 1U);
    work[sizeof(work) - 1U] = '\0';

    char *tokens[4] = {0};
    int token_count = 0;
    char *ctx = NULL;
    char *tok = strtok_r(work, ",", &ctx);
    while (tok != NULL && token_count < 4) {
        tokens[token_count++] = trim_ws(tok);
        tok = strtok_r(NULL, ",", &ctx);
    }

    if (token_count == 1 && ci_equals(tokens[0], "CFG")) {
        AT(G "OK");
        return;
    }

    AT(R "ERROR: use AT+YOUR? for syntax");
}
