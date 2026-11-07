#!/usr/bin/env bash
# Set a GitHub Project (v2) item's Status field, looking up project/field/
# option IDs dynamically - nothing hardcoded. Requires `gh` authenticated
# with the `project` scope (PROJECT_TOKEN in CI).
set -euo pipefail

if [ $# -ne 2 ]; then
  echo "usage: project-status.sh <issue-or-pr-number> <status>" >&2
  exit 1
fi

number="$1"
status="$2"
owner="${PROJECT_OWNER:-ethanwheatthin}"
project_title="${PROJECT_TITLE:-Wheats-GTA6-ModMenu}"
repo="${GH_REPO:-ethanwheatthin/Wheats-GTA6-ModMenu}"

project_number=$(gh project list --owner "$owner" --format json \
  | jq -r --arg t "$project_title" '.projects[] | select(.title == $t) | .number')
if [ -z "$project_number" ]; then
  echo "Project '$project_title' not found for owner '$owner'" >&2
  exit 1
fi

project_id=$(gh project view "$project_number" --owner "$owner" --format json | jq -r '.id')

field_json=$(gh project field-list "$project_number" --owner "$owner" --format json)
field_id=$(echo "$field_json" | jq -r '.fields[] | select(.name == "Status") | .id')
option_id=$(echo "$field_json" | jq -r --arg s "$status" '.fields[] | select(.name == "Status") | .options[] | select(.name == $s) | .id')

if [ -z "$field_id" ] || [ -z "$option_id" ]; then
  echo "Status field or option '$status' not found on project '$project_title'" >&2
  exit 1
fi

item_url=$(gh issue view "$number" --repo "$repo" --json url -q .url 2>/dev/null \
  || gh pr view "$number" --repo "$repo" --json url -q .url)

item_id=$(gh project item-list "$project_number" --owner "$owner" --format json \
  | jq -r --arg u "$item_url" '.items[] | select(.content.url == $u) | .id')

if [ -z "$item_id" ]; then
  echo "#$number not yet on project '$project_title' - adding it"
  item_id=$(gh project item-add "$project_number" --owner "$owner" --url "$item_url" --format json | jq -r '.id')
fi

gh project item-edit --project-id "$project_id" --id "$item_id" --field-id "$field_id" --single-select-option-id "$option_id"
echo "Set #$number to '$status'"
