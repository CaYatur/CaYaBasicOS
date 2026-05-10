param(
    [switch]$Run,
    [string]$IsoPath = "dist\CaYaBasicOS.iso"
)

Set-StrictMode -Version Latest
$ErrorActionPreference = "Stop"

$Root = Split-Path -Parent $MyInvocation.MyCommand.Path
$BuildDir = Join-Path $Root "build"
$DistDir = Join-Path $Root "dist"
$BootAsm = Join-Path $Root "src\boot\boot.asm"
$Stage16Asm = Join-Path $Root "src\kernel\stage16.asm"
$EntryAsm = Join-Path $Root "src\kernel\entry.asm"
$KernelC = Join-Path $Root "src\kernel\kernel.c"
$UefiC = Join-Path $Root "src\uefi\bootx64.c"
$Linker = Join-Path $Root "src\kernel\linker.ld"
$BootBin = Join-Path $BuildDir "boot.bin"
$Stage16Bin = Join-Path $BuildDir "stage16.bin"
$EntryObj = Join-Path $BuildDir "entry.o"
$KernelObj = Join-Path $BuildDir "kernel.o"
$UefiObj = Join-Path $BuildDir "bootx64.obj"
$KernelElf = Join-Path $BuildDir "kernel.elf"
$KernelBin = Join-Path $BuildDir "kernel.bin"
$BootEfi = Join-Path $BuildDir "BOOTX64.EFI"
$UefiImg = Join-Path $BuildDir "uefi.img"
$BootImg = Join-Path $BuildDir "boot.img"
$IsoFullPath = Join-Path $Root $IsoPath

New-Item -ItemType Directory -Force -Path $BuildDir, $DistDir | Out-Null

function Find-Exe {
    param(
        [string[]]$Names,
        [string[]]$ExtraDirs = @()
    )
    foreach ($name in $Names) {
        $cmd = Get-Command $name -ErrorAction SilentlyContinue
        if ($cmd) {
            return $cmd.Source
        }
    }
    foreach ($dir in $ExtraDirs) {
        foreach ($name in $Names) {
            $candidate = Join-Path $dir $name
            if (Test-Path $candidate) {
                return $candidate
            }
            if ($name -notmatch '\.exe$') {
                $candidateExe = Join-Path $dir ($name + ".exe")
                if (Test-Path $candidateExe) {
                    return $candidateExe
                }
            }
        }
    }
    return $null
}

function Invoke-Tool {
    param(
        [string]$Exe,
        [string[]]$ToolArgs
    )
    Write-Host ("> " + $Exe + " " + ($ToolArgs -join " "))
    & $Exe @ToolArgs
    if ($LASTEXITCODE -ne 0) {
        throw "Command failed with exit code ${LASTEXITCODE}: $Exe"
    }
}

function Require-Tool {
    param([string]$Tool, [string]$Message)
    if (-not $Tool) {
        throw $Message
    }
}

function Copy-Bytes {
    param(
        [byte[]]$Source,
        [byte[]]$Dest,
        [int]$Offset
    )
    [Array]::Copy($Source, 0, $Dest, $Offset, $Source.Length)
}

$ToolDirs = @(
    "C:\Program Files\NASM",
    "C:\Program Files\LLVM\bin",
    "C:\Program Files (x86)\LLVM\bin",
    "C:\msys64\mingw32\bin",
    "C:\msys64\ucrt64\bin",
    "C:\msys64\clang32\bin",
    "C:\ProgramData\chocolatey\bin"
)

$Nasm = Find-Exe @("nasm") $ToolDirs
Require-Tool $Nasm "NASM bulunamadi. PATH icine nasm ekleyip .\build.ps1 tekrar calistirin."

$Gcc = Find-Exe @("i686-elf-gcc") $ToolDirs
$Ld = Find-Exe @("i686-elf-ld") $ToolDirs
$Objcopy = Find-Exe @("i686-elf-objcopy") $ToolDirs
$Clang = Find-Exe @("clang") $ToolDirs
$Lld = Find-Exe @("ld.lld") $ToolDirs
$LldLink = Find-Exe @("lld-link") $ToolDirs
$LlvmObjcopy = Find-Exe @("llvm-objcopy") $ToolDirs

