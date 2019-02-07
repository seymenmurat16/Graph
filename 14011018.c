#include<stdio.h>
#include<stdlib.h>
#include<string.h>

# define boyut 5000 // queue nin boyutu

typedef struct Queue {
	int front,rear;
	int qu[boyut];
	int count;
}Queue;

int DugumlerBagliMi(char kelime1[5],char kelime2[5]);
int indisDondur(char kelime[5],char **kelimeler,int size);
void initialize(Queue *);
void enqueue (int value,Queue *queue);
int isEmpty(Queue *queue);
int isFull(Queue *queue);


int main (){
	FILE *fs;
	int  size=2500,i,j,z,compare,**mtr,a,dizi[2500],sayac=0;
	int path[1000],basdeger,bitdeger,sayac2=0,sirali[1000];
	char kelime[6],**kelimeler,baslangic[6],bitis[6];
   		
 	kelimeler = (char **)calloc( size , sizeof(char*) ); // kelimeler i�in yer a��yorum
   	if( kelimeler == NULL ) {
		printf( "Yetersiz bellek!" );
	}
	for( i = 0; i < size; i++ ) {
		kelimeler[i] = (char *)calloc( size , sizeof(char) );
		if( kelimeler[i] == NULL )
			printf( "Yetersiz bellek!" );
	}
	i=0;
	fs=fopen("kelime.txt","r");  // Dosyay� okuyorum
	 	while(!feof(fs)){ 
		 	fscanf(fs,"%s",kelimeler[i]); // Matrise her kelimeyi yerle�tiriyorum
		 	i++;
	  	}
   	fclose(fs); 
   	mtr = (int **)calloc( size , sizeof(int*) ); // D���mlerin birbirleri ile aralar�nda ba�lant�s� i�in mtr yi olu�turuyorum
   	if( mtr == NULL ) {
		printf( "Yetersiz bellek!" );
	}
	for( i = 0; i < size; i++ ) {
		mtr[i] = (int *)calloc( size , sizeof(int) );
		if( mtr[i] == NULL )
			printf( "Yetersiz bellek!" );
	}
	for(i=0;i<size;i++){ // Kelimenin queue ya daha �nce eklenip eklenmedi�ini kontrol etmek i�in diziyi olu�turuyorum
		dizi[i]=0;
	}
	
   	for(i=0;i<size;i++){ // D���mler aras�ndaki ba�lant� bilgisini matrise at�yorum
   		for(j=0;j<size;j++){
   			compare=0;
   			for(z=0;z<5;z++){
   				if(kelimeler[i][z]!=kelimeler[j][z]){
   					compare++;
				   }   
			   }
			if(compare==1){
				mtr[i][j]=1;
			}
			else{				
				mtr[i][j]=0;
			}  
	    }
   }
   
   // Labta DugumlerBagliMi fonksiyonunu �al���p �al��mad���n� g�stermek i�in yorum sat�r� olarak ekledim
   /*
   printf("Baslangic:"); // Ba�lang�� kelimesini al�yorum
   scanf("%s",baslangic);
   printf("Bitis:"); // Bitis kelimesini al�yorum
   scanf("%s",bitis);
   printf("return : %d\n",DugumlerBagliMi(baslangic,bitis)); */
   
   
   Queue *queue = (Queue *)malloc(sizeof(Queue)); // Queue i�in yer a��yorum
   initialize(queue); // Queue yu olu�turuyorum
   
   printf("Baslangic:"); // Ba�lang�� kelimesini al�yorum
   scanf("%s",baslangic);
   printf("Bitis:"); // Bitis kelimesini al�yorum
   scanf("%s",bitis);
   
   basdeger=indisDondur(baslangic,kelimeler,size); // Baslang�� ve biti� kelimelerinin indisini basdeger ve bitdeger e at�yorum
   bitdeger=indisDondur(bitis,kelimeler,size);
   
   if(basdeger==-1 && bitdeger==-1){ // E�er kelimeler dosyada yoksa program� sonland�r�yorum
   	 printf("%s ve %s kelimeleri dosyada yok",baslangic,bitis);
   	 exit(0);
   }
   if(basdeger==-1){
   	 printf("%s kelimesi dosyada yok",baslangic);
   	 exit(0);
   }
   if(bitdeger==-1){
   	printf("%s kelimesi dosyada yok",bitis);
	exit(0);   
   }
   
   enqueue(basdeger,queue); // Baslangicin indisini queue ya koyuyorum
   dizi[basdeger]=1; // Queue ya ekledi�im i�in dizide o indisi 1e e�itliyorum
   
   while(!isEmpty(queue) && basdeger!=bitdeger){ // Queue bo�alana kadar ya da biti� kelimesini bulana kadar devam ediyorum
   		basdeger=dequeue(queue); // Queue dan kelimenin indisini ��kar�yorum
   		if(basdeger!=bitdeger){ // while i�inde basdegeri de�i�tirdi�im i�in ba�degerin bitdegere e�it olup olmad���n� kontrol ediyorum
   				path[sayac]=basdeger; // path dizisine queue dan ��kard���m her d���m�n indisini ekliyorum
   				sayac++; 
   				for(i=0;i<size;i++){ // t�m kelimelerle aras�nda ba�lant�s�n� kontol ediyorum
   					if(mtr[basdeger][i]==1 && dizi[i]==0){ // e�er queueya daha �nceden eklenmediyse ve aras�nda ba�lant� varsa if e giriyor
   						enqueue(i,queue); // her buldu�um d���m� queue ya ekliyorum 
						if(i==bitdeger){ // e�er biti� kelimesini bulursam bu if e giriyor
							path[sayac]=i; // biti� kelimesini de path dizisine ekliyorum
							sayac++; 
							basdeger=bitdeger; // while d�ng�s�nden ��kmas� i�in basdegeri bitde�ere e�itliyorum
							i=size;	// for d�ng�s�nden ��kmas� i�in i yi size a e�itliyorum 		 		 		 	
						}
   						dizi[i]=1; // queue ya ekledi�im her kelimenin indisini dizide 1 e e�itliyorum
					   }  
				   }
		   }
   }
   
   if(basdeger!=bitdeger){ // e�er basdeger bitdeger e�it de�ilse queue bo�ald��� i�in ��kt���n� anl�yorum ve kullan�c�ya yolun bulunamad���n� bildiriyorum
   	printf("Yol bulunamadi.");
   	exit(0);
   }
   
   // Queue ya eklenen kelimelerin raporda ad�mlar�n� g�sterilmesi istendi�i i�in yorum olarak koda ekledim
   /*printf("\nQueue ya eklenen kelimeler\n");
   for(i=0;i<sayac-1;i++){
			printf("%s\n",kelimeler[path[i]]);
   }
   printf("%s\n",kelimeler[path[sayac-1]]);*/
   
   path[sayac]=bitdeger; // path e son olarak bitis kelimesini ekliyorum
   i=sayac; 
   while(i>0){ // // path dizisine ekledi�im t�m kelimeleri en sondan ba�layarak aralar�nda bir harf fark var m� diye kontrol ediyorum
	   	if(DugumlerBagliMi(kelimeler[path[i]],kelimeler[path[i-1]])){ // kelimeler aras�nda bir harf fark var m� diye kontrol ediyorum
	   		sirali[sayac2]=path[i]; // e�er bir harf fark varsa sirali dizisine ekliyorum
	   		sayac2++; 
	   		i--;
		   }
		else{ // e�er bir harf fark yoksa
			a=i;
			while(DugumlerBagliMi(kelimeler[path[i]],kelimeler[path[a-1]])==0){ // sirali dizisine ekleyece�im kelime ile aras�nda bir harf fark olan kelimeyi bulana kadar devam ediyorum
				a--;
			}
			sirali[sayac2]=path[i]; // sirali dizisine ekliyorum
	   		sayac2++;
			i=a-1;
		}   
   }
   
   sirali[sayac2]=indisDondur(baslangic,kelimeler,size); // siraliya son olarak baslangic kelimesininin indisini ekliyorum
   
   printf("\n%s ",kelimeler[sirali[sayac2]]); // sirali dizisine kelimeleri tersten ba�layarak ekledi�im i�in kullan�c�ya g�sterirken bunu de�i�tiriyorum
   for(i=sayac2-1;i>=0;i=i-1){
   		printf(" -> %s",kelimeler[sirali[i]]);																	
   }
  
   printf("\n\nAdim Sayisi : %d",sayac2+1);
   
   for( i = 0; i < size; i++ ) { 
		free( kelimeler[i] );
	}
	free( kelimeler );
	
	for( i = 0; i < size; i++ ) {
		free( mtr[i] );
	}
	free( mtr );
   return 0;
   
}
   void initialize(Queue *queue){
   	queue->front=queue->rear=0;
   	queue->count=0;
   }
   int isEmpty(Queue *queue){
	   	if(queue->count==0){
	   		return 1;
		   }
		else {
			 return 0;	
		}   
   }
   int isFull(Queue *queue){
	   	if(queue->count==boyut){
	   		return 1;
		   }
		else {
			 return 0;	
		}   
   }
   void enqueue (int value,Queue *queue){
   		queue->qu[queue->rear]=value;
   		queue->rear=queue->rear+1;
   		queue->count++;
   }
   int dequeue (Queue *queue){
  	   int donen;
  	   donen=queue->qu[queue->front];
  	   queue->front=queue->front+1;
  	   queue->count--;
  	   return donen;
   }
   
   int indisDondur(char kelime[5],char **kelimeler,int size){ // Kelimenini ka��nc� indiste oldu�unu d�nd�r�yor
   	int i,j,compare;
   	   for(i=0;i<size;i++){ // t�m kelimeleri ar�yorum
	     compare=0;
   			for(j=0;j<5;j++){ // e�er t�m karakterler ayn� ise kelimeler dizisinde keliminin ka��nc� indiste oldu�unu d�nd�r�yorum
   				if(kelimeler[i][j]==kelime[j]){
   					compare++;
				   }   
			   }
			if(compare==5){
				return i;
			}
	    }
	    return -1; // e�er kelime yoksa -1 d�n�yor
   }
  
   int DugumlerBagliMi(char kelime1[5],char kelime2[5]){ // �ki kelime aras�nda 1 harfin farkl� olup olmamas�na bak�yor
	   int i,compare=0;
	   for(i=0;i<5;i++){ // iki kelimenin karekterlerini kar��la�t�r�p e�er ayn� olmayan 1 harf var 1 d�nd�r�yor yoksa 0 d�nd�r�yor
		   	if(kelime1[i]!=kelime2[i]){
		   		compare++;
			   }
		}
		if(compare==1){
			return 1;
		}
		else{		
			return 0;
		}  
    }
