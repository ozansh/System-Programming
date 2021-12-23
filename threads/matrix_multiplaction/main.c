#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <limits.h>
#include <time.h>

void fill_the_blanks(void);
void multiple_row_p(int rows);
void create_the_blanks(void);
void* multiple_thread( void );
void read_from_file(int row_f, int colmn_f,int fd,int matrix_d);
void print_matrix_p(void);

int row ,middle,colmn, line;
long int ** result;
int ** first_matrix; 
int ** second_matrix;
// column: 5 middle: 5 column: 7 
// ./a.out 5 5 7  dataset1.txt dataset2.txt
int main(int argc, char const *argv[])
{
    if (argc == 6)
    {
        clock_t main_clock = clock();
        /**
         * main_clock ile ana prosesin  ne kadar sürede bittiğini ölçtüm. Bunu proses sonundaki CPU saatinden 
         * başlangıcındaki CPU saatini çıkararak yapıyorum. Diğer tüm proseslerin  bitiş sürelerinin
         * hesaplanmasını aynı teknikle yaptım.
         */
        row = atoi(argv[1]);
        middle = atoi(argv[2]);
        colmn = atoi(argv[3]);
        create_the_blanks();
        // (row x middle) ve (middle x colmn) boyutlarındaki matrislerin boyutlarını global değişkenlere atadım
        srand(main_clock);
        pid_t process_read = fork();
        if (process_read < 0)
            exit(-1);
        pid_t process_nread = fork();
        if (process_nread < 0)
            exit(-1);
        else if ((process_nread == 0) && (process_read == 0))
            exit(-1);
        pid_t thread_read = fork();
        if (thread_read < 0 )
            exit(-1);
        else if ((process_read == 0) && (process_nread > 0) && (thread_read == 0))
            exit(0);
        else if ((process_nread == 0) && (process_read > 0) && (thread_read == 0))
            exit(0);
        pid_t thread_nread = fork();
        if (thread_nread < 0)
            exit(-1);
        else if ((process_read == 0) && (thread_nread == 0) && (process_nread > 0) && (thread_read > 0))
            exit(0);
        else if ((thread_nread == 0) && (process_nread == 0) && (process_read > 0) && (thread_read > 0))
            exit(0);
        else if ((thread_nread == 0) && (thread_read == 0) && (process_nread > 0) && (process_read > 0))    
            exit(0);    
        /**
         * Üstteki satırlarla 15 tane proses yaratıp 11 tanesini sildim.
         * Bu şekilde: Matrisleri dosyadan okuyup proses içinde çarpacak bir proses, threadlere bölüp çarpacak bir proses
         * dosyadan okumadan proses içinde çarpacak bir proses ve dosyadan okumadan threadlere bölüp çarpacak birer proses oluşturdum. 
         */

        if (process_read == 0)
        {// dosyadan okuyup proses içinde çarpacak proses
            clock_t process_read_c = clock();
            /**
             *  Bu proseste kullanıcıdan alınan dosyaları açıp (8,3) A ve B matrislerine bilgi aktardım (1, 4). ardından dosyaları kapattım (2,5). 
             * Ardından her satırı ayrı ayrı çarptım (6). Sonra da bastırdım (7)
             */
            int fd = open(argv[4], O_RDONLY);// 8
            if (fd == -1)
                exit(-1);
            read_from_file( row, middle, fd, 1);// 1
            if (close(fd) == -1)// 2
                exit(-1);
            fd = open (argv[5], O_RDONLY);// 3
            if (fd == -1)
                exit(-1);
            read_from_file( middle, colmn, fd, 2);// 4
            if (close(fd) == -1)// 5
                exit(-1);
            for (size_t i = 0; i < row; i++)
            {
                multiple_row_p(i);// 6
            }
            print_matrix_p();// 7

            printf("Dosyadan A ve B matrixlerini okuyarak proses ile çarpmak %ldms sürdü.\n", clock() - process_read_c);
        }
        else if (process_nread == 0)
        {// dosyadan okumadan proses içinde çarpacak proses
            clock_t process_nread_c = clock();
            /**
             *  Bu proseste kullanıcıdan alınan satır ve sütun değerlerine göre A ve B matrislerini rastgele sayılarla doldurdum (1, değerler fonksiyon dışından kontol ediliyor).
             *  Ardından her satırı ayrı ayrı çarptım (2). Sonra da bastırdım (3)
             */
            fill_the_blanks();// 1

            for (size_t i = 0; i < row; i++)
            {
                multiple_row_p(i); // 2
            }
            print_matrix_p(); // 3

            printf("Matrixleri proses içinde çarpmak %ldms sürdü.\n", clock() - process_nread_c);
        }
        else if (thread_read == 0)
        {// dosyadan okuyup threadler yardımıyla çarpacak proses   
            clock_t thread_read_c = clock();
            /**
             *  Bu proseste kullanıcıdan alınan dosyaları açıp (1,4) A ve B matrislerine bilgi aktardım (2, 5). ardından dosyaları kapattım (3,11). 
             *  threadlerin kimliklerinin tutulacağı diziyi oluşturdum (6). Ardından her satırı ayrı ayrı threadler ile çarptım (7). ardından tüm threadlerin işini bitirmesini 
             *  bekledim (8). Sonra da bastırdım (9). En son da  threadlerin bekleme süresini "Sleep(1)" hesapladım (10)
             */
            int fd = open(argv[4], O_RDONLY);// 1
            if (fd == -1)
                exit(-1);
            read_from_file( row, middle, fd, 1);// 2
            if (close(fd) == -1) // 3
                exit(-1);
            fd = open (argv[5], O_RDONLY);// 4
            if (fd == -1)
                exit(-1);
            read_from_file( middle, colmn, fd, 2);// 5
            if (close(fd) == -1)// 11
                exit(-1);
            pthread_t threads[row]; // 6
            
            for (size_t i = 0; i < row; i++)
            {
                line  = i;
                pthread_create(&threads[i], NULL, &multiple_thread, NULL);// 7
                sleep(1);
                pthread_join(threads[i], NULL);// 8
            }
            print_matrix_p();// 9

            long int sum_sleep = row * 100; // 10
            printf("Dosyadan A ve B matrixlerini okuyarak threadlerle çarpmak %ldms sürdü.\n", clock() - (thread_read_c  + sum_sleep));

        }
        else if (thread_nread == 0)
        {// dosyadan okumadan threadler yardımıyla çarpacak olan proses
            clock_t thread_nread_c = clock();
            /**
             *  Bu proseste kullanıcıdan alınan satır ve sütun değerlerine göre A ve B matrislerini rastgele sayılarla doldurdum (1, değerler fonksiyon dışından kontol ediliyor).
             *  threadlerin kimliklerinin tutulacağı diziyi oluşturdum (2). Ardından her satırı ayrı ayrı threadler ile çarptım (3). ardından her threadin işini bitirmesini 
             *  bekledim (4). Sonra da bastırdım (5). En son da  threadlerin bekleme süresini "Sleep(1)" hesapladım (6)
             */
            fill_the_blanks();// 1

            pthread_t threads[row]; // 2
            
            for (size_t i = 0; i < row; i++)
            {
                line  = i;
                pthread_create(&threads[i], NULL, &multiple_thread, NULL);// 3
                sleep(1);
                pthread_join(threads[i], NULL);// 4
            }
            print_matrix_p(); // 5
            long int sum_sleep = row * 100; // 6
            printf("Matrixleri threadler ile çarpmak %ldms  sürdü.\n", clock() - (thread_nread_c + sum_sleep));
        }
        else 
        {// ana proses
            /**
             *  Burası ana proses. Bu prosesi sadece global değişkenlerin atanması ve child prosesler için uygun ortamın ayarlanması için kullandım 
             */
            wait();
            wait();
            wait();
            wait();
                
        }
    }
    else{
        puts("Hatalı giriş yaptınız");
        puts("Matrix çarpımı: AxB = C A:nxm boyutlu, B: mxr boyutlu, C: nxr boyutlu\n");
        printf("Programın çalıştırılması: %s n m r <A'nın okunacağı dosya> <B'nin okunacağı dosya>\n",argv[0]);
    }
    return 0;
}
void create_the_blanks(void)
{
    /**
     *  bu fonksiyon, matrixleri program başında pointer olarak tanımladığım için matrix için gerekli
     *  hafızayı dinamik bir şekilde ayırmaya yarıyor.
     */
    first_matrix = malloc(sizeof(first_matrix) * row);
    for (size_t i = 0; i < row; i++)
    {
        first_matrix[i] = malloc(sizeof(int) * middle);
    }
    second_matrix = malloc(sizeof(second_matrix)* middle);
    for (size_t i = 0; i < middle; i++)
    {
        second_matrix[i] = malloc(sizeof(int) * colmn);
    }
    result = malloc(sizeof(result) * row);
    for (size_t i = 0; i < row; i++)
    {
        result[i] = malloc(sizeof(long int) * colmn);
    } 
}
void multiple_row_p(int rows)
{
    /**
     * Bu fonksiyon, proses içinde çarpma yapan prosesler için matrixlerin istenen satırını çarpmaya yarıyor.
     */
    for (size_t i = 0; i < colmn; i++)
    {
        result[rows][i]= 0;// gerekli alanın sıfırlanması
        for (size_t j = 0; j < middle; j++)
        {
            result[rows][i] += first_matrix[rows][j] * second_matrix[j][i];// işlenmesi
        }
    }
        
}
void* multiple_thread( void )
{
    /**
     * Bu fonksiyon threadli çarpma yapmak için var. multiple_row_p den farkı ise fonksiyon tanımlamasının 
     * threalere göre tasarlanmış olmasıdır. fonksiyonun tanımındaki geri dönüş tipinin void* olması ve satır
     * değerini global değişkenden alması gibi 
     */
    for (size_t i = 0; i < colmn; i++)
    {
        result[line][i]= 0;
        for (size_t j = 0; j < middle; j++)
        {
            result[line][i] += first_matrix[line][j] * second_matrix[j][i];
        }
    }
}
void fill_the_blanks(void)
{
    /**
     * Bu fonksiyon çarpılacak matrixlerin içini rastgele değerlerle doldurur
     */
    for (size_t i = 0; i < row; i++)
    {
        for (size_t j = 0; j < middle; j++)
        {
            first_matrix[i][j] = (int)rand() % 100;
        }
    }
    for (size_t i = 0; i < middle; i++)
    {
        for (size_t j = 0; j < colmn; j++)
        {
            second_matrix[i][j] = (int)rand() % 100;
        }
    }
}
void print_matrix_p(void)
{   
    /**
     * Bu fonksiyon çarpılan matrixleri ve sonuç matrixini ekrana yansıtır
     */
    puts("\t\t\t A Matrisi");
    for (size_t i = 0; i < row; i++)
    {
        for (size_t j = 0; j < middle; j++)
        {
            printf("%d\t",first_matrix[i][j]);
        }
        puts("\n");
    }
    puts("\n\t\t\t B Matrisi");
    for (size_t i = 0; i < middle; i++)
    {
        for (size_t j = 0; j < colmn; j++)
        {
            printf("%d\t",second_matrix[i][j]);
        }
        puts("\n");
    }
    puts("\n\t\t AxB = C Matrisi");
    for (size_t i = 0; i < row; i++)
    {
        for (size_t j = 0; j < colmn; j++)
        {
            printf("%ld\t",result[i][j]);
        }
        puts("\n");
    }
}
void read_from_file(int row_f, int colmn_f,int fd,int matrix_d)
{
    /**
    *  Bu fonksiyon, kendisine gönderilen satır ve sütun bilgisi, dosya, ve hangi matrise yazacağı bilgisini kullanarak
    *  dosyadaki verileri matrixe işler. (15,16) da yazmak istediğimiz matrixe göre fonksiyon ikiye ayrılır.
    *  Fakat iki tarafın tek farkı işlemlerin hangi değişkene yapıldığıdır. (1)de dosyadan okuduğum verilerin saklanacağı 
    * diziyi (2) de ise sayıları saklayacağım diziyi dinanmik bir şekilde oluşturdum. (3) de dosyadan okudum ve okunan
    * bit sayısını size değişkenine yazdım. (4) de algoritmamın dosyadaki son sayıyı da okuması için dizinin sonuna boşluk ekledim
    * (5) de en sona karakter katarının bittiğini belirten karakteri ekledim
    * (6)da matrix sınırlarını aşmamayı sağladım. (7) de, eğer bir satır sonu karakterine denk geldiysek bu matrixteki sonraki 
    * satıra geçmek olduğu için okunmuş olan sayıyı yazıp matrixte de sonraki satıra geçmeyi sağladım
    * (8) de sayıyı yazdım. (9) da bufferdaki sayıyı önceki satırda yazdığım için bufferı sıfırladım. (10,11) de diğer döngü
    * elemanlerını sıfırladım. (12) de, boşluk karakteri sayının bittiğini temsil ettiğinden bufferdaki sayıyı matrixe yazıp 
    * sonraki sütuna geçmesini sağladım. (13) de gelen sayıyı sayı bufferına yazdım. (14) de ise aynı işlemleri B matrixine uyguladım
    */
    if (matrix_d == 1)//15   
    {
        int size, row_d = 0, colmn_d = 0, digit =0, control =0;
        char * readed = (char*) malloc(sizeof(char) * 512);//1
        char * number = (char*) malloc(sizeof(char) * 10);//2
        size = read(fd, readed, 510);//3
        if (size == -1)
            exit(1);
        readed[size] = ' ';//4
        readed[size + 1] = '\0';//5

        for (size_t i = 0; i < size + 1; i++)
        {
            if (row_d > row_f || colmn_d > colmn_f)//6
                break;
            if (readed[i] == '\n')//7
            {
                first_matrix[row_d][colmn_d] = atoi(number);//8
                for (size_t j = 0; j < 10; j++)
                {
                    number[j] = ' ';//9
                }
                
                row_d++;
                colmn_d = 0;//10
                control = 0;//11
            }
            else if (readed[i] == ' ')//12
            {
                first_matrix[row_d][colmn_d] = atoi(number);
                for (size_t j = 0; j < 10; j++)
                {
                    number[j] = ' ';
                }
                control = 0;
                colmn_d++;
            }
            else
            {
                number[control] = readed[i];//13
                control ++;   
            }
        }
        
    }
    else if (matrix_d == 2)//14
    {
        int size, row_d = 0, colmn_d = 0, digit =0, control =0;
        char * readed = (char*) malloc(sizeof(char) * 512); 
        char * number = (char*) malloc(sizeof(char) * 10);
        size = read(fd, readed, 510);
        if (size == -1)
            exit(1);
        readed[size] = ' ';
        readed[size + 1] = '\0';

        for (size_t i = 0; i < size + 1; i++)
        {
            if (row_d > row_f || colmn_d > colmn_f)
                break;
            if (readed[i] == '\n')
            {
                second_matrix[row_d][colmn_d] = atoi(number);
                for (size_t j = 0; j < 10; j++)
                {
                    number[j] = ' ';
                }
                
                row_d++;
                colmn_d = 0;
                control = 0;
            }
            else if (readed[i] == ' ')
            {
                second_matrix[row_d][colmn_d] = atoi(number);
                for (size_t j = 0; j < 10; j++)
                {
                    number[j] = ' ';
                }
                control = 0;
                colmn_d++;
            }
            else
            {
                number[control] = readed[i];
                control ++;   
            }
        }
    }
}