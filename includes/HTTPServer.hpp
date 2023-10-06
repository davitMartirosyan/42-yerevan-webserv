/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPServer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:44:02 by dmartiro          #+#    #+#             */
/*   Updated: 2023/10/06 13:08:22 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPSERVER_HPP
#define HTTPSERVER_HPP
#include "Lib.hpp"
#include "HTTPRequest.hpp"
#include "ServerException.hpp"

class HTTPServer
{
    public:
        HTTPServer(std::string const &ipv4, int domain, int type, int protocol, int port, int backlog);
        ~HTTPServer();
    public: //external interface
        HTTPRequest request;
    public: //interface
        int getServerSocket( void ) const;
    private:
        std::map<unsigned int, HTTPRequest> clients;
    private:
        struct  sockaddr_in remoteAddr;
    private:
        std::string ipv4;
    private:
        int server_socket;
        int domain;
        int type;
        int protocol;
        int port;
        int backlog;
};

#endif

