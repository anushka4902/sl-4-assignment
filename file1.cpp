#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

typedef struct node
{
   
    int count;
    struct node *next_1;
    struct node *next_2;
    struct node *next_3;
     int data;
    bool mark;
    
    
}Node;

 Node *pointers[8];

void display_node(int i)
{
	printf("value=%d\t reference count=%d\nfree size=%d\n",pointers[i]->data,pointers[i]->count,sizeof(Node));
}//display reference count and freed size

void edge_set(int start1,int d1,int d2,int d3)
{
	if(d1!=-1)
	{
		pointers[start1]->next_1=pointers[d1];
		pointers[d1]->count+=1;
	}
	if(d2!=-1)
	{
		pointers[start1]->next_2=pointers[d2];
		pointers[d2]->count+=1;
	}
	if(d3!=-1)
	{
		pointers[start1]->next_3=pointers[d3];
		pointers[d3]->count+=1;
	}
	
}

void all_nodes_display(Node* root)
{
	if(root!=NULL)
	{
		printf("value=%d\ncount=%d\n",root->data,root->count);
	}
	if(root==NULL)
	{
		return;
	}
	all_nodes_display(root->next_1);
	all_nodes_display(root->next_2);
	all_nodes_display(root->next_3);
}

void adjacency_list()
{
	int i=0;
	for(i=0;i<8;i++)
	{
		if(pointers[i]!=NULL)
		{
			printf("Value=%d: ",pointers[i]->data);
			if(pointers[i]->next_1!=NULL)
			{
				printf("%d ->",pointers[i]->next_1->data);
			}
			if(pointers[i]->next_2!=NULL)
			{
				printf("%d ->",pointers[i]->next_2->data);
			}
			if(pointers[i]->next_3!=NULL)
			{
				printf("%d ->",pointers[i]->next_3->data);
			}
			printf("NULL\n");
		}
	}
}

int root_is_present(Node* root1,Node* temp)
{
	if(root1==NULL)
	{
		return 0;
	}
	if(root1->data==temp->data)
	{
		return 1;
	}
	
	if(root_is_present(root1->next_1,temp))
	{
		return 1;
	}
	
	if(root_is_present(root1->next_2,temp))
	{
		return 1;
	}
	if(root_is_present(root1->next_3,temp))
	{
		return 1;
	}
 return 0;
}


void garbage_collection_counting(Node* root)
{
	int i=0;
	while(i<8)
	{
		if(root_is_present(root,pointers[i])==0 )
		{		
			if(pointers[i]->next_1!=NULL)
			{
				pointers[i]->next_1->count-=1;
			}
			if(pointers[i]->next_2!=NULL)
			{
				pointers[i]->next_2->count-=1;
			}
			if(pointers[i]->next_3!=NULL)
			{
				pointers[i]->next_3->count-=1;
			}
			printf("Garbage -------:");
			display_node(i);
			free(pointers[i]);
			pointers[i]=NULL;
		}
		 i++;		
	}
	 
}

void adjacency_Matrix()
{
	int xyz[8][8];
	int i,j,k;
	
	for(i=0;i<8;i++)		
	{
		for(j=0;j<8;j++)
		{
			xyz[i][j]=0;
		}	
	}
	
	for(i=0;i<8;i++)
	{
		for(j=0;j<8;j++)
		{
			
		if(pointers[j]!=NULL&&pointers[i]!=NULL)
		{
			
			if(pointers[i]->next_1!=NULL)
			{
				if(pointers[i]->next_1->data==pointers[j]->data&&i!=j)
				{
					xyz[i][j]=1;
				}
			}
			if(pointers[i]->next_2!=NULL)
			{
				if(pointers[i]->next_2->data==pointers[j]->data&&i!=j)
				{
					xyz[i][j]=1;
				}
			}
			if(pointers[i]->next_3!=NULL)
			{
				if(pointers[i]->next_3->data==pointers[j]->data&&i!=j)
				{
					xyz[i][j]=1;
				}
			}
		}
		
		}
	}
	
	for(i=0;i<8;i++)
	{
		for(j=0;j<8;j++)
		{
			printf("%d ",xyz[i][j]);		
		}
		printf("\n");
	}
}