$UseClang = $false
if ($Gcc -and $Ld -and $Objcopy) {
    $UseClang = $false
} elseif ($Clang -and $Lld -and $LlvmObjcopy) {
    $UseClang = $true
} else {
    throw "32-bit freestanding C toolchain bulunamadi. i686-elf-gcc/i686-elf-ld/i686-elf-objcopy veya clang/ld.lld/llvm-objcopy gerekir."
}

if (-not ($Clang -and $LldLink)) {
    throw "UEFI BOOTX64.EFI uretimi icin clang ve lld-link gerekir."
}

Invoke-Tool $Nasm @("-f", "elf32", $EntryAsm, "-o", $EntryObj)

Invoke-Tool $Clang @(
    "-target", "x86_64-unknown-windows",
    "-std=c11",
    "-ffreestanding",
    "-fshort-wchar",
    "-fno-builtin",
    "-fno-stack-protector",
    "-fno-asynchronous-unwind-tables",
    "-fno-unwind-tables",
    "-mno-red-zone",
    "-O2",
    "-Wall",
    "-Wextra",
    "-c", $UefiC,
    "-o", $UefiObj
)

Invoke-Tool $LldLink @(
    "/subsystem:efi_application",
    "/entry:efi_main",
    "/nodefaultlib",
    "/out:$BootEfi",
    $UefiObj
)

if ($UseClang) {
    Invoke-Tool $Clang @(
        "-target", "i386-elf",
        "-std=c11",
        "-ffreestanding",
        "-fno-builtin",
        "-fno-pic",
        "-fno-stack-protector",
        "-fno-asynchronous-unwind-tables",
        "-fno-unwind-tables",
        "-m32",
        "-O2",
        "-Wall",
        "-Wextra",
        "-c", $KernelC,
        "-o", $KernelObj
    )
    Invoke-Tool $Lld @(
        "-m", "elf_i386",
        "-T", $Linker,
        "-nostdlib",
        $EntryObj,
        $KernelObj,
        "-o", $KernelElf
    )
    Invoke-Tool $LlvmObjcopy @("-O", "binary", $KernelElf, $KernelBin)
} else {
    Invoke-Tool $Gcc @(
        "-std=c11",
        "-ffreestanding",
        "-fno-builtin",
        "-fno-pic",
        "-fno-stack-protector",
        "-fno-asynchronous-unwind-tables",
        "-fno-unwind-tables",
        "-m32",
        "-O2",
        "-Wall",
        "-Wextra",
        "-c", $KernelC,
        "-o", $KernelObj
    )
    Invoke-Tool $Ld @(
        "-T", $Linker,
        "-nostdlib",
        $EntryObj,
        $KernelObj,
        "-o", $KernelElf
    )
    Invoke-Tool $Objcopy @("-O", "binary", $KernelElf, $KernelBin)
}

$KernelBytes = [System.IO.File]::ReadAllBytes($KernelBin)
$Stage16Size = 4096

Invoke-Tool $Nasm @(
    "-f", "bin",
    "-D", "STAGE16_BASE=0x10000",
    "-D", "KERNEL32_ADDR=0x11000",
    $Stage16Asm,
    "-o", $Stage16Bin
)

$Stage16Bytes = [System.IO.File]::ReadAllBytes($Stage16Bin)
if ($Stage16Bytes.Length -gt $Stage16Size) {
    throw "stage16.bin cok buyuk: $($Stage16Bytes.Length) bytes. Ust sinir: $Stage16Size bytes."
}

$Stage16Padded = [byte[]]::new($Stage16Size)
Copy-Bytes $Stage16Bytes $Stage16Padded 0

$KernelPayload = [byte[]]::new($Stage16Size + $KernelBytes.Length)
Copy-Bytes $Stage16Padded $KernelPayload 0
Copy-Bytes $KernelBytes $KernelPayload $Stage16Size

$KernelSectors = [int][Math]::Ceiling($KernelPayload.Length / 512.0)
if ($KernelSectors -le 0) {
    throw "kernel.bin bos olustu."
}
if ((1 + $KernelSectors) * 512 -gt 1474560) {
    throw "Kernel boot image icin cok buyuk: $($KernelPayload.Length) bytes."
}

Invoke-Tool $Nasm @(
    "-f", "bin",
    "-D", "KERNEL_SECTORS=$KernelSectors",
    $BootAsm,
    "-o", $BootBin
)

