a=input()
b=""
for i in range(len(a)):
    if a[i] == '"':
        b=b+'\\"'
        print("test")
    else:
        b=b+a[i]
print(b)
