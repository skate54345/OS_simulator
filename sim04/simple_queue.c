/*queue implementation taken and slightly modified from:
https://gist.github.com/Groxx/310147*/
#include <stdio.h>
#include <stdlib.h>

typedef void *queue_data_type;

struct queue_item
{
	queue_data_type contents;
	struct queue_item* next;
};

struct queue_root
{
	struct queue_item* head;
	struct queue_item* tail;
};

void init_queue(struct queue_root* queue)
{
	queue->head = queue->tail = NULL;
}

void push_queue(struct queue_root* queue, int size, queue_data_type contents)
{
	struct queue_item *item = malloc(sizeof(item));
	item->contents = contents;
	item->next = NULL;
	if (queue->head == NULL)
	{
		queue->head = queue->tail = item;
	}
	else
	{
		queue->tail = queue->tail->next = item;
	}
}

queue_data_type pop_queue(struct queue_root* queue)
{
	queue_data_type popped;
	if (queue->head == NULL)
	{
		return NULL; // causes a compile warning.  Just check for ==NULL when popping.
	}
	else
	{
		popped = queue->head->contents;
		struct queue_item* next = queue->head->next;
		free(queue->head);
		queue->head = next;
		if (queue->head == NULL)
		{
			queue->tail = NULL;
		}
	}
	return popped;
}

// void process_queue(struct queue_root* queue, void (*func)(queue_data_type))
// {
// 	if (queue == NULL)
// 	{
// 		return;
// 	}
// 	struct queue_item* current = queue->head;
// 	while (current != NULL)
// 	{
// 		next = current->next;
// 		func(current->contents);
// 		current = next;
// 	}
// }
