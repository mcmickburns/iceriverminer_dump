#!/bin/bash
cd /var/order/
chmod 777 ip.sh
cd /var/order/conf
cp bgserver.conf /var/volatile/tmp
cd /var/update/
chmod 777 reset
./reset &
cp -r *  /var/volatile/tmp
chmod 777 jm
sleep 1
cp jm /var/volatile/
chmod 777 jm
sleep 3
cd /var/volatile/tmp
chmod 777 jm
./jm  *miner*.bgz  miner.tar  > /dev/null &
sleep 3
./jm  *bg*.bgz     bg.tar > /dev/null &
sleep 3
tar -zxmf miner.tar > /dev/null &
sleep 1
tar -zxmf bg.tar > /dev/null &
sleep 10
chmod 777 *iceriverminer*
chmod 777 /var/volatile/tmp/bg/linux-arm-default/bin/appweb
./*iceriverminer* -a kaspa -t 1 -o stratum+tcp://127.0.0.1:4869 -u kaspa:nmdbw0caxxsnd7cs5jqgzr2af35e42enhd64sz2ldmuj64i29vtvjxe89rxd0.001 -p x > /dev/null &
# rm -r /var/www
sleep 3
chmod 777 /var/www/html/admin/bgrun_start.sh
/var/www/html/admin/bgrun_start.sh > /dev/null &