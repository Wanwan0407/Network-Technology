//#include"pcap.h"
//#define _WINSOCK_DEPRECATED_NO_WARNINGS
//#include <WinSock2.h>
//#include <Windows.h>
//#include<iostream>
//using namespace std;
//#pragma comment(lib, "packet.lib")
//#pragma comment(lib, "wpcap.lib")
//#pragma comment(lib,"ws2_32.lib")
//
//#pragma pack (1)
////进入字 节对齐方式
//typedef struct FrameHeader_t{
//	BYTE DesMAC[6];// 目的地址
//	BYTE SrcMAC[6];//源地址
//	WORD FrameType;//帧类型
//}FrameHeader_t;
//typedef struct IPHeader_t{
//	//IP首部
//	BYTE Ver_HLen;//IP协议版本和IP首部长度。高4位为版本，低4位为首部的长度(单位为4bytes)
//	BYTE TOS;//服务类型
//	WORD TotalLen;//IP包总长度
//	WORD ID;
//	WORD Flag_Segment; 
//	BYTE TTL;//一个网络层的网络数据包(package)的生存周期
//	BYTE Protocol;//协议
//	WORD Checksum;//校验和
//	ULONG SrcIP;//源地址
//	ULONG DstIP;//目标地址
//} IPHeader_t;
//typedef struct Data_t {
//	//包含帧首部和IP首部的数据包
//	FrameHeader_t FrameHeader;
//	IPHeader_t IPHeader;
//} Data_t;
//#pragma pack() //恢复缺省对齐方式
//
//void PrintEtherHeader(const u_char* packetData)
//{
//	struct FrameHeader_t* data;
//	data = (struct FrameHeader_t*)packetData;
//	//将一个16位数由网络字节顺序转换为主机字节顺序
//	u_short ether_type = ntohs(data->FrameType);  // 以太网类型
//	u_char* ether_src = data->SrcMAC;         // 以太网原始MAC地址
//	u_char* ether_dst = data->DesMAC;         // 以太网目标MAC地址
//
//	printf("类型: 0x%x \t", ether_type);
//	printf("原MAC地址: %02X:%02X:%02X:%02X:%02X:%02X \t",
//		ether_src[0], ether_src[1], ether_src[2], ether_src[3], ether_src[4], ether_src[5]);
//	printf("目标MAC地址: %02X:%02X:%02X:%02X:%02X:%02X \n",
//		ether_dst[0], ether_dst[1], ether_dst[2], ether_dst[3], ether_dst[4], ether_dst[5]);
//}
//
////void PrintIPHeader(const u_char* packetData) {
////	struct IPHeader_t* ip_protocol;
////
////	// +14 跳过数据链路层
////	ip_protocol = (struct IPHeader_t*)(packetData + 14);
////	SOCKADDR_IN Src_Addr, Dst_Addr = { 0 };
////
////	u_short check_sum = ntohs(ip_protocol->Checksum);
////	int ttl = ip_protocol->TTL;
////	int proto = ip_protocol->Protocol;
////
////	Src_Addr.sin_addr.s_addr = ip_protocol->SrcIP;
////	Dst_Addr.sin_addr.s_addr = ip_protocol->DstIP;
////
////	//printf("源地址: %15s --> ", inet_ntoa(Src_Addr.sin_addr));
////	//printf("目标地址: %15s --> ", inet_ntoa(Dst_Addr.sin_addr));
////	char buff1[17];
////	::inet_ntop(AF_INET, (const void*)&Src_Addr.sin_addr, buff1, 17);
////	printf("源地址: %s --> ", buff1);
////	char buff2[17];
////	::inet_ntop(AF_INET, (const void*)&Dst_Addr.sin_addr, buff2, 17);
////	printf("目标地址: %s --> ", buff2);
////	printf("校验和: %5X --> TTL: %4d --> 协议类型: ", check_sum, ttl);
////	switch (ip_protocol->Protocol)
////	{
////	case 1: printf("ICMP \n"); break;
////	case 2: printf("IGMP \n"); break;
////	case 6: printf("TCP \n");  break;
////	case 17: printf("UDP \n"); break;
////	case 89: printf("OSPF \n"); break;
////	default: printf("None \n"); break;
////	}
////}
//int main() {
//	//接口链表数据结构
//	pcap_if_t* alldevs;
//	pcap_if_t* d;
//	pcap_if_t* d1;
//	pcap_addr_t* a;
//	char errbuf[PCAP_ERRBUF_SIZE];
//	//获取设备列表
//	if (pcap_findalldevs_ex(PCAP_SRC_IF_STRING, NULL, &alldevs, errbuf) !=-1) {
//		cout << "获取设备列表成功" << endl;
//	}
//	else { cout << "获取设备列表失败" << endl; return 0; }
//	//显示获取的设备列表
//	int i1 = 1;
//	for (d1 = alldevs; d1 != NULL; d1 = d1->next) {
//		cout <<  i1 <<endl; i1++;
//		cout << "name: " << d1->name << endl;
//		cout << "description: " << d1->description << endl;
//		cout << "addresses: " << d1->addresses << endl;
//	}
//
//	int i = 1;
//	pcap_pkthdr* Packet_Header;    // 数据包头
//	const u_char* Packet_Data;
//	for (d = alldevs; d != NULL; d = d->next) {
//
//		pcap_if_t* pname = d;
//		//打开网络接口
//		pcap_t* handle = pcap_open(pname->name, 655340, PCAP_OPENFLAG_PROMISCUOUS, 1000, 0, 0);
//		//不初始化会报错
//		pcap_pkthdr* Packet_Header=NULL;    // 数据包头
//		const u_char* Packet_Data=NULL;    // 数据本身
//		
//		cout << i << " :"; i++;
//		int ex_value;
//		int k = 0;
//		while (k >= 0) {
//			//pcap_open 数据包基本信息 指向数据包
//			if ((ex_value = pcap_next_ex(handle, &Packet_Header, &Packet_Data)) == 1)
//			{
//				//if (retValue == 0) { continue; }
//				cout << "name: " << d->name << endl;
//				cout << "description: " << d->description << endl;
//				cout << "addresses: " << d->addresses << endl;
//				cout << "侦听长度: " << Packet_Header->len << endl;
//				//cout<<Packet_Data<<endl;
//				PrintEtherHeader(Packet_Data);
//				//PrintIPHeader(Packet_Data);
//				cout << endl;
//			}
//			else { k--; cout <<ex_value<< "超时" << endl; }
//		}
//	}
//	int num = i - 1;//接口总数
//	//释放设备列表
//	pcap_freealldevs(alldevs);
//}






