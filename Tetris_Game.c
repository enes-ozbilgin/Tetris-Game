#include <stdio.h>
#include <stdlib.h>//rand() fonksiyonunu kullanmak i�in bu k�t�phaneyi ekledim
#include <time.h>//program zaman� kullanarak bize rastgele bir say� verece�i i�in bu k�t�phaneyi ekledim


void randomblock(int matrix[3][3],int num){//kolayl�k olsun diye rastgele block fonksiyonu tan�mlad�k
	int i,j;
	int pieces[7][3][3] = {//par�alar�m�zdan olu�an bir k�p tan�mlad�k if else zincirinden kurtulmak i�in
        {{1,0,0},
         {1,0,0},
         {1,1,0}},// L par�as�

        {{0,0,0},
         {0,0,0},
         {1,1,1}},// - par�as�

        {{0,0,0},
         {1,1,0},
         {1,1,0}},// [] par�as�

        {{0,0,0},
         {1,1,0},
         {0,1,1}},// Z par�as�

        {{0,1,0},
         {0,1,0},
         {1,1,0}},// ters L par�as�

        {{0,0,0},
         {0,0,0},
         {1,0,0}},// . par�as�

        {{0,0,0},
         {1,1,1},
         {0,1,0}}//  T par�as� 
    };
    for (i=0;i<3;i++) {
        for (j=0;j<3;j++) {
            matrix[i][j] = pieces[num-1][i][j];//piece matriximize num say�s�na denk gelen par�ay� atad�k
        }
    }
}

void printpiece(int matrix[3][3]){//par�ay� ekrana yazd�racak fonksiyon tan�mlad�k
	int i,j;
	printf("\nCurrent Piece: \n");
	for (i=0;i<3;i++) {
        for (j=0;j<3;j++) {
            if (matrix[i][j]==0)//matrixin eleman� 0 ise bo�luk, 1 ise 1 yazd�racak
                printf("0 ");
            else
                printf("1 ");
        }
        printf("\n");
    }
    printf("^-----\n");
}

void printboard(int N,int M,int board[N][M],int score){//board� ekrana yazd�racak fonksiyon tan�mlad�k
	int i,j;
	printf("\nCurrent score: %d\n",score);//�uanki scoreumuzu g�sterdik
    for (i=0;i<N;i++) {
        for (j=0;j<M;j++) {
            if (board[i][j] == 0)//e�er board 0 sa 0, 1 se 1 yazd�rd�k
                printf("0 ");
            else
                printf("1 ");
        }
        printf("\n");
    }
    for(j=0;j<M;j++)
    printf("--");
    
    printf("\n");
    
    for(j=1;j<=M;j++)
    printf("%d ",j);
    
    printf("\n");
}

void rotatepiece(int matrix[3][3]){//par�am�z� d�nd�recek fonksiyon tan�mlad�k
	int matrix2[3][3];//ge�ici olarak par�am�z�n de�erlerini saklayacak matrix tan�mlad�k
	int i,j;
	for (i=0;i<3;i++) {
        for (j=0;j<3;j++) 
        matrix2[i][j]=matrix[i][j];//par�am�z� ge�ici matrixe kopyalad�k
	}
	for (i=0;i<3;i++) {
        for (j=0;j<3;j++) 
        matrix[i][j]=matrix2[2-j][i];//matrixi saat y�n�nde d�nd�rmek i�in bu i�lemi kulland�k
	}
}

