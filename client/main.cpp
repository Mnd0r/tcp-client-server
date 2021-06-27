/*
    C++ Socket Client
*/
#include <iostream> //cout
#include <stdio.h> //printf
#include <string.h> //strlen
#include <string> //string
#include <sys/socket.h> //socket
#include <arpa/inet.h> //inet_addr
#include <netdb.h> //hostent
#include <bitset>
#include <unistd.h>

using namespace std;

/*
    TCP Client class
*/
class TcpClient
{
    private:
        int sock;
        std::string address;
        string response_data = "";
        int port;
        struct sockaddr_in server;

    public:
        TcpClient();
        bool conn(string, int);
        bool send_data(int original, string data);
        string receive(int);
};

/*
    constructor
*/
TcpClient::TcpClient()
{
    sock = -1;
    port = 0;
    address = "";
}

/*
    Connect to a host on a certain port number
*/
bool TcpClient::conn(string address , int port)
{
    // create socket if it is not already created
    if(sock == -1)
    {
        //Create socket
        sock = socket(AF_INET , SOCK_STREAM , 0);
        if (sock == -1)
        {
            perror("Could not create socket");
        }

        cout<<"Socket created\n";
    }
    else { /* OK , nothing */ }

    // setup address structure
    if(inet_addr(address.c_str()) == -1)
    {
        struct hostent *he;
        struct in_addr **addr_list;

        //resolve the hostname, its not an ip address
        if ( (he = gethostbyname( address.c_str() ) ) == NULL)
        {
            //gethostbyname failed
            herror("gethostbyname");
            cout<<"Failed to resolve hostname\n";

            return false;
        }

        // Cast the h_addr_list to in_addr , since h_addr_list also has the ip address in long format only
        addr_list = (struct in_addr **) he->h_addr_list;

        for(int i = 0; addr_list[i] != NULL; i++)
        {
            //strcpy(ip , inet_ntoa(*addr_list[i]) );
            server.sin_addr = *addr_list[i];

            cout<<address<<" resolved to "<<inet_ntoa(*addr_list[i])<<endl;

            break;
        }
    }

    //plain ip address
    else
    {
        server.sin_addr.s_addr = inet_addr( address.c_str() );
    }

    server.sin_family = AF_INET;
    server.sin_port = htons( port );

    //Connect to remote server
    if( connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0 )
    {
        perror("connect failed. Error");
        return false;
    }

    cout<<"Connected\n";
    return true;
}

/*
    Send data to the connected host
*/
bool TcpClient::send_data(int original, string data)
{
    cout<<"CLIENT C++ Sending data... :";
    cout<<original;
    cout<<" as ";
    cout<<data;
    cout<<"\n";
    
    // Send some data
    if( send(sock , data.c_str() , strlen( data.c_str() ) , 0) < 0)
    {
        perror("Send failed : ");
        return false;
    }
    
    cout<<"Data send\n";

    return true;
}

/*
    Receive data from the connected host
*/
string TcpClient::receive(int size=512)
{
    char buffer[size];
    string reply;

    //Receive a reply from the server
    if( recv(sock , buffer , sizeof(buffer) , 0) < 0)
    {
        puts("recv failed");
        return NULL;
    }

    reply = buffer;
    response_data = reply;
    
    return reply;
}

int main(int argc , char *argv[])
{
    TcpClient c;
    string HOST = "127.0.0.1";

    //connect to host
    c.conn(HOST , 3001);

    while (1) {
        int randomNumber = rand() % 100;
        std::string binaryData = std::bitset<8>(randomNumber).to_string();
        //send some data
        cout<<"----------------------------\n";
        c.send_data(randomNumber, binaryData);
        //receive and echo reply
        cout<<c.receive(1024);
        cout<<"\n\n----------------------------\n\n\n";
        sleep(5);
    }

    //done
    return 0;
}