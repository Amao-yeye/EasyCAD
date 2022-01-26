#include"lucky.h"

void output()
{
	Graph* s = pheadGraph;
	TextString* t = pheadText;
	FILE* fp;
	fp = fopen("savefile.txt", "w");
	while (s)
	{
		fprintf(fp, "Graph: %lf,%lf,%lf,%lf,%lf,%lf,%d,%d,%d,%lf,%d,%d,%d,%d\n", s->x1, s->y1, s->x2, s->y2, s->xmid, s->ymid, s->type, s->color, s->fill, s->angle, s->size, s->ischoosed, s->drawing, s->move);
		s = s->next;
	}
	fprintf(fp, "ToText\n");
	while (t)
	{
		char* textit ;
		textit = t->text;
		fprintf(fp,"Text: ");
		while (*textit != '\0')
		{
			fprintf(fp,"%d ", *textit);
			textit++;
		}
		fprintf(fp,"1000");
		fprintf(fp,"\n");
		fprintf(fp, "%lf,%lf,%lf,%lf,%lf,%lf,%lf,%d,%d,%d,%d,%d\n", t->x0, t->y0, t->x1, t->y1, t->ygraph, t->cx, t->cy, t->color, t->size, t->wordtype, t->ischoosed, t->move);
		t = t->next;
	}
	fclose(fp);
}

void input()//传入Graph的头指针和Text的头指针，读取文件中的内容，对这两个指针指向的地址进行修改
{
	FILE* fp;
	int check = 1;
	fp = fopen("savefile.txt", "r");
	clear();
	char a[10];
	Graph* s = NULL, * sfore;
	TextString* t = NULL, * tfore = NULL;
	check = fscanf(fp, "%s", a);

	while (strcmp(a, "ToText"))
	{
		s = malloc(sizeof(Graph));
		fscanf(fp, "%lf,%lf,%lf,%lf,%lf,%lf,%d,%d,%d,%lf,%d,%d,%d,%d\n", &(s->x1), &(s->y1), &(s->x2), &(s->y2), &(s->xmid), &(s->ymid), &(s->type), &(s->color), &(s->fill), &(s->angle), &(s->size), &(s->ischoosed), &(s->drawing), &(s->move));
		if (pheadGraph == NULL)
		{
			pheadGraph = s;
			s->fore = NULL;
		}
		else {
			s->fore = sfore;
			sfore->next = s;
		}
		sfore = s;
		s->next = NULL;
		check = fscanf(fp, "%s", a);
	}
	check = fscanf(fp, "%s", a);
	while (check != EOF)
	{
		char* textit;
		int read=0;
		t = malloc(sizeof(TextString));
		textit = t->text;
		fscanf(fp, "%d", &read);
		while (read != 1000)
		{
			*textit = (char)read;
			textit++;
			fscanf(fp, "%d",&read);
		}
		*textit = '\0';
		fscanf(fp, "%lf,%lf,%lf,%lf,%lf,%lf,%lf,%d,%d,%d,%d,%d\n", &(t->x0), &(t->y0), &(t->x1), &(t->y1), &(t->ygraph), &(t->cx), &(t->cy), &(t->color), &(t->size), &(t->wordtype), &(t->ischoosed), &(t->move));
		printf("%s", t->text);
		if (pheadText == NULL)
		{
			pheadText = t;
			t->fore = NULL;
		}
		else {
			t->fore = tfore;
			tfore->next = t;
		}
		tfore = t;
		t->next = NULL;
		check = fscanf(fp, "%s", a);
	}
	fclose(fp);
	ReDraw();
}


