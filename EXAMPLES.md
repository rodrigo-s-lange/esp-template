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

## API example with flags

```c
#include "esp_your_component.h"

void app_main(void)
{
    ESP_ERROR_CHECK(esp_your_component_init(ESP_INIT_AT | ESP_INIT_LOG));
    ESP_ERROR_CHECK(esp_your_component_deinit());
}
```

## Runtime-managed example

Only keep this example if the component is truly runtime-ready.

```c
#include "esp_at.h"
#include "esp_runtime.h"

void app_main(void)
{
    ESP_ERROR_CHECK(esp_at_init(ESP_AT_INIT_DEFAULT));
    ESP_ERROR_CHECK(esp_runtime_init(ESP_RUNTIME_AT));
    ESP_ERROR_CHECK(esp_runtime_enable(ESP_RUNTIME_MODULE_<YOUR_MODULE>, ESP_RUNTIME_ENABLE_AT));
}
```

AT runtime usage for the same component:

```text
AT+ESP=<YOUR_MODULE>,ENABLE
AT+ESP=<YOUR_MODULE>,ENABLE,AT
AT+ESP=<YOUR_MODULE>,ENABLE,LOG
AT+ESP=<YOUR_MODULE>,ENABLE,AT,LOG
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
