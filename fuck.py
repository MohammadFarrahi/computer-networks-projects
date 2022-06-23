f= open('./test.txt', 'w')
for i in range(512*1023):
  f.write(str(i))
f.close()
