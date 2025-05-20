# Analog TV Tools project
This project focuses on developing a suite of software tools for decoding analog TV signals. The current toolset includes two primary components:
- **Command Line Interface (CLI)** for anlog TV decoder: This command line tool enables the conversion of digitized analog CVBS SECAM signals into standard AVI video files. For using examples please see the tests at [https://github.com/rukhov/analog-tv-tools/tree/main/pytests](https://github.com/rukhov/analog-tv-tools/tree/main/pytests).
- **AnalogTv/TvDecode** GNU Radio Block: This component allows integration of the Analog TV decoder into the [GNU Radio](https://wiki.gnuradio.org/) ecosystem.

## Samples

### Decoded video fragment
https://github.com/user-attachments/assets/aca3b354-d356-47e6-95f8-39b7d00446ff

For encoding the [hacktv](https://github.com/fsphil/hacktv) tool was used.
### Using the Analog TV Decoder with GNU radio ecosystem.
![GnuRadio-color-bars](https://github.com/user-attachments/assets/5d9b85ac-ec47-4c62-a662-037f1fb34b48)

## Build
You can download pre-built binaries from the GitHub Actions page: https://github.com/rukhov/analog-tv-tools/actions.
Locate the most recent successful build, and download the artifacts compatible with your operating system.

##
Copyright &copy; 2025 Roman Ukhov
