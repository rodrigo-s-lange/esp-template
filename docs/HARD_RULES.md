# Hard Rules

## Language

- English only.

## Error handling

- No `ESP_ERROR_CHECK()` for expected runtime failures in reusable components.
- Return `esp_err_t`.
- AT diagnostics must be readable by humans.

## Lifecycle

- reject double init with `ESP_ERR_INVALID_STATE`
- release all resources in `deinit()`
- `is_initialized()` must reflect reality

## Resource ownership

If a resource is acquired, it must be released.

Examples:

- tasks
- timers
- queues
- semaphores
- event handlers
- GPIO ownership
- bus/device handles
- heap allocations

## Public headers

- self-contained
- explicit includes
- no transitive include assumptions

## Dependencies

- minimal
- justified
- documented

## Main rule

Do not move feature logic into `main` if it belongs in a reusable component.
