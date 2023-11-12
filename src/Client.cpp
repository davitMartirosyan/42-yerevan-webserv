/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 10:29:55 by dmartiro          #+#    #+#             */
/*   Updated: 2023/11/12 21:35:57 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client( void )
{
    this->rd = 0;
}

Client::Client(sock_t clfd, sock_t srfd)
{
    this->fd = clfd;
    this->serverFd = srfd;
    this->rd = 0;
}

Client::Client(sock_t clfd)
{
    this->fd = clfd;
    this->serverFd = -1;
}

sock_t Client::getFd( void ) const
{
    return (this->fd);
}

sock_t Client::getServerFd( void ) const
{
    return (this->serverFd);
}

Client::~Client()
{
}

void Client::request(ServerManager &mgn)
{
    (void)mgn;
}

void Client::appendRequest( void )
{
    rd = recv(fd, http, sizeof(http), 0);
    http[rd] = '\0';
    httpRequest.append(http);
    if (httpRequest.find_first_not_of("\r\n") != std::string::npos)
    {
        int sp = 0;
        requestLine = httpRequest.substr(0, httpRequest.find_first_of("\r\n"));
        std::cout << requestLine << std::endl;
        for(size_t i = 0; i < requestLine.size(); i++)
            if (requestLine[i] == ' ')
                sp++;
        if (sp == 2)
        {
            std::string tmpLine = requestLine;
            method = tmpLine.substr(0, tmpLine.find_first_of(" "));
            tmpLine.erase(0, tmpLine.find_first_of(" ") + 1);
            path = tmpLine.substr(0, tmpLine.find_first_of(" "));
            tmpLine.erase(0, tmpLine.find_first_of(" ") + 1);
            version = tmpLine;
            std::cout << "|" << method << "|" << std::endl;
            std::cout << "|" << path << "|" << std::endl;
            std::cout << "|" << version << "|" << std::endl;
        }
    }
}