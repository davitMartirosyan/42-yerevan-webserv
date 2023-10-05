/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPServer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:45:11 by dmartiro          #+#    #+#             */
/*   Updated: 2023/10/06 01:21:28 by dmartiro         ###   ########.fr       */
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
    setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
    if (server_socket < 0)
        throw ServerException("Socket");
    remoteAddr.sin_family = domain;
    remoteAddr.sin_addr.s_addr = inet_addr(ipv4.c_str());
    remoteAddr.sin_port = htons(port);
    if (bind(server_socket, (struct sockaddr*)&remoteAddr, sizeof(remoteAddr)) < 0)
        throw ServerException("Bind");
    if (listen(server_socket, backlog) < 0)
        throw ServerException("Listen");
}

HTTPServer::~HTTPServer()
{
}