#include"pcap.h"
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <Windows.h>
#include<iostream>
#include<cstring>
using namespace std;
#pragma comment(lib, "packet.lib")
#pragma comment(lib, "wpcap.lib")
#pragma comment(lib,"ws2_32.lib")

#define ETH_ARP         0x0806  //以太网帧类型表示后面数据的类型，对于ARP请求或应答来说，该字段的值为x0806
#define ARP_HARDWARE    1  //硬件类型字段值为表示以太网地址
#define ETH_IP          0x0800  //协议类型字段表示要映射的协议地址类型值为x0800表示IP地址
#define ARP_REQUEST     1   //ARP请求
#define ARP_REPLY       2      //ARP应答
#define HOSTNUM         255   //主机数量

#pragma pack (1)
//进入字 节对齐方式
typedef struct FrameHeader_t {
	BYTE DesMAC[6];// 目的地址
	BYTE SrcMAC[6];//源地址
	WORD FrameType;//帧类型
}FrameHeader_t;
typedef struct IPHeader_t {
	//IP首部
	BYTE Ver_HLen;//IP协议版本和IP首部长度。高4位为版本，低4位为首部的长度(单位为4bytes)
	BYTE TOS;//服务类型
	WORD TotalLen;//IP包总长度
	WORD ID;
	WORD Flag_Segment;
	BYTE TTL;//一个网络层的网络数据包(package)的生存周期
	BYTE Protocol;//协议
	WORD Checksum;//校验和
	ULONG SrcIP;//源地址
	ULONG DstIP;//目标地址
} IPHeader_t;
typedef struct Data_t {
	//包含帧首部和IP首部的数据包
	FrameHeader_t FrameHeader;
	IPHeader_t IPHeader;
} Data_t;
typedef struct ARPFrame_t {
	FrameHeader_t FrameHeader;//以太网帧头
	WORD HardwareType;//硬件类型
	WORD ProtocolType;//协议类型
	BYTE HLen;//硬件地址长度
	BYTE PLen;//协议地址长度
	WORD Operation;
	BYTE SendHa[6];	//发送端以太网地址
	DWORD SendIP;	//发送端IP地址
	BYTE RecvHa[6];	//目的以太网地址
	DWORD RecvIP;	//目的IP地址

} ARPFrame_t;
//帧头部结构体，共14字节
struct EthernetHeader
{
	u_char DestMAC[6];    //目的MAC地址 6字节
	u_char SourMAC[6];   //源MAC地址 6字节
	u_short EthType;         //上一层协议类型，如0x0800代表上一层是IP协议，0x0806为arp  2字节
};

