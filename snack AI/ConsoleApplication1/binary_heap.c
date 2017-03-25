#include "binary_heap.h"

typedef struct _binaryheap_head 
{
	//����ͷ����̬����
	BINARYHEAP_ELEMENT* list;
	//ʵ�ʴ��Ԫ����
	int corrent_size;
	//�������
	int max_size;

}Binaryheap_head;

//��ʼ��һ�������ͷ������󳤶�Ϊmax_element_num
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

//���ݱȽϺ��������Ѳ���һ��ֵ��compare��������ֵ�ο�qsort��compare��������a����bǰ��ͷ���1������ͷ���0��
int binaryheap_insrt(Binaryheap_head* head, BINARYHEAP_ELEMENT element, int (*compare)(const void* element_a,const void* element_b))
{
	//�������ϵ���
	if(head->corrent_size >= head->max_size)
	{
		return 1;
	}
	else
	{
		// ��ǰ�ڵ��λ��
		int corrent = (head->corrent_size)++;
		// ��(parent)����λ��
		int parent = PARENT(corrent);
		//��element�Ҹ����ʵ�λ��
		while(corrent > 0)
		{
			//������ڵ�����󣬲��õ���
			if(compare(&(head->list)[parent],&element) >= 0)
				break;
			//���򣬽������븸�ڵ�λ�ã��ȼ��ڣ�
			else
			{
				(head->list)[corrent] = (head->list)[parent];
				corrent = parent;
				parent = PARENT(parent);
			}
		}
		//��element�Ž�ȥ
		(head->list)[corrent] = element;
		return 0;
	}
}

//�õ��Ѷ�Ԫ�ص�ֵ�����ı�ѣ�
BINARYHEAP_ELEMENT binaryheap_get_top(Binaryheap_head* head)
{
	if(head->corrent_size != 0)
		return (head->list)[0];
	else
		return NOTHING;
}

//ɾ���Ѷ�Ԫ�أ�������compare����������
int binaryheap_delete_top(Binaryheap_head* head, int (*compare)(const void* element_a,const void* element_b))
{
	//�������µ���
	if(head->corrent_size <= 0)
	{
		return 1;
	}
	else
	{
		//�ȼ��ڣ�����βԪ���õ���ͷ����ɾ����βԪ��
		//��ǰλ��
		int corrent = 0;
		//��ǰֵ
		BINARYHEAP_ELEMENT temp = (head->list)[--(head->corrent_size)];
		// ����bigger child�������ӵ�λ��
		int bigger_child = LEFT_CHILD(corrent);

		//����βԪ���Ҹ����ʵ�λ��
		while(bigger_child <= head->corrent_size)
		{
			//����ǰԪ�غ����������ӽڵ���бȽ�
			//��ѡ���ӽڵ��нϴ��һ��
			if(bigger_child <  head->corrent_size && compare(  &(head->list)[bigger_child+1] , &(head->list)[bigger_child])  >=0 )
			{
				bigger_child++;
			}
			//�����ǰԪ�ر��ӽڵ��нϴ�Ļ��󣨻���ڣ����Ͳ��õ�����
			if(compare( &temp ,  &(head->list)[bigger_child] )>=0 )
			{
				break;
			}
			//���򣬵����ϴ��ӽڵ�͸��ڵ��ֵ���ȼ��ڣ�
			//�������ﲢû����ĵ��������ǽ����ڵ㸳ֵΪ�ϴ��ӽڵ㣩�����ӽڵ�λ�ü������µ���
			else
			{
				(head->list)[corrent] = (head->list)[bigger_child];
				corrent = bigger_child;
				bigger_child = LEFT_CHILD(bigger_child);
			}
		}
		//�����Ҫ���ҳ����ĺ��ʵ�λ�ø�ֵΪ�����ڵ��ֵ
		(head->list)[corrent] = temp;
		return 0;
	}

}

//���Ƿ�Ϊ��
int binaryheap_isnull(Binaryheap_head* head)
{
	if(head->corrent_size == 0)
		return 1;
	else
		return 0;
}

//ɾ����������Ԫ�أ��൱�ڻص�init���״̬��
int binaryheap_reset(Binaryheap_head* head)
{
	head->corrent_size = 0;
	return 0;
}

//free�����ѣ�����ͷ��㱾��
int binaryheap_free(Binaryheap_head* head)
{
	free(head->list);
	free(head);
	return 0;
}

/*
//������
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