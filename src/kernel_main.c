void write_zero();

extern long __bss_start;
extern long __bss_end;
extern struct ppage* free_list;

#include "list.h"
#include "linkedlist.h"
#include "led.h"
#include "serial.h"
#include "rprintf.h"
#include "page.h"
#include "gpio.h"
#include "fat.h"
#include "sd.h"


void kernel_main(){

	struct file fat_test;

	sd_init();
	fatInit();
	fatOpen(&fat_test, "TESTSTART");
	fatRead(&fat_test, "TESTFILE", 32);
}

void write_zero() {

	int x = 0;
	while ((&__bss_start)+x != &__bss_end) {
		(&__bss_start)[x] = 0;
		x++;
	}

}
