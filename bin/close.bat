@echo off
rem taskkill /f /im pause.exe /im netchatC.exe
rem taskkill /f /im netchatC.exe /im pause.exe

rem /im��������, /f:ǿ�ƹر�,/t:�رս�����(netchatC.exe��������pause.exe)
taskkill /im iocp_ex_client.exe /f /t  
     
rem pause