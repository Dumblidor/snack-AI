#include "max_heap.h"

// 数据
static int maxheap_list[MAXHEAP_MAX_LENGTH];
// 实际容量(初始化为0)
static int maxheap_size=0;


int maxheap_get_index(int data)
{
    int i=0;

    for(i=0; i<maxheap_size; i++)
        if (data==maxheap_list[i])
            return i;

    return -1;
}

int maxheap_get_max_num()
{
	if(maxheap_size == 0)
		return 0;
	else
	{
		int max_num=maxheap_list[0];
		// 用最后元素填补
		maxheap_list[0] = maxheap_list[--maxheap_size];
		// 从index位置开始自上向下调整为最大堆
		maxheap_filterdown(0, maxheap_size-1);

		return max_num;
	}

}

void maxheap_init()
{
	int i;
	maxheap_size=0;
	for(i=0;i<MAXHEAP_MAX_LENGTH;++i)
	{
		maxheap_list[i]=0;
	}
}


static void maxheap_filterdown(int start, int end)
{
    // 当前节点的位置
    int corrent = start;
    // 当前节点的大小
    int temp = maxheap_list[corrent];
	// 先让bigger child等于左孩子的位置
	int bigger_child = LEFT_CHILD(corrent);

    while(bigger_child <= end)
    {
        // "bigger_child"是左孩子，"bigger_child+1"是右孩子，如果右孩子比较大就让bigger child变成右孩子的位置
        if(bigger_child < end && maxheap_list[bigger_child] < maxheap_list[bigger_child+1])
		{
            bigger_child++;
		}
		//如果当前节点比子节点都大（或等于），就不用调整了
        if(temp >= maxheap_list[bigger_child])
		{
            break;
		}
		//否则，调换较大子节点和父节点的值（在这里并没有真的调换，而是将父节点赋值为较大子节点），对子节点位置继续向下调整
        else
        {
            maxheap_list[corrent] = maxheap_list[bigger_child];
            corrent = bigger_child;
            bigger_child = LEFT_CHILD(bigger_child);
        }
    }
	//最后需要把找出来的合适的位置赋值为调整节点的值
    maxheap_list[corrent] = temp;
}

int maxheap_remove(int data)
{
    int index;
    // 如果"堆"已空，则返回-1
    if(maxheap_size == 0)
        return -1;

    // 获取data在数组中的索引
    index = maxheap_get_index(data);
    if (index==-1)
        return -1;
	// 用最后元素填补
    maxheap_list[index] = maxheap_list[--maxheap_size];
	// 从index位置开始自上向下调整为最大堆
    maxheap_filterdown(index, maxheap_size-1);

    return 0;
}

static void maxheap_filterup(int start)
{
	// 当前节点(current)的位置
    int corrent = start;
	// 父(parent)结点的位置
    int parent = PARENT(corrent);
	// 当前节点(current)的大小
    int temp = maxheap_list[corrent];

    while(corrent > 0)
    {
        if(maxheap_list[parent] >= temp)
            break;
        else
        {
            maxheap_list[corrent] = maxheap_list[parent];
            corrent = parent;
            parent = PARENT(parent);
        }
    }
    maxheap_list[corrent] = temp;
}

int maxheap_insert(int data)
{
    // 如果"堆"已满，则返回
    if(maxheap_size == MAXHEAP_MAX_LENGTH)
        return -1;

    maxheap_list[maxheap_size] = data;        // 将"数组"插在表尾
    maxheap_filterup(maxheap_size);    // 向上调整堆
    maxheap_size++;                    // 堆的实际容量+1

    return 0;
}

void maxheap_print()
{
    int i;
    for (i=0; i<maxheap_size; i++)
        printf("%d ", maxheap_list[i]);
}

/*
//测试用
void main()
{
    int a[] = {10, 40, 30, 60, 90, 70, 20, 50, 80};
    int i, len=LENGTH(a);

    printf("== 依次添加: ");
    for(i=0; i<len; i++)
    {
        printf("%d ", a[i]);
        maxheap_insert(a[i]);
    }

    printf("\n== 最 大 堆: ");
    maxheap_print();

    i=85;
    maxheap_insert(i);
    printf("\n== 添加元素: %d", i);
    printf("\n== 最 大 堆: ");
    maxheap_print();

    i=90;
    maxheap_remove(i);
    printf("\n== 删除元素: %d", i);
    printf("\n== 最 大 堆: ");
    maxheap_print();
    printf("\n");
}
*/
