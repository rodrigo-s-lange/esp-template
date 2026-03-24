# Examples

## Minimal API example

```c
#include "esp_your_component.h"

void app_main(void)
{
    ESP_ERROR_CHECK(esp_your_component_init(ESP_INIT_NONE));
    // Configure or use the component here.
    ESP_ERROR_CHECK(esp_your_component_deinit());
}
```

## Runtime-managed example

Only keep this example if the component is truly runtime-ready.

```c
#include "esp_runtime.h"

void app_main(void)
{
    ESP_ERROR_CHECK(esp_at_init(false));
    ESP_ERROR_CHECK(esp_runtime_init(ESP_RUNTIME_AT));
    ESP_ERROR_CHECK(esp_runtime_enable(ESP_RUNTIME_MODULE_<YOUR_MODULE>, false, true));
}
```

## AT example

```text
AT+YOUR?
AT+YOUR=CFG
AT+YOUR=DO,123,456
```

## When to delete examples

Delete sections that do not apply.
A weak, misleading example is worse than no example.
