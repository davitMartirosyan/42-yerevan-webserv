/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPServer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:45:11 by dmartiro          #+#    #+#             */
/*   Updated: 2023/10/06 12:54:39 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HTTPServer.hpp"

HTTPServer::HTTPServer(std::string const &ipv4, int domain, int type, int protocol, int port, int backlog)
{
    int opt = 1;
    this->domain = domain;
    this->type = type;
    this->protocol = protocol;
    this->port = port;
    this->server_socket = socket(domain, type, protocol);
    this->backlog = backlog;
    if (server_socket < 0)
        throw ServerException("Socket");
    // if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR & SO_REUSEPORT, &opt, sizeof(opt)) < 0)
    //     throw ServerException("Setsockopt");
    remoteAddr.sin_family = domain;
    remoteAddr.sin_addr.s_addr = INADDR_ANY;
    remoteAddr.sin_port = htons(port);
    if (bind(server_socket, (struct sockaddr*)&remoteAddr, sizeof(remoteAddr)) < 0)
        throw ServerException("Bind");
    if (listen(server_socket, backlog) < 0)
        throw ServerException("Listen");
}

HTTPServer::~HTTPServer()
{
}

int HTTPServer::getServerSocket( void ) const
{
    return (this->server_socket);
}