int Ycordinate(int N,int M,int board[N][M],int piece[3][3],int Xc){//Y kordinat�m�z� bulacak fonksiyon tan�mlad�k
	int y[3],i,j,x=2,Yc[3],k=0,z=3,X[3],Y=-1;
	
	for (i=0;i<3 && Y==-1;i++) {//blo�umuz havada m� diye kontrol ediyoruz
    	for (j=0;j<3;j++) {
        	if (piece[x - i][j] == 1) {
            	Y = i;//blo�un ka� blok havada oldu�unu bulduk
            	j=4;//sat�r� bulduktan sonra d�ng�lerden ��k�yoruz
        	}
    	}
	}
	i=2;
	j=0;
	while( j < 3 ) {//ilk olarak par�am�z�n s�t�nlar�n�n y kordinatlar�n� bulduk
		i=2;
		while( i >= 0 && piece[i][j] != 1 ){
			i--;
		}
		if( i >= 0 ){
			y[k] = i;//buldu�umuz par�aya ait y kordinatlar�n� arrayde saklad�k
			k++;
		}
		else {
			y[k] = -N;//e�er s�t�n bo�sa -N de�eri verdik
			k++;
		}
		j++;
	}//par�am�z�n y kordinatlar�n� arrayde saklad�k
	i=0;
	j=0;
	k=0;
	while ( j < 3 ) {//�imdide boardumuzun s�t�nlar�n�n y kordinatlar�n� buluyoruz
		i=0;
		while ( i < N && board[i][Xc+j] != 1 ){
			i++;
		}
		if( i < N ){
			Yc[k] = -i+1;//buldu�umuz y kordinat�n� arrayde saklad�k
			k++;
		}
		else{
			Yc[k] = -N+1;//e�er s�tun bo�sa N-1 sat�rdan bas�l�r
			k++;
			z--;
		}
		j++;
	}//�imdide boardumuzun y kordinatlar�n� bulduk
	for (i=0;i<3;i++){
		X[i]=0;
		X[i] += y[i] + Yc[i];//board ve par�an�n kordinatlar�n� topluyoruz
	}
	if( z == 0 ){//e�er hi�bir s�tunda 1 yoksa o zaman N-1 bizim Y kordinat�m�zd�r
		return N-1;
	}
	if ( X[0] >= X[1] && X[0] >= X[2] ){//en b�y�k de�er bizim ger�ek Y kordinat�m�zd�r
		return -Yc[0] + 2 - y[0] - Y;
	}
	else if ( X[1] > X[0] && X[1] >= X[2] ){
		return -Yc[1] + 2 - y[1] - Y;
	}
	else if ( X[2] > X[1] && X[2] > X[0] ){
		return -Yc[2] + 2 - y[2] - Y;
	}
}

void placepiece(int N,int M,int board[N][M],int piece[3][3],int Xc,int Yc){//par�am�z� boarda koyacak bir fonksiyon tan�mlad�k
	int i,j,x=2,y=-1;

	for (i=0;i<3 && y==-1;i++) {//bast�rmaya ba�l�yaca��m�z sat�r� ar�yoruz
    	for (j=0;j<3;j++) {
        	if (piece[x - i][j] == 1) {
            	y = x - i;//ba�lama sat�r�m�z� bulduk
            	j=4;//sat�r� bulduktan sonra d�ng�lerden ��k�yoruz
        	}
    	}
	}

	if (y!=-1) {//e�er bir ba�lama sat�r� bulduysak o sat�rdan ba�layarak boarda yaz�yoruz
    	for (i=0;i<3 && Yc - i>=0;i++) {
        	for (j=0;j<3;j++) {
            	if (piece[y - i][j] == 1) {//sadece 1 de�erlerimizi boarda bast�r�yoruz
                	board[Yc - i][Xc + j] = 1;//bu i�lemle ba�lama sat�r�ndan ba�lay�p de�erlerimizi boarda yaz�yoruz
            	}
        	}
    	}
	}
}

