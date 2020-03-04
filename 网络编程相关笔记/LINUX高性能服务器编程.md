# 目标

​	2.22看完，----》2.25看完

​	周六造轮子。----》无

# 第一篇 tcp/ip协议详解

## 第一章：

1数据链路层 常用的协议是

ARP 协议,RARP 协议。

2，网络层。

最主要的是IP协议，其中ICMP协议是IP协议的补充，检测网络l连接。

是逐跳转发。

3.传输层。

不关心如何到达，只关心通信两端。

![image-20200219050225762](C:\Users\fuckoff\AppData\Roaming\Typora\typora-user-images\image-20200219050225762.png)

TCP,UDP 外加一个SCTP协议

​			TCP 是基于数据流的协议。

​			UDP是基于数据报的协议。

4.应用层

​	telnet协议，OSPF协议，DNS协议

### 1.2封装

​	当程序调用到send 或者write的时候，TCP模块就会把数据复制到缓冲区，然后配置，

### 1.3 分用

​	等到数据到达接受方的时候，数据需要分用。

### 1.5 arp协议工作原理

​	主机向网络广播一个ARP 请求，里面有目标的**网络i地址**，被请求的机器回应ARP应答，其中有自己的**物理地址。**

具体细节没有涉及。

### 1.6 DNS工作原理。

​	这是应用层协议。

​	一般而言，我们是用域名来访问机器，而不是使用相对的IP地址进行访问。这个转换就是用到DNS

 host 指令 查看对应域名的IP地址

### 1.7 socket 和 TCP/IP 协议的关系/

socket 一般两个功能：

1.应用层到TCP/UDP内核发送缓冲区的相互复制。

2.修改TCP/IP的数据报报头。

## 第二章 IP协议

### 	2.1 IP服务

 提供无状态，无连接，不可靠的服务。

​	无状态：数据报是不能保证有序的情况，很有可能出现的数据是乱序，重复的。但是上层协议可以保证整理。

​	无连接：指的是IP通信双方之间不等待，没有TCP那种意义。每一次，每一个报都要有目的IP 地址和源地址。

​	不可靠：不要求重发，只是宣告失败。

### 	2.2 IPV4



![image-20200219053941231](C:\Users\fuckoff\AppData\Roaming\Typora\typora-user-images\image-20200219053941231.png)

最后的选项字段是可变长，最多40字节。总长最多60字节。

### 2.3 IP分片

![image-20200219054623365](C:\Users\fuckoff\AppData\Roaming\Typora\typora-user-images\image-20200219054623365.png)

分片顺序。

### 2.4 IP路由

​	ip路由机制，分为三步走

1.路由表和数据报的目标IP地址匹配吗

2.路由表和数据报目标IP地址是否同一个网络

3.选择默认路由项。

### 2.6 重定向

重定向不是什么高端单词。可以理解成是一个出错，或者改需求的一个过程

**就是一个改变路由的报文。**

## 第三章 TCP协议

​	**TCP 头部信息，字段。**

​	**TCP状态转移**

​	**TCP数据流。**

​	**TCP拥塞控制和超时重传。**

TCP 是基于数据流的形式，所以就会设立一个缓冲区，缓冲区满了再发送。

​	**两个缓冲区，一个是应用程序设定的缓冲区，一个是TCP自身的缓冲区**

​	相反，UDP 不同，每次进行写或者读，都会封装成一个数据报发送。

### 3.3 TCP 连接的建立和关闭

![image-20200219065703371](C:\Users\fuckoff\AppData\Roaming\Typora\typora-user-images\image-20200219065703371.png)

在管理关闭中，有个状态时半关闭状态。

应用程序怎么判断，read函数返回一个0.



### 3.4 状态转移

![image-20200219070545000](C:\Users\fuckoff\AppData\Roaming\Typora\typora-user-images\image-20200219070545000.png)

同样的图，

​	客户端的状态转移过程：

​	1/客户端通过 connect系统进行调用，根据返回进行判断。

​	在进入FIN_WAIT_2的时候，要等到服务器发送确认才进入TIME_WAIT,如果时间过长，就会在自动断掉，进入到孤儿进程类似的孤儿连接。

​	

![image-20200219071347012](C:\Users\fuckoff\AppData\Roaming\Typora\typora-user-images\image-20200219071347012.png)

注意这里，要两个都是ESTABLSHED 才允许相互通信。所以还是要确认接受方的确认。

​	TIME_WAIT 状态设计MSL

​	目的：1，可靠结束TCP连接

​				2，保证迟到的TCP报文有充足的时间被识别且丢弃。

### 3.5 半打开连接

​	相比于半关闭连接，它其实也是有点相似的。

复位报文段就可以解决，只要重启之后，客户端再从这个写数据，对方都回应一个复位报文段。

### 3.6 交互数据流

### 3.7 成块数据流

### 3.8 带外数据

带外数据比普通数据优先级更加高，可以用独立的运输层连接，也可以映射到普通数据连接中。

本身没有这样的定义，但是通过加入紧急指针的帮助，定义他的位置，但是它也是缓冲在普通缓冲区。

### 3.9超时重传

维护一个重传定时器，超时没收到确认就重传并重置时间。

和超时重连类似。每次失败增加一倍时间。

### 3.10 拥塞控制

慢启动，拥塞避免，快重传，快恢复。

拥塞控制的最终受控变量是发送端向网络一次连续写入的数据量，称为SWND(发送窗口)

其受接受窗口RWND 和拥塞窗口CWND控制，即

SWND = MIN( RWND  ,  CWND );

![image-20200219175602525](C:\Users\fuckoff\AppData\Roaming\Typora\typora-user-images\image-20200219175602525.png)

真延时才用的慢启动和拥塞避免，

在收到重复的（至少3个）确认报文段的时候，用的是快重传和快恢复。

在快重传和快恢复完成之后，拥塞控制恢复到拥塞避免状态中。

因为 CWND 的启动值就是 ssthresh

## 第四章 通信案例

应用层使用的是HTTP协议，其默认是使用TCP协议的。

### 4.2 代理服务器

​	分为正向代理服务器，反向代理服务器。

![image-20200219181209489](C:\Users\fuckoff\AppData\Roaming\Typora\typora-user-images\image-20200219181209489.png)

还有透明代理服务器，其是正向代理的一种情况。

### 4.3 访问DNS服务器

1. 代理服务器访问DNS服务器，通过UDP协议。

2. 代理服务器ARP请求，寻找mac地址。

3. 客户端和代理服务器HTTP通信。

   ![image-20200219182503714](C:\Users\fuckoff\AppData\Roaming\Typora\typora-user-images\image-20200219182503714.png)

ps / 局域网的主机可以通过用静态文件访问。不行再通过DNS服务器访问。

### 4.6 HTTP通信

   ​	短连接和长连接。

   因为HTTP协议是一种无状态协议，所以需要Cookie进行保证客户端的信息，不然区分不了客户。

   问题：无状态协议怎么用tcp通信的呢

   ![image-20200219184209990](C:\Users\fuckoff\AppData\Roaming\Typora\typora-user-images\image-20200219184209990.png)

   为什么要无状态

   因为连接太多，每一个都记住耗费太多资源。

   但是现在采用长连接，就是keep-alive。

   ![image-20200219184832419](C:\Users\fuckoff\AppData\Roaming\Typora\typora-user-images\image-20200219184832419.png)

   但是这个保证也不是很长的，还是会一段时间后就关闭。

# 第二篇 深入解析高性能服务器编程

## 	第五章	 linux 网络编程 基础API

### 5.1 socket 地址

   在unix 定义是

   ![image-20200219191154692](C:\Users\fuckoff\AppData\Roaming\Typora\typora-user-images\image-20200219191154692.png)

   ip地址转换

   ​	地址记录的时候，是用点分10进制，但是在计算机中要用到二进制。

   ![image-20200219191748998](C:\Users\fuckoff\AppData\Roaming\Typora\typora-user-images\image-20200219191748998.png)

   address to number

   更新函数

   ![image-20200219223235760](C:\Users\fuckoff\AppData\Roaming\Typora\typora-user-images\image-20200219223235760.png)

   

### 5.2 创建socket

   ![image-20200219200511077](C:\Users\fuckoff\AppData\Roaming\Typora\typora-user-images\image-20200219200511077.png)

   FIRST ONE IS PE_INET OR PE_INET6 

   SECOND  ONE IS SOCK_STREAM OR SOCK_UGRAM

   STREAM OR UGRAM

   THIRD ONE IS 0 .

   成功会返回一个socket 文件描述符。失败返回-1.

   **fd诞生。** 

