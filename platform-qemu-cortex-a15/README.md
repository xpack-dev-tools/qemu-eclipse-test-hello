# platform-qemu-cortex-a15

Support files for running on QEMU Cortex-A15 (virt).

- <https://qemu.readthedocs.io/en/latest/system/arm/virt.html>

To start QEMU for debug sessions:

```console
.../qemu-system-arm --machine virt --cpu=cortex-a15 --nographic -d unimp,guest_errors --semihosting-config enable=on,target=native,arg=test -s -S
```

## Heap & stack

The SYS_HEAPINFO returns 0x4400_0000 - 0x4800_0000, but only if the
initial stack is not in this range (weird!).

## RAM

There is only a RAM version of the application.
