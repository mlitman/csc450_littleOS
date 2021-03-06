#include "interrupts.h"
#include "mem_manager.h"
#include "string.h"

struct IDTDescriptor idt_descriptors[INTERRUPTS_DESCRIPTOR_COUNT];
struct IDT idt;

void interrupts_init_descriptor(int index, unsigned int address)
{
	idt_descriptors[index].offset_high = (address >> 16) & 0xFFFF; // offset bits 0..15
	idt_descriptors[index].offset_low = (address & 0xFFFF); // offset bits 16..31

	idt_descriptors[index].segment_selector = 0x08; // The second (code) segment selector in GDT: one segment is 64b.
	idt_descriptors[index].reserved = 0x00; // Reserved.

	/*
	   Bit:     | 31              16 | 15 | 14 13 | 12 | 11     10 9 8   | 7 6 5 | 4 3 2 1 0 |
	   Content: | offset high        | P  | DPL   | S  | D and  GateType | 0 0 0 | reserved
		P	If the handler is present in memory or not (1 = present, 0 = not present). Set to 0 for unused interrupts or for Paging.
		DPL	Descriptor Privilige Level, the privilege level the handler can be called from (0, 1, 2, 3).
		S	Storage Segment. Set to 0 for interrupt gates.
		D	Size of gate, (1 = 32 bits, 0 = 16 bits).
	*/
	idt_descriptors[index].type_and_attr =	(0x01 << 7) |			// P
						(0x00 << 6) | (0x00 << 5) |	// DPL
						0xe;				// 0b1110=0xE 32-bit interrupt gate
}

void interrupts_install_idt()
{
	interrupts_init_descriptor(INTERRUPTS_KEYBOARD, (unsigned int) interrupt_handler_33);

	idt.address = (int) &idt_descriptors;
	idt.size = sizeof(struct IDTDescriptor) * INTERRUPTS_DESCRIPTOR_COUNT;
	load_idt((int) &idt);

	/*pic_remap(PIC_PIC1_OFFSET, PIC_PIC2_OFFSET);*/
	pic_remap(PIC_1_OFFSET, PIC_2_OFFSET);
}

void interrupt_handler(__attribute__((unused)) struct cpu_state cpu, unsigned int interrupt, __attribute__((unused)) struct stack_state stack)
{
	unsigned char scan_code;
	char ascii;
    scan_code = keyboard_read_scan_code();
	if(scan_code == 0x0e) //a backspace
	{
		strshorten(interrupt_input, 1);
		fb_clear();
	fb_write_string(0, interrupt_prompt_string, strlen(interrupt_prompt_string));
	fb_write_string(strlen(interrupt_prompt_string)*2, interrupt_input, strlen(interrupt_input));
	}
	else if(scan_code == 0x1c) //enter key
	{
		//char** theTokens;
		strtok(interrupt_input);
		//char* is a collecton of char (string)
		//int* is a collection int (int array)
		//char** is a collection of strings
		//int** is a collection of int arrays

		//strtok(theTokens, interrupt_input);
	}
	else
	{
		/* code */
		ascii = keyboard_scan_code_to_ascii(scan_code);
		char* temp = getMem(2);
		
		strcpy(temp, &ascii,1);
		strcat(interrupt_input, temp);
		freeMem(temp, strlen(temp));
		fb_clear();
	fb_write_string(0, interrupt_prompt_string, strlen(interrupt_prompt_string));
	fb_write_string(strlen(interrupt_prompt_string)*2, interrupt_input, strlen(interrupt_input));
	}
    pic_acknowledge(interrupt);
}