$BootBytes = [System.IO.File]::ReadAllBytes($BootBin)
if ($BootBytes.Length -ne 512) {
    throw "boot.bin 512 byte olmali, mevcut: $($BootBytes.Length)"
}

$Floppy = [byte[]]::new(1474560)
Copy-Bytes $BootBytes $Floppy 0
Copy-Bytes $KernelPayload $Floppy 512
[System.IO.File]::WriteAllBytes($BootImg, $Floppy)

function Write-Ascii {
    param([byte[]]$Buffer, [int]$Offset, [int]$Length, [string]$Text)
    $bytes = [System.Text.Encoding]::ASCII.GetBytes($Text)
    $n = [Math]::Min($Length, $bytes.Length)
    [Array]::Copy($bytes, 0, $Buffer, $Offset, $n)
    for ($i = $n; $i -lt $Length; $i++) {
        $Buffer[$Offset + $i] = 0x20
    }
}

function Write-Le16 {
    param([byte[]]$Buffer, [int]$Offset, [int]$Value)
    $Buffer[$Offset] = [byte]($Value -band 0xFF)
    $Buffer[$Offset + 1] = [byte](($Value -shr 8) -band 0xFF)
}

function Write-Be16 {
    param([byte[]]$Buffer, [int]$Offset, [int]$Value)
    $Buffer[$Offset] = [byte](($Value -shr 8) -band 0xFF)
    $Buffer[$Offset + 1] = [byte]($Value -band 0xFF)
}

function Write-Both16 {
    param([byte[]]$Buffer, [int]$Offset, [int]$Value)
    Write-Le16 $Buffer $Offset $Value
    Write-Be16 $Buffer ($Offset + 2) $Value
}

function Write-Le32 {
    param([byte[]]$Buffer, [int]$Offset, [int]$Value)
    $u = [uint32]$Value
    $Buffer[$Offset] = [byte]($u -band 0xFF)
    $Buffer[$Offset + 1] = [byte](($u -shr 8) -band 0xFF)
    $Buffer[$Offset + 2] = [byte](($u -shr 16) -band 0xFF)
    $Buffer[$Offset + 3] = [byte](($u -shr 24) -band 0xFF)
}

function Write-Be32 {
    param([byte[]]$Buffer, [int]$Offset, [int]$Value)
    $u = [uint32]$Value
    $Buffer[$Offset] = [byte](($u -shr 24) -band 0xFF)
    $Buffer[$Offset + 1] = [byte](($u -shr 16) -band 0xFF)
    $Buffer[$Offset + 2] = [byte](($u -shr 8) -band 0xFF)
    $Buffer[$Offset + 3] = [byte]($u -band 0xFF)
}

function Write-Both32 {
    param([byte[]]$Buffer, [int]$Offset, [int]$Value)
    Write-Le32 $Buffer $Offset $Value
    Write-Be32 $Buffer ($Offset + 4) $Value
}

function New-DirRecord {
    param(
        [int]$Lba,
        [int]$Size,
        [byte]$Flags,
        [byte[]]$Name
    )
    $pad = if (($Name.Length % 2) -eq 0) { 1 } else { 0 }
    $len = 33 + $Name.Length + $pad
    $rec = [byte[]]::new($len)
    $rec[0] = [byte]$len
    $rec[1] = 0
    Write-Both32 $rec 2 $Lba
    Write-Both32 $rec 10 $Size
    $rec[18] = 126
    $rec[19] = 5
    $rec[20] = 3
    $rec[21] = 12
    $rec[22] = 0
    $rec[23] = 0
    $rec[24] = 0
    $rec[25] = $Flags
    $rec[26] = 0
    $rec[27] = 0
    Write-Both16 $rec 28 1
    $rec[32] = [byte]$Name.Length
    [Array]::Copy($Name, 0, $rec, 33, $Name.Length)
    return $rec
}

function Put-Sector {
    param([byte[]]$Iso, [int]$Lba, [byte[]]$Sector)
    [Array]::Copy($Sector, 0, $Iso, $Lba * 2048, [Math]::Min(2048, $Sector.Length))
}

function Append-Record {
    param([byte[]]$Sector, [ref]$Offset, [byte[]]$Record)
    [Array]::Copy($Record, 0, $Sector, $Offset.Value, $Record.Length)
    $Offset.Value += $Record.Length
}

