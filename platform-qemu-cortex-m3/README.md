# platform-qemu-cortex-m3

Support files for running on QEMU Cortex-M3 (mps2-an385).

- <https://qemu.readthedocs.io/en/latest/system/arm/mps2.html>

To start QEMU for debug sessions:

```
.../qemu-system-arm --machine mps2-an385 --nographic -d unimp,guest_errors --semihosting-config enable=on,target=native,arg=test -s -S
```


## Heap & stack

The SYS_HEAPINFO returns 0x2100_0000 - 0x2200_0000.

## RAM

Under the debugger, the application runs both in RAM and FLASH,
but the standlone RAM version crashes QEMU:

```console
ilg@wksi ~ % /Users/ilg/Library/xPacks/@xpack-dev-tools/qemu-arm/7.0.0-1.1/.content/bin/qemu-system-arm "--machine" "mps2-an385" "--nographic" "-d" "unimp,guest_errors" "--semihosting-config" "enable=on,target=native,arg=test,arg=M3" -kernel /Users/ilg/My\ Files/WKS\ Projects/xpack-dev-tools.github/xPacks/qemu-arm-xpack.git/tests/eclipse/hello/cortex-m3-ram-debug/hello.elf
Invalid write at addr 0xFFFFFFE0, size 4, region '(null)', reason: rejected
qemu: fatal: Lockup: can't escalate 3 to HardFault (current priority -1)

R00=00000000 R01=00000000 R02=00000000 R03=00000000
R04=00000000 R05=00000000 R06=00000000 R07=00000000
R08=00000000 R09=00000000 R10=00000000 R11=00000000
R12=00000000 R13=ffffffe0 R14=fffffff9 R15=00000000
XPSR=40000003 -Z-- A handler
FPSCR: 00000000
zsh: abort       "--machine" "mps2-an385" "--nographic" "-d" "unimp,guest_errors"   -kernel 
ilg@wksi ~ % 
```

