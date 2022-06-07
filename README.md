# qemu-eclipse-test-hello

## Overall

A small "Hello World!" application to test QEMU in bare-metal configurations.

The supported platforms are:

- Cortex-M3
- Cortex-A15 (32-bit)
- Cortex-A72 (64-bit)

For each one see the corresponding `platform-*` folder.

## Arm semihosting

The application uses Arm semihosting to communicate with QEMU.

For newlib, the options added to the linker line are:

```console
--specs=rdimon.specs -Wl,--start-group -lgcc -lc -lc -lm -lrdimon -Wl,--end-group
```

## initialised `.data`

The librdimon startup assumes the code will run from RAM,
and does not copy initialised data from FLASH to RAM; to fix
this, manually copy the memory area before `_start()`.