function Set-Fat12Entry {
    param([byte[]]$Image, [int]$Cluster, [int]$Value)
    $fatOffsets = @(512, 512 + 9 * 512)
    foreach ($fatOffset in $fatOffsets) {
        $offset = [int](($Cluster * 3) / 2)
        $value12 = $Value -band 0xFFF
        if (($Cluster -band 1) -eq 0) {
            $Image[$fatOffset + $offset] = [byte]($value12 -band 0xFF)
            $Image[$fatOffset + $offset + 1] = [byte](($Image[$fatOffset + $offset + 1] -band 0xF0) -bor (($value12 -shr 8) -band 0x0F))
        } else {
            $Image[$fatOffset + $offset] = [byte](($Image[$fatOffset + $offset] -band 0x0F) -bor (($value12 -shl 4) -band 0xF0))
            $Image[$fatOffset + $offset + 1] = [byte](($value12 -shr 4) -band 0xFF)
        }
    }
}

function Set-FatDirEntry {
    param(
        [byte[]]$Image,
        [int]$Offset,
        [string]$Name11,
        [byte]$Attr,
        [int]$Cluster,
        [int]$Size
    )
    Write-Ascii $Image $Offset 11 $Name11
    $Image[$Offset + 11] = $Attr
    Write-Le16 $Image ($Offset + 26) $Cluster
    Write-Le32 $Image ($Offset + 28) $Size
}

