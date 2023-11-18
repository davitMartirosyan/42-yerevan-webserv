/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 10:29:55 by dmartiro          #+#    #+#             */
/*   Updated: 2023/11/18 15:42:54 by dmartiro         ###   ########.fr       */
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


void Client::appendRequest( void )
{
    int count = 0;
    fd = 4;
    while ((rd = recv(fd, http, sizeof(http), 0)) > 0)
    {
        if (rd > 0)
        {
            count++;
            http[rd] = '\0';
            httpRequest.append(http);
        }
        else
            break;
    }
    std::string data;
    HTTPRequest::parsing(fd);
    HTTPRequest::processing(fd);
    int r = 0;
    int size = 0;
    
    while ((r = recv(fd, http, sizeof(http), 0)) > 0)
    {
        if (r > 0)
        {
            http[r] = '\0';
            data.append(http);
            size += r;
        }
        else
            break;
    }
    std::cout << strerror(errno) << std::endl;
    std::cout << bodySize << " | " << size << std::endl;
    std::cout << data << std::endl;
}