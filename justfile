dev:
    pwsh ./scripts/dev.ps1

build preset="dev":
    pwsh ./scripts/build.ps1 -Preset {{preset}}

lint:
    pwsh ./scripts/lint.ps1

typecheck:
    pwsh ./scripts/typecheck.ps1

test preset="dev":
    pwsh ./scripts/test.ps1 -Preset {{preset}}
