---
description: Update the changelog after making a user-facing change (improvement, breaking change, bug fix, new feature, removal)
---

# Update Changelog

After making a user-facing change to the firmware, update `firmware/CHANGELOG.md`.

## What counts as user-facing

- New features or capabilities
- Bug fixes that affect behavior
- Breaking changes (config format, pin assignments, removed features, TunerStudio changes)
- Changes to Lua API
- Changes to CAN bus behavior
- Changes to sensor processing that affect readings/calibration
- Removed features or settings

## What does NOT need a changelog entry

- Internal refactors with no behavior change
- Unit test changes
- Code formatting / style changes
- Build system or CI changes
- Documentation-only changes
- Changes only to comments

## How to update

1. Read `firmware/CHANGELOG.md` to see the current state.
2. Add the entry under the `## Unreleased` section, in the appropriate subsection:
   - `### Breaking Changes` - changes that may require user action (reconfiguration, recalibration, etc.)
   - `### Added` - new features or capabilities
   - `### Fixed` - bug fixes
   - `### Removed` - removed features or settings
3. Match the style of existing entries: start with a capital letter, be concise but descriptive, include issue/PR numbers if known (e.g. `#578`).
4. Write from the user's perspective, not the developer's. Describe what changed for them, not what code was modified. Keep changelog entries concise: they are intended for ordinary users, so don't write a huge essay explaining the full picture, just enough that they can know if this release fixes their bug.
5. Make the entry as short as possible, ideally one line. Say what changed for the user and stop. Leave out reasons, how it works and edge cases; those belong in the PR description. Name the TunerStudio setting in quotes if there is one, and end with the PR or issue number if known.

### Examples

Good: `DFCO "After cut timing ramp-in time" is now actually respected, rather than ignored and using 0.5s. #819`
Bad: `"After cut timing ramp-in time" now actually controls how long DFCO timing retard takes to ramp back out after fuel is restored. The ramp was hardcoded to 0.5 seconds regardless of the setting, so values above 0.5s returned timing sooner than asked for, and values below 0.5s stepped the remaining retard away in one jump instead of ramping it out`

Good: `Allow fractional tachometer pulse ratio for fine tachometer calibration`
Bad: `Changed tach_pulse_ratio from int to float in config`

Good: `Fix idle control D-term by improving RPM rate of change signal`
Bad: `Fixed derivative calculation in PidController::getOutput`
