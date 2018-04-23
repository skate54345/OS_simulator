/*linked list modified from code I had used for a previous course in C */
#include<stdio.h>
#include<stdlib.h>

//Node creation
typedef struct Node
{
    char *string;
    struct Node *next;
} Node;

void skipString(FILE *file, char array[], int times)
{
  int iterator = 0;
  for (iterator; iterator<times; iterator++)
  {
    fscanf(file, "%s", array);
  }
}

void printList(Node *head)
{
    while(head != NULL)
    {
        printf("%s ", head->string);
        head = head->next;
    }
}


int compareStrings (const char *s1, const char *s2)
{
    const unsigned char *p1 = (const unsigned char *)s1;
    const unsigned char *p2 = (const unsigned char *)s2;

    while (*p1 != '\0')
    {
        if (*p2 == '\0')
        {
          return  1;
        }
        if (*p2 > *p1)
        {
          return -1;
        }
        if (*p1 > *p2)
        {
          return  1;
        }

        p1++;
        p2++;
    }

    if (*p2 != '\0') return -1;

    return 0;
}


int rangeCheck (int test_number, int integer1, int integer2)
{
  if (test_number <= integer1 || test_number >= integer2)
  {
    return 0; //false
  }
  else
  {
    return 1; //true
  }
}








// void getNode(Node *head)
// {
//     while(head != NULL)
//     {
//         printf("%s ", head->string);
//         head = head->next;
//     }
// }

// int main()
// {
//     //Open input file
//     FILE *input = fopen("input.txt", "r");
//     char next_string[20] = "";
//
//     //Scan in first string for head node
//     fscanf(input, "%s", next_string);
//
//     //create head, fill it in with the first string, and create current
//     Node *head = malloc(sizeof(Node));
//     head->next = malloc(sizeof(Node));
//     head->string = next_string;
//
//     printf("%s ", head->string);
//     Node *current = head->next;
//
// //Begin Iteration
//     while(fscanf(input, "%s", next_string) != EOF)
//     {
//         current = (Node*)malloc(sizeof(Node));
//         current->string = next_string;
//         current->next = NULL;
//         printf("%s ", current->string);
//         current = current->next;
//    }
//
//     printList(head);
//  }
