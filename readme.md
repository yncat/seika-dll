# Unofficial seika client library

## Motivation

Seika is apparently shipped with seikaDevice.dll, an official seika client library. But! It's broken, and there's no sdk available as far as I know.

Even in the latest NVDA, the built-in seika driver doesn't work. The only working solution at the moment is installing an addon, in which communication with the seika device is performed using raw serial IO.

I just rewrote a similar communication protocol and made it usable as a dll.

## Limitations

Since it's currently focused on my own usecase and I have only one seika device, the library is not perfect. Here is the list of limitations and known issues:
- It works for Seika v3 pro, but other devices are not tested. Braille display and cursor routing may work, but other key bindings most likely won't. It does not necessarily mean I'm not going to implement support for other devices, but I simply do not have devices to test.
- number of cells are hardcoded to 40!!!!!!!!!!!!!!!
- I don't know button names for seika at all, so button name enum isn't good.
- The original implementation had included seika80 identification, but I did not implement it since I was not able to test.
- Currently using a third-party library for serial IO (https://www.vector.co.jp/download/file/winnt/util/fh539143.html). It's better to use Windows native API for this, but I just cut a coner.

## API
```
SEIKA_API DWORD seikaOpen(DWORD port);
port: COM port number.
returns: true on success, false on failure.
SEIKA_API DWORD seikaGetCells();
returns: number of cells.
SEIKA_API char* seikaGetDeviceName();
returns: A pointer to char which holds the device name.
SEIKA_API VOID seikaDisplay(const char* bytes, DWORD size);
bytes: braille bytes. each byte represents a single cell. Dot pattern is described in enums in the header.
size: length of the bytes.
SEIKA_API DWORD seikaGetKey();
returns: key enums in the header. When cursor routing key is pressed, return 100+(cell counting from the left side).
SEIKA_API VOID seikaClose();
```