int checklines(int N,int M,int board[N][M],int score){
	int i,j,x=1,y=0,k;
    for (i=N-1;i>=0;i--) {
        x=1;//x de�erimizi her sat�r i�in tekrar 1 e e�itliyoruz
        for (j=0;j<M;j++) {
            x *= board[i][j];//e�er sat�r�m�zda her s�t�n 1 se o zaman x de�eri 1 kalacak
        }
        if (x == 1) {//e�er sat�r�m�z doluysa bu ko�ul sa�lanacak
            for (j=0;j<M;j++) {
                board[i][j]= 0;//dolu sat�r� sildik
            }
            score += M;//puan�m�z� s�t�n say�s� miktar�nda art�rd�k
            
            for (k=i;k>0;k--) {//�ste kalan 1 lerimizi a�a�� kayd�rmak i�in sildi�imiz sat�r�n �st�ndeki sat�rlar 1 a�a�� indirilir
                for (j=0;j<M;j++) {
                    board[k][j]= board[k - 1][j];//�st sa�rdaki de�erleri alt sat�ra kopyalad�k
                }
            }
            for (j=0;j<M;j++) {//en �ste kalan elemanlar� sildik
                board[1][j] = 0;
            }
        }
    }
    return score;
}

int gameover(int N,int M,int board[N][M]){//en �st sat�r� kontrol eden fonksiyon tan�mlad�k
    int i,j,y = 0;
    for (j = 0; j < M; j++) {//en �st sat�r�m�zda 1 var m� diye kontrol ederiz
        y += board[0][j];
    }
	if( y == 0 ){
		return 0;//bir yoksa 0
	}
	else if( y > 0 ){
		return 1;// bir varsa 1 g�nderdik
	}
}

int canplace(int M,int piece[3][3],int Xc){//e�er bize verilen x kordinat� board�n d���ndam� de�il diye bakan fonksiyon
	int i,j,y,x;
	for (i=2;i>=0;i--) {
    	for (j=0;j<3;j++) {//bast�rmaya ba�l�yaca��m�z s�tunu ar�yoruz
    		if(piece[j][i] == 1){
    			y=i+1;//bast�rmaya ba�l�yaca��m�z s�tunu bulduk
				i=-1;//for ko�ullar�n� break kullanmadan k�rmak i�in bunu kullan�yoruz
				j=4;//for ko�ullar�n� break kullanmadan k�rmak i�in bunu kullan�yoruz	
			}
    	}
    }
    for (i=0;i<3;i++) {
    	for (j=0;j<3;j++) {//bast�rmaya ba�l�yaca��m�z s�tunu ar�yoruz
    		if(piece[j][i] == 1){
    			x=i+1;//bast�rmaya ba�l�yaca��m�z s�tunu bulduk
				i=4;//for ko�ullar�n� break kullanmadan k�rmak i�in bunu kullan�yoruz
				j=4;//for ko�ullar�n� break kullanmadan k�rmak i�in bunu kullan�yoruz	
			}
    	}
    }
    if( Xc < 0 ) {
    	if ( Xc + x > 0 ){//bu ko�ul sa�lan�rsa par�ay� yerle�tirebiliyoruz
    		return 1;
		}
		else//bu ko�ul sa�lan�rsa par�ay� yerle�tiremiyoruz
		return 0;	
	}
	if( Xc + y > M ){//bu ko�ul sa�lan�rsa par�ay� yerle�tiremiyoruz
		return 0;
	}
	else if( Xc + y <= M ){//bu ko�ul sa�lan�rsa par�ay� yerle�tirebiliyoruz
		return 1;
	}
}