function New-UefiFatImage {
    param(
        [string]$EfiFilePath,
        [string]$OutputPath,
        [string]$LogoPath,
        [string]$FontPath,
        [string]$DriverDir,
        [string]$CyxDir
    )
    $efi = [System.IO.File]::ReadAllBytes($EfiFilePath)
    $assetFiles = @()
    $driverFiles = @()
    if ($LogoPath -and (Test-Path $LogoPath)) {
        $assetFiles += [pscustomobject]@{
            Name11 = "CAYADEV SVG"
            Bytes = [System.IO.File]::ReadAllBytes($LogoPath)
        }
    }
    if ($FontPath -and (Test-Path $FontPath)) {
        $assetFiles += [pscustomobject]@{
            Name11 = "CONSOLASTTF"
            Bytes = [System.IO.File]::ReadAllBytes($FontPath)
        }
    }
    if ($CyxDir -and (Test-Path $CyxDir)) {
        Get-ChildItem -Path $CyxDir -File | Where-Object { $_.Name -match '\.(cyx|txt)$' } | Sort-Object Name | ForEach-Object {
            $base = [System.IO.Path]::GetFileNameWithoutExtension($_.Name).ToUpperInvariant()
            $ext  = [System.IO.Path]::GetExtension($_.Name).TrimStart('.').ToUpperInvariant()
            $cleanBase = -join ($base.ToCharArray() | Where-Object { ($_ -ge 'A' -and $_ -le 'Z') -or ($_ -ge '0' -and $_ -le '9') -or $_ -eq '_' })
            if (-not $cleanBase) { $cleanBase = "APP" }
            if ($cleanBase.Length -gt 8) { $cleanBase = $cleanBase.Substring(0, 8) }
            if ($ext.Length -gt 3) { $ext = $ext.Substring(0, 3) }
            $name11 = $cleanBase.PadRight(8).Substring(0, 8) + $ext.PadRight(3).Substring(0, 3)
            $assetFiles += [pscustomobject]@{
                Name11 = $name11
                Bytes  = [System.IO.File]::ReadAllBytes($_.FullName)
            }
        }
    }
    if ($DriverDir -and (Test-Path $DriverDir)) {
        $idx = 0
        Get-ChildItem -Path $DriverDir -Filter *.efi -File | Sort-Object Name | ForEach-Object {
            $base = [System.IO.Path]::GetFileNameWithoutExtension($_.Name).ToUpperInvariant()
            $clean = -join ($base.ToCharArray() | Where-Object { ($_ -ge 'A' -and $_ -le 'Z') -or ($_ -ge '0' -and $_ -le '9') -or $_ -eq '_' })
            if (-not $clean) {
                $clean = "DRIVER$idx"
            }
            if ($clean.Length -gt 8) {
                $clean = $clean.Substring(0, 8)
            }
            $driverFiles += [pscustomobject]@{
                Name11 = $clean.PadRight(8).Substring(0, 8) + "EFI"
                Bytes = [System.IO.File]::ReadAllBytes($_.FullName)
            }
            $idx++
        }
    }

    $image = [byte[]]::new(1474560)
    $fileClusters = [int][Math]::Ceiling($efi.Length / 512.0)
    if ($fileClusters -le 0) {
        throw "BOOTX64.EFI bos olustu."
    }
    $driversDirCluster = 4
    $nextCluster = 5
    $bootCluster = $nextCluster
    $nextCluster += $fileClusters
    foreach ($asset in $assetFiles) {
        $asset | Add-Member -NotePropertyName StartCluster -NotePropertyValue $nextCluster
        $clusters = [int][Math]::Ceiling($asset.Bytes.Length / 512.0)
        if ($clusters -lt 1) {
            $clusters = 1
        }
        $asset | Add-Member -NotePropertyName ClusterCount -NotePropertyValue $clusters
        $nextCluster += $clusters
    }
    foreach ($driver in $driverFiles) {
        $driver | Add-Member -NotePropertyName StartCluster -NotePropertyValue $nextCluster
        $clusters = [int][Math]::Ceiling($driver.Bytes.Length / 512.0)
        if ($clusters -lt 1) {
            $clusters = 1
        }
        $driver | Add-Member -NotePropertyName ClusterCount -NotePropertyValue $clusters
        $nextCluster += $clusters
    }
    if ($nextCluster -gt 2848) {
        throw "UEFI FAT image icin dosyalar cok buyuk."
    }

    $image[0] = 0xEB
    $image[1] = 0x3C
    $image[2] = 0x90
    Write-Ascii $image 3 8 "CAYAEFI"
    Write-Le16 $image 11 512
    $image[13] = 1
    Write-Le16 $image 14 1
    $image[16] = 2
    Write-Le16 $image 17 224
    Write-Le16 $image 19 2880
    $image[21] = 0xF0
    Write-Le16 $image 22 9
    Write-Le16 $image 24 18
    Write-Le16 $image 26 2
    Write-Le32 $image 28 0
    Write-Le32 $image 32 0
    $image[36] = 0
    $image[38] = 0x29
    Write-Le32 $image 39 0x20260503
    Write-Ascii $image 43 11 "CAYA UEFI"
    Write-Ascii $image 54 8 "FAT12"
    $image[510] = 0x55
    $image[511] = 0xAA

    foreach ($fatOffset in @(512, 512 + 9 * 512)) {
        $image[$fatOffset + 0] = 0xF0
        $image[$fatOffset + 1] = 0xFF
        $image[$fatOffset + 2] = 0xFF
    }

    function Set-FatChain {
        param([int]$StartCluster, [int]$ClusterCount)
        for ($i = 0; $i -lt $ClusterCount; $i++) {
            $cluster = $StartCluster + $i
            $next = if ($i + 1 -eq $ClusterCount) { 0xFFF } else { $cluster + 1 }
            Set-Fat12Entry $image $cluster $next
        }
    }

    function Copy-FatFile {
        param([byte[]]$Bytes, [int]$StartCluster)
        $offset = (33 + ($StartCluster - 2)) * 512
        [Array]::Copy($Bytes, 0, $image, $offset, $Bytes.Length)
    }

    Set-Fat12Entry $image 2 0xFFF
    Set-Fat12Entry $image 3 0xFFF
    Set-Fat12Entry $image $driversDirCluster 0xFFF
    Set-FatChain $bootCluster $fileClusters
    foreach ($asset in $assetFiles) {
        Set-FatChain $asset.StartCluster $asset.ClusterCount
    }
    foreach ($driver in $driverFiles) {
        Set-FatChain $driver.StartCluster $driver.ClusterCount
    }

    $rootOffset = 19 * 512
    $efiDirOffset = 33 * 512
    $bootDirOffset = 34 * 512
    $driversDirOffset = 35 * 512

    Set-FatDirEntry $image ($rootOffset + 0) "EFI" 0x10 2 0
    $rootEntryOffset = $rootOffset + 32
    foreach ($asset in $assetFiles) {
        Set-FatDirEntry $image $rootEntryOffset $asset.Name11 0x20 $asset.StartCluster $asset.Bytes.Length
        $rootEntryOffset += 32
    }
    Set-FatDirEntry $image ($efiDirOffset + 0) "." 0x10 2 0
    Set-FatDirEntry $image ($efiDirOffset + 32) ".." 0x10 0 0
    Set-FatDirEntry $image ($efiDirOffset + 64) "BOOT" 0x10 3 0
    Set-FatDirEntry $image ($bootDirOffset + 0) "." 0x10 3 0
    Set-FatDirEntry $image ($bootDirOffset + 32) ".." 0x10 2 0
    Set-FatDirEntry $image ($bootDirOffset + 64) "BOOTX64 EFI" 0x20 $bootCluster $efi.Length
    Set-FatDirEntry $image ($bootDirOffset + 96) "DRIVERS" 0x10 $driversDirCluster 0
    Set-FatDirEntry $image ($driversDirOffset + 0) "." 0x10 $driversDirCluster 0
    Set-FatDirEntry $image ($driversDirOffset + 32) ".." 0x10 3 0
    $driverEntryOffset = $driversDirOffset + 64
    foreach ($driver in $driverFiles) {
        Set-FatDirEntry $image $driverEntryOffset $driver.Name11 0x20 $driver.StartCluster $driver.Bytes.Length
        $driverEntryOffset += 32
    }
    Copy-FatFile $efi $bootCluster
    foreach ($asset in $assetFiles) {
        Copy-FatFile $asset.Bytes $asset.StartCluster
    }
    foreach ($driver in $driverFiles) {
        Copy-FatFile $driver.Bytes $driver.StartCluster
    }
    [System.IO.File]::WriteAllBytes($OutputPath, $image)
}

