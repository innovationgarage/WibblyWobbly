# WibblyWobbly
Tiny data collector based on a ESP8266

![](images/device.png)

# Parts

* Wemos D1 https://www.aliexpress.com/item/10pcs-D1-PRO-Battery-Shield-D1-mini-Mini-NodeMcu-4M-bytes-Lua-WIFI-Internet-of-Things/32832670731.html
* Battery shield https://www.aliexpress.com/item/D1-Mini-Battery-Shield-Lithium-Battery-Charging-Boost-With-LED-Light-Module-Mini-Micro-USB-Interface/32798209192.html
* RTC SD shield https://www.aliexpress.com/item/RTC-DS1307-Real-Time-Clock-DataLog-Shield-for-Micro-SD-WeMos-D1-Mini-RTC-DS1307-Clock/32839371626.html
* Accelerometer/Gyro GY-521 https://www.aliexpress.com/item/MPU-6050-3-Axis-gyroscope-acce-lerometer-module-3V-5V-compatible-For-Arduino/2035920870.html

# Assembly

## Layout stack

    SD/RTC Shield
    --------------
    Accel/Gyro module held by hardware/gyro_holder.stl (x2, 1 mirrored)
    --------------
    Wemos D1
    --------------
    Battery shield (bridge A0 to batt+ with a 100 ohm resistor)
    
## Connections

Accel/Gyro module: 5V and GND should be connected to the respective rail. SCL to D1, SDA to D2 and AD0 to 5V.
