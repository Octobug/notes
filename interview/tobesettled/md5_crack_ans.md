# 参考答案

```py
# -*- coding:utf-8 -*-
import hashlib
import string

piece = '5ed34925bdbd'


def crack(hash):
    s = string.lowercase + string.uppercase + string.digits
    for a in s:
        for b in s:
            for c in s:
                for d in s:
                    st = a+b+c+d
                    flag = hashlib.md5(st).hexdigest()
                    if(piece in flag):
                        print(flag)
                        print(st)
                        return


crack(piece)

```
