一. 文件与流
1.1 文件
⛱什么是文件？
文件是当今计算机系统不可或缺的部分。文件用于储存程序、文档、数据、书信、表格、图形、照片、视频和许多其他种类的信息。作为程序员， 必须会编写创建文件和从文件读写数据的程序。

文件（file）通常是在磁盘或固态硬盘上的一段已命名的存储区。对我们而言，stdio.h就是一个文件的名称，该文件中包含一些有用的信息。然而，对操作系统而言，文件更复杂一些。例如，大型文件会被分开储存，或者包含一些额外的数据，方便操作系统确定文件的种类。然而，这都是操作系统所关心的，程序员关心的是C程序如何处理文件（除非你正在编写操作系统）。

程序文件：包括源程序文件（后缀为.c）,目标文件（windows环境后缀为.obj）,可执行程序（windows环境 后缀为.exe）。

数据文件：文件的内容不一定是程序，而是程序运行时读写的数据，比如程序运行需要从中读取数据的文件， 或者输出内容的文件。

文件名：一个文件要有一个唯一的文件标识，以便用户识别和引用。 文件名包含3部分：文件路径+文件名主干+文件后缀例如： c:\code\test.txt为了方便起见，文件标识常被称为文件名。

⛱文本文件与二进制文件
在C语言中，<stdio.h>支持两种类型的文件∶文本文件和二进制文件。首先，要区分文本内容和二进制内容、文本文件格式和二进制文件格式，以及文件的文本模式和二进制模式。所有文件的内容都以二进制形式（0或1）储存。但是，如果文件最初使用二进制编码的字符（例如， ASCII或Unicode）表示文本（就像C字符串那样），该文件就是文本文件，其中包含文本内容。如果文件中的二进制值代表机器语言代码或数值数据（使用相同的内部表示，假设，用于long或 double类型的值）或图片或音乐编码，该文件就是二进制文件，其中包含二进制内容。

为了规范文本文件的处理，C 提供两种访问文件的途径：二进制模式和文本模式。 在二进制模式中，程序可以访问文件的每个字节。而在文本模式中，程序所见的内容和文件的实际内容不同。程序以文本模式读取文件时， 把本地环境表示的行末尾或文件结尾映射为C模式。例如，C程序在旧式 Macintosh中以文本模式读取文件时，把文件中的\r转换成\n；以文本模式写 入文件时，把\n转换成\r。或者，C文本模式程序在MS-DOS平台读取文件 时，把\r\n转换成\n；写入文件时，把\n转换成\r\n。在其他环境中编写的文本 模式程序也会做类似的转换。

除了以文本模式读写文本文件，还能以二进制模式读写文本文件。如果读写一个旧式MS-DOS文本文件，程序会看到文件中的\r 和\n 字符，不会发生映射。如果要编写旧式 Mac格式、MS-DOS格式或UNIX/Linux格式的文件模式程序，应该使用二进制模式，这样程序才能 确定实际的文件内容并执行相应的动作。



文本文件具有两种二进制文件没有的特性。

文本文件分为若干行。文本文件的每一行通常以一两个特殊字符结尾，特殊字符的
选择与操作系统有关。在Windows中，行末的标记是回车符（’\x0d’）与一个紧跟其后的回行符（’\x0a’）。在UNIX和Macintosh操作系统（Mac OS）的较新版本中，行末的标记是一个单独的回行符。旧版本的Mac OS使用一个单独的回车符。
文本文件可以包含一个特殊的"文件末尾"标记。一些操作系统允许在文本文件的末尾
使用一个特殊的字节作为标记。在Windows中，标记为’\xla’（Ctrl+Z）。Ctrl+Z不是必需的，但如果存在，它就标志着文件的结束，其后的所有字节都会被忽略。使用Ctrl+Z 的这一习惯继承自DOS，而DOS中的这一习惯又是从CP/M（早期用于个人电脑的一种操作系统）来的。大多数其他操作系统（包括UNIX）没有专门的文件末尾字符。
二进制文件不分行，也没有行末标记和文件末尾标记，所有字节都是平等对待的。
向文件写入数据时，我们需要考虑是按文本格式存储还是按二进制格式进行存储。为了搞清楚其中的差别，考虑在文件中存储数32 767的情况。一种选择是以文本的形式把该数按字符3、2、7、6、7写入。假设字符集为ASCII，那么就可以得到下列5个字节∶



