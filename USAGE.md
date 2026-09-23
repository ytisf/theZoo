# theZoo — Usage Guide

> **WARNING: This repository contains LIVE and DANGEROUS malware.**
> All samples are encrypted with password `infected` (AES-256).
> **Do NOT run or extract samples unless you are operating inside an isolated, air-gapped VM with no network access or shared folders.**
> theZoo is intended exclusively for malware research, analysis, and education.

---

## Table of Contents

1. [Requirements](#1-requirements)
2. [Installation](#2-installation)
3. [Quickstart](#3-quickstart)
4. [CLI Reference](#4-cli-reference)
5. [Graphical Interfaces](#5-graphical-interfaces)
6. [Working with Samples](#6-working-with-samples)
7. [Compiling Source Code Samples](#7-compiling-source-code-samples)
8. [Database Catalog](#8-database-catalog)
9. [Contributing New Samples](#9-contributing-new-samples)
10. [Known Limitations](#10-known-limitations)
11. [Safe Analysis Environment Setup](#11-safe-analysis-environment-setup)

---

## 1. Requirements

| Dependency | Minimum Version | Purpose |
|---|---|---|
| Python | 3.8+ | Runtime |
| pyzipper | 0.4.0+ | AES-256 archive extraction |
| urllib3 | 1.26+ | HTTP downloads |
| streamlit | latest | Streamlit GUI (optional) |

Install all at once:

```bash
pip install -r requirements.txt
```

---

## 2. Installation

```bash
# Clone the full repository (all samples included)
git clone --recurse-submodules https://github.com/ytisf/theZoo.git
cd theZoo

# Install Python dependencies
pip install -r requirements.txt
```

> **Note for Windows users:** If `readline` is unavailable, the CLI will attempt to install `winreadline` automatically. Run PowerShell as Administrator if needed.

---

## 3. Quickstart

```bash
# Start the interactive CLI
python theZoo.py

# List all available samples
python theZoo.py
mdb #> list all

# Search by type, platform, or name
mdb #> search ransomware
mdb #> search android trojan
mdb #> search wannacry

# Select a malware by ID
mdb #> use 42

# Get info about selected malware
mdb #> info

# Download selected malware to current directory
mdb #> get

# Update the database from GitHub
mdb #> update-db

# Exit
mdb #> exit
```

---

## 4. CLI Reference

### Global commands

| Command | Description |
|---|---|
| `list all` | Print the full catalog with ID, name, and type |
| `search <terms>` | Free-text search across name, type, platform, language, tags |
| `use <id>` | Select a malware entry by its numeric ID |
| `info` | Display full metadata for the currently selected entry |
| `get` | Download the selected sample's `.zip`, `.pass`, `.md5`, and `.sha256` files |
| `update-db` | Fetch the latest `conf/maldb.db` from the upstream GitHub repository |
| `report-mal` | Interactive form to report a new malware for submission |
| `help` | Print available commands |
| `exit` / `quit` | Exit the CLI |

### Command-line flags

```bash
python theZoo.py --help
python theZoo.py --filter ransomware windows   # pre-filter on startup
python theZoo.py --update                      # run update-db and exit
python theZoo.py --version                     # print version string
python theZoo.py --license                     # print GPL v3 text
```

### Tab completion

Tab completion is active in the CLI for all commands. Press `Tab` once to complete, twice to list options.

---

## 5. Graphical Interfaces

### Streamlit web UI (recommended)

```bash
python theZoo_streamlit.py
# Opens in browser at http://localhost:8501
```

### Tkinter GUI

```bash
python theZoo_gui.py
```

> The Tkinter GUI requires `tkinter` (usually bundled with Python on Windows/macOS; on Debian/Ubuntu: `sudo apt install python3-tk`).

---

## 6. Working with Samples

### Archive format

All samples in theZoo are stored as **AES-256 encrypted ZIP archives**.

| Extension | Contents |
|---|---|
| `<name>.zip` | AES-256 encrypted archive containing the malware |
| `<name>.pass` | Plain-text file with the archive password |
| `<name>.md5` | MD5 hash of the encrypted `.zip` file |
| `<name>.sha256` / `<name>.shasum` | SHA-256 hash of the encrypted `.zip` file |

### Default password

The password for all samples in this repository is:

```
infected
```

### Extracting manually

**Using pyzipper (Python — recommended, preserves AES-256):**

```python
import pyzipper

with pyzipper.AESZipFile('WannaCry.zip') as zf:
    zf.setpassword(b'infected')
    zf.extractall('/tmp/analysis/')
```

**Using 7-Zip (command-line):**

```bash
7z x WannaCry.zip -pinfected -o/tmp/analysis/
```

> **Always extract inside an isolated VM.** Never extract malware on a host system.

### Verifying integrity

```bash
# Verify SHA-256 hash before extraction
sha256sum WannaCry.zip
cat WannaCry.sha256   # compare output

# MD5
md5sum WannaCry.zip
cat WannaCry.md5
```

---

## 7. Compiling Source Code Samples

theZoo includes both **binaries** (`malware/Binaries/`) and **source code** (`malware/Source/`).

### Source directory structure

```
malware/Source/
├── Original/    # Original source code (compilable)
└── Reversed/    # Decompiled / reversed source code
```

### Prerequisites by language

| Language | Toolchain |
|---|---|
| C / C++ | `gcc`, `g++`, MSVC (Windows) |
| Visual Basic (VB) | Visual Studio, VB 6 runtime |
| ASM (x86/x64) | NASM, MASM, FASM |
| Java | JDK 8+ |
| Android (APK) | Android Studio, Gradle, JDK 17 |
| Python | CPython 3.8+ |
| PHP | PHP 7.4+ |

### Example: compiling a C botnet

```bash
# 1. Extract source
python3 -c "
import pyzipper
with pyzipper.AESZipFile('Win32.TinyNuke.zip') as zf:
    zf.setpassword(b'infected')
    zf.extractall('/tmp/tinynuke/')
"

# 2. Build (inside isolated VM — Linux cross-compile for Win32)
cd /tmp/tinynuke/Win32.TinyNuke/
sudo apt install mingw-w64
i686-w64-mingw32-gcc *.c -o tinynuke.exe -lws2_32 -lwininet

# 3. Analyse with static analysis BEFORE running
file tinynuke.exe
strings tinynuke.exe | grep -E "http|cmd|reg"
```

### Example: building an Android APK

```bash
# 1. Extract
python3 -c "
import pyzipper
with pyzipper.AESZipFile('Android.OctoBankBot.zip') as zf:
    zf.setpassword(b'infected')
    zf.extractall('/tmp/octobankbot/')
"

# 2. Open in Android Studio (inside VM)
# OR build from CLI:
cd /tmp/octobankbot/Android.OctoBankBot/
./gradlew assembleDebug

# APK will be at: app/build/outputs/apk/debug/app-debug.apk
```

> **Warning:** Never run compiled malware outside a fully isolated, snapshotted VM with:
> - No internet access
> - No shared folders or clipboard sync
> - No guest additions installed

---

## 8. Database Catalog

The malware catalog is stored in `conf/maldb.db` — a standard SQLite3 database.

```bash
# Browse with sqlite3
sqlite3 conf/maldb.db

# List all entries
sqlite3 conf/maldb.db "SELECT ID, NAME, TYPE, PLATFORM FROM Malwares ORDER BY ID"

# Search by type
sqlite3 conf/maldb.db "SELECT ID, NAME FROM Malwares WHERE TYPE='ransomware'"

# Search by platform
sqlite3 conf/maldb.db "SELECT ID, NAME, TYPE FROM Malwares WHERE PLATFORM='android'"
```

### Database schema

| Column | Type | Description |
|---|---|---|
| `ID` | INTEGER | Primary key |
| `LOCATION` | TEXT | Relative path to the sample directory |
| `TYPE` | TEXT | `botnet`, `trojan`, `ransomware`, `rootkit`, `worm`, `apt`, `dropper`, `exploitkit`, `spyware`, `virus` |
| `NAME` | TEXT | Common name |
| `VERSION` | TEXT | Version string |
| `AUTHOR` | TEXT | Known author / group |
| `LANGUAGE` | TEXT | `c`, `cpp`, `vb`, `asm`, `java`, `apk`, `php`, `python`, `bin` |
| `DATE` | DATE | Date of first known appearance |
| `ARCHITECTURE` | TEXT | `x86`, `x64`, `arm`, `web` |
| `PLATFORM` | TEXT | `win32`, `win64`, `android`, `ios`, `mac`, `*nix32`, `*nix64` |
| `VIP` | BOOLEAN | 1 = high-priority / notable sample |
| `COMMENTS` | TEXT | Free-text notes |
| `TAGS` | TEXT | Comma-separated tags |

---

## 9. Contributing New Samples

See [CONTRIBUTING.md](CONTRIBUTING.md) for full guidelines.

### Quick reference

```bash
# 1. Prepare the archive (creates OUTPUT/ directory with .zip, .pass, .md5, .sha)
python prep_file.py /path/to/malware_file

# 2. Move the OUTPUT/ contents to the appropriate malware directory
mkdir -p malware/Binaries/Win32.MyMalware/
mv OUTPUT/malware_file.* malware/Binaries/Win32.MyMalware/

# 3. Add a row to the database (use any SQLite3 editor)
sqlite3 conf/maldb.db
INSERT INTO Malwares(ID, LOCATION, TYPE, NAME, LANGUAGE, ARCHITECTURE, PLATFORM, VIP)
VALUES (376, 'malware/Binaries/Win32.MyMalware', 'trojan', 'MyMalware', 'c', 'x86', 'win32', 0);

# 4. Open a Pull Request
git checkout -b add/Win32.MyMalware
git add malware/Binaries/Win32.MyMalware/ conf/maldb.db
git commit -m "feat(samples): add Win32.MyMalware trojan"
gh pr create --repo ytisf/theZoo --title "feat(samples): add Win32.MyMalware"
```

### Naming conventions

```
malware/
├── Binaries/         # Pre-compiled executables, DLLs, APKs
│   └── <OS>.<Name>/  # e.g. Win32.WannaCry, Android.Cerberus
└── Source/
    ├── Original/     # Compilable original source code
    └── Reversed/     # Decompiled/reversed source
        └── <OS>.<Name>/
```

File naming inside the directory **must** match the directory name exactly:

```
malware/Binaries/Win32.WannaCry/
├── Win32.WannaCry.zip     ← AES-256 ZIP (password: infected)
├── Win32.WannaCry.pass    ← contains: infected
├── Win32.WannaCry.md5     ← MD5 of the .zip
└── Win32.WannaCry.sha256  ← SHA-256 of the .zip
```

---

## 10. Known Limitations

| Sample | Issue | Status |
|---|---|---|
| `Win32.Sality` | Archive format is RAR disguised as `.zip`; extraction yields 0-byte file (CRC error in source archive) | Cannot fix without original binary |
| `Win32.Ixeshe` | Same as above | Cannot fix without original binary |
| `Android.CEREBRUS` | Previously stored as split archive (`.zip.001`/`.zip.002`); combined and re-encrypted in v0.7.2 | Fixed in PR#243 |
| Samples with `LOCATION` pointing to empty directories | 5 entries: Fargus (ID 98), LeoxBot (ID 199), DarkHydrus (ID 311), StealthyTrident (ID 337), Talerat (ID 350) | Samples genuinely absent from repo |

---

## 11. Safe Analysis Environment Setup

### Recommended VM configuration

```
Hypervisor:       VirtualBox 7.x / VMware Workstation / KVM
RAM:              4 GB minimum, 8 GB recommended
Disk:             40 GB (snapshot-capable)
Network:          Host-only adapter (NO NAT, NO bridged)
Shared folders:   DISABLED
Guest additions:  NOT installed
Clipboard sync:   DISABLED
Drag-and-drop:    DISABLED
```

### Recommended analysis tools (install inside VM)

| Tool | Purpose |
|---|---|
| [x64dbg](https://github.com/x64dbg/x64dbg) | Dynamic analysis / debugging |
| [qiling](https://github.com/qilingframework/qiling) | Cross-arch binary emulation |
| [al-khaser](https://github.com/ayoubfaouzi/al-khaser) | Anti-VM/sandbox evasion testing |
| Ghidra / IDA Free | Static disassembly |
| Wireshark | Network traffic capture |
| Regshot | Registry diff |
| ProcMon | System call monitoring |

### Basic analysis workflow

```bash
# 1. Snapshot VM before analysis
# 2. Extract sample inside VM
python3 -c "
import pyzipper
with pyzipper.AESZipFile('sample.zip') as zf:
    zf.setpassword(b'infected')
    zf.extractall('.')
"
# 3. Perform static analysis first (strings, PE headers, imports)
strings sample.exe
file sample.exe

# 4. Only then run dynamically under a debugger/monitor
# 5. Restore snapshot when done
```

---

*theZoo v0.7.2 — maintained by [ytisf](https://github.com/ytisf) and community contributors.*
*See [CONTRIBUTING.md](CONTRIBUTING.md) and [CODE-OF-CONDUCT.md](CODE-OF-CONDUCT.md) before submitting.*
