import socket
import os
import array

SOCKET_PATH = '/tmp/socket_example'

client = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
client.connect(SOCKET_PATH)

fds = array.array("i")
msg, ancdata, *_ = client.recvmsg(1024, socket.CMSG_LEN(4))
for cmsg_level, cmsg_type, cmsg_data in ancdata:
    if cmsg_level == socket.SOL_SOCKET and cmsg_type == socket.SCM_RIGHTS:
        fds.frombytes(cmsg_data[:4])

fd = fds[0]
print("[Receiver] Received descriptor:", fd)

with os.fdopen(fd, 'r') as f:
    content = f.read()
    print("[Receiver] Inside file:", content)

client.close()