int main(){
	
	srand(time(0));//ayn� say�y� almamak i�in zaman� s�f�rlad�k
	
	char X='a',Y='a',x='a';//karakter variablelar�m�z� tan�mlad�k
	
	int xcordinate,ycordinate,N,M,RandNum,i,j,Gameover,can,highscore = 0,score = 0;//integer variablelar�m�z� tan�mlad�k
	
	int piece[3][3]={0};//bu bizim rastgele blockumuz			  
				             			
	while (X!='n') {//While d�ng�s�nde X ile ko�ul kurduk.Burada X, kullan�c� oyun bitiminde oyunu tekrar oynamak istemezse while'� k�racak.
	
		Y='a';//tekrar oynanmak isterse Y'yi resetledik
		
		printf("\nWelcome to my Tetris game\n");//men�m�z
		
		printf("\nCurrent Highscore:%d\n",highscore);//Highscore g�sterdik

		printf("\nPlease enter the boards Row Number min(5) max(20):");
		scanf(" %d",&N);
		
		while (N<5 || N>20){//e�er tan�mlad���m�z aral�kta de�ilse tekrar de�er al�yoruz
			printf("wrong");
			printf("\nPlease enter the boards Row Number min(5) max(20):");
			scanf(" %d",&N);
		}
		
		printf("Please enter the boards Column Number min(5) max(10):");
		scanf(" %d",&M);
		
		while (M<5 || M>10){//e�er tan�mlad���m�z aral�kta de�ilse tekrar de�er al�yoruz
			printf("wrong");
			printf("\nPlease enter the boards Column Number min(5) max(10):");
			scanf(" %d",&N);
		}
		
		int board[N][M];//oyun tahtas�n� kullan�c�dan ald���m�z bilgilerle tan�mlad�k
		
		for (i=0;i<N;i++) {
        	for (j=0;j<M;j++)
			board[i][j]=0;//oyun tahtas�n� s�f�rlad�k
		}
		while(Y!='n'){//burada Y oyuncu oyunu kaybederse veya oyundayken ��kmak isterse while� k�r�p ana men�ye geri d�necek.
		
			RandNum=rand() % 7 + 1;// 7 par�am�z oldu�u i�in 7den 1e rastgele say� istiyoruz
			
			randomblock(piece,RandNum);//randomblock fonksiyonuyla rastgele par�am�z� elde ettik
			
			printboard(N,M,board,score);//board� ve score u kullan�c�ya g�sterdik
			
			printpiece(piece);//par�am�z� kullan�c�ya g�sterdik
			
			printf("\nDo you want to rotate the piece to the right? (y,n)\n");//kullan�c� par�ay� sa�a d�nd�rmek istiyormu diye sorduk
			scanf(" %c",&x);
			
			while ( x != 'y' && x != 'n' ){
				printf("\nYou can only answer with y (yes) or n (no)");
				printf("\nDo you want to rotate the piece to the right? (y,n)\n");//kullan�c� par�ay� sa�a d�nd�rmek istiyormu diye sorduk
				scanf(" %c",&x);
			}
			
			while (x!='n'){//e�er kullan�c� soruya no yani n ile cevap verirse par�a d�nd�r�lmeyecek
				rotatepiece(piece);//par�ay� sa�a d�nd�rd�k
				
				printpiece(piece);//par�ay� tekrar kullan�c�ya g�sterdik
				
				printf("\nDo you want to rotate the piece to the right again? (y,n)");//kullan�c�ya tekrar par�ay� sa�a d�nd�rmek istiyormu diye sorduk
				scanf(" %c",&x);
				while ( x != 'y' && x != 'n' ){
					printf("\nYou can only answer with y (yes) or n (no)");
					printf("\nDo you want to rotate the piece to the right? (y,n)\n");//kullan�c� par�ay� sa�a d�nd�rmek istiyormu diye sorduk
					scanf(" %c",&x);
				}		
			}//kullan�c�ya par�ay� sonsuz defa d�nd�rme hakk� verdik
			
			printboard(N,M,board,score);//board� ve score u kullan�c�ya g�sterdik
			
			printpiece(piece);//par�am�z� kullan�c�ya g�sterdik
			
			printf("\nPlease enter the x cordinate of the pieces lower left side:");//kullan�c�dan sol alt k��enin x kordinat�n� istedik
			scanf(" %d",&xcordinate);
			
			xcordinate--;// Bize 1 verilirse 0. s�tundan bahsediliyordur
			
			can=canplace(M,piece,xcordinate);//verilen x kordinat�n� boarda yerle�tirebiliyormuyuz diye kontrol ediyoruz
						
			while (can == 0){//e�er bu ko�ul sa�lan�rsa bize verilen x kordinat� boarda yerle�tirilmez
				printf("\nThe given x cordinate isn't valid\n");
				
				printpiece(piece);//par�ay� tekrar kullan�c�ya g�sterdik
				
				printf("\nPlease enter the x cordinate of the pieces lower left side:");//kullan�c�dan tekrar sol alt k��enin x kordinat�n� istedik
				scanf(" %d",&xcordinate);
				
				xcordinate--;// Bize 1 verilirse 0. s�tundan bahsediliyordur
					
				can=canplace(M,piece,xcordinate);//verilen x kordinat�n� boarda yerle�tirebiliyormuyuz diye kontrol ediyoruz
			}
			
			ycordinate=Ycordinate(N,M,board,piece,xcordinate);//Y kordinat�m�z� bulduk
			
			placepiece(N,M,board,piece,xcordinate,ycordinate);//par�am�z� boarda yerle�tirdik
			
			score = checklines(N,M,board,score);//burada sat�rlar� kontrol ediyoruz,dolu sat�rlar� yok edip puana ekliyoruz,puan� geri d�nd�r�yoruz
			
			score = checklines(N,M,board,score);//tekrar kontrol ediyoruz e�er sat�r� sildikten sonra bir dolu sat�r daha olu�ursa diye
			
			Gameover = gameover(N,M,board);//�st sat�rda bir varsa gameover de�erimiz 1 olur.
			
			printboard(N,M,board,score);//board� ve score u kullan�c�ya g�sterdik
			
			if(Gameover == 1){//e�er bu �art sa�lan�rsa kullan�c� oyunu kaybetmi� demektir
				printf("Game over!!!\n");
				printf("Your final score:%d\n",score);//kullan�c�ya son scoreunu g�sterdik
				Y='n';
				if (score > highscore){//e�er puan�m�z Highscore dan b�y�kse highscore olur
					highscore=score;
					printf("CONGRATS YOU HAVE BEATEN THE HIGHSCORE\n");//kullan�c�ya highscoreu ge�ti�ini s�yledik	
				}
				printf("Do you want to play again? (y,n):");//kullan�c�ya tekrar oynamak istiyor mu diye sorduk
				scanf(" %c",&X);
				while ( X != 'y' && X != 'n' ){
					printf("\nYou can only answer with y (yes) or n (no)");
					printf("\nDo you want to rotate the piece to the right? (y,n)\n");//kullan�c� par�ay� sa�a d�nd�rmek istiyormu diye sorduk
					scanf(" %c",&X);
				}
			}
			else if(Gameover == 0) {//e�er bu �art sa�lan�rsa kullan�c� oyuna devam edebilir
				printf("\nDo you want to continue this game? (y,n):");//kullan�c�ya oyuna devam etmek istiyormu diye sorduk
				scanf(" %c",&Y);
				while ( Y != 'y' && Y != 'n' ){
					printf("\nYou can only answer with y (yes) or n (no)");
					printf("\nDo you want to rotate the piece to the right? (y,n)\n");//kullan�c� par�ay� sa�a d�nd�rmek istiyormu diye sorduk
					scanf(" %c",&Y);
				}
				if(Y == 'n') {
					printf("\nDo you want to play again? (y,n):");//kullan�c�ya tekrar oynamak istiyor mu diye sorduk
					scanf(" %c",&X);
					while ( X != 'y' && X != 'n' ){
						printf("\nYou can only answer with y (yes) or n (no)");
						printf("\nDo you want to rotate the piece to the right? (y,n)\n");//kullan�c� par�ay� sa�a d�nd�rmek istiyormu diye sorduk
						scanf(" %c",&X);
					}
				}
			}	
		}	
	}
	return 0;
}
