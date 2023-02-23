import socket
import threading

HOST = "127.0.0.1"
PORT = 5000
SIZE = 1024
FORMAT = "utf-8"
DISCONNECT_MSG = "!DISCONNECT"

def handle_client(conn, addr):
    print(f"[NEW CONNECTION] {addr} connected.")

    with conn:
        while True:
            msg = conn.recv(SIZE).decode(FORMAT)
            if not msg:
                break

            print(f"Thread {threading.get_ident()}[{addr}] {msg}")
            conn.send(f"Msg received: {msg}".encode(FORMAT))

    print(f"[DISCONNECTED] {addr} disconnected.")

def main():
    print("[Starting] Server is starting...")
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as server:
        server.bind((HOST, PORT))
        server.listen()
        print(f"[Listening] Server is listening on port {HOST}:{PORT}")

        while True:
            conn, addr = server.accept()
            thread = threading.Thread(target=handle_client, args=(conn, addr))
            thread.start()
            print(f"[Active Connections] {threading.active_count() - 1}") # -1 because of the main thread

if __name__ == "__main__":
    main()