function New-PathRecord {
    param(
        [int]$Lba,
        [int]$Parent,
        [byte[]]$Name,
        [bool]$BigEndian
    )
    $pad = if (($Name.Length % 2) -eq 1) { 1 } else { 0 }
    $rec = [byte[]]::new(8 + $Name.Length + $pad)
    $rec[0] = [byte]$Name.Length
    $rec[1] = 0
    if ($BigEndian) {
        Write-Be32 $rec 2 $Lba
        Write-Be16 $rec 6 $Parent
    } else {
        Write-Le32 $rec 2 $Lba
        Write-Le16 $rec 6 $Parent
    }
    [Array]::Copy($Name, 0, $rec, 8, $Name.Length)
    return $rec
}

function Append-PathRecord {
    param([byte[]]$Sector, [ref]$Offset, [byte[]]$Record)
    [Array]::Copy($Record, 0, $Sector, $Offset.Value, $Record.Length)
    $Offset.Value += $Record.Length
}

function New-BootableIso {
    param(
        [string]$ImagePath,
        [string]$EfiFilePath,
        [string]$UefiImagePath,
        [string]$OutputPath
    )

    $bootImage = [System.IO.File]::ReadAllBytes($ImagePath)
    $efiFile = [System.IO.File]::ReadAllBytes($EfiFilePath)
    $uefiImage = [System.IO.File]::ReadAllBytes($UefiImagePath)
    $readme = [System.Text.Encoding]::ASCII.GetBytes(
        "CaYaBasicOS`r`nHybrid BIOS + UEFI x64 control OS prototype.`r`n"
    )

    $bootImageSectors = [int][Math]::Ceiling($bootImage.Length / 2048.0)
    $uefiImageSectors = [int][Math]::Ceiling($uefiImage.Length / 2048.0)
    $efiFileSectors = [int][Math]::Ceiling($efiFile.Length / 2048.0)
    $readmeSectors = [int][Math]::Ceiling($readme.Length / 2048.0)

    $pvdLba = 16
    $bootRecordLba = 17
    $terminatorLba = 18
    $pathTableLLba = 19
    $pathTableMLba = 20
    $rootDirLba = 21
    $efiDirLba = 22
    $efiBootDirLba = 23
    $bootCatalogLba = 24
    $bootImageLba = 25
    $uefiImageLba = $bootImageLba + $bootImageSectors
    $efiFileLba = $uefiImageLba + $uefiImageSectors
    $readmeLba = $efiFileLba + $efiFileSectors
    $totalSectors = $readmeLba + $readmeSectors

    $iso = [byte[]]::new($totalSectors * 2048)

    $pvd = [byte[]]::new(2048)
    $pvd[0] = 1
    Write-Ascii $pvd 1 5 "CD001"
    $pvd[6] = 1
    Write-Ascii $pvd 8 32 "CAYA"
    Write-Ascii $pvd 40 32 "CAYABASICOS"
    Write-Both32 $pvd 80 $totalSectors
    Write-Both16 $pvd 120 1
    Write-Both16 $pvd 124 1
    Write-Both16 $pvd 128 2048
    Write-Both32 $pvd 132 34
    Write-Le32 $pvd 140 $pathTableLLba
    Write-Le32 $pvd 144 0
    Write-Be32 $pvd 148 $pathTableMLba
    Write-Be32 $pvd 152 0
    $rootRecord = New-DirRecord $rootDirLba 2048 2 ([byte[]](0))
    [Array]::Copy($rootRecord, 0, $pvd, 156, $rootRecord.Length)
    Put-Sector $iso $pvdLba $pvd

    $bootRecord = [byte[]]::new(2048)
    $bootRecord[0] = 0
    Write-Ascii $bootRecord 1 5 "CD001"
    $bootRecord[6] = 1
    Write-Ascii $bootRecord 7 32 "EL TORITO SPECIFICATION"
    Write-Ascii $bootRecord 39 32 "CAYABASICOS"
    Write-Le32 $bootRecord 71 $bootCatalogLba
    Put-Sector $iso $bootRecordLba $bootRecord

    $terminator = [byte[]]::new(2048)
    $terminator[0] = 255
    Write-Ascii $terminator 1 5 "CD001"
    $terminator[6] = 1
    Put-Sector $iso $terminatorLba $terminator

    $pathL = [byte[]]::new(2048)
    $pathOff = 0
    Append-PathRecord $pathL ([ref]$pathOff) (New-PathRecord $rootDirLba 1 ([byte[]](0)) $false)
    Append-PathRecord $pathL ([ref]$pathOff) (New-PathRecord $efiDirLba 1 ([System.Text.Encoding]::ASCII.GetBytes("EFI")) $false)
    Append-PathRecord $pathL ([ref]$pathOff) (New-PathRecord $efiBootDirLba 2 ([System.Text.Encoding]::ASCII.GetBytes("BOOT")) $false)
    Put-Sector $iso $pathTableLLba $pathL

    $pathM = [byte[]]::new(2048)
    $pathOff = 0
    Append-PathRecord $pathM ([ref]$pathOff) (New-PathRecord $rootDirLba 1 ([byte[]](0)) $true)
    Append-PathRecord $pathM ([ref]$pathOff) (New-PathRecord $efiDirLba 1 ([System.Text.Encoding]::ASCII.GetBytes("EFI")) $true)
    Append-PathRecord $pathM ([ref]$pathOff) (New-PathRecord $efiBootDirLba 2 ([System.Text.Encoding]::ASCII.GetBytes("BOOT")) $true)
    Put-Sector $iso $pathTableMLba $pathM

    $root = [byte[]]::new(2048)
    $off = 0
    Append-Record $root ([ref]$off) (New-DirRecord $rootDirLba 2048 2 ([byte[]](0)))
    Append-Record $root ([ref]$off) (New-DirRecord $rootDirLba 2048 2 ([byte[]](1)))
    Append-Record $root ([ref]$off) (New-DirRecord $efiDirLba 2048 2 ([System.Text.Encoding]::ASCII.GetBytes("EFI")))
    Append-Record $root ([ref]$off) (New-DirRecord $bootImageLba $bootImage.Length 0 ([System.Text.Encoding]::ASCII.GetBytes("BOOT.IMG;1")))
    Append-Record $root ([ref]$off) (New-DirRecord $uefiImageLba $uefiImage.Length 0 ([System.Text.Encoding]::ASCII.GetBytes("UEFI.IMG;1")))
    Append-Record $root ([ref]$off) (New-DirRecord $readmeLba $readme.Length 0 ([System.Text.Encoding]::ASCII.GetBytes("README.TXT;1")))
    Put-Sector $iso $rootDirLba $root

    $efiDir = [byte[]]::new(2048)
    $off = 0
    Append-Record $efiDir ([ref]$off) (New-DirRecord $efiDirLba 2048 2 ([byte[]](0)))
    Append-Record $efiDir ([ref]$off) (New-DirRecord $rootDirLba 2048 2 ([byte[]](1)))
    Append-Record $efiDir ([ref]$off) (New-DirRecord $efiBootDirLba 2048 2 ([System.Text.Encoding]::ASCII.GetBytes("BOOT")))
    Put-Sector $iso $efiDirLba $efiDir

    $efiBootDir = [byte[]]::new(2048)
    $off = 0
    Append-Record $efiBootDir ([ref]$off) (New-DirRecord $efiBootDirLba 2048 2 ([byte[]](0)))
    Append-Record $efiBootDir ([ref]$off) (New-DirRecord $efiDirLba 2048 2 ([byte[]](1)))
    Append-Record $efiBootDir ([ref]$off) (New-DirRecord $efiFileLba $efiFile.Length 0 ([System.Text.Encoding]::ASCII.GetBytes("BOOTX64.EFI;1")))
    Put-Sector $iso $efiBootDirLba $efiBootDir

    $catalog = [byte[]]::new(2048)
    $catalog[0] = 0x01
    $catalog[1] = 0x00
    Write-Ascii $catalog 4 24 "CaYaBasicOS"
    $catalog[30] = 0x55
    $catalog[31] = 0xAA
    $sum = 0
    for ($i = 0; $i -lt 32; $i += 2) {
        $sum = ($sum + ($catalog[$i] -bor ($catalog[$i + 1] -shl 8))) -band 0xFFFF
    }
    $checksum = ((0 - $sum) -band 0xFFFF)
    Write-Le16 $catalog 28 $checksum

    $catalog[32] = 0x88
    $catalog[33] = 0x02
    Write-Le16 $catalog 38 1
    Write-Le32 $catalog 40 $bootImageLba
    $catalog[64] = 0x91
    $catalog[65] = 0xEF
    Write-Le16 $catalog 66 1
    Write-Ascii $catalog 68 28 "UEFI X64"
    $catalog[96] = 0x88
    $catalog[97] = 0x00
    Write-Le16 $catalog 98 0
    $catalog[100] = 0
    Write-Le16 $catalog 102 ([int][Math]::Ceiling($uefiImage.Length / 512.0))
    Write-Le32 $catalog 104 $uefiImageLba
    Put-Sector $iso $bootCatalogLba $catalog

    [Array]::Copy($bootImage, 0, $iso, $bootImageLba * 2048, $bootImage.Length)
    [Array]::Copy($uefiImage, 0, $iso, $uefiImageLba * 2048, $uefiImage.Length)
    [Array]::Copy($efiFile, 0, $iso, $efiFileLba * 2048, $efiFile.Length)
    [Array]::Copy($readme, 0, $iso, $readmeLba * 2048, $readme.Length)

    $outDir = Split-Path -Parent $OutputPath
    if ($outDir) {
        New-Item -ItemType Directory -Force -Path $outDir | Out-Null
    }
    [System.IO.File]::WriteAllBytes($OutputPath, $iso)
}