另一种选择是以二进制的形式存储此数(short类型)，这种方法只会占用两个字节∶



编写用来读写文件的程序时，需要考虑该文件是文本文件还是二进制文件。在屏幕上显示文件内容的程序可能要把文件视为文本文件。但是，文件复制程序就不能认为要复制的文件为文本文件。如果那样做，就不能完全复制含有文件末尾字符的二进制文件了。在无法确定文件是文本形式还是二进制形式时，安全的做法是把文件假定为二进制文件。

1.2 C语言中的流
⛱什么是流？
在C语言中，术语流（stream）表示任意输入的源或任意输出的目的地。许多小型程序都是通过一个流（通常和键盘相关）获得全部的输入，并且通过另一个流（通常和屏幕相关）写出全部的输出。
较大规模的程序可能会需要额外的流。这些流常常表示存储在不同介质（如硬盘驱动器、CD、DVD和闪存）上的文件，但也很容易和不存储文件的设备（网络端口、打印机等）相关联。这里将集中讨论文件，因为它们常见且容易理解。但是，请千万记住一点，<stdio.h>中的许多函数可以处理各种形式的流，而不仅仅可以处理表示文件的流。

程序的处理结果或计算结果会随着程序运行结束而消失。因此要将程序运行结束后仍需保存的数值和字符串等数据保存在文件（file）中。
针对文件、键盘、显示器、打印机等外部设备的数据读写操作都是通过流（stream进行的。我们可以将流想象成流淌着字符的河。)
由此可见，在前面的学习中所有用到 printf函数或 scanf函数的程序都使用了流。

⛱标准流
我们之所以能够如此简单方便地执行使用了流的输入输出操作，是因为C语言程序在启动时已经将标准（standard stream）准备好了。
标准流有以下三种。

■ stdin —— 标准输入流（standard input stream）
用于读取普通输入的流。在大多数环境中为从键盘输入。scanf与getchar等函数会从这个流中读取字符。

■stdout —— 标准输出流（standard output stream）
用于写入普通输出的流。在大多数环境中为输出至显示器界面。printf、puts 与putchar 等函数会向这个流写入字符。


■stderr —— 标准错误流（standard error stream）
用于写出错误的流。在大多数环境中为输出至显示器界面。

⛱文件指针
每个被使用的文件都在内存中开辟了一个相应的文件信息区，用来存放文件的相关信息（如文件的名 字，文件状态及文件当前的位置等）。这些信息是保存在一个结构体变量中的。该结构体类型是有系统 声明的，取名FILE.

表示标准流的 stdin、stdout、stderr都是指向 FILE型的指针型。FILE 型是在<stdio.h>头文件中定义的，该数据类型用于记录控制流所需要的信息，其中包含以下数据。

文件位置指示符（file position indicator），记录当前访问地址。
错误指示符（error indicator），记录是否发生了读取错误或写入错误。
文件结束指示符（end-of-file indicator）记录是否已到达文件末尾。

通过流进行的输入输出都是根据上述信息执行操作的。而且这些信息也会随着操作结果更新。FILE 型的具体实现方法因编译器而异，一般多以结构体的形式实现。

不同的C编译器的FILE类型包含的内容不完全相同，但是大同小异。每当打开一个文件的时候，系统会根据文件的情况自动创建一个FILE结构的变量，并填充其中的信息， 使用者不必关心细节。一般都是通过一个FILE的指针来维护这个FILE结构的变量，这样使用起来更加方便。 下面我们可以创建一个FILE的指针变量:

