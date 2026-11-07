#!/usr/bin/env pwsh
# clang-format check (no edits) + clang-tidy against the dev build's compile_commands.json.
$ErrorActionPreference = "Stop"
Set-Location (Join-Path $PSScriptRoot "..")

$sources = git ls-files "*.cpp" "*.hpp" "*.cc" "*.h"
if (-not $sources) {
  Write-Output "No C++ sources tracked yet."
  exit 0
}

Write-Output "Running clang-format --dry-run --Werror..."
& clang-format --dry-run --Werror $sources
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

if (-not (Test-Path "build/dev/compile_commands.json")) {
  cmake --preset dev
}

Write-Output "Running clang-tidy..."
& clang-tidy -p build/dev $sources
exit $LASTEXITCODE
