/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tcp.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 21:34:14 by dmartiro          #+#    #+#             */
/*   Updated: 2023/10/31 00:20:47 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Tcp.hpp"

Tcp::Tcp( void )
{
	memset(&this->rules, 0, sizeof(rules));
	memset(&this->Socket, 0, sizeof(Socket));
	memset(&this->SocketAddress, 0, sizeof(SocketAddress));
	memset(&this->SocketStorage, 0, sizeof(SocketStorage));
}

Tcp::~Tcp()
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