FILE* pf;//文件指针变量
1
定义pf是一个指向FILE类型数据的指针变量。可以使pf指向某个文件的文件信息区（是一个结构体变 量）。通过该文件信息区中的信息就能够访问该文件。也就是说，通过文件指针变量能够找到与它关联 的文件。比如：



二. 文件打开与关闭及其读写操作
2.1 文件的打开与关闭
文件在读写之前应该先打开文件，在使用结束之后应该关闭文件。在编写程序的时候，在打开文件的同时，都会返回一个FILE*的指针变量指向该文件，也相当于建立了指针和文件的关系。ANSIC 规定使用fopen函数来打开文件，fclose来关闭文件。

⛱文件操作模式
文件使用方式	含义	如果指定文件不存在
“r”（只读）	为了输入数据，打开一个已经存在的文本文件	出错
“w”（只写）	为了输出数据，打开一个文本文件	建立一个新的文件
“a”（追加）	向文本文件尾添加数据	建立一个新的文件
“rb”（只读）	为了输入数据，打开一个二进制文件	出错
“wb”（只写）	为了输出数据，打开一个二进制文件	建立一个新的文件
“ab”（追加）	向一个二进制文件尾添加数据	出错
“r+”（读写）	为了读和写，打开一个文本文件	出错
“w+”（读写）	为了读和写，建议一个新的文件	建立一个新的文件
“a+”（读写）	打开一个文件，在文件尾进行读写	建立一个新的文件
“rb+”（读写）	为了读和写打开一个二进制文件	出错
“wb+”（读写）	为了读和写，新建一个新的二进制文件	建立一个新的文件
“ab+”（读写）	打开一个二进制文件，在文件尾进行读和写	建立一个新的文件


打开文件时可以指定以下四种模式：

只读模式 —— 只从文件输入。
只写模式 —— 只向文件输出。
更新模式 —— 既从文件输入，也向文件输出。
追加模式 —— 从文件末尾处开始向文件输出。
⛱打开文件
文件的打开是使用fopen函数，打开后务必记得关闭！

FILE *fopen( const char *filename, const char *mode );
1
名称	详情
头文件	stdio.h
参数 const char *filename	文件名（或文件路径）
参数 const char *mode	文件模式（以字符串形式输入）
返回值	FILE *型的指针（返回NULL表示打开失败）
作用	打开文件（文本或二进制文件）
⛱关闭文件
int fclose( FILE *stream );
1
名称	详情
头文件	stdio.h
参数 FILE *stream	需要关闭的文件指针
返回值	整型（表示关闭流或文件指针总数，返回EOF表示文件关闭失败）
作用	关闭文件（文本或二进制文件）
示例

#include <stdio.h>
int main()
{
	//打开文件，以w+模式为例，若没指定路径，默认跟随该.c文件
	FILE* pf = fopen("abc.txt", "w+");//read and write
	if (pf == NULL)
	{
		perror("file open");
		return -1;
	}

	//文件操作（读文件，写文件）

	//代码

	//关闭文件
	fclose(pf);
	pf=NULL;

	return 0;
}

2.2 文件的读写
功能	函数名	适用于
字符输入函数	fgetc	所有输入流
字符输出函数	fputc	所有输出流
文本行输入函数	fgets	所有输入流
文本行输出函数	fputs	所有输出流
格式化输入函数	fscanf	所有输入流
格式化输出函数	fprintf	所有输出流
二进制输入	fread	文件
二进制输出	fwrite	文件
getchar只针对标准输入流stdin。即使对stdin重定向，getchar针对的也只是stdin。

■ stdin —— 标准输入流（standard input stream）
用于读取普通输入的流。在大多数环境中为从键盘输入。scanf与getchar等函数会从这个流中读取字符。

