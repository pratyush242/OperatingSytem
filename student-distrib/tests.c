#include "tests.h"
#include "x86_desc.h"
#include "lib.h"
#include "idt.h"

#define PASS 1
#define FAIL 0

/* format these macros as you see fit */
#define TEST_HEADER 	\
	printf("[TEST %s] Running %s at %s:%d\n", __FUNCTION__, __FUNCTION__, __FILE__, __LINE__)
#define TEST_OUTPUT(name, result)	\
	printf("[TEST %s] Result = %s\n", name, (result) ? "PASS" : "FAIL");

static inline void assertion_failure(){
	/* Use exception #15 for assertions, otherwise
	   reserved by Intel */
	asm volatile("int $15");
}


/* Checkpoint 1 tests */

/* IDT Test - Example
 * 
 * Asserts that first 10 IDT entries are not NULL
 * Inputs: None
 * Outputs: PASS/FAIL
 * Side Effects: None
 * Coverage: Load IDT, IDT definition
 * Files: x86_desc.h/S
 */
int idt_test(){
	TEST_HEADER;

	int i;
	int result = PASS;
	for (i = 0; i < 10; ++i){
		if ((idt[i].offset_15_00 == NULL) && 
			(idt[i].offset_31_16 == NULL)){
			assertion_failure();
			result = FAIL;
		}
	}

	return result;
}

// add more tests here
/* exceptions Test
 * 
 * checks for division by 0 test case
 * Inputs: None
 * Outputs: exception/FAIL
 * Side Effects: None

 */

int exceptions_test(){
	TEST_HEADER;
	/* Use exception #15 for assertions, otherwise
	   reserved by Intel */
	int i = 1 / 0;
	// asm volatile("int $00");
	return FAIL;
}


/* Video_Memory_Test
 * 
 * checks for video memory paging case
 * Inputs: None
 * Outputs: pass
 * Side Effects: None

 */


int video_memory_test(){

	TEST_HEADER;

	char* temp_pointer = (char*)0xB8000;
	char final;
	final = *temp_pointer;


	return PASS;

}

/* Null_Test
 * 
 * checks for null value case
 * Inputs: None
 * Outputs: PAGE_FAULT/fail
 * Side Effects: None

 */
int null_test(){
	TEST_HEADER;
    int result;
	int* a = NULL;
	
	result = *(a);
	return FAIL;

}

int rtc_test(){
	TEST_HEADER;
	test_interrupts();
	return FAIL;
}



int kernel_lower__fail_test(){
    TEST_HEADER;
    char* temp_pointer = (char*)0x3FFFFF;
    char final = *temp_pointer;
    return FAIL;
}


int kernel_upper__fail_test(){
    TEST_HEADER;
    char* temp_pointer = (char*)0x800000;
    char final = *temp_pointer;
    return FAIL;
}


int video_lower__fail_test(){

    TEST_HEADER;
    char* temp_pointer = (char*)0xB7FFF;
    char final = *temp_pointer;
    return FAIL;

}


int video_upper__fail_test(){

    TEST_HEADER;
    char* temp_pointer = (char*)0xB9000;
    char final = *temp_pointer;
    return FAIL;

}

// void system__call_test(){
// 	TEST_HEADER;
//     // __asm__("int 0x80");
// 	printf("syscall");
// 	return FAIL;
// }


/* Checkpoint 2 tests */
/* Checkpoint 3 tests */
/* Checkpoint 4 tests */
/* Checkpoint 5 tests */


/* Test suite entry point */

void launch_tests(){
	//printf("WEHITTHIS");
	//division_by_zero_test();
	//idt_init();
	TEST_OUTPUT("idt_test", idt_test());
	//TEST_OUTPUT("video_memory_test", video_memory_test());
	//TEST_OUTPUT("kernel_lower__fail_test", kernel_lower__fail_test());
	TEST_OUTPUT("division_by_zero_test", exceptions_test());
	//TEST_OUTPUT("null_test", null_test());
	//TEST_OUTPUT("_test", rtc_test());
	// launch your tests here
}
