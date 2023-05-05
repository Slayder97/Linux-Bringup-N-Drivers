/******************************************************************************
*  @brief      Fake ethernet driver
*
*  @author     phonglt9 <p.linuxfromscratch@gmail.com>
*******************************************************************************/

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>
#include <linux/skbuff.h>
#include <linux/rtnetlink.h>

#define DRIVER_AUTHOR "phonglt9 <p.linuxfromscratch@gmail.com>"
#define DRIVER_DESC   "Fake ethernet driver"

#define FAKE_NETDEV_IFNAME  "mnetdev"
#define FAKE_NETDEV_MTU     1200

struct m_netdev_priv {
    struct net_device foo_ndev;
};

static struct net_device *m_netdev = NULL;

static int  m_netdev_init(struct net_device *dev)
{
    pr_info("%s - %d\n", __func__, __LINE__);
    return 0;
}

static void  m_netdev_uninit(struct net_device *dev)
{
    pr_info("%s - %d\n", __func__, __LINE__);
}

static int  m_netdev_open(struct net_device *dev)
{
    netif_start_queue(dev);
    pr_info("%s - %d\n", __func__, __LINE__);
    return 0;
}

static int  m_netdev_stop(struct net_device *dev)
{
	netif_stop_queue(dev);
    pr_info("%s - %d\n", __func__, __LINE__);
	return 0;
}

static int  m_netdev_start_xmit(struct sk_buff *skb, struct net_device *dev)
{
    pr_info("%s - %d\n", __func__, __LINE__);
    return NETDEV_TX_OK;
}

static void  m_netdev_get_stats64(struct net_device *dev, struct rtnl_link_stats64 *stats)
{
    pr_info("%s - %d\n", __func__, __LINE__);
}

static const struct net_device_ops m_netdev_ops = {
	.ndo_change_mtu		= NULL,
	.ndo_init			= m_netdev_init,
	.ndo_uninit			= m_netdev_uninit,
	.ndo_open			= m_netdev_open,
	.ndo_stop			= m_netdev_stop,
	.ndo_start_xmit 	= m_netdev_start_xmit,
	.ndo_get_stats64	= m_netdev_get_stats64
};

void m_netdev_setup(struct net_device *ndev)
{
    eth_hw_addr_random(ndev);   /* 02. Generate random MAC address and */
    ether_setup(ndev);          /* 03. Initialize default values for the net_device structure */

    /* 04. Re-initialize data fields for the net_device structure */
    ndev->priv_flags = IFF_NO_QUEUE;
    ndev->netdev_ops	= &m_netdev_ops;
    ndev->ethtool_ops	= NULL;
    ndev->min_mtu		= 0;
	ndev->max_mtu		= ETH_MAX_MTU;
    ndev->mtu		    = FAKE_NETDEV_MTU;
}

static int __init netdev_init(void)
{
    int ret;
    struct m_netdev_priv *priv;

    /* 01. Allocate the network device along with its private data */
    m_netdev = alloc_netdev(sizeof(struct m_netdev_priv), \
                        FAKE_NETDEV_IFNAME, \
                        NET_NAME_UNKNOWN, \
                        m_netdev_setup);
    if (!m_netdev)
        return -ENOBUFS;

    priv = netdev_priv(m_netdev);

    /* 05. Register the network device */
    rtnl_lock();
    ret = register_netdevice(m_netdev);
    rtnl_unlock();
    if (ret < 0)
        goto release_m_netdev; 

    /* Module init infor then return */
    pr_info("%s - %d: Fake ndev init\n", __func__, __LINE__);
    return 0;

release_m_netdev:  
    free_netdev(m_netdev);
    return ret;
}

static void __exit netdev_exit(void)
{
    pr_info("%s - %d: Fake ndev exit\n", __func__, __LINE__);
    rtnl_lock();
    if (m_netdev) 
        unregister_netdevice(m_netdev);
    rtnl_unlock();

    free_netdev(m_netdev);
}

module_init(netdev_init);
module_exit(netdev_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);