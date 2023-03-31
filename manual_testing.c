#include <malloc.h>
#include <stdio.h>

#include "./src/lists/double/dllist.h"
#include "./src/text.h"
#include "./src/arguments/arguments.h"
#include "./src/arguments/flags.h"

void myFree(void *data) {
	//printf("> Reee !\n");
	free(data);
}

int main(int argc, char **argv) {
	Verb *rootVerb = args_createVerb("root", "");
	Verb *subVerb = args_createVerb("123", "");
	Option *helpOption = args_createOption('h', "help", "", FLAG_OPTION_NONE);
	
	if(!args_registerVerb(subVerb, rootVerb)) {
		printf("NOK 1\n");
		args_freeOption(helpOption);
		args_freeVerb(subVerb);
		args_freeVerb(rootVerb);
		return 1;
	}
	
	if(!args_registerOption(helpOption, rootVerb)) {
		printf("NOK 2\n");
		args_freeOption(helpOption);
		args_freeVerb(rootVerb);
		return 2;
	}
	
	if(!args_registerOption(helpOption, subVerb)) {
		printf("NOK 3\n");
		args_freeOption(helpOption);
		args_freeVerb(rootVerb);
		return 3;
	}
	
	char *arguments[] = {"123", "--help"};
	
	Verb *lastUsedVerb = NULL;
	if(args_parseArguments(rootVerb, arguments, 0, 1, &lastUsedVerb) != ERROR_ARGUMENTS_NONE) {
		printf("Failed to parse !\n");
	}
	
	if(lastUsedVerb != NULL) {
		printf("The last used verb is '%s' !\n", lastUsedVerb->name);
	} else {
		printf("The last used verb is NULL !\n");
	}
	
	printf("Done testing !\n");
	args_freeVerb(rootVerb);
	
	/*char* str1 = "123abc";
	
	char* str2 = copyString(str1);
	
	printf("%s\n", str1);
	printf("%p\n", (void*) str1);
	
	printf("%s\n", str2);
	printf("%p\n", (void*) str2);
	
	free(str2);*/
	
	/*while(true) {
		//printf("Creating...\n");
		DoubleLinkedList* doubleLinkedList = DoubleLinkedLists.create(&myFree);
		
		//printf("Populating...\n");
		for(int i = 0; i < 50; i++) {
			void* dataTest = malloc(16);
			DoubleLinkedLists.append(doubleLinkedList, dataTest);
		}
		
		//printf("Cleaning...\n");
		DoubleLinkedLists.free(doubleLinkedList);
		
		//printf(".");
	}*/
	return 0;
}
