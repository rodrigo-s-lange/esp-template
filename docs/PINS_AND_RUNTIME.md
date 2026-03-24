# Pins And Runtime

## Use `esp_pins` when

- the component owns physical pins
- a user may need to diagnose ownership conflicts
- board-awareness matters
- the component needs labels such as `I2C_MASTER SDA` or `SPI_MASTER CS`

## Use `esp_runtime` when

- the component has a real lifecycle
- enable/disable is meaningful
- status belongs in the system overview
- AT and log modes should be selectable by users or examples

## Do not use either when

- the component is just an internal helper
- it owns no visible resources

## Rule of thumb

- base components often belong in both `esp_pins` and `esp_runtime`
- device components often belong in `esp_runtime`
- device components should use `esp_pins` only when they truly own or reserve GPIOs
