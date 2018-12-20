#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#define SIZE 20

struct DataItem {
   int data;
   int key;
};

struct DataItem* hashArray[UINT16_MAX];
struct DataItem* dummyItem;
struct DataItem* item;

int hashCode(int key) {
   return key % SIZE;
}

struct DataItem *search(int key)
{
   int hashIndex = hashCode(key);

   while(hashArray[hashIndex] != NULL)
   {
      if(hashArray[hashIndex]->key == key)
         return hashArray[hashIndex];
      ++hashIndex;
      hashIndex %= SIZE;
   }

   return NULL;
}

void insert(int key,int data)
{

   struct DataItem *item = (struct DataItem*) malloc(sizeof(struct DataItem));
   item->data = data;
   item->key = key;

   int hashIndex = hashCode(key);

   while(hashArray[hashIndex] != NULL && hashArray[hashIndex]->key != -1)
   {
       if (hashArray[hashIndex]->key == key)
       {
           hashArray[hashIndex]->data = data;
           return;
       }
      ++hashIndex;
      hashIndex %= SIZE;
   }
   hashArray[hashIndex] = item;
}

void delete(struct DataItem* item)
{
   int key = item->key;

   int hashIndex = hashCode(key);

   while(hashArray[hashIndex] != NULL) {

      if(hashArray[hashIndex]->key == key)
      {
         hashArray[hashIndex]->data = -1;
         hashArray[hashIndex]->key = -1;
      }

      ++hashIndex;
      hashIndex %= SIZE;
   }
}

void display() {
   int i = 0;

   for(i = 0; i<SIZE; i++) {

      if(hashArray[i] != NULL && hashArray[i]->key != -1 )
         printf("%d -> %d \n",hashArray[i]->key,hashArray[i]->data);
    }
   printf("\n");
}

int main()
{
   int choice = 0;

   while (choice != 3)
   {
       printf(" - 1 : Insert\n - 2 : Delete\n - 3 : Quit\n");
       scanf("%d", &choice);
       if (choice == 1)
       {
           unsigned int key = 0;
           int value = 0;
           printf("Enter key : ");
           scanf("%u", &key);
           printf("Enter value : ");
           scanf("%d", &value);
           insert(key, value);
       }
       if (choice == 2)
       {
            int key = 0;
            printf("Enter key : ");
            scanf("%u", &key);
            delete(search(key));
       }
       if (choice == 1 || choice == 2)
       {
           display();
       }
   }

   free(hashArray);
   free(dummyItem);

   return 0;

}