//28字节ARP帧结构
struct Arpheader {
	unsigned short HardwareType; //硬件类型
	unsigned short ProtocolType; //协议类型
	unsigned char HardwareAddLen; //硬件地址长度
	unsigned char ProtocolAddLen; //协议地址长度
	unsigned short OperationField; //操作字段
	unsigned char SourceMacAdd[6]; //源mac地址
	unsigned long SourceIpAdd; //源ip地址
	unsigned char DestMacAdd[6]; //目的mac地址
	unsigned long DestIpAdd; //目的ip地址
};

//arp包结构
struct ArpPacket {
	EthernetHeader ed;
	Arpheader ah;
};

struct sparam {
	pcap_t* adhandle;
	char* ip;
	unsigned char* mac;
	char* netmask;
};
struct gparam {
	pcap_t* adhandle;
};

struct sparam sp;
struct gparam gp;
#pragma pack() //恢复缺省对齐方式

/* 将数字类型的IP地址转换成字符串类型的 */
#define IPTOSBUFFERS    12
char* iptos(u_long in)
{
	static char output[IPTOSBUFFERS][3 * 4 + 3 + 1];
	static short which;
	u_char* p;

	p = (u_char*)&in;
	which = (which + 1 == IPTOSBUFFERS ? 0 : which + 1);
	sprintf_s(output[which], "%d.%d.%d.%d", p[0], p[1], p[2], p[3]);
	return output[which];
}

//获取IP和子网掩码赋值为ip_addr和ip_netmask
void ifget(pcap_if_t* d, char* ip_addr, char* ip_netmask) {
	pcap_addr_t* a;
	//遍历所有的地址,a代表一个pcap_addr
	for (a = d->addresses; a; a = a->next) {
		switch (a->addr->sa_family) {
		case AF_INET:  //sa_family ：是2字节的地址家族，一般都是“AF_xxx”的形式。通常用的都是AF_INET。代表IPV4
			if (a->addr) {
				char* ipstr;
				//将地址转化为字符串
				ipstr = iptos(((struct sockaddr_in*)a->addr)->sin_addr.s_addr); //*ip_addr
				printf("ipstr:%s\n", ipstr);
				memcpy(ip_addr, ipstr, 16);
			}
			if (a->netmask) {
				char* netmaskstr;
				netmaskstr = iptos(((struct sockaddr_in*)a->netmask)->sin_addr.s_addr);
				printf("netmask:%s\n", netmaskstr);
				memcpy(ip_netmask, netmaskstr, 16);
			}
		case AF_INET6:
			break;
		}
	}
}

