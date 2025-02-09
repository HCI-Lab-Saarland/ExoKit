Software Setup:
1.	Download the code from this folder (“Arduino API“)
2.	Install CLION (or similar) and follow existing online guides to set up the platformIO extension. Test the successful installation with a simple Arduino program (you can find examples online).
3.	Install the required plugins in CLION:
  o	Serial Port Monitor Plugin: https://plugins.jetbrains.com/plugin/8031-serial-port-monitor
  o	PlatformIO Plugin for CLion: https://plugins.jetbrains.com/plugin/13922-platformio-for-clion  
4.	Open the project as a platformIO project with CLION.
  o	To work with the Arduino Mega, PlatformIO must be set up for megaatmega2560. We provide the suitable platformio.ini file as part of the downloaded code. The platformio.ini contains further library dependencies, such as Dynamixel2Arduino, DynamixelShield, HX711, LinkedList, TaskManagerIO.
5.	Build the project.
  o	In case of an error message about undefined references to loop and setup functions, make sure that one (and only one!) of the example programs in the src folder is commented in.
  o	In case of error messages about libraries not being available for the system, the library dependencies listed in platform.ini (“lib_deps”) might need to be adjusted to fit your system.

You can find an example video for setting up the platformIO project in CLION in the repo’s video folder (“Software Installation PlatformIO”). 

For details about the software and a quick start guide please refer to Chapter 2 of the user manual.
Fpr more details about how to program interactive behavaior with the Arduino API, please refer to Chapter 7 of the user manual.
