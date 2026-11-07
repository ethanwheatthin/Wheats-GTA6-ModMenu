# 1. Record architecture decisions

Date: 2026-11-06

## Status

Accepted

## Context

We need a record of the architecturally significant decisions made on this
project: what was decided, why, and what alternatives were considered. This
matters more than usual here because the project is explicitly designed to
be partially rebuilt (the game adapter) once GTA VI tooling exists, and
because multiple sessions of a coding agent will work on it over time without
shared memory beyond the repo itself.

## Decision

We will use Architecture Decision Records (ADRs), as described by Michael
Nygard. Each significant decision gets a new file in `docs/adr/`, numbered
sequentially, named `NNNN-title-with-dashes.md`. Records are immutable once
accepted; a decision that changes gets a new ADR that supersedes the old one.

## Consequences

Anyone (human or agent) can see not just what the architecture is, but why,
without re-deriving it from the code or guessing.
