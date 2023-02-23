import socket

HOST = "127.0.0.1"
PORT = 5000
SIZE = 1024
FORMAT = "utf-8"
DISCONNECT_MSG = "!DISCONNECT"

def main():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as client:
        client.connect((HOST, PORT))
        print(f"[Connected] Client is connected to {HOST}:{PORT}")

        while True:
            msg = input(">: ")

            if not msg:
                continue

            client.send(msg.encode(FORMAT))

            if msg == DISCONNECT_MSG:
                break

            msg = client.recv(SIZE).decode(FORMAT)
            print(f"[SERVER] {msg}")

    print("[DISCONNECTED] Client disconnected from the server.")

if __name__ == "__main__":
    main()