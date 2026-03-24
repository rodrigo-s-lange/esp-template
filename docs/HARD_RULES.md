# Hard Rules

## Language

- English only.
- Use ASCII unless a file already requires something else.

## Error handling

- No `ESP_ERROR_CHECK()` for expected runtime failures in reusable components.
- Return `esp_err_t`.
- AT diagnostics must be readable by humans.
- Public status/help output must prefer operational wording over raw booleans.

## Lifecycle

- reject double init with `ESP_ERR_INVALID_STATE`
- release all resources in `deinit()`
- `is_initialized()` must reflect reality
- init flags must use `ESP_INIT_NONE`, `ESP_INIT_AT`, and `ESP_INIT_LOG`

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
- Doxygen on every public type, enum, macro, and function

## Dependencies

- minimal
- justified
- documented

## Runtime and AT

- Do not add runtime integration until enable/disable is clean.
- If runtime integration exists, examples and docs must use `AT+ESP=<MODULE>,ENABLE[,AT][,LOG]`.
- AT registration and unregistration must be symmetrical.
- Query commands must print syntax that the user can copy and run.

## Main rule

Do not move feature logic into `main` if it belongs in a reusable component.