■stdout —— 标准输出流（standard output stream）
用于写入普通输出的流。在大多数环境中为输出至显示器界面。printf、puts 与putchar 等函数会向这个流写入字符。


■stderr —— 标准错误流（standard error stream）
用于写出错误的流。在大多数环境中为输出至显示器界面。

⛱文本文件字符输入输出（fgetc、fputc）
文本文件字符输入函数，用法与函数getchar基本一样。

//Read a character from a stream (fgetc, fgetwc) or stdin (_fgetchar, _fgetwchar).
int fgetc( FILE *stream );

名称	详情
fgetc	读取一个数据，读一次后保存下一个数据的位置，下次读取从保存的位置开始。
头文件	stdio.h
参数 FILE *stream	输入流（从流中读取数据输入，传文件指针读取文件，传stdin读取键盘等）
返回值	整型（表示输入字符ASCII码，返回EOF表示输入失败）
文本文件字符输出函数，用法与函数putchar基本一样。

//Writes a character to a stream (fputc, fputwc) or to stdout (_fputchar, _fputwchar).
int fputc( int c, FILE *stream );

名称	详情
fputc	输出(写入)一个数据
头文件	stdio.h
参数int c	待写入流字符，要写入的数据
参数 FILE *stream	输出流（将字符写入目标流，如传文件指针输出至文件，传stdout输出至屏幕等）
返回值	整型（表示输出字符ASCII码，返回EOF表示输出失败）
从文件输入输出一个字符a程序：

int main()
{
	//打开文件，以w+模式为例，若没指定路径，默认跟随该.c文件
	FILE* pf = fopen("abc.txt", "w+");//read and write
	if (pf == NULL)
	{
		perror("file open");
		return -1;
	}

	//文件操作（读文件，写文件）
	//输出字符
	fputc('a', pf);
	//将文件指针重新定位到文件的开头
	rewind(pf);
	//输入字符
	char ch = 0;
	ch = fgetc(pf);
	printf("%c ", ch);

	//关闭文件
	fclose(pf);
	//代码
	return 0;
}
运行结果：

a
C:\Users\HP\Desktop\gitee\test\world\test\x64\Debug\test.exe (进程 17240)已退出，代码为 0。
按任意键关闭此窗口. . .
文件中的数据：


⛱文本文件字符串行输入输出（fgets、fputs）
文件输入字符串函数，作用与gets基本一致。

//Get a string from a stream.
char *fgets( char *string, int n, FILE *stream );

名称	详情
fgets	输入一个字符，输入目标字符数组后，会在最后一个字符后面自动加上\0
头文件	stdio.h
参数char *string	输入的目的地址（字符指针）
参数int n	从流中读取字符后加上\0后字符串字符数数量（包括\0）
参数 FILE *stream	输入流（起源地）（从流中读取数据输入，传文件指针读取文件，传stdin读取键盘等）
返回值	字符指针（表示输入目的地的地址），返回NULL表示输入失败
文件输入字符串函数，作用与puts基本一致。

Write a string to a stream.
int fputs( const char *string, FILE *stream );

名称	详情
fputs	输出一个字符串
头文件	stdio.h
参数const char *string	待写入流字符串的地址
参数 FILE *stream	输出流（将字符写入目标流，如传文件指针输出至文件，传stdout输出至屏幕等）
返回值	整型（返回EOF表示输出失败）
在空文件abc.txt中写入字符串str1:zaoqideyang，并从文件中将该字符串输入至str2。

int main()
{
	//打开文件，以w+模式为例，若没指定路径，默认跟随该.c文件
	FILE* pf = fopen("abc.txt", "w+");//read and write
	if (pf == NULL)
	{
		perror("file open");
		return -1;
	}

	//文件操作（读文件，写文件）
	char* str1 = "zaoqideyang";
	//输出字符串
	
	if (fputs(str1, pf) == EOF)
	{
		perror("fputs");
		return -2;
	}
	//将文件指针重新定位到文件的开头
	rewind(pf);
	//输入字符串
	char str2[20] = { 0 };
	if (fgets(str2, 20, pf) == NULL)
	{
		perror("fgets");
		return -2;
	}
	printf("%s ", str2);

	//关闭文件
	fclose(pf);
	//代码
	return 0;
}
输出结果：


