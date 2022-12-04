#ifndef _SERVER_HPP_
#define _SERVER_HPP_

#include <iostream>
#include <winsock2.h>
#include <string>

class Server{

    uint32_t m_port;

    uint32_t m_client_size;

    std::string m_ip;

    struct sockaddr_in m_addr; 

    SOCKET m_server_socket;

    bool m_is_server_alive;

    public:

        Server():Server{"127.0.0.1",8000,6}{


        }

        ~Server(){

            clean_winsock();

        }

        Server(const std::string &ip,const uint32_t &port,const uint32_t &max_client_size);

        void init_winsock();

        void create_server_socket();

        void bind_server_socket();

        void listen_server_socket();

        void accept_client_connection();

        void get_client_name(SOCKET &client_socket);

        void clean_winsock();

        bool check_error(const int &result,const int &err_value = -1);

};

#endif