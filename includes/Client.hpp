/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 10:29:10 by dmartiro          #+#    #+#             */
/*   Updated: 2023/11/12 21:02:57 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP
#include "Libs.hpp"
#include "HTTPRequest.hpp"
#include "ServerManager.hpp"
// #include "HTTPServer.hpp"

// class HTTPServer;
class ServerManager;
class Client : public HTTPRequest
{
    public:
        Client( void );
        Client(sock_t clfd, sock_t srfd);
        Client(sock_t clfd);
        ~Client();
    public:
        void appendRequest( void );
        void request(ServerManager &mgn);
    public:
        sock_t getFd( void ) const;
        sock_t getServerFd( void ) const;
    private:
        int rd;
        sock_t fd;
        sock_t serverFd;
    private:
        struct sockaddr_in ClientInfo;
        struct sockaddr ClientAddress;
        struct sockaddr_storage addressStorage;
};

#endif