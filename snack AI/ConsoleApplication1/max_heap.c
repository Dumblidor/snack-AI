#include "max_heap.h"

// ����
static int maxheap_list[MAXHEAP_MAX_LENGTH];
// ʵ������(��ʼ��Ϊ0)
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
		// �����Ԫ���
		maxheap_list[0] = maxheap_list[--maxheap_size];
		// ��indexλ�ÿ�ʼ�������µ���Ϊ����
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
    // ��ǰ�ڵ��λ��
    int corrent = start;
    // ��ǰ�ڵ�Ĵ�С
    int temp = maxheap_list[corrent];
	// ����bigger child�������ӵ�λ��
	int bigger_child = LEFT_CHILD(corrent);

    while(bigger_child <= end)
    {
        // "bigger_child"�����ӣ�"bigger_child+1"���Һ��ӣ�����Һ��ӱȽϴ����bigger child����Һ��ӵ�λ��
        if(bigger_child < end && maxheap_list[bigger_child] < maxheap_list[bigger_child+1])
		{
            bigger_child++;
		}
		//�����ǰ�ڵ���ӽڵ㶼�󣨻���ڣ����Ͳ��õ�����
        if(temp >= maxheap_list[bigger_child])
		{
            break;
		}
		//���򣬵����ϴ��ӽڵ�͸��ڵ��ֵ�������ﲢû����ĵ��������ǽ����ڵ㸳ֵΪ�ϴ��ӽڵ㣩�����ӽڵ�λ�ü������µ���
        else
        {
            maxheap_list[corrent] = maxheap_list[bigger_child];
            corrent = bigger_child;
            bigger_child = LEFT_CHILD(bigger_child);
        }
    }
	//�����Ҫ���ҳ����ĺ��ʵ�λ�ø�ֵΪ�����ڵ��ֵ
    maxheap_list[corrent] = temp;
}

int maxheap_remove(int data)
{
    int index;
    // ���"��"�ѿգ��򷵻�-1
    if(maxheap_size == 0)
        return -1;

    // ��ȡdata�������е�����
    index = maxheap_get_index(data);
    if (index==-1)
        return -1;
	// �����Ԫ���
    maxheap_list[index] = maxheap_list[--maxheap_size];
	// ��indexλ�ÿ�ʼ�������µ���Ϊ����
    maxheap_filterdown(index, maxheap_size-1);

    return 0;
}

static void maxheap_filterup(int start)
{
	// ��ǰ�ڵ�(current)��λ��
    int corrent = start;
	// ��(parent)����λ��
    int parent = PARENT(corrent);
	// ��ǰ�ڵ�(current)�Ĵ�С
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
    // ���"��"�������򷵻�
    if(maxheap_size == MAXHEAP_MAX_LENGTH)
        return -1;

    maxheap_list[maxheap_size] = data;        // ��"����"���ڱ�β
    maxheap_filterup(maxheap_size);    // ���ϵ�����
    maxheap_size++;                    // �ѵ�ʵ������+1

    return 0;
}

void maxheap_print()
{
    int i;
    for (i=0; i<maxheap_size; i++)
        printf("%d ", maxheap_list[i]);
}

/*
//������
void main()
{
    int a[] = {10, 40, 30, 60, 90, 70, 20, 50, 80};
    int i, len=LENGTH(a);

    printf("== �������: ");
    for(i=0; i<len; i++)
    {
        printf("%d ", a[i]);
        maxheap_insert(a[i]);
    }

    printf("\n== �� �� ��: ");
    maxheap_print();

    i=85;
    maxheap_insert(i);
    printf("\n== ���Ԫ��: %d", i);
    printf("\n== �� �� ��: ");
    maxheap_print();

    i=90;
    maxheap_remove(i);
    printf("\n== ɾ��Ԫ��: %d", i);
    printf("\n== �� �� ��: ");
    maxheap_print();
    printf("\n");
}
*/
