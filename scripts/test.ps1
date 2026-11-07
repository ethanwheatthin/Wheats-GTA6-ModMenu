#!/usr/bin/env pwsh
param([string]$Preset = "dev")
$ErrorActionPreference = "Stop"
Set-Location (Join-Path $PSScriptRoot "..")

cmake --preset $Preset
cmake --build --preset $Preset
ctest --preset $Preset