New-UefiFatImage `
    -EfiFilePath $BootEfi `
    -OutputPath $UefiImg `
    -LogoPath (Join-Path $Root "assets\CaYaDev.svg") `
    -FontPath (Join-Path $Root "assets\Consolas.ttf") `
    -DriverDir (Join-Path $Root "drivers") `
    -CyxDir (Join-Path $Root "assets\cyx")
New-BootableIso $BootImg $BootEfi $UefiImg $IsoFullPath

Write-Host ""
Write-Host "OK"
Write-Host "Stage16: $($Stage16Bytes.Length) bytes"
Write-Host "Kernel32: $($KernelBytes.Length) bytes"
Write-Host "BOOTX64.EFI: $((Get-Item $BootEfi).Length) bytes"
Write-Host "Boot payload: $($KernelPayload.Length) bytes / $KernelSectors sectors"
Write-Host "Boot image: $BootImg"
Write-Host "UEFI image: $UefiImg"
Write-Host "ISO: $IsoFullPath"

if ($Run) {
    $Qemu = Find-Exe @("qemu-system-i386")
    Require-Tool $Qemu "QEMU bulunamadi. ISO olustu ama calistirma yapilamadi."
    Invoke-Tool $Qemu @("-m", "128M", "-cdrom", $IsoFullPath, "-boot", "d")
}
