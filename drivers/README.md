# UEFI filesystem drivers

`ntfs_x64.efi` is the x64 UEFI NTFS read/write driver from pbatard/ntfs-3g
release 1.7:

https://github.com/pbatard/ntfs-3g/releases/tag/1.7

The driver is GPL-2.0 licensed upstream. `build.ps1` packages `*.efi` files
from this directory into `\EFI\BOOT\DRIVERS` inside the UEFI boot image.
