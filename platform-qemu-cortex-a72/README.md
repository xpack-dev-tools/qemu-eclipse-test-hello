# platform-qemu-cortex-a72

Support files for running on QEMU Cortex-A72 (virt).

- <https://qemu.readthedocs.io/en/latest/system/arm/mps2.html>

To start QEMU for debug sessions:

```
.../qemu-system-aarch64 --machine virt --cpu=cortex-a72 --nographic -d unimp,guest_errors --semihosting-config enable=on,target=native,arg=test -s -S
```

## Heap & stack

The SYS_HEAPINFO returns 0x4400_0000 - 0x4800_0000, but only if the
initial stack is not in this range (weird!).

## RAM

There is only a RAM version of the application.

