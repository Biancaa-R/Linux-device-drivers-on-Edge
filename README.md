# Linux-device-driver-
A simple linux device driver that can be run on both x86 and edge device (specifically most compatible with Raspberry Pi) as Rpi 's OS is easier to configure

# Setup:
1. sudo apt update
2. sudo apt upgrade -y
3. sudo apt install -y raspberrypi-kernal-headers
   
   // for installing the kernal headers
4. sudo apt install -y build-essential
5. sudo reboot
   
   //for opening of a fresh kernel
   
// 4. is necessary as we are running c scripts therefore it requires gcc , make

Then check the conents of the build folder:
![image](https://github.com/user-attachments/assets/a726110f-da0a-42f1-9d67-217bbc47ef80)

