# AT Commands

Replace this file if the component does not expose AT commands.
If the component has no AT interface, delete `COMMANDS.md` before publishing.

## Required behavior

- syntax must be deterministic
- errors must be readable by humans
- `AT+...?...` should show status and usage when practical
- registration and unregistration must be symmetrical
- query output should prefer operational wording over raw booleans
- help must show exact syntax the user can paste back into the terminal

## Template commands

- `AT+YOUR?`
- `AT+YOUR=CFG`
- `AT+YOUR=DO,<arg1>,<arg2>`

## Example

```text
AT+YOUR?
AT+YOUR=CFG
AT+YOUR=DO,123,456
```

## AT style rules

Good:
```text
ERROR: sensor not configured
ERROR: invalid parameter
ERROR: transfer timed out
State: configured
AT: enabled
```

Weak:
```text
ERROR: cfg failed (ESP_ERR_INVALID_STATE)
ERROR: fail
cfg : TRUE
```
