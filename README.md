# CarrotController 
STM32H563ZIT6核心控制板，主要用于DUT测试与上位机交互，项目软硬件均开源，可根据需求二次开发。    

## 硬件详情 
### stm32h563_controller    
主控：STM32H563ZIT6 
特点：含下载器、片外RAM、板对板接口、高速通信和时钟芯片 
|文件|链接| 
|-|-|   
|原始工程 Ver.A|[LCEDA](https://oshwhub.com/hardware-technology-research/stm32h563_controller) |  
|SCH PDF Ver.A|[SCH PDF](https://github.com/CRThu/CarrotController/blob/main/PCB/SCH.stm32h563_controller.Ver.A.pdf) |  
|PCB PDF Ver.A|[PCB PDF](https://github.com/CRThu/CarrotController/blob/main/PCB/PCB.stm32h563_controller.Ver.A.pdf) |  

### stm32h563_controller_mini    
主控：STM32H563ZIT6核心板   
特点：含下载器、片外RAM、板对板接口、排针、多电源域供电可调 
|文件|链接| 
|-|-|   
|原始工程 Ver.A|[LCEDA](https://oshwhub.com/hardware-technology-research/stm32h563_controller_mini) |    
|SCH PDF Ver.A|[SCH PDF](https://github.com/CRThu/CarrotController/blob/main/PCB/SCH.stm32h563_controller_mini.Ver.A.pdf) |  
|PCB PDF Ver.A|[PCB PDF](https://github.com/CRThu/CarrotController/blob/main/PCB/PCB.stm32h563_controller_mini.Ver.A.pdf) |  

## 使用说明 
- 首次使用根据boot.md进行初始化配置方可正常运行 
- IO和外设初始化需在CubeMX中定义和更新（如果需要两个核心板兼容，需要同时修改两个CubeMX文件）  
- 驱动需要写在APP文件夹，在每个Keil工程内引入需要的.c文件   
- main.c需要根据每个Keil工程编写一份，由于项目间不互通，建议只加入抽象函数，具体实现在APP中 