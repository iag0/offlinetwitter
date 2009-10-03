# include<stdio.h>
# include<pcap.h>


void callback(u_char *data, const struct pcap_pkthdr *pkthdr,const u_char  *packet)

{

	static int count=1;
	printf("%d ",count++);
	fflush(stdout);
}

int main()
{
	char *dev,errbuf[PCAP_ERRBUF_SIZE];
	pcap_t * handle;
	struct pcap_pkthdr header;
	const u_char *packet;
	
	struct bpf_program fp;
	char filter_exp[]="dst host www.google.com";
	bpf_u_int32 mask,net;
	
	dev=pcap_lookupdev(errbuf);
	
	pcap_lookupnet(dev,&net,&mask,errbuf);
	
	handle=pcap_open_live(dev,BUFSIZ,0,-1,errbuf);
	
	//pcap_compile(handle,&fp,filter_exp,0,net);
	
	//pcap_setfilter(handle,&fp);
	
	packet=pcap_next(handle,&header);
	printf("%d\n",header.len);
	
	pcap_loop(handle,-1,callback,NULL);
	pcap_close(handle);
	
	return 0;
}

