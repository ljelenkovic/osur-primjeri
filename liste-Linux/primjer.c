#include <stdio.h>
#include <unistd.h>

#include "list.h"

struct trojke {
	int a, b, c;
	struct list_head list;
};

LIST_HEAD(lista);

int main()
{
	struct trojke p[10], *obj;
	struct list_head *iter, *next;
	int i;

	for (i = 0; i < 10; i++) {
		p[i].a = i;
		p[i].b = i*i;
		p[i].c = i*i*i;

		list_add_tail(&p[i].list, &lista);
	}

	printf("iteracija preko: list_for_each_entry\n");
	list_for_each_entry(obj, &lista, list) {
		printf("%d %d %d\n", obj->a, obj->b, obj->c);
		sleep(1);
	}
	printf("U listi imam elemenata: %ld\n", list_count_nodes(&lista));

	printf("\niteracija preko: list_for_each_safe\n");
	list_for_each_safe(iter, next, &lista) {
		obj = list_entry(iter, struct trojke, list);
		if (obj->a == 5) {
			list_del(iter);
		}
		else {
			printf("%d %d %d\n", obj->a, obj->b, obj->c);
			sleep(1);
		}
	}
	printf("U listi imam elemenata: %ld\n", list_count_nodes(&lista));

	return 0;
}