void node_marking(Node*root,int i,int j)
{
    Node *currt, *pre;

    currt = root;
        
    while (currt != NULL) 
    {
  
        if (currt->next_1== NULL) 
        {
            currt->mark=true;
            currt = currt->next_2;
        }   
        else 
        {
            pre = currt->next_1;
            while ((pre->next_2 != NULL) && (pre->next_2 != currt))
            {
            	pre = pre->next_2;
			}
                
            if (pre->next_2 == NULL) 
            {
                pre->next_2 = currt;
                currt = currt->next_1;
            }
            else 
            {
                pre->next_2 = NULL;
                currt->mark=true;
                currt = currt->next_2;
            } 
        }
    }   
    
    currt = root;
        
    while (currt != NULL) 
    {
  
        if (currt->next_1== NULL) 
        {
            currt->mark=true;
            currt = currt->next_3;
        }   
        else 
        {
            pre = currt->next_1;
            while ((pre->next_3 != NULL) && (pre->next_3 != currt))
            {
            	pre = pre->next_3;
			}
                
            if (pre->next_3 == NULL) 
            {
                pre->next_3 = currt;
                currt = currt->next_1;
            }
            else 
            {
                pre->next_3 = NULL;
                currt->mark=true;
                currt = currt->next_3;
            } 
        }
    }  
    
}

void marking(Node* root)
{
	
	if(root!=NULL)
	{
		root->mark=true;
	}
	if(root==NULL)
	{
		return;
	}
	marking(root->next_1);
	marking(root->next_2);
	marking(root->next_3);
}

void sweep()
{
	int i;
	for(i=0;i<8;i++)
	{
		if(pointers[i]->mark==false)
		{
			if(pointers[i]->next_1!=NULL)
			{
				pointers[i]->next_1->count-=1;
			}
			if(pointers[i]->next_2!=NULL)
			{
				pointers[i]->next_2->count-=1;
			}
			if(pointers[i]->next_3!=NULL)
			{
				pointers[i]->next_3->count-=1;
			}
			printf("Garbage:");
			display_node(i);
			free(pointers[i]);
			pointers[i]=NULL;
		}
	}
}

int main()
{
	
		
	int arr[]={1,2,3,5,7,8,9,10};
	int j;
	for( j=0;j<8;j++)
	{
		Node* nodenew =(Node*)malloc(sizeof(Node));
		nodenew->data=arr[j];
		nodenew->next_1=NULL;
		nodenew->next_2=NULL;
		nodenew->next_3=NULL;
		nodenew->count=0;
		nodenew->mark=false;		
		pointers[j]=nodenew;
	}
	
	Node*root1=pointers[3];
	pointers[3]->count+=1;
	Node*root2=pointers[0];
	pointers[0]->count+=1;
	
	edge_set(0,1,6,7);
	edge_set(2,5,7,-1);
	edge_set(3,0,-1,-1);
	edge_set(4,0,5,-1);
	edge_set(5,6,-1,-1);
	

	
	printf("\nAll nodes through Root 1:\n");
	all_nodes_display(root1);	
	printf("\nAll nodes through Root 2:\n");
	all_nodes_display(root2);
	printf("\n\nAdjacency list \n");
	adjacency_list();
	printf("\n\nAdjacency matrix\n");
	adjacency_Matrix();
	

	
	printf("\nCalling the mark and sweep garbage collector\n");
	//node_marking(root1,0,1);
	marking(root1);
	sweep();
    printf("\n\nAdjacency list after removal of garbage:\n");
	adjacency_list();
	printf("\n\nAdjacency matrix after removal of garbage:\n");
	adjacency_Matrix();
	
}