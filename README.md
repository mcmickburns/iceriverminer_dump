# iceriverminer_dump
Dump of iceriver firmware files and filesystem 
<br>
Join the kaspa discord: https://discord.gg/kS3SK5F36R

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
