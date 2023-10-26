/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tcp.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 21:34:14 by dmartiro          #+#    #+#             */
/*   Updated: 2023/10/26 14:03:13 by dmartiro         ###   ########.fr       */
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