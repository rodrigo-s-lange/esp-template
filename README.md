# esp-template

This repository is a component template for the ESP framework used in this project.

Its purpose is not to provide a working feature by itself.
Its purpose is to guide humans and AI tools toward creating new components that:

- follow the framework lifecycle contract
- use resources explicitly
- expose readable diagnostics
- integrate cleanly with `esp_runtime` only when ready
- integrate with `esp_pins` only when they actually own GPIOs
- stay publishable as independent repositories

## What this template includes

- `CMakeLists.txt`
- `LICENSE`
- `README.md`
- `COMMANDS.md`
- `EXAMPLES.md`
- `include/esp_your_component.h`
- `esp_your_component.c`
- `docs/` guidance for architecture, AT style, pins, and publish rules

## How to use this template

1. Copy the folder.
2. Rename `esp_your_component` to the real component name.
3. Replace every placeholder token before publishing.
4. Remove sections that do not apply.
5. Keep the hard rules unless there is a documented architectural reason to break them.

## Required rename targets

Rename these consistently:

- folder name
- repo name
- public header name
- source file name
- include guard/macros if any
- AT commands
- log tag
- README title

## Placeholder tokens used in this template

- `your_component`
- `YOUR_COMPONENT`
- `AT+YOUR?`
- `AT+YOUR`
- `ESP_PINS_OWNER_<YOUR_OWNER>`

Do not publish a repository with these placeholders still present.

## Hard rules

- English only in code, comments, logs, AT output, and docs.
- No `ESP_ERROR_CHECK()` for expected runtime failures inside reusable components.
- `deinit()` must release everything allocated by `init()`.
- If AT commands are registered, they must be unregistered in `deinit()`.
- If a component owns GPIOs, claim them through `esp_pins`.
- If a component does not own GPIOs, do not integrate it with `esp_pins`.
- If a component cannot be enabled and disabled cleanly, do not put it in `esp_runtime` yet.
- Public headers must describe capability, not backend implementation details.
- Keep dependencies minimal.

## Recommended release flow

1. Build locally.
2. Test on real hardware when the component touches hardware.
3. Review AT output for human readability.
4. Review `README.md`, `COMMANDS.md`, and `EXAMPLES.md`.
5. Publish the standalone repository.
6. Only then integrate it into `esp_runtime` if it is stable enough.

## Related guidance

Read these before building a real component:

- `docs/COMPONENT_BLUEPRINT.md`
- `docs/HARD_RULES.md`
- `docs/AT_GUIDE.md`
- `docs/PINS_AND_RUNTIME.md`
- `docs/PUBLISH_CHECKLIST.md`
