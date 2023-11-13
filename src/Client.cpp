/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 10:29:55 by dmartiro          #+#    #+#             */
/*   Updated: 2023/11/14 01:25:30 by dmartiro         ###   ########.fr       */
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
    rd = recv(fd, http, sizeof(http), 0);
    http[rd] = '\0';
    parse_typeface face = HTTPRequest::parse(http);
    if (face == HTTP_REQUEST_LINE_ERROR)
    {
        std::cout << "error in request line" << std::endl;
    }
    else if (face == HTTP_HEADER_ERROR)
    {
        std::cout << "error header line" << std::endl;
    }
}