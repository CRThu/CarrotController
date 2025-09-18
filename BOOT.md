## STLink    
所需软件: STM32 ST-LINK Utility v4.6.0, stm32cubeprg    
在CN6(controller)/H5(mini)使用STLink下载固件STLinkV2.J28.M18.bin    
使用ST-Link Utility 4.6.0下载后升级，再使用最新的STM32CubeProgrammer升级到最新版本  
20250912:使用最新的STM32CubeProgrammer 2.20可直接下载并升级STLink固件，无需多次跨版本升级   
先供电，再连接swd线，最后接入stlink，否则可能不识别 
连接后无法读取尝试重连，以及OB标签页关闭读保护RDP   

## ESP32    
** 仅stm32h563_controller **    
所需软件: zadig, ESP-IDF       
使用zadig安装驱动   
Interface0:cdc  
Interface2:winusb   
安装ESP-IDF 
cd examples 
cd get-started  
cd hello_world  
Idf.py set-target esp32-s3  
Idf.py menuconfig   
Idf.py build    
idf.py -p COM21 flash (COM21:USB JTAG/serial debug unit(interface0))    
或串口下载  
idf.py -p COM20 flash(COM20:CH343)  
若因为路径不同无法build，运行 idf.py fullclean   

## FT2232H  
** 仅stm32h563_controller **    
所需软件: FT_Prog   
FTPROG配置A为FIFO+D2XX  
FTPROG配置B为RS232+VCP  