// 获取自己主机的MAC地址
int GetSelfMac(pcap_t* adhandle, const char* ip_addr, unsigned char* ip_mac) {
	unsigned char sendbuf[42]; //arp包结构大小
	int i = -1;
	int res;
	EthernetHeader eh; //以太网帧头
	Arpheader ah;  //ARP帧头
	struct pcap_pkthdr* pkt_header;
	const u_char* pkt_data;
	//将已开辟内存空间 eh.dest_mac_add 的首 6个字节的值设为值 0xff。
	memset(eh.DestMAC, 0xff, 6); //目的地址为全为广播地址
	memset(eh.SourMAC, 0x0f, 6);
	memset(ah.DestMacAdd, 0x0f, 6);
	memset(ah.SourceMacAdd, 0x00, 6);
	//htons将一个无符号短整型的主机数值转换为网络字节顺序
	eh.EthType = htons(ETH_ARP);
	ah.HardwareType = htons(ARP_HARDWARE);
	ah.ProtocolType = htons(ETH_IP);
	ah.HardwareAddLen = 6;
	ah.ProtocolAddLen = 4;
	ah.SourceIpAdd = inet_addr("100.100.100.100"); //随便设的请求方ip
	ah.OperationField = htons(ARP_REQUEST);
	ah.DestIpAdd = inet_addr(ip_addr);
	memset(sendbuf, 0, sizeof(sendbuf));
	memcpy(sendbuf, &eh, sizeof(eh));
	memcpy(sendbuf + sizeof(eh), &ah, sizeof(ah));
	printf("%s", sendbuf);
	if (pcap_sendpacket(adhandle, sendbuf, 42) == 0) {
		printf("\nPacketSend succeed\n");
	}
	else {
		printf("PacketSendPacket in getmine Error: %d\n", GetLastError());
		return 0;
	}
	//从interface或离线记录文件获取一个报文
	//pcap_next_ex(pcap_t* p,struct pcap_pkthdr** pkt_header,const u_char** pkt_data)
	while ((res = pcap_next_ex(adhandle, &pkt_header, &pkt_data)) >= 0) {
		if (*(unsigned short*)(pkt_data + 12) == htons(ETH_ARP)
			&& *(unsigned short*)(pkt_data + 20) == htons(ARP_REPLY)
			&& *(unsigned long*)(pkt_data + 38)
			== inet_addr("100.100.100.100")) {
			for (i = 0; i < 6; i++) {
				ip_mac[i] = *(unsigned char*)(pkt_data + 22 + i);
			}
			printf("获取自己主机的MAC地址成功!\n");
			break;
		}
	}
	if (i == 6) {
		return 1;
	}
	else {
		return 0;
	}
}

