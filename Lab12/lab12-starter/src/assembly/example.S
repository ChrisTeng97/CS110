.section .text
.globl example
.type example, @function
example:
	li a0, 40
	li a1, 40
	li a2, 40
	li a3, 0xF800
	jal LCD_DrawCircle
	li a0, 80
	li a1, 0
	li a2, 159
	li a3, 79
	li a4, 0xFFFF
	jal LCD_DrawRectangle
	li a0, 0
	li a1, 30
	la a2, str
	li a3, 0xFFE0
	jal LCD_ShowString
	ret
.data
str: .string "Japan Red-White"
