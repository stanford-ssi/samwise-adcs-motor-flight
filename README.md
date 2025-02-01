# SAMWISE ADCS Flight Software
Flight Software for the SAMWISE ADCS board

## Install Instructions
Follow [the flight software onboarding doc](docs/ONBOARDING.md) for development environment setup.

Run `source configure.sh` for initial repository setup.

**Note: Only Mac and Linux are supported. If you are on Windows, create a Linux VM**

## Building instructions
Enter the `build` folder:
```
cd build
```

Run `cmake` (Note: this is usually only necessary if you have added, moved, or deleted files):
```
cmake ..
```

Make the project:
```
make -j8
```






### Useful Links
* [Picubed flight software repo](https://github.com/stanford-ssi/samwise-flight-software)
* [ADCS sims repo](https://github.com/stanford-ssi/samwise-adcs-sims)
