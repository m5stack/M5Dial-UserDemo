
# M5Dial-UserDemo

M5Dial user demo for hardware evaluation.

## Environment set up

To start using ESP-IDF on ESP32, install the following software:

* Toolchain to compile code for ESP32
* Build tools - CMake and Ninja to build a full Application for ESP32
* ESP-IDF that essentially contains API (software libraries and source code) for ESP32 and scripts to operate the Toolchain

![What you need to know](./assets/images/what-you-need.png)

### Installation

To install all the required software, we offer some different ways to facilitate this task. Choose from one of the available options.

More information can be found [ESP-IDF v5.1](https://docs.espressif.com/projects/esp-idf/en/release-v5.1/esp32/index.html)

#### IDE

* [Eclipse Plugin](https://github.com/espressif/idf-eclipse-plugin/blob/master/README.md)
* [VSCode Extension](https://github.com/espressif/vscode-esp-idf-extension/blob/master/docs/tutorial/install.md)

#### Manual Installation

> For the manual procedure, please select according to your operating system.

* [Windows Installer](https://docs.espressif.com/projects/esp-idf/en/release-v5.1/esp32/get-started/windows-setup.html)
* [Linux and macOS](https://docs.espressif.com/projects/esp-idf/en/release-v5.1/esp32/get-started/linux-macos-setup.html)

### Build

```bash
git clone https://github.com/m5stack/M5Dial-UserDemo.git
cd M5Dial-UserDemo
idf.py build
```
