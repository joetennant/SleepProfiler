# SleepProfiler

Spike to determine how timer coalescing affects the `usleep` and `select` C function calls under different conditions.

In macOS (since Mavericks) timers are coalesced under certain circumstances and this can affect existing C code in unforseen ways.
This code was designed to help test this while running as a Daemon process or user process under certain conditions.

Messages are logged to the Console using the "subsystem" `com.sevensignal.sleepprofiler`.
