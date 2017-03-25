#include "binary_heap.h"

typedef struct _binaryheap_head 
{
	//数组头，动态申请
	BINARYHEAP_ELEMENT* list;
	//实际存放元素数
	int corrent_size;
	//最大容量
	int max_size;

}Binaryheap_head;

//初始化一个二叉堆头，其最大长度为max_element_num
Binaryheap_head* binaryheap_init(int max_element_num)
{
	Binaryheap_head* head = (Binaryheap_head*)malloc(sizeof(Binaryheap_head));
	if(head != NULL)
	{
		head->corrent_size=0;
		head->list = (BINARYHEAP_ELEMENT*)malloc(max_element_num * sizeof(BINARYHEAP_ELEMENT));
		head->max_size = max_element_num;
		if(head->list != NULL)
		{
			return head;
		}
		else
		{
			free(head);
			return NULL;
		}
	}
	else
		return NULL;
}

//根据比较函数向二叉堆插入一个值。compare函数返回值参考qsort的compare（你想让a排在b前面就返回1，否则就返回0）
int binaryheap_insrt(Binaryheap_head* head, BINARYHEAP_ELEMENT element, int (*compare)(const void* element_a,const void* element_b))
{
	//从下往上调整
	if(head->corrent_size >= head->max_size)
	{
		return 1;
	}
	else
	{
		// 当前节点的位置
		int corrent = (head->corrent_size)++;
		// 父(parent)结点的位置
		int parent = PARENT(corrent);
		//给element找个合适的位置
		while(corrent > 0)
		{
			//如果父节点比它大，不用调整
			if(compare(&(head->list)[parent],&element) >= 0)
				break;
			//否则，交换它与父节点位置（等价于）
			else
			{
				(head->list)[corrent] = (head->list)[parent];
				corrent = parent;
				parent = PARENT(parent);
			}
		}
		//把element放进去
		(head->list)[corrent] = element;
		return 0;
	}
}

//得到堆顶元素的值（不改变堆）
BINARYHEAP_ELEMENT binaryheap_get_top(Binaryheap_head* head)
{
	if(head->corrent_size != 0)
		return (head->list)[0];
	else
		return NOTHING;
}

//删除堆顶元素，并按照compare函数重整堆
int binaryheap_delete_top(Binaryheap_head* head, int (*compare)(const void* element_a,const void* element_b))
{
	//从上往下调整
	if(head->corrent_size <= 0)
	{
		return 1;
	}
	else
	{
		//等价于：将堆尾元素拿到堆头，并删除堆尾元素
		//当前位置
		int corrent = 0;
		//当前值
		BINARYHEAP_ELEMENT temp = (head->list)[--(head->corrent_size)];
		// 先让bigger child等于左孩子的位置
		int bigger_child = LEFT_CHILD(corrent);

		//给堆尾元素找个合适的位置
		while(bigger_child <= head->corrent_size)
		{
			//将当前元素和它的两个子节点进行比较
			//先选出子节点中较大的一个
			if(bigger_child <  head->corrent_size && compare(  &(head->list)[bigger_child+1] , &(head->list)[bigger_child])  >=0 )
			{
				bigger_child++;
			}
			//如果当前元素比子节点中较大的还大（或等于），就不用调整了
			if(compare( &temp ,  &(head->list)[bigger_child] )>=0 )
			{
				break;
			}
			//否则，调换较大子节点和父节点的值（等价于）
			//（在这里并没有真的调换，而是将父节点赋值为较大子节点），对子节点位置继续向下调整
			else
			{
				(head->list)[corrent] = (head->list)[bigger_child];
				corrent = bigger_child;
				bigger_child = LEFT_CHILD(bigger_child);
			}
		}
		//最后需要把找出来的合适的位置赋值为调整节点的值
		(head->list)[corrent] = temp;
		return 0;
	}

}

//看是否为空
int binaryheap_isnull(Binaryheap_head* head)
{
	if(head->corrent_size == 0)
		return 1;
	else
		return 0;
}

//删除堆内所有元素（相当于回到init后的状态）
int binaryheap_reset(Binaryheap_head* head)
{
	head->corrent_size = 0;
	return 0;
}

//free整个堆（包括头结点本身）
int binaryheap_free(Binaryheap_head* head)
{
	free(head->list);
	free(head);
	return 0;
}

/*
//测试用
int cmp(const int a,const int b)
{
	return a-b;
}

int main()
{
	Binaryheap_head* head = binaryheap_init(30);
	int i,num;
	for(i=0;i<30;++i)
		binaryheap_insrt(head,(i*8)%34,cmp);
	for(i=0;i<30;++i)
	{
		num = binaryheap_get_top(head);
		binaryheap_delete_top(head,cmp);
		printf("%d ",num);
	}

}

*/