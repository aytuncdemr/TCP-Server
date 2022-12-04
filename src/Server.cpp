#include "Server.hpp"


Server::Server(const std::string &ip,const uint32_t &port,const uint32_t &max_client_size):m_ip{ip},m_port{port},m_client_size{max_client_size},m_is_server_alive{true}{

    std::cout << "[Server object created " << this << "]" << std::endl;
    
    init_winsock();

}

void Server::init_winsock(){
    
    std::cout << "[Initializing winsock]" << std::endl;

    WSADATA ws_data;
    
    int result = WSAStartup(MAKEWORD(2,2),&ws_data);

    if(!check_error(result)){
    
        std::cout << "[Done]" << std::endl;
    
        create_server_socket();
    
    }
    
}

void Server::create_server_socket(){

    std::cout << "[Creating TCP server socket]" << std::endl;

    m_server_socket = socket(AF_INET,SOCK_STREAM,0);

    if(!check_error(m_server_socket,INVALID_SOCKET)){
    
        std::cout << "[Done]" << std::endl;

        bind_server_socket();
    
    }

}

void Server::bind_server_socket(){

    std::cout << "[Binding server socket with ip of " << m_ip << ":" << m_port << "]" << std::endl; 

    m_addr.sin_addr.S_un.S_addr = inet_addr(m_ip.c_str());

    m_addr.sin_port = htons(m_port);

    m_addr.sin_family = AF_INET;

    int result = bind(m_server_socket,(struct sockaddr*)&m_addr,sizeof(struct sockaddr));

    if(!check_error(result)){
    
        std::cout << "[Done]" << std::endl;

        listen_server_socket();
        
    }


}

void Server::listen_server_socket(){

    std::cout << "[Server is listening with maximum client size of " << m_client_size << "]" << std::endl;

    int result = listen(m_server_socket,m_client_size);

    if(!check_error(result)){
    
        std::cout << "[Done]" << std::endl;

        accept_client_connection();
    
    }

}

void Server::accept_client_connection(){

    std::cout << "[Server is ready to accept client connections]" << std::endl;

    while(m_is_server_alive){

        struct sockaddr_in client_addr;

        int addr_length = sizeof(struct sockaddr_in);

        SOCKET client_socket = accept(m_server_socket,(struct sockaddr*)&client_addr,&addr_length);

        if(!check_error(client_socket,INVALID_SOCKET)){

            get_client_name(client_socket);

        }

    }
    
}

void Server::get_client_name(SOCKET &client_socket){

    char name_data[256];

    int result = recv(client_socket,name_data,256,0);

    if(!check_error(result)){

       std::cout << "[" << name_data << " connected to the server]" << std::endl;  

    }
    
}

void Server::clean_winsock(){

    std::cout << "[Cleaning winsock]" << std::endl;

    int result = WSACleanup();

    if(!check_error(result)){

        std::cout << "[Done]" << std::endl;

    }
    
}

bool Server::check_error(const int &result,const int &err_value){

    if(result == err_value){

        std::cout << "Error ["  << std::system_category().message(WSAGetLastError()) << "]";

        return true;
    }

    return false;
}
