# Linux-device-driver-
A simple linux device driver that can be run on both x86 and edge device (specifically most compatible with Raspberry Pi) as Rpi 's OS is easier to configure

note: GPIO drivers are specific to Rpi / Any other SBC with similar numbering

# Setup:
1. sudo apt update
2. sudo apt upgrade -y
3. sudo apt install -y raspberrypi-kernal-headers
   
   // for installing the kernal headers
4. sudo apt install -y build-essential 
5. sudo reboot
   
   //for opening of a fresh kernel
   
// 4. is necessary as we are running c scripts therefore it requires gcc , make (most probably preinstalled)

Then check the conents of the build folder:
![image](https://github.com/user-attachments/assets/a726110f-da0a-42f1-9d67-217bbc47ef80)

after the running of the initial kernel:

![image](https://github.com/user-attachments/assets/6db73b6e-b029-4fba-aab6-5267e8a2e0b3)

# Loading and unloading:

the generated .ko file can be used to load/ unload the kernel module (lkm):

![image](https://github.com/user-attachments/assets/26bedea7-f341-4760-a21f-93ebd3f04ee2)


# Number:
* for chosing of a number , it should be a number that was not listed in ls proc/devices
* Kernel modules can register block or character devices (in the traditional unix sense, "device" is a word with many meanings) in the kernel, using a routine like register_blkdev together with a string that is supposed to identify the device.
*  It's possible to use any string for that purpose, and these strings show up in the /proc/devices file (which is just a textual representation of this kernel table).
* //which are different from the major and minor numbers shown in /dev

* After the generation of device number and loading , it can be checked by
*  cat /proc/devices | grep my_device_nr

![image](https://github.com/user-attachments/assets/ff16d68d-17d4-41ed-840c-0529ad61a8ea)

$ ls /dev/ -al

shows the device in the list after the creation of the node . cat /proc/devices doesnt confirm the device creation (node) only the number associted.

# Reading after the creation of device:

So the loading of the .ko file (lkm) of the corresponding device is necessary for the accessing of that device for either read/write

* initially when the corresponding kernel module for major no. 90 was not loaded but for 104 , it is unable to access the file.

![image](https://github.com/user-attachments/assets/8b4b521c-7002-46e0-a6b2-f4aa5445e05e)

output messages:

![image](https://github.com/user-attachments/assets/e6b2e871-3999-4004-9b82-a77ed37ec21a)


Issues: https://www.notion.so/Issues-16b3175a5f4380b3bb9fc1a1f0b49a01
