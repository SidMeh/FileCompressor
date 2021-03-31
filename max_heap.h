typedef struct max_heap{
	int arr[256][2];
	int rear;
}max_heap;

void init_max_heap(max_heap *h);
void insert_max_heap(max_heap *h,int key, int ascii);
void traverse_max_heap(max_heap h);
void map_code_via_heap(max_heap h,int code_arr[256][2]);
