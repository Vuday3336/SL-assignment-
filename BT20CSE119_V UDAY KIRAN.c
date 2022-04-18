#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef enum{FAILURE,SUCCESS} status;
typedef struct node
{
	float data;
	int size;
	int mark;
	struct node* prev;
	struct node* next;
}heap;
void initialise(heap** dptr)
{
	heap* ptr;
	ptr=(heap*)malloc(sizeof(heap));
	ptr=*dptr;
	ptr->data=0.0;
	ptr->mark=0;
	ptr->size=0;
	ptr->next=NULL;
	ptr->prev=NULL;
}
void push(heap** dptr,int size)
{
	heap *ptr,*nptr;
	ptr=(heap*)malloc(sizeof(heap));
	ptr=*dptr;
	nptr=(heap*)malloc(sizeof(heap));
	initialise(&nptr);
	nptr->size=size;
	while(ptr->next!=NULL)
	{
		ptr=ptr->next;
	}
	ptr->next=nptr;
	nptr->next=NULL;
	nptr->prev=ptr;
}
status allocate(heap** dptr,int size,float d)
{
	status ret_val=SUCCESS;
    heap *ptr,*previous,*nptr;
    ptr=(heap*)malloc(sizeof(heap));
    previous=(heap*)malloc(sizeof(heap));
    nptr=(heap*)malloc(sizeof(heap));
    initialise(&nptr);
    ptr=*dptr;
    while(ptr!=NULL && size>ptr->size && ptr->mark==0) 
    {
    	ptr=ptr->next;
	}
	if(ptr->mark==1)
	{
		ptr=ptr->next;
		while(ptr!=NULL && (size!=ptr->size||size>ptr->size) && ptr->mark==0)
		{
			ptr=ptr->next;
		}
	}
	else if(ptr==NULL)
	{
		ret_val=FAILURE;
	}
	else if(size==ptr->size && ptr->mark==0)
	{
		ptr->data=d;
		ptr->mark=1;
	}
	else if(size<ptr->size && ptr->mark==0)
	{
		previous=ptr->prev;
		ptr->data=d;
		ptr->mark=1;
		nptr->size=ptr->size-size;
        previous->next=nptr;
        nptr->next=ptr;
        nptr->prev=previous;
        ptr->prev=nptr;
		ptr->size=size;
	}
	else
	{
		ret_val=FAILURE;
	}
	return ret_val;
}
status deallocate(heap** dptr,int size,float d)
{
	status ret_val=SUCCESS;
	heap *ptr;
	ptr=(heap*)malloc(sizeof(heap));
	ptr=*dptr;
	while(ptr!=NULL && size!=ptr->size && ptr->data!=d)
	{
		ptr=ptr->next;
	}
	if(ptr==NULL)
	{
		ret_val=FAILURE;
	}
	else if(ptr->size==size && ptr->data==d)
	{
		ptr->data=0.0;
		ptr->mark=0;
	}
	else
	{
		ret_val=FAILURE;
	}
	return ret_val;
}
void print_list(heap** ptr)
{
	heap* dptr;
	dptr=(heap*)malloc(sizeof(heap));
	dptr=*ptr;
	printf("mark bit is used to indicate whether it is allocated or not\n");
	while(dptr->next!=NULL)
	{
		printf("mark bit- %d data- %f size- %d",dptr->mark,dptr->data,dptr->size);
		printf("\n");
		dptr=dptr->next;
	}
}
int main()
{
	status sc;
	heap* head;
	head=(heap*)malloc(sizeof(heap));
	initialise(&head);
	float data;
	int i,size,arr[6],flag=0;;
	char s1[]="show";
	char s2[]="allocate";
	char s3[]="deallocate";
	char s4[]="exit";
	char str[10];
	for(i=0;i<6;i++)
	{
		arr[i]=(i+1)*10;
	}
	push(&head,arr[0]);
	push(&head,arr[1]);
	push(&head,arr[2]);
	push(&head,arr[3]);
	push(&head,arr[4]);
	push(&head,arr[5]);
	while(!flag)
	{
		printf("enter the operations like show or allocate or deallocate or exit as ur wish\n");
		scanf("%s",str);
		if(strcmp(str,s1)==0)
		{
			print_list(&head);
		}
		else if(strcmp(str,s2)==0)
		{
			printf("enter the data and it's size to allocate\n");
			scanf("%f %d",&data,&size);
			sc=allocate(&head,size,data);
			if(sc==FAILURE)
			{
				printf("allocation failed\n");
			}
			print_list(&head);
		}
		else if(strcmp(str,s3)==0)
		{
			printf("enter the data and it's size u wish to deallocate\n");
			scanf("%f %d",&data,&size);
			sc=deallocate(&head,size,data);
			if(sc==FAILURE)
			{
				printf("deallocation failed\n");
			}
			print_list(&head);
		}
		else
		{
			flag=1;
		}
	}
	return 0;
}
