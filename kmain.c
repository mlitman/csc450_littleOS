#include "io.h"
#include "string.h"
#include "segments.h"
#include "interrupts.h"
#include "mem_manager.h"
#include "frame_buffer.h"

int main() 
{
    //prepare OS for handing out mem
    unmarkAllMemory();
    segments_install_gdt();
	interrupts_install_idt();
    //char* s;
    
    interrupt_prompt_string = getMem(4);
    strcpy(interrupt_prompt_string, "V> ", 4);

    interrupt_input = getMem(80*25-strlen(interrupt_prompt_string));
    strcpy(interrupt_input, "\0", 1);

    fb_clear();
    fb_write_string(0, interrupt_prompt_string,strlen(interrupt_prompt_string));
    return 0;
}