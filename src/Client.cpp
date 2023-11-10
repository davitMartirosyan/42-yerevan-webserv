/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 10:29:55 by dmartiro          #+#    #+#             */
/*   Updated: 2023/11/02 23:50:13 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client( void )
{
}

Client::Client(sock_t clfd, sock_t srfd)
{
    this->clientFd = clfd;
    this->serverFd = srfd;
}

Client::Client(sock_t clfd)
{
    this->clientFd = clfd;
    this->serverFd = -1;
}

sock_t Client::getFd( void ) const
{
    return (this->clientFd);
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