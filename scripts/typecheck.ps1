#!/usr/bin/env pwsh
# Compile-only check with warnings as errors (see target_compile_options in
# adapters/mock and tests CMakeLists). No SDK required - mock adapter only.
$ErrorActionPreference = "Stop"
Set-Location (Join-Path $PSScriptRoot "..")

cmake --preset dev
cmake --build --preset dev --target modmenu_core modmenu_mock_adapter modmenu_ui modmenu_tests
