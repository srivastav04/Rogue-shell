# Rogue-shell

A miniature Unix shell written in **C**, designed to demonstrate core Unix process-management and shell concepts.

## Requirements

* Linux / Unix-like operating system
* GCC
* Make

> **Note:** Rogue-shell is designed for Linux and Unix-like systems and will not run natively on Windows.

## Build

Clone the repository and navigate to the project directory:

```bash
git clone <repository-url>
cd Rogue-shell
```

Build the project using `make`:

```bash
make
```

This will generate the `shell` executable.

## Run

Make the executable runnable:

```bash
chmod +x shell
```

Start Rogue-shell:

```bash
./shell
```

You should see:

```text
Welcome to Rogue!
```

## Running on WSL

If you are using **Windows Subsystem for Linux (WSL)** and have downloaded the pre-built `shell` executable to your Windows Downloads folder:

### 1. Copy the executable to WSL

Replace `[name]` with your Windows username:

```bash
cp /mnt/c/Users/[name]/Downloads/shell ~/Downloads/
```

Navigate to the Downloads directory:

```bash
cd ~/Downloads
```

### 2. Check the executable

```bash
file shell
```

Example:

```text
shell: ELF 64-bit LSB pie executable, x86-64, version 1 (SYSV), dynamically linked, ...
```

### 3. Make it executable

```bash
chmod +x shell
```

### 4. Run Rogue-shell

```bash
./shell
```

## Examples

### Execute a command

```text
$ echo Hello World
```


### Exit the shell

```text
$ exit
```



## License

This project is intended for educational and learning purposes.
