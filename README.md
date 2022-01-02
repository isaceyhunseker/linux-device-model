 # Basic Structure in Linux Device: **ldm-basic**

- This Program creates and registers basic dummy bus, driver and device according to Linux Device Model.
- This module is an external module.
- Module works on the Kernel 4.19.190

## How to clean and build the module

- The Makefile includes make and clean commands. 

### clean
- Run `make clean`.

### build
- Run  `make`.
- This command runs `make clean` before building the target.
- After completing build you have to see `ldm-basic.ko`

## How to insert the module

- ldm-basic module has no dependency to any external modules. So insmod command will be enough to insert the module:`sudo insmod ldm-basic.ko`
- Then you could check the module installation with `lsmod | grep ldm-basic` command. 
- You could see relative folders and files under `sys` directory like that:
    ```
    user@linux:/sys/bus$ find -name "ldm_basic_bus"
    ./ldm_basic_bus
    ```
    ```
    user@linux:/sys/devices$ find -name "ldm_basic_device"
    ./ldm_basic_bus/devices/ldm_basic_device
    ./ldm_basic_bus/drivers/ldm_basic_driver/ldm_basic_device
    ```
    ```
    user@linux:/sys/module/ldm_basic$ ls
    coresize  initsize   notes   sections    taint
    holders   initstate  refcnt  srcversion  uevent
    ```