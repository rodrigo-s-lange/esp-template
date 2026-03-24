# Component Blueprint

Use this blueprint when creating a new component from this template.

## 1. Decide what kind of component this is

Choose one category first:

- low-level helper
- base bus/protocol component
- device driver component
- UI/output component
- runtime-managed feature component

Do not mix categories casually.

## 2. Decide whether it belongs in `esp_runtime`

Add runtime integration only if all are true:

- init is clean
- deinit is complete
- AT registration is symmetrical
- no leaked tasks or handlers
- operator-facing status is useful

## 3. Decide whether it belongs in `esp_pins`

Add `esp_pins` integration only if the component owns GPIOs that matter to diagnostics.

Examples:

- I2C master: yes
- SPI master: yes
- UART bus: yes
- pure math/helper component: no

## 4. Define the public API

Keep it capability-oriented.
Do not expose backend internals in the public header.

Good:

- `set_brightness()`
- `transfer()`
- `read_register()`

Weak:

- `set_ledc_channel()`
- `use_spi2_host()`
- `set_rmt_symbol_clock()`

## 5. Write docs before publish

At minimum:

- purpose
- lifecycle
- config defaults if any
- AT commands if any
- realistic examples
- constraints and assumptions
