## 板上管脚分配 

### KEY/LED 

| NAME      | PIN   | DIR   | NO    | 
| -         | -     | -     | -     | 
| KEYA      | PF10  | I     | 22    | 
| LEDA      | PF08  |  O    | 20    | 
| LEDB      | PF09  |  O    | 21    | 
 
### UART A 
| NAME      | PIN   | DIR   | NO    | 
| -         | -     | -     | -     | 
| UART4_TX  | PA12  |  O    | 104   | 
| UART4_RX  | PA11  | I     | 103   | 
 
### UART B 

default: H10 header 

| NAME      | PIN   | DIR   | NO    | 
| -         | -     | -     | -     | 
| H10-TXD   | H10-2 |  O    |       | 
| H10-RXD   | H10-3 | I     |       | 

using UART5: short R305, R306 

| NAME      | PIN   | DIR   | NO    | 
| -         | -     | -     | -     | 
| UART5_TX  | PB13  |  O    | 74    | 
| UART5_RX  | PB15  | I     | 76    |

using UART1(or from DUT): short R303, R304 

| NAME      | PIN   | DIR   | NO    | 
| -         | -     | -     | -     | 
| UART1_TX  | PA09  | IO    | 101   | 
| UART1_RX  | PA10  | IO    | 102   | 
 
### USB FS 

default: NC 
using usbfs: short R301, R302 

| NAME      | PIN   | DIR   | NO    | 
| -         | -     | -     | -     | 
| USB_DM    | PA11  | IO    | 103   | 
| USB_DP    | PA12  | IO    | 104   | 
 
### PSRAM 

default: NC
using psram: place APS6404L-3SQN-SN(3.3V) or APS6404L-SQN-SN(1.8V)

| NAME      | PIN   | DIR   | NO    | 
| -         | -     | -     | -     |
| OSPI_NCS  | PE11  |  O    | 64    |
| OSPI_CLK  | PB02  |  O    | 48    |
| OSPI_IO0  | PB01  | IO    | 47    |
| OSPI_IO1  | PB00  | IO    | 46    |
| OSPI_IO2  | PA07  | IO    | 43    |
| OSPI_IO3  | PA06  | IO    | 42    |
| OSPI_IO4  | PE07  | IO    | 58    |
| OSPI_IO5  | PE08  | IO    | 59    |
| OSPI_IO6  | PE09  | IO    | 60    |
| OSPI_IO7  | PE10  | IO    | 63    |

### IIC 

default: shared with dut iic

| NAME      | PIN   | DIR   | NO    | 
| -         | -     | -     | -     | 
| IIC2_SCL  | PB10  | IO    | 69    | 
| IIC2_SDA  | PB12  | IO    | 73    | 

## BTB管脚分配 
| BTB NAME      | PIN   | MCU PIN   | ALT                   | 
| -             | -     | -         | -                     | 
| CLK1	        | 11    | PA01      | R123: PC04            | 
| CLK2	        | 13    | PA00      |                       | 
| CLK3	        | 12    | PC02      |                       | 
| CLK4	        | 14    | PC03      |                       | 
| CLK5	        | 18    | PA02      | R126: PC00            | 
| CLK6	        | 20    | PA03      | R127: PC01            | 
| SPIA_NSS/CS0  | 17    | PA04      |                       | 
| SPIA_SCK      | 23    | PB03      |                       | 
| SPIA_MOSI     | 25    | PB05      |                       | 
| SPIA_MISO     | 27    | PB04      |                       | 
| SPIB_NSS/CS1  | 19    | PA15      |                       | 
| SPIB_SCK      | 24    | PC10      | R295: SPIA_SCK(PB03)  | 
| SPIB_MOSI     | 26    | PC12      |                       | 
| SPIB_MISO     | 28    | PC11      |                       | 
| CS2           | 32    | PC06      |                       | 
| CS3           | 31    | PC07      |                       | 
| D00           | 34    | PD00      |                       | 
| D01           | 36    | PD01      |                       | 
| D02           | 38    | PD02      |                       | 
| D03           | 40    | PD03      |                       | 
| D04           | 42    | PD04      |                       | 
| D05           | 44    | PD05      |                       | 
| D06           | 46    | PD06      | LVIO(default: 1.8V)   | 
| D07           | 48    | PD07      | LVIO(default: 1.8V)   | 
| D08           | 33    | PD08      |                       | 
| D09           | 35    | PD09      |                       | 
| D10           | 37    | PD10      |                       | 
| D11           | 39    | PD11      |                       | 
| D12           | 41    | PD12      |                       | 
| D13           | 43    | PD13      |                       | 
| D14           | 45    | PD14      |                       | 
| D15           | 47    | PD15      |                       | 
| RDL           | 50    | PE13      |                       | 
| WRL           | 52    | PE15      |                       | 
| RDH           | 49    | PE12      |                       | 
| WRH           | 51    | PE14      |                       | 
| UART_TXD      | 55    | PA09      |                       | 
| UART_RXD      | 57    | PA10      |                       | 
| IIC_SDA       | 56    | PB12      |                       | 
| IIC_SCL       | 58    | PB10      |                       | 

