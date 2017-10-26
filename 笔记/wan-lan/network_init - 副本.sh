#!/bin/sh

#set mac address of eth0 & eth1
printf "start: Network\n"
/root/locator getmac
ifconfig eth0 hw ether `cat /tmp/getmac0`
ifconfig eth1 hw ether `cat /tmp/getmac1`

echo "1" > /proc/sys/net/ipv4/ip_forward
ifconfig eth0 0.0.0.0 up
ifconfig eth1 0.0.0.0 up

set mac and up ,and forword

ip2num ()
{
	ip_str="$1"
	ip1=`echo $ip_str|cut -d "." -f1`
	ip2=`echo $ip_str|cut -d "." -f2`                   
	ip3=`echo $ip_str|cut -d "." -f3`                                   
	ip4=`echo $ip_str|cut -d "." -f4`
	
	a=$ip1 << 24
	b=$ip2 << 16
	c=$ip3 << 8
	d=$ip4
	e=$a | $b | $c | $d
	
	echo $e;
	
	#echo $(( (($ip1<<24)) | (($ip2<<16)) | (($ip3<<8)) | $ip4 )); 
}


num2ip ()
{
	ip=$1
	
	a=$ip & 0x000000ff
	b=$ip & 0x0000ff00
	c=$ip & 0x00ff0000
	d=$ip & 0xff000000
	H1=$a
	H2=$b >> 8
	L1=$c >>16
	L2=$d >>24
	
	#H1=$(($ip & 0x000000ff))
	#H2=$((($ip & 0x0000ff00) >> 8))
	#L1=$((($ip & 0x00ff0000) >> 16))
	#L2=$((($ip & 0xff000000) >> 24))
	
	echo $L2.$L1.$H2.$H1
}


# ip2num ()
# {
	# ip_str="$1"
    # iptol ip_str
	
# }

# num2ip ()
# {
	# n="$1"
	# ltoip n
	
# }

#-----------------------------


#config iptables
echo "--restore iptables--"
iptables-restore < /mnt/user/iptables.conf


#目前
#只有eth0可配置为lan或wan
#eth1只能为lan


#set eth0
#如果都是lan,直接桥接为br0,udhcpc - i br0 ,通过br0上网.相当于交换机功能.
#如果eth0是wan,将eth0单独设置ip。将eth1桥接为br0, 开启udhcpd服务。
#

eth0_mode=`uci get network.eth0mode.eth0_mode -q`
wan_proto=`uci get network.eth0mode.proto -q`

if [[ $eth0_mode == "wan" ]]; then
	echo "--set wan--"
	brctl addbr br0
	brctl addif br0 eth1
	ifconfig eth1 0.0.0.0
	ifconfig br0 up
	if [[ $wan_proto == "static" ]]; then	#wan口静态IP
		ifconfig eth0 `uci get -q network.eth0mode.ipaddr` netmask `uci get -q network.eth0mode.netmask`
		route add default gw `uci get -q network.eth0mode.gateway` dev eth0
	elif [ $wan_proto == "dhcp" ];then
		ifconfig eth0 up	#wan口动态IP
		udhcpc -i eth0 
	else					#wan口pppoe,pppoe默认使用eth0拨号上网
		ifconfig eth0 up
		pppoe -p /mnt/user/pppoe/pppoe.conf
	fi
else
	brctl addbr br0
	brctl addif br0 eth0
	brctl addif br0 eth1
	ifconfig eth0 0.0.0.0
	ifconfig eth1 0.0.0.0
	ifconfig br0 up
fi


#set lan
# set Staticip / Dhcp, and submask  
printf "start: Network set local ip ...\n"
lan_proto=`uci get network.lan.proto -q`
echo $lan_proto `uci get network.lan.ipaddr -q` `uci get -q network.lan.gateway` 
if [ $lan_proto == "static" ]
then
	ifconfig br0 `uci get -q network.lan.ipaddr` netmask `uci get -q network.lan.netmask` up
	route add default gw `uci get -q network.lan.gateway` dev br0
	if [[ $eth0_mode == "wan" ]]; then	#ip伪装/映射
		#lan_static_ip_sec=$(num2ip $(($(ip2num `uci get -q network.lan.ipaddr`) & $(ip2num `uci get -q network.lan.netmask`))));
		a=$(ip2num `uci get -q network.lan.ipaddr`)
		b=$(ip2num `uci get -q network.lan.netmask`)
		
		echo a = $a b = $b
		c=$a & $b
		lan_static_ip_sec=$(num2ip $c)
		
		echo $a $b $c $lan_static_ip_sec [$lan_static_ip_sec/`uci get -q network.lan.netmask`]
		 
		
		iptables -t nat -A POSTROUTING -s $lan_static_ip_sec/`uci get -q network.lan.netmask` -j MASQUERADE
	fi	
elif [ $lan_proto == "pppoe" ]
then	
	ip link set br0 up 
	# config pppoe interface
	pppoe -p /mnt/user/pppoe/pppoe.conf
else			
	if [[ $eth0_mode == "wan" ]]; then	#ip伪装/映射
	
		#ip_sec=$(num2ip $(($(ip2num `uci get -q network.lan.router`) & $(ip2num `uci get -q network.lan.subnet`))));
		
		a=$(ip2num `uci get -q network.lan.router`)
		b=$(ip2num `uci get -q network.lan.subnet`)
		
		echo a = $a b = $b
		
		c=$a & $b
		ip_sec=$(num2ip $c)
		
		echo $a $b $c $ip_sec [$ip_sec/`uci get -q network.lan.subnet`]
		
		ifconfig br0 `uci get -q network.lan.router` netmask `uci get -q network.lan.subnet`
		iptables -t nat -D POSTROUTING -s $ip_sec/`uci get -q network.lan.subnet` -j MASQUERADE
		iptables -t nat -A POSTROUTING -s $ip_sec/`uci get -q network.lan.subnet` -j MASQUERADE
		
		#写配置文件
	    udhcpd_enable=`uci get network.lan.dhcps_enabled -q`
		if [ $udhcpd_enable == "1" ];then
			echo "start "`uci get network.lan.start -q` > /mnt/user/udhcpd.conf
			echo "end "`uci get network.lan.end -q` >> /mnt/user/udhcpd.conf
			echo "interface "`uci get network.lan.interface -q` >> /mnt/user/udhcpd.conf
			echo "max_leases "`uci get network.lan.max_leases -q` >> /mnt/user/udhcpd.conf
			echo "option subnet "`uci get network.lan.subnet -q` >> /mnt/user/udhcpd.conf
			echo "option router "`uci get network.lan.router -q` >> /mnt/user/udhcpd.conf
			echo "option domain "`uci get network.lan.domain -q` >> /mnt/user/udhcpd.conf
			echo "option lease "`uci get network.lan.lease -q` >> /mnt/user/udhcpd.conf
			echo "option dns "`uci get network.lan.dns -q` >> /mnt/user/udhcpd.conf
			echo "option dns "`uci get network.lan.dns2 -q` >> /mnt/user/udhcpd.conf
			
			#启动udhcpd
			udhcpd /mnt/user/udhcpd.con
			echo "--lan udhcpd start--"
		fi
		
	else
		ip link set br0 up 
		udhcpc -i br0 	
	fi	
	
	# set resolv.conf
	printf "start: resolv.conf copy\n"	
	echo "nameserver "`uci get network.lan.dns -q` > /etc/resolv.conf.static
	echo "nameserver "`uci get network.lan.dns2 -q` >> /etc/resolv.conf.static
	cp -a /etc/resolv.conf.static /tmp/resolv.conf
	
fi
