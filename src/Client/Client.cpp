/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 10:29:55 by dmartiro          #+#    #+#             */
/*   Updated: 2023/11/01 08:07:09 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client(sock_t clfd)
{
    this->fd = clfd;
    this->http = new char[READ_BUFFER];
}

sock_t Client::getFd( void ) const
{
    return (this->fd);
}

Client::~Client()
{
    delete [] this->http;
}

void Client::setFd(sock_t fd)
{
    this->fd = fd;
}