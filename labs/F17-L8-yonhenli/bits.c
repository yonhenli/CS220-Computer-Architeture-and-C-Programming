#include "bits.h"
#include <stdio.h>

void print_in_binary(unsigned int x) {
	int i = 0;
	for (i = 31; i > -1; i--) {
		if (IS_SET_ANY(x, BIT(i)) != 0) {
			printf("1");			
		}
		else{
			printf("0");		
		}
	}
	printf("\n");
}

unsigned int get_page_offset (unsigned int address) {
	/*page offset: 0 - 11 bits*/
	return BF_GET(address, 0, 12);
}

unsigned int get_tlb_id (unsigned int address) {
	/*tlb id: 12 - 14 bits*/
	return BF_GET(address, 12, 3);
}

unsigned int get_tlb_tag (unsigned int address) {
	/*tld tag: 24 - 31 bits*/
	return BF_GET(address, 24, 8);
}

unsigned int set_page_offset (unsigned int address, unsigned int new_page_offset) {
	return BF_SET(address, new_page_offset, 0, 12);
}

unsigned int set_tlb_id (unsigned int address, unsigned int new_tld_id) {
	return BF_SET(address, new_tld_id, 12, 3);
}

unsigned int set_tlb_tag (unsigned int address, unsigned int new_tlb_tag) {
	return BF_SET(address, new_tlb_tag, 24, 8);
}


int main() {
	int i = 6;
	print_in_binary(i);

	unsigned int address = 0xf712c0d0, page_offset = 0x1a3, tlb_id = 0x0, tlb_tag = 0x8400, new_address;
	
	printf("page offset: ");
	print_in_binary(get_page_offset(address));

	printf("tlb id: ");
	print_in_binary(get_tlb_id(address));
	
	printf("tlb tag: ");
	print_in_binary(get_tlb_tag(address));

	printf("old address: ");
	print_in_binary(address);
	
	new_address = set_page_offset(address, page_offset);
	new_address = set_tlb_id(new_address, tlb_id);
	new_address = set_tlb_tag(new_address, tlb_tag);
	
	printf("page offset: ");
	print_in_binary(get_page_offset(new_address));
	
	printf("tlb id: ");
	print_in_binary(get_tlb_id(new_address));
	
	printf("tlb tag: ");
	print_in_binary(get_tlb_tag(new_address));
	
	printf("new address: ");
	print_in_binary(new_address);
	
	return 0;
}