zaoqideyang
C:\Users\HP\Desktop\gitee\test\world\test\x64\Debug\test.exe (进程 8208)已退出，代码为 0。
按任意键关闭此窗口. . .

⛱文本文件格式化输入输出（fscanf、fprintf）
所谓文本文件格式化输入输出，其实就是把原来输入源为键盘改为文件，输出源为屏幕改为文件。那理所当然就比原来的printf和scanf函数多了一个文件指针的参数，格式化的字符串参数是一样的。

Read formatted data from a stream.
int fscanf( FILE *stream, const char *format [, argument ]... );
Read formatted data from the standard input stream.
int scanf( const char *format [,argument]... );
Print formatted data to a stream.
int fprintf( FILE *stream, const char *format [, argument ]...);
Print formatted output to the standard output stream.
int printf( const char *format [, argument]... );


fprintf，第一个参数是文件指针，后面的参数与printf打印一样，只不过这个不是打印在屏幕上而是打印到文件里。

fscanf，第一个参数是文件指针，后面的参数与scanf写入一样，只不过这个不是自己输入数据，是用文件里面的数据当作我们输入的数据写进变量里面。

struct s
{
	int i;
	char c[20];
	double d;
};

int main()
{
	struct s s1 = { 2, "zhangsan", 5.5f };
	//打开文件，以w+模式为例，若没指定路径，默认跟随该.c文件
	FILE* pf = fopen("text.txt", "w+");//read and write
	if (pf == NULL)
	{
		perror("file open");
		return -1;
	}

	//文件操作（读文件，写文件）
	//格式化输出，将数据写到文件里
	if (fprintf(pf, "%d %s %.2lf", s1.i, s1.c, s1.d) == EOF)
	{
		perror("fputs");
		return -2;
	}
	//将文件指针重新定位到文件的开头
	rewind(pf);
	//格式化输入
	struct s s2 = { 0 };
	if (fscanf(pf, "%d %s %lf", &(s2.i), &(s2.c), &(s2.d)) == EOF)
	{
		perror("fgets");
		return -2;
	}
	printf("%d %s %.2lf ", s2.i, s2.c, s2.d);

	//关闭文件
	fclose(pf);

	return 0;
}

运行结果：


2 zhangsan 5.50
C:\Users\HP\Desktop\gitee\test\world\test\x64\Debug\test.exe (进程 12016)已退出，代码为 0。
按任意键关闭此窗口. . .

⛱二进制文件输入输出（fread、fwrite）
Reads data from a stream.
size_t fread( void *buffer, size_t size, size_t count, FILE *stream );

名称	详情
fread	二进制读取文件函数
头文件	stdio.h
参数void *buffer	目标地址
参数 size_t size	单个元素字节数
参数size_t count	读取元素个数
返回值	无符号整型（返回实际读取的完整项目数，如果发生错误或在达到计数之前遇到文件结尾，则该值可能小于计数。）
作用	读取文件
int main()
{
    struct S s = {"zhangsan", 20, 50.5f};
    //以二进制的形式写到文件中
    FILE* pf = fopen("text.txt","wb");
    if(pf == NULL)
    {
        perror("fopen");
        return 1;
    }
    //二进制的方式写
    fwrite(&s, sizeof(struct S), 1, pf);
    
    fclose(pf);
    pf = NULL;
    return 0;
}



在文件中储存的是二进制信息，虽然我们读不懂，但是计算机能够读懂它。

