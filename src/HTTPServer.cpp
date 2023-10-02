/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPServer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:45:11 by dmartiro          #+#    #+#             */
/*   Updated: 2023/10/02 18:02:44 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HTTPServer.hpp"

HTTPServer::HTTPServer(int domain, int type, int protocol)
{
    this->domain = domain;
    this->type = type;
    this->protocol = protocol;
    this->sock = socket(domain, type, protocol);
    if (sock < 0)
    {
        perror("Could not Create new Socket: ");
        exit(EXIT_FAILURE);
    }
}

HTTPServer::~HTTPServer()
{
}

void HTTPServer::bindServer(std::string const &ip, int port)
{
    remoteAddr.sin_family = domain;
    remoteAddr.sin_addr.s_addr = inet_addr(ip.c_str());
    remoteAddr.sin_port = htons(port);
    if (bind(sock, (struct sockaddr*)&remoteAddr, sizeof(remoteAddr)) < 0)
    {
        perror("Could not bind ip and port: ");
        exit(EXIT_FAILURE);
    }
    
}

void HTTPServer::startListening(int backlog)
{
    this->backlog = backlog;
    if (listen(sock, backlog) < 0)
    {
        perror("Could not start listening: ");
        exit(EXIT_FAILURE);
    }
}