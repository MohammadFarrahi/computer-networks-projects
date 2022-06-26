import sys

if(len(sys.argv) != 3):
  print("you should provide 2 args")
else:
  filename = sys.argv[1]
  size = int(float(sys.argv[2]) * 2**16)
  sixteen_byte_data = "0123456789012345"

  with open(filename, 'w') as f:
    for _ in range(size):
      f.write(sixteen_byte_data)

