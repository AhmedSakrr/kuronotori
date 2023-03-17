## `🩸` Kuro No Tori

<p align="center" width="100%">
    <img width="30%" src="https://user-images.githubusercontent.com/59679082/220690535-7516365f-3383-4385-b7b2-d511d8fb1d17.png">
</p>

<div id="header" align="center">

![Visual Studio](https://img.shields.io/badge/Visual%20Studio-5C2D91.svg?style=for-the-badge&logo=visual-studio&logoColor=white)
![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![Windows](https://img.shields.io/badge/Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white)

</div>

`Kuro No Tori` is a simple injector made in C++. I've been attempting to learn [low-level](https://github.com/cr-0w/low-level) (C, C++, Win32 API, ...) stuff pertaining to [malware-development](https://github.com/cr-0w/MALDEV) and this project, although a combination of everything I've learned so far, seemed like it deserved its own repository - where I could continously develop this as I learn more and more.


- [⚠️ **Disclaimer**](https://github.com/cr-0w/kuronotori#-Disclaimer)
- [🎉 **Features**](https://github.com/cr-0w/kuronotori#-Features)
- [🔮 **For The Future**](https://github.com/cr-0w/kuronotori#-For-The-Future)
- [💽 **Installation**](https://github.com/cr-0w/kuronotori#-Installation)
- [🍀 **Demos**](https://github.com/cr-0w/kuronotori#-Demos)

> **Note**: *Where it stands currently, the injector is quite primitive - although I hope that changes soon.* 😊

## `⚠️` Disclaimer

This is strictly for educational purposes. I am not responsible for what you choose to do with this tool. I do not condone attacking that which you do not have explicit permission to do so.

## `🎉` Features

Currently, the injector is capable of:

- Enumerating current processes using [`WTSEnumerateProcessesEx()`](https://learn.microsoft.com/en-us/windows/win32/api/wtsapi32/nf-wtsapi32-wtsenumerateprocessesexw).
- Allowing you to specify the PID you'd like to inject into.
- Performing shellcode injection using the super basic/vanilla [`CreateRemoteThread()/CreateRemoteThreadEx()`](https://learn.microsoft.com/en-us/windows/win32/api/processthreadsapi/nf-processthreadsapi-createremotethread) method.
- Performing DLL injection using the [`LoadLibrary()`](https://learn.microsoft.com/en-us/windows/win32/api/libloaderapi/nf-libloaderapi-loadlibrarya?redirectedfrom=MSDN) and [`GetModuleHandleA()`](https://learn.microsoft.com/en-us/windows/win32/api/libloaderapi/nf-libloaderapi-getmodulehandlea) APIs.
- Asking you for time (in seconds) that you'd like the program to sleep for. This is currently a placeholder for some actual sleeping techniques like [DeathSleep](https://github.com/janoglezcampos/DeathSleep) until I can figure out how to implement something similar.

## `🔮` For The Future

- No CRT.
- Show SID.
- Show process owner.
- ~~Aesthetics update.~~ ✅
- Show process privileges.
- Add in the ability for dynamic shellcode support.
- Try messing around with NTDLL/NTAPI; slowly start removing wrappers. A point where I can start messing around with `syscalls` would be awesome.
- ~~Add in the ability for more process injection techniques like `DLL Injections`; currently the program only supports the very basic [`CreateRemoteThread()`](https://learn.microsoft.com/en-us/windows/win32/api/processthreadsapi/nf-processthreadsapi-createremotethread) shellcode injection.~~ ✅

## `💽` Installation

To start using the program, open the solution (`kuronotori.sln` file), and build the solution. Once you've done that, you can interact with the program by running the executable.

```
C:\> kuronotori.exe
```

## `🍀` Demos 

## `💉` `Shellcode Injection`


https://user-images.githubusercontent.com/59679082/225786351-b7be291a-84ad-46eb-a40a-b894f4d9d946.mp4

<br>

## `💉` `DLL Injection`

https://user-images.githubusercontent.com/59679082/225786376-a82a87cf-a825-4f30-8aac-fc9a19a85f01.mp4