int main() {
	char* ip_addr;                  //IP地址
	char* ip_netmask;               //子网掩码
	unsigned char* ip_mac;          //本机MAC地址
	//为三个变量分配内存空间
	ip_addr = (char*)malloc(sizeof(char) * 16); //申请内存存放IP地址
	if (ip_addr == NULL)
	{
		printf("申请内存存放IP地址失败!\n");
		return -1;
	}
	ip_netmask = (char*)malloc(sizeof(char) * 16); //申请内存存放NETMASK地址
	if (ip_netmask == NULL)
	{
		printf("申请内存存放NETMASK地址失败!\n");
		return -1;
	}
	ip_mac = (unsigned char*)malloc(sizeof(unsigned char) * 6); //申请内存存放MAC地址
	if (ip_mac == NULL)
	{
		printf("申请内存存放MAC地址失败!\n");
		return -1;
	}


	//接口链表数据结构
	/*pcap_if_t* alldevs;
	pcap_if_t* d;
	pcap_if_t* d1;
	pcap_addr_t* a;
	char errbuf[PCAP_ERRBUF_SIZE];*/

	pcap_if_t* alldevs;				 //所有网络适配器
	pcap_if_t* d;                    //选中的网络适配器
	char errbuf[PCAP_ERRBUF_SIZE];   //错误缓冲区,大小为256
	pcap_t* adhandle;				//捕捉实例,是pcap_open返回的对象
	int i = 0;                       //适配器计数变量

	//获取本地适配器列表
	if (pcap_findalldevs_ex(PCAP_SRC_IF_STRING, NULL, &alldevs, errbuf) == -1) {
		//结果为-1代表出现获取适配器列表失败
		fprintf(stderr, "Error in pcap_findalldevs_ex:\n", errbuf);
		//exit(0)代表正常退出,exit(other)为非正常退出,这个值会传给操作系统
		exit(1);
	}


	for (d = alldevs; d != NULL; d = d->next) {
		printf("-----------------------------------------------------------------\nnumber:%d\nname:%s\n", ++i, d->name);
		if (d->description) {
			//打印适配器的描述信息
			printf("description:%s\n", d->description);
		}
		else {
			//适配器不存在描述信息
			printf("description:%s", "no description\n");
		}
		//打印本地环回地址
		printf("\tLoopback: %s\n", (d->flags & PCAP_IF_LOOPBACK) ? "yes" : "no");
		/**
		pcap_addr *  next     指向下一个地址的指针
		sockaddr *  addr       IP地址
		sockaddr *  netmask  子网掩码
		sockaddr *  broadaddr   广播地址
		sockaddr *  dstaddr        目的地址
		*/
		pcap_addr_t* a;       //网络适配器的地址用来存储变量
		for (a = d->addresses; a; a = a->next) {
			//sa_family代表了地址的类型,是IPV4地址类型还是IPV6地址类型
			switch (a->addr->sa_family)
			{
			case AF_INET:  //代表IPV4类型地址
				printf("Address Family Name:AF_INET\n");
				if (a->addr) {
					//->的优先级等同于括号,高于强制类型转换,因为addr为sockaddr类型，对其进行操作须转换为sockaddr_in类型
					printf("Address:%s\n", iptos(((struct sockaddr_in*)a->addr)->sin_addr.s_addr));
				}
				if (a->netmask) {
					printf("\tNetmask: %s\n", iptos(((struct sockaddr_in*)a->netmask)->sin_addr.s_addr));
				}
				if (a->broadaddr) {
					printf("\tBroadcast Address: %s\n", iptos(((struct sockaddr_in*)a->broadaddr)->sin_addr.s_addr));
				}
				if (a->dstaddr) {
					printf("\tDestination Address: %s\n", iptos(((struct sockaddr_in*)a->dstaddr)->sin_addr.s_addr));
				}
				break;
			case AF_INET6: //代表IPV6类型地址
				printf("Address Family Name:AF_INET6\n");
				printf("this is an IPV6 address\n");
				break;
			default:
				break;
			}
		}
	}
	//i为0代表上述循环未进入,即没有找到适配器,可能的原因为Winpcap没有安装导致未扫描到
	if (i == 0) {
		printf("interface not found,please check winpcap installation");
	}

	int num;
	printf("Enter the interface number(1-%d):", i);
	//让用户选择选择哪个适配器进行抓包
	scanf_s("%d", &num);
	printf("\n");

	//用户输入的数字超出合理范围
	if (num<1 || num>i) {
		printf("number out of range\n");
		pcap_freealldevs(alldevs);
		return -1;
	}
	//跳转到选中的适配器
	for (d = alldevs, i = 0; i < num - 1; d = d->next, i++);

	//运行到此处说明用户的输入是合法的
	if ((adhandle = pcap_open(d->name,        //设备名称
		65535,       //存放数据包的内容长度
		PCAP_OPENFLAG_PROMISCUOUS,  //混杂模式
		1000,           //超时时间
		NULL,          //远程验证
		errbuf         //错误缓冲
	)) == NULL) {
		//打开适配器失败,打印错误并释放适配器列表
		fprintf(stderr, "\nUnable to open the adapter. %s is not supported by WinPcap\n", d->name);
		// 释放设备列表 
		pcap_freealldevs(alldevs);
		return -1;
	}

	////获取设备列表
	//if (pcap_findalldevs_ex(PCAP_SRC_IF_STRING, NULL, &alldevs, errbuf) != -1) {
	//	cout << "获取设备列表成功" << endl;
	//}
	//else { cout << "获取设备列表失败" << endl; return 0; }
	////显示获取的设备列表
	//int i1 = 1;
	//for (d1 = alldevs; d1 != NULL; d1 = d1->next) {
	//	cout << i1 << endl; 
	//	cout << "name: " << d1->name << endl;
	//	cout << "description: " << d1->description << endl;
	//	cout << "addresses: " << d1->addresses << endl;

	//	for (a = d1->addresses; a != NULL; a = a->next) {
	//		if (a->addr->sa_family == AF_INET) //判断地址是否为IP地址
	//		{
	//			cout << a->addr->sa_data<<endl;
	//			cout << "a->addr: " << a->addr << endl;
	//			cout << "a->netmask: " << a->netmask << endl;
	//			cout << "a->broadaddr: " << a->broadaddr << endl;
	//			cout << "a->dstaddr: " << a->dstaddr << endl;
	//		}
	//	}
	//	if (i1 == 5) { break;}//选择本地网卡
	//	i1++;
	//}

	////打开第i1个网卡
	//pcap_if_t* pname = d1;
	////打开网络接口
	//pcap_t* handle = pcap_open(pname->name, 655340, PCAP_OPENFLAG_PROMISCUOUS, 1000, 0, 0);
	//int ex_value=0,k=0;
	//pcap_pkthdr* Packet_Header = NULL;    // 数据包头
	//const u_char* Packet_Data = NULL;    // 数据本身
	//while (k >= 0) {
	//	//pcap_open 数据包基本信息 指向数据包
	//	if ((ex_value = pcap_next_ex(handle, &Packet_Header, &Packet_Data)) == 1)
	//	{
	//		//if (retValue == 0) { continue; }
	//		cout << "name: " << d->name << endl;
	//		cout << "description: " << d->description << endl;
	//		cout << "addresses: " << d->addresses << endl;
	//		cout << "侦听长度: " << Packet_Header->len << endl;
	//		//cout<<Packet_Data<<endl;
	//		//PrintIPHeader(Packet_Data);
	//		cout << endl;
	//	}
	//	else { k--; cout << ex_value << "超时" << endl; }
	//}


	//ARPFrame_t ARPFrame;
	////ARPFrame .FrameHeader.DesMAC设置为广播地址
	//	for (int i = 0; i < 6; i++) {
	//		ARPFrame.FrameHeader.DesMAC[i] = 0xff; //表示广播
	//	}
	////ARPFrame.FrameHeader.SrcMAc 设置为本机网卡的MAC地址
	//	for (int i = 0; i < 6; i++) {
	//		ARPFrame.FrameHeader.SrcMAC[i] = 0x0f;
	//	}

	//ARPFrame.FrameHeader.FrameType = htons(0x0806); //

	//ARPFrame.HardwareType = htons(0x0001); //硬件类型为以太网
	//ARPFrame.ProtocolType = htons(0x0800); //协议类型为IP
	//ARPFrame.HLen = 6; //硬件地址长度为6
	//ARPFrame.PLen = 4; //协议地址长度为4
	//ARPFrame.Operation = htons(0x0001); //操作为ARP请求


	//	//将ARPFrame.SendHa设置为本机网卡的MAC地址
	//	for (int i = 0; i < 6; i++) {
	//		ARPFrame.SendHa[i] = 0x0f;
	//	}
	////将ARPFrame.SendIP设置为本机网卡的IP地址
	//ARPFrame.SendIP = inet_addr("122.122.122.122");
	////将ARPFrame.RecvHa设置为0
	//for (int i = 0; i < 6; i++)
	//	ARPFrame.RecvHa[i] = 0;//表示目的地址未知
	////将ARPFrame.RecvIP设置为请求的IP地址
	//ARPFrame.RecvIP = inet_addr("0.0.0.0");

	//if (pcap_sendpacket(handle, (u_char*)&ARPFrame, sizeof(ARPFrame_t) != 0)) {cout<<"发送错误处理"; }
	//else {cout<<"成功"; }

	//释放设备列表
	//pcap_freealldevs(alldevs);


}