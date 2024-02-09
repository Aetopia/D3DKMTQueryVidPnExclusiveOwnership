@echo off
cd "%~dp0"
gcc -mwindows -nostdlib -Os -s WinMain.c -lUser32 -lKernel32 -lGdi32 -o D3DKMTQueryVidPnExclusiveOwnership.exe
upx --best --ultra-brute D3DKMTQueryVidPnExclusiveOwnership.exe>nul 2>&1