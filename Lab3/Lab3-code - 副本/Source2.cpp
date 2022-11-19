#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include"pcap.h"
#include <WinSock2.h>
#include <Windows.h>
#include<iostream>
#include<stdio.h>
#include<cstring>
using namespace std;

#pragma comment(lib, "packet.lib")
#pragma comment(lib, "wpcap.lib")
#pragma comment(lib,"ws2_32.lib")

#pragma pack (1)//�����ֽڶ��뷽ʽ
//��̫��֡ 14�ֽ�
typedef struct FrameHeader_t {
	BYTE DesMAC[6];// Ŀ�ĵ�ַ
	BYTE SrcMAC[6];//Դ��ַ
	WORD FrameType;//֡����
}FrameHeader_t;
//ARP֡ 28�ֽ�
typedef struct ARPFrame_t {
	FrameHeader_t FrameHeader;//��̫��֡ͷ
	WORD HardwareType;//Ӳ������
	WORD ProtocolType;//Э������
	BYTE HLen;//Ӳ����ַ����
	BYTE PLen;//Э���ַ����
	WORD Operation;
	BYTE SendHa[6];	//���Ͷ���̫����ַ
	DWORD SendIP;	//���Ͷ�IP��ַ
	BYTE RecvHa[6];	//Ŀ����̫����ַ
	DWORD RecvIP;	//Ŀ��IP��ַ
} ARPFrame_t;
#pragma pack ()

//ȫ��
pcap_t* adhandle;				 //��׽ʵ��,��pcap_open���صĶ���
string iplist[100];
int i = 0;                       //��������������
BYTE MAC[6];

int main() {
	string ip_far;
	cin >> ip_far;

	pcap_if_t* alldevs;				 //��������������
	char errbuf[PCAP_ERRBUF_SIZE];   //���󻺳���,��СΪ256
	pcap_findalldevs_ex(PCAP_SRC_IF_STRING, NULL, &alldevs, errbuf);
	for (pcap_if_t* d = alldevs; d != nullptr; d = d->next)//��ʾ�ӿ��б�
	{
		//��ȡ������ӿ��豸��ip��ַ��Ϣ
		for (pcap_addr* a = d->addresses; a != nullptr; a = a->next)
		{
			if (((struct sockaddr_in*)a->addr)->sin_family == AF_INET && a->addr)
			{//��ӡip��ַ
				i++;
				if (i == 2) {
				//��ӡ�����Ϣ
				//inet_ntoa��ip��ַת���ַ�����ʽ
					//printf("%d\n", i);
					//printf("%s\t\t%s\n%s\t%s\n", "name:", d->name, "description:", d->description);
					//printf("%s\t\t%s\n", "IP��ַ:", inet_ntoa(((struct sockaddr_in*)a->addr)->sin_addr));
					string ip_ben= iplist[i] = inet_ntoa(((struct sockaddr_in*)a->addr)->sin_addr);
					cout << "����ip��" << ip_ben << endl;
					//α��
					ARPFrame_t ARPFrame;
					for (int i = 0; i < 6; i++)
						ARPFrame.FrameHeader.DesMAC[i] = 0xff;//��ʾ�㲥
					//��APRFrame.FrameHeader.SrcMAC����Ϊ����������MAC��ַ
					for (int i = 0; i < 6; i++)
						ARPFrame.FrameHeader.SrcMAC[i] = 0x0f;

					ARPFrame.FrameHeader.FrameType = htons(0x806);//֡����ΪARP
					ARPFrame.HardwareType = htons(0x0001);//Ӳ������Ϊ��̫��
					ARPFrame.ProtocolType = htons(0x0800);//Э������ΪIP
					ARPFrame.HLen = 6;//Ӳ����ַ����Ϊ6
					ARPFrame.PLen = 4;//Э���ַ��Ϊ4
					ARPFrame.Operation = htons(0x0001);//����ΪARP����

					//��ȡԶ��IP��MAC��ӦʱӦ�ý�ARPFrame.SendHa����Ϊ����������MAC��ַ
					for (int i = 0; i < 6; i++)
						ARPFrame.SendHa[i] = 0x0f;
					//��ȡԶ��IP��MAC��ӦʱӦ�ý�ARPFrame.SendIP����Ϊ���������ϰ󶨵�IP��ַ
					ARPFrame.SendIP = inet_addr("100.100.100.100");
					//��ARPFrame.RecvHa����Ϊ0
					for (int i = 0; i < 6; i++)
						ARPFrame.RecvHa[i] = 0;//��ʾĿ�ĵ�ַδ֪
					//��ȡԶ��IP��MAC��ӦʱӦ�ý�ARPFrame.RecvIP����Ϊ�����IP��ַ
					ARPFrame.RecvIP = inet_addr(inet_ntoa(((struct sockaddr_in*)a->addr)->sin_addr));
					//����
					if (pcap_sendpacket(adhandle, (u_char*)&ARPFrame, sizeof(ARPFrame_t)) == 0) {
					
					}
					//�ձ�
					struct pcap_pkthdr* pkt_header;
					const u_char* pkt_data;
					int res;
					while ((res = pcap_next_ex(adhandle, &pkt_header, &pkt_data)) >= 0) {
						ARPFrame_t* RecPacket = (ARPFrame_t*)pkt_data;
						if (
							*(unsigned short*)(pkt_data + 12) == htons(0x0806)	//0x0806Ϊ��̫��֡���ͱ�ʾ�������ݵ����ͣ�����ARP�����Ӧ����˵�����ֶε�ֵΪx0806
							//&& *(unsigned short*)(pkt_data + 20) == htons(2)	//ARPӦ��
							&& *(unsigned long*)(pkt_data + 38) == inet_addr("100.100.100.100")
							)
						{
							printf("%s:\t%02x-%02x-%02x-%02x-%02x-%02x\n", "MAC��ַ",
								RecPacket->FrameHeader.SrcMAC[0],
								RecPacket->FrameHeader.SrcMAC[1],
								RecPacket->FrameHeader.SrcMAC[2],
								RecPacket->FrameHeader.SrcMAC[3],
								RecPacket->FrameHeader.SrcMAC[4],
								RecPacket->FrameHeader.SrcMAC[5]);
							for (int i = 0; i < 6; i++) {
								MAC[i] = RecPacket->FrameHeader.SrcMAC[i];
							}
							break;
						}
					}







				}
				

			}
		}
	}
}