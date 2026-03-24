# Pins And Runtime

## Use `esp_pins` when

- the component owns physical pins
- a user may need to diagnose ownership conflicts
- board-awareness matters

## Use `esp_runtime` when

- the component has a real lifecycle
- enable/disable is meaningful
- status belongs in the system overview

## Do not use either when

- the component is just an internal helper
- it owns no visible resources
