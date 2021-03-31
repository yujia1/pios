struct list_element {
	struct list_element *next;
	int data;
};

void add(struct list_element* head, int data);
void remove_list(struct list_element* head, int data);
void print_list(struct list_element* head);
