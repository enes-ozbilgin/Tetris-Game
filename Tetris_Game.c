#include <stdio.h>
#include <stdlib.h>//rand() fonksiyonunu kullanmak için bu kütüphaneyi ekledim
#include <time.h>//program zamaný kullanarak bize rastgele bir sayý vereceði için bu kütüphaneyi ekledim


void randomblock(int matrix[3][3],int num){//kolaylýk olsun diye rastgele block fonksiyonu tanýmladýk
	int i,j;
	int pieces[7][3][3] = {//parçalarýmýzdan oluþan bir küp tanýmladýk if else zincirinden kurtulmak için
        {{1,0,0},
         {1,0,0},
         {1,1,0}},// L parçasý

        {{0,0,0},
         {0,0,0},
         {1,1,1}},// - parçasý

        {{0,0,0},
         {1,1,0},
         {1,1,0}},// [] parçasý

        {{0,0,0},
         {1,1,0},
         {0,1,1}},// Z parçasý

        {{0,1,0},
         {0,1,0},
         {1,1,0}},// ters L parçasý

        {{0,0,0},
         {0,0,0},
         {1,0,0}},// . parçasý

        {{0,0,0},
         {1,1,1},
         {0,1,0}}//  T parçasý 
    };
    for (i=0;i<3;i++) {
        for (j=0;j<3;j++) {
            matrix[i][j] = pieces[num-1][i][j];//piece matriximize num sayýsýna denk gelen parçayý atadýk
        }
    }
}

void printpiece(int matrix[3][3]){//parçayý ekrana yazdýracak fonksiyon tanýmladýk
	int i,j;
	printf("\nCurrent Piece: \n");
	for (i=0;i<3;i++) {
        for (j=0;j<3;j++) {
            if (matrix[i][j]==0)//matrixin elemaný 0 ise boþluk, 1 ise 1 yazdýracak
                printf("0 ");
            else
                printf("1 ");
        }
        printf("\n");
    }
    printf("^-----\n");
}

