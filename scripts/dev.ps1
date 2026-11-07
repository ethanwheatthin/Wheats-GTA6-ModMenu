#!/usr/bin/env pwsh
# One-time local dev setup: configure the dev preset and install pre-commit hooks.
$ErrorActionPreference = "Stop"
Set-Location (Join-Path $PSScriptRoot "..")

cmake --preset dev
pre-commit install --hook-type pre-commit --hook-type commit-msg
