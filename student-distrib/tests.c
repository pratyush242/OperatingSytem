#include "tests.h"
#include "x86_desc.h"
#include "lib.h"

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



// void division_by_zero_test(){
// 	TEST_HEADER;

// 	int result;
// 	int a = 22;
// 	int b = 0;
// 	result = b/a;
// 	return result;
// }

// void null_test(){
// 	TEST_HEADER;
//     int result;
// 	int* a = NULL;
	
// 	result = *(a);
// 	return FAIL;

// }

// void rtc_test(){
// 	TEST_HEADER;
// 	printf("rtc");
//     // __asm__("int 0x21");
// 	return FAIL;
// }

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
	TEST_OUTPUT("idt_test", idt_test());
	// TEST_OUTPUT("division_by_zero_test", division_by_zero_test());
	// TEST_OUTPUT("null_test", null_test());
	// TEST_OUTPUT("rtc_test", rtc_test());
	// TEST_OUTPUT("system__call_test", system__call_test());
	// launch your tests here
}
