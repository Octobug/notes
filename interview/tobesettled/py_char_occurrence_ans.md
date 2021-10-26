# 参考答案

```py
import os

file_path = (os.path.abspath(__file__))


def count_chars(str):
    str_lower = str.lower()

    d_count = {}.fromkeys([x for x in str_lower], 0)

    for char in str_lower:
        d_count[char] += 1

    d_sorted = {
        k: v for k, v in sorted(
            d_count.items(), key=lambda item: item[1], reverse=True
        )
    }
    for i in d_sorted:
        print(i, d_sorted[i])


code_str = None

with open(file_path, 'r') as f:
    code_str = f.read()

count_chars(code_str)

```