Writes data to a stream.
size_t fwrite( const void *buffer, size_t size, size_t count, FILE *stream );
1
2
名称	详情
fwrite	二进制写入文件函数
头文件	stdio.h
参数const void *buffer	原数据地址
参数 size_t size	单个元素字节数
参数size_t count	写入元素个数
返回值	无符号整型（返回实际写入的完整项的数量，如果发生错误，该数量可能小于count。）
作用	写入文件
int main()
{
    struct S s = { 0 };
    //以二进制的形式读取
    FILE* pf = fopen("text.txt","rb");
    if(pf == NULL)
    {
        perror("fopen");
        return 1;
    }
    //写入结构体
    fread(&s, sizeof(struct S), 1, pf);
    printf("%s %d %f\n", s.arr, s.age, s.score);
    
    fclose(pf);
    pf = NULL;
    return 0;
}



⛱sscanf、sprintf
sprintf把一个格式化的数据转换成字符串



sscanf从一个字符串中转换出一个格式化的数据。如果没有空格，读不出来三段的格式化



函数	作用
scanf	针对标准输入的格式化输入语句
printf	针对标准输出的格式化输出语句
fscanf	针对所有输入流的格式化输入语句
fprintf	针对所有输出流的格式化输出语句
sscanf	从一个字符串中转化成一个格式化的数据
sprintf	把一个格式化的数据转化成字符串
⛱文件随机访问相关函数（rewind、fseek、ftell）
首先就是前面栗子中已经使用过的函数rewind，该函数作用就是让“文件指针”指向文件开始的位置上。

Repositions the file pointer to the beginning of a file.
void rewind( FILE *stream );

因为上面栗子已经示范使用过，不再另举例子。

函数fseek，根据文件指针的位置和偏移量来定位文件指针。
函数ftell，返回文件指针相对于起始位置的偏移量。

Moves the file pointer to a specified location.
int fseek( FILE *stream, long offset, int origin );
Gets the current position of a file pointer.
long ftell( FILE *stream );

名称	详情
fseek	文件指针定位函数
头文件	stdio.h
参数FILE *stream	目标文件指针
参数 long offset	距离初始位置的偏移量
参数int origin	初始位置，有三个值可选，1.SEEK_CUR：文件当前位置；2.SEEK_END：文件末尾位置；3.SEEK_SET：文件开始位置
返回值	整型（返回0表示定位文件指针成功，否则失败）
作用	设置文件指针位置
模式	偏移量的起始位置
SEEK_SET	文件开头
SEEK_CUR	文件指针的当前位置
SEEK_END	文件结尾
fseek(fp, 0L, SEEK_SET); // 定位至文件开始处 
fseek(fp, 10L, SEEK_SET); // 定位至文件中的第10个字节 
fseek(fp, 2L, SEEK_CUR); // 从文件当前位置前移2个字节 
fseek(fp, 0L, SEEK_END); // 定位至文件结尾 
fseek(fp, -10L, SEEK_END); // 从文件结尾处回退10个字节



名称	详情
ftell	文件偏移量函数
头文件	stdio.h
参数FILE *stream	目标文件指针
返回值	长整型（返回距离文件开始位置的偏移量大小）
作用	计算距文件开始的偏移量
三. 文件结束判断与缓冲
3.1 文件读取结束判断
对于feof函数，用来判断是否位于文件末尾，参数为文件指针，如果不是文件末尾则返回0，否则返回非0值。

Tests for end-of-file on a stream.
int feof( FILE *stream );

该函数常常配合ferror函数来判断文件读取结束是因为文件读取完成而结束还是因为输入输出异常而导致文件读取结束，简单说就是判断文件读取结束是正常结束还是异常结束。
对于feeror函数，判断流上是否有错误，也就是判断读取过程中是否异常。如果正常返回0，否则返回非0值。

feof用来判断是不是读到文件末尾而结束；ferror判断文件是否是因为读取失败结束。

feof(fp)为真，说明读到文件末尾；ferroe(fp)为真，说明读取错误。

