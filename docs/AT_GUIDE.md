# AT Guide

Use this only if the component truly benefits from an operator-facing AT interface.

## Rules

- one query command when practical: `AT+NAME?`
- one action command family: `AT+NAME=...`
- errors must explain the problem in plain English
- help output must show exact syntax

## Good examples

- `ERROR: invalid parameter`
- `ERROR: bus not configured`
- `ERROR: measurement not ready`

## Weak examples

- `ERROR: fail`
- `ERROR: invalid state`
- `ERROR: cfg failed (ESP_ERR_INVALID_STATE)`
