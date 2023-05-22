You may need to execute `chmod +x ./dfu-util` to make the `./dfu-util -l | grep 28e9:0189` instruction work.

If you encounter `LIBUSB_ERROR_ACCESS`, please do: 
```
sudo chmod -R 777 /dev/bus/usb/
```

The board is $160\times 80$ pixels.

---

```
.section .text
.globl your_function_name
.type your_function_name, @function
your_function_name:
	# The above lines declares a function that can be accessed from C code.
	# When you're implementing your own function, you make a new file in
	# this folder, copy the above 4 lines, and replace all
	# "your_function_name" to your function's name.

	# Then you can add code after the label on line 4.

	# The rest of things work the same as in Venus, except that the directive
	# ".asciiz" is removed. Use ".string" instead.

	# Also, please make sure that each assembly function has a filename with 
	# extension name ".S", not ".s". Otherwise it will not be recognized
	# by the riscv-nuclei-elf-as and will throw an error.

	# You're free to remove this function after you've read the above.
```

When you call a RISC-V function inside a `.c` file, remember to add a function declaration before.

---

# Project 4: Longan Nano minigame

This repo contains the framework code for your Project 4. 

In this project, you will be implementing a Pong game using the Longan Nano development board we've given to you. We've provided you a framework here.

You can also choose to implement your own minigame.

We hope this project will help you experience programming RISC-V on a real machine rather than in a simulator.

For full details of this project, please see course website

## PLEASE READ

The projects are part of your design project worth 2 credit points. As such they run in parallel to the actual course. So be aware that the due date for project and homework might be very close to each other! Start early and do not procrastinate.

## Download Framework

Download the framework from gitlab and Check if you already have the following files after pulling.

```
.
├── LICENSE
├── Makefile
├── README.md
├── dfu-util
├── include
│   ├── README
│   ├── fatfs
│   │   ├── diskio.h
│   │   ├── ff.h
│   │   ├── ffconf.h
│   │   └── tf_card.h
│   ├── gd32v_pjt_include.h
│   ├── gd32vf103_libopt.h
│   ├── lcd
│   │   ├── bmp.h
│   │   ├── lcd.h
│   │   └── oledfont.h
│   ├── systick.h
│   └── utils.h
├── platformio.ini
└── src
    ├── assembly
    │   └── example.S
    ├── fatfs
    │   ├── 00history.txt
    │   ├── 00readme.txt
    │   ├── ff.c
    │   ├── ffsystem.c
    │   ├── ffunicode.c
    │   └── tf_card.c
    ├── lcd
    │   └── lcd.c
    ├── main.c
    ├── systick.c
    └── utils.c
```
