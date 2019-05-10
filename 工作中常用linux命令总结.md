## 系统信息
```
uname -a
cat /proc/cpuinfo
arch
```
## 网络相关
```
mii-tool
brctl
ifconfig
service network status
tcpdump
tcpreplay
ping
iptables/firewalld
netstat
nc
sysctl.conf(vlan-tag)
```
## 文件管理
```
diff
sort
```
## 磁盘管理
```
df
du
ls
mount/umount
fsck
/etc/fstab
```
## 系统管理
```
date
hwclock/clock
ps/pstree
top
free
crontab
dmesg
insmod/lsmod
last
```
## linux程序相关
```
kill
pstack
readelf
objdump
strings
strace
gdb

```
# 数据库

## 数据库外部配置
```
my.cnf
service mysql status
```
## 数据库内部查询
```
show processlist
explain
mysqldump
max(id)
最大分区
最大主键值
```
## Elasticsearch
```
/etc/elasticsearch
service elasticsearch status 查看ES服务的状态
service elasticsearch stop 停止ES服务
service elasticsearch start 启动ES服务
service elasticsearch restart 重启ES服务

curl localhost:9200/_cat/health?v   查看ES集群的健康状态，green代表正常，yellow代表副本不可用，不影响数据入库，red代表分片不可用，会影响数据入库

curl localhost:9200/_cat/indices?v 查看进群所有的索引

curl localhost:9200/_cat/shards/dsa?v  查看dsa索引分片信息

 curl localhost:9200/_cat/indices/dsa?v 查看dsa索引相关信息

curl localhost:9200/_cat/segments/dsa?v 查看dsa中segment

curl localhost:9200/dsa/_mapping/records 查看dsa索引的records类型情况

curl -XGET localhost:9200/_cat/nodes?v 查看ES占用分配内存百分比
```