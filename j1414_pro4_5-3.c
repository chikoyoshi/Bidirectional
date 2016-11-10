//j1414 小林　佳樹　j1414_pro4_4-1.c

#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int data;
	struct node *next;
	struct node *prev;
}LISTEL;

LISTEL root;

//双方向リストを構築する関数
void construct_list()
{
	LISTEL *p,*q;
	int n, y, i, k, noIndex[50];
	char buf[100];
	while(1)
	{
		fprintf(stdout,"Input Data: ");
		fgets(buf, sizeof(buf), stdin);

		if(buf[0] == '\n')	{return;}
		i = 0, k = 0;
		//最初に入力された文字がスペースでない場合、配列の場所をnoIndex[]に格納
		if(buf[i] != ' ')		{noIndex[k++] = i;}
		//2つ目以降に入力された文字がスペースでない場合、配列の場所をnoIndex[]に格納
		while(buf[i] != '\0')
		{
			i++;
			if(buf[i-1] == ' ' && buf[i] != ' ' && buf[i] != '\n')		{noIndex[k++] = i;}
		}
		//文字数がオーバーした場合
		if(buf[i-1] != '\n')
		{
			fprintf(stderr, "Error : Too long input data\n");
			exit(1);
		}
		//入力された数字を双方向リストに格納する
		for(i=0;i<k;i++){
			//buf[]に格納されている数字を読み込んでｙに格納し、その結果をｎに格納
			n = sscanf(&buf[noIndex[i]], "%d",&y);
			if(n != 1){
				fprintf(stderr, "Error no number input data\n");
				continue;
			}

			//追加するノードを指すポインタのメモリを動的に確保する
			p = (LISTEL *)malloc(sizeof(LISTEL));
			q = (LISTEL *)malloc(sizeof(LISTEL));
			q = root.next;	//先頭のノードのアドレスを格納
			p->data = y;	//追加するノードに入力された数字を格納
			p->next = q;	//追加するノードの次のアドレスを先頭ノードにする
			p->prev = q->prev;
			root.next = q->prev = p;	//追加前の先頭ノードが指す前のノードを追加するノードにする,先頭を指すノードが、追加するノードを指すようにする
		}
	}
}

//連結リストを出力する関数
void print_list()
{
	LISTEL *p,*q;
	p = root.next;
	q = root.prev;
	if(p == &root || q == &root)
	{
		fprintf(stderr, "There is no data!");
		return;
	}
	fprintf(stdout,"List data(From Last):");
	while(p != &root)
	{
		fprintf(stdout,"%2d  ",p->data);
		p = p->next;
	}
	printf("\n");
	fprintf(stdout,"List data(From First):");
	while(q != &root)
	{
		fprintf(stdout,"%2d  ",q->data);
		q = q->prev;
	}
	fprintf(stdout,"\n");
}

//新しいノード(データ:y)をｋ番目に挿入する関数
void insert_node(int k, int y)
{
	int i;
	LISTEL *p,*q;
	if(k <= 0)
	{
		fprintf(stderr, "Error : Target node is not found!\n");
		return ;
	}
	p = (LISTEL *)malloc( sizeof(LISTEL));
	q = (LISTEL *)malloc( sizeof(LISTEL));
	p = root.next;
	q->data = y;
	if(k==1)
	{
		q->next = p;
		q->prev = &root;
		root.next = q;
		p->prev = q;
	}
	else{
	for(i=0;i<k-2;i++)
	{
		if(p == &root)
		{
			fprintf(stderr,"Error : Target node is not found!\n");
			return;
		}
		p = p->next;
	}
	q->next = p->next;
	q->prev = p;
	p->next->prev = q;
	p->next = q;
}
}

//リスト内のデータを削除する関数
void delete_node(int k)
{
	int i;
	LISTEL *p,*q;
	p = (LISTEL *)malloc(sizeof(LISTEL));
	p = root.next;
	if(p == &root|| k <= 0)
	{
		printf("Error : Target node is not found!\n");
		return;
	}
	//先頭ノードを削除するプログラムを書く
	/*p = p->next;
	p = root.next;
	q = (LISTEL *)malloc(sizeof(LISTEL));
	q = NULL;*/
	//2番目以降のノードを削除するプログラムを書く
	for(i=0;i<k-1;i++)
	{
		if(p == &root)
		{
			printf("Erro : Target node is not found!\n");
			return;
		}
		p = p->next;
	}
	p->prev->next = p->next;
	p->next->prev = p->prev;
}

//置き換え関数
void replace_node(int x,int y)
{
	int i;
	LISTEL *p;
	if((p = (LISTEL *)malloc(sizeof(LISTEL))) == NULL)	{exit(1);}
	p = root.next;
	for(i=0;;i++)
	{
		if(p == &root)
		{
			fprintf(stderr,"Error : Target node is not found!\n");
			return;
		}
		if(p->data == x)
		{
			p->data = y;
		}
		p = p->next;
	}
}

int main()
{
	int k, y,x;
	root.next = root.prev = &root;
	construct_list();
	print_list();

	printf("*******Insert*******\n");
	printf("Input insert-location: ");
	scanf("%d", &k);
	printf("Input insert data:");
	scanf("%d", &y);
	insert_node(k,y);
	print_list();

	printf("*******Delete*******\n");
	printf("Input delete-location: ");
	scanf("%d",&k);
	delete_node(k);
	print_list();

	printf("*******Replace*******\n");
	printf("Input search data: ");
	scanf("%d",&x);
	printf("Input replace data: ");
	scanf("%d", &y);
	replace_node(x,y);
	print_list();

	return 0;
}
