# AI Authoring Guide

This template is designed to be consumed by both humans and AI coding agents.

## If you are an AI agent

You must not treat this template as a toy example.
You must turn placeholders into a coherent component that obeys the framework rules.

## Minimum obligations

- rename every placeholder consistently
- keep public headers self-contained
- keep the public API capability-oriented
- do not expose backend internals without a strong reason
- keep dependencies minimal
- use readable diagnostics
- add Doxygen to every public API before considering the component finished
- implement symmetric init/deinit behavior
- do not invent runtime integration if the lifecycle is not ready
- do not invent `esp_pins` integration if the component owns no GPIOs
- classify the component correctly as base or device
- keep examples aligned with `ESP_INIT_*` and `AT+ESP=<MODULE>,ENABLE[,AT][,LOG]`

## Do not do this

- leave placeholder names in the repo
- leave dead or fake AT commands in place
- add `ESP_ERROR_CHECK()` inside reusable library code for expected failures
- expose target-specific backend details in the public header
- add undocumented global state
- add tasks/timers without proper deinit logic

## Deliverables expected from an AI-generated component

- working code
- public header
- README
- EXAMPLES
- COMMANDS when AT exists
- realistic defaults only when justified
- explicit constraints and assumptions
