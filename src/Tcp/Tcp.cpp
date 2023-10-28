/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tcp.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 21:34:14 by dmartiro          #+#    #+#             */
/*   Updated: 2023/10/28 13:12:15 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Tcp.hpp"

Tcp::Tcp( void )
{
	memset(&this->ServerAddress, 0, sizeof(ServerAddress));
	memset(&this->SocketInfo, 0, sizeof(SocketInfo));
	memset(&this->SocketAddress, 0, sizeof(SocketAddress));
	memset(&this->SocketStorage, 0, sizeof(SocketStorage));
}

Tcp::~Tcp()
{
	
}

void Tcp::up( void )
{
	
}

const char* Tcp::pton(uint32_t ipv) const
{
    char *ip = new char[16];
    std::stringstream ss;
    ss << ((int)(ipv >> 24) & 0XFF) << "." << ((int)(ipv >> 16) & 0XFF) << "." << ((int)(ipv >> 8) & 0XFF) << "." << ((int)(ipv) & 0XFF);
    int i = -1;
    while (++i < ss.str().size())
        ip[i] = ss.str().c_str()[i];
    ip[i] = '\0';
    return (ip);
}