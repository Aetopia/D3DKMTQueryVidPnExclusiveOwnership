# D3DKMTQueryVidPnExclusiveOwnership
This project provides the following:
- An example of how to use the `D3DKMTQueryVidPnExclusiveOwnership` function.
- A way to easily detect if a process uses Exclusive Fullscreen, Emulated Fullscreen or Windowed.

## Usage
1. Open an application that is able to acquire exclusive ownership to the display its present on.
2. Open a Command Prompt window and do the following:

    - Navigate to the directory where the binary is present.
    - Invoke the binary as follows:

        ```cmd
        timeout 5 & D3DKMTQueryVidPnExclusiveOwnership.exe
        ```
3. Switch to the application and have it acquire exclusive ownership.

4. `D3DKMTQueryVidPnExclusiveOwnership.exe` will spawn a message box displaying the owner type for the foreground process, switch to this window once the timeout has elapsed.

### Owner Types
|Owner Type|Description|
|-|-|
|Not owned.|The foreground process doesn't have exclusive ownership of a display.|
|Shared.|The foreground process has the ability to yield exclusive ownership of a display to other processes with exclusive ownership.|
|Exclusive.|The foreground process has sole exclusive ownership of a display.|
|Exclusive GDI.|The foreground process has sole exclusive ownership of a display alongside a shared primary GDI surface.|
|Emulated.|The foreground process doesn't have sole exclusive ownership of a display but emulates having exclusive ownership.|

> [!NOTE]
> You may read more in depth on this topic by checking out [Presentation Model on Special K's wiki](https://wiki.special-k.info/Presentation_Model).

## Build
1. Install [GCC](https://winlibs.com/) & [UPX](https://upx.github.io).
2. Run [Build.cmd](Build.cmd).
