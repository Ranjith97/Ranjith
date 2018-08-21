/**
 * @file            : my_nwdriver.c
 * @brief           : This program will create a network driver to create an
 *                    interface and send the ARP reply packets.
 * @author          : Ranjith Kumar K V (ranjithkumatkv@vvdntech.in)
 * @Copyright(c)    : 2018, VVDN Technologies Pvt. Ltd. Permission is
 *                    hereby granted to everyone in VVDN Technologies to use
 *                    the Software without restriction, including without
 *                    limitation the rights to use, copy, modify, merge,
 *                    publish, distribute, distribute with modifications.
 */

#include<linux/module.h>
#include<linux/netdevice.h>
#include<linux/kernel.h>
#include<linux/etherdevice.h>

#define SUCCESS 0
#define MAC_LENGTH 6
#define IP_LENGTH 4

struct net_device *my_device;

/**
 * @function: my_open
 * @param   : net_device structure
 * @return  : SUCCESS
 * @brief   : This function opens the device.
 **/
int my_open(struct net_device *dev) {
    printk("Open function called\n");
    netif_start_queue(dev);
    return SUCCESS;
}

/**
 * @function: my_close
 * @param   : net_device structure
 * @return  : SUCCESS
 * @brief   : This function stops the transmission.
 **/
int my_close(struct net_device *dev) {
    printk("Close function called\n");
    netif_stop_queue(dev);
    return SUCCESS;
}

struct arp_header {
    unsigned char hwtype[1];
    unsigned char prototype[2];
    unsigned char hwdsize[1];
    unsigned char protosize[1];
    unsigned char opcode[1];
    unsigned char smac[MAC_LENGTH];
    unsigned char sip[IP_LENGTH];
    unsigned char dmac[MAC_LENGTH];
    unsigned char dip[IP_LENGTH];
};

struct eth_header {
    unsigned char dest_mac[MAC_LENGTH];
    unsigned char src_mac[MAC_LENGTH];
    unsigned char type[2];
};

/**
 * @function: my_xmit
 * @param   : sk_buff structure, net_device structure
 * @return  : SUCCESS
 * @brief   : This function transmits the packets.
 **/
int my_xmit(struct sk_buff *skb, struct net_device *dev) {
    struct eth_header *reply, *send;
    struct arp_header *reply1, *send1;

    reply = (struct eth_header*)skb_pull(skb, 0);
    reply1 = (struct arp_header*)skb_pull(skb, sizeof(struct eth_header));
    skb_pull(skb, sizeof(struct arp_header));

    send1 = skb_push(skb, sizeof(send1));
    memcpy(send1->hwtype, reply1->hwtype, 1);
    memcpy(send1->prototype, reply1->prototype, 2);
    memcpy(send1->hwdsize, reply1->hwdsize, 1);
    memcpy(send1->protosize, reply1->protosize, 1);
    send1->opcode[0] = 2;
    memcpy(send1->smac, reply1->dmac, MAC_LENGTH);
    memcpy(send1->sip, reply1->dip, IP_LENGTH);
    memcpy(send1->dmac, reply1->smac, MAC_LENGTH);
    memcpy(send1->dip, reply1->sip, IP_LENGTH);

    send = skb_push(skb, sizeof(send));
    memcpy(send->src_mac, reply1->dmac, MAC_LENGTH);
    memcpy(send->dest_mac, reply->src_mac, MAC_LENGTH);
    memcpy(send->type, reply->type, 2);

    netif_rx(skb);
    return SUCCESS;
}

/**
 * @function: my_init
 * @param   : net_device structure
 * @return  : SUCCESS
 * @brief   : this function runs while initiation.
 **/
int my_init(struct net_device *dev) {
    printk("Device initialized\n");
    return SUCCESS;
}

/**
 * net_device_ops structure linking
 **/
const struct net_device_ops my_netdevice = {
    .ndo_init = my_init,
    .ndo_open = my_open,
    .ndo_stop = my_close,
    .ndo_start_xmit = my_xmit
};

/**
 * @function: virtual_setup
 * @param   : net_device structure
 * @brief   : This function links the net_device_ops with
 *            net_device structure
 **/
static void virtual_setup(struct net_device *dev) {
    ether_setup(dev);
    dev->dev_addr[0] = 0x10;
    dev->dev_addr[1] = 0x11;
    dev->dev_addr[2] = 0x12;
    dev->dev_addr[3] = 0x13;
    dev->dev_addr[4] = 0x14;
    dev->dev_addr[5] = 0x15;
    dev->netdev_ops = &my_netdevice;
}

/**
 * @function: my_init_module
 * @return  : result/SUCCESS
 * @Brief   : This function initiates the net device.
 **/
int my_init_module(void) {
    int result;
    my_device = alloc_netdev(0, "newnw", 0, virtual_setup);
    if ((result = register_netdev(my_device))) {
        printk("Device registration failed\n");
        return result;
    }
    return SUCCESS;
}

/**
 * @function: my_cleanup
 * @brief   : This function is called while removing the module
 *            from the kernel.
 **/
void my_cleanup(void) {
    printk("Cleaning the module\n");
    unregister_netdev(my_device);
}

module_init(my_init_module);
module_exit(my_cleanup);
MODULE_LICENSE("GPL");
