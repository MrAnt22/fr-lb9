import socket
import os
import array

SOCKET_PATH = '/tmp/socket_example'

try:
    os.unlink(SOCKET_PATH)
except FileNotFoundError:
    pass

server = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
server.bind(SOCKET_PATH)

os.chmod(SOCKET_PATH, 0o777)
server.listen(1)

print("[Sender] Connecting...")
conn, _ = server.accept()
print("[Sender] Client connected.")

fd = os.open("secret.txt", os.O_RDONLY)

fds = array.array("i", [fd])
conn.sendmsg([b"take this!"], [(socket.SOL_SOCKET, socket.SCM_RIGHTS, fds)])

print("[Sender] Descriptor sended.")
conn.close()
server.close()
