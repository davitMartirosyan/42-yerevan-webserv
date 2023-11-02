/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 10:29:55 by dmartiro          #+#    #+#             */
/*   Updated: 2023/11/02 00:41:12 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client( void )
{
}

Client::Client(sock_t clfd)
{
    this->fd = clfd;
}

sock_t Client::getFd( void ) const
{
    return (this->fd);
}

Client::~Client()
{
}