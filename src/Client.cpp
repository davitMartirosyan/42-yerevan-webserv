/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 10:29:55 by dmartiro          #+#    #+#             */
/*   Updated: 2023/11/16 01:52:27 by dmartiro         ###   ########.fr       */
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
    while ((rd = recv(fd, http, sizeof(http), 0)) > 0)
    {
        if (rd > 0)
        {
            http[rd] = '\0';
            httpRequest.append(http);
        }
        else
            break;
    }
    // std::cout << "**************************************************************" << std::endl;
    // std::cout << httpRequest << std::endl;
    // std::cout << "**************************************************************" << std::endl;
    
    HTTPRequest::parsing(fd);
    
    
    // rd = recv(fd, http, sizeof(http), 0);
    // http[rd] = '\0';
    // HTTPRequest::parse(fd, http);
}