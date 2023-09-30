#!/bin/bash

#   Copyright 2023 rdugan
#
#   Licensed under the Apache License, Version 2.0 (the "License");
#   you may not use this file except in compliance with the License.
#   You may obtain a copy of the License at
#
#       http://www.apache.org/licenses/LICENSE-2.0
#
#   Unless required by applicable law or agreed to in writing, software
#   distributed under the License is distributed on an "AS IS" BASIS,
#   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#   See the License for the specific language governing permissions and
#   limitations under the License.

if [ $# != 3 ];
then
  echo "Usage: $0 <bg archive> <miner archive> <output file>"
  exit 1;
fi

cd $(dirname "$(realpath $0)")

export IRPW=Aptx-4869aptx-\$\*^\(

# extract filenames w/o path or extensions
f=${1##*/}
bgFile=${f%.*}

f=${2##*/}
minerFile=${f%.*}

f=${3##*/}
upgradeFile=${f%.*}

# create fake salt file
FSTMP=$(mktemp)
dd if=/dev/zero of=$FSTMP bs=1 count=16 status=none

# encrypt inputs and prepend fake salt
CRYPTTMP=$(mktemp)

openssl enc -nosalt -aes-256-cbc -in $1 -out $CRYPTTMP -pass env:IRPW >/dev/null 2>&1
cat $FSTMP $CRYPTTMP > /tmp/${bgFile}.bgz

openssl enc -nosalt -aes-256-cbc -in $2 -out $CRYPTTMP -pass env:IRPW >/dev/null 2>&1
cat $FSTMP $CRYPTTMP > /tmp/${minerFile}.bgz


# create and encrypt archive of encrypted inputs, and prepend fake salt
tar czf /tmp/${upgradeFile}.tar -C /tmp ${bgFile}.bgz ${minerFile}.bgz
openssl enc -nosalt -aes-256-cbc -in /tmp/${upgradeFile}.tar -out $CRYPTTMP -pass env:IRPW >/dev/null 2>&1
cat $FSTMP $CRYPTTMP > $3

echo "${3} created"