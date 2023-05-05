# Linux-Bringup-N-Drivers

## 01-Character-device-driver
  - Hello-world kernel module
  - Device number (major/minor)
  - Device file
  - File operations
## 02-Led-driver (legacy)
  - Guide to read datasheet, schematic
  - Gpio banks, gpio number
  - Pins, pins functions
  - Control led via ioremap
## 03-Gpio-subsystem
  - Control gpios via sysfs
  - Write your own gpio driver (control all banks/gpios via device file)
## 04-Gpio-sysfs-driver
  - Create sysfs
  - Write your own gpio driver (control all banks/gpios via sysfs) 
## 05-Device-tree (new)
  - Analysis device-tree
  - Custom device-tree node and driver
## 06-Pin-control-subsystem
  - Concepts of pin-control ID, pin-control name and so on
  - Bring-up PWM
  - Controlled led fades out via pwm
  - Play a song by using pwm
## 07-I2C-driver
  - Basic protocol
  - Operations mode
  - I2C Architecture in Linux
  - Control LCD 16x2
## 08-SPI-driver
  - Basic protocol
  - Operations mode
  - SPI Architecture in Linux
  - SPI protocol driver
  - SPI Transaction
  - SPI Master
  - Control LCD nokia 5110 or proximity sensor
## 09-USB-driver
  - Basic concepts
  - USB descriptor
    - Device descriptor
    - Configuration descriptor
    - Interface descriptor
    - Endpoint descriptor
  - Data Flow Types
    - Control Transfers
    - Interrupt Transfers
    - Bulk Transfers
    - Isochronous Transfers
  - USB device driver
## 10-Bringup-display-panel
  - Bringup LCD panel ili9341
  - Display video
## 11-Ethernet-driver
