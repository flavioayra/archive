#include <stdio.h>
#include <string.h>
#include <glib/glib.h>

GList *list;

typedef struct {
   	char buf[1024];
	char desc[1024];
} data_t;

data_t data;

void show_list(GList *l)
{
   	GList *ll = g_list_first(l);
	unsigned short int i = 0;
	void *p;
	
   	fprintf(stderr, "starting list dump\n");
	
	for (i = 0;i < g_list_length(list) - 1; i++) {
	   	fprintf(stderr, "%s\n", g_list_nth_data(list, i));
	}
	
	fprintf(stderr, "finishing list dump\n");
}

int main(int argc, char **arv)
{
   	data_t d, d2;
	
	list = g_list_alloc();
		
	show_list(list);

	memset(d.buf, 0, sizeof(d.buf));
	memset(d.desc, 0, sizeof(d.desc));
	strcpy(d.buf, "abc");
	strcpy(d.desc, "desc1");

	list = g_list_insert(list, &d, 0);

	show_list(list);
	
	memset(d2.buf, 0, sizeof(d2.buf));
	memset(d2.desc, 0, sizeof(d2.desc));
	strcpy(d2.buf, "def");
	strcpy(d2.desc, "desc2");
                        
	list = g_list_insert(list, &d2, 1);


	show_list(list);

	g_list_free(list);

	return 0;
}