void printboard(int N,int M,int board[N][M],int score){//boardý ekrana yazdýracak fonksiyon tanýmladýk
	int i,j;
	printf("\nCurrent score: %d\n",score);//þuanki scoreumuzu gösterdik
    for (i=0;i<N;i++) {
        for (j=0;j<M;j++) {
            if (board[i][j] == 0)//eðer board 0 sa 0, 1 se 1 yazdýrdýk
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

void rotatepiece(int matrix[3][3]){//parçamýzý döndürecek fonksiyon tanýmladýk
	int matrix2[3][3];//geçici olarak parçamýzýn deðerlerini saklayacak matrix tanýmladýk
	int i,j;
	for (i=0;i<3;i++) {
        for (j=0;j<3;j++) 
        matrix2[i][j]=matrix[i][j];//parçamýzý geçici matrixe kopyaladýk
	}
	for (i=0;i<3;i++) {
        for (j=0;j<3;j++) 
        matrix[i][j]=matrix2[2-j][i];//matrixi saat yönünde döndürmek için bu iþlemi kullandýk
	}
}

int Ycordinate(int N,int M,int board[N][M],int piece[3][3],int Xc){//Y kordinatýmýzý bulacak fonksiyon tanýmladýk
	int y[3],i,j,x=2,Yc[3],k=0,z=3,X[3],Y=-1;
	
	for (i=0;i<3 && Y==-1;i++) {//bloðumuz havada mý diye kontrol ediyoruz
    	for (j=0;j<3;j++) {
        	if (piece[x - i][j] == 1) {
            	Y = i;//bloðun kaç blok havada olduðunu bulduk
            	j=4;//satýrý bulduktan sonra döngülerden çýkýyoruz
        	}
    	}
	}
	i=2;
	j=0;
	while( j < 3 ) {//ilk olarak parçamýzýn sütünlarýnýn y kordinatlarýný bulduk
		i=2;
		while( i >= 0 && piece[i][j] != 1 ){
			i--;
		}
		if( i >= 0 ){
			y[k] = i;//bulduðumuz parçaya ait y kordinatlarýný arrayde sakladýk
			k++;
		}
		else {
			y[k] = -N;//eðer sütün boþsa -N deðeri verdik
			k++;
		}
		j++;
	}//parçamýzýn y kordinatlarýný arrayde sakladýk
	i=0;
	j=0;
	k=0;
	while ( j < 3 ) {//þimdide boardumuzun sütünlarýnýn y kordinatlarýný buluyoruz
		i=0;
		while ( i < N && board[i][Xc+j] != 1 ){
			i++;
		}
		if( i < N ){
			Yc[k] = -i+1;//bulduðumuz y kordinatýný arrayde sakladýk
			k++;
		}
		else{
			Yc[k] = -N+1;//eðer sütun boþsa N-1 satýrdan basýlýr
			k++;
			z--;
		}
		j++;
	}//þimdide boardumuzun y kordinatlarýný bulduk
	for (i=0;i<3;i++){
		X[i]=0;
		X[i] += y[i] + Yc[i];//board ve parçanýn kordinatlarýný topluyoruz
	}
	if( z == 0 ){//eðer hiçbir sütunda 1 yoksa o zaman N-1 bizim Y kordinatýmýzdýr
		return N-1;
	}
	if ( X[0] >= X[1] && X[0] >= X[2] ){//en büyük deðer bizim gerçek Y kordinatýmýzdýr
		return -Yc[0] + 2 - y[0] - Y;
	}
	else if ( X[1] > X[0] && X[1] >= X[2] ){
		return -Yc[1] + 2 - y[1] - Y;
	}
	else if ( X[2] > X[1] && X[2] > X[0] ){
		return -Yc[2] + 2 - y[2] - Y;
	}
}

void placepiece(int N,int M,int board[N][M],int piece[3][3],int Xc,int Yc){//parçamýzý boarda koyacak bir fonksiyon tanýmladýk
	int i,j,x=2,y=-1;

	for (i=0;i<3 && y==-1;i++) {//bastýrmaya baþlýyacaðýmýz satýrý arýyoruz
    	for (j=0;j<3;j++) {
        	if (piece[x - i][j] == 1) {
            	y = x - i;//baþlama satýrýmýzý bulduk
            	j=4;//satýrý bulduktan sonra döngülerden çýkýyoruz
        	}
    	}
	}

	if (y!=-1) {//eðer bir baþlama satýrý bulduysak o satýrdan baþlayarak boarda yazýyoruz
    	for (i=0;i<3 && Yc - i>=0;i++) {
        	for (j=0;j<3;j++) {
            	if (piece[y - i][j] == 1) {//sadece 1 deðerlerimizi boarda bastýrýyoruz
                	board[Yc - i][Xc + j] = 1;//bu iþlemle baþlama satýrýndan baþlayýp deðerlerimizi boarda yazýyoruz
            	}
        	}
    	}
	}
}

int checklines(int N,int M,int board[N][M],int score){
	int i,j,x=1,y=0,k;
    for (i=N-1;i>=0;i--) {
        x=1;//x deðerimizi her satýr için tekrar 1 e eþitliyoruz
        for (j=0;j<M;j++) {
            x *= board[i][j];//eðer satýrýmýzda her sütün 1 se o zaman x deðeri 1 kalacak
        }
        if (x == 1) {//eðer satýrýmýz doluysa bu koþul saðlanacak
            for (j=0;j<M;j++) {
                board[i][j]= 0;//dolu satýrý sildik
            }
            score += M;//puanýmýzý sütün sayýsý miktarýnda artýrdýk
            
            for (k=i;k>0;k--) {//üste kalan 1 lerimizi aþaðý kaydýrmak için sildiðimiz satýrýn üstündeki satýrlar 1 aþaðý indirilir
                for (j=0;j<M;j++) {
                    board[k][j]= board[k - 1][j];//üst saýrdaki deðerleri alt satýra kopyaladýk
                }
            }
            for (j=0;j<M;j++) {//en üste kalan elemanlarý sildik
                board[1][j] = 0;
            }
        }
    }
    return score;
}

int gameover(int N,int M,int board[N][M]){//en üst satýrý kontrol eden fonksiyon tanýmladýk
    int i,j,y = 0;
    for (j = 0; j < M; j++) {//en üst satýrýmýzda 1 var mý diye kontrol ederiz
        y += board[0][j];
    }
	if( y == 0 ){
		return 0;//bir yoksa 0
	}
	else if( y > 0 ){
		return 1;// bir varsa 1 gönderdik
	}
}

int canplace(int M,int piece[3][3],int Xc){//eðer bize verilen x kordinatý boardýn dýþýndamý deðil diye bakan fonksiyon
	int i,j,y,x;
	for (i=2;i>=0;i--) {
    	for (j=0;j<3;j++) {//bastýrmaya baþlýyacaðýmýz sütunu arýyoruz
    		if(piece[j][i] == 1){
    			y=i+1;//bastýrmaya baþlýyacaðýmýz sütunu bulduk
				i=-1;//for koþullarýný break kullanmadan kýrmak için bunu kullanýyoruz
				j=4;//for koþullarýný break kullanmadan kýrmak için bunu kullanýyoruz	
			}
    	}
    }
    for (i=0;i<3;i++) {
    	for (j=0;j<3;j++) {//bastýrmaya baþlýyacaðýmýz sütunu arýyoruz
    		if(piece[j][i] == 1){
    			x=i+1;//bastýrmaya baþlýyacaðýmýz sütunu bulduk
				i=4;//for koþullarýný break kullanmadan kýrmak için bunu kullanýyoruz
				j=4;//for koþullarýný break kullanmadan kýrmak için bunu kullanýyoruz	
			}
    	}
    }
    if( Xc < 0 ) {
    	if ( Xc + x > 0 ){//bu koþul saðlanýrsa parçayý yerleþtirebiliyoruz
    		return 1;
		}
		else//bu koþul saðlanýrsa parçayý yerleþtiremiyoruz
		return 0;	
	}
	if( Xc + y > M ){//bu koþul saðlanýrsa parçayý yerleþtiremiyoruz
		return 0;
	}
	else if( Xc + y <= M ){//bu koþul saðlanýrsa parçayý yerleþtirebiliyoruz
		return 1;
	}
}

int main(){
	
	srand(time(0));//ayný sayýyý almamak için zamaný sýfýrladýk
	
	char X='a',Y='a',x='a';//karakter variablelarýmýzý tanýmladýk
	
	int xcordinate,ycordinate,N,M,RandNum,i,j,Gameover,can,highscore = 0,score = 0;//integer variablelarýmýzý tanýmladýk
	
	int piece[3][3]={0};//bu bizim rastgele blockumuz			  
				             			
	while (X!='n') {//While döngüsünde X ile koþul kurduk.Burada X, kullanýcý oyun bitiminde oyunu tekrar oynamak istemezse while'ý kýracak.
	
		Y='a';//tekrar oynanmak isterse Y'yi resetledik
		
		printf("\nWelcome to my Tetris game\n");//menümüz
		
		printf("\nCurrent Highscore:%d\n",highscore);//Highscore gösterdik

		printf("\nPlease enter the boards Row Number min(5) max(20):");
		scanf(" %d",&N);
		
		while (N<5 || N>20){//eðer tanýmladýðýmýz aralýkta deðilse tekrar deðer alýyoruz
			printf("wrong");
			printf("\nPlease enter the boards Row Number min(5) max(20):");
			scanf(" %d",&N);
		}
		
		printf("Please enter the boards Column Number min(5) max(10):");
		scanf(" %d",&M);
		
		while (M<5 || M>10){//eðer tanýmladýðýmýz aralýkta deðilse tekrar deðer alýyoruz
			printf("wrong");
			printf("\nPlease enter the boards Column Number min(5) max(10):");
			scanf(" %d",&N);
		}
		
		int board[N][M];//oyun tahtasýný kullanýcýdan aldýðýmýz bilgilerle tanýmladýk
		
		for (i=0;i<N;i++) {
        	for (j=0;j<M;j++)
			board[i][j]=0;//oyun tahtasýný sýfýrladýk
		}
		while(Y!='n'){//burada Y oyuncu oyunu kaybederse veya oyundayken çýkmak isterse whileý kýrýp ana menüye geri dönecek.
		
			RandNum=rand() % 7 + 1;// 7 parçamýz olduðu için 7den 1e rastgele sayý istiyoruz
			
			randomblock(piece,RandNum);//randomblock fonksiyonuyla rastgele parçamýzý elde ettik
			
			printboard(N,M,board,score);//boardý ve score u kullanýcýya gösterdik
			
			printpiece(piece);//parçamýzý kullanýcýya gösterdik
			
			printf("\nDo you want to rotate the piece to the right? (y,n)\n");//kullanýcý parçayý saða döndürmek istiyormu diye sorduk
			scanf(" %c",&x);
			
			while ( x != 'y' && x != 'n' ){
				printf("\nYou can only answer with y (yes) or n (no)");
				printf("\nDo you want to rotate the piece to the right? (y,n)\n");//kullanýcý parçayý saða döndürmek istiyormu diye sorduk
				scanf(" %c",&x);
			}
			
			while (x!='n'){//eðer kullanýcý soruya no yani n ile cevap verirse parça döndürülmeyecek
				rotatepiece(piece);//parçayý saða döndürdük
				
				printpiece(piece);//parçayý tekrar kullanýcýya gösterdik
				
				printf("\nDo you want to rotate the piece to the right again? (y,n)");//kullanýcýya tekrar parçayý saða döndürmek istiyormu diye sorduk
				scanf(" %c",&x);
				while ( x != 'y' && x != 'n' ){
					printf("\nYou can only answer with y (yes) or n (no)");
					printf("\nDo you want to rotate the piece to the right? (y,n)\n");//kullanýcý parçayý saða döndürmek istiyormu diye sorduk
					scanf(" %c",&x);
				}		
			}//kullanýcýya parçayý sonsuz defa döndürme hakký verdik
			
			printboard(N,M,board,score);//boardý ve score u kullanýcýya gösterdik
			
			printpiece(piece);//parçamýzý kullanýcýya gösterdik
			
			printf("\nPlease enter the x cordinate of the pieces lower left side:");//kullanýcýdan sol alt köþenin x kordinatýný istedik
			scanf(" %d",&xcordinate);
			
			xcordinate--;// Bize 1 verilirse 0. sütundan bahsediliyordur
			
			can=canplace(M,piece,xcordinate);//verilen x kordinatýný boarda yerleþtirebiliyormuyuz diye kontrol ediyoruz
						
			while (can == 0){//eðer bu koþul saðlanýrsa bize verilen x kordinatý boarda yerleþtirilmez
				printf("\nThe given x cordinate isn't valid\n");
				
				printpiece(piece);//parçayý tekrar kullanýcýya gösterdik
				
				printf("\nPlease enter the x cordinate of the pieces lower left side:");//kullanýcýdan tekrar sol alt köþenin x kordinatýný istedik
				scanf(" %d",&xcordinate);
				
				xcordinate--;// Bize 1 verilirse 0. sütundan bahsediliyordur
					
				can=canplace(M,piece,xcordinate);//verilen x kordinatýný boarda yerleþtirebiliyormuyuz diye kontrol ediyoruz
			}
			
			ycordinate=Ycordinate(N,M,board,piece,xcordinate);//Y kordinatýmýzý bulduk
			
			placepiece(N,M,board,piece,xcordinate,ycordinate);//parçamýzý boarda yerleþtirdik
			
			score = checklines(N,M,board,score);//burada satýrlarý kontrol ediyoruz,dolu satýrlarý yok edip puana ekliyoruz,puaný geri döndürüyoruz
			
			score = checklines(N,M,board,score);//tekrar kontrol ediyoruz eðer satýrý sildikten sonra bir dolu satýr daha oluþursa diye
			
			Gameover = gameover(N,M,board);//üst satýrda bir varsa gameover deðerimiz 1 olur.
			
			printboard(N,M,board,score);//boardý ve score u kullanýcýya gösterdik
			
			if(Gameover == 1){//eðer bu þart saðlanýrsa kullanýcý oyunu kaybetmiþ demektir
				printf("Game over!!!\n");
				printf("Your final score:%d\n",score);//kullanýcýya son scoreunu gösterdik
				Y='n';
				if (score > highscore){//eðer puanýmýz Highscore dan büyükse highscore olur
					highscore=score;
					printf("CONGRATS YOU HAVE BEATEN THE HIGHSCORE\n");//kullanýcýya highscoreu geçtiðini söyledik	
				}
				printf("Do you want to play again? (y,n):");//kullanýcýya tekrar oynamak istiyor mu diye sorduk
				scanf(" %c",&X);
				while ( X != 'y' && X != 'n' ){
					printf("\nYou can only answer with y (yes) or n (no)");
					printf("\nDo you want to rotate the piece to the right? (y,n)\n");//kullanýcý parçayý saða döndürmek istiyormu diye sorduk
					scanf(" %c",&X);
				}
			}
			else if(Gameover == 0) {//eðer bu þart saðlanýrsa kullanýcý oyuna devam edebilir
				printf("\nDo you want to continue this game? (y,n):");//kullanýcýya oyuna devam etmek istiyormu diye sorduk
				scanf(" %c",&Y);
				while ( Y != 'y' && Y != 'n' ){
					printf("\nYou can only answer with y (yes) or n (no)");
					printf("\nDo you want to rotate the piece to the right? (y,n)\n");//kullanýcý parçayý saða döndürmek istiyormu diye sorduk
					scanf(" %c",&Y);
				}
				if(Y == 'n') {
					printf("\nDo you want to play again? (y,n):");//kullanýcýya tekrar oynamak istiyor mu diye sorduk
					scanf(" %c",&X);
					while ( X != 'y' && X != 'n' ){
						printf("\nYou can only answer with y (yes) or n (no)");
						printf("\nDo you want to rotate the piece to the right? (y,n)\n");//kullanýcý parçayý saða döndürmek istiyormu diye sorduk
						scanf(" %c",&X);
					}
				}
			}	
		}	
	}
	return 0;
}