## HDR管脚分配 
### H7 HDR(BTB SIGNAL) 
| PIN   | NO    | NO    | PIN   | 
| -     | -     | -     | -     | 
| PC02  | 01    | 02    | PA01  | 
| PC03  | 03    | 04    | PA00  | 
| PA02  | 05    | 06    | PA04  | 
| PA03  | 07    | 08    | PA15  | 
| PC10  | 09    | 10    | PB03  | 
| PC12  | 11    | 12    | PB05  | 
| PC11  | 13    | 14    | PB04  | 
| PC06  | 15    | 16    | PC07  | 
| PD00  | 17    | 18    | PD08  | 
| PD01  | 19    | 20    | PD09  | 
| PD02  | 21    | 22    | PD10  | 
| PD03  | 23    | 24    | PD11  | 
| PD04  | 25    | 26    | PD12  | 
| PD05  | 27    | 28    | PD13  | 
| PD06  | 29    | 30    | PD14  | 
| PD07  | 31    | 32    | PD15  | 
| PE13  | 33    | 34    | PE12  | 
| PE15  | 35    | 36    | PE14  | 
| PB12  | 37    | 38    | PA09  | 
| PB10  | 39    | 40    | PA10  | 

### H8 HDR 
| PIN   | NO    | NO    | PIN   | 
| -     | -     | -     | -     | 
| PB06  | 01    | 02    | PG15  | 
| PE00  | 03    | 04    | PB07  | 
| PE03  | 05    | 06    | PE02  | 
| PE05  | 07    | 08    | PE04  | 
| PF00  | 09    | 10    | PE06  | 
| PF02  | 11    | 12    | PF01  | 
| PF04  | 13    | 14    | PF03  | 
| PF06  | 15    | 16    | PF05  | 
| PC00  | 17    | 18    | PF07  | 
| PA05  | 19    | 20    | PC01  | 
| PC05  | 21    | 22    | PC04  | 
| PF12  | 23    | 24    | PF11  | 
| PF14  | 25    | 26    | PF13  | 
| PG00  | 27    | 28    | PF15  | 
| PB15  | 29    | 30    | PG01  | 
| PG03  | 31    | 32    | PG02  | 
| PG05  | 33    | 34    | PG04  | 
| PG07  | 35    | 36    | PG06  | 
| PC08  | 37    | 38    | PG08  | 
| PA08  | 39    | 40    | PC09  | 

### H13 LVIO HDR 
| PIN   | NO    | NO    | PIN   | 
| -     | -     | -     | -     | 
| VIO2  | 01    | 02    | VIO2  | 
| PB09  | 03    | 04    | PB08  | 
| PG14  | 05    | 06    | PG13  | 
| PG12  | 07    | 08    | PG11  | 
| PG10  | 09    | 10    | PG09  | 
| PD07  | 11    | 12    | PD06  | 
| GND   | 13    | 14    | GND   | 