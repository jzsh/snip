//打印IP:
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/types.h>
#include <linux/netdevice.h>
#include <linux/skbuff.h>
#include <linux/netfilter_ipv4.h>
#include <linux/inet.h>
#include <linux/in.h>
#include <linux/ip.h>
#include <linux/tcp.h>
#include <linux/udp.h>

#define NIPQUAD(addr) \
  ((unsigned char *)&addr)[0], \
  ((unsigned char *)&addr)[1], \
  ((unsigned char *)&addr)[2], \
  ((unsigned char *)&addr)[3]


static unsigned int ipprint_func(
	unsigned int hooknum,
	struct sk_buff * skb,
	const struct net_device *in,
	const struct net_device *out,
	int (*okfn) (struct sk_buff *))
{
	__be32 sip,dip;

	struct tcphdr *tcph = NULL;
	struct udphdr *udph = NULL;
	unsigned short sport = 0;
	unsigned short dport = 0;
	struct iphdr *iph;
	if(skb)
	{
		struct sk_buff *sb = NULL;
		sb = skb;
		iph  = ip_hdr(sb);
		sip = iph->saddr;
		dip = iph->daddr;

		if(iph->protocol==IPPROTO_TCP)
		{
			tcph = (struct tcphdr *)((char *)skb->data + (int)(iph->ihl * 4));
			//tcph = tcp_hdr(sb);
			sport=ntohs(tcph->source);
			dport=ntohs(tcph->dest);
		}
		else if(iph->protocol==IPPROTO_UDP)
		{
			udph = (struct udphdr *)((char *)skb->data + (int)(iph->ihl * 4));
			//udph = udp_hdr(sb);
			sport=ntohs(udph->source);
			dport=ntohs(udph->dest);
		}
		printk("Packet for source address: %u.%u.%u.%u:%u destination address: %u.%u.%u.%u:%u\n ", NIPQUAD(sip),sport,NIPQUAD(dip),dport);
	}
	return NF_DROP;
}


struct nf_hook_ops ipprint_ops = {
	.list =  {NULL,NULL},
	.hook = ipprint_func,
	.pf = PF_INET,
	//.hooknum = NF_INET_PRE_ROUTING,
	.hooknum = NF_INET_LOCAL_IN,
	.priority = NF_IP_PRI_FILTER+2
};


static int __init ipprint_init(void) {
	nf_register_hook(&ipprint_ops);
	return 0;
}

static void __exit ipprint_exit(void) {
	nf_unregister_hook(&ipprint_ops);
}

module_init(ipprint_init);
module_exit(ipprint_exit);
MODULE_AUTHOR("djwow");
MODULE_DESCRIPTION("ipprint");
MODULE_LICENSE("GPL");
