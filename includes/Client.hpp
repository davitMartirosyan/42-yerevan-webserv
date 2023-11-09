/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 10:29:10 by dmartiro          #+#    #+#             */
/*   Updated: 2023/11/10 00:44:47 by dmartiro         ###   ########.fr       */
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
        Client(sock_t clfd);
        ~Client();
    public:
        void request(ServerManager &mgn);
    public:
        sock_t getFd( void ) const;
    private:
        sock_t fd;
    private:
        struct sockaddr_in ClientInfo;
        struct sockaddr ClientAddress;
        struct sockaddr_storage addressStorage;
};

#endif