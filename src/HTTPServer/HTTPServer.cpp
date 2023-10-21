/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPServer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 23:57:39 by dmartiro          #+#    #+#             */
/*   Updated: 2023/10/21 11:35:07 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HTTPServer.hpp"

HTTPServer::HTTPServer(int sock)
{
    fd = sock;
}

HTTPServer::~HTTPServer()
{
    
}

int HTTPServer::getServerSocket( void )
{
    return (fd);
}