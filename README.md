# iceriverminer_dump

Dump of iceriver firmware files and filesystem 
<br>
Join the kaspa discord: https://discord.gg/kS3SK5F36R

If you found this helpful donate to:
`kaspa:qqzj7elguaa6d4p59ww9sh90za20y9qvh4wvllcnz2mspw04qrspz9jljsued`


# Gernal info
The startup service for the miner is found at: 
<br>
https://github.com/mcmickburns/iceriverminer_dump/blob/main/OS/KS3L/etc/rc0.d/K99bgserver.sh 



# OS 
The OS dump is located in the OS folder. 
<br>
The OS dump was taken from a KS3L that has not been updated to the lastest version.  

# Firmware
The firmware folder contains firmware from 
https://www.iceriver.io/firmware-download/

The firmware is encrypted with the jm binary located 
https://github.com/mcmickburns/iceriverminer_dump/blob/main/OS/KS3L/var/volatile/jm

In the firmware folder is each version of the iceriver firmware for each model.
There is a original verison plus the decrypted and extracted versions. 

A version of the KS3M miner has been placed added too:
<br>
https://github.com/mcmickburns/iceriverminer_dump/tree/main/firmware/KS3M/PRE-MODELLOCK-2023-09-16

# Changing miner versions 
### DAMAGE TO HARDWARE WARNING. 
To change the version of the miner you can change out the bgz files used in `/var/update`
<br>
You'll want to keep the original version around incase you want to switch back. 
<br>
Creating a sub folder in `/var/update` is recommended `bak` for example 
<br>
Then place the oringal .bgz files in the bak folder 
<br>
Next upload the version of the bg.bgz and miner.bgz you'd like to use. 
The names don't matter as long as they end in bg.bgz and miner.bgz so the scripts pick them up. 
Once uploaded restart the asic and the new miners will be used. 

If you want to switch back you can replace the uploaded .bgz with the originals and reboot. 


Example: 
KS3M bg.bgz https://github.com/mcmickburns/iceriverminer_dump/blob/main/firmware/KS3M/PRE-MODELLOCK-2023-09-16/Recovery/order/reset/0808_ks3mbg.bgz
<br>
KS3M miner.bgz https://github.com/mcmickburns/iceriverminer_dump/blob/main/firmware/KS3M/PRE-MODELLOCK-2023-09-16/Recovery/order/reset/formal/0823_ks3mminer.bgz
<br>
## Converting KS3L to KS3M 
 <b>WARNING ONLY USE IF YOU HAVE A 2 FAN PSU. </b>
 <b>REPORTS ARE 3 FAN PSU's CAN'T HANDLE THE OC </b>
The conversion is done by swapping the miner/bgserver/reset.conf that are used when the miner starts. 
<br>
The KS3M miner does a quick check to see what model the machine is set to. 
<br>
By default miner defaults to a KS3L. 
<br>
The reset.conf has a extra parameter:
```
[model]
model=ks3m
```
Once it finds the model has been set to KS3M it then applies the overclocks. 


Files to backup: 
<br>
reset.conf `/var/order/conf/reset.conf`
<br>
*bg.bgz `/var/update/*bg.bgz`
<br>
*miner.bgz `/var/update/*miner.bgz`

The best method is to make a sub folder in in `/var/order/conf` and `/var/update` called orig.
<br>
Then move the original files on the miner into the orig folder. 

Once done you can download and replace the miner/bg/reset.conf with the ones listed below: 
<br>
reset.conf: https://github.com/mcmickburns/iceriverminer_dump/blob/main/firmware/KS3M/PRE-MODELLOCK-2023-09-16/Recovery/order/conf/reset.conf
<br>
*bg.bgz: https://github.com/mcmickburns/iceriverminer_dump/blob/main/firmware/KS3M/PRE-MODELLOCK-2023-09-16/Recovery/order/reset/0808_ks3mbg.bgz
<br>
*miner.bgz: https://github.com/mcmickburns/iceriverminer_dump/blob/main/firmware/KS3M/PRE-MODELLOCK-2023-09-16/Recovery/order/reset/formal/0823_ks3mminer.bgz

The .bgz files belong in `/var/update/` 
Reset.conf belongs in `/var/order/conf/`

Once the files have been replaced restart the miner.
<br>
You should see increased hashrate. 
<br>Note there is also increased power draw to 14a/3400W. 

# KS0 OC 
see the KS0 OC [README.md](./firmware/KS0/OC/README.md)


# Access a iceriver asic yourself 
```
Users on system bgchris168
SSH port is 48699
TCF/debug port is 1534

To get connected:
1. Download and install eclipse https://www.eclipse.org/downloads/download.php?file=/technology/epp/downloads/release/2023-09/R/eclipse-java-2023-09-R-win32-x86_64.zip&r=1
2. Start eclipse
3. Go to Help -> Install new Software
4. in the work with field enter: https://download.eclipse.org/tools/tcf/releases/1.7/1.7.0
5. Click add 
6. Give it a name 
7. Click add
8. Select "Target Communication Framework" and "TCF Target Explorer" 
9. Click next and agree to the license, click finish 
10. Restart eclipse when prompted 
11. When eclipse restarts along the top bar there should be a new option for "New Connection" 
12. Click "New Connection"
13. Select Generic Connection 
14. For Connection Name click browse
15. The IP of the miner should appear as a tcf agent  
16. Select the ip 
17. Click OK 
18. Click Finish 

You should now be connected to the debug interface of the miner. 
You can view information or browse/edit files on the filesystem. 

If you want a easy shell. Edit the password for bgchris168 and add him to sudoers.
Then ssh into the account and make your own. 
Remember to backup bgchris168 password incase its important and replace it afterwards. 
```


<br><br><br>
If you found this helpful donate to:
`kaspa:qqzj7elguaa6d4p59ww9sh90za20y9qvh4wvllcnz2mspw04qrspz9jljsued`