Tests for an error on a stream.
int ferror( FILE *stream );

⛱判断文本文件读取是否正常结束
#include <stdio.h>
#include <stdlib.h>
int main(void)
{
	int c; // 注意：int，非char，要求处理EOF
	FILE* fp = fopen("test.txt", "r");
	if (!fp)
    {
		perror("File opening failed");
		return EXIT_FAILURE;
	}
	//fgetc 当读取失败的时候或者遇到文件结束的时候，都会返回EOF
	while ((c = fgetc(fp)) != EOF) // 标准C I/O读取文件循环
	{
		putchar(c);
	}
	//判断是什么原因结束的
	if (ferror(fp))
		puts("I/O error when reading");
	else if (feof(fp))
		puts("End of file reached successfully");
	fclose(fp);
	return 0;
}

⛱判断二进制文件是否正常结束
通过判断fread返回值与预期读入元素个数是否相等来判断程序是否出现异常。

#include <stdio.h>
enum { SIZE = 5 };
int main(void) 
{
	double a[SIZE] = { 1.,2.,3.,4.,5. };
	FILE* fp = fopen("test.bin", "wb"); // 必须用二进制模式
	fwrite(a, sizeof * a, SIZE, fp); // 写 double 的数组
	fclose(fp);
	double b[SIZE];
	fp = fopen("test.bin", "rb");
	size_t ret_code = fread(b, sizeof * b, SIZE, fp); // 读 double 的数组
	if (ret_code == SIZE) 
    {
		puts("Array read successfully, contents: ");
		for (int n = 0; n < SIZE; ++n) printf("%f ", b[n]);
		putchar('\n');
	}
	else 
    { // error handling
		if (feof(fp))
			printf("Error reading test.bin: unexpected end of file\n");
		else if (ferror(fp)) 
        {
			perror("Error reading test.bin");
		}
	}
	fclose(fp);
	return 0;
}

3.2 文件缓冲区
ANSIC 标准采用“缓冲文件系统”处理的数据文件的，所谓缓冲文件系统是指系统自动地在内存中为程序中每一个正在使用的文件开辟一块“文件缓冲区”。从内存向磁盘输出数据会先送到内存中的缓冲区，装满缓冲区后才一起送到磁盘上。如果从磁盘向计算机读入数据，则从磁盘文件中读取数据输入到内存缓冲区（充满缓冲区），然后再从缓冲区逐个地将数据送到程序数据区（程序变量等）。缓冲区的大小根据C编译系统决定的。



#include <stdio.h>  
#include <windows.h>
//VS2013 WIN10环境测试 
int main()
{
    FILE*pf = fopen("test.txt", "w");  
    fputs("abcdef", pf);//先将代码放在输出缓冲区
    printf("睡眠10秒-已经写数据了，打开test.txt文件，发现文件没有内容\n");  
    Sleep(10000);
    printf(" 刷 新 缓 冲 区 \n");  
    fflush(pf);//刷新缓冲区时，才将输出缓冲区的数据写到文件（磁盘）
    //注：fflush 在高版本的VS上不能使用了
    printf("再睡眠10秒-此时，再次打开test.txt文件，文件有内容了\n");  
    Sleep(10000);
    fclose(pf);
    //注：fclose在关闭文件的时候，也会刷新缓冲区  
    pf = NULL;
    return 0;
}

系统先将数据写到缓冲区里，然后再从缓冲区里将数据移到文件中。缓冲区的意义是将写入的数据统一、一起写入文件中，避免频繁的调用操作系统将数据写到文件里，影响效率。

刷新缓冲区时，才会输出缓冲区的数据，写到文件。fflush和fclose都会刷新缓冲区。

因为有缓冲区的存在，C语言在操作文件的时候，需要做刷新缓冲区或者在文件操作结束的时候关闭文件。如果不做，可能导致读写文件的问题。