### 5.3 命名socket

   注意：这里一般只是服务器程序需要。客户端一般使用匿名方式连接。

   一个fd没有绑定socket地址，也就是命名。

   ![image-20200219201802170](C:\Users\fuckoff\AppData\Roaming\Typora\typora-user-images\image-20200219201802170.png)

   作用是把my_addr指向的socket地址分配到文件描述符中。

   成功返回0.失败返回-1。

   并且设定error

   socket地址应该是就是**ip+端口号那个东西/**，前面有提到。

### 5.4 监听socket

   ![image-20200219221110500](C:\Users\fuckoff\AppData\Roaming\Typora\typora-user-images\image-20200219221110500.png)

   放进去队列，但是没有显示这个队列的具体位置，只是队列长度超过backlog，服务器端不受理新的客户端。

成功返回0，失败返回-1。

### 5.5 接受连接

   ![image-20200219222156151](C:\Users\fuckoff\AppData\Roaming\Typora\typora-user-images\image-20200219222156151.png)

   成功返回一个可以新的socket，失败返回-1.

![image-20200220010323785](C:\Users\fuckoff\AppData\Roaming\Typora\typora-user-images\image-20200220010323785.png)



connect发送客户端的ip和端口过去/。前面listen 在这个端口监听，代码会等到对方调用到connect ，发送客户端的ip和端口过去，然后定义一个client，进行承接。接下来就是内核的工作。

```
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main( int argc, char* argv[] )
{
    if( argc <= 2 )
    {
        printf( "usage: %s ip_address port_number\n", basename( argv[0] ) );
        return 1;
    }
    const char* ip = argv[1];
    int port = atoi( argv[2] );

    struct sockaddr_in address;
    bzero( &address, sizeof( address ) );
    address.sin_family = AF_INET;
    inet_pton( AF_INET, ip, &address.sin_addr );
    address.sin_port = htons( port );

    int sock = socket( PF_INET, SOCK_STREAM, 0 );
    assert( sock >= 0 );

    int ret = bind( sock, ( struct sockaddr* )&address, sizeof( address ) );
    assert( ret != -1 );

    ret = listen( sock, 5 );
    assert( ret != -1 );

    struct sockaddr_in client;
    socklen_t client_addrlength = sizeof( client );
    //这里的connfd 和sock 不是一样，connfd是连接socket，sock是监听socket。ret是结果判断值。
    int connfd = accept( sock, ( struct sockaddr* )&client, &client_addrlength );
    if ( connfd < 0 )
    {
        printf( "errno is: %d\n", errno );
    }
    else
    {
        char remote[INET_ADDRSTRLEN ];
        printf( "connected with ip: %s and port: %d\n", 
            inet_ntop( AF_INET, &client.sin_addr, remote, INET_ADDRSTRLEN ), ntohs( client.sin_port ) );
        close( connfd );
    }

    close( sock );
    return 0;
}

```



### 5.6 发起连接

   ![image-20200219223439449](C:\Users\fuckoff\AppData\Roaming\Typora\typora-user-images\image-20200219223439449.png)

   成功返回0.失败返回-1 且设置errno/

   成功后，sockfd 唯一标识 连接。客户端读写sockfd进行通信，这个sockfd是直接是使用

![image-20200220005953983](C:\Users\fuckoff\AppData\Roaming\Typora\typora-user-images\image-20200220005953983.png)

![image-20200220010005704](C:\Users\fuckoff\AppData\Roaming\Typora\typora-user-images\image-20200220010005704.png)

所以这个三次握手开始于listen，结束于accept。accept返回的时候，就已经第三次握手结束了。

![image-20200220010149067](C:\Users\fuckoff\AppData\Roaming\Typora\typora-user-images\image-20200220010149067.png)

**connect返回的是本地的sockfd**

### 5.7 关闭连接

   **![image-20200219224329294](C:\Users\fuckoff\AppData\Roaming\Typora\typora-user-images\image-20200219224329294.png)**

   关闭连接---》这里只是把fd的计数减一

   直到置为0才真正关闭。

   马上杀掉的是 shutdown函数。

   ![image-20200219224743912](C:\Users\fuckoff\AppData\Roaming\Typora\typora-user-images\image-20200219224743912.png)

   howto 有三种：

   ![image-20200219224754686](C:\Users\fuckoff\AppData\Roaming\Typora\typora-user-images\image-20200219224754686.png)

### 5.8数据读写

​	read 和write 函数 

相比于 

​	send recv函数

![image-20200219225224741](C:\Users\fuckoff\AppData\Roaming\Typora\typora-user-images\image-20200219225224741.png)

buf是设定的缓冲区位置，len 为长度。

成功返回recv的长度，

失败返回-1.

同理，send 成功返回写的实际长度，失败返回-1。



#### example code：

客户端代码：

输入的是服务器ip和端口

```cpp
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main( int argc, char* argv[] )
{
    if( argc <= 2 )
    {
        printf( "usage: %s ip_address port_number\n", basename( argv[0] ) );
        return 1;
    }
    const char* ip = argv[1];
    int port = atoi( argv[2] );

    struct sockaddr_in server_address;
    bzero( &server_address, sizeof( server_address ) );
    server_address.sin_family = AF_INET;
    inet_pton( AF_INET, ip, &server_address.sin_addr );
    server_address.sin_port = htons( port );

    int sockfd = socket( PF_INET, SOCK_STREAM, 0 );
    assert( sockfd >= 0 );
    if ( connect( sockfd, ( struct sockaddr* )&server_address, sizeof( server_address ) ) < 0 )
    {
        printf( "connection failed\n" );
    }
    else
    {
        printf( "send oob data out\n" );
        const char* oob_data = "abc";
        const char* normal_data = "123";
        send( sockfd, normal_data, strlen( normal_data ), 0 );
        send( sockfd, oob_data, strlen( oob_data ), MSG_OOB );
        send( sockfd, normal_data, strlen( normal_data ), 0 );
    }

    close( sockfd );
    return 0;
}

```

   

   服务器代码：

这里一样是输入服务器的ip和端口。

指的是listen 自己的ip和端口。等到这个位置有connect请求，进行通信。

```cpp
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define BUF_SIZE 1024

int main( int argc, char* argv[] )
{
    if( argc <= 2 )
    {
        printf( "usage: %s ip_address port_number\n", basename( argv[0] ) );
        return 1;
    }
    const char* ip = argv[1];
    int port = atoi( argv[2] );

    struct sockaddr_in address;
    bzero( &address, sizeof( address ) );
    address.sin_family = AF_INET;
    inet_pton( AF_INET, ip, &address.sin_addr );
    address.sin_port = htons( port );

    int sock = socket( PF_INET, SOCK_STREAM, 0 );
    assert( sock >= 0 );

    int ret = bind( sock, ( struct sockaddr* )&address, sizeof( address ) );
    assert( ret != -1 );

    ret = listen( sock, 5 );
    assert( ret != -1 );

    struct sockaddr_in client;
    socklen_t client_addrlength = sizeof( client );
    int connfd = accept( sock, ( struct sockaddr* )&client, &client_addrlength );
    if ( connfd < 0 )
    {
        printf( "errno is: %d\n", errno );
    }
    else
    {
        char buffer[ BUF_SIZE ];

        memset( buffer, '\0', BUF_SIZE );
        ret = recv( connfd, buffer, BUF_SIZE-1, 0 );
        printf( "got %d bytes of normal data '%s'\n", ret, buffer );

        memset( buffer, '\0', BUF_SIZE );
        ret = recv( connfd, buffer, BUF_SIZE-1, MSG_OOB );
        printf( "got %d bytes of oob data '%s'\n", ret, buffer );

        memset( buffer, '\0', BUF_SIZE );
        ret = recv( connfd, buffer, BUF_SIZE-1, 0 );
        printf( "got %d bytes of normal data '%s'\n", ret, buffer );

        close( connfd );
    }

    close( sock );
    return 0;
}


```

​    实现指令

![image-20200219232116543](C:\Users\fuckoff\AppData\Roaming\Typora\typora-user-images\image-20200219232116543.png)

所以函数两边都是记录服务器的ip和端口。

####  UDP数据读写

![image-20200220000859552](C:\Users\fuckoff\AppData\Roaming\Typora\typora-user-images\image-20200220000859552.png)



因为无连接，所以每次都不要知道发送端的socket地址。

写一样，每次都要知道接收端的地址。

### 5.9 带外标记

### 5.10 地址信息函数

![image-20200220001721046](C:\Users\fuckoff\AppData\Roaming\Typora\typora-user-images\image-20200220001721046.png)

第一个是本端socket地址，第二个是远端socket地址，超出len，就截断。

### 5.12 网络信息API

​	IP地址和端口号的使用。

![image-20200220010624976](C:\Users\fuckoff\AppData\Roaming\Typora\typora-user-images\image-20200220010624976.png)

gethostbyname 和gethostbyaddr 

getservbyname  and get servbyport

getaddrinfo and getnameinfo

![image-20200220011048764](C:\Users\fuckoff\AppData\Roaming\Typora\typora-user-images\image-20200220011048764.png)

![image-20200220011203109](C:\Users\fuckoff\AppData\Roaming\Typora\typora-user-images\image-20200220011203109.png)



## 第六章 高级io函数

### 6.1 pipe 函数

​	![image-20200220045212198](C:\Users\fuckoff\AppData\Roaming\Typora\typora-user-images\image-20200220045212198.png)

**成功把一对打开的文件描述符填入数组中。**

这边是两个fd 进行的通信。只有单方面的通信，只能一边写一边读，不能反过来。fd【0】读，fd【1】写。

创建的是单向管道。

![image-20200220045542802](C:\Users\fuckoff\AppData\Roaming\Typora\typora-user-images\image-20200220045542802.png)

创建双向通道。但是只能本地使用，只是用本地域协议族AF_UNIX.

### 6.2 dup 和 dup2 函数

不经常用这个东西。

![image-20200220050229193](C:\Users\fuckoff\AppData\Roaming\Typora\typora-user-images\image-20200220050229193.png)



作用是创建一个新的文件描述符，但是它是最小的可使用文件描述符。这个描述符指向和原先的一样，只是变成最小的描述符而已。可能控制大小把。

### 6.3 readv 和writev 函数/

![image-20200220050633517](C:\Users\fuckoff\AppData\Roaming\Typora\typora-user-images\image-20200220050633517.png)

分散读和集中写。

成功返回读出和写入fd 的字节数。

从fd读到分散的内存块。write从分散的内存块写入到fd中



![image-20200220053359530](C:\Users\fuckoff\AppData\Roaming\Typora\typora-user-images\image-20200220053359530.png)

两块分散的内存块，只要用数组串联起来就可以读。

### 6.4 sendfile 函数

![image-20200220053612918](C:\Users\fuckoff\AppData\Roaming\Typora\typora-user-images\image-20200220053612918.png)

在两个文件描述符之间直接传递数据（完全在内核操作。）：零拷贝

之前的send，write，read等函数都是对单个的文件描述符进行操作，但是这个是双向的操作。

in传到out，读出到写入。

![image-20200220054434757](C:\Users\fuckoff\AppData\Roaming\Typora\typora-user-images\image-20200220054434757.png)

### 6.5 mmap 函数和munmap 函数

![image-20200220054624632](C:\Users\fuckoff\AppData\Roaming\Typora\typora-user-images\image-20200220054624632.png)

​	一个申请一段内存空间，既可以用来作为进程通信的共享内存，还可以将文件映射到其中。

​	释放空间。

prot是空间的访问权限。

![image-20200220055249165](C:\Users\fuckoff\AppData\Roaming\Typora\typora-user-images\image-20200220055249165.png)

flag参数控制内存段内容被修改后程序的行为，

![image-20200220055339627](C:\Users\fuckoff\AppData\Roaming\Typora\typora-user-images\image-20200220055339627.png)

fd一般都是open文件返回的文件描述符。

### 6.6 splice 函数

没用过这个函数

用于两个文件描述符之间移动数据，同属于零拷贝。

ps 零拷贝就是在内核缓冲区执行，不经过用户缓冲区。

![](C:\Users\fuckoff\AppData\Roaming\Typora\typora-user-images\image-20200220055758317.png)

使用splice 函数。至少fd_in 和fd_out 必须有一个是管道描述符  -----pipe

![image-20200220060611760](C:\Users\fuckoff\AppData\Roaming\Typora\typora-user-images\image-20200220060611760.png)

![image-20200220060743187](C:\Users\fuckoff\AppData\Roaming\Typora\typora-user-images\image-20200220060743187.png)

### 6.7 tee 函数

​	 在两个管道文件描述符之间复制数据。同为零拷贝操作。原文件描述符上的数据还可以用在后续的读操作中。

![image-20200220061355748](C:\Users\fuckoff\AppData\Roaming\Typora\typora-user-images\image-20200220061355748.png)

tee 和splice 区别

![image-20200220062101402](C:\Users\fuckoff\AppData\Roaming\Typora\typora-user-images\image-20200220062101402.png)

注意这里，pipe内部本身就会从读出【1】到写入【0】

### **6.8 fcntl 函数(联系第十章)

![image-20200220062155560](C:\Users\fuckoff\AppData\Roaming\Typora\typora-user-images\image-20200220062155560.png)

提供对文件控制符的各种控制操作/

例子：

![image-20200220062836968](C:\Users\fuckoff\AppData\Roaming\Typora\typora-user-images\image-20200220062836968.png)

这个联系到信号的处理 ----第十章的信息。

暂时搁置！



## 第七章 linux服务器程序规范

### 7.1 日志

syslog函数 和 rsylogd 守护进程通信。

![image-20200220064640414](C:\Users\fuckoff\AppData\Roaming\Typora\typora-user-images\image-20200220064640414.png)

### 7.2 用户信息

UID:当前进程的真实用户ID

 EUID：有效用户

GID：真实组

EGID：有效组

![image-20200220070040767](C:\Users\fuckoff\AppData\Roaming\Typora\typora-user-images\image-20200220070040767.png)

​	一个进程有两个用户ID: UID 和 EUID。EUID 作用是：使运行程序的用户拥有该程序的**有效用户**权限。

example：su 程序。普通用户怎么获得root 权限？用EUID ,所有普通用户运行su时，允许有有效用户的权限，这里的有效用户时root用户。

### 7.3 进程间关系

进程组：每一个进程都隶属一个进程组

![image-20200220071659058](C:\Users\fuckoff\AppData\Roaming\Typora\typora-user-images\image-20200220071659058.png)

pid 是进程的id。uid是用户运行程序的id。

## 第八章 高性能服务器程序框架(重点)

### 8.1 服务器模型

##### c/s 模型

​	在这个图中，服务器使用的是I/O复用技术之一的select系统调用。select函数对每一个请求fork一个新进程。

![](C:\Users\fuckoff\Desktop\INTERNSHIP\mkfile_picture\image-20200221031904050.png)

##### p2p模型

​	每一个客户端都可以充当服务器，但是网络负载加重，而且需要一个专门的发现服务器，提供寻找资源的查找。

![](C:\Users\fuckoff\Desktop\INTERNSHIP\mkfile_picture\image-20200221033124815.png)

### 8.2 服务器编程框架

​	抽象的服务器框架，需要的内容是

![](D:\电子书\网络编程相关笔记\picture\服务器基本框架.png)

i/o处理单元：一般是用来处理客户连接，读写客户端网络数据。又或者是负责负载均衡。

逻辑单元：业务线程或者进程，负责完成客户端请求或者说是交互。

网络储存单元：本地数据库或者数据库服务器。

请求队列：不是客户端对服务器的请求队列哦，而是各个单元之间的通信方式。一般IO处理单元要 通知逻辑单元处理请求的时候，就需要请求队列。

一般请求队列通常被实现成池的一部分。**在后面池的部分提及。**

### 8.3 i/o 模型

​	简书： https://www.jianshu.com/p/486b0965c296 

首先分清楚 socket 和文件描述符的区别和联系。

socket是特殊的文件描述符，是特别的网络通信的文件描述符。

阻塞i/o–----》阻塞的文件描述符。

非阻塞i/o，非阻塞i/o的系统调用总是需要立即返回，如果事情还没发生，返回也是-1，和异常一样，但是在errno 的设计里却是不一样/

-----》非阻塞i/o（读写等）通常需要和其他i/o通知机制使用，例如i/o复用和SIGIO信号。

#### I/O 复用

io复用是最常用的io通知机制，应用程序通过io复用函数向“内核注册一组事件”，内核通过io复用函数把时间**通知**给应用程序。

 IO多路复用是指内核一旦发现进程指定的一个或者多个IO条件准备读取，它就通知该进程 

I/O多路复用就是`通过一种机制，一个进程可以监视多个描述符，一旦某个描述符就绪（一般是读就绪或者写就绪），能够通知程序进行相应的读写操作`。`但select，pselect，poll，epoll本质上都是同步I/O`

```
当客户处理多个描述符时（一般是交互式输入和网络套接口），必须使用I/O复用。

当一个客户同时处理多个套接口时，而这种情况是可能的，但很少出现。

如果一个TCP服务器既要处理监听套接口，又要处理已连接套接口，一般也要用到I/O复用。

如果一个服务器即要处理TCP，又要处理UDP，一般要使用I/O复用。

如果一个服务器要处理多个服务或多个协议，一般要使用I/O复用。

作者：猿码道
链接：https://www.jianshu.com/p/dfd940e7fca2
来源：简书
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

```



#### 信号处理

SIGIO信号的作用也是很像的。

#### ps 异步IO 和同步IO的区别：

异步io是把读写控制权交给内核，所以可以马上返回，不管io是否阻塞。

例如：AIO.H头文件函数

同步io模型是要求用户代码自行执行IO操作，

例如：IO复用，阻塞IO，信号驱动IO

总的来说；

同步IO是向应用程序通知IO就绪事件，

异步IO是向应用程序通知IO完成事件。

![8.2](D:\电子书\网络编程相关笔记\picture\模型对比.png)

```
阻塞I/O：同步阻塞
非阻塞I/O：同步（轮询）非阻塞
I/O多路复用：同步阻塞（不过可以同时监听多个socket状态，效率高了）
信号驱动I/O：异步非阻塞
异步I/O：真正意义上的异步非阻塞（上面的都只是数据准备阶段，这个是数据准备和数据处理阶段）

```



### 8.4 两种高效的事件处理模式

服务器程序需要处理的三类事件：

1. IO事件![五大io模型](D:\电子书\网络编程相关笔记\picture\五大io模型.png)

2. 信号

3. 定时事件。

   怎么处理：

   ​	同步IO模型实现的REACTOR 模式

   ​	异步IO模型实现的PROACTOR 模式

#### REACTOR 模式

​	主线程只负责监听消息，工作通知给请求队列上的工作线程实现，并且工作线程也实现读写操作。主线程只是调用epoll_wait函数进行监听事件。

和proactor事件不同的是：

​	**工作线程在读的事件中，会向epoll内核事件表注册socket的写就绪事件**

![](D:\电子书\网络编程相关笔记\picture\reactor 模式.png)

#### PROACTOR 模式

​	proactor模式所有IO操作都是IO主线程和内核负责，**工作线程只负责业务逻辑**，不负责写IO注册。业务逻辑是应用程序定义的。

​	主线程的epoll_wait 只是用来监听socket上的连接请求。读写事件都交给aio_write 和aio_read 进行，都是内核完成。

#### REACTOR 模拟 PROACTOR 模式

​	让主线程执行读写操作，工作线程只负责业务逻辑，看起来就和异步IO一样。

​	主线程读取数据后，封装成一个请求对象插入请求队列。

​	

![](D:\电子书\网络编程相关笔记\picture\模拟proactor模式.png)

### 8.5 两种并发模式（不是并发编程哦）

#### 半同步/半异步模式

有一个显性的请求队列。

这里的同步和异步不是io模型的同步/异步

io模型的同步/异步指的是内核向应用程序通知饿是就绪事件还是完成事件。（谁来读，读完了吗）

并发模式的同步：程序执行完全靠代码序列完成。（怎么读，怎么处理。）

**异步：程序执行由系统事件驱动。**

![](D:\电子书\网络编程相关笔记\picture\并发模式的同步异步.png)



所以在服务器中，适合同步线程和异步线程合作一起实现。

异步线程相当于io处理单元。------用于处理io事件。

同步线程相当于逻辑单元。---用于处理业务逻辑

example： 半同步/半反应堆模式

![](D:\电子书\网络编程相关笔记\picture\半同步_半反应堆模式.png)

这里只有一个主线程充当异步线程，调用epoll_wait监听socket连接，如果由新的连接，就产生新的连接socket，向epoll没和事件表中注册读写事件，当出现读写事件后，放到请求队列中，同步线程（工作线程）睡眠在请求队列中，竞争使用**（所以这里是REACTOR事件处理模式）**

​	同样的哦，这样的模式也可以模拟	PROACTOR 模式，即用主线程进行读写，然后同步线程只需要完成业务逻辑。

-----第15章。

##### 缺点：

	1.	主线程和工作线程共享请求队列，用互斥锁浪费CPU等待时间。
 	2.	工作线程只能阻塞处理一个客户请求，客户请求很多的情况下，会导致请求队列堆积很多任务对象，

![](D:\电子书\网络编程相关笔记\picture\高效半同步异步模式.png)

改变时把中间的连接socket过程直接发到工作线程中去，而不是放到请求队列中等待。

​	每一个线程都是**异步模式**，不算严格意义的半同步半异步。

#### 领导者/追随者模式

​	核心：线程池/

​	在池中，轮流当领导线程，处理io事件，其他的在线程池中等待称为新的领导者。原先领导挑选新领导，然后完成自己的io事件。

​	模式组件分为：句柄集，线程集，事件处理器，具体的事件处理器（concreteEventHandler）。

![](D:\电子书\网络编程相关笔记\picture\领导者追随者模式.png)

举例子：

您可能已经读过，该模式由4个组件组成：ThreadPool，HandleSet，Handle，ConcreteEventHandler（实现EventHandler接口）。

您可以将其视为夜间的出租车站，那里的所有驾驶员都在睡觉，除了一个领导者。ThreadPool是管理多个线程的站点-出租车。

领导者正在等待HandleSet上的IO事件，例如驱动程序如何等待客户端。

当客户到达时（以标识IO事件的Handle的形式），领队驾驶员唤醒另一位驾驶员成为下一位领队，并为其乘客提供服务。

当他将客户带到给定的地址（调用ConcreteEventHandler并将Handle移交给它）时，下一位领导者可以同时为另一位乘客提供服务。

驾驶员完成后，他乘坐出租车返回车站，如果车站不空，则入睡。否则，他将成为领导者。

这种模式的优点是：

- 线程之间不需要通信，不需要同步，也不需要共享内存（没有锁，互斥体）。
- 可以添加更多的ConcreteEventHandlers而不影响任何其他EventHandler
- 由于有多个线程，最大限度地减少了延迟

缺点是：

- 复杂
- 网络IO可能成为瓶颈

![](D:\电子书\网络编程相关笔记\picture\领导者追随者流程图.png)

### 8.6 有限状态机

​	是逻辑单元内部的编程方法。

​	状态转移和状态独立的两种状态机。

​	不同的状态，逻辑单元触发不同事件。

### 8.7 提高服务器性能的其他建议。

##### 	池的设计/

​		静态资源分配，提前分配资源，不许每次都访问内核进行动态资源分配，用资源换时间。

​	内存池，线程池，连接池，进程池。

​	内存池：通常用在socker的接受缓存和发送缓存中，设立缓冲区来接受，满了再输送上去。

​	线程池：不需要每次都pthread_create 来创建，再池中已经有“足够的”线程等待处理新的客户请求。

​	进程池：同线程池。

​	连接池：是一些服务器内部或者服务器机群内部需要频繁访问本地数据库，先预先建立一组连接集合，逻辑单元需要访问数据库的时候，直接重连接池中获取一个实体。

##### 	数据复制/

​	尽量避免数据复制。

1.内核缓冲区和应用程序缓冲区之间的数据复制。

例如ftp服务器，客户端请求一个文件，服务器只需要直接发送，不需要拷贝出来放到应用程序缓冲区。

2.用户代码之间的数据复制也要避免，共享内存使用，例如指针指向内存，不过这样可能要修改内存，又是另一个问题了。

##### 	上下文切换和锁/

	1. 避免太多的线程或者进程切换。因为回耗费很多CPU时间。
 	2. 共享资源的锁也要减少，因为上锁后，其他只能阻塞等待，所以在半同步/半反应堆的模式没有下面的半同步半异步的效率高。因为避免主线程在请求队列中上锁。
 	3. 还可以减小锁的粒度。



## 第九章 i/O复用

### 9.1 select 系统调用

![](D:\电子书\网络编程相关笔记\picture\select_function.png)

select处理的异常情况：socket上接收到带外数据。

```cpp
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>

int main( int argc, char* argv[] )
{
	if( argc <= 2 )
	{
		printf( "usage: %s ip_address port_number\n", basename( argv[0] ) );
		return 1;
	}
	const char* ip = argv[1];
	int port = atoi( argv[2] );
	printf( "ip is %s and port is %d\n", ip, port );

	int ret = 0;
        struct sockaddr_in address;
        bzero( &address, sizeof( address ) );
        address.sin_family = AF_INET;
        inet_pton( AF_INET, ip, &address.sin_addr );
        address.sin_port = htons( port );

	int listenfd = socket( PF_INET, SOCK_STREAM, 0 );
	assert( listenfd >= 0 );

        ret = bind( listenfd, ( struct sockaddr* )&address, sizeof( address ) );
	assert( ret != -1 );

	ret = listen( listenfd, 5 );
	assert( ret != -1 );

	struct sockaddr_in client_address;
        socklen_t client_addrlength = sizeof( client_address );
	int connfd = accept( listenfd, ( struct sockaddr* )&client_address, &client_addrlength );
	if ( connfd < 0 )
	{
		printf( "errno is: %d\n", errno );
		close( listenfd );
	}

	char remote_addr[INET_ADDRSTRLEN];
	printf( "connected with ip: %s and port: %d\n", inet_ntop( AF_INET, &client_address.sin_addr, remote_addr, INET_ADDRSTRLEN ), ntohs( client_address.sin_port ) );

	char buf[1024];
        fd_set read_fds;
        fd_set exception_fds;

        FD_ZERO( &read_fds );
        FD_ZERO( &exception_fds );

        int nReuseAddr = 1;
	setsockopt( connfd, SOL_SOCKET, SO_OOBINLINE, &nReuseAddr, sizeof( nReuseAddr ) );
	while( 1 )
	{
		memset( buf, '\0', sizeof( buf ) );
		FD_SET( connfd, &read_fds );
		FD_SET( connfd, &exception_fds );

        	ret = select( connfd + 1, &read_fds, NULL, &exception_fds, NULL );
		printf( "select one\n" );
        	if ( ret < 0 )
        	{
                	printf( "selection failure\n" );
                	break;
        	}
	
        	if ( FD_ISSET( connfd, &read_fds ) )
		{
        		ret = recv( connfd, buf, sizeof( buf )-1, 0 );
			if( ret <= 0 )
			{
				break;
			}
			printf( "get %d bytes of normal data: %s\n", ret, buf );
		}
		else if( FD_ISSET( connfd, &exception_fds ) )
        	{
        		ret = recv( connfd, buf, sizeof( buf )-1, MSG_OOB );
			if( ret <= 0 )
			{
				break;
			}
			printf( "get %d bytes of oob data: %s\n", ret, buf );
        	}

	}

	close( connfd );
	close( listenfd );
	return 0;
}

```

有趣点：

select返回的是文件描述符吗？

是，是就绪的文件描述符。但是还需要用一个FD_ISSET 函数判断是哪个文件就绪了，

```
通常我们使用FD_ISSET是为了检查在select函数返回后，某个描述符是否准备好，以便进行接下来的处理操作。 当描述符fd在描述符集fdset中返回非零值，否则，返回零。
                  --百度百科
```

### 9.2 poll 系统调用

poll和select类似，返回值含义和select一样。

![](D:\电子书\网络编程相关笔记\picture\poll模型.png)

注意fds参数，是一个特定结构参数，是一个自定义的数组。

![](D:\电子书\网络编程相关笔记\picture\structure_fds.png)

### select和poll不同

1. select最多只支持1024，因为select是用的定长数组。poll是用户自定义数组长度。

2. s只支持 fd小于1024，如果单个进程多于1024.则不适合用select

3. select函数是用的位运算，在select之前要生成读写和异常的掩码变量，然后FD_ZERO初始化，再使用select函数应用掩码变量。

   然而poll函数用的是自己定义的structure 中的 fd和event来使用 ，revent 指的是实际发生的事，由内核修改，通知应用程序实际情况。事件有定义的词语。

4. select中fd_set事被内核和用户共同修改，所以，哟啊么每次FD_CLR后FD_SET,要么备份。poll用户修改的events，内核修改的是revents。

### 9.3 epoll 系列系统调用

epoll用一组函数完成任务。

 epoll_create,epoll_ctl和epoll_wait 三个函数，相比于select 和 poll只有一个函数。

 把用户关心的文件描述符的事件放在内核的一个事件表。

![](D:\电子书\网络编程相关笔记\picture\epoll_create.png)



下面函数操作epoll的内核事件表。

![](D:\电子书\网络编程相关笔记\picture\epoll_ctl.png)

event是一个定义的结构体

![](D:\电子书\网络编程相关笔记\picture\epoll_event结构.png)

事件和poll的一样。只是加个e再首部。

epoll系列系统调用主要接口epoll_wait函数。

![](D:\电子书\网络编程相关笔记\picture\epoll_wait.png)

成功返回救赎的文件描述符个数。检测到事件，把所有事件从内核事件表复制到数组中。

数组空间比较干净，

对比于select函数和poll函数而言，他们的数组既用于用户存进去的注册事件，还有就绪事件。

![](D:\电子书\网络编程相关笔记\picture\poll &&epoll using difference.png)

#### LT && ET MODE

LT 是电平触发，ET是边沿触发。

LT是默认高效方式，事件触发的时候，可以不立即处理，再下一次再调用epol_wait 还会再次通告。

但ET Y有时候也会使用，，事件触发的时候，必须马上处理，因为后续调用不再通知该事件。

代码对比两个模式：

首先先看这个注册到内核事件表中

```cpp
void addfd( int epollfd, int fd, bool enable_et )
{
    epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN;
    if( enable_et )
    {
        event.events |= EPOLLET;
    }
    epoll_ctl( epollfd, EPOLL_CTL_ADD, fd, &event );
    setnonblocking( fd );
}
```

LT:监听的放进内核事件表，不是监听的
读出数据，因为是LT，只执行一次。

```CPP
void lt( epoll_event* events, int number, int epollfd, int listenfd )
{
    char buf[ BUFFER_SIZE ];
    for ( int i = 0; i < number; i++ )
    {
        int sockfd = events[i].data.fd;
        if ( sockfd == listenfd )
        {
            struct sockaddr_in client_address;
            socklen_t client_addrlength = sizeof( client_address );
            int connfd = accept( listenfd, ( struct sockaddr* )&client_address, &client_addrlength );
            addfd( epollfd, connfd, false );
        }
        else if ( events[i].events & EPOLLIN )
        {
            ////
            ////
            ///监听的放进内核事件表，不是监听的
////////读出数据，因为是LT，只执行一次。
            printf( "event trigger once\n" );
            memset( buf, '\0', BUFFER_SIZE );
            int ret = recv( sockfd, buf, BUFFER_SIZE-1, 0 );
            if( ret <= 0 )
            {
                close( sockfd );
                continue;
            }
            printf( "get %d bytes of content: %s\n", ret, buf );
        }
        else
        {
            printf( "something else happened \n" );
        }
    }
}

```

ET://这里进循环，把全部数据读出来才停止。

```CPP
void et( epoll_event* events, int number, int epollfd, int listenfd )
{
    char buf[ BUFFER_SIZE ];
    for ( int i = 0; i < number; i++ )
    {
        int sockfd = events[i].data.fd;
        if ( sockfd == listenfd )
        {
            struct sockaddr_in client_address;
            socklen_t client_addrlength = sizeof( client_address );
            int connfd = accept( listenfd, ( struct sockaddr* )&client_address, &client_addrlength );
            addfd( epollfd, connfd, true );
        }
        else if ( events[i].events & EPOLLIN )
        {
            printf( "event trigger once\n" );
            ///////
            /////这里进循环，把全部数据读出来才停止。//
            ////
            while( 1 )
            {
                memset( buf, '\0', BUFFER_SIZE );
                int ret = recv( sockfd, buf, BUFFER_SIZE-1, 0 );
                if( ret < 0 )
                {
                    if( ( errno == EAGAIN ) || ( errno == EWOULDBLOCK ) )
                    {
                        printf( "read later\n" );
                        break;
                    }
                    close( sockfd );
                    break;
                }
                else if( ret == 0 )
                {
                    close( sockfd );
                }
                else
                {
                    printf( "get %d bytes of content: %s\n", ret, buf );
                }
            }
        }
        else
        {
            printf( "something else happened \n" );
        }
    }
}

```



```cpp
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <pthread.h>

#define MAX_EVENT_NUMBER 1024
#define BUFFER_SIZE 10

int setnonblocking( int fd )
{
    int old_option = fcntl( fd, F_GETFL );
    int new_option = old_option | O_NONBLOCK;
    fcntl( fd, F_SETFL, new_option );
    return old_option;
}

void addfd( int epollfd, int fd, bool enable_et )
{
    epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN;
    if( enable_et )
    {
        event.events |= EPOLLET;
    }
    epoll_ctl( epollfd, EPOLL_CTL_ADD, fd, &event );
    setnonblocking( fd );
}

void lt( epoll_event* events, int number, int epollfd, int listenfd )
{
    char buf[ BUFFER_SIZE ];
    for ( int i = 0; i < number; i++ )
    {
        int sockfd = events[i].data.fd;
        if ( sockfd == listenfd )
        {
            struct sockaddr_in client_address;
            socklen_t client_addrlength = sizeof( client_address );
            int connfd = accept( listenfd, ( struct sockaddr* )&client_address, &client_addrlength );
            addfd( epollfd, connfd, false );
        }
        else if ( events[i].events & EPOLLIN )
        {
            printf( "event trigger once\n" );
            memset( buf, '\0', BUFFER_SIZE );
            int ret = recv( sockfd, buf, BUFFER_SIZE-1, 0 );
            if( ret <= 0 )
            {
                close( sockfd );
                continue;
            }
            printf( "get %d bytes of content: %s\n", ret, buf );
        }
        else
        {
            printf( "something else happened \n" );
        }
    }
}

void et( epoll_event* events, int number, int epollfd, int listenfd )
{
    char buf[ BUFFER_SIZE ];
    for ( int i = 0; i < number; i++ )
    {
        int sockfd = events[i].data.fd;
        if ( sockfd == listenfd )
        {
            struct sockaddr_in client_address;
            socklen_t client_addrlength = sizeof( client_address );
            int connfd = accept( listenfd, ( struct sockaddr* )&client_address, &client_addrlength );
            addfd( epollfd, connfd, true );
        }
        else if ( events[i].events & EPOLLIN )
        {
            printf( "event trigger once\n" );
            while( 1 )
            {
                memset( buf, '\0', BUFFER_SIZE );
                int ret = recv( sockfd, buf, BUFFER_SIZE-1, 0 );
                if( ret < 0 )
                {
                    if( ( errno == EAGAIN ) || ( errno == EWOULDBLOCK ) )
                    {
                        printf( "read later\n" );
                        break;
                    }
                    close( sockfd );
                    break;
                }
                else if( ret == 0 )
                {
                    close( sockfd );
                }
                else
                {
                    printf( "get %d bytes of content: %s\n", ret, buf );
                }
            }
        }
        else
        {
            printf( "something else happened \n" );
        }
    }
}

int main( int argc, char* argv[] )
{
    if( argc <= 2 )
    {
        printf( "usage: %s ip_address port_number\n", basename( argv[0] ) );
        return 1;
    }
    const char* ip = argv[1];
    int port = atoi( argv[2] );

    int ret = 0;
    struct sockaddr_in address;
    bzero( &address, sizeof( address ) );
    address.sin_family = AF_INET;
    inet_pton( AF_INET, ip, &address.sin_addr );
    address.sin_port = htons( port );

    int listenfd = socket( PF_INET, SOCK_STREAM, 0 );
    assert( listenfd >= 0 );

    ret = bind( listenfd, ( struct sockaddr* )&address, sizeof( address ) );
    assert( ret != -1 );

    ret = listen( listenfd, 5 );
    assert( ret != -1 );

    epoll_event events[ MAX_EVENT_NUMBER ];
    int epollfd = epoll_create( 5 );
    assert( epollfd != -1 );
    addfd( epollfd, listenfd, true );

    while( 1 )
    {
        int ret = epoll_wait( epollfd, events, MAX_EVENT_NUMBER, -1 );
        if ( ret < 0 )
        {
            printf( "epoll failure\n" );
            break;
        }
    
        lt( events, ret, epollfd, listenfd );
        //et( events, ret, epollfd, listenfd );
    }

    close( listenfd );
    return 0;
}

```

#### epolloneshot 事件

​	因为ET模式只触发一次，但是在多线程或者多进程中，一个socket在被处理的时候又来了新数据可读，唤醒另一个线程对它操作，这样就不合适。

添加addfd函数 ，区别上面的

```cpp
void addfd( int epollfd, int fd, bool oneshot )
{
    epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN | EPOLLET;
    if( oneshot )
    {
        event.events |= EPOLLONESHOT;
    }
    epoll_ctl( epollfd, EPOLL_CTL_ADD, fd, &event );
    setnonblocking( fd );
}
```

### 9.4 三组io复用函数比较

![](D:\电子书\网络编程相关笔记\picture\3个io复用系统调用区别.png)



### 9.5 非阻塞connect

因为connect函数在出错时的 时，如果时对于非阻塞的socket调用connect，就会返回EINPROGRESS的错误，这个时可以工作的，

依然可以用select或者poll等函数进行监听**可写事件**，等到返回后，再用getsocket函数进行消除socket错误。

​	出问题，错误不是EINPROGRESS，立马返回-1。

```cpp
    else if ( errno != EINPROGRESS )
    {
        printf( "unblock connect not support\n" );
        return -1;
  }
```

是这个错误。，但是还要继续判断

```cpp
fd_set readfds;
    fd_set writefds;
    struct timeval timeout;
	//保证read是0把。
    FD_ZERO( &readfds );
    FD_SET( sockfd, &writefds );

    timeout.tv_sec = time;
    timeout.tv_usec = 0;
	//只监控writefd的事件。
    ret = select( sockfd + 1, NULL, &writefds, NULL, &timeout );
    if ( ret <= 0 )
    {
        printf( "connection time out\n" );
        close( sockfd );
        return -1;
    }

    if ( ! FD_ISSET( sockfd, &writefds  ) )
    {
        printf( "no events on sockfd found\n" );
        close( sockfd );
        return -1;
    }

    int error = 0;
    socklen_t length = sizeof( error );
    if( getsockopt( sockfd, SOL_SOCKET, SO_ERROR, &error, &length ) < 0 )
    {
        printf( "get socket option failed\n" );
        close( sockfd );
        return -1;
    }

    if( error != 0 )
    {
        printf( "connection failed after select with the error: %d \n", error );
        close( sockfd );
        return -1;
    }
    
    printf( "connection ready after select with the socket: %d \n", sockfd );
    fcntl( sockfd, F_SETFL, fdopt );
    return sockfd;
```

缺点：

​	unix 系统对于connect函数失败有些事返回-1，有些事返回0/不好移植/

### ***9.6 IO复用高级应用：聊天室程序。（看看和自己有啥不同。）

#### 	9.6.1 客户端

1.使用poll同时用户输入和网络连接。

2.直接用splice函数将用户输入内容直接定向到网络连接中，进行零拷贝

代码：

注意点1： poll函数的使用。

首先定义pollfd  数组，这里定义了注册文件描述符和文件描述符sockfd可读事件。

可读事件处理。

POLLIN 代表可读，POLLOUT代表可写。

```cpp
 else if( fds[1].revents & POLLIN )
        {
            memset( read_buf, '\0', BUFFER_SIZE );
            recv( fds[1].fd, read_buf, BUFFER_SIZE-1, 0 );
            printf( "%s\n", read_buf );
        }
```

如果注册文件描述符，则用splice函数进行内核零拷贝，因为它需要至少一个pipe描述符。

```cpp

        if( fds[0].revents & POLLIN )
        {
            ret = splice( 0, NULL, pipefd[1], NULL, 32768, SPLICE_F_MORE | SPLICE_F_MOVE );
            ret = splice( pipefd[0], NULL, sockfd, NULL, 32768, SPLICE_F_MORE | SPLICE_F_MOVE );
        }
    }
```



```cpp
#define _GNU_SOURCE 1
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <poll.h>
#include <fcntl.h>

#define BUFFER_SIZE 64

int main( int argc, char* argv[] )
{
    if( argc <= 2 )
    {
        printf( "usage: %s ip_address port_number\n", basename( argv[0] ) );
        return 1;
    }
    const char* ip = argv[1];
    int port = atoi( argv[2] );

    struct sockaddr_in server_address;
    bzero( &server_address, sizeof( server_address ) );
    server_address.sin_family = AF_INET;
    inet_pton( AF_INET, ip, &server_address.sin_addr );
    server_address.sin_port = htons( port );

    int sockfd = socket( PF_INET, SOCK_STREAM, 0 );
    assert( sockfd >= 0 );
    if ( connect( sockfd, ( struct sockaddr* )&server_address, sizeof( server_address ) ) < 0 )
    {
        printf( "connection failed\n" );
        close( sockfd );
        return 1;
    }

    pollfd fds[2];
    fds[0].fd = 0;
    fds[0].events = POLLIN;
    fds[0].revents = 0;
    fds[1].fd = sockfd;
    fds[1].events = POLLIN | POLLRDHUP;
    fds[1].revents = 0;
    char read_buf[BUFFER_SIZE];
    int pipefd[2];
    int ret = pipe( pipefd );
    assert( ret != -1 );

    while( 1 )
    {
        ret = poll( fds, 2, -1 );
        if( ret < 0 )
        {
            printf( "poll failure\n" );
            break;
        }

        if( fds[1].revents & POLLRDHUP )
        {
            printf( "server close the connection\n" );
            break;
        }
        else if( fds[1].revents & POLLIN )
        {
            memset( read_buf, '\0', BUFFER_SIZE );
            recv( fds[1].fd, read_buf, BUFFER_SIZE-1, 0 );
            printf( "%s\n", read_buf );
        }

        if( fds[0].revents & POLLIN )
        {
            ret = splice( 0, NULL, pipefd[1], NULL, 32768, SPLICE_F_MORE | SPLICE_F_MOVE );
            ret = splice( pipefd[0], NULL, sockfd, NULL, 32768, SPLICE_F_MORE | SPLICE_F_MOVE );
        }
    }
    
    close( sockfd );
    return 0;
}

```

#### 9.6.2 服务端

​	使用poll同时管理监听socket，连接socket/

​	有没有用线程池？无

​	做到用户连接管理

代码如下：

```cpp
#define _GNU_SOURCE 1
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <poll.h>

#define USER_LIMIT 5
#define BUFFER_SIZE 64
#define FD_LIMIT 65535

struct client_data
{
    sockaddr_in address;
    char* write_buf;
    char buf[ BUFFER_SIZE ];
};

int setnonblocking( int fd )
{
    int old_option = fcntl( fd, F_GETFL );
    int new_option = old_option | O_NONBLOCK;
    fcntl( fd, F_SETFL, new_option );
    return old_option;
}

int main( int argc, char* argv[] )
{
    if( argc <= 2 )
    {
        printf( "usage: %s ip_address port_number\n", basename( argv[0] ) );
        return 1;
    }
    const char* ip = argv[1];
    int port = atoi( argv[2] );

    int ret = 0;
    struct sockaddr_in address;
    bzero( &address, sizeof( address ) );
    address.sin_family = AF_INET;
    inet_pton( AF_INET, ip, &address.sin_addr );
    address.sin_port = htons( port );

    int listenfd = socket( PF_INET, SOCK_STREAM, 0 );
    assert( listenfd >= 0 );

    ret = bind( listenfd, ( struct sockaddr* )&address, sizeof( address ) );
    assert( ret != -1 );

    ret = listen( listenfd, 5 );
    assert( ret != -1 );

    client_data* users = new client_data[FD_LIMIT];
    pollfd fds[USER_LIMIT+1];
    int user_counter = 0;
    //只是开始的初始化，
    for( int i = 1; i <= USER_LIMIT; ++i )
    {
        fds[i].fd = -1;
        fds[i].events = 0;
    }
    //阻塞结束，等到一个监听fd
    fds[0].fd = listenfd;
    fds[0].events = POLLIN | POLLERR;
    fds[0].revents = 0;
    //进入循环，有新的连接，在里面更新？
    //哪里更新listenfd
    //  int listenfd = socket( PF_INET, SOCK_STREAM, 0 );
    //注意这个
    while( 1 )
    {
        ret = poll( fds, user_counter+1, -1 );
        if ( ret < 0 )
        {
            printf( "poll failure\n" );
            break;
        }
    
        for( int i = 0; i < user_counter+1; ++i )
        {
            if( ( fds[i].fd == listenfd ) && ( fds[i].revents & POLLIN ) )
            {
                struct sockaddr_in client_address;
                socklen_t client_addrlength = sizeof( client_address );
                int connfd = accept( listenfd, ( struct sockaddr* )&client_address, &client_addrlength );
                if ( connfd < 0 )
                {
                    printf( "errno is: %d\n", errno );
                    continue;
                }
                //请求太多。关闭新到连接。
                if( user_counter >= USER_LIMIT )
                {
                    const char* info = "too many users\n";
                    printf( "%s", info );
                    send( connfd, info, strlen( info ), 0 );
                    close( connfd );
                    continue;
                }
                //只要fd == listenfd，就是新连接，修改fds和数组。
                //但是哪里写进去的呢？
                //poll( fds, user_counter+1, -1 );这里写进去
                user_counter++;
                users[connfd].address = client_address;
                setnonblocking( connfd );
                fds[user_counter].fd = connfd;
                fds[user_counter].events = POLLIN | POLLRDHUP | POLLERR;
                fds[user_counter].revents = 0;
                printf( "comes a new user, now have %d users\n", user_counter );
            }
            else if( fds[i].revents & POLLERR )
            {
                printf( "get an error from %d\n", fds[i].fd );
                char errors[ 100 ];
                memset( errors, '\0', 100 );
                socklen_t length = sizeof( errors );
                if( getsockopt( fds[i].fd, SOL_SOCKET, SO_ERROR, &errors, &length ) < 0 )
                {
                    printf( "get socket option failed\n" );
                }
                continue;
            }
            else if( fds[i].revents & POLLRDHUP )
            {   
                //断开连接，要管理用户连接和连接数目。
                users[fds[i].fd] = users[fds[user_counter].fd];
                close( fds[i].fd );
                fds[i] = fds[user_counter];
                i--;
                user_counter--;
                printf( "a client left\n" );
            }
            else if( fds[i].revents & POLLIN )
            {   
                //正常读
                int connfd = fds[i].fd;
                memset( users[connfd].buf, '\0', BUFFER_SIZE );
                ret = recv( connfd, users[connfd].buf, BUFFER_SIZE-1, 0 );
                printf( "get %d bytes of client data %s from %d\n", ret, users[connfd].buf, connfd );
                if( ret < 0 )
                {
                    if( errno != EAGAIN )
                    {
                        close( connfd );
                        users[fds[i].fd] = users[fds[user_counter].fd];
                        fds[i] = fds[user_counter];
                        i--;
                        user_counter--;
                    }
                }
                else if( ret == 0 )
                {
                    printf( "code should not come to here\n" );
                }
                else
                {   
                    //收到客户数据，通知其他socket连接准备写数据。
                    for( int j = 1; j <= user_counter; ++j )
                    {
                        if( fds[j].fd == connfd )
                        {
                            continue;
                        }
                        
                        fds[j].events |= ~POLLIN;
                        fds[j].events |= POLLOUT;
                        users[fds[j].fd].write_buf = users[connfd].buf;
                    }
                }
            }
            else if( fds[i].revents & POLLOUT )
            {
                int connfd = fds[i].fd;
                if( ! users[connfd].write_buf )
                {
                    continue;
                }
                ret = send( connfd, users[connfd].write_buf, strlen( users[connfd].write_buf ), 0 );
                users[connfd].write_buf = NULL;
                fds[i].events |= ~POLLOUT;
                fds[i].events |= POLLIN;
            }
        }
    }

    delete [] users;
    close( listenfd );
    return 0;
}

```

#### 9.7 同时处理TCP  和UDP

设置两个socket，不同对应不同操作

```cpp
for ( int i = 0; i < number; i++ )
        {
            int sockfd = events[i].data.fd;
            if ( sockfd == listenfd )
            {
                struct sockaddr_in client_address;
                socklen_t client_addrlength = sizeof( client_address );
                int connfd = accept( listenfd, ( struct sockaddr* )&client_address, &client_addrlength );
                addfd( epollfd, connfd );
            }
            else if ( sockfd == udpfd )
            {
                char buf[ UDP_BUFFER_SIZE ];
                memset( buf, '\0', UDP_BUFFER_SIZE );
                struct sockaddr_in client_address;
                socklen_t client_addrlength = sizeof( client_address );

                ret = recvfrom( udpfd, buf, UDP_BUFFER_SIZE-1, 0, ( struct sockaddr* )&client_address, &client_addrlength );
                if( ret > 0 )
                {
                    sendto( udpfd, buf, UDP_BUFFER_SIZE-1, 0, ( struct sockaddr* )&client_address, client_addrlength );
                }
            }
```



## 第十章 信号

### 网络编程相关信号

SIGHUP 信号：挂起进程的控制终端，SIGHUP信号将触发。

SIGPIPE 信号：关闭管道

SIGURG 信号：内核通知应用程序带外数据到达：1.select或poll或者epoll等复用。

2.信号处理

## 第十一章 定时器

#### 定时器

Linux提供三种定时方法：

socket选项中so_rvtimeo and so_sendtimeo

用于receive类函数和send类函数

#### SIGALRM信号

基于升序链表的定时器

定时器至少包括：

1. 一个超时时间
2. 一个任务回调函数

用链表串联所有定时器就还需要next指向下一个定时器的指针成员。

##### 	处理非活动连接

1.可以用socket中的KEEPALIVE的机制管理所有长时间处于非活动状态的连接。

2.在应用层实现类似机制，管理所有非活动连接。

其实定时器很简单，就是连接在定时时间内完成工作，当定时时间过去后，发现连接是处于闲置状态，就关闭连接。否则，延长工作时间。

### 超时参数

### 高性能定时器

#### 时间轮

​	因为基于排序链表得定时器添加效率很低。

![](D:\电子书\网络编程相关笔记\picture\时间轮.png)



原先得排序链表通过管理唯一一条链表进行管理定时器。

时间轮使用的哈希表思想，

每一个定时器链表定时时间相差N*si 的整数倍。

![](D:\电子书\网络编程相关笔记\picture\定时器存放位置.png)

简单时间轮--->一个轮子的实现。

```cpp
//定时器设计
class tw_timer
{
public:
    tw_timer( int rot, int ts ) 
    : next( NULL ), prev( NULL ), rotation( rot ), time_slot( ts ){}

public:
	//位置和第几轮生效
    int rotation;
    int time_slot;
    //回调函数
    void (*cb_func)( client_data* );
    //客户数据
    client_data* user_data;
    tw_timer* next;
    tw_timer* prev;
};
```

```cpp
//时间轮
class time_wheel
{
public:
    time_wheel() : cur_slot( 0 )
    {
        for( int i = 0; i < N; ++i )
        {
            slots[i] = NULL;
        }
    }
    ~time_wheel()
    {
        for( int i = 0; i < N; ++i )
        {
            tw_timer* tmp = slots[i];
            while( tmp )
            {
                slots[i] = tmp->next;
                delete tmp;
                tmp = slots[i];
            }
        }
    }
    tw_timer* add_timer( int timeout )
    {
        if( timeout < 0 )
        {
            return NULL;
        }
        int ticks = 0;
        if( timeout < TI )
        {
            ticks = 1;
        }
        else
        {
            ticks = timeout / TI;
        }
        int rotation = ticks / N;
        int ts = ( cur_slot + ( ticks % N ) ) % N;
        tw_timer* timer = new tw_timer( rotation, ts );
        if( !slots[ts] )
        {
            printf( "add timer, rotation is %d, ts is %d, cur_slot is %d\n", rotation, ts, cur_slot );
            slots[ts] = timer;
        }
        else
        {
            timer->next = slots[ts];
            slots[ts]->prev = timer;
            slots[ts] = timer;
        }
        return timer;
    }
    void del_timer( tw_timer* timer )
    {
        if( !timer )
        {
            return;
        }
        int ts = timer->time_slot;
        if( timer == slots[ts] )
        {
            slots[ts] = slots[ts]->next;
            if( slots[ts] )
            {
                slots[ts]->prev = NULL;
            }
            delete timer;
        }
        else
        {
            timer->prev->next = timer->next;
            if( timer->next )
            {
                timer->next->prev = timer->prev;
            }
            delete timer;
        }
    }
    void tick()
    {
        tw_timer* tmp = slots[cur_slot];
        printf( "current slot is %d\n", cur_slot );
        while( tmp )
        {
            printf( "tick the timer once\n" );
            if( tmp->rotation > 0 )
            {
                tmp->rotation--;
                tmp = tmp->next;
            }
            else
            {
                tmp->cb_func( tmp->user_data );
                if( tmp == slots[cur_slot] )
                {
                    printf( "delete header in cur_slot\n" );
                    slots[cur_slot] = tmp->next;
                    delete tmp;
                    if( slots[cur_slot] )
                    {
                        slots[cur_slot]->prev = NULL;
                    }
                    tmp = slots[cur_slot];
                }
                else
                {
                    tmp->prev->next = tmp->next;
                    if( tmp->next )
                    {
                        tmp->next->prev = tmp->prev;
                    }
                    tw_timer* tmp2 = tmp->next;
                    delete tmp;
                    tmp = tmp2;
                }
            }
        }
        cur_slot = ++cur_slot % N;
    }

private:
    static const int N = 60;
    static const int TI = 1; 
    tw_timer* slots[N];
    int cur_slot;
};
```

时间轮其实就是基于哈希表实现的一个定时设置，对于定时器的修改时间删除时间都是o（1）

## 第十三章 多进程编程

#### 13.1 fork 和exec 

fork是复制映像。exec是替换映像

fork在父进程中返回 子进程的PID .子进程返回0.

所以在函数中，靠这个判断是子进程还是父进程。

分配新的内存和数据复制。文件描述符引用数加一。



exec函数是替换父进程，父进程的状态子进程不保存。

#### 13.3 僵尸进程

当子进程运行之后，父进程读取其退出状态之前，处于僵尸态。

父进程结束或者异常终止，子进程继续运行，此时init进程接管所有该子进程。

这些都是僵尸进程。

所以加入了两个wait函数

![](D:\电子书\网络编程相关笔记\picture\僵尸进程控制.png)

 1. wait 函数 会一直阻塞，等到返回某个子进程的PID ，并将子进程的退出状态信息存储在内存中/，这个子进程是随机的。

 2. waitpid 函数是非阻塞型，只监听对应PID的子进程。

    对应子进程的完整控制：

    ![](D:\电子书\网络编程相关笔记\picture\防止僵尸进程的处理.png)

### 进程间通信

#### 13.4 管道 pipe

![](D:\电子书\网络编程相关笔记\picture\管道.png)

sockpair 对比于pipe 来说，更加的好，因为pipe只允许单工，一个方向的数据传输。

​	缺点：只能关联到有关系的两个进程之间的通信。

#### 13.5 信号量

对于信号量的操作总结成

 1.P操作，信号量大于0 .就减一，等于0.就挂起进程。

2.V操作，如果有其他进程等待SV挂起，则唤醒，没有，SV+1;.

![](D:\电子书\网络编程相关笔记\picture\信号量的使用.png)



#### 13.6 共享内存

最高效的IPC机制，不涉及到进程之间的任何数据传输。所以需要用其他方法来保证共享内存的使用，避免产生竞态条件。

4个系统调用：shmget , shmat , shmdt, shmctl.

1. shmget 成功返回一个正整数值，是共享内存的标识符

2. 共享内存创建或者获取后，我们不能立刻访问，要关联到进程的地址空间，使用完还需要从进程地址空间中分离。shmat , shmdt函数就是这个作用。

   首先关联地址一般为空，让操作系统控制，保证代码移植性。

   如果是空的地址，该这么用shmdt呢。

3. shmctl 控制共享内存属性。

   主要是command属性的选择。

##### 共享内存的posix方法

​	之前用的mmap函数，其实就是一种共享内存的方法。

shm_open 方法



#### 13.7 消息队列

​	两个进程间传递二进制块数据的一个方式/

#### 13.9 在进程间传递文件描述符

​	父进程打开的文件描述符，在子进程中，其实不是对应一样的文件描述符，而是一个新的文件描述符，然后，这个文件描述符和被传递的文件描述符指向同样文件。

相反怎么传递呢？

​	用管道！

```cpp
int main()
{
    int pipefd[2];
    int fd_to_pass = 0;
	//创建父子进程的管道。
    int ret = socketpair( PF_UNIX, SOCK_DGRAM, 0, pipefd );
    assert( ret != -1 );

    pid_t pid = fork();
    assert( pid >= 0 );
	//子进程工作
    if ( pid == 0 )
    {
        close( pipefd[0] );
        fd_to_pass = open( "test.txt", O_RDWR, 0666 );
        send_fd( pipefd[1], ( fd_to_pass > 0 ) ? fd_to_pass : 0 );
        close( fd_to_pass );
        exit( 0 );
    }

    close( pipefd[1] );
    fd_to_pass = recv_fd( pipefd[0] );
    char buf[1024];
    memset( buf, '\0', 1024 );
    read( fd_to_pass, buf, 1024 );
    printf( "I got fd %d and data %s\n", fd_to_pass, buf );
    close( fd_to_pass );
}

```

接受fd描述符

```cpp
int recv_fd( int fd )
{
    struct iovec iov[1];
    struct msghdr msg;
    char buf[0];

    iov[0].iov_base = buf;
    iov[0].iov_len = 1;
    msg.msg_name    = NULL;
    msg.msg_namelen = 0;
    msg.msg_iov     = iov;
    msg.msg_iovlen = 1;

    cmsghdr cm;
    msg.msg_control = &cm;//辅助数据
    msg.msg_controllen = CONTROL_LEN;

    recvmsg( fd, &msg, 0 );

    int fd_to_read = *(int *)CMSG_DATA( &cm );
    return fd_to_read;
}
```

发送fd，fd是socket，fd_to_send 是文件描述符/

```cpp
void send_fd( int fd, int fd_to_send )
{
    struct iovec iov[1];
    struct msghdr msg;
    char buf[0];

    iov[0].iov_base = buf;
    iov[0].iov_len = 1;
    msg.msg_name    = NULL;
    msg.msg_namelen = 0;
    msg.msg_iov     = iov;
    msg.msg_iovlen = 1;

    cmsghdr cm;
    cm.cmsg_len = CONTROL_LEN;
    cm.cmsg_level = SOL_SOCKET;
    cm.cmsg_type = SCM_RIGHTS;
    *(int *)CMSG_DATA( &cm ) = fd_to_send;
    msg.msg_control = &cm;//辅助数据
    msg.msg_controllen = CONTROL_LEN;

    sendmsg( fd, &msg, 0 );
}

```



## 第十四章 多线程编程

POSIX 线程，线程库来自NPTL。

​	创建线程和结束线程

​	读取和设置线程属性

​	POSIX线程同步方式：POSIX信号量，互斥锁，条件变量。

### 14.1 线程概述

​	内核线程和用户线程的区别和联系。

​	进程中的一个内核线程获得CPU使用权，就加载并运行一个用户线程。

​	线程实现模式有三种：完全在用户空间实现，完全由内核调度，双层调度。

		1.	由线程库负责管理所有执行线程。好处是不占额外的内核资源，一个进程创建了很多线程，都不会对系统性能造成影响。多线程在外部看来优先级一样，内核线程就是进程本身。缺点是多处理器系统，一个进程的多个线程无法运行在不同的CPU上，
  		2.	第二种是完全由内核分配管理。与第一相反。
                		3.	两层就是混合体，内核调度M个内核线程，线程库调度N个用户线程，

线程库 NPTL 优势：

1. 内核线程不再是一个线程，避免了用进程模拟线程的语义问题。
2. 由内核统一管理线程工作
3. 一个进程的不同线程可以工作在不同CPU。
4. 线程同步由内核完成。

### 14.2 创建线程和结束线程

pthread_create ：

![](D:\电子书\网络编程相关笔记\picture\pthread_create.png)

​	thread 参数是 新线程的标识符，

第三为新线程将运行的函数和参数。

pthread_exit ： 

​	线程退出，内核调度内核线程安全退出。

pthread_join ：

​	一个进程中所有线程都可以调用这个函数来回收其他线程。

一直阻塞等到被回收的线程结束为止。成功返回0，失败返回错误码。

pthread_cancel:

​	异常终止线程，接收到取消请求的目标线程可以决定是否允许被取消以及如何取消。

​	![](D:\电子书\网络编程相关笔记\picture\异常线程取消方式.png)

### 14.3 线程属性

### 14.4 POSIX信号量

​	注意到同步问题，仅是pthread_join 线程同步 不够。

用 POSIX 信号量，互斥量，条件变量 进行同步。

#### POSIX 信号量   sem_ 开头的信号量。

![](D:\电子书\网络编程相关笔记\picture\POSIX 信号量.png)

#### 互斥量

互斥锁-----mutex，是一个互斥量

![](D:\电子书\网络编程相关笔记\picture\互斥锁.png)

linux支持4种互斥锁：

1. PTHREAD_MUTEX_NORMAL , 普通锁

   容易出现死锁。当一个线程对一个普通锁加锁后，其余请求该锁的线程形成队列等待。

2. PTHREAD_MUTEX_ERRORCHECK ,检错锁

   但往加锁的检错锁再加锁的时候，就会报错。

1. PTHREAD_MUTEX_RECURSIVE , 嵌套锁

   允许多次加锁解锁过程。但是不允许对已经解锁的嵌套锁解锁，或对其他线程加锁的嵌套锁解锁。

2. PTHREAD_MUTEX_DEFAULT , 默认锁

   就是映射到上面的三种锁之一。

死锁代码：

```cpp
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

int a = 0;
int b = 0;
pthread_mutex_t mutex_a;
pthread_mutex_t mutex_b;

void* another( void* arg )
{
    pthread_mutex_lock( &mutex_b );
    printf( "in child thread, got mutex b, waiting for mutex a\n" );
    sleep( 5 );
    ++b;
    pthread_mutex_lock( &mutex_a );
    b += a++;
    pthread_mutex_unlock( &mutex_a );
    pthread_mutex_unlock( &mutex_b );
    pthread_exit( NULL );
}

int main()
{
    pthread_t id;
    
    pthread_mutex_init( &mutex_a, NULL );
    pthread_mutex_init( &mutex_b, NULL );
    pthread_create( &id, NULL, another, NULL );

    pthread_mutex_lock( &mutex_a );
    printf( "in parent thread, got mutex a, waiting for mutex b\n" );
    sleep( 5 );
    ++a;
    pthread_mutex_lock( &mutex_b );
    a += b++;
    pthread_mutex_unlock( &mutex_b );
    pthread_mutex_unlock( &mutex_a );

    pthread_join( id, NULL );
    pthread_mutex_destroy( &mutex_a );
    pthread_mutex_destroy( &mutex_b );
    return 0;
}

```

#### 条件变量

![](D:\电子书\网络编程相关笔记\picture\条件变量.png)

互斥锁指的是同步线程对于共享数据的访问。条件变量用于在线程之间同步共享数据值。

condition，cond_init

cond_broadcast 以广播的形式唤醒所有等待目标条件变量的线程，至于哪个线程被唤醒，取决于调度和线程优先级。

如何唤醒特定的线程，定义一个全局变量识别目标线程，采用广播形式唤醒，然后每个线程自己判断。

### 14.7 线程同步机制包装类

```cpp
#ifndef LOCKER_H
#define LOCKER_H

#include <exception>
#include <pthread.h>
#include <semaphore.h>
//信号量
class sem
{
public:
    sem()
    {
        if( sem_init( &m_sem, 0, 0 ) != 0 )
        {
            throw std::exception();
        }
    }
    ~sem()
    {
        sem_destroy( &m_sem );
    }
    bool wait()
    {
        return sem_wait( &m_sem ) == 0;
    }
    bool post()
    {
        return sem_post( &m_sem ) == 0;
    }

private:
    sem_t m_sem;
};
//互斥锁
class locker
{
public:
    locker()
    {
        if( pthread_mutex_init( &m_mutex, NULL ) != 0 )
        {
            throw std::exception();
        }
    }
    ~locker()
    {
        pthread_mutex_destroy( &m_mutex );
    }
    //获取锁
    bool lock()
    {
        return pthread_mutex_lock( &m_mutex ) == 0;
    }
    //释放锁
    bool unlock()
    {
        return pthread_mutex_unlock( &m_mutex ) == 0;
    }

private:
    pthread_mutex_t m_mutex;
};
//条件变量
class cond
{
public:
    //创建并初始化条件变量
    cond()
    {
        if( pthread_mutex_init( &m_mutex, NULL ) != 0 )
        {
            throw std::exception();
        }
        if ( pthread_cond_init( &m_cond, NULL ) != 0 )
        {
            pthread_mutex_destroy( &m_mutex );
            throw std::exception();
        }
    }
    ~cond()
    {
        pthread_mutex_destroy( &m_mutex );
        pthread_cond_destroy( &m_cond );
    }
    bool wait()
    {
        int ret = 0;
        pthread_mutex_lock( &m_mutex );
        ret = pthread_cond_wait( &m_cond, &m_mutex );
        pthread_mutex_unlock( &m_mutex );
        return ret == 0;
    }
    bool signal()
    {
        //唤醒等待条件变量的线程
        return pthread_cond_signal( &m_cond ) == 0;
    }

private:
    pthread_mutex_t m_mutex;
    pthread_cond_t m_cond;
};

#endif

```

#### 14.8 多线程环境

##### 可重入函数

线程安全的函数为可重入函数，多线程程序中调用库函数，必须使用可重入版本。否则无法控制。

##### 进程和线程	

当父进程的某个线程调用fork函数的时候，子进程不会拥有和父进程一样多的线程，只有一个执行线程，和父进程一样。但是继承父进程的所有互斥锁，条件变量等，所有容易出现死锁。

```cpp
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <wait.h>

pthread_mutex_t mutex;

void* another( void* arg )
{
    printf( "in child thread, lock the mutex\n" );
    //工作线程先上锁
    pthread_mutex_lock( &mutex );
    sleep( 5 );
    pthread_mutex_unlock( &mutex );
}

void prepare()
{
    pthread_mutex_lock( &mutex );
}

void infork()
{
    pthread_mutex_unlock( &mutex );
}

int main()
{
    pthread_mutex_init( &mutex, NULL );
    pthread_t id;
    pthread_create( &id, NULL, another, NULL );
    
    //pthread_atfork( prepare, infork, infork );
    sleep( 1 );
    int pid = fork();
    if( pid < 0 )
    {
        pthread_join( id, NULL );
        pthread_mutex_destroy( &mutex );
        return 1;
    }
    else if( pid == 0 )
    {
        printf( "I anm in the child, want to get the lock\n" );
        //这里会一直阻塞，因为这个互斥锁是另一个线程锁住的，在生成子进程过程中，这个状态保持下去，但是子进程中的线程没有解锁。
        pthread_mutex_lock( &mutex );
        printf( "I can not run to here, oop...\n" );
        pthread_mutex_unlock( &mutex );
        exit( 0 );
    }
    else
    {
        pthread_mutex_unlock( &mutex );
        wait( NULL );
    }
    pthread_join( id, NULL );
    pthread_mutex_destroy( &mutex );
    return 0;
}

```

加上了phtread_atfork 函数 之后， 这个函数可以让子进程自己执行函数，也可以让父进程自己执行函数。

![](D:\电子书\网络编程相关笔记\picture\pthread_atfork.png)

##### 线程和信号

## 第十五章 进程池和线程池

### 15.3 半同步/半异步进程池实现

​		避免父，子进程之间传递文件描述符，把接受新连接的操作放到子进程中，一个客户连接上的所有任务始终由一个子进程处理。

基础进程类：

```cpp
class process
{
public:
    process() : m_pid( -1 ){}

public:
//目标子进程的PID 和 m_pipefd 是父进程和子进程通信用的管道。
    pid_t m_pid;
    int m_pipefd[2];
};
```

进程池的设计：

```cpp
template< typename T >
class processpool
{
private:
    processpool( int listenfd, int process_number = 8 );
public:
    //把构造函数定义成私有。这样就能保证只能通过后面的create静态函数来创建processpool实例
    static processpool< T >* create( int listenfd, int process_number = 8 )
    {
        //m_instance进程池静态实例。再下面设计成null，再调用之前生成进程池。
        if( !m_instance )
        {
            m_instance = new processpool< T >( listenfd, process_number );
        }
        return m_instance;
    }
    ~processpool()
    {
        delete [] m_sub_process;
    }

    void run();

private:
    void setup_sig_pipe();
    void run_parent();
    void run_child();

private:
    static const int MAX_PROCESS_NUMBER = 16;
    static const int USER_PER_PROCESS = 65536;
    static const int MAX_EVENT_NUMBER = 10000;
    int m_process_number;
    int m_idx;
    int m_epollfd;
    int m_listenfd;
    int m_stop;
    process* m_sub_process;
    static processpool< T >* m_instance;
};
```

信号管道

```cpp
static int sig_pipefd[2];
```

进程池构造函数，进程的生成，并建立他们和父进程的管道：

```cpp
template< typename T >
processpool< T >::processpool( int listenfd, int process_number ) 
    : m_listenfd( listenfd ), m_process_number( process_number ), m_idx( -1 ), m_stop( false )
{
    assert( ( process_number > 0 ) && ( process_number <= MAX_PROCESS_NUMBER ) );

    m_sub_process = new process[ process_number ];
    assert( m_sub_process );

    for( int i = 0; i < process_number; ++i )
    {
        //生成管道。不用pipe因为这个是全双工管道。
        int ret = socketpair( PF_UNIX, SOCK_STREAM, 0, m_sub_process[i].m_pipefd );
        assert( ret == 0 );
        //生成子进程
        m_sub_process[i].m_pid = fork();
        assert( m_sub_process[i].m_pid >= 0 );
        if( m_sub_process[i].m_pid > 0 )
        {
            close( m_sub_process[i].m_pipefd[1] );
            continue;
        }
        else
        {
            close( m_sub_process[i].m_pipefd[0] );
            m_idx = i;
            break;
        }
    }
}
```

统一事件源且创建epoll事件监听表和信号管道

```CPP
static void addsig( int sig, void( handler )(int), bool restart = true )
{
    struct sigaction sa;
    memset( &sa, '\0', sizeof( sa ) );
    sa.sa_handler = handler;
    if( restart )
    {
        sa.sa_flags |= SA_RESTART;
    }
    sigfillset( &sa.sa_mask );
    assert( sigaction( sig, &sa, NULL ) != -1 );
}

static void sig_handler( int sig )
{
    int save_errno = errno;
    int msg = sig;
    send( sig_pipefd[1], ( char* )&msg, 1, 0 );
    errno = save_errno;
}

template< typename T >
void processpool< T >::setup_sig_pipe()
{
    //创建epoll事件监听表和信号管道
    m_epollfd = epoll_create( 5 );
    assert( m_epollfd != -1 );

    int ret = socketpair( PF_UNIX, SOCK_STREAM, 0, sig_pipefd );
    assert( ret != -1 );

    setnonblocking( sig_pipefd[1] );
    addfd( m_epollfd, sig_pipefd[0] );
	
    //信号处理函数
    addsig( SIGCHLD, sig_handler );
    addsig( SIGTERM, sig_handler );
    addsig( SIGINT, sig_handler );
    addsig( SIGPIPE, SIG_IGN );
}
```

注册fd

```cpp
static void addfd( int epollfd, int fd )
{
    epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN | EPOLLET;
    epoll_ctl( epollfd, EPOLL_CTL_ADD, fd, &event );
    setnonblocking( fd );
}
```

run_child 函数

```cpp
template< typename T >
void processpool< T >::run_child()
{
    setup_sig_pipe();
	//找到该子进程和父进程相对应的管道。
    int pipefd = m_sub_process[m_idx].m_pipefd[ 1 ];
    //子进程监听epollfd注册的内核事件表中的pipefd，父进程通知它accpect新连接
    addfd( m_epollfd, pipefd );

    epoll_event events[ MAX_EVENT_NUMBER ];
    T* users = new T [ USER_PER_PROCESS ];
    assert( users );
    int number = 0;
    int ret = -1;
	//停止信号
    while( ! m_stop )
    {
        number = epoll_wait( m_epollfd, events, MAX_EVENT_NUMBER, -1 );
        if ( ( number < 0 ) && ( errno != EINTR ) )
        {
            printf( "epoll failure\n" );
            break;
        }
		//要处理的事件，从父子进程中的管道读取数据。
        for ( int i = 0; i < number; i++ )
        {
            int sockfd = events[i].data.fd;
            if( ( sockfd == pipefd ) && ( events[i].events & EPOLLIN ) )
            {
                int client = 0;
                //接收管道的数据。并保存再client中，如果读取成功，表示由新客户连接到来。，读出的是ip地址。
                ret = recv( sockfd, ( char* )&client, sizeof( client ), 0 );
                if( ( ( ret < 0 ) && ( errno != EAGAIN ) ) || ret == 0 ) 
                {
                    continue;
                }
                else
                {
                    struct sockaddr_in client_address;
                    socklen_t client_addrlength = sizeof( client_address );
                    //这里的listenfd由父进程传来
                    int connfd = accept( m_listenfd, ( struct sockaddr* )&client_address, &client_addrlength );
                    if ( connfd < 0 )
                    {
                        printf( "errno is: %d\n", errno );
                        continue;
                    }
                    addfd( m_epollfd, connfd );
                    //模板类T必须实现init方法。以初始化一个客户连接，这里直接使用connfd来索引逻辑处理对象，提高程序效率。
                    users[connfd].init( m_epollfd, connfd, client_address );
                }
            }
            else if( ( sockfd == sig_pipefd[0] ) && ( events[i].events & EPOLLIN ) )
            {
                int sig;
                char signals[1024];
                ret = recv( sig_pipefd[0], signals, sizeof( signals ), 0 );
                if( ret <= 0 )
                {
                    continue;
                }
                else
                {
                    for( int i = 0; i < ret; ++i )
                    {
                        switch( signals[i] )
                        {
                            case SIGCHLD:
                            {
                                pid_t pid;
                                int stat;
                                while ( ( pid = waitpid( -1, &stat, WNOHANG ) ) > 0 )
                                {
                                    continue;
                                }
                                break;
                            }
                            case SIGTERM:
                            case SIGINT:
                            {
                                m_stop = true;
                                break;
                            }
                            default:
                            {
                                break;
                            }
                        }
                    }
                }
            }
            else if( events[i].events & EPOLLIN )
            {
                 users[sockfd].process();
            }
            else
            {
                continue;
            }
        }
    }

    delete [] users;
    users = NULL;
    close( pipefd );
    //close( m_listenfd );、
    //这里的意思是提醒我们：应该由m_listenfd的创建者来关闭文件描述符，对象（比如一个文件描述符，或者一段堆内存）由哪个函数创建，就应该由哪个函数销毁。
    close( m_epollfd );
}
```

run_parent

//如果新连接到来，使用round robin分配到子进程管理。

父进程如何处理?



```cpp

template< typename T >
void processpool< T >::run_parent()
{
    setup_sig_pipe();

    addfd( m_epollfd, m_listenfd );

    epoll_event events[ MAX_EVENT_NUMBER ];
    int sub_process_counter = 0;
    int new_conn = 1;
    int number = 0;
    int ret = -1;

    while( ! m_stop )
    {
        number = epoll_wait( m_epollfd, events, MAX_EVENT_NUMBER, -1 );
        if ( ( number < 0 ) && ( errno != EINTR ) )
        {
            printf( "epoll failure\n" );
            break;
        }

        for ( int i = 0; i < number; i++ )
        {
            int sockfd = events[i].data.fd;
            if( sockfd == m_listenfd )
            {	
                //如果新连接到来，使用round robin分配到子进程管理。
                int i =  sub_process_counter;
                do
                {
                    if( m_sub_process[i].m_pid != -1 )
                    {
                        break;
                    }
                    i = (i+1)%m_process_number;
                }
                while( i != sub_process_counter );
                
                if( m_sub_process[i].m_pid == -1 )
                {
                    m_stop = true;
                    break;
                }
                sub_process_counter = (i+1)%m_process_number;
                //send( m_sub_process[sub_process_counter++].m_pipefd[0], ( char* )&new_conn, sizeof( new_conn ), 0 );
                send( m_sub_process[i].m_pipefd[0], ( char* )&new_conn, sizeof( new_conn ), 0 );
                printf( "send request to child %d\n", i );
                //sub_process_counter %= m_process_number;
            }
            else if( ( sockfd == sig_pipefd[0] ) && ( events[i].events & EPOLLIN ) )
            {
                int sig;
                char signals[1024];
                ret = recv( sig_pipefd[0], signals, sizeof( signals ), 0 );
                if( ret <= 0 )
                {
                    continue;
                }
                else
                {
                    for( int i = 0; i < ret; ++i )
                    {
                        switch( signals[i] )
                        {
                            case SIGCHLD:
                            {
                                pid_t pid;
                                int stat;
                                while ( ( pid = waitpid( -1, &stat, WNOHANG ) ) > 0 )
                                {
                                    for( int i = 0; i < m_process_number; ++i )
                                    {
                                        //关闭通信管道。在进程池追踪的第i个子进程退出。
                                        if( m_sub_process[i].m_pid == pid )
                                        {
                                            printf( "child %d join\n", i );
                                            close( m_sub_process[i].m_pipefd[0] );
                                            m_sub_process[i].m_pid = -1;
                                        }
                                    }
                                }
                                //全部关闭就退出。
                                m_stop = true;
                                for( int i = 0; i < m_process_number; ++i )
                                {
                                    if( m_sub_process[i].m_pid != -1 )
                                    {
                                        m_stop = false;
                                    }
                                }
                                break;
                            }
                            case SIGTERM:
                            case SIGINT:
                            {
                                //父进程接受到终止信号，杀死所有子进程。
                                printf( "kill all the clild now\n" );
                                for( int i = 0; i < m_process_number; ++i )
                                {
                                    int pid = m_sub_process[i].m_pid;
                                    if( pid != -1 )
                                    {
                                        kill( pid, SIGTERM );
                                    }
                                }
                                break;
                            }
                            default:
                            {
                                break;
                            }
                        }
                    }
                }
            }
            else
            {
                continue;
            }
        }
    }

    //close( m_listenfd );
    close( m_epollfd );
}
```

### 15.5 半同步/半反应堆线程池实现

特别点：

使用一个工作队列完全解除主线程和工作线程的耦合关系。

主线程往工作队列插入任务，工作线程竞争获得任务。

客户请求必须是无状态的，因为同一个连接不同请求会由不同线程处理。

//线程池类

```cpp
template< typename T >
class threadpool
{
public:
    //thread_number 是线程数量，max_requests 是请求队列总最多允许的等待处理的请求的数量。
    threadpool( int thread_number = 8, int max_requests = 10000 );
    ~threadpool();
    //请求队列添加任务。
    bool append( T* request );

private:
    //工作线程工作函数。取出任务，执行。
    static void* worker( void* arg );
    void run();

private:
    int m_thread_number;
    int m_max_requests;
    pthread_t* m_threads;
    std::list< T* > m_workqueue;
    locker m_queuelocker;//保护请求队列的互斥锁
    sem m_queuestat;//是否有任务要处理
    bool m_stop;
};
```

线程池构造函数：

```cpp
template< typename T >
threadpool< T >::threadpool( int thread_number, int max_requests ) : 
        m_thread_number( thread_number ), m_max_requests( max_requests ), m_stop( false ), m_threads( NULL )
{
    if( ( thread_number <= 0 ) || ( max_requests <= 0 ) )
    {
        throw std::exception();
    }

    m_threads = new pthread_t[ m_thread_number ];
    if( ! m_threads )
    {
        throw std::exception();
    }
	//创建线程，设置脱离线程。
    for ( int i = 0; i < thread_number; ++i )
    {
        printf( "create the %dth thread\n", i );
        //注意这里的创建
        if( pthread_create( m_threads + i, NULL, worker, this ) != 0 )
        {
            delete [] m_threads;
            //脱离线程
            throw std::exception();
        }
        if( pthread_detach( m_threads[i] ) )
        {
            delete [] m_threads;
            throw std::exception();
        }
    }
}
```

析构函数：

```cpp
template< typename T >
threadpool< T >::~threadpool()
{
    delete [] m_threads;
    m_stop = true;
}
```

主线程添加任务进工作队列

注意，在添加时候，要及时加锁。

```cpp
template< typename T >
bool threadpool< T >::append( T* request )
{	
    //上锁
    m_queuelocker.lock();
    //大于请求，直接舍弃。
    if ( m_workqueue.size() > m_max_requests )
    {
        m_queuelocker.unlock();
        return false;
    }
    m_workqueue.push_back( request );
    m_queuelocker.unlock();
    m_queuestat.post();
    return true;
}
```

工作线程工作函数

```
//线程池工作，调用run
template< typename T >
void* threadpool< T >::worker( void* arg )
{
    threadpool* pool = ( threadpool* )arg;
    pool->run();
    return pool;
}

template< typename T >
void threadpool< T >::run()
{
    while ( ! m_stop )
    {
        m_queuestat.wait();
        m_queuelocker.lock();
        if ( m_workqueue.empty() )
        {
            m_queuelocker.unlock();
            continue;
        }
        T* request = m_workqueue.front();
        m_workqueue.pop_front();
        m_queuelocker.unlock();
        if ( ! request )
        {
            continue;
        }
        request->process();
    }
}
```

pthread_create 函数第三个参数必须指向一个静态函数，而要在一个静态函数中使用类的动态成员（包括成员函数和成员变量）

​	将类的对象作为参数传递给该静态函数，然后在静态函数中引用这个对象，并调用其动态方法。

在这里是用this指针，然后work中获取指针，调用run。

### 15.6 线程池实现的简单web服务器

之前状态机模式的解析HTTP请求的服务器。现在重新实现一个并发的web服务器。

分为http_conn 类：头文件和实现文件。

