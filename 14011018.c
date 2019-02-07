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
   		
 	kelimeler = (char **)calloc( size , sizeof(char*) ); // kelimeler için yer açýyorum
   	if( kelimeler == NULL ) {
		printf( "Yetersiz bellek!" );
	}
	for( i = 0; i < size; i++ ) {
		kelimeler[i] = (char *)calloc( size , sizeof(char) );
		if( kelimeler[i] == NULL )
			printf( "Yetersiz bellek!" );
	}
	i=0;
	fs=fopen("kelime.txt","r");  // Dosyayý okuyorum
	 	while(!feof(fs)){ 
		 	fscanf(fs,"%s",kelimeler[i]); // Matrise her kelimeyi yerleþtiriyorum
		 	i++;
	  	}
   	fclose(fs); 
   	mtr = (int **)calloc( size , sizeof(int*) ); // Düðümlerin birbirleri ile aralarýnda baðlantýsý için mtr yi oluþturuyorum
   	if( mtr == NULL ) {
		printf( "Yetersiz bellek!" );
	}
	for( i = 0; i < size; i++ ) {
		mtr[i] = (int *)calloc( size , sizeof(int) );
		if( mtr[i] == NULL )
			printf( "Yetersiz bellek!" );
	}
	for(i=0;i<size;i++){ // Kelimenin queue ya daha önce eklenip eklenmediðini kontrol etmek için diziyi oluþturuyorum
		dizi[i]=0;
	}
	
   	for(i=0;i<size;i++){ // Düðümler arasýndaki baðlantý bilgisini matrise atýyorum
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
   
   // Labta DugumlerBagliMi fonksiyonunu çalýþýp çalýþmadýðýný göstermek için yorum satýrý olarak ekledim
   /*
   printf("Baslangic:"); // Baþlangýç kelimesini alýyorum
   scanf("%s",baslangic);
   printf("Bitis:"); // Bitis kelimesini alýyorum
   scanf("%s",bitis);
   printf("return : %d\n",DugumlerBagliMi(baslangic,bitis)); */
   
   
   Queue *queue = (Queue *)malloc(sizeof(Queue)); // Queue için yer açýyorum
   initialize(queue); // Queue yu oluþturuyorum
   
   printf("Baslangic:"); // Baþlangýç kelimesini alýyorum
   scanf("%s",baslangic);
   printf("Bitis:"); // Bitis kelimesini alýyorum
   scanf("%s",bitis);
   
   basdeger=indisDondur(baslangic,kelimeler,size); // Baslangýç ve bitiþ kelimelerinin indisini basdeger ve bitdeger e atýyorum
   bitdeger=indisDondur(bitis,kelimeler,size);
   
   if(basdeger==-1 && bitdeger==-1){ // Eðer kelimeler dosyada yoksa programý sonlandýrýyorum
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
   dizi[basdeger]=1; // Queue ya eklediðim için dizide o indisi 1e eþitliyorum
   
   while(!isEmpty(queue) && basdeger!=bitdeger){ // Queue boþalana kadar ya da bitiþ kelimesini bulana kadar devam ediyorum
   		basdeger=dequeue(queue); // Queue dan kelimenin indisini çýkarýyorum
   		if(basdeger!=bitdeger){ // while içinde basdegeri deðiþtirdiðim için baþdegerin bitdegere eþit olup olmadýðýný kontrol ediyorum
   				path[sayac]=basdeger; // path dizisine queue dan çýkardýðým her düðümün indisini ekliyorum
   				sayac++; 
   				for(i=0;i<size;i++){ // tüm kelimelerle arasýnda baðlantýsýný kontol ediyorum
   					if(mtr[basdeger][i]==1 && dizi[i]==0){ // eðer queueya daha önceden eklenmediyse ve arasýnda baðlantý varsa if e giriyor
   						enqueue(i,queue); // her bulduðum düðümü queue ya ekliyorum 
						if(i==bitdeger){ // eðer bitiþ kelimesini bulursam bu if e giriyor
							path[sayac]=i; // bitiþ kelimesini de path dizisine ekliyorum
							sayac++; 
							basdeger=bitdeger; // while döngüsünden çýkmasý için basdegeri bitdeðere eþitliyorum
							i=size;	// for döngüsünden çýkmasý için i yi size a eþitliyorum 		 		 		 	
						}
   						dizi[i]=1; // queue ya eklediðim her kelimenin indisini dizide 1 e eþitliyorum
					   }  
				   }
		   }
   }
   
   if(basdeger!=bitdeger){ // eðer basdeger bitdeger eþit deðilse queue boþaldýðý için çýktýðýný anlýyorum ve kullanýcýya yolun bulunamadýðýný bildiriyorum
   	printf("Yol bulunamadi.");
   	exit(0);
   }
   
   // Queue ya eklenen kelimelerin raporda adýmlarýný gösterilmesi istendiði için yorum olarak koda ekledim
   /*printf("\nQueue ya eklenen kelimeler\n");
   for(i=0;i<sayac-1;i++){
			printf("%s\n",kelimeler[path[i]]);
   }
   printf("%s\n",kelimeler[path[sayac-1]]);*/
   
   path[sayac]=bitdeger; // path e son olarak bitis kelimesini ekliyorum
   i=sayac; 
   while(i>0){ // // path dizisine eklediðim tüm kelimeleri en sondan baþlayarak aralarýnda bir harf fark var mý diye kontrol ediyorum
	   	if(DugumlerBagliMi(kelimeler[path[i]],kelimeler[path[i-1]])){ // kelimeler arasýnda bir harf fark var mý diye kontrol ediyorum
	   		sirali[sayac2]=path[i]; // eðer bir harf fark varsa sirali dizisine ekliyorum
	   		sayac2++; 
	   		i--;
		   }
		else{ // eðer bir harf fark yoksa
			a=i;
			while(DugumlerBagliMi(kelimeler[path[i]],kelimeler[path[a-1]])==0){ // sirali dizisine ekleyeceðim kelime ile arasýnda bir harf fark olan kelimeyi bulana kadar devam ediyorum
				a--;
			}
			sirali[sayac2]=path[i]; // sirali dizisine ekliyorum
	   		sayac2++;
			i=a-1;
		}   
   }
   
   sirali[sayac2]=indisDondur(baslangic,kelimeler,size); // siraliya son olarak baslangic kelimesininin indisini ekliyorum
   
   printf("\n%s ",kelimeler[sirali[sayac2]]); // sirali dizisine kelimeleri tersten baþlayarak eklediðim için kullanýcýya gösterirken bunu deðiþtiriyorum
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
   
   int indisDondur(char kelime[5],char **kelimeler,int size){ // Kelimenini kaçýncý indiste olduðunu döndürüyor
   	int i,j,compare;
   	   for(i=0;i<size;i++){ // tüm kelimeleri arýyorum
	     compare=0;
   			for(j=0;j<5;j++){ // eðer tüm karakterler ayný ise kelimeler dizisinde keliminin kaçýncý indiste olduðunu döndürüyorum
   				if(kelimeler[i][j]==kelime[j]){
   					compare++;
				   }   
			   }
			if(compare==5){
				return i;
			}
	    }
	    return -1; // eðer kelime yoksa -1 dönüyor
   }
  
   int DugumlerBagliMi(char kelime1[5],char kelime2[5]){ // Ýki kelime arasýnda 1 harfin farklý olup olmamasýna bakýyor
	   int i,compare=0;
	   for(i=0;i<5;i++){ // iki kelimenin karekterlerini karþýlaþtýrýp eðer ayný olmayan 1 harf var 1 döndürüyor yoksa 0 döndürüyor
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
