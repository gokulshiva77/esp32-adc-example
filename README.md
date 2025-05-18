   - Run: `lsusb` to see if your FTDI device appears.
   - If not, unplug/replug and try a different USB port/cable.
   - If it appears, but OpenOCD still fails, you may need a udev rule:
     - Create a file `/etc/udev/rules.d/99-ftdi.rules` with:
       ```
       SUBSYSTEM=="usb", ATTR{idVendor}=="0403", ATTR{idProduct}=="6010", MODE="0666"
       ```
     - Then run:
       ```bash
       sudo udevadm control --reload-rules
       sudo udevadm trigger
       ```
     - Unplug and replug your debugger.
