A client connects to the server and passes a file. The server will download a file to the directory "ServerDir" that is located in the same dir where Server.exe is.
To run server you need to launch Server.exe
To run client you need to launch Client.exe with parameters ip-port file-path.
Example: Client.exe 127.0.0.1:12345 "d:\your-dir\sample.txt"