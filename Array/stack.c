/*
 * Stack Data Structure using Array in C
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define STACK_SIZE	10

/* stack data structure */
struct stack {
	int arr[STACK_SIZE];
	int top;
	int capacity;
};

/* Push Element into stack */
static void push(struct stack *stack, int data)
{
	/* Stack Overflow condition check */
	if (stack->top == stack->capacity -1) {
		printf("Stack Overflow\n");
		return;
	}
	stack->top++;
	stack->arr[stack->top] = data;
}

/* Pop Element from stack */
static int pop(struct stack *stack)
{
	int result;

	/* Stack underflow condition check */
	if (stack->top == -1) {
		printf("Stack Underflow\n");
		return -1;
	}
	
	result = stack->arr[stack->top];
	stack->top--;
	return result;
}

/* Check Top of the stack */
static int peek(struct stack *stack)
{
	/* Stack underflow condition check */
	if (stack->top == -1) {
		printf("Stack Underflow\n");
		return -1;
	}
	return stack->arr[stack->top];
}

/* Check is stack empty */
static bool is_empty(struct stack *stack)
{
	return (stack->top == -1);
}

int main() {
	struct stack *stack = NULL; 
	int choice, data;	

	stack = calloc(1, sizeof(struct stack));
	if (stack == NULL) {
		printf("Error: Failed to allocate memory for stack\n");
		exit(1);
	}

	stack->top = -1;
	stack->capacity = STACK_SIZE;

	while(true) {
		printf("1 - Push\n");
		printf("2 - Pop\n");
		printf("3 - peek\n");
		printf("4 - Is empty\n");
		printf("99 - exit\n");
		printf("Please enter the choice: ");
		scanf("%d", &choice);

		switch(choice) {
			case 1:
				printf("Please enter the number: ");
				scanf("%d", &data);
				push(stack, data);
					break;	
			case 2:
				printf("Data is: %d\n", pop(stack));
				break;
			case 3:
				printf("Data is: %d\n", peek(stack));
				break;
			case 4:
				printf("Stack %s empty!\n", 
						is_empty(stack) ? "is" : "is not");
				break;
			case 99:
				free(stack);
				exit(0);
			default:
				printf("ERROR: Invalid choice given!\n");
		}
	}

	return 0;
}
