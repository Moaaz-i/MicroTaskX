# Changelog

All notable changes to this project will be documented in this file.

## [4.0.0] - 2026-07-07

### Added

- Major stable release of MicroTaskX scheduler with full API optimizations.
- Production-ready support for cooperative multitasking across multi-core architectures (ESP32).
- Full integration of repository health checks, workflows, and enterprise community guidelines.

### Changed

- Improved memory footprint and task switching efficiency.
- Refactored core scheduler loops for strictly non-blocking execution.

## [3.1.0] - 2026-06-23

### Added

- **Advanced Control Systems:** Anti-Windup PID Controller (`computePID`) and Hysteresis Logic (`applyHysteresis`).
- **Flicker-Free UI Rendering:** Differential buffer updates for LiquidCrystal/I2C displays (`updateScreenSmart`), eliminating screen flashes.
- **Cinematic Text Utilities:** Non-blocking typewriter effect (`printTypewriter`), centered output calculator, and visual progress bars.
- **Signal Filtering & Buffering:** True Moving Average filter and High-Speed lock-free Circular Queue template class (`MTXCircularQueue`).
- **System Metrics:** CRC8 Checksum verification and hardware-aware battery percentage scaling.

## [3.0.0] - 2026-06-09

### Added

- Transitioned to a fully modular template-based architecture (`MicroTaskXKernel<MAX_TASKS>`).
- Dynamic runtime task management (`pauseTask()`, `resumeTask()`, `setInterval()`).
- One-Shot task support (`addOneShotTask()`).
- True ESP32 Low-Power integration via calculation-mapped `esp_light_sleep_start()`.

### Breaking Changes

- `MTX_END` macro no longer uses parenthesis.
- `smoothRead` functions now require a logging variable reference to prevent analog cross